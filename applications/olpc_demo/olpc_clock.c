#include <rtthread.h>
#if defined(RT_USING_OLPC_DEMO) && defined(OLPC_CLOCK_ENABLE)

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
#define CLOCK_RGB332_WIN    0
#define CLOCK_GRAY1_WIN     1

/* display fb size */
#define DISP_WIN_W          440
#define DISP_WIN_H          520

/* display region define */
#define CLOCK_REGION_X      0
#define CLOCK_REGION_Y      0
#define CLOCK_REGION_W      WIN_LAYERS_W
#define CLOCK_REGION_H      660
#define CLOCK_FB_W          440     /* clock frame buffer w */
#define CLOCK_FB_H          440     /* clock frame buffer h */
#define CLOCK_MOVE_XSTEP    (200)   /* clock X direction move step */
#define CLOCK_MOVE_YSTEP    (100)   /* clock Y direction move step */

#define MSG_REGION_X        0
#define MSG_REGION_Y        (CLOCK_REGION_Y + CLOCK_REGION_H)
#define MSG_REGION_W        WIN_LAYERS_W
#define MSG_REGION_H        480
#define MSG_FB_W            440     /* message frame buffer w */
#define MSG_FB_H            300     /* message frame buffer h */
#define MSG_MOVE_XSTEP      (200)   /* message X direction move step */
#define MSG_MOVE_YSTEP      (50)    /* message Y direction move step */

#define HOME_REGION_X       0
#define HOME_REGION_Y       (MSG_REGION_Y + MSG_REGION_H)
#define HOME_REGION_W       WIN_LAYERS_W
#define HOME_REGION_H       860
#define HOME_FB_W           544     /* home frame buffer w */
#define HOME_FB_H           540     /* home frame buffer h */

#define FP_REGION_X         0
#define FP_REGION_Y         (HOME_REGION_Y + HOME_REGION_H)
#define FP_REGION_W         WIN_LAYERS_W
#define FP_REGION_H         190
#define FP_FB_W             160     /* fingerprint frame buffer w */
#define FP_FB_H             150     /* fingerprint frame buffer h */

/* Event define */
#define EVENT_UPDATE_CLOCK  (0x01UL << 0)
#define EVENT_GET_TOUCH     (0x01UL << 1)

/* Command define */
#define UPDATE_CLOCK        (0x01UL << 0)
#define UPDATE_MSG          (0x01UL << 1)
#define UPDATE_HOME         (0x01UL << 2)
#define UPDATE_FINGERP      (0x01UL << 3)
#define MOVE_CLOCK          (0x01UL << 4)
#define MOVE_MSG            (0x01UL << 5)

#define COLOR_DEPTH         8

#define DISP_UPDATE_TIME    (RT_TICK_PER_SECOND / 100)
#define HOME_HOLD_TIME      (RT_TICK_PER_SECOND * 5)
#define FP_HOLD_TIME        (RT_TICK_PER_SECOND * 5)
#define FP_LOOP_TIME        (RT_TICK_PER_SECOND / 10)

/*
 **************************************************************************************************
 *
 * Declaration
 *
 **************************************************************************************************
 */
extern image_info_t clock_bkg_info;
extern image_info_t clock_sec_info;
extern image_info_t clock_min_info;
extern image_info_t clock_hour_info;

extern image_info_t msg_font_0_info;
extern image_info_t msg_font_1_info;
extern image_info_t msg_font_2_info;
extern image_info_t msg_font_percent_info;

extern image_info_t msg_font_CHN_6_info;
extern image_info_t msg_font_CHN_day_info;
extern image_info_t msg_font_CHN_month_info;
extern image_info_t msg_font_CN_week_info;

extern image_info_t msg_bat5_info;
extern image_info_t msg_mov3_info;

extern image_info_t msg_music3_info;
extern image_info_t msg_qq3_info;
extern image_info_t msg_wb3_info;
extern image_info_t msg_wx3_info;

extern image_info_t home_backgroung_info;
extern image_info_t home_arrow1_info;
extern image_info_t home_lock1_info;
extern image_info_t home_unlock1_info;
extern image_info_t home_light1_info;
extern image_info_t home_cam1_info;
extern image_info_t home_srlock1_info;
extern image_info_t home_clock1_info;
extern image_info_t home_ebook1_info;
extern image_info_t home_game1_info;
extern image_info_t home_calc1_info;

extern image_info_t fingerprint0_info;
extern image_info_t fingerprint1_info;
extern image_info_t fingerprint2_info;
extern image_info_t fingerprint3_info;

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

#if defined(RT_USING_TOUCH)
    struct point_info point;
    rt_device_t   touch_dev;
#endif

    rt_uint8_t *fb;
    rt_uint32_t fblen;
    rt_timer_t  clock_timer;
    void       *clock_timer_parameter;

    rt_event_t  disp_event;
    rt_uint32_t cmd;

    rt_uint8_t  hour;
    rt_uint8_t  minute;
    rt_uint8_t  second;
    rt_uint32_t ticks;

    rt_uint8_t  month;
    rt_uint8_t  day;
    rt_uint8_t  week;

    rt_uint8_t  batval;
    rt_uint32_t moval;

    rt_uint8_t  musicval;
    rt_uint8_t  qqval;
    rt_uint8_t  webval;
    rt_uint8_t  wexval;

    rt_int16_t  clock_xoffset;
    rt_int16_t  clock_yoffset;
    rt_int8_t   clock_xdir;
    rt_int8_t   clock_ydir;
    rt_int16_t  clock_ylast;

    rt_int16_t  msg_xoffset;
    rt_int16_t  msg_yoffset;
    rt_int16_t  msg_xdir;
    rt_int16_t  msg_ydir;
    rt_int16_t  msg_ylast;

    rt_uint8_t  home_id;
    rt_uint8_t  home_sta;
    rt_uint32_t home_timeout;

    rt_uint8_t  fp_id;
    rt_uint8_t  fp_sta;
    rt_uint32_t fp_timeout;
    rt_uint32_t fp_lpcnt;
};

