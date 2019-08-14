#include <rtthread.h>
#if defined(RT_USING_OLPC_DEMO) && defined(OLPC_LVGL_CLOCK_ENABLE) && defined(RT_USING_LITTLEVGL2RTT)
#include <stdio.h>
#include <math.h>

#include <littlevgl2rtt.h>
#include <lvgl/lvgl.h>
#include <lvgl/lvgl.h>

#include "drv_heap.h"
#include "image_info.h"
#include "olpc_display.h"

/**
 * color palette for 1bpp
 */
static uint32_t bpp1_lut[2] =
{
    0x00000000, 0x00ffffff
};

/*
 **************************************************************************************************
 *
 * Macro define
 *
 **************************************************************************************************
 */

/* display win layers */
#define DISP_CLOCK_WIN      0

#define DISP_CLOCK_YOFFSET  260//650
#define DISP_UPDATE_TIME    (RT_TICK_PER_SECOND / 100)
#define COLOR_DEPTH         RT_LV_COLOR_DEPTH

#define LV_REFR_TIME        1000

/*
 **************************************************************************************************
 *
 * Declaration
 *
 **************************************************************************************************
 */
LV_FONT_DECLARE(lv_font_50_0_9);
extern image_info_t clock_bkg_info;

/*
 **************************************************************************************************
 *
 * Global static struct & data define
 *
 **************************************************************************************************
 */
struct olpc_clock_data
{
    rt_display_data_t disp;
    rt_event_t  disp_event;
    rt_uint32_t cmd;

    rt_uint8_t hour;
    rt_uint8_t minute;
    rt_uint8_t second;

    rt_uint8_t month;
    rt_uint8_t day;
    rt_uint8_t week;

    rt_uint8_t batval;
    rt_uint8_t msgsta;
    rt_uint8_t locksta;
    rt_uint8_t fingerprintval;

    rt_uint8_t *fb;
    rt_uint32_t fblen;
    rt_timer_t  clock_timer;
    void       *clock_timer_parameter;

    lv_obj_t   *lv_clock;
    lv_obj_t   *lv_date;
    char        date_str[30];
    lv_task_t  *lv_refr_task;
};
static  struct olpc_clock_data *g_olpc_data = RT_NULL;

static uint8_t *week_table[] = {"日", "一", "二", "三", "四", "五", "六"};

/*
 **************************************************************************************************
 *
 * lvgl GUI sub functions: Win layer0.
 *
 **************************************************************************************************
 */

/**
 * Init lvgl_dsc info by image_info
 */
static void lvgl_img_dsc_init(lv_img_dsc_t *dsc, image_info_t *info)
{
    dsc->header.always_zero = 0;
    dsc->header.w = info->w;
    dsc->header.h = info->h;
    dsc->data_size = (info->w * info->h) * LV_COLOR_SIZE / 8;
    dsc->header.cf = LV_IMG_CF_TRUE_COLOR;
    dsc->data = info->data;
}

/**
 * (x, y) = (cx + r*cosA, cy + r*sinA)
 */
static void lvgl_clock_get_coord_by_second(lv_point_t *e, lv_point_t *c, uint32_t r, uint32_t s)
{
    float angle = (float)s / 60.0 * 2 * M_PI - (M_PI / 2);

    e->x = c->x + r * cosf(angle);
    e->y = c->y + r * sinf(angle);
}

/**
 * Refresh clock
 */
