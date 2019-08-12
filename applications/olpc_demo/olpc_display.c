#include <rtthread.h>
#if defined(RT_USING_OLPC_DEMO)
#include <stdio.h>
#include <math.h>

#include "color_palette.h"
#include "drv_display.h"
#include "drv_heap.h"
#include "image_info.h"
#include "olpc_display.h"

#define PI 3.1415926535898
#define NULL_CODE           -1      // indicates a NULL prefix
#define CLEAR_CODE          256     // code to flush dictionary and restart decoder
#define FIRST_STRING        257     // code of first dictionary string

/**
 * color palette for 1bpp
 */
static uint32_t bpp1_lut[2] =
{
    0x00000000, 0x00ffffff
};

/**
 * color palette for RGB332
 */
static uint32_t bpp_lut[256] = {0};

/**
 * color palette for RGB332 and BGR233,default format is RGB332.
 */
static  struct rt_display_data *g_disp_data = RT_NULL;

static size_t read_count, write_count;

/**
 * decompress read buffer.
 */
static int rt_decompress_read_buff(image_info_t *img_info)
{
    int value = img_info->data[read_count++];
    if (read_count == img_info->size)
    {
        value = EOF;
    }
    return value;
}

/**
 * decompress write buffer.
 */
static void rt_decompress_write_buff(int value, rt_uint8_t *fb, rt_int32_t xVir, rt_int32_t xoffset, rt_int32_t yoffset, int width)
{
    xoffset = xoffset + write_count % width;
    yoffset = yoffset + write_count / width;
    *((uint8_t *)((uint32_t)fb + (yoffset)* xVir + xoffset)) = value;

    if (value == EOF)
    {
        return;
    }

    write_count++;
}

/**
 * decompress sub function.
 */
