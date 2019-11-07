/**
  * Copyright (c) 2019 Fuzhou Rockchip Electronics Co., Ltd
  *
  * SPDX-License-Identifier: Apache-2.0
  */

#include <rtthread.h>
#if defined(RT_USING_OLPC_DEMO) && defined(OLPC_APP_NOTE_ENABLE)

#include "drv_heap.h"
#include "image_info.h"
#include "olpc_display.h"

#if defined(RT_USING_TOUCH)
#include "drv_touch.h"
#include "olpc_touch.h"
#endif

/**
 * color palette for 1bpp
 */
static uint32_t bpp1_lut[2] =
{
    0x000000, 0x00FFFFFF
};

/*
 **************************************************************************************************
 *
 * Macro define
 *
 **************************************************************************************************
 */
#define NOTE_TEST

#define NOTE_TEXT_GRAY1_WIN    0

#define NOTE_CTRL_REGION_X     ((WIN_LAYERS_W - NOTE_CTRL_FB_W) / 2)
#define NOTE_CTRL_REGION_Y     40
#define NOTE_CTRL_REGION_W     ((WIN_LAYERS_W / 32) * 32)
#define NOTE_CTRL_REGION_H     80
#define NOTE_CTRL_FB_W         NOTE_CTRL_REGION_W
#define NOTE_CTRL_FB_H         NOTE_CTRL_REGION_H

#define NOTE_DRAW_REGION_X     ((WIN_LAYERS_W - NOTE_DRAW_FB_W) / 2)
#define NOTE_DRAW_REGION_Y     200
#define NOTE_DRAW_REGION_W     ((WIN_LAYERS_W / 32) * 32)
#define NOTE_DRAW_REGION_H     2000
#define NOTE_DRAW_FB_W         NOTE_DRAW_REGION_W
#define NOTE_DRAW_FB_H         NOTE_DRAW_REGION_H

/* Event define */
#define EVENT_NOTE_REFRESH     (0x01UL << 0)
#define EVENT_NOTE_EXIT        (0x01UL << 1)
#define EVENT_SRCSAVER_ENTER   (0x01UL << 2)
#define EVENT_SRCSAVER_EXIT    (0x01UL << 3)

/* Command define */
#define UPDATE_DRAW            (0x01UL << 0)
#define UPDATE_REVIEW_IMG      (0x01UL << 1)
#define UPDATE_DRAW_IMG        (0x01UL << 2)
#define UPDATE_DRAW_CLEAR      (0x01UL << 3)
#define UPDATE_CTRL            (0x01UL << 4)
#define UPDATE_CTRL_BTNPREV    (0x01UL << 5)
#define UPDATE_CTRL_BTNCLR     (0x01UL << 6)
#define UPDATE_CTRL_BTNSAVE    (0x01UL << 7)
#define UPDATE_CTRL_BTNNEXT    (0x01UL << 8)

#define NOTE_SRCSAVER_TIME     (RT_TICK_PER_SECOND * 15)

/*
 **************************************************************************************************
 *
 * Declaration
 *
 **************************************************************************************************
 */
extern image_info_t note_dot_info;
extern image_info_t note_btnprev_info;
extern image_info_t note_btnclear_info;
extern image_info_t note_btnsave_info;
extern image_info_t note_btnnext_info;

static image_info_t screen_item;
static image_info_t draw_item;

#ifdef NOTE_TEST
extern image_info_t note_prevpage_info;
static image_info_t save_item;
#endif

/*
 **************************************************************************************************
 *
 * Global static struct & data define
 *
 **************************************************************************************************
 */
struct olpc_note_data
{
    rt_display_data_t disp;
    rt_timer_t    srctimer;

    rt_uint8_t *fb;
    rt_uint32_t fblen;
#ifdef NOTE_TEST
    rt_uint8_t *savefb;
    rt_uint32_t savefblen;
#endif

    rt_uint8_t *ctrlfb;
    rt_uint32_t ctrlfblen;

    rt_event_t  disp_event;
    rt_uint32_t cmd;

    rt_uint16_t touch_xlast;
    rt_uint16_t touch_ylast;

    image_info_t *pageinfo;
};

struct olpc_note_touch_point
{
    rt_uint16_t x;
    rt_uint16_t y;
};
#define NOTE_POINT_BUFFER_SIZE      32
struct olpc_note_touch_point note_point_buffer[NOTE_POINT_BUFFER_SIZE];

/*
 **************************************************************************************************
 *
 * 1bpp note test demo
 *
 **************************************************************************************************
 */