static bool lvgl_clock_design(lv_obj_t *lv_clock, const lv_area_t *mask, lv_design_mode_t mode)
{
    struct olpc_clock_data *olpc_data = g_olpc_data;

    if (mode == LV_DESIGN_COVER_CHK)
    {
        return false;       /*A clock won't covert the whole area so return false*/
    }
    else if (mode == LV_DESIGN_DRAW_MAIN)
    {
        lv_opa_t opa_scale = lv_obj_get_opa_scale(lv_clock);          /*Object level opacity*/

        /*Set-up a style for the background*/
        lv_style_t bg_style;
        lv_style_copy(&bg_style, &lv_style_plain);
        bg_style.body.radius = LV_RADIUS_CIRCLE;

        /*Draw the background*/
        lv_img_dsc_t img_dsc;
        lvgl_img_dsc_init(&img_dsc, &clock_bkg_info);
        lv_draw_img(&lv_clock->coords, mask, &img_dsc, &bg_style, opa_scale);

        /*Create a line style*/
        lv_style_t line_style;
        lv_style_copy(&line_style, &lv_style_plain);

        /*Draw a hour line*/
        lv_point_t p1;
        lv_point_t p2;
        uint32_t r = (lv_clock->coords.x2 - lv_clock->coords.x1) / 2;

        p1.x = lv_clock->coords.x1 + r;
        p1.y = lv_clock->coords.y1 + r;

        /*Draw a hour line*/
        line_style.line.color = LV_COLOR_CYAN;
        line_style.line.width = 4 * 2;

        uint32_t hour = olpc_data->hour;
        if (hour >= 12)
        {
            hour -= 12;
        }
        lvgl_clock_get_coord_by_second(&p2, &p1, (r - 85), (hour * 60 / 12) + (olpc_data->minute * 5) / 60);
        lv_draw_line(&p1, &p2, mask, &line_style, opa_scale);

        /*Draw a minute line*/
        line_style.line.color = LV_COLOR_YELLOW;
        line_style.line.width = 3 * 2;
        lvgl_clock_get_coord_by_second(&p2, &p1, (r - 80), olpc_data->minute);
        lv_draw_line(&p1, &p2, mask, &line_style, opa_scale);

        /*Draw a second line*/
        line_style.line.color = LV_COLOR_RED;
        line_style.line.width = 2 * 2;
        lvgl_clock_get_coord_by_second(&p2, &p1, (r - 75), olpc_data->second);
        lv_draw_line(&p1, &p2, mask, &line_style, opa_scale);
    }

    return true;
}

/**
 * Called periodically to draw clock.
 */
static void lvgl_clock_update(void *param)
{
    struct olpc_clock_data *olpc_data = (struct olpc_clock_data *)param;
    lv_obj_t *lv_clock = olpc_data->lv_clock;
    lv_obj_t *lv_date = olpc_data->lv_date;

    if (++olpc_data->second == 60)
    {
        olpc_data->second = 0;
        if (++olpc_data->minute == 60)
        {
            olpc_data->minute = 0;
            if (++olpc_data->hour >= 24)
            {
                olpc_data->hour = 0;

                if (++olpc_data->week == 7)
                {
                    olpc_data->week = 0;
                }

                if (++olpc_data->day > 31)
                {
                    olpc_data->day = 1;
                    if (++olpc_data->month > 12)
                    {
                        olpc_data->month = 1;
                    }
                }

                // update date
                {
                    char *str = olpc_data->date_str;//lv_label_get_text(date);
                    snprintf(str, 30, "%02u月%02u日  星期%s", olpc_data->month, olpc_data->day, week_table[olpc_data->week]);
                    lv_label_set_text(lv_date, str);
                    lv_obj_invalidate(lv_date);
                }
            }
        }
    }
    lv_obj_invalidate(lv_clock);
}

/**
 * lvgl clock timer callback.
 */
static void lvgl_clock_timeout(void *parameter)
{
    struct olpc_clock_data *olpc_data = (struct olpc_clock_data *)parameter;
    rt_event_t event = olpc_data->disp_event;

    rt_event_send(olpc_data->disp_event, 0x01L << DISP_CLOCK_WIN);
}

/**
 * lvgl clock dmeo init.
 */