static int rt_display_decompress(image_info_t *img_info, rt_uint8_t *fb, rt_int32_t xVir, rt_int32_t xoffset, rt_int32_t yoffset)
{
    int read_byte, next = FIRST_STRING, prefix = CLEAR_CODE, bits = 0, total_codes;
    unsigned char *terminators, *reverse_buffer;
    unsigned long shifter = 0;
    short *prefixes;

    write_count = 0;
    read_count = 0;

    if ((read_byte = (rt_decompress_read_buff(img_info))) == EOF || (read_byte & 0xfc))  //sanitize first byte
    {
        //rt_kprintf("rt_display_decompress 111\n");
        return RT_ERROR;
    }

    // based on the "maxbits" parameter, compute total codes and allocate dictionary storage
    total_codes = 512 << (read_byte & 0x3);
    reverse_buffer = malloc((total_codes - 256) * sizeof(reverse_buffer[0]));
    prefixes = malloc((total_codes - 256) * sizeof(prefixes[0]));
    terminators = malloc((total_codes - 256) * sizeof(terminators[0]));

    if (!reverse_buffer || !prefixes || !terminators)       // check for mallco() failure
    {
        if (reverse_buffer)
            free(reverse_buffer);
        if (prefixes)
            free(prefixes);
        if (terminators)
            free(terminators);

        //rt_kprintf("rt_display_decompress 222\n");
        return RT_ERROR;
    }

    // This is the main loop where we read input symbols. The values range from 0 to the code value
    // of the "next" string in the dictionary (although the actual "next" code cannot be used yet,
    // and so we reserve that code for the END_CODE). Note that receiving an EOF from the input
    // stream is actually an error because we should have gotten the END_CODE first.
    while (1)
    {
        int code_bits = next < 1024 ? (next < 512 ? 8 : 9) : (next < 2048 ? 10 : 11), code;
        int extras = (1 << (code_bits + 1)) - next - 1;

        do
        {
            if ((read_byte = (rt_decompress_read_buff(img_info))) == EOF)
            {
                free(terminators);
                free(prefixes);
                free(reverse_buffer);

                //rt_kprintf("rt_display_decompress 333\n");
                //return RT_ERROR;
                return RT_EOK;
            }

            shifter |= (long)read_byte << bits;
        }
        while ((bits += 8) < code_bits);

        // first we assume the code will fit in the minimum number of required bits
        code = (int)shifter & ((1 << code_bits) - 1);
        shifter >>= code_bits;
        bits -= code_bits;

        // but if code >= extras, then we need to read another bit to calculate the real code
        // (this is the "adjusted binary" part)
        if (code >= extras)
        {
            if (!bits)
            {
                if ((read_byte = (rt_decompress_read_buff(img_info))) == EOF)
                {
                    free(terminators);
                    free(prefixes);
                    free(reverse_buffer);

                    //rt_kprintf("rt_display_decompress 444\n");
                    //return RT_ERROR;
                    return RT_EOK;
                }

                shifter = (long)read_byte;
                bits = 8;
            }

            code = (code << 1) - extras + (shifter & 1);
            shifter >>= 1;
            bits--;
        }

        if (code == next)                   // sending the maximum code is reserved for the end of the file
            break;
        else if (code == CLEAR_CODE)        // otherwise check for a CLEAR_CODE to start over early
            next = FIRST_STRING;
        else if (prefix == CLEAR_CODE)      // this only happens at the first symbol which is always sent
        {
            rt_decompress_write_buff(code, fb, xVir, xoffset, yoffset, img_info->w);                   // literally and becomes our initial prefix
            next++;
        }
        // Otherwise we have a valid prefix so we step through the string from end to beginning storing the
        // bytes in the "reverse_buffer", and then we send them out in the proper order. One corner-case
        // we have to handle here is that the string might be the same one that is actually being defined
        // now (code == next-1). Also, the first 256 entries of "terminators" and "prefixes" are fixed and
        // not allocated, so that messes things up a bit.
        else
        {
            int cti = (code == next - 1) ? prefix : code;
            unsigned char *rbp = reverse_buffer, c;

            do *rbp++ = cti < 256 ? cti : terminators[cti - 256];      // step backward through string...
            while ((cti = (cti < 256) ? NULL_CODE : prefixes[cti - 256]) != NULL_CODE);

            c = *--rbp;     // the first byte in this string is the terminator for the last string, which is
            // the one that we'll create a new dictionary entry for this time
            do rt_decompress_write_buff(*rbp, fb, xVir, xoffset, yoffset, img_info->w);                        // send string in corrected order (except for the terminator
            while (rbp-- != reverse_buffer);        // which we don't know yet)

            if (code == next - 1)
                rt_decompress_write_buff(c, fb, xVir, xoffset, yoffset, img_info->w);

            prefixes[next - 1 - 256] = prefix;     // now update the next dictionary entry with the new string
            terminators[next - 1 - 256] = c;       // (but we're always one behind, so it's not the string just sent)

            if (++next == total_codes)              // check for full dictionary, which forces a reset (and, BTW,
                next = FIRST_STRING;                // means we'll never use the dictionary entry we just wrote)
        }

        prefix = code;      // the code we just received becomes the prefix for the next dictionary string entry
        // (which we'll create once we find out the terminator)
    }

    free(terminators);
    free(prefixes);
    free(reverse_buffer);

    return RT_EOK;
}

