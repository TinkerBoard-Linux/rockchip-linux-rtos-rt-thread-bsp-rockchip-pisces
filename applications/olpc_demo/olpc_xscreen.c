/**
  * Copyright (c) 2019 Fuzhou Rockchip Electronics Co., Ltd
  *
  * SPDX-License-Identifier: Apache-2.0
  */

#include <rtthread.h>
#if defined(OLPC_APP_XSCREEN_ENABLE)

#include "drv_heap.h"
#include "image_info.h"
#include "olpc_display.h"
#include "gcc_segment.h"

#if defined(RT_USING_TOUCH)
#include "drv_touch.h"
#include "olpc_touch.h"
#endif

/*
 **************************************************************************************************
 *
 * Macro define
 *
 **************************************************************************************************
 */
#define XSCREEN_RGB332_WIN        1

#define XSCREEN_REGION_X          0
#define XSCREEN_REGION_Y          0
#define XSCREEN_REGION_W          WIN_LAYERS_W
#define XSCREEN_REGION_H          WIN_LAYERS_H
#define XSCREEN_FB_W              720            /* xscreen frame buffer w */
#define XSCREEN_FB_H              720            /* xscreen frame buffer h */

/* Event define */
#define EVENT_XSCREEN_REFRESH     (0x01UL << 0)
#define EVENT_XSCREEN_EXIT        (0x01UL << 1)

/* Command define */
#define UPDATE_XSCREEN            (0x01UL << 0)

#define XSCREEN_SRCSAVER_TIME     (RT_TICK_PER_SECOND / 20)

/*
 **************************************************************************************************
 *
 * Declaration
 *
 **************************************************************************************************
 */
extern image_info_t x_screen00_info;
extern image_info_t x_screen01_info;
extern image_info_t x_screen02_info;
extern image_info_t x_screen03_info;
extern image_info_t x_screen04_info;
extern image_info_t x_screen05_info;
extern image_info_t x_screen06_info;
extern image_info_t x_screen07_info;
extern image_info_t x_screen08_info;
extern image_info_t x_screen09_info;
extern image_info_t x_screen10_info;
extern image_info_t x_screen11_info;
extern image_info_t x_screen12_info;
extern image_info_t x_screen13_info;
extern image_info_t x_screen14_info;
extern image_info_t x_screen15_info;
extern image_info_t x_screen16_info;
extern image_info_t x_screen17_info;
extern image_info_t x_screen18_info;
extern image_info_t x_screen19_info;

/*
 **************************************************************************************************
 *
 * Global static struct & data define
 *
 **************************************************************************************************
 */
struct olpc_xscreen_data
{
    rt_display_data_t disp;
    rt_timer_t        timer;

    rt_uint8_t *fb;
    rt_uint32_t fblen;

    rt_event_t  disp_event;
    rt_uint32_t cmd;

    rt_uint16_t pic_id;
};

#define XSCREEN_PIC_MAX_NUM  20
static image_info_t *xscreen_pages_num[XSCREEN_PIC_MAX_NUM] =
{
    &x_screen00_info,
    &x_screen01_info,
    &x_screen02_info,
    &x_screen03_info,
    &x_screen04_info,
    &x_screen05_info,
    &x_screen06_info,
    &x_screen07_info,
    &x_screen08_info,
    &x_screen09_info,
    &x_screen10_info,
    &x_screen11_info,
    &x_screen12_info,
    &x_screen13_info,
    &x_screen14_info,
    &x_screen15_info,
    &x_screen16_info,
    &x_screen17_info,
    &x_screen18_info,
    &x_screen19_info,
};

/*
 **************************************************************************************************
 *
 * xscreen test demo
 *
 **************************************************************************************************
 */

/**
 * olpc xscreen lut set.
 */
