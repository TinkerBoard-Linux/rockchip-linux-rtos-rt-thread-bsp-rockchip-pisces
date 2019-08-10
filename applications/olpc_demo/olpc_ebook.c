#include <rtthread.h>
#if defined(RT_USING_OLPC_DEMO) && defined(OLPC_EBOOK_ENABLE)

#include "drv_heap.h"
#include "image_info.h"
#include "olpc_display.h"

#if defined(RT_USING_TOUCH)
#include "drv_touch.h"
#endif


/*
 **************************************************************************************************
 *
 * Macro define
 *
 **************************************************************************************************
 */
#define COLOR_DEPTH         1

#define EBOOK_WIN_FB_MAX_W  ((WIN_LAYERS_W / 32) * 32)    /* align 32 */
#define EBOOK_WIN_FB_MAX_H  WIN_LAYERS_H

#define EBOOK_REGION_X      0
#define EBOOK_REGION_Y      0
#define EBOOK_REGION_W      WIN_LAYERS_W
#define EBOOK_REGION_H      WIN_LAYERS_H
#define EBOOK_FB_W          1000                /* ebook frame buffer w */
#define EBOOK_FB_H          2000                /* ebook frame buffer h */

#define DISP_EBOOK_WIN      1
#define EBOOK_TIMER_PERIOD  (RT_TICK_PER_SECOND / 100)

/* Event define */
#define EVENT_EBOOK_REFRESH (0x01UL << 0)
#define EVENT_GET_TOUCH     (0x01UL << 1)

/* Command define */
#define UPDATE_PAGE         (0x01UL << 0)

/*
 **************************************************************************************************
 *
 * Declaration
 *
 **************************************************************************************************
 */
extern image_info_t bpp1_text1_info;

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

#if defined(RT_USING_TOUCH)
    struct point_info point;
    rt_device_t   touch_dev;
#endif

    rt_uint8_t *fb;
    rt_uint32_t fblen;
    rt_timer_t  ebook_timer;
    void       *ebook_timer_parameter;

    rt_event_t  disp_event;
    rt_uint32_t cmd;
    rt_uint32_t ticks;

    rt_uint16_t page_num;
};

static image_info_t *ebook_pages_num[3] =
{
    &bpp1_text1_info,
    &bpp1_text1_info,
    &bpp1_text1_info,
};

/*
 **************************************************************************************************
 *
 * 1bpp ebook test demo
 *
 **************************************************************************************************
 */
/**
 * olpc ebook demo timer callback.
 */
static void olpc_ebook_timeout(void *parameter)
{
    struct olpc_ebook_data *olpc_data = (struct olpc_ebook_data *)parameter;
    rt_event_t event = olpc_data->disp_event;

    olpc_data->ticks += EBOOK_TIMER_PERIOD;

#if defined(RT_USING_TOUCH)
    // Check touch screen every 10ms
    if ((olpc_data->ticks % 10) == 0)
    {
        rt_event_send(olpc_data->disp_event, EVENT_GET_TOUCH);
    }
#endif
}

/**
 * olpc ebook demo init.
 */