/**
 * float angle : rotate angle
 * int w
 * int h :
 * unsigned char *src :
 * unsigned char *dst :
 * int dst_str :
*/
static unsigned char rt_display_SegGradSelect(int x, int y, int w, int h, int x_res, int y_res, unsigned char *data, unsigned char *src)
{
    unsigned char alpha = 0xff;
    int pos = 0;

    if (x == -1 && y == -1)
    {
        alpha = (x_res * y_res) >> 8;
        pos = (y + 1) * w + (x + 1);
    }
    else if (x == w && y == -1)
    {
        alpha = ((255 - x_res) * y_res) >> 8;
        pos = (y + 1) * w + (x - 1);
    }
    else if (x == -1 && y == h)
    {
        alpha = ((x_res) * (255 - y_res)) >> 8;
        pos = (y - 1) * w + (x + 1);
    }
    else if (x == w && y == h)
    {
        alpha = ((255 - x_res) * (255 - y_res)) >> 8;
        *data = src[(y - 1) * w + (x - 1)];
    }
    else if (x == -1 && y > -1 && y < h)
    {
        alpha = x_res;
        pos = y * w + (x + 1);
    }
    else if (y == -1 && x > -1 && x < w)
    {
        alpha = y_res;
        pos = (y + 1) * w + x;
    }
    else if (x == w && y > -1 && y < h)
    {
        alpha = 255 - x_res;
        pos = y * w + x - 1;
    }
    else if (y == h && x > -1 && x < w)
    {
        alpha = 255 - y_res;
        pos = (y - 1) * w + x;
    }

    *data = src[pos];

    return alpha;
}

/**
 * display rotate.
 */
void rt_display_rotate(float angle, int w, int h, unsigned char *src, unsigned char *dst, int dst_str, int xcen, int ycen)
{
    int x, y;

    int xlt, xrt, xld, xrd;
    int ylt, yrt, yld, yrd;
    int xmin, xmax, ymin, ymax;

    float cosa = cos((angle * PI) / 180);
    float sina = sin((angle * PI) / 180);

    xlt = cosa * (-xcen) + -sina * (-ycen);
    ylt = sina * (-xcen) +  cosa * (-ycen);
    xrt = cosa * (w - xcen) + -sina * (-ycen);
    yrt = sina * (w - xcen) +  cosa * (-ycen);
    xld = cosa * (-xcen) + -sina * (h - ycen);
    yld = sina * (-xcen) +  cosa * (h - ycen);
    xrd = cosa * (w - xcen) + -sina * (h - ycen);
    yrd = sina * (w - xcen) +  cosa * (h - ycen);

    xmin = MIN(xrd, MIN(xld, MIN(xlt, xrt))) - 1;
    xmax = MAX(xrd, MAX(xld, MAX(xlt, xrt))) + 1;
    ymin = MIN(yrd, MIN(yld, MIN(ylt, yrt))) - 1;
    ymax = MAX(yrd, MAX(yld, MAX(ylt, yrt))) + 1;

    float x_pos, y_pos;
    unsigned char alpha;

    int m = ymin;
    for (int j = ymin; j < ymax; j++)
    {
        int n = xmin;
        for (int i = xmin; i < xmax; i++)
        {
            x_pos = (cosa * i + sina * j) + xcen;
            y_pos = (-sina * i + cosa * j) + ycen;
            x = floor(x_pos);
            y = floor(y_pos);

            if (x_pos >= 0 && x_pos < w && y_pos >= 0 && y_pos < h)
            {
                dst[m * dst_str + n] = src[y * w + x];
            }
            else if ((x >= -1) && (y >= -1) && (x <= w) && (y <= h))
            {
                int x_res = (x_pos - x) * (1 << 8);
                int y_res = (y_pos - y) * (1 << 8);
                unsigned char data = 0;

                alpha = rt_display_SegGradSelect(x, y, w, h, x_res, y_res, &data, src);

                unsigned char sr, sg, sb, dr, dg, db;
                sr = (dst[m * dst_str + n]) & 0x7;
                sg = (dst[m * dst_str + n] >> 3) & 0x7;
                sb = (dst[m * dst_str + n] >> 6) & 0x3;

                dr = (data) & 0x7;
                dg = (data >> 3) & 0x7;
                db = (data >> 6) & 0x3;

                dr = (sr * (255 - alpha) + dr * alpha) >> 8;
                dg = (sg * (255 - alpha) + dg * alpha) >> 8;
                db = (sb * (255 - alpha) + db * alpha) >> 8;

                dst[m * dst_str + n] = dr | (dg << 3) | (db << 6);
            }
            n++;
        }
        m++;
    }
}

