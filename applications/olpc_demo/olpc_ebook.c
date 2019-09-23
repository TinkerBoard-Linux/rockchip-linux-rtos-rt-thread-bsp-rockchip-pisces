#include <rtthread.h>
#if defined(RT_USING_OLPC_DEMO) && defined(OLPC_APP_EBOOK_ENABLE)

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
    //0x000000, 0x005E5E5E
    0x000000, 0x00FFFFFF
};

/*
 **************************************************************************************************
 *
 * Macro define
 *
 **************************************************************************************************
 */
#define EBOOK_TEXT_GRAY1_WIN   0
#define EBOOK_BTG_RGB565_WIN   1

#define EBOOK_WIN_FB_MAX_W  ((WIN_LAYERS_W / 32) * 32)    /* align 32 */
#define EBOOK_WIN_FB_MAX_H  WIN_LAYERS_H

#define EBOOK_REGION_X      0
#define EBOOK_REGION_Y      0
#define EBOOK_REGION_W      WIN_LAYERS_W
#define EBOOK_REGION_H      WIN_LAYERS_H
#define EBOOK_FB_W          EBOOK_WIN_FB_MAX_W            /* ebook frame buffer w */
#define EBOOK_FB_H          EBOOK_WIN_FB_MAX_H            /* ebook frame buffer h */

#define BTN_REGION_X        0
#define BTN_REGION_Y        (WIN_LAYERS_H - 100 - 10)
#define BTN_REGION_W        WIN_LAYERS_W
#define BTN_REGION_H        100
#define BTN_FB_W            EBOOK_WIN_FB_MAX_W            /* ebook frame buffer w */
#define BTN_FB_H            100                           /* ebook frame buffer h */

/* Event define */
#define EVENT_EBOOK_REFRESH (0x01UL << 0)

/* Command define */
#define UPDATE_PAGE         (0x01UL << 0)

/*
 **************************************************************************************************
 *
 * Declaration
 *
 **************************************************************************************************
 */
extern image_info_t ebook_page1_info;
extern image_info_t ebook_page2_info;
extern image_info_t ebook_page3_info;
extern image_info_t ebook_page4_info;
extern image_info_t ebook_page5_info;

/*
 **************************************************************************************************
 *
 * Global static struct & data define
 *
 **************************************************************************************************
 */
struct olpc_ebook_data
{
    rt_display_data_t disp;

    rt_uint8_t *fb;
    rt_uint32_t fblen;

    rt_event_t  disp_event;
    rt_uint32_t cmd;

    rt_uint16_t page_num;
};

#define EBOOK_PAGE_MAX_NUM  5
static image_info_t *ebook_pages_num[EBOOK_PAGE_MAX_NUM] =
{
    &ebook_page1_info,
    &ebook_page2_info,
    &ebook_page3_info,
    &ebook_page4_info,
    &ebook_page5_info,
};

#if defined(OLPC_APP_EBOOK_USE_BTN)
static image_info_t *btn_right_num[2] =
{
    &ebook_btn_rightup_info,
    &ebook_btn_rightdown_info,
};

static image_info_t *btn_left_num[2] =
{
    &ebook_btn_leftup_info,
    &ebook_btn_leftdown_info,
};
#endif

/*
 **************************************************************************************************
 *
 * 1bpp ebook test demo
 *
 **************************************************************************************************
 */

/**
 * olpc ebook demo init.
 */
static rt_err_t olpc_ebook_init(struct olpc_ebook_data *olpc_data)
{
    rt_err_t    ret;
    rt_device_t device = olpc_data->disp->device;
    struct rt_display_config wincfg;
    struct rt_device_graphic_info info;

    olpc_data->page_num = 0;
    olpc_data->cmd = UPDATE_PAGE;

    ret = rt_device_control(device, RTGRAPHIC_CTRL_GET_INFO, &info);
    RT_ASSERT(ret == RT_EOK);

    olpc_data->fblen = EBOOK_WIN_FB_MAX_W * EBOOK_WIN_FB_MAX_H / 8;
    olpc_data->fb    = (rt_uint8_t *)rt_malloc_large(olpc_data->fblen);
    RT_ASSERT(olpc_data->fb != RT_NULL);

    rt_memset(&wincfg, 0, sizeof(struct rt_display_config));

    wincfg.winId = EBOOK_TEXT_GRAY1_WIN;
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

    rt_memset((void *)wincfg.fb, 0x00, wincfg.fblen);

    //refresh screen
    ret = rt_display_win_layers_set(&wincfg);
    RT_ASSERT(ret == RT_EOK);

    return RT_EOK;
}