static rt_err_t lvgl_clock_init(struct olpc_clock_data *olpc_data)
{
    rt_err_t    ret;
    rt_uint8_t  *fb;
    rt_uint32_t fb_len;
    rt_timer_t  timer;
    lv_obj_t    *lv_clock, *lv_date;
    lv_task_t   *refr_task;
    rt_device_t device = olpc_data->disp->device;
    struct rt_device_graphic_info info;
    struct display_state *state = (struct display_state *)device->user_data;
    struct rt_device_graphic_info *graphic_info = &state->graphic_info;

    ret = rt_device_control(device, RTGRAPHIC_CTRL_GET_INFO, &info);
    RT_ASSERT(ret == RT_EOK);

    fb_len  = (LV_HOR_RES * COLOR_DEPTH / 8 + 3) / 4 * 4 * LV_VER_RES;
    fb      = (rt_uint8_t *)rt_malloc_large(fb_len);
    RT_ASSERT(fb != RT_NULL);
    rt_memset((void *)fb, 0, fb_len);

    /* Var init */
    olpc_data->hour = 3;
    olpc_data->minute = 30;
    olpc_data->second = 0;
    olpc_data->day = 1;
    olpc_data->month = 9;
    olpc_data->week = 3;
    snprintf(olpc_data->date_str,
             sizeof(olpc_data->date_str),
             "%02u月%02u日  星期%s",
             olpc_data->month,
             olpc_data->day,
             week_table[olpc_data->week]);

    /* set info.framebuffer */
    graphic_info->framebuffer = fb;

    /* init littlevGL */
    ret = littlevgl2rtt_init(device, NULL);
    RT_ASSERT(ret == RT_EOK);

    /* lv clock init */
    {
        /* clock obj init */
        lv_clock = lv_obj_create(lv_scr_act(), NULL);
        RT_ASSERT(lv_clock != NULL);

        lv_obj_set_size(lv_clock, 440, 440);
        lv_obj_set_pos(lv_clock, 0, 0);
        lv_obj_set_design_func(lv_clock, lvgl_clock_design);

        /* date obj init */
        lv_date = lv_label_create(lv_scr_act(), NULL);
        RT_ASSERT(lv_date != NULL);

        lv_obj_set_size(lv_date, 440, 100);
        lv_obj_set_pos(lv_date, 80, 460);

        lv_style_t label_style;
        lv_style_copy(&label_style, &lv_style_plain);
        label_style.text.font = &lv_font_50_0_9;
        label_style.text.color = LV_COLOR_WHITE;
        lv_obj_set_style(lv_date, &label_style);
        lv_label_set_text(lv_date, olpc_data->date_str);

        //lv_obj_set_design_func(lv_date, lvgl_date_design);

        refr_task = lv_task_create(lvgl_clock_update, LV_REFR_TIME, LV_TASK_PRIO_LOW, olpc_data);
        RT_ASSERT(refr_task != NULL);
    }

    /* init lvgui timer */
    timer = rt_timer_create("display_clock_timer",
                            lvgl_clock_timeout,
                            (void *)olpc_data,
                            DISP_UPDATE_TIME,
                            RT_TIMER_FLAG_PERIODIC);
    RT_ASSERT(timer != RT_NULL);

    rt_timer_start(timer);

    olpc_data->fb  = fb;
    olpc_data->fblen = fb_len;
    olpc_data->clock_timer = timer;
    olpc_data->clock_timer_parameter = (void *)olpc_data;

    olpc_data->lv_refr_task = refr_task;
    olpc_data->lv_date  = lv_date;
    olpc_data->lv_clock = lv_clock;

    return RT_EOK;
}

/**
 * lvgl clock demo deinit.
 */
static void lvgl_clock_deinit(struct olpc_clock_data *olpc_data)
{
    rt_err_t ret;

    ret = rt_timer_stop(olpc_data->clock_timer);
    RT_ASSERT(ret == RT_EOK);

    ret = rt_timer_delete(olpc_data->clock_timer);
    RT_ASSERT(ret == RT_EOK);

    lv_task_del(olpc_data->lv_refr_task);

    lv_obj_del(olpc_data->lv_date);

    lv_obj_del(olpc_data->lv_clock);

    rt_free_large((void *)olpc_data->fb);
}

/**
 * lvgl clock demo task function.
 */
static rt_err_t lvgl_clock_task_fun(struct olpc_clock_data *olpc_data)
{
    lv_task_handler();

    return RT_EOK;
}

/**
 * Hook function for lvgl GUI, used for wait data transfer finish.
 */