/**
 * olpc note lut set.
 */
static rt_err_t olpc_note_lutset(void *parameter)
{
    rt_err_t ret = RT_EOK;
    struct rt_display_lut lut0;

    lut0.winId = NOTE_TEXT_GRAY1_WIN;
    lut0.format = RTGRAPHIC_PIXEL_FORMAT_GRAY1;
    lut0.lut  = bpp1_lut;
    lut0.size = sizeof(bpp1_lut) / sizeof(bpp1_lut[0]);

    ret = rt_display_lutset(&lut0, RT_NULL, RT_NULL);
    RT_ASSERT(ret == RT_EOK);

    return ret;
}

/**
 * olpc note demo init.
 */
static rt_err_t olpc_note_init(struct olpc_note_data *olpc_data)
{
    rt_err_t    ret;
    rt_device_t device = olpc_data->disp->device;
    struct rt_device_graphic_info info;

    ret = rt_device_control(device, RTGRAPHIC_CTRL_GET_INFO, &info);
    RT_ASSERT(ret == RT_EOK);

    olpc_data->fblen = NOTE_DRAW_FB_W * NOTE_DRAW_FB_H / 8;
    olpc_data->fb    = (rt_uint8_t *)rt_malloc_large(olpc_data->fblen);
    RT_ASSERT(olpc_data->fb != RT_NULL);
    rt_memset((void *)olpc_data->fb, 0x00, olpc_data->fblen);
#ifdef NOTE_TEST
    olpc_data->savefblen = olpc_data->fblen;
    olpc_data->savefb    = (rt_uint8_t *)rt_malloc_dtcm(olpc_data->savefblen);
    RT_ASSERT(olpc_data->savefb != RT_NULL);
    rt_memset((void *)olpc_data->savefb, 0x00, olpc_data->savefblen);

    save_item.type  = IMG_TYPE_RAW;
    save_item.pixel = RTGRAPHIC_PIXEL_FORMAT_GRAY1;
    save_item.x     = 0;
    save_item.y     = 0;
    save_item.w     = NOTE_DRAW_FB_W;
    save_item.h     = NOTE_DRAW_FB_H;
    save_item.data  = olpc_data->savefb;
#endif

    olpc_data->ctrlfblen = NOTE_CTRL_FB_W * NOTE_CTRL_FB_H / 8;
    olpc_data->ctrlfb    = (rt_uint8_t *)rt_malloc_large(olpc_data->ctrlfblen);
    RT_ASSERT(olpc_data->ctrlfb != RT_NULL);
    rt_memset((void *)olpc_data->ctrlfb, 0x00, olpc_data->ctrlfblen);

#if 0
    {
        struct rt_display_config wincfg;
        rt_memset(&wincfg, 0, sizeof(struct rt_display_config));

        wincfg.winId = NOTE_TEXT_GRAY1_WIN;
        wincfg.fb    = olpc_data->fb;
        wincfg.w     = 32;
        wincfg.h     = WIN_LAYERS_H;
        wincfg.fblen = wincfg.w * wincfg.h / 8;
        wincfg.x     = 0;
        wincfg.y     = 0;
        wincfg.ylast = wincfg.y;

        RT_ASSERT((wincfg.w % 4) == 0);
        RT_ASSERT((wincfg.h % 2) == 0);
        RT_ASSERT((wincfg.fblen) <= olpc_data->fblen);

        ret = rt_display_win_layers_set(&wincfg);
        RT_ASSERT(ret == RT_EOK);
    }
#endif

    return RT_EOK;
}

/**
 * olpc note demo deinit.
 */
static void olpc_note_deinit(struct olpc_note_data *olpc_data)
{
    rt_free_large((void *)olpc_data->ctrlfb);
    olpc_data->ctrlfb = RT_NULL;

    rt_free_large((void *)olpc_data->fb);
    olpc_data->fb = RT_NULL;

#ifdef NOTE_TEST
    rt_free_dtcm((void *)olpc_data->savefb);
    olpc_data->savefb = RT_NULL;
#endif
}

/**
 * olpc note control refresh
 */
static rt_err_t olpc_note_ctrl_region_refresh(struct olpc_note_data *olpc_data,
        struct rt_display_config *wincfg)
{
    rt_err_t ret;
    rt_int32_t   xoffset, yoffset;
    rt_device_t  device = olpc_data->disp->device;
    image_info_t *img_info = NULL;
    struct rt_device_graphic_info info;