/**
 * olpc ebook demo deinit.
 */
static void olpc_ebook_deinit(struct olpc_ebook_data *olpc_data)
{
    rt_free_large((void *)olpc_data->fb);
}

/**
 * olpc ebook refresh process
 */
static rt_err_t olpc_ebook_task_fun(struct olpc_ebook_data *olpc_data)
{
    rt_err_t ret;
    rt_int32_t   xoffset, yoffset;
    rt_device_t  device = olpc_data->disp->device;
    image_info_t *img_info = NULL;
    struct rt_device_graphic_info info;
    struct rt_display_config pagewin, *wlist_head = RT_NULL;

    //rt_tick_t ticks = rt_tick_get();

    ret = rt_device_control(device, RTGRAPHIC_CTRL_GET_INFO, &info);
    RT_ASSERT(ret == RT_EOK);

    rt_display_sync_hook(device);

    // only send page buffer
    {
        rt_display_win_layers_list(&wlist_head, &pagewin);

        rt_memset(&pagewin, 0, sizeof(struct rt_display_config));
        pagewin.winId = EBOOK_TEXT_GRAY1_WIN;
        pagewin.fb    = olpc_data->fb;
        pagewin.w     = ((EBOOK_FB_W + 31) / 32) * 32;
        pagewin.h     = EBOOK_FB_H;
        pagewin.fblen = pagewin.w * pagewin.h / 8;
        pagewin.x     = EBOOK_REGION_X + (EBOOK_REGION_W - EBOOK_FB_W) / 2;
        pagewin.y     = EBOOK_REGION_Y + (EBOOK_REGION_H - EBOOK_FB_H) / 2;
        pagewin.ylast = pagewin.y;

        RT_ASSERT((pagewin.w % 4) == 0);
        RT_ASSERT((pagewin.h % 2) == 0);
        RT_ASSERT(pagewin.fblen <= olpc_data->fblen);
    }

    ret = rt_device_control(device, RTGRAPHIC_CTRL_POWERON, NULL);
    RT_ASSERT(ret == RT_EOK);

    /* Page update */
    if ((olpc_data->cmd & UPDATE_PAGE) == UPDATE_PAGE)
    {
        olpc_data->cmd &= ~UPDATE_PAGE;

        rt_memset((void *)pagewin.fb, 0x00, pagewin.fblen);

        xoffset = 0;
        yoffset = 0;

        //draw pages
        img_info = ebook_pages_num[olpc_data->page_num];
        //rt_kprintf("page_num = %d\n", olpc_data->page_num);
        RT_ASSERT(img_info->w <= pagewin.w);
        RT_ASSERT(img_info->h <= pagewin.h);
        rt_display_img_fill(img_info, pagewin.fb, pagewin.w, xoffset + img_info->x, yoffset + img_info->y);
    }

    ret = rt_display_win_layers_set(wlist_head);
    RT_ASSERT(ret == RT_EOK);

    ret = rt_display_sync_hook(device);
    RT_ASSERT(ret == RT_EOK);

    ret = rt_device_control(device, RTGRAPHIC_CTRL_POWEROFF, NULL);
    RT_ASSERT(ret == RT_EOK);

    //update date next item
    if (olpc_data->cmd != 0)
    {
        rt_event_send(olpc_data->disp_event, EVENT_EBOOK_REFRESH);
    }

    return RT_EOK;
}

/*
 **************************************************************************************************
 *
 * olpc ebook touch functions
 *
 **************************************************************************************************
 */
#if defined(RT_USING_TOUCH)
/**
 * screen touch.
 */