static rt_err_t olpc_ebook_init(struct olpc_ebook_data *olpc_data)
{
    rt_err_t    ret;
    rt_uint8_t  *fb;
    rt_uint32_t fb_len;
    rt_timer_t  timer;
    rt_device_t device = olpc_data->disp->device;
    struct rt_device_graphic_info info;

    olpc_data->page_num = 0;
    olpc_data->ticks = 0;
    olpc_data->cmd = UPDATE_PAGE;

    ret = rt_device_control(device, RTGRAPHIC_CTRL_GET_INFO, &info);
    RT_ASSERT(ret == RT_EOK);

    fb_len  = EBOOK_WIN_FB_MAX_W * EBOOK_WIN_FB_MAX_H * COLOR_DEPTH / 8;
    fb   = (rt_uint8_t *)rt_malloc_large(fb_len);
    RT_ASSERT(fb != RT_NULL);

    rt_uint16_t fb_w   = 32;
    rt_uint16_t fb_h   = WIN_LAYERS_H;
    RT_ASSERT((fb_w % 4) == 0);
    RT_ASSERT((fb_h % 2) == 0);
    RT_ASSERT((fb_w * fb_h) <= fb_len);
    rt_memset((void *)fb, 0x00, fb_len);

    //refresh screen
    ret = rt_display_win_layer_set(device, DISP_EBOOK_WIN, RT_TRUE,
                                   fb,   fb_w * fb_h / 8,
                                   fb_w, fb_h,
                                   0,    0,
                                   0,    fb_h);
    RT_ASSERT(ret == RT_EOK);

    timer = rt_timer_create("olpc_ebook_timer",
                            olpc_ebook_timeout,
                            (void *)olpc_data,
                            EBOOK_TIMER_PERIOD,
                            RT_TIMER_FLAG_PERIODIC);
    RT_ASSERT(timer != RT_NULL);

    rt_timer_start(timer);

    olpc_data->fb  = fb;
    olpc_data->fblen = fb_len;

    olpc_data->ebook_timer = timer;
    olpc_data->ebook_timer_parameter = (void *)olpc_data;

    return RT_EOK;
}

/**
 * olpc ebook demo deinit.
 */
static void olpc_ebook_deinit(struct olpc_ebook_data *olpc_data)
{
    rt_err_t ret;

    ret = rt_timer_stop(olpc_data->ebook_timer);
    RT_ASSERT(ret == RT_EOK);

    ret = rt_timer_delete(olpc_data->ebook_timer);
    RT_ASSERT(ret == RT_EOK);

    rt_free_large((void *)olpc_data->fb);
}

/**
 * olpc ebook page refresh
 */
static rt_err_t olpc_ebook_page_refresh(struct olpc_ebook_data *olpc_data)
{
    rt_err_t ret;
    rt_int32_t    x, y;
    rt_int32_t    xoffset, yoffset;
    rt_uint8_t   *fb = olpc_data->fb;
    rt_uint32_t  fb_w, fb_h, fb_len;
    rt_device_t  device = olpc_data->disp->device;
    image_info_t *img_info = NULL;
    struct rt_device_graphic_info info;

    rt_tick_t ticks = rt_tick_get();

    ret = rt_device_control(device, RTGRAPHIC_CTRL_GET_INFO, &info);
    RT_ASSERT(ret == RT_EOK);

    rt_display_sync_hook(device, DISP_EBOOK_WIN);

    fb     = olpc_data->fb;
    fb_w   = ((EBOOK_FB_W + 31) / 32) * 32;
    fb_h   = EBOOK_FB_H;
    fb_len = fb_w * fb_h / 8;
    RT_ASSERT((fb_w % 4) == 0);
    RT_ASSERT((fb_h % 2) == 0);
    RT_ASSERT(fb_len <= olpc_data->fblen);
    rt_memset((void *)fb, 0x00, fb_len);

    xoffset = 0;
    yoffset = 0;
    x  = EBOOK_REGION_X + (EBOOK_REGION_W - EBOOK_FB_W) / 2;
    y  = EBOOK_REGION_Y + (EBOOK_REGION_H - EBOOK_FB_H) / 2;

    //draw pages
    img_info = ebook_pages_num[olpc_data->page_num];
    rt_kprintf("PAGE: page_num = %d\n", olpc_data->page_num);
    RT_ASSERT(img_info->w <= fb_w);
    RT_ASSERT(img_info->h <= fb_h);
    rt_display_img_fill(img_info, fb, fb_w, xoffset + img_info->x, yoffset + img_info->y);

    //refresh screen
    ret = rt_display_win_layer_set(device, DISP_EBOOK_WIN, RT_TRUE,
                                   fb,   fb_len,
                                   fb_w, fb_h,
                                   x,    y,
                                   y,    fb_h);
    RT_ASSERT(ret == RT_EOK);

    rt_kprintf("ebook page refresh ticks = %d\n", rt_tick_get() - ticks);

    return RT_EOK;
}