    ret = rt_device_control(device, RTGRAPHIC_CTRL_GET_INFO, &info);
    RT_ASSERT(ret == RT_EOK);

    wincfg->winId = NOTE_TEXT_GRAY1_WIN;
    wincfg->fb    = olpc_data->ctrlfb;
    wincfg->w     = ((NOTE_CTRL_FB_W + 31) / 32) * 32;
    wincfg->h     = NOTE_CTRL_FB_H;
    wincfg->fblen = wincfg->w * wincfg->h / 8;
    wincfg->x     = NOTE_CTRL_REGION_X + (NOTE_CTRL_REGION_W - NOTE_CTRL_FB_W) / 2;
    wincfg->y     = NOTE_CTRL_REGION_Y + (NOTE_CTRL_REGION_H - NOTE_CTRL_FB_H) / 2;
    wincfg->ylast = wincfg->y;

    RT_ASSERT((wincfg->w % 4) == 0);
    RT_ASSERT((wincfg->h % 2) == 0);
    RT_ASSERT(wincfg->fblen <= olpc_data->fblen);

    //rt_memset(wincfg->fb, 0, wincfg->fblen);

    /* prev button */
    if ((olpc_data->cmd & UPDATE_CTRL_BTNPREV) == UPDATE_CTRL_BTNPREV)
    {
        olpc_data->cmd &= ~UPDATE_CTRL_BTNPREV;

        img_info = &note_btnprev_info;
        xoffset = 0;
        yoffset = 0;
        rt_display_img_fill(img_info, wincfg->fb, wincfg->w, img_info->x + xoffset, img_info->y + yoffset);
    }
    /* next button */
    /* else */if ((olpc_data->cmd & UPDATE_CTRL_BTNNEXT) == UPDATE_CTRL_BTNNEXT)
    {
        olpc_data->cmd &= ~UPDATE_CTRL_BTNNEXT;

        img_info = &note_btnnext_info;
        xoffset = 0;
        yoffset = 0;
        rt_display_img_fill(img_info, wincfg->fb, wincfg->w, img_info->x + xoffset, img_info->y + yoffset);
    }
    /* clear button */
    /* else */if ((olpc_data->cmd & UPDATE_CTRL_BTNCLR) == UPDATE_CTRL_BTNCLR)
    {
        olpc_data->cmd &= ~UPDATE_CTRL_BTNCLR;

        img_info = &note_btnclear_info;
        xoffset = 0;
        yoffset = 0;
        rt_display_img_fill(img_info, wincfg->fb, wincfg->w, img_info->x + xoffset, img_info->y + yoffset);
    }
    /* save button */
    /* else */if ((olpc_data->cmd & UPDATE_CTRL_BTNSAVE) == UPDATE_CTRL_BTNSAVE)
    {
        olpc_data->cmd &= ~UPDATE_CTRL_BTNSAVE;

        img_info = &note_btnsave_info;
        xoffset = 0;
        yoffset = 0;
        rt_display_img_fill(img_info, wincfg->fb, wincfg->w, img_info->x + xoffset, img_info->y + yoffset);
    }

    return RT_EOK;
}

/**
 * olpc note refresh draw
 */
static rt_err_t olpc_note_draw_region_refresh(struct olpc_note_data *olpc_data,
        struct rt_display_config *wincfg)
{
    rt_err_t ret;
    rt_int32_t   xoffset, yoffset;
    rt_device_t  device = olpc_data->disp->device;
    image_info_t *img_info = NULL;
    struct rt_device_graphic_info info;

    ret = rt_device_control(device, RTGRAPHIC_CTRL_GET_INFO, &info);
    RT_ASSERT(ret == RT_EOK);

    wincfg->winId = NOTE_TEXT_GRAY1_WIN;
    wincfg->x     = NOTE_DRAW_REGION_X + (NOTE_DRAW_REGION_W - NOTE_DRAW_FB_W) / 2;
    wincfg->y     = NOTE_DRAW_REGION_Y + (NOTE_DRAW_REGION_H - NOTE_DRAW_FB_H) / 2;
    wincfg->w     = ((NOTE_DRAW_FB_W + 31) / 32) * 32;
    wincfg->h     = NOTE_DRAW_FB_H;
    wincfg->fb    = olpc_data->fb;
    wincfg->fblen = wincfg->w * wincfg->h / 8;
    wincfg->ylast = wincfg->y;
    RT_ASSERT((wincfg->w % 4) == 0);
    RT_ASSERT((wincfg->h % 2) == 0);
    RT_ASSERT(wincfg->fblen <= olpc_data->fblen);