#define BL_MOVE_STEP_MIN    (100)
#define PAGE_MOVE_STEP_MIN  (440)
static image_info_t screen_item;
static struct point_info down_point;
static struct point_info up_point;
static uint8_t page_bl_flag = 0;
static rt_err_t olpc_ebook_screen_touch_callback(rt_int32_t touch_id, enum olpc_touch_event event, struct point_info *point, void *parameter)
{
    rt_err_t ret = RT_ERROR;
    struct olpc_ebook_data *olpc_data = (struct olpc_ebook_data *)parameter;

    switch (event)
    {
    case TOUCH_EVENT_SHORT_DOWN:
        page_bl_flag = 0;
        down_point.x = point->x;
        down_point.y = point->y;
        ret = RT_EOK;
        break;

    case TOUCH_EVENT_MOVE:
        //check page move or bl move
        if (page_bl_flag == 0)
        {
            rt_int16_t xdiff = point->x - down_point.x;
            rt_int16_t ydiff = point->y - down_point.y;

            if (ABS(xdiff) >= PAGE_MOVE_STEP_MIN)
            {
                //rt_kprintf("page move!!!!\n");
                page_bl_flag = 1;
            }
            else if ((ABS(ydiff) >= BL_MOVE_STEP_MIN) && (ABS(xdiff) < BL_MOVE_STEP_MIN))
            {
                //rt_kprintf("bl move!!!!\n");
                page_bl_flag = 2;
            }
        }

        // page move
        if (page_bl_flag == 1)
        {
            up_point.x = point->x;
            up_point.y = point->y;
        }
        // backlight move
        else if (page_bl_flag == 2)
        {
            rt_int32_t xdiff = point->x - down_point.x;
            rt_int32_t ydiff = -(point->y - down_point.y);

            // if x out of range reset touch
            if (ABS(xdiff) > BL_MOVE_STEP_MIN)
            {
                rt_kprintf("touch reset\n");
                olpc_touch_reset();
            }

            if (ABS(ydiff) > BL_MOVE_STEP_MIN)
            {
                down_point.y = point->y;

                struct rt_device_graphic_info info;
                rt_memcpy(&info, &olpc_data->disp->info, sizeof(struct rt_device_graphic_info));

                olpc_data->disp->blval += ydiff * rt_display_get_bl_max(olpc_data->disp->device) / WIN_LAYERS_H * 2;
                if ((rt_int16_t)olpc_data->disp->blval < 0)
                {
                    olpc_data->disp->blval = 0;
                }
                else if ((rt_int16_t)olpc_data->disp->blval > rt_display_get_bl_max(olpc_data->disp->device))
                {
                    olpc_data->disp->blval = rt_display_get_bl_max(olpc_data->disp->device);
                }
                //rt_kprintf("backlight val = %d\n", olpc_data->disp->blval);

                ret = rt_device_control(olpc_data->disp->device, RTGRAPHIC_CTRL_POWERON, NULL);
                RT_ASSERT(ret == RT_EOK);

                ret = rt_device_control(olpc_data->disp->device, RK_DISPLAY_CTRL_UPDATE_BL, &olpc_data->disp->blval);
                RT_ASSERT(ret == RT_EOK);

                ret = rt_device_control(olpc_data->disp->device, RTGRAPHIC_CTRL_POWEROFF, NULL);
                RT_ASSERT(ret == RT_EOK);
            }

            ret = RT_EOK;
        }
        break;

    case TOUCH_EVENT_UP:
    {
        if (page_bl_flag == 1)
        {
            rt_int16_t diff = up_point.x - down_point.x;
            if (diff < -PAGE_MOVE_STEP_MIN)
            {
                if (olpc_data->page_num < EBOOK_PAGE_MAX_NUM - 1)
                {
                    olpc_data->page_num ++;
                }
                olpc_data->cmd |= UPDATE_PAGE;
                rt_event_send(olpc_data->disp_event, EVENT_EBOOK_REFRESH);
                ret = RT_EOK;
            }
            else if (diff > PAGE_MOVE_STEP_MIN)
            {
                if (olpc_data->page_num > 0)
                {
                    olpc_data->page_num --;
                }
                olpc_data->cmd |= UPDATE_PAGE;
                rt_event_send(olpc_data->disp_event, EVENT_EBOOK_REFRESH);
                ret = RT_EOK;
            }
        }
    }
    break;

    default:
        break;
    }

    return ret;
}