static rt_err_t olpc_xscreen_lutset(void *parameter)
{
    rt_err_t ret = RT_EOK;
    struct rt_display_lut lut0;

    lut0.winId = XSCREEN_RGB332_WIN;
    lut0.format = RTGRAPHIC_PIXEL_FORMAT_RGB332;
    lut0.lut  = bpp_lut;
    lut0.size = sizeof(bpp_lut) / sizeof(bpp_lut[0]);

    ret = rt_display_lutset(&lut0, RT_NULL, RT_NULL);
    RT_ASSERT(ret == RT_EOK);

    // clear screen
    {
        struct olpc_xscreen_data *olpc_data = (struct olpc_xscreen_data *)parameter;
        rt_device_t device = olpc_data->disp->device;
        struct rt_device_graphic_info info;

        ret = rt_device_control(device, RTGRAPHIC_CTRL_GET_INFO, &info);
        RT_ASSERT(ret == RT_EOK);

        rt_display_win_clear(XSCREEN_RGB332_WIN, RTGRAPHIC_PIXEL_FORMAT_RGB332, 0, WIN_LAYERS_H, 0);
    }

    return ret;
}

/**
 * olpc xscreen demo init.
 */
extern FIRMWARE_INFO_T const FirmwareInfoCopy;
static rt_err_t olpc_xscreen_init(struct olpc_xscreen_data *olpc_data)
{
    rt_err_t    ret;
    rt_device_t device = olpc_data->disp->device;
    rt_uint32_t i, id, addr, len;
    struct rt_device_graphic_info info;

    ret = rt_device_control(device, RTGRAPHIC_CTRL_GET_INFO, &info);
    RT_ASSERT(ret == RT_EOK);

    olpc_data->fblen = XSCREEN_FB_W * XSCREEN_FB_H;
    olpc_data->fb    = (rt_uint8_t *)rt_malloc_large(olpc_data->fblen);
    RT_ASSERT(olpc_data->fb != RT_NULL);

    for (i = 0; i < XSCREEN_PIC_MAX_NUM; i++)
    {
        id   = i + SEGMENT_ID_OLPC_XSCREEN_RES00;
        len  = (rt_uint32_t)FirmwareInfoCopy.SegmentInfo.Segment[id].CodeImageLength;
        addr = (rt_uint32_t)FirmwareInfoCopy.SegmentInfo.Segment[id].CodeImageBase;
        olpc_firmware_request(id);
        xscreen_pages_num[i]->data  = (const rt_uint8_t *)rt_malloc_dtcm(len);
        RT_ASSERT(xscreen_pages_num[i]->data != RT_NULL);
        rt_memcpy((rt_uint8_t *)xscreen_pages_num[i]->data, (rt_uint8_t *)addr, len);
    }

    return RT_EOK;
}

/**
 * olpc xscreen demo deinit.
 */
static void olpc_xscreen_deinit(struct olpc_xscreen_data *olpc_data)
{
    rt_uint32_t i;

    for (i = 0; i < XSCREEN_PIC_MAX_NUM; i++)
    {
        rt_free_dtcm((rt_uint8_t *)xscreen_pages_num[i]->data);
        xscreen_pages_num[i]->data = RT_NULL;
    }

    rt_free_large((void *)olpc_data->fb);
    olpc_data->fb = RT_NULL;
}

/**
 * olpc xscreen refresh page
 */
static rt_err_t olpc_xscreen_region_refresh(struct olpc_xscreen_data *olpc_data,
        struct rt_display_config *wincfg)
{
    rt_err_t ret;
    rt_int32_t   xoffset, yoffset;
    rt_device_t  device = olpc_data->disp->device;
    image_info_t *img_info = NULL;
    struct rt_device_graphic_info info;

    ret = rt_device_control(device, RTGRAPHIC_CTRL_GET_INFO, &info);
    RT_ASSERT(ret == RT_EOK);

    wincfg->winId = XSCREEN_RGB332_WIN;
    wincfg->fb    = olpc_data->fb;
    wincfg->w     = ((XSCREEN_FB_W + 3) / 4) * 4;
    wincfg->h     = XSCREEN_FB_H;
    wincfg->fblen = wincfg->w * wincfg->h;
    wincfg->x     = XSCREEN_REGION_X + (XSCREEN_REGION_W - XSCREEN_FB_W) / 2;
    wincfg->y     = XSCREEN_REGION_Y + (XSCREEN_REGION_H - XSCREEN_FB_H) / 2;
    wincfg->y     = (wincfg->y / 2) * 2;
    wincfg->ylast = wincfg->y;