    /* img clear */
    if ((olpc_data->cmd & UPDATE_DRAW_CLEAR) == UPDATE_DRAW_CLEAR)
    {
        olpc_data->cmd &= ~UPDATE_DRAW_CLEAR;

        rt_memset(wincfg->fb, 0, wincfg->fblen);
    }
    /* img update */
    else if ((olpc_data->cmd & UPDATE_DRAW_IMG) == UPDATE_DRAW_IMG)
    {
        olpc_data->cmd &= ~UPDATE_DRAW_IMG;

        rt_int32_t i, j;
        rt_int16_t touch_x, touch_y;
        struct olpc_note_touch_point pointbuffer[NOTE_POINT_BUFFER_SIZE];

        rt_memcpy(pointbuffer, note_point_buffer, NOTE_POINT_BUFFER_SIZE * sizeof(struct olpc_note_touch_point));
        rt_memset(note_point_buffer, 0, NOTE_POINT_BUFFER_SIZE * sizeof(struct olpc_note_touch_point));

        img_info = &note_dot_info;
        for (j = 0 ; j < NOTE_POINT_BUFFER_SIZE; j++)
        {
            if ((pointbuffer[j].x == 0) && (pointbuffer[j].y == 0))
            {
                break;
            }

            touch_x = pointbuffer[j].x;
            touch_y = pointbuffer[j].y;

            rt_int32_t len   = MAX(1, MAX(ABS(touch_x - olpc_data->touch_xlast), ABS(touch_y - olpc_data->touch_ylast)));
            rt_int32_t xrate = ((touch_x - olpc_data->touch_xlast) * 100) / len;
            rt_int32_t yrate = ((touch_y - olpc_data->touch_ylast) * 100) / len;

            for (i = 0; i < len; i += 1)
            {
                xoffset = i * xrate / 100 + olpc_data->touch_xlast - wincfg->x - img_info->w / 2;
                yoffset = i * yrate / 100 + olpc_data->touch_ylast - wincfg->y - img_info->h / 2;
                rt_display_img_fill(img_info, wincfg->fb, wincfg->w, img_info->x + xoffset, img_info->y + yoffset);
            }

            olpc_data->touch_xlast = touch_x;
            olpc_data->touch_ylast = touch_y;
        }
    }
    /* img review */
    else if ((olpc_data->cmd & UPDATE_REVIEW_IMG) == UPDATE_REVIEW_IMG)
    {
        olpc_data->cmd &= ~UPDATE_REVIEW_IMG;

        img_info = olpc_data->pageinfo;
        xoffset = 0;
        yoffset = 0;
        rt_display_img_fill(img_info, wincfg->fb, wincfg->w, img_info->x + xoffset, img_info->y + yoffset);
    }

    return RT_EOK;
}

/**
 * olpc note refresh process
 */
static rt_err_t olpc_note_task_fun(struct olpc_note_data *olpc_data)
{
    rt_err_t ret;
    struct rt_display_config  wincfg;
    struct rt_display_config *winhead = RT_NULL;

    rt_memset(&wincfg, 0, sizeof(struct rt_display_config));

    if ((olpc_data->cmd & UPDATE_CTRL) == UPDATE_CTRL)
    {
        olpc_data->cmd &= ~UPDATE_CTRL;

        olpc_note_ctrl_region_refresh(olpc_data, &wincfg);
    }
    else if ((olpc_data->cmd & UPDATE_DRAW) == UPDATE_DRAW)
    {
        olpc_data->cmd &= ~UPDATE_DRAW;

        olpc_note_draw_region_refresh(olpc_data, &wincfg);
    }

    //refresh screen
    rt_display_win_layers_list(&winhead, &wincfg);
    ret = rt_display_win_layers_set(winhead);
    RT_ASSERT(ret == RT_EOK);

    if (olpc_data->cmd != 0)
    {
        rt_event_send(olpc_data->disp_event, EVENT_NOTE_REFRESH);
    }

    return RT_EOK;
}

/*
 **************************************************************************************************
 *
 * olpc note touch functions
 *
 **************************************************************************************************
 */
#if defined(RT_USING_TOUCH)
/**
 * screen touch.
 */