/**
 * color palette for RGB332 and BGR233,default format is RGB332.
 */
static void rt_display_update_lut(int format)
{
    int i = 0;
    int r2, r1, r0, g2, g1, g0, b1, b0;
    int R, G, B;
    float f;

    for (i = 0; i < 256; i++)
    {
        if (format == FORMAT_RGB_332)
        {
            r2 = (i & 0x80) >> 7;
            r1 = (i & 0x40) >> 6;
            r0 = (i & 0x20) >> 5;
            g2 = (i & 0x10) >> 4;
            g1 = (i & 0x8) >> 3;
            g0 = (i & 0x4) >> 2;
            b1 = (i & 0x2) >> 1;
            b0 = (i & 0x1) >> 0;
            R = (r2 << 7) | (r1 << 6) | (r0 << 5) | (r2 << 4) | (r1 << 3) | (r0 << 2) | (r2 << 1) | r1;
            G = (g2 << 7) | (g1 << 6) | (g0 << 5) | (g2 << 4) | (g1 << 3) | (g0 << 2) | (g2 << 1) | g1;
            B = (b1 << 7) | (b0 << 6) | (b1 << 5) | (b0 << 4) | (b1 << 3) | (b0 << 2) | (b1 << 1) | b0;
        }
        else if (format == FORMAT_BGR_233)
        {
            b1 = (i & 0x80) >> 7;
            b0 = (i & 0x40) >> 6;
            g2 = (i & 0x20) >> 5;
            g1 = (i & 0x10) >> 4;
            g0 = (i & 0x8) >> 3;
            r2 = (i & 0x4) >> 2;
            r1 = (i & 0x2) >> 1;
            r0 = (i & 0x1) >> 0;
            R = (r2 << 7) | (r1 << 6) | (r0 << 5) | (r2 << 4) | (r1 << 3) | (r0 << 2) | (r2 << 1) | r1;
            G = (g2 << 7) | (g1 << 6) | (g0 << 5) | (g2 << 4) | (g1 << 3) | (g0 << 2) | (g2 << 1) | g1;
            B = (b1 << 7) | (b0 << 6) | (b1 << 5) | (b0 << 4) | (b1 << 3) | (b0 << 2) | (b1 << 1) | b0;
        }
        else
        {
            f = (i + 0.5F) / 256;
            R = (unsigned char)((float)pow(f, 1 / GAMMA_RED) * 255 - 0.5F);
            G = (unsigned char)((float)pow(f, 1 / GAMMA_GREEN) * 255 - 0.5F);
            B = (unsigned char)((float)pow(f, 1 / GAMMA_BLUE) * 255 - 0.5F);
        }
        bpp_lut[i] = (R << 16) | (G << 8) | B;

        /* if (i % 4 == 0)
            printf("\n");
        printf("0x%08x, ", bpp_lut[i]); */
    }
}

/**
 * fill image data to fb buffer
 */