    RT_ASSERT((wincfg->w % 4) == 0);
    RT_ASSERT((wincfg->h % 2) == 0);
    RT_ASSERT(wincfg->fblen <= olpc_data->fblen);

    xoffset = 0;
    yoffset = 0;
    img_info = xscreen_pages_num[olpc_data->pic_id];
    RT_ASSERT(img_info->w <= wincfg->w);
    RT_ASSERT(img_info->h <= wincfg->h);
    rt_display_img_fill(img_info, wincfg->fb, wincfg->w, xoffset + img_info->x, yoffset + img_info->y);

    return RT_EOK;
}

/**
 * olpc xscreen refresh process
 */
static rt_err_t olpc_xscreen_task_fun(struct olpc_xscreen_data *olpc_data)
{
    rt_err_t ret;
    struct rt_display_config  wincfg;
    struct rt_display_config *winhead = RT_NULL;

    //rt_tick_t ticks = rt_tick_get();

    rt_memset(&wincfg, 0, sizeof(struct rt_display_config));

    if ((olpc_data->cmd & UPDATE_XSCREEN) == UPDATE_XSCREEN)
    {
        olpc_data->cmd &= ~UPDATE_XSCREEN;
        olpc_xscreen_region_refresh(olpc_data, &wincfg);
    }

    //refresh screen
    rt_display_win_layers_list(&winhead, &wincfg);
    ret = rt_display_win_layers_set(winhead);
    RT_ASSERT(ret == RT_EOK);

    if (olpc_data->cmd != 0)
    {
        rt_event_send(olpc_data->disp_event, EVENT_XSCREEN_REFRESH);
    }

    //rt_kprintf("ticks = %d\n", rt_tick_get() - ticks);

    return RT_EOK;
}

/*
 **************************************************************************************************
 *
 * olpc xscreen touch functions
 *
 **************************************************************************************************
 */
#if defined(RT_USING_TOUCH)
/**
 * screen touch.
 */
static image_info_t screen_item;
static rt_err_t olpc_xscreen_screen_touch_callback(rt_int32_t touch_id, enum olpc_touch_event event, struct point_info *point, void *parameter)
{
    rt_err_t ret = RT_ERROR;
    struct olpc_xscreen_data *olpc_data = (struct olpc_xscreen_data *)parameter;

    switch (event)
    {
    case TOUCH_EVENT_LONG_DOWN:
        rt_event_send(olpc_data->disp_event, EVENT_XSCREEN_EXIT);
        return RT_EOK;

    default:
        break;
    }

    return ret;
}

static rt_err_t olpc_xscreen_screen_touch_register(void *parameter)
{
    image_info_t *img_info = &screen_item;
    struct olpc_xscreen_data *olpc_data = (struct olpc_xscreen_data *)parameter;
    struct rt_device_graphic_info info;

    rt_memcpy(&info, &olpc_data->disp->info, sizeof(struct rt_device_graphic_info));

    /* screen on button touch register */
    {
        screen_item.w = WIN_LAYERS_W;
        screen_item.h = WIN_LAYERS_H;
        register_touch_item((struct olpc_touch_item *)(&img_info->touch_item), (void *)olpc_xscreen_screen_touch_callback, (void *)olpc_data, 0);
        update_item_coord((struct olpc_touch_item *)(&img_info->touch_item), 0, 0, 0, 0);
    }

    return RT_EOK;
}

static rt_err_t olpc_xscreen_screen_touch_unregister(void *parameter)
{
    image_info_t *img_info = &screen_item;

    unregister_touch_item((struct olpc_touch_item *)(&img_info->touch_item));

    return RT_EOK;
}

#endif

/*
 **************************************************************************************************
 *
 * olpc xscreen demo init & thread
 *
 **************************************************************************************************
 */

/**
 * screen protection timer callback.
 */