static rt_err_t olpc_note_screen_touch_callback(rt_int32_t touch_id, enum olpc_touch_event event, struct point_info *point, void *parameter)
{
    rt_err_t ret = RT_ERROR;
    struct olpc_note_data *olpc_data = (struct olpc_note_data *)parameter;

    switch (event)
    {
    default:
        break;
    }

#if defined(OLPC_APP_SRCSAVER_ENABLE)
    if ((olpc_data) && (olpc_data->srctimer))
    {
        rt_timer_start(olpc_data->srctimer);    //reset screen protection timer
    }
#endif

    return ret;
}

static rt_err_t olpc_note_screen_touch_register(void *parameter)
{
    image_info_t *img_info = &screen_item;
    struct olpc_note_data *olpc_data = (struct olpc_note_data *)parameter;
    struct rt_device_graphic_info info;

    rt_memcpy(&info, &olpc_data->disp->info, sizeof(struct rt_device_graphic_info));
    rt_memset(note_point_buffer, 0, NOTE_POINT_BUFFER_SIZE * sizeof(struct olpc_note_touch_point));

    /* screen on button touch register */
    {
        img_info->w = WIN_SCALED_W;
        img_info->h = WIN_SCALED_H;
        register_touch_item((struct olpc_touch_item *)(&img_info->touch_item), (void *)olpc_note_screen_touch_callback, (void *)olpc_data, 0);
        update_item_coord((struct olpc_touch_item *)(&img_info->touch_item), 0, 0, 0, 0);
    }

    return RT_EOK;
}

static rt_err_t olpc_note_screen_touch_unregister(void *parameter)
{
    image_info_t *img_info = &screen_item;
    unregister_touch_item((struct olpc_touch_item *)(&img_info->touch_item));
    return RT_EOK;
}

/**
 * draw touch.
 */
static rt_err_t olpc_note_draw_touch_callback(rt_int32_t touch_id, enum olpc_touch_event event, struct point_info *point, void *parameter)
{
    rt_err_t ret = RT_ERROR;
    rt_uint32_t i;
    image_info_t *img_info = &note_dot_info;
    struct olpc_note_data *olpc_data = (struct olpc_note_data *)parameter;
    struct rt_device_graphic_info info;
    rt_memcpy(&info, &olpc_data->disp->info, sizeof(struct rt_device_graphic_info));

    switch (event)
    {
    case TOUCH_EVENT_SHORT_DOWN:
        olpc_data->touch_xlast = point->x;
        olpc_data->touch_ylast = point->y;
    case TOUCH_EVENT_MOVE:
        if (((NOTE_DRAW_REGION_X + img_info->w <= point->x) && (point->x < NOTE_DRAW_REGION_X + NOTE_DRAW_REGION_W - img_info->w)) &&
                ((NOTE_DRAW_REGION_Y + img_info->h <= point->y) && (point->y < NOTE_DRAW_REGION_Y + NOTE_DRAW_REGION_H - img_info->h)))
        {
            for (i = 0 ; i < NOTE_POINT_BUFFER_SIZE; i++)
            {
                if ((note_point_buffer[i].x == 0) && (note_point_buffer[i].y == 0))
                {
                    break;
                }
            }
            if (i < NOTE_POINT_BUFFER_SIZE)
            {
                note_point_buffer[i].x = point->x;
                note_point_buffer[i].y = point->y;
                olpc_data->cmd = UPDATE_DRAW | UPDATE_DRAW_IMG;
                rt_event_send(olpc_data->disp_event, EVENT_NOTE_REFRESH);
            }
            else
            {
                rt_kprintf("olpc note touch point overflow!!!\n");
            }
        }
        else
        {
            olpc_touch_reset();
        }
        break;

    default:
        break;
    }

    return ret;
}

static rt_err_t olpc_note_draw_touch_register(void *parameter)
{
    image_info_t *img_info = &draw_item;
    struct olpc_note_data *olpc_data = (struct olpc_note_data *)parameter;
    struct rt_device_graphic_info info;

    rt_memcpy(&info, &olpc_data->disp->info, sizeof(struct rt_device_graphic_info));

    /* screen on button touch register */
    {
        img_info->x = NOTE_DRAW_REGION_X;
        img_info->y = NOTE_DRAW_REGION_Y;
        img_info->w = NOTE_DRAW_REGION_W;
        img_info->h = NOTE_DRAW_REGION_H;
        register_touch_item((struct olpc_touch_item *)(&img_info->touch_item), (void *)olpc_note_draw_touch_callback, (void *)olpc_data, 0);
        update_item_coord((struct olpc_touch_item *)(&img_info->touch_item), img_info->x, img_info->y, 0, 0);
    }

    return RT_EOK;
}

