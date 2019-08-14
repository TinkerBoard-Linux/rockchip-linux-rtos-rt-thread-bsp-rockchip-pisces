#include <rtthread.h>
#if defined(RT_USING_OLPC_DEMO) && defined(OLPC_EBOOK_ENABLE)

#include "drv_heap.h"
#include "image_info.h"
#include "olpc_display.h"

#if defined(RT_USING_TOUCH)
#include "drv_touch.h"
#endif

/**
 * color palette for 1bpp
 */
static uint32_t bpp1_lut[2] =
{
    0x000000, 0x005E5E5E
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

#define EBOOK_TIMER_PERIOD  (RT_TICK_PER_SECOND / 100)
#define BTN_HOLD_TIME       (RT_TICK_PER_SECOND * 5)
#define BTN_DOWN_TIME       (RT_TICK_PER_SECOND * 1)

/* Event define */
#define EVENT_EBOOK_REFRESH (0x01UL << 0)
#define EVENT_GET_TOUCH     (0x01UL << 1)

/* Command define */
#define UPDATE_PAGE         (0x01UL << 0)
#define UPDATE_BTN          (0x01UL << 1)

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

extern image_info_t ebook_btn_rightup_info;
extern image_info_t ebook_btn_rightdown_info;
extern image_info_t ebook_btn_leftup_info;
extern image_info_t ebook_btn_leftdown_info;

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

    rt_uint8_t *btn_fb;
    rt_uint32_t btn_fblen;

    rt_event_t  disp_event;
    rt_uint32_t cmd;
    rt_uint32_t ticks;

    rt_uint16_t page_num;
    rt_uint8_t  lbtn_num;
    rt_uint8_t  rbtn_num;
    rt_uint8_t  btn_sta;
    rt_uint32_t btnon_timeout;
    rt_uint32_t btndown_timeout;
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

    olpc_data->ticks += EBOOK_TIMER_PERIOD;
    if ((olpc_data->ticks % EBOOK_TIMER_PERIOD) != 0)
    {
        olpc_data->ticks = (olpc_data->ticks / EBOOK_TIMER_PERIOD) * EBOOK_TIMER_PERIOD;
    }

#if defined(RT_USING_TOUCH)
    // btn display on
    if (olpc_data->btn_sta == 1)
    {
        olpc_data->btnon_timeout -= EBOOK_TIMER_PERIOD;
        if (olpc_data->btnon_timeout < EBOOK_TIMER_PERIOD)
        {
            olpc_data->btn_sta = 0;
            olpc_data->cmd |= /*UPDATE_PAGE | */UPDATE_BTN;
            rt_event_send(olpc_data->disp_event, EVENT_EBOOK_REFRESH);
        }

        // btn key timeout
        if (olpc_data->btndown_timeout >= EBOOK_TIMER_PERIOD)
        {
            olpc_data->btndown_timeout -= EBOOK_TIMER_PERIOD;
            if (olpc_data->btndown_timeout < EBOOK_TIMER_PERIOD)
            {
                olpc_data->lbtn_num = 0;
                olpc_data->rbtn_num = 0;

                olpc_data->cmd |= UPDATE_BTN;
                rt_event_send(olpc_data->disp_event, EVENT_EBOOK_REFRESH);
            }
        }
    }

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
    rt_device_t device = olpc_data->disp->device;
    struct rt_display_config wincfg;
    struct rt_device_graphic_info info;

    olpc_data->ticks = 0;
    olpc_data->page_num = 0;
    olpc_data->lbtn_num = 0;
    olpc_data->rbtn_num = 0;
    olpc_data->btn_sta = 0;
    olpc_data->btnon_timeout = 0;
    olpc_data->btndown_timeout = 0;

    olpc_data->cmd = UPDATE_PAGE;

    ret = rt_device_control(device, RTGRAPHIC_CTRL_GET_INFO, &info);
    RT_ASSERT(ret == RT_EOK);

    olpc_data->btn_fblen = BTN_FB_W * BTN_FB_H * 2;
    olpc_data->btn_fb    = (rt_uint8_t *)rt_malloc_large(olpc_data->btn_fblen);
    RT_ASSERT(olpc_data->btn_fb != RT_NULL);

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

    olpc_data->ebook_timer = rt_timer_create("olpc_ebook_timer",
                             olpc_ebook_timeout,
                             (void *)olpc_data,
                             EBOOK_TIMER_PERIOD,
                             RT_TIMER_FLAG_PERIODIC);
    RT_ASSERT(olpc_data->ebook_timer != RT_NULL);
    olpc_data->ebook_timer_parameter = (void *)olpc_data;

    rt_timer_start(olpc_data->ebook_timer);

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
    rt_free_large((void *)olpc_data->btn_fb);
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
    struct rt_display_config btnwin, pagewin, *wlist_head = RT_NULL;

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

    if ((olpc_data->cmd & UPDATE_BTN) == UPDATE_BTN)
    {
        olpc_data->cmd &= ~UPDATE_BTN;

        rt_display_win_layers_list(&wlist_head, &btnwin);

        rt_memset(&btnwin, 0, sizeof(struct rt_display_config));
        btnwin.winId = EBOOK_BTG_RGB565_WIN;
        btnwin.fb    = olpc_data->btn_fb;
        btnwin.colorkey = COLOR_KEY_EN | 0x000000;
        btnwin.w     = BTN_FB_W;
        btnwin.h     = BTN_FB_H;
        btnwin.fblen = btnwin.w * btnwin.h * 2;
        btnwin.x     = BTN_REGION_X + (BTN_REGION_W - BTN_FB_W) / 2;
        btnwin.y     = BTN_REGION_Y + (BTN_REGION_H - BTN_FB_H) / 2;
        btnwin.ylast = btnwin.y;

        RT_ASSERT((btnwin.w % 4) == 0);
        RT_ASSERT((btnwin.h % 2) == 0);
        RT_ASSERT(btnwin.fblen <= olpc_data->btn_fblen);

        rt_memset((void *)btnwin.fb, 0x00, btnwin.fblen);

        xoffset = 0;
        yoffset = 0;

        if (olpc_data->btn_sta == 1)
        {
            //draw left btn
            img_info     = btn_left_num[olpc_data->lbtn_num];
            //rt_kprintf("lbtn_num = %d\n", olpc_data->lbtn_num);
            RT_ASSERT(img_info->w <= btnwin.w);
            RT_ASSERT(img_info->h <= btnwin.h);
            rt_display_img_fill(img_info, btnwin.fb, btnwin.w, xoffset + img_info->x, yoffset + img_info->y);

            //draw left btn
            img_info     = btn_right_num[olpc_data->rbtn_num];
            //rt_kprintf("rbtn_num = %d\n", olpc_data->rbtn_num);
            RT_ASSERT(img_info->w <= btnwin.w);
            RT_ASSERT(img_info->h <= btnwin.h);
            rt_display_img_fill(img_info, btnwin.fb, btnwin.w, xoffset + img_info->x, yoffset + img_info->y);
        }
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
 * olpc ebook touch_panel process.
 */

static rt_err_t olpc_ebook_get_touch(struct olpc_ebook_data *olpc_data)
{
    rt_size_t rd_size;
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

    if (olpc_data->btn_sta == 0)
    {
        olpc_data->btn_sta = 1;

        olpc_data->lbtn_num = 0;
        olpc_data->rbtn_num = 0;
        olpc_data->cmd |= /*UPDATE_PAGE | */UPDATE_BTN;
        rt_event_send(olpc_data->disp_event, EVENT_EBOOK_REFRESH);
    }
    else
    {
        image_info_t *img_info;
        rt_uint16_t x = BTN_REGION_X + (BTN_REGION_W - BTN_FB_W) / 2;
        rt_uint16_t y = BTN_REGION_Y + (BTN_REGION_H - BTN_FB_H) / 2;

        //left btn
        img_info = btn_left_num[olpc_data->lbtn_num];
        if (((x + img_info->x) < olpc_data->point.x) && (olpc_data->point.x < (x + img_info->x + img_info->w)))
        {
            if (((y + img_info->y) < olpc_data->point.y) && (olpc_data->point.y < (y + img_info->y + img_info->h)))
            {
                olpc_data->lbtn_num  = 1;
                olpc_data->rbtn_num  = 0;

                if (olpc_data->page_num > 0)
                {
                    olpc_data->page_num --;
                }

                olpc_data->btndown_timeout = BTN_DOWN_TIME;
                olpc_data->cmd |= UPDATE_PAGE | UPDATE_BTN;
                rt_event_send(olpc_data->disp_event, EVENT_EBOOK_REFRESH);
                goto btn_down;
            }
        }

        //right btn
        img_info = btn_right_num[olpc_data->rbtn_num];
        if (((x + img_info->x) < olpc_data->point.x) && (olpc_data->point.x < (x + img_info->x + img_info->w)))
        {
            if (((y + img_info->y) < olpc_data->point.y) && (olpc_data->point.y < (y + img_info->y + img_info->h)))
            {
                olpc_data->lbtn_num  = 0;
                olpc_data->rbtn_num  = 1;

                if (olpc_data->page_num < EBOOK_PAGE_MAX_NUM - 1)
                {
                    olpc_data->page_num ++;
                }

                olpc_data->btndown_timeout = BTN_DOWN_TIME;
                olpc_data->cmd |= UPDATE_PAGE | UPDATE_BTN;
                rt_event_send(olpc_data->disp_event, EVENT_EBOOK_REFRESH);
                //goto btn_down;
            }
        }
    }

btn_down:
    olpc_data->btnon_timeout = BTN_HOLD_TIME;   //reset timer

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
    olpc_data->touch_dev = rt_device_find("s3706");
    RT_ASSERT(olpc_data->touch_dev != RT_NULL);

    ret = rt_device_open(olpc_data->touch_dev, RT_DEVICE_FLAG_RDWR);
    RT_ASSERT(ret == RT_EOK);
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
    rt_thread_t rtt_ebook;

    rtt_ebook = rt_thread_create("olpcclock", olpc_ebook_thread, RT_NULL, 2048 * 5, 5, 10);
    RT_ASSERT(rtt_ebook != RT_NULL);
    rt_thread_startup(rtt_ebook);

    return RT_EOK;
}

INIT_APP_EXPORT(olpc_ebook_app_init);
#endif