static void olpc_xscreen_srcprotect_callback(void *parameter)
{
    struct olpc_xscreen_data *olpc_data = (struct olpc_xscreen_data *)parameter;

    if (++olpc_data->pic_id >= XSCREEN_PIC_MAX_NUM)
    {
        olpc_data->pic_id = 0;
    }

    olpc_data->cmd |= UPDATE_XSCREEN;
    rt_event_send(olpc_data->disp_event, EVENT_XSCREEN_REFRESH);
}

/**
 * olpc xscreen dmeo thread.
 */
static void olpc_xscreen_thread(void *p)
{
    rt_err_t ret;
    uint32_t event;
    struct olpc_xscreen_data *olpc_data;

    olpc_data = (struct olpc_xscreen_data *)rt_malloc(sizeof(struct olpc_xscreen_data));
    RT_ASSERT(olpc_data != RT_NULL);
    rt_memset((void *)olpc_data, 0, sizeof(struct olpc_xscreen_data));

    olpc_data->disp = rt_display_get_disp();
    RT_ASSERT(olpc_data->disp != RT_NULL);

    ret = olpc_xscreen_lutset(olpc_data);
    RT_ASSERT(ret == RT_EOK);

#if defined(RT_USING_TOUCH)
    olpc_xscreen_screen_touch_register(olpc_data);
#endif

    olpc_data->disp_event = rt_event_create("display_event", RT_IPC_FLAG_FIFO);
    RT_ASSERT(olpc_data->disp_event != RT_NULL);

    ret = olpc_xscreen_init(olpc_data);
    RT_ASSERT(ret == RT_EOK);

    olpc_data->timer = rt_timer_create("xscreentmr",
                                       olpc_xscreen_srcprotect_callback,
                                       (void *)olpc_data,
                                       XSCREEN_SRCSAVER_TIME,
                                       RT_TIMER_FLAG_PERIODIC);
    RT_ASSERT(olpc_data->timer != RT_NULL);
    rt_timer_start(olpc_data->timer);

    olpc_data->pic_id = 0;
    olpc_data->cmd = UPDATE_XSCREEN;
    rt_event_send(olpc_data->disp_event, EVENT_XSCREEN_REFRESH);

    while (1)
    {
        ret = rt_event_recv(olpc_data->disp_event,
                            EVENT_XSCREEN_REFRESH | EVENT_XSCREEN_EXIT,
                            RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR,
                            RT_WAITING_FOREVER, &event);
        if (ret != RT_EOK)
        {
            /* Reserved... */
        }

        if (event & EVENT_XSCREEN_REFRESH)
        {
            ret = olpc_xscreen_task_fun(olpc_data);
            RT_ASSERT(ret == RT_EOK);
        }

        if (event & EVENT_XSCREEN_EXIT)
        {
            break;
        }
    }

    /* Thread deinit */
    rt_timer_stop(olpc_data->timer);
    ret = rt_timer_delete(olpc_data->timer);
    RT_ASSERT(ret == RT_EOK);
    olpc_data->timer = RT_NULL;

#if defined(RT_USING_TOUCH)
    olpc_xscreen_screen_touch_unregister(olpc_data);
    olpc_touch_list_clear();
#endif

    olpc_xscreen_deinit(olpc_data);

    rt_event_delete(olpc_data->disp_event);
    olpc_data->disp_event = RT_NULL;

    rt_free(olpc_data);
    olpc_data = RT_NULL;

    rt_event_send(olpc_main_event, EVENT_APP_CLOCK);
}

/**
 * olpc xscreen demo application init.
 */
int olpc_xscreen_app_init(void)
{
    rt_thread_t rtt_xscreen;

    rtt_xscreen = rt_thread_create("olpcxscreen", olpc_xscreen_thread, RT_NULL, 2048, 5, 10);
    RT_ASSERT(rtt_xscreen != RT_NULL);
    rt_thread_startup(rtt_xscreen);

    return RT_EOK;
}

//INIT_APP_EXPORT(olpc_xscreen_app_init);
#endif