static rt_err_t olpc_note_draw_touch_unregister(void *parameter)
{
    image_info_t *img_info = &draw_item;
    unregister_touch_item((struct olpc_touch_item *)(&img_info->touch_item));
    return RT_EOK;
}

/**
 * prev btn touch.
 */
static rt_err_t olpc_note_btnprev_touch_callback(rt_int32_t touch_id, enum olpc_touch_event event, struct point_info *point, void *parameter)
{
    rt_err_t ret = RT_ERROR;
    struct olpc_note_data *olpc_data = (struct olpc_note_data *)parameter;

    switch (event)
    {
    case TOUCH_EVENT_SHORT_DOWN:
        rt_kprintf("prev key down!!!\n");
#ifdef NOTE_TEST
        olpc_data->pageinfo = &note_prevpage_info;
        olpc_data->cmd = UPDATE_DRAW | UPDATE_REVIEW_IMG;
        rt_event_send(olpc_data->disp_event, EVENT_NOTE_REFRESH);
#endif
        break;

    default:
        break;
    }
    return ret;
}

/**
 * next btn touch.
 */
static rt_err_t olpc_note_btnnext_touch_callback(rt_int32_t touch_id, enum olpc_touch_event event, struct point_info *point, void *parameter)
{
    rt_err_t ret = RT_ERROR;
    struct olpc_note_data *olpc_data = (struct olpc_note_data *)parameter;

    switch (event)
    {
    case TOUCH_EVENT_SHORT_DOWN:
        rt_kprintf("next key down!!!\n");
#ifdef NOTE_TEST
        olpc_data->pageinfo = &save_item;
        olpc_data->cmd = UPDATE_DRAW | UPDATE_REVIEW_IMG;
        rt_event_send(olpc_data->disp_event, EVENT_NOTE_REFRESH);
#endif
        break;

    default:
        break;
    }
    return ret;
}

/**
 * clear btn touch.
 */
static rt_err_t olpc_note_btnclear_touch_callback(rt_int32_t touch_id, enum olpc_touch_event event, struct point_info *point, void *parameter)
{
    rt_err_t ret = RT_ERROR;
    struct olpc_note_data *olpc_data = (struct olpc_note_data *)parameter;

    switch (event)
    {
    case TOUCH_EVENT_SHORT_DOWN:
        rt_kprintf("clear key down!!!\n");
        olpc_data->cmd = UPDATE_DRAW | UPDATE_DRAW_CLEAR;
        rt_event_send(olpc_data->disp_event, EVENT_NOTE_REFRESH);
        break;

    default:
        break;
    }
    return ret;
}

/**
 * save btn touch.
 */
static rt_err_t olpc_note_btnsave_touch_callback(rt_int32_t touch_id, enum olpc_touch_event event, struct point_info *point, void *parameter)
{
    rt_err_t ret = RT_ERROR;
    struct olpc_note_data *olpc_data = (struct olpc_note_data *)parameter;

    switch (event)
    {
    case TOUCH_EVENT_SHORT_DOWN:
        rt_kprintf("save key down!!!\n");
#ifdef NOTE_TEST
        rt_memcpy(olpc_data->savefb, olpc_data->fb, olpc_data->fblen);
#endif
        rt_thread_delay(10);
        rt_event_send(olpc_data->disp_event, EVENT_NOTE_EXIT);
        break;

    default:
        break;
    }
    return ret;
}