/* 0 ~ 9 */
static image_info_t *msg_font_num[10] =
{
    &msg_font_0_info,
    &msg_font_1_info,
    &msg_font_2_info,
    &msg_font_0_info,
    &msg_font_0_info,
    &msg_font_0_info,
    &msg_font_0_info,
    &msg_font_0_info,
    &msg_font_0_info,
    &msg_font_0_info,
};

static image_info_t *msg_week_num[7] =
{
    &msg_font_CHN_day_info,
    &msg_font_CHN_day_info,
    &msg_font_CHN_day_info,
    &msg_font_CHN_day_info,
    &msg_font_CHN_day_info,
    &msg_font_CHN_day_info,
    &msg_font_CHN_6_info,
};

static image_info_t *msg_bat_num[5] =
{
    &msg_bat5_info,
    &msg_bat5_info,
    &msg_bat5_info,
    &msg_bat5_info,
    &msg_bat5_info,
};

static image_info_t *msg_music_num[3] =
{
    &msg_music3_info,
    &msg_music3_info,
    &msg_music3_info,
};

static image_info_t *msg_qq_num[3] =
{
    &msg_qq3_info,
    &msg_qq3_info,
    &msg_qq3_info,
};

static image_info_t *msg_web_num[3] =
{
    &msg_wb3_info,
    &msg_wb3_info,
    &msg_wb3_info,
};

static image_info_t *msg_wx_num[3] =
{
    &msg_wx3_info,
    &msg_wx3_info,
    &msg_wx3_info,
};

static image_info_t *home_item[8 + 1] =
{
    &home_unlock1_info,
    &home_light1_info,
    &home_cam1_info,
    &home_srlock1_info,
    &home_clock1_info,
    &home_ebook1_info,
    &home_game1_info,
    &home_calc1_info,
    RT_NULL,
};

static image_info_t *fingerprint_item[7] =
{
    &fingerprint3_info,
    &fingerprint2_info,
    &fingerprint1_info,
    &fingerprint0_info,
    &fingerprint1_info,
    &fingerprint2_info,
    &fingerprint3_info
};
/*
 **************************************************************************************************
 *
 * Display clock demo functions
 *
 **************************************************************************************************
 */
/**
 * Display clock demo timer callback.
 */
static void olpc_clock_timeout(void *parameter)
{
    struct olpc_clock_data *olpc_data = (struct olpc_clock_data *)parameter;

    olpc_data->ticks += DISP_UPDATE_TIME;
    if ((olpc_data->ticks % DISP_UPDATE_TIME) != 0)
    {
        olpc_data->ticks = (olpc_data->ticks / DISP_UPDATE_TIME) * DISP_UPDATE_TIME;
    }

    //clock update every 1000ms
    if ((olpc_data->ticks % 1000) == 0)
    {
        ++olpc_data->second;

        if (olpc_data->second >= 60)
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
                    olpc_data->cmd |= UPDATE_MSG;
                    rt_event_send(olpc_data->disp_event, EVENT_UPDATE_CLOCK);
                }
            }
        }

        olpc_data->cmd |= UPDATE_CLOCK;
        rt_event_send(olpc_data->disp_event, EVENT_UPDATE_CLOCK);

    }

    // clock region move update every 3 min
    if ((olpc_data->ticks % (1000 * 60 * 3)) == 0)
    {
        olpc_data->cmd |= UPDATE_CLOCK | MOVE_CLOCK;
        rt_event_send(olpc_data->disp_event, EVENT_UPDATE_CLOCK);
    }

    // msg region move update every 3 min
    if ((olpc_data->ticks % (1000 * 60 * 3)) == 0)
    {
        olpc_data->cmd |= UPDATE_MSG | MOVE_MSG;
        rt_event_send(olpc_data->disp_event, EVENT_UPDATE_CLOCK);
    }