void rt_display_img_fill(image_info_t *img_info, rt_uint8_t *fb, rt_int32_t xVir, rt_int32_t xoffset, rt_int32_t yoffset)
{
    rt_err_t ret = RT_EOK;
    rt_int32_t x, y, i;
    rt_uint8_t bitval;

    if (img_info->type == IMG_TYPE_COMPRESS)
    {
        if (img_info->pixel == RTGRAPHIC_PIXEL_FORMAT_RGB332)
        {
            ret = rt_display_decompress(img_info, fb, xVir, xoffset, yoffset);
            RT_ASSERT(ret == RT_EOK);
        }
        else //if (img_info->pixel == RTGRAPHIC_PIXEL_FORMAT_GRAY1)
        {
            /* code */
        }

    }
    else //if (img_info->type == IMG_TYPE_RAW)
    {
        if (img_info->pixel == RTGRAPHIC_PIXEL_FORMAT_RGB332)
        {
            for (i = 0, y = yoffset; y < yoffset + img_info->h; y++)
            {
                for (x = xoffset; x < xoffset + img_info->w; x++)
                {
                    fb[(y * xVir) + x] = img_info->data[i++];
                }
            }
        }
        else //if (img_info->pixel == RTGRAPHIC_PIXEL_FORMAT_GRAY1)
        {
            RT_ASSERT((xVir % 8) == 0);

            if ((xoffset % 8) == 0)
            {
                for (y = yoffset; y < yoffset + img_info->h; y++)
                {
                    i = (y - yoffset) * ((img_info->w + 7) / 8);
                    for (x = xoffset; x < xoffset + img_info->w; x += 8)
                    {
                        fb[y * (xVir / 8) + x / 8] = img_info->data[i++];
                    }

                    if ((img_info->w % 8) == 0)
                    {
                        rt_uint8_t maskval = 0xff >> (img_info->w % 8);
                        fb[y * (xVir / 8) + x / 8] &= maskval;
                        fb[y * (xVir / 8) + x / 8] |= (img_info->data[i++] & (~maskval));
                    }
                }
            }
            else
            {
                for (y = yoffset; y < yoffset + img_info->h; y++)
                {
                    i = (y - yoffset) * ((img_info->w + 7) / 8) * 8;
                    for (x = xoffset; x < xoffset + img_info->w; x++)
                    {
                        bitval = (img_info->data[i / 8] << (i % 8)) & 0x80;

                        fb[y * (xVir / 8) + x / 8] &= ~(0x80 >> (x % 8));
                        fb[y * (xVir / 8) + x / 8] |= bitval >> (x % 8);

                        i++;
                    }
                }
            }
        }
    }
}

/**
 * Configuration win layers.
 */
rt_err_t rt_display_win_layer_set(rt_device_t device,
                                  uint8_t   winId,    rt_bool_t winEn,
                                  uint8_t  *framebuf, uint32_t len,
                                  uint16_t srcW,      uint16_t srcH,
                                  uint16_t srcX,      uint16_t srcY,
                                  uint16_t dstY,      uint16_t dstH)
{
    struct rt_device_graphic_info info;
    struct CRTC_WIN_STATE win_config;
    struct VOP_POST_SCALE_INFO post_scale;
    struct rt_display_data *disp_data = g_disp_data;
    rt_err_t ret = RT_EOK;

    //rt_kprintf("winID = %d, srcW=%d, srcH=%d, srcX= %d, srcY = %d, dstY=%d, dstH = %d\n",
    //           winId, srcW, srcH, srcX, srcY, dstY, dstH);

    RT_ASSERT(winId <= 1);

    ret = rt_device_control(device, RTGRAPHIC_CTRL_GET_INFO, &info);
    RT_ASSERT(ret == RT_EOK);

    rt_memset(&win_config, 0, sizeof(struct CRTC_WIN_STATE));

    win_config.winId = winId;
    win_config.winEn = winEn;
    win_config.winUpdate = winEn;

    win_config.zpos = 0;

    win_config.yrgbAddr = (uint32_t)framebuf;
    win_config.cbcrAddr = (uint32_t)framebuf;
    win_config.yrgbLength = len;
    win_config.cbcrLength = len;
    win_config.xVir = srcW;

    win_config.srcX  = srcX;
    win_config.srcY  = srcY;
    win_config.srcW  = srcW;
    win_config.srcH  = srcH;

    win_config.xLoopOffset = 0;
    win_config.yLoopOffset = 0;

    win_config.alphaEn = 0;
    win_config.alphaMode = VOP_ALPHA_MODE_PER_PIXEL;
    win_config.alphaPreMul = VOP_NON_PREMULT_ALPHA;

    post_scale.srcW = disp_data->xres;
    post_scale.srcH = dstH;
    post_scale.dstX = 0;
    post_scale.dstY = dstY;
    post_scale.dstW = disp_data->xres;
    post_scale.dstH = dstH; //dstH * HSCALE

    if (winId == 0)
    {
        win_config.lut = bpp_lut;
        win_config.format = info.pixel_format;
    }
    else if (winId == 1)
    {
        //win_config.lut = bpp_lut;
        //win_config.format = info.pixel_format;
        win_config.lut = bpp1_lut;
        win_config.format = RTGRAPHIC_PIXEL_FORMAT_GRAY1;
    }

    ret = rt_device_control(device,
                            RK_DISPLAY_CTRL_SET_SCALE, &post_scale);
    RT_ASSERT(ret == RT_EOK);
    ret = rt_device_control(device, RK_DISPLAY_CTRL_SET_PLANE, &win_config);
    RT_ASSERT(ret == RT_EOK);

    ret = rt_device_control(device, RK_DISPLAY_CTRL_COMMIT, NULL);
    RT_ASSERT(ret == RT_EOK);
    return ret;
}