static rt_err_t olpc_ebook_screen_touch_register(void *parameter)
{
    image_info_t *img_info = &screen_item;
    struct olpc_ebook_data *olpc_data = (struct olpc_ebook_data *)parameter;
    struct rt_device_graphic_info info;

    rt_memcpy(&info, &olpc_data->disp->info, sizeof(struct rt_device_graphic_info));

    /* screen on button touch register */
    {
        screen_item.w = WIN_LAYERS_W;
        screen_item.h = WIN_LAYERS_H;
        register_touch_item((struct olpc_touch_item *)(&img_info->touch_item), (void *)olpc_ebook_screen_touch_callback, (void *)olpc_data, 0);
        update_item_coord((struct olpc_touch_item *)(&img_info->touch_item), 0, 0, 0, 0);
    }

    return RT_EOK;
}

static rt_err_t olpc_ebook_screen_touch_unregister(void *parameter)
{
    image_info_t *img_info = &screen_item;

    unregister_touch_item((struct olpc_touch_item *)(&img_info->touch_item));

    return RT_EOK;
}

#endif

/*
 **************************************************************************************************
 *
 * olpc ebook demo init & thread
 *
 **************************************************************************************************
 */

/**
 * olpc ebook dmeo thread.
 */
static void olpc_ebook_thread(void *p)
{
    rt_err_t ret;
    uint32_t event;
    struct olpc_ebook_data *olpc_data;
    struct rt_display_lut btnlut, pagelut;

    olpc_data = (struct olpc_ebook_data *)rt_malloc(sizeof(struct olpc_ebook_data));
    RT_ASSERT(olpc_data != RT_NULL);
    rt_memset((void *)olpc_data, 0, sizeof(struct olpc_ebook_data));

    /* init bpp_lut[256] */
    //rt_display_update_lut(FORMAT_RGB_332);

    pagelut.winId = EBOOK_TEXT_GRAY1_WIN;
    pagelut.format = RTGRAPHIC_PIXEL_FORMAT_GRAY1;
    pagelut.lut  = bpp1_lut;
    pagelut.size = sizeof(bpp1_lut) / sizeof(bpp1_lut[0]);

    btnlut.winId = EBOOK_BTG_RGB565_WIN;
    btnlut.format = RTGRAPHIC_PIXEL_FORMAT_RGB565;
    btnlut.lut  = RT_NULL;
    btnlut.size = 0;

    olpc_data->disp = rt_display_init(&pagelut, &btnlut, RT_NULL);
    RT_ASSERT(olpc_data->disp != RT_NULL);

#if defined(RT_USING_TOUCH)
    olpc_ebook_screen_touch_register(olpc_data);
#endif

    olpc_data->disp_event = rt_event_create("display_event", RT_IPC_FLAG_FIFO);
    RT_ASSERT(olpc_data->disp_event != RT_NULL);

    ret = olpc_ebook_init(olpc_data);
    RT_ASSERT(ret == RT_EOK);

    rt_event_send(olpc_data->disp_event, EVENT_EBOOK_REFRESH);

    while (1)
    {
        ret = rt_event_recv(olpc_data->disp_event, EVENT_EBOOK_REFRESH,
                            RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR,
                            RT_WAITING_FOREVER, &event);
        if (ret != RT_EOK)
        {
            /* Reserved... */
        }

        if (event & EVENT_EBOOK_REFRESH)
        {
            ret = olpc_ebook_task_fun(olpc_data);
            RT_ASSERT(ret == RT_EOK);
        }
    }

    /* Thread deinit */
#if defined(RT_USING_TOUCH)
    olpc_ebook_screen_touch_unregister(olpc_data);
#endif

    olpc_ebook_deinit(olpc_data);

    rt_event_delete(olpc_data->disp_event);

    rt_display_deinit(olpc_data->disp);

    rt_free(olpc_data);
}

/**
 * olpc ebook demo application init.
 */
int olpc_ebook_app_init(void)
{
    rt_thread_t rtt_ebook;

    rtt_ebook = rt_thread_create("olpcclock", olpc_ebook_thread, RT_NULL, 2048, 5, 10);
    RT_ASSERT(rtt_ebook != RT_NULL);
    rt_thread_startup(rtt_ebook);

    return RT_EOK;
}

INIT_APP_EXPORT(olpc_ebook_app_init);
#endif