static rt_err_t olpc_note_btn_touch_register(void *parameter)
{
    rt_int16_t   xoffset = 0;
    rt_int16_t   yoffset = 0;
    image_info_t *img_info;
    struct olpc_note_data *olpc_data = (struct olpc_note_data *)parameter;
    struct rt_device_graphic_info info;

    rt_memcpy(&info, &olpc_data->disp->info, sizeof(struct rt_device_graphic_info));
    xoffset = NOTE_CTRL_REGION_X + (NOTE_CTRL_REGION_W - NOTE_CTRL_FB_W) / 2;
    yoffset = NOTE_CTRL_REGION_Y + (NOTE_CTRL_REGION_H - NOTE_CTRL_FB_H) / 2;

    /* prev button touch register */
    img_info = &note_btnprev_info;
    {
        register_touch_item((struct olpc_touch_item *)(&img_info->touch_item), (void *)olpc_note_btnprev_touch_callback, (void *)olpc_data, 0);
        update_item_coord((struct olpc_touch_item *)(&img_info->touch_item), img_info->x, img_info->y, xoffset, yoffset);
    }
    /* next button touch register */
    img_info = &note_btnnext_info;
    {
        register_touch_item((struct olpc_touch_item *)(&img_info->touch_item), (void *)olpc_note_btnnext_touch_callback, (void *)olpc_data, 0);
        update_item_coord((struct olpc_touch_item *)(&img_info->touch_item), img_info->x, img_info->y, xoffset, yoffset);
    }
    /* clear button touch register */
    img_info = &note_btnclear_info;
    {
        register_touch_item((struct olpc_touch_item *)(&img_info->touch_item), (void *)olpc_note_btnclear_touch_callback, (void *)olpc_data, 0);
        update_item_coord((struct olpc_touch_item *)(&img_info->touch_item), img_info->x, img_info->y, xoffset, yoffset);
    }
    /* save button touch register */
    img_info = &note_btnsave_info;
    {
        register_touch_item((struct olpc_touch_item *)(&img_info->touch_item), (void *)olpc_note_btnsave_touch_callback, (void *)olpc_data, 0);
        update_item_coord((struct olpc_touch_item *)(&img_info->touch_item), img_info->x, img_info->y, xoffset, yoffset);
    }

    return RT_EOK;
}

static rt_err_t olpc_note_btn_touch_unregister(void *parameter)
{
    image_info_t *img_info;

    img_info = &note_btnprev_info;
    unregister_touch_item((struct olpc_touch_item *)(&img_info->touch_item));

    img_info = &note_btnnext_info;
    unregister_touch_item((struct olpc_touch_item *)(&img_info->touch_item));

    img_info = &note_btnclear_info;
    unregister_touch_item((struct olpc_touch_item *)(&img_info->touch_item));

    img_info = &note_btnsave_info;
    unregister_touch_item((struct olpc_touch_item *)(&img_info->touch_item));

    return RT_EOK;
}

static rt_err_t olpc_note_touch_register(void *parameter)
{
    olpc_note_screen_touch_register(parameter);
    olpc_note_draw_touch_register(parameter);
    olpc_note_btn_touch_register(parameter);
    return RT_EOK;
}

static rt_err_t olpc_note_touch_unregister(void *parameter)
{
    olpc_note_btn_touch_unregister(parameter);
    olpc_note_draw_touch_unregister(parameter);
    olpc_note_screen_touch_unregister(parameter);
    return RT_EOK;
}
#endif

/*
 **************************************************************************************************
 *
 * olpc note screen protection functions
 *
 **************************************************************************************************
 */
#if defined(OLPC_APP_SRCSAVER_ENABLE)

/**
 * note screen protection timeout callback.
 */
static void olpc_note_srcprotect_callback(void *parameter)
{
    struct olpc_note_data *olpc_data = (struct olpc_note_data *)parameter;
    rt_event_send(olpc_data->disp_event, EVENT_SRCSAVER_ENTER);
}

/**
 * exit screen protection hook.
 */
static rt_err_t olpc_note_screen_protection_hook(void *parameter)
{
    struct olpc_note_data *olpc_data = (struct olpc_note_data *)parameter;

    rt_event_send(olpc_data->disp_event, EVENT_SRCSAVER_EXIT);

    return RT_EOK;
}

/**
 * start screen protection.
 */
static rt_err_t olpc_note_screen_protection_enter(void *parameter)
{
    struct olpc_note_data *olpc_data = (struct olpc_note_data *)parameter;

    rt_timer_stop(olpc_data->srctimer);

#if defined(RT_USING_TOUCH)
    olpc_note_touch_unregister(parameter);
    olpc_touch_list_clear();
#endif

    // register exit hook & start screen protection
    olpc_srcprotect_app_init(olpc_note_screen_protection_hook, parameter);

    return RT_EOK;
}

/**
 * exit screen protection.
 */
static rt_err_t olpc_note_screen_protection_exit(void *parameter)
{
    struct olpc_note_data *olpc_data = (struct olpc_note_data *)parameter;

    olpc_note_lutset(olpc_data);

#if defined(RT_USING_TOUCH)
    olpc_note_touch_register(parameter);
#endif

    olpc_data->cmd  = UPDATE_DRAW;
    olpc_data->cmd |= UPDATE_CTRL | UPDATE_CTRL_BTNPREV | UPDATE_CTRL_BTNCLR | UPDATE_CTRL_BTNSAVE | UPDATE_CTRL_BTNNEXT;
    rt_event_send(olpc_data->disp_event, EVENT_NOTE_REFRESH);

    rt_timer_start(olpc_data->srctimer);

    return RT_EOK;
}
#endif