/**
 * Clear screen for display initial.
 */
int rt_display_screen_clear(rt_device_t device)
{
    rt_err_t ret = RT_EOK;
    struct CRTC_WIN_STATE win_config;
    struct rt_device_graphic_info info;

    ret = rt_device_control(device, RTGRAPHIC_CTRL_GET_INFO, &info);
    RT_ASSERT(ret == RT_EOK);

    win_config.winEn = 0;
    win_config.winId = 0;
    win_config.winUpdate = 1;

    win_config.srcW = info.width;
    win_config.srcH = info.height;
    win_config.crtcX = 0;
    win_config.crtcY = 0;
    win_config.crtcW = info.width;
    win_config.crtcH = info.height;

    ret = rt_device_control(device, RK_DISPLAY_CTRL_SET_PLANE, &win_config);
    RT_ASSERT(ret == RT_EOK);

    rt_thread_delay(200);

    return ret;
}

/**
 * Display screen scroll API.
 */
rt_err_t rt_display_screen_scroll(rt_device_t device, uint8_t winId, uint32_t mode,
                                  uint16_t srcW, uint16_t srcH,
                                  int16_t xoffset, int16_t yoffset)
{
    int ret;
    struct display_state *state = (struct display_state *)device->user_data;
    struct CRTC_WIN_STATE win_config, *win_state = &(state->crtc_state.win_state[winId]);
    struct VOP_POST_SCALE_INFO post_scale;

    memcpy(&win_config, win_state, sizeof(struct CRTC_WIN_STATE));

    win_config.winEn = 1;
    win_config.winId = winId;
    win_config.winUpdate = 1;

    win_config.xVir = srcW;

    win_config.xLoopOffset += xoffset;
    if (win_config.xLoopOffset >= srcW)
    {
        win_config.xLoopOffset = 0;
    }

    win_config.yLoopOffset += yoffset;
    if (win_config.yLoopOffset >= srcH)
    {
        win_config.yLoopOffset = 0;
    }

    post_scale.srcW = g_disp_data->xres;
    post_scale.srcH = win_config.srcH;
    post_scale.dstX = 0;
    post_scale.dstY = win_config.srcY;
    post_scale.dstW = g_disp_data->xres;
    post_scale.dstH = win_config.srcH;

    ret = rt_device_control(device, RK_DISPLAY_CTRL_SET_SCALE, &post_scale);
    RT_ASSERT(ret == RT_EOK);

    ret = rt_device_control(device, RK_DISPLAY_CTRL_SET_PLANE, &win_config);
    RT_ASSERT(ret == RT_EOK);

    ret = rt_device_control(device, RK_DISPLAY_CTRL_COMMIT, NULL);
    RT_ASSERT(ret == RT_EOK);

    return RT_EOK;
}

/**
 * Display driver sync hook, wait for drv_display finish.
 */