/**
 * olpc ebook refresh process
 */
static rt_err_t olpc_ebook_task_fun(struct olpc_ebook_data *olpc_data)
{
    rt_err_t ret;

    if ((olpc_data->cmd & UPDATE_PAGE) == UPDATE_PAGE)
    {
        olpc_data->cmd &= ~UPDATE_PAGE;

        ret = olpc_ebook_page_refresh(olpc_data);
        RT_ASSERT(ret == RT_EOK);

    }

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
 * olpc ebook touch_panel process.
 */

static rt_err_t olpc_ebook_get_touch(struct olpc_ebook_data *olpc_data)
{
    rt_size_t rd_size;
    rt_uint16_t i, x, y;
    struct point_info point;
    struct rt_device_graphic_info info;
    rt_memcpy(&info, &olpc_data->disp->info, sizeof(struct rt_device_graphic_info));

    rd_size = rt_device_read(olpc_data->touch_dev, 0, &point, sizeof(struct point_info));
    RT_ASSERT(rd_size != 0);

    if (point.status == 0)
    {
        rt_memcpy(&olpc_data->point, &point, sizeof(struct point_info));
        return RT_EOK;
    }
    else if (point.status == olpc_data->point.status)
    {
        return RT_EOK;
    }
    rt_memcpy(&olpc_data->point, &point, sizeof(struct point_info));

    {
        olpc_data->page_num ++;
        olpc_data->page_num %= 3;
        olpc_data->cmd |= UPDATE_PAGE;
        rt_event_send(olpc_data->disp_event, EVENT_EBOOK_REFRESH);
    }

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

    olpc_data = (struct olpc_ebook_data *)rt_malloc(sizeof(struct olpc_ebook_data));
    RT_ASSERT(olpc_data != RT_NULL);
    rt_memset((void *)olpc_data, 0, sizeof(struct olpc_ebook_data));

    olpc_data->disp = rt_display_init();
    RT_ASSERT(olpc_data->disp != RT_NULL);

#if defined(RT_USING_TOUCH)
    olpc_data->touch_dev = rt_device_find("s3706");
    RT_ASSERT(olpc_data->touch_dev != RT_NULL);
#endif

    olpc_data->disp_event = rt_event_create("display_event", RT_IPC_FLAG_FIFO);
    RT_ASSERT(olpc_data->disp_event != RT_NULL);

    ret = olpc_ebook_init(olpc_data);
    RT_ASSERT(ret == RT_EOK);

    rt_event_send(olpc_data->disp_event, EVENT_EBOOK_REFRESH);

    while (1)
    {
        ret = rt_event_recv(olpc_data->disp_event, EVENT_EBOOK_REFRESH | EVENT_GET_TOUCH,
                            RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR,
                            RT_WAITING_FOREVER, &event);
        if (ret != RT_EOK)
        {
            /* Reserved... */
        }

#if defined(RT_USING_TOUCH)
        if (event & EVENT_GET_TOUCH)
        {
            ret = olpc_ebook_get_touch(olpc_data);
            RT_ASSERT(ret == RT_EOK);
        }
#endif

        if (event & EVENT_EBOOK_REFRESH)
        {
            ret = olpc_ebook_task_fun(olpc_data);
            RT_ASSERT(ret == RT_EOK);
        }
    }

    /* Thread deinit */
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
    rt_thread_t rtt_ebook, rtt_touch;

    rtt_ebook = rt_thread_create("olpcclock", olpc_ebook_thread, RT_NULL, 2048, 5, 10);
    RT_ASSERT(rtt_ebook != RT_NULL);
    rt_thread_startup(rtt_ebook);

#if defined(RT_USING_TOUCH)
    rtt_touch = rt_thread_create("touch", touch_thread_entry, RT_NULL, 1024, 10, 20);
    RT_ASSERT(rtt_touch != RT_NULL);
    rt_thread_startup(rtt_touch);
#endif

    return RT_EOK;
}

INIT_APP_EXPORT(olpc_ebook_app_init);
#endif