uint32_t lv_refr_areas_wait_hook(void *par)
{
    int ret, i;
    struct olpc_clock_data *olpc_data = g_olpc_data;
    rt_device_t device = olpc_data->disp->device;
    struct display_state *state = (struct display_state *)device->user_data;
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
 * Hook function for lvgl GUI, used for start transfer data to LCD
 */
uint32_t lv_refr_areas_update_hook(void *par)
{
    rt_err_t ret;
    struct rt_device_graphic_info info;
    struct olpc_clock_data *olpc_data = g_olpc_data;
    rt_device_t device = olpc_data->disp->device;

    ret = rt_device_control(device, RTGRAPHIC_CTRL_GET_INFO, &info);
    RT_ASSERT(ret == RT_EOK);

    struct rt_display_config wincfg;
    rt_memset(&wincfg, 0, sizeof(struct rt_display_config));
    wincfg.winId = DISP_CLOCK_WIN;
    wincfg.fb    = olpc_data->fb;
    wincfg.fblen = olpc_data->fblen;
    wincfg.x     = ((WIN_LAYERS_W - LV_HOR_RES) / 2);
    wincfg.y     = DISP_CLOCK_YOFFSET;
    wincfg.ylast = DISP_CLOCK_YOFFSET;
    wincfg.w     = LV_HOR_RES;
    wincfg.h     = LV_VER_RES;

    ret = rt_display_win_layers_set(&wincfg);
    RT_ASSERT(ret == RT_EOK);

    return 0;
}

/*
 **************************************************************************************************
 *
 * olpc lvgl clock demo init & thread
 *
 **************************************************************************************************
 */

/**
 * olpc lvgl clock demo thread
 */
static void olpc_lvgl_clock_thread(void *p)
{
    rt_err_t ret;
    uint32_t event;
    struct olpc_clock_data *olpc_data;
    struct rt_display_lut lut0;

    g_olpc_data = olpc_data = (struct olpc_clock_data *)rt_malloc(sizeof(struct olpc_clock_data));
    RT_ASSERT(olpc_data != RT_NULL);
    rt_memset((void *)olpc_data, 0, sizeof(struct olpc_clock_data));

    /* init bpp_lut[256] */
    rt_display_update_lut(FORMAT_RGB_332);

    lut0.winId = DISP_CLOCK_WIN;
    lut0.format = RTGRAPHIC_PIXEL_FORMAT_RGB332;
    lut0.lut  = bpp_lut;
    lut0.size = sizeof(bpp_lut) / sizeof(bpp_lut[0]);

    olpc_data->disp = rt_display_init(&lut0, RT_NULL, RT_NULL);
    RT_ASSERT(olpc_data->disp != RT_NULL);

    olpc_data->disp_event = rt_event_create("display_event", RT_IPC_FLAG_FIFO);
    RT_ASSERT(olpc_data->disp_event != RT_NULL);

    ret = lvgl_clock_init(olpc_data);
    RT_ASSERT(ret == RT_EOK);

    rt_event_send(olpc_data->disp_event, 0x01L << DISP_CLOCK_WIN);

    while (1)
    {
        ret = rt_event_recv(olpc_data->disp_event, 0x07,
                            RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR,
                            RT_WAITING_FOREVER, &event);
        if (ret != RT_EOK)
        {
            /* Reserved... */
        }

        if (event & 0x01L << DISP_CLOCK_WIN)
        {
            ret = lvgl_clock_task_fun(olpc_data);
            RT_ASSERT(ret == RT_EOK);
        }
    }

    /* Thread deinit */
    lvgl_clock_deinit(olpc_data);

    rt_event_delete(olpc_data->disp_event);

    rt_display_deinit(olpc_data->disp);

    rt_free(olpc_data);
}

/**
 * olpc lvgl clock demo init
 */
int olpc_lvgl_clock_app_init(void)
{
    rt_thread_t thread;

    thread = rt_thread_create("olpcclock", olpc_lvgl_clock_thread, RT_NULL, 2048, 5, 10);
    RT_ASSERT(thread != RT_NULL);

    rt_thread_startup(thread);

    return RT_EOK;
}

INIT_APP_EXPORT(olpc_lvgl_clock_app_init);
#endif