rt_err_t rt_display_sync_hook(rt_device_t device, uint8_t winid)
{
    int ret, i;
    struct display_sync display_sync_data;
    display_sync_data.cmd = DISPLAY_SYNC;

    for (i = 0; i < 100; i++)
    {
        ret = rt_device_control(device, RK_DISPLAY_CTRL_DISPLAY_SYNC, &display_sync_data);
        if (ret == RT_EOK)
            break;
        else
            rt_thread_mdelay(1);
    }
    if (i == 100)
        rt_kprintf("rt_display_sync_hook time out\n");

    return RT_EOK;
}

/**
 * Display driver update hook, send update command to drv_display.
 */
rt_err_t rt_display_update_hook(rt_device_t device, uint8_t winid)
{
    rt_err_t ret;

    struct display_state *state = (struct display_state *)device->user_data;
    struct CRTC_WIN_STATE *win_state = &(state->crtc_state.win_state[winid]);
    struct CRTC_WIN_STATE win_config;

    memcpy(&win_config, win_state, sizeof(struct CRTC_WIN_STATE));
    win_config.winEn = 1;
    win_config.winId = winid;
    win_config.winUpdate = 1;

    ret = rt_device_control(device, RK_DISPLAY_CTRL_SET_PLANE, &win_config);
    RT_ASSERT(ret == RT_EOK);

    return RT_EOK;
}

/**
 * Display application initial, initial screen and win layers.
 */
rt_display_data_t rt_display_init(void)
{
    rt_err_t ret = RT_EOK;
    rt_device_t device;
    rt_display_data_t disp_data;
    struct rt_device_graphic_info info;
    struct crtc_lut_state lut_state;

    disp_data = (struct rt_display_data *)rt_malloc(sizeof(struct rt_display_data));
    RT_ASSERT(disp_data != RT_NULL);
    rt_memset((void *)disp_data, 0, sizeof(struct rt_display_data));

    device = rt_device_find("lcd");
    RT_ASSERT(device != RT_NULL);

    ret = rt_device_open(device, RT_DEVICE_OFLAG_RDWR);
    RT_ASSERT(ret == RT_EOK);

    ret = rt_device_control(device, RK_DISPLAY_CTRL_ENABLE, NULL);
    RT_ASSERT(ret == RT_EOK);

    ret = rt_device_control(device, RTGRAPHIC_CTRL_GET_INFO, &info);
    RT_ASSERT(ret == RT_EOK);
    memcpy(&disp_data->info, &info, sizeof(struct rt_device_graphic_info));

    /* init lut */
    rt_display_update_lut(FORMAT_RGB_332);

    /* load lut */
    memset(&lut_state, 0, sizeof(struct crtc_lut_state));
    lut_state.lut = bpp_lut;
    lut_state.lut_size = sizeof(bpp_lut) / sizeof(bpp_lut[0]);
    lut_state.win_id = 0;
    ret = rt_device_control(device, RK_DISPLAY_CTRL_LOAD_LUT, &lut_state);
    RT_ASSERT(ret == RT_EOK);

    lut_state.lut = bpp1_lut;
    lut_state.lut_size = sizeof(bpp1_lut) / sizeof(bpp1_lut[0]);
    lut_state.win_id = 1;
    ret = rt_device_control(device, RK_DISPLAY_CTRL_LOAD_LUT, &lut_state);
    RT_ASSERT(ret == RT_EOK);

    ret = rt_device_control(device, RK_DISPLAY_CTRL_COMMIT, NULL);
    RT_ASSERT(ret == RT_EOK);

    /* clear screen */
    ret = rt_display_screen_clear(device);
    RT_ASSERT(ret == RT_EOK);

    disp_data->xres = WIN_SCALED_W;
    disp_data->yres = WIN_SCALED_H;
    disp_data->device = device;
    g_disp_data = disp_data;

    return disp_data;
}

/**
 * Display application deinitial, free resources.
 */
void rt_display_deinit(rt_display_data_t disp_data)
{
    while (1)
    {
        if (RT_EOK == rt_device_close(disp_data->device))
        {
            break;
        }
        rt_thread_delay(10);
    }

    rt_free(g_disp_data);
}

#endif