#if defined(RT_USING_TOUCH)
    // home on state time out check, timeout = HOME_HOLD_TIME ms
    if (olpc_data->home_sta == 1)
    {
        olpc_data->home_timeout -= DISP_UPDATE_TIME;
        if (olpc_data->home_timeout == 0)
        {
            olpc_data->home_sta = 0;
            olpc_data->cmd |= UPDATE_HOME;
            rt_event_send(olpc_data->disp_event, EVENT_UPDATE_CLOCK);
        }
    }

    // fingerprint on state time out check && fingerprint loop change
    // fingerprint on state timeout = FP_HOLD_TIME ms
    // fingerprint loop change every FP_LOOP_TIME ms
    if (olpc_data->fp_sta == 1)
    {
        olpc_data->fp_timeout -= DISP_UPDATE_TIME;
        if (olpc_data->fp_timeout == 0)
        {
            olpc_data->fp_sta = 0;
            olpc_data->cmd |= UPDATE_FINGERP;
            rt_event_send(olpc_data->disp_event, EVENT_UPDATE_CLOCK);
        }

        if (olpc_data->fp_lpcnt > 0)
        {
            if ((olpc_data->ticks % FP_LOOP_TIME) == 0)
            {
                olpc_data->fp_lpcnt--;
                olpc_data->fp_id++;
                olpc_data->cmd |= UPDATE_FINGERP;
                rt_event_send(olpc_data->disp_event, EVENT_UPDATE_CLOCK);
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
 * Display clock demo init.
 */
static rt_err_t olpc_clock_init(struct olpc_clock_data *olpc_data)
{
    rt_err_t    ret;
    rt_uint8_t  *fb;
    rt_uint32_t fb_len;
    rt_timer_t  timer;
    rt_device_t device = olpc_data->disp->device;
    struct rt_display_config wincfg;
    struct rt_device_graphic_info info;

    olpc_data->hour = 3;
    olpc_data->minute = 30;
    olpc_data->second = 0;
    olpc_data->ticks = 0;
    olpc_data->day = 2;
    olpc_data->month = 12;
    olpc_data->week = 6;

    olpc_data->batval = 21;
    olpc_data->moval = 100121;
    olpc_data->musicval = 2;
    olpc_data->qqval = 2;
    olpc_data->webval = 2;
    olpc_data->wexval = 2;

    olpc_data->clock_xoffset = 0;
    olpc_data->clock_yoffset = 0;
    olpc_data->clock_xdir = -1;
    olpc_data->clock_ydir = -1;
    olpc_data->clock_ylast = CLOCK_REGION_Y + (CLOCK_REGION_H - CLOCK_FB_H) / 2;

    olpc_data->msg_xoffset = 0;
    olpc_data->msg_yoffset = 0;
    olpc_data->msg_xdir = 1;
    olpc_data->msg_ydir = 1;
    olpc_data->msg_ylast = MSG_REGION_Y + (MSG_REGION_H - MSG_FB_H) / 2;

    olpc_data->home_id = 8;
    olpc_data->home_sta = 1;
    olpc_data->home_timeout = HOME_HOLD_TIME;

    olpc_data->fp_id = 0;
    olpc_data->fp_sta = 1;
    olpc_data->fp_timeout = FP_HOLD_TIME;
    olpc_data->fp_lpcnt = 0;

    olpc_data->cmd = UPDATE_CLOCK | UPDATE_MSG | UPDATE_HOME | UPDATE_FINGERP;

    ret = rt_device_control(device, RTGRAPHIC_CTRL_GET_INFO, &info);
    RT_ASSERT(ret == RT_EOK);

    fb_len  = DISP_WIN_W * DISP_WIN_H * COLOR_DEPTH / 8;
    fb   = (rt_uint8_t *)rt_malloc_large(fb_len);
    RT_ASSERT(fb != RT_NULL);

    rt_memset(&wincfg, 0, sizeof(struct rt_display_config));

    wincfg.winId = CLOCK_RGB332_WIN;
    wincfg.fb    = fb;
    wincfg.x     = 0;
    wincfg.y     = 0;
    wincfg.w     = 4;
    wincfg.h     = WIN_LAYERS_H;
    wincfg.fblen = wincfg.w * wincfg.h;

    RT_ASSERT((wincfg.w % 4) == 0);
    RT_ASSERT((wincfg.h % 2) == 0);
    RT_ASSERT((wincfg.fblen) <= fb_len);

    rt_memset((void *)wincfg.fb, 0x00, wincfg.fblen);

    //refresh screen
    ret = rt_display_win_layers_set(&wincfg);
    RT_ASSERT(ret == RT_EOK);

    timer = rt_timer_create("olpc_clock_timer",
                            olpc_clock_timeout,
                            (void *)olpc_data,
                            DISP_UPDATE_TIME,
                            RT_TIMER_FLAG_PERIODIC);
    RT_ASSERT(timer != RT_NULL);

    rt_timer_start(timer);

    olpc_data->fb  = fb;
    olpc_data->fblen = fb_len;

    olpc_data->clock_timer = timer;
    olpc_data->clock_timer_parameter = (void *)olpc_data;

    return RT_EOK;
}

/**
 * Display clock demo deinit.
 */
static void olpc_clock_deinit(struct olpc_clock_data *olpc_data)
{
    rt_err_t ret;

    ret = rt_timer_stop(olpc_data->clock_timer);
    RT_ASSERT(ret == RT_EOK);

    ret = rt_timer_delete(olpc_data->clock_timer);
    RT_ASSERT(ret == RT_EOK);

    rt_free_large((void *)olpc_data->fb);
}

/**
 * Clock region move.
 */
static rt_err_t olpc_clock_clock_region_move(struct olpc_clock_data *olpc_data)
{
    struct rt_device_graphic_info info;
    rt_memcpy(&info, &olpc_data->disp->info, sizeof(struct rt_device_graphic_info));

    olpc_data->clock_xoffset += olpc_data->clock_xdir * CLOCK_MOVE_XSTEP;
    if (olpc_data->clock_xoffset > (CLOCK_REGION_W - CLOCK_FB_W) / 2)
    {
        olpc_data->clock_xoffset = (CLOCK_REGION_W - CLOCK_FB_W) / 2;
        olpc_data->clock_xdir = -1 * olpc_data->clock_xdir;
    }
    if (olpc_data->clock_xoffset <= (CLOCK_FB_W - CLOCK_REGION_W) / 2)
    {
        olpc_data->clock_xoffset = (CLOCK_FB_W - CLOCK_REGION_W) / 2;
        olpc_data->clock_xdir = -1 * olpc_data->clock_xdir;
    }

    olpc_data->clock_yoffset += olpc_data->clock_ydir * CLOCK_MOVE_YSTEP;
    if (olpc_data->clock_yoffset > (CLOCK_REGION_H - CLOCK_FB_H) / 2)
    {
        olpc_data->clock_yoffset = (CLOCK_REGION_H - CLOCK_FB_H) / 2;
        olpc_data->clock_ydir = -1 * olpc_data->clock_ydir;
    }
    if (olpc_data->clock_yoffset <= (CLOCK_FB_H - CLOCK_REGION_H) / 2)
    {
        olpc_data->clock_yoffset = (CLOCK_FB_H - CLOCK_REGION_H) / 2;
        olpc_data->clock_ydir = -1 * olpc_data->clock_ydir;
    }

    return RT_EOK;
}

/**
 * Clock region refresh.
 */
static rt_err_t olpc_clock_clock_region_refresh(struct olpc_clock_data *olpc_data)
{
    rt_err_t ret;
    rt_int16_t   xoffset, yoffset;
    rt_device_t  device = olpc_data->disp->device;
    image_info_t *img_info = NULL;
    struct rt_display_config wincfg;
    struct rt_device_graphic_info info;

    ret = rt_device_control(device, RTGRAPHIC_CTRL_GET_INFO, &info);

    RT_ASSERT(ret == RT_EOK);

    rt_display_sync_hook(device);

    rt_memset(&wincfg, 0, sizeof(struct rt_display_config));

    wincfg.winId = CLOCK_RGB332_WIN;
    wincfg.fb    = olpc_data->fb;
    wincfg.w     = ((CLOCK_FB_W + 3) / 4) * 4;
    wincfg.h     = CLOCK_FB_H;
    wincfg.fblen = wincfg.w * wincfg.h;
    wincfg.x     = CLOCK_REGION_X + (CLOCK_REGION_W - CLOCK_FB_W) / 2 + olpc_data->clock_xoffset;
    wincfg.y     = CLOCK_REGION_Y + (CLOCK_REGION_H - CLOCK_FB_H) / 2 + olpc_data->clock_yoffset;
    wincfg.ylast = olpc_data->clock_ylast;
    olpc_data->clock_ylast = wincfg.y;

    RT_ASSERT((wincfg.w % 4) == 0);
    RT_ASSERT((wincfg.h % 2) == 0);
    RT_ASSERT(wincfg.fblen <= olpc_data->fblen);

    rt_memset((void *)wincfg.fb, 0x00, wincfg.fblen);

    xoffset = 0;
    yoffset = 0;

    //draw background
    img_info = &clock_bkg_info;
    RT_ASSERT(img_info->w <= wincfg.w);
    RT_ASSERT(img_info->h <= wincfg.h);

    yoffset  += 0;
    xoffset  += (CLOCK_FB_W - img_info->w) / 2;
    rt_display_img_fill(img_info, wincfg.fb, wincfg.w, xoffset, yoffset);

    // draw hour,min,sec
    {
        int32_t hour, angle;
        uint32_t background_w = wincfg.w;//img_info->w;

        xoffset += (img_info->w / 2);
        yoffset += (img_info->h / 2);

        //draw hour line
        img_info = &clock_hour_info;
        RT_ASSERT(img_info->w <= wincfg.w / 2);
        RT_ASSERT(img_info->h <= wincfg.h / 2);

        hour = olpc_data->hour;
        if (hour >= 12)
        {
            hour -= 12;
        }
        angle = hour * (360 / 12) + (olpc_data->minute * 30) / 60 - 90;
        if (angle < 0)
        {
            angle += 360;
        }
        rt_display_rotate((float)angle, img_info->w, img_info->h, img_info->data,
                          (unsigned char *)((uint32_t)wincfg.fb + yoffset * wincfg.w + xoffset), background_w, 16, img_info->h / 2);

        //draw min line
        img_info = &clock_min_info;
        RT_ASSERT(img_info->w <= wincfg.w / 2);
        RT_ASSERT(img_info->h <= wincfg.h / 2);

        angle = olpc_data->minute * (360 / 60);
        angle -= 90;
        if (angle < 0)
        {
            angle += 360;
        }
        rt_display_rotate((float)angle, img_info->w, img_info->h, img_info->data,
                          (unsigned char *)((uint32_t)wincfg.fb + yoffset * wincfg.w + xoffset), background_w, 18, img_info->h / 2);

        //draw second line
        img_info = &clock_sec_info;
        RT_ASSERT(img_info->w <= wincfg.w / 2);
        RT_ASSERT(img_info->h <= wincfg.h / 2);

        angle = olpc_data->second * (360 / 60);
        angle -= 90;
        if (angle < 0)
        {
            angle += 360;
        }
        rt_display_rotate((float)angle, img_info->w, img_info->h, img_info->data,
                          (unsigned char *)((uint32_t)wincfg.fb + yoffset * wincfg.w + xoffset), background_w, 20, img_info->h / 2);
    }

    //refresh screen
    ret = rt_display_win_layers_set(&wincfg);
    RT_ASSERT(ret == RT_EOK);

    return RT_EOK;
}

/**
 * Msg region move.
 */
static rt_err_t olpc_clock_msg_region_move(struct olpc_clock_data *olpc_data)
{
    struct rt_device_graphic_info info;
    rt_memcpy(&info, &olpc_data->disp->info, sizeof(struct rt_device_graphic_info));

    olpc_data->msg_xoffset += olpc_data->msg_xdir * MSG_MOVE_XSTEP;
    if (olpc_data->msg_xoffset > (MSG_REGION_W - MSG_FB_W) / 2)
    {
        olpc_data->msg_xoffset = (MSG_REGION_W - MSG_FB_W) / 2;
        olpc_data->msg_xdir = -1 * olpc_data->msg_xdir;
    }
    if (olpc_data->msg_xoffset <= (MSG_FB_W - MSG_REGION_W) / 2)
    {
        olpc_data->msg_xoffset = (MSG_FB_W - MSG_REGION_W) / 2;
        olpc_data->msg_xdir = -1 * olpc_data->msg_xdir;
    }

    olpc_data->msg_yoffset += olpc_data->msg_ydir * MSG_MOVE_YSTEP;
    if (olpc_data->msg_yoffset > (MSG_REGION_H - MSG_FB_H) / 2)
    {
        olpc_data->msg_yoffset = (MSG_REGION_H - MSG_FB_H) / 2;
        olpc_data->msg_ydir = -1 * olpc_data->msg_ydir;
    }
    if (olpc_data->msg_yoffset <= (MSG_FB_H - MSG_REGION_H) / 2)
    {
        olpc_data->msg_yoffset = (MSG_FB_H - MSG_REGION_H) / 2;
        olpc_data->msg_ydir = -1 * olpc_data->msg_ydir;
    }
    return RT_EOK;
}

/**
 * Clock region refresh.
 */
static rt_err_t olpc_clock_msg_region_refresh(struct olpc_clock_data *olpc_data)
{
    rt_err_t ret;
    rt_int16_t   xoffset, yoffset;
    rt_device_t  device = olpc_data->disp->device;
    image_info_t *img_info = NULL;
    struct rt_display_config wincfg;
    struct rt_device_graphic_info info;

    ret = rt_device_control(device, RTGRAPHIC_CTRL_GET_INFO, &info);
    RT_ASSERT(ret == RT_EOK);

    rt_display_sync_hook(device);

    rt_memset(&wincfg, 0, sizeof(struct rt_display_config));

    wincfg.winId = CLOCK_RGB332_WIN;
    wincfg.fb    = olpc_data->fb;
    wincfg.w     = ((MSG_FB_W + 3) / 4) * 4;
    wincfg.h     = MSG_FB_H;
    wincfg.fblen = wincfg.w * wincfg.h;
    wincfg.x     = MSG_REGION_X + (MSG_REGION_W - MSG_FB_W) / 2 + olpc_data->msg_xoffset;
    wincfg.y     = MSG_REGION_Y + (MSG_REGION_H - MSG_FB_H) / 2 + olpc_data->msg_yoffset;
    wincfg.ylast = olpc_data->msg_ylast;
    olpc_data->msg_ylast = wincfg.y;

    RT_ASSERT((wincfg.w % 4) == 0);
    RT_ASSERT((wincfg.h % 2) == 0);
    RT_ASSERT(wincfg.fblen <= olpc_data->fblen);

    rt_memset((void *)wincfg.fb, 0x00, wincfg.fblen);

    xoffset = 0;
    yoffset = 0;

    // draw date & week
    uint16_t xoffset_bak = xoffset;
    uint16_t yoffset_bak = yoffset;

    yoffset = yoffset_bak + 0;
    {
        /* month num */
        xoffset = xoffset_bak + 49;
        img_info = msg_font_num[(olpc_data->month / 10) % 10];
        RT_ASSERT((yoffset + img_info->h) <= MSG_FB_H);
        if ((olpc_data->month / 10) != 0)
        {
            rt_display_img_fill(img_info, wincfg.fb, wincfg.w, xoffset, yoffset);
        }
        xoffset  = xoffset + img_info->w + 0;
        img_info = msg_font_num[olpc_data->month % 10];
        RT_ASSERT((yoffset + img_info->h) <= MSG_FB_H);
        rt_display_img_fill(img_info, wincfg.fb, wincfg.w, xoffset, yoffset);

        /* month */
        xoffset  = xoffset + img_info->w + 0;
        img_info = &msg_font_CHN_month_info;
        RT_ASSERT((yoffset + img_info->h) <= MSG_FB_H);
        rt_display_img_fill(img_info, wincfg.fb, wincfg.w, xoffset, yoffset);

        /* day num */
        xoffset  = xoffset + img_info->w + 0;
        img_info = msg_font_num[(olpc_data->day / 10) % 10];
        RT_ASSERT((yoffset + img_info->h) <= MSG_FB_H);
        rt_display_img_fill(img_info, wincfg.fb, wincfg.w, xoffset, yoffset);

        xoffset  = xoffset + img_info->w + 0;
        img_info = msg_font_num[olpc_data->day % 10];
        rt_display_img_fill(img_info, wincfg.fb, wincfg.w, xoffset, yoffset);

        /* day */
        xoffset  = xoffset + img_info->w + 0;
        img_info = &msg_font_CHN_day_info;
        RT_ASSERT((yoffset + img_info->h) <= MSG_FB_H);
        rt_display_img_fill(img_info, wincfg.fb, wincfg.w, xoffset, yoffset);

        /* week */
        xoffset  = xoffset + img_info->w + 30;
        img_info = &msg_font_CN_week_info;
        RT_ASSERT((yoffset + img_info->h) <= MSG_FB_H);
        rt_display_img_fill(img_info, wincfg.fb, wincfg.w, xoffset, yoffset);

        /* week num */
        xoffset  = xoffset + img_info->w + 0;
        img_info = msg_week_num[olpc_data->week % 7];
        RT_ASSERT((yoffset + img_info->h) <= MSG_FB_H);
        rt_display_img_fill(img_info, wincfg.fb, wincfg.w, xoffset, yoffset);
    }

    /* draw battery & motion */
    yoffset = yoffset_bak + 80;
    {
        /* battary */
        xoffset = xoffset_bak + 48;
        img_info = msg_bat_num[olpc_data->batval / 20];
        RT_ASSERT((yoffset + img_info->h) <= MSG_FB_H);
        rt_display_img_fill(img_info, wincfg.fb, wincfg.w, xoffset, yoffset + 8);

        /* battary num */
        xoffset += img_info->w + 0;
        img_info = msg_font_num[(olpc_data->batval / 100) % 10];
        RT_ASSERT((yoffset + img_info->h) <= MSG_FB_H);
        if ((olpc_data->batval / 100) != 0)
        {
            rt_display_img_fill(img_info, wincfg.fb, wincfg.w, xoffset, yoffset + 3);
        }

        xoffset += img_info->w + 0;
        img_info = msg_font_num[(olpc_data->batval / 10) % 10];
        RT_ASSERT((yoffset + img_info->h) <= MSG_FB_H);
        if ((olpc_data->batval / 10) != 0)
        {
            rt_display_img_fill(img_info, wincfg.fb, wincfg.w, xoffset, yoffset + 3);
        }

        xoffset += img_info->w + 0;
        img_info = msg_font_num[olpc_data->batval % 10];
        RT_ASSERT((yoffset + img_info->h) <= MSG_FB_H);
        rt_display_img_fill(img_info, wincfg.fb, wincfg.w, xoffset, yoffset + 3);

        xoffset += img_info->w;
        img_info = &msg_font_percent_info;
        RT_ASSERT((yoffset + img_info->h) <= MSG_FB_H);
        rt_display_img_fill(img_info, wincfg.fb, wincfg.w, xoffset, yoffset + 3);

        /* motion */
        xoffset += img_info->w + 30;
        img_info = &msg_mov3_info;
        RT_ASSERT((yoffset + img_info->h) <= MSG_FB_H);
        rt_display_img_fill(img_info, wincfg.fb, wincfg.w, xoffset, yoffset + 0);

        /* motion num */
        uint8_t flag = 0;
        xoffset += img_info->w + 0;
        img_info = msg_font_num[(olpc_data->moval / 100000) % 10];
        RT_ASSERT((yoffset + img_info->h) <= MSG_FB_H);
        if (((olpc_data->moval / 100000) % 10) != 0)
        {
            flag = 1;
            rt_display_img_fill(img_info, wincfg.fb, wincfg.w, xoffset, yoffset + 3);
            xoffset += img_info->w + 0;
        }
        img_info = msg_font_num[(olpc_data->moval / 10000) % 10];
        RT_ASSERT((yoffset + img_info->h) <= MSG_FB_H);
        if (((olpc_data->moval / 10000) != 0) || (flag == 1))
        {
            flag = 1;
            rt_display_img_fill(img_info, wincfg.fb, wincfg.w, xoffset, yoffset + 3);
            xoffset += img_info->w + 0;
        }
        img_info = msg_font_num[(olpc_data->moval / 1000) % 10];
        RT_ASSERT((yoffset + img_info->h) <= MSG_FB_H);
        if (((olpc_data->moval / 1000) != 0) || (flag == 1))
        {
            flag = 1;
            rt_display_img_fill(img_info, wincfg.fb, wincfg.w, xoffset, yoffset + 3);
            xoffset += img_info->w + 0;
        }
        img_info = msg_font_num[(olpc_data->moval / 100) % 10];
        RT_ASSERT((yoffset + img_info->h) <= MSG_FB_H);
        if (((olpc_data->moval / 100) != 0) || (flag == 1))
        {
            flag = 1;
            rt_display_img_fill(img_info, wincfg.fb, wincfg.w, xoffset, yoffset + 3);
            xoffset += img_info->w + 0;
        }
        img_info = msg_font_num[(olpc_data->moval / 10) % 10];
        RT_ASSERT((yoffset + img_info->h) <= MSG_FB_H);
        if (((olpc_data->moval / 10) != 0) || (flag == 1))
        {
            rt_display_img_fill(img_info, wincfg.fb, wincfg.w, xoffset, yoffset + 3);
            xoffset += img_info->w + 0;
        }
        img_info = msg_font_num[olpc_data->moval % 10];
        RT_ASSERT((yoffset + img_info->h) <= MSG_FB_H);
        rt_display_img_fill(img_info, wincfg.fb, wincfg.w, xoffset, yoffset + 3);
    }

    /* draw message: music & web & qq & wx */
    yoffset = yoffset_bak + 160;
    {
        /* music */
        xoffset = xoffset_bak + 106;
        img_info = msg_music_num[olpc_data->musicval];
        RT_ASSERT((yoffset + img_info->h) <= MSG_FB_H);
        rt_display_img_fill(img_info, wincfg.fb, wincfg.w, xoffset, yoffset);

        /* qq */
        xoffset += img_info->w + 20;
        img_info = msg_qq_num[olpc_data->qqval];
        RT_ASSERT((yoffset + img_info->h) <= MSG_FB_H);
        rt_display_img_fill(img_info, wincfg.fb, wincfg.w, xoffset, yoffset);

        /* web */
        xoffset += img_info->w + 20;
        img_info = msg_web_num[olpc_data->webval];
        RT_ASSERT((yoffset + img_info->h) <= MSG_FB_H);
        rt_display_img_fill(img_info, wincfg.fb, wincfg.w, xoffset, yoffset);

        /* wx */
        xoffset += img_info->w + 20;
        img_info = msg_wx_num[olpc_data->wexval];
        RT_ASSERT((yoffset + img_info->h) <= MSG_FB_H);
        rt_display_img_fill(img_info, wincfg.fb, wincfg.w, xoffset, yoffset);
    }

    //refresh screen
    ret = rt_display_win_layers_set(&wincfg);
    RT_ASSERT(ret == RT_EOK);

    return RT_EOK;
}

/**
 * Clock region refresh.
 */
static rt_err_t olpc_clock_home_region_refresh(struct olpc_clock_data *olpc_data)
{
    rt_err_t ret;
    rt_int16_t   xoffset, yoffset;
    rt_device_t  device = olpc_data->disp->device;
    image_info_t *img_info = NULL;
    struct rt_display_config wincfg;
    struct rt_device_graphic_info info;

    ret = rt_device_control(device, RTGRAPHIC_CTRL_GET_INFO, &info);
    RT_ASSERT(ret == RT_EOK);

    rt_display_sync_hook(device);

    rt_memset(&wincfg, 0, sizeof(struct rt_display_config));

    wincfg.winId = CLOCK_GRAY1_WIN;
    wincfg.fb    = olpc_data->fb;
    wincfg.w     = ((HOME_FB_W + 31) / 32) * 32;
    wincfg.h     = HOME_FB_H;
    wincfg.fblen = wincfg.w * wincfg.h / 8;
    wincfg.x     = HOME_REGION_X + (HOME_REGION_W - HOME_FB_W) / 2;
    wincfg.y     = HOME_REGION_Y + (HOME_REGION_H - HOME_FB_H) / 2;
    wincfg.ylast = wincfg.y;

    RT_ASSERT((wincfg.w % 4) == 0);
    RT_ASSERT((wincfg.h % 2) == 0);
    RT_ASSERT(wincfg.fblen <= olpc_data->fblen);

    rt_memset((void *)wincfg.fb, 0x00, wincfg.fblen);

    xoffset = 0;
    yoffset = 0;
    if (olpc_data->home_sta == 1)
    {
        /* home background */
        img_info = &home_backgroung_info;
        RT_ASSERT(img_info->w <= wincfg.w);
        RT_ASSERT(img_info->h <= wincfg.h);

        yoffset  += 0;
        xoffset  += (HOME_FB_W - img_info->w) / 2;
        rt_display_img_fill(img_info, wincfg.fb, wincfg.w, xoffset, yoffset);

        /* home arrow */
        img_info = &home_arrow1_info;
        rt_display_img_fill(img_info, wincfg.fb, wincfg.w, xoffset + img_info->x, yoffset + img_info->y);

        /* home lock */
        img_info = &home_lock1_info;
        rt_display_img_fill(img_info, wincfg.fb, wincfg.w, xoffset + img_info->x, yoffset + img_info->y);

        /* home ebook */
        img_info = home_item[olpc_data->home_id];
        if (img_info != NULL)
        {
            rt_display_img_fill(img_info, wincfg.fb, wincfg.w, xoffset + img_info->x, yoffset + img_info->y);
        }
    }

    //refresh screen
    ret = rt_display_win_layers_set(&wincfg);
    RT_ASSERT(ret == RT_EOK);

    return RT_EOK;
}

/**
 * Clock region refresh.
 */
static rt_err_t olpc_clock_fingerprint_region_refresh(struct olpc_clock_data *olpc_data)
{
    rt_err_t ret;
    rt_int16_t   xoffset, yoffset;
    rt_device_t  device = olpc_data->disp->device;
    image_info_t *img_info = NULL;
    struct rt_display_config wincfg;
    struct rt_device_graphic_info info;

    ret = rt_device_control(device, RTGRAPHIC_CTRL_GET_INFO, &info);
    RT_ASSERT(ret == RT_EOK);

    rt_display_sync_hook(device);

    rt_memset(&wincfg, 0, sizeof(struct rt_display_config));

    wincfg.winId = CLOCK_RGB332_WIN;
    wincfg.fb    = olpc_data->fb;
    wincfg.w     = ((FP_FB_W + 3) / 4) * 4;
    wincfg.h     = FP_FB_H;
    wincfg.fblen = wincfg.w * wincfg.h;
    wincfg.x     = FP_REGION_X + (FP_REGION_W - FP_FB_W) / 2;
    wincfg.y     = FP_REGION_Y + (FP_REGION_H - FP_FB_H) / 2;
    wincfg.ylast = wincfg.y;

    RT_ASSERT((wincfg.w % 4) == 0);
    RT_ASSERT((wincfg.h % 2) == 0);
    RT_ASSERT(wincfg.fblen <= olpc_data->fblen);

    rt_memset((void *)wincfg.fb, 0x00, wincfg.fblen);

    xoffset = 0;
    yoffset = 0;

    if (olpc_data->fp_sta == 1)
    {
        // draw fingerprint img
        img_info = fingerprint_item[olpc_data->fp_id];
        RT_ASSERT(img_info->w <= wincfg.w);
        RT_ASSERT(img_info->h <= wincfg.h);

        yoffset  += 0;
        xoffset  += (FP_FB_W - img_info->w) / 2;
        rt_display_img_fill(img_info, wincfg.fb, wincfg.w, xoffset, yoffset);
    }

    //refresh screen
    ret = rt_display_win_layers_set(&wincfg);
    RT_ASSERT(ret == RT_EOK);

    return RT_EOK;
}

/**
 * Display clock demo task function.
 */
static rt_err_t olpc_clock_task_fun(struct olpc_clock_data *olpc_data)
{
    rt_err_t ret;

    //rt_tick_t ticks = rt_tick_get();
    //rt_kprintf("clock ticks = %d\n", rt_tick_get() - ticks);

    //rt_kprintf("cmd = 0x%2x\n", olpc_data->cmd);
    if ((olpc_data->cmd & MOVE_CLOCK) == MOVE_CLOCK)
    {
        olpc_data->cmd &= ~MOVE_CLOCK;

        olpc_clock_clock_region_move(olpc_data);
    }
    /* else */if ((olpc_data->cmd & MOVE_MSG) == MOVE_MSG)
    {
        olpc_data->cmd &= ~MOVE_MSG;

        olpc_clock_msg_region_move(olpc_data);
    }

    if ((olpc_data->cmd & UPDATE_CLOCK) == UPDATE_CLOCK)
    {
        olpc_data->cmd &= ~UPDATE_CLOCK;

        ret = olpc_clock_clock_region_refresh(olpc_data);
        RT_ASSERT(ret == RT_EOK);
    }
    /* else */if ((olpc_data->cmd & UPDATE_MSG) == UPDATE_MSG)
    {
        olpc_data->cmd &= ~UPDATE_MSG;

        ret = olpc_clock_msg_region_refresh(olpc_data);
        RT_ASSERT(ret == RT_EOK);

    }
    /* else */if ((olpc_data->cmd & UPDATE_HOME) == UPDATE_HOME)
    {
        olpc_data->cmd &= ~UPDATE_HOME;

        ret = olpc_clock_home_region_refresh(olpc_data);
        RT_ASSERT(ret == RT_EOK);

    }
    /* else */if ((olpc_data->cmd & UPDATE_FINGERP) == UPDATE_FINGERP)
    {
        olpc_data->cmd &= ~UPDATE_FINGERP;

        ret = olpc_clock_fingerprint_region_refresh(olpc_data);
        RT_ASSERT(ret == RT_EOK);
    }

    if (olpc_data->cmd != 0)
    {
        rt_event_send(olpc_data->disp_event, EVENT_UPDATE_CLOCK);
    }

    return RT_EOK;
}

/*
 **************************************************************************************************
 *
 * olpc clock touch functions
 *
 **************************************************************************************************
 */
#if defined(RT_USING_TOUCH)
/**
 * Display clock demo task function.
 */

static rt_err_t olpc_clock_get_touch(struct olpc_clock_data *olpc_data)
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

    //rt_kprintf("size111 = %d, x = %d, y = %d, z = %d, width = %d, touch = %d, status = %d\n",
    //        rd_size, olpc_data->point.x, olpc_data->point.y, olpc_data->point.z, olpc_data->point.width_major,olpc_data->point.touch_major,olpc_data->point.status);

    if ((olpc_data->home_sta == 0) || (olpc_data->fp_sta == 0))
    {
        //screen on
        olpc_data->home_sta = 1;
        olpc_data->home_id  = 8;
        olpc_data->cmd |= UPDATE_HOME;
        rt_event_send(olpc_data->disp_event, EVENT_UPDATE_CLOCK);

        olpc_data->fp_sta = 1;
        olpc_data->fp_id  = 0;
        olpc_data->cmd |= UPDATE_FINGERP;
        rt_event_send(olpc_data->disp_event, EVENT_UPDATE_CLOCK);
    }
    else
    {
        //check home key
        x  = HOME_REGION_X + (HOME_REGION_W - HOME_FB_W) / 2;
        y  = HOME_REGION_Y + (HOME_REGION_H - HOME_FB_H) / 2;
        for (i = 0; i < 8; i++)
        {
            image_info_t *img_info = home_item[i];
            //rt_kprintf("home: x = %d, y = %d, w = %d, h = %d\n",x + img_info->x, y + img_info->y, img_info->w, img_info->h);
            if (((x + img_info->x) < olpc_data->point.x) && (olpc_data->point.x < (x + img_info->x + img_info->w)))
            {
                if (((y + img_info->y) < olpc_data->point.y) && (olpc_data->point.y < (y + img_info->y + img_info->h)))
                {
                    olpc_data->home_id  = i;
                    olpc_data->cmd |= UPDATE_HOME;
                    rt_event_send(olpc_data->disp_event, EVENT_UPDATE_CLOCK);
                }
            }
        }

        //check finger printf key
        if (olpc_data->fp_lpcnt == 0)
        {
            image_info_t *img_info = &fingerprint0_info;

            x  = FP_REGION_X + (FP_REGION_W - FP_FB_W) / 2 + (FP_FB_W - img_info->w) / 2;
            y  = FP_REGION_Y + (FP_REGION_H - FP_FB_H) / 2;

            //rt_kprintf("fp: x = %d, y = %d, w = %d, h = %d\n",x + img_info->x, y + img_info->y, img_info->w, img_info->h);

            if (((x + img_info->x) < olpc_data->point.x) && (olpc_data->point.x < (x + img_info->x + img_info->w)))
            {
                if (((y + img_info->y) < olpc_data->point.y) && (olpc_data->point.y < (y + img_info->y + img_info->h)))
                {
                    olpc_data->fp_id  = 0;
                    olpc_data->fp_lpcnt = 6;
                    olpc_data->cmd |= UPDATE_FINGERP;
                    rt_event_send(olpc_data->disp_event, EVENT_UPDATE_CLOCK);
                }
            }
        }
    }

    //reset timer
    olpc_data->home_timeout = HOME_HOLD_TIME;
    olpc_data->fp_timeout   = FP_HOLD_TIME;

    return RT_EOK;
}

#endif
/*
 **************************************************************************************************
 *
 * olpc clock demo init & thread
 *
 **************************************************************************************************
 */

/**
 * olpc clock dmeo thread.
 */
static void olpc_clock_thread(void *p)
{
    rt_err_t ret;
    uint32_t event;
    struct olpc_clock_data *olpc_data;
    struct rt_display_lut lut0, lut1;

    olpc_data = (struct olpc_clock_data *)rt_malloc(sizeof(struct olpc_clock_data));
    RT_ASSERT(olpc_data != RT_NULL);
    rt_memset((void *)olpc_data, 0, sizeof(struct olpc_clock_data));

    /* init bpp_lut[256] */
    rt_display_update_lut(FORMAT_RGB_332);

    lut0.winId = CLOCK_RGB332_WIN;
    lut0.format = RTGRAPHIC_PIXEL_FORMAT_RGB332;
    lut0.lut  = bpp_lut;
    lut0.size = sizeof(bpp_lut) / sizeof(bpp_lut[0]);

    lut1.winId = CLOCK_GRAY1_WIN;
    lut1.format = RTGRAPHIC_PIXEL_FORMAT_GRAY1;
    lut1.lut  = bpp1_lut;
    lut1.size = sizeof(bpp1_lut) / sizeof(bpp1_lut[0]);

    olpc_data->disp = rt_display_init(&lut0, &lut1, RT_NULL);
    RT_ASSERT(olpc_data->disp != RT_NULL);

#if defined(RT_USING_TOUCH)
    olpc_data->touch_dev = rt_device_find("s3706");
    RT_ASSERT(olpc_data->touch_dev != RT_NULL);
#endif

    olpc_data->disp_event = rt_event_create("display_event", RT_IPC_FLAG_FIFO);
    RT_ASSERT(olpc_data->disp_event != RT_NULL);

    ret = olpc_clock_init(olpc_data);
    RT_ASSERT(ret == RT_EOK);

    rt_event_send(olpc_data->disp_event, EVENT_UPDATE_CLOCK);

    while (1)
    {
        ret = rt_event_recv(olpc_data->disp_event, EVENT_UPDATE_CLOCK | EVENT_GET_TOUCH,
                            RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR,
                            RT_WAITING_FOREVER, &event);
        if (ret != RT_EOK)
        {
            /* Reserved... */
        }

#if defined(RT_USING_TOUCH)
        if (event & EVENT_GET_TOUCH)
        {
            ret = olpc_clock_get_touch(olpc_data);
            RT_ASSERT(ret == RT_EOK);
        }
#endif

        if (event & EVENT_UPDATE_CLOCK)
        {
            ret = olpc_clock_task_fun(olpc_data);
            RT_ASSERT(ret == RT_EOK);
        }
    }

    /* Thread deinit */
    olpc_clock_deinit(olpc_data);

    rt_event_delete(olpc_data->disp_event);

    rt_display_deinit(olpc_data->disp);

    rt_free(olpc_data);
}

/**
 * olpc clock demo application init.
 */
int olpc_clock_app_init(void)
{
    rt_thread_t rtt_clock, rtt_touch;

    rtt_clock = rt_thread_create("olpcclock", olpc_clock_thread, RT_NULL, 2048 * 4, 5, 10);
    RT_ASSERT(rtt_clock != RT_NULL);
    rt_thread_startup(rtt_clock);

#if defined(RT_USING_TOUCH)
    rtt_touch = rt_thread_create("touch", touch_thread_entry, RT_NULL, 1024, 10, 20);
    RT_ASSERT(rtt_touch != RT_NULL);
    rt_thread_startup(rtt_touch);
#endif

    return RT_EOK;
}

INIT_APP_EXPORT(olpc_clock_app_init);
#endif