/*
 **************************************************************************************************
 *
 * olpc note demo init & thread
 *
 **************************************************************************************************
 */

/**
 * olpc note dmeo thread.
 */
static void olpc_note_thread(void *p)
{
    rt_err_t ret;
    uint32_t event;
    struct olpc_note_data *olpc_data;

    olpc_data = (struct olpc_note_data *)rt_malloc(sizeof(struct olpc_note_data));
    RT_ASSERT(olpc_data != RT_NULL);
    rt_memset((void *)olpc_data, 0, sizeof(struct olpc_note_data));

    olpc_data->disp = rt_display_get_disp();
    RT_ASSERT(olpc_data->disp != RT_NULL);

    ret = olpc_note_lutset(olpc_data);
    RT_ASSERT(ret == RT_EOK);

#if defined(RT_USING_TOUCH)
    olpc_note_touch_register(olpc_data);
#endif

    olpc_data->disp_event = rt_event_create("display_event", RT_IPC_FLAG_FIFO);
    RT_ASSERT(olpc_data->disp_event != RT_NULL);

    ret = olpc_note_init(olpc_data);
    RT_ASSERT(ret == RT_EOK);

#if defined(OLPC_APP_SRCSAVER_ENABLE)
    olpc_data->srctimer = rt_timer_create("noteprotect",
                                          olpc_note_srcprotect_callback,
                                          (void *)olpc_data,
                                          NOTE_SRCSAVER_TIME,
                                          RT_TIMER_FLAG_PERIODIC);
    RT_ASSERT(olpc_data->srctimer != RT_NULL);

    rt_timer_start(olpc_data->srctimer);
#endif

    olpc_data->cmd  = UPDATE_DRAW | UPDATE_DRAW_CLEAR;
    olpc_data->cmd |= UPDATE_CTRL | UPDATE_CTRL_BTNPREV | UPDATE_CTRL_BTNCLR | UPDATE_CTRL_BTNSAVE | UPDATE_CTRL_BTNNEXT;
    rt_event_send(olpc_data->disp_event, EVENT_NOTE_REFRESH);

    while (1)
    {
        ret = rt_event_recv(olpc_data->disp_event,
                            EVENT_NOTE_REFRESH | EVENT_NOTE_EXIT | EVENT_SRCSAVER_ENTER | EVENT_SRCSAVER_EXIT,
                            RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR,
                            RT_WAITING_FOREVER, &event);
        if (ret != RT_EOK)
        {
            /* Reserved... */
        }

        if (event & EVENT_NOTE_REFRESH)
        {
            ret = olpc_note_task_fun(olpc_data);
            RT_ASSERT(ret == RT_EOK);
        }

#if defined(OLPC_APP_SRCSAVER_ENABLE)
        if (event & EVENT_SRCSAVER_ENTER)
        {
            ret = olpc_note_screen_protection_enter(olpc_data);
            RT_ASSERT(ret == RT_EOK);
        }

        if (event & EVENT_SRCSAVER_EXIT)
        {
            ret = olpc_note_screen_protection_exit(olpc_data);
            RT_ASSERT(ret == RT_EOK);
        }
#endif
        if (event & EVENT_NOTE_EXIT)
        {
            break;
        }
    }

    /* Thread deinit */
#if defined(OLPC_APP_SRCSAVER_ENABLE)
    rt_timer_stop(olpc_data->srctimer);
    ret = rt_timer_delete(olpc_data->srctimer);
    RT_ASSERT(ret == RT_EOK);
    olpc_data->srctimer = RT_NULL;
#endif

#if defined(RT_USING_TOUCH)
    olpc_note_touch_unregister(olpc_data);
    olpc_touch_list_clear();
#endif

    olpc_note_deinit(olpc_data);

    rt_event_delete(olpc_data->disp_event);
    olpc_data->disp_event = RT_NULL;

    rt_free(olpc_data);
    olpc_data = RT_NULL;

    rt_event_send(olpc_main_event, EVENT_APP_CLOCK);
}

/**
 * olpc note demo application init.
 */
int olpc_note_app_init(void)
{
    rt_thread_t rtt_note;

    rtt_note = rt_thread_create("olpcnote", olpc_note_thread, RT_NULL, 2048, 5, 10);
    RT_ASSERT(rtt_note != RT_NULL);
    rt_thread_startup(rtt_note);

    return RT_EOK;
}

//INIT_APP_EXPORT(olpc_note_app_init);
#endif
