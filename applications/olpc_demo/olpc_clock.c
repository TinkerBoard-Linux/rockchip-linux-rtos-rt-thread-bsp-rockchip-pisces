#include <rtthread.h>
#if defined(RT_USING_OLPC_DEMO) && defined(OLPC_APP_CLOCK_ENABLE)

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
#define CLOCK_GRAY1_WIN     0
#define CLOCK_RGB332_WIN    1
#define CLOCK_RGB565_WIN    2

/* display fb size */
#define DISP_WIN_W          440
#if defined(OLPC_APP_CLOCK_STYLE_ROUND_ROMAN565)
#define DISP_WIN_H          (440*2)
#else
#define DISP_WIN_H          440
#endif

/* display region define */

#define LAMP_MAX_NUM         8
#define LAMP_HORIZONTAL_NUM  17
#define LAMP_VERTICAL_NUM    10
#define LAMP_HORIZONTAL_SIZE 34
#define LAMP_VERTICAL_SIZE   34
#define LAMP_HORIZONTAL_STEP 64
#define LAMP_VERTICAL_STEP   64
#define LAMP_HORIZONTAL_DIFF (LAMP_HORIZONTAL_STEP - LAMP_HORIZONTAL_SIZE)
#define LAMP_VERTICAL_DIFF   (LAMP_VERTICAL_STEP - LAMP_VERTICAL_SIZE)

#define LAMP_REGION_X       ((WIN_LAYERS_W - (LAMP_HORIZONTAL_NUM * LAMP_HORIZONTAL_STEP - LAMP_HORIZONTAL_DIFF)) / 2)
#define LAMP_REGION_Y       12
#define LAMP_W              (((LAMP_HORIZONTAL_SIZE + 3) / 4) * 4)
#define LAMP_H              (((LAMP_VERTICAL_SIZE + 3) / 4) * 4)
#define LAMP_FB_W           (((LAMP_MAX_NUM * LAMP_HORIZONTAL_STEP - LAMP_HORIZONTAL_DIFF + 3) / 4) * 4)
#define LAMP_FB_H           LAMP_H

#define CLOCK_REGION_X      (LAMP_REGION_X + LAMP_W)
#define CLOCK_REGION_Y      (LAMP_REGION_Y + LAMP_H)
#define CLOCK_REGION_W      (WIN_LAYERS_W - (CLOCK_REGION_X + LAMP_W) * 2)
#define CLOCK_REGION_H      (LAMP_VERTICAL_NUM * LAMP_VERTICAL_STEP - LAMP_VERTICAL_DIFF)
#define CLOCK_FB_W          440     /* clock frame buffer w */
#define CLOCK_FB_H          440     /* clock frame buffer h */
#define CLOCK_MOVE_XSTEP    (200)   /* clock X direction move step */
#define CLOCK_MOVE_YSTEP    (100)   /* clock Y direction move step */

#define MSG_REGION_X        0
#define MSG_REGION_Y        (CLOCK_REGION_Y + CLOCK_REGION_H + LAMP_VERTICAL_STEP * 2)
#define MSG_REGION_W        WIN_LAYERS_W
#define MSG_REGION_H        450
#define MSG_FB_W            440     /* message frame buffer w */
#define MSG_FB_H            300     /* message frame buffer h */
#define MSG_MOVE_XSTEP      (200)   /* message X direction move step */
#define MSG_MOVE_YSTEP      (50)    /* message Y direction move step */

#define HOME_REGION_X       0
#define HOME_REGION_Y       (MSG_REGION_Y + MSG_REGION_H)
#define HOME_REGION_W       WIN_LAYERS_W
#define HOME_REGION_H       720
#define HOME_FB_W           544     /* home frame buffer w */
#define HOME_FB_H           540     /* home frame buffer h */

#define FP_REGION_X         0
#define FP_REGION_Y         (HOME_REGION_Y + HOME_REGION_H)
#define FP_REGION_W         WIN_LAYERS_W
#define FP_REGION_H         190
#define FP_FB_W             160     /* fingerprint frame buffer w */
#define FP_FB_H             150     /* fingerprint frame buffer h */

#define LOCK_REGION_X       0
#define LOCK_REGION_Y       1800
#define LOCK_REGION_W       WIN_LAYERS_W
#define LOCK_REGION_H       162
#define LOCK_FB_W           800
#define LOCK_FB_H           162

/* Event define */
#define EVENT_UPDATE_CLOCK  (0x01UL << 0)

/* Command define */
#define UPDATE_CLOCK        (0x01UL << 0)
#define UPDATE_LAMP_U       (0x01UL << 1)
#define UPDATE_LAMP_R       (0x01UL << 2)
#define UPDATE_LAMP_D       (0x01UL << 3)
#define UPDATE_LAMP_L       (0x01UL << 4)
#define UPDATE_MSG          (0x01UL << 5)
#define UPDATE_HOME         (0x01UL << 6)
#define UPDATE_FINGERP      (0x01UL << 7)
#define UPDATE_LOCK         (0x01UL << 8)
#define MOVE_CLOCK          (0x01UL << 9)
#define MOVE_MSG            (0x01UL << 10)
#define MOVE_LAMP           (0x01UL << 11)

/* Screen state define */
#define SCREEN_OFF          0
#define SCREEN_LOCK         1
#define SCREEN_HOME         2

#define COLOR_DEPTH         8

#define CLOCK_UPDATE_TIME   (RT_TICK_PER_SECOND)
#define SCREEN_HOLD_TIME    (RT_TICK_PER_SECOND * 5)
#define FP_LOOP_TIME        (RT_TICK_PER_SECOND / 10)
#define LAMP_LOOP_TIME      (RT_TICK_PER_SECOND / 5)

/*
 **************************************************************************************************
 *
 * Declaration
 *
 **************************************************************************************************
 */
extern image_info_t lock_bar_info;
extern image_info_t lock_block_info;

extern image_info_t clock_bkg_info;
extern image_info_t clock_sec_info;
extern image_info_t clock_min_info;
extern image_info_t clock_hour_info;
#if defined(OLPC_APP_CLOCK_STYLE_ROUND_ROMAN332) || defined(OLPC_APP_CLOCK_STYLE_ROUND_ROMAN565)
extern image_info_t clock_centre_info;
#endif

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

#if defined(OLPC_APP_CLOCK_LOOP_LAMP)
extern image_info_t clock_lamp0_info;
extern image_info_t clock_lamp1_info;
extern image_info_t clock_lamp2_info;
extern image_info_t clock_lamp3_info;
extern image_info_t clock_lamp4_info;
extern image_info_t clock_lamp5_info;
extern image_info_t clock_lamp6_info;
extern image_info_t clock_lamp7_info;
#endif

#if defined(RT_USING_TOUCH)
static rt_err_t olpc_clock_screen_touch_register(void *parameter);
static rt_err_t olpc_clock_screen_touch_unregister(void *parameter);
static rt_err_t olpc_clock_home_touch_register(void *parameter);
static rt_err_t olpc_clock_home_touch_unregister(void *parameter);
static rt_err_t olpc_clock_fingerprint_touch_register(void *parameter);
static rt_err_t olpc_clock_fingerprint_touch_unregister(void *parameter);
static rt_err_t olpc_clock_lock_touch_register(void *parameter);
static rt_err_t olpc_clock_lock_touch_unregister(void *parameter);
static image_info_t screen_item;
#endif

#if defined(OLPC_APP_CLOCK_LOOP_LAMP)
static rt_err_t olpc_clock_lamp_init(void *parameter);
static rt_err_t olpc_clock_lamp_move(void *parameter);
static rt_err_t olpc_clock_lamp_refresh(void *parameter);
#endif

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

    rt_uint8_t *fb;
    rt_uint32_t fblen;

    rt_uint8_t *lampfb;
    rt_uint32_t lampfblen;
    rt_int16_t  lamp_ylast;

    rt_timer_t  clock_timer;
    rt_timer_t  src_timer;
    rt_timer_t  fp_timer;
    rt_timer_t  lamp_timer;

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
    rt_int8_t   clock_flag;

    rt_int16_t  msg_xoffset;
    rt_int16_t  msg_yoffset;
    rt_int16_t  msg_xdir;
    rt_int16_t  msg_ydir;
    rt_int16_t  msg_ylast;

    rt_uint8_t  fp_id;
    rt_uint8_t  home_id;

    rt_int16_t  lock_px;
    rt_int16_t  lock_py;

    rt_uint8_t  screen_sta;
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

#if defined(OLPC_APP_CLOCK_LOOP_LAMP)
#define LAMP_VALUE_NULL         0x7f
static image_info_t *clock_lamp[LAMP_MAX_NUM] =
{
    &clock_lamp0_info,
    &clock_lamp1_info,
    &clock_lamp2_info,
    &clock_lamp3_info,
    &clock_lamp4_info,
    &clock_lamp5_info,
    &clock_lamp6_info,
    &clock_lamp7_info
};

struct olpc_lamp_t
{
    rt_int8_t  up[LAMP_HORIZONTAL_NUM];
    rt_int8_t  right[LAMP_VERTICAL_NUM];
    rt_int8_t  down[LAMP_HORIZONTAL_NUM];
    rt_int8_t  left[LAMP_VERTICAL_NUM];
};
struct olpc_lamp_t lamp;
#endif

/*
 **************************************************************************************************
 *
 * Display clock demo functions
 *
 **************************************************************************************************
 */
/**
 * Clock timer callback.
 */
static void olpc_clock_timeout(void *parameter)
{
    struct olpc_clock_data *olpc_data = (struct olpc_clock_data *)parameter;

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
            }
        }

        if ((olpc_data->minute % 3) == 0)
        {
            olpc_data->cmd |= MOVE_CLOCK | UPDATE_CLOCK;
            olpc_data->cmd |= MOVE_MSG | UPDATE_MSG;
        }
    }

    olpc_data->clock_flag = 1;

#if defined(OLPC_APP_CLOCK_LOOP_LAMP)
    olpc_clock_lamp_refresh(parameter);
#endif

    olpc_data->cmd |= UPDATE_CLOCK;
    rt_event_send(olpc_data->disp_event, EVENT_UPDATE_CLOCK);
}

/**
 * Screen timeout timer callback.
 */
static void olpc_screen_timeout(void *parameter)
{
    struct olpc_clock_data *olpc_data = (struct olpc_clock_data *)parameter;

    if (olpc_data->screen_sta == SCREEN_HOME)
    {
        olpc_clock_home_touch_unregister(olpc_data);
        olpc_clock_fingerprint_touch_unregister(olpc_data);

        olpc_data->cmd |= UPDATE_HOME | UPDATE_FINGERP;
        rt_event_send(olpc_data->disp_event, EVENT_UPDATE_CLOCK);
    }
    else if (olpc_data->screen_sta == SCREEN_LOCK)
    {
        olpc_clock_lock_touch_unregister(olpc_data);

        olpc_data->cmd |= UPDATE_LOCK;
        rt_event_send(olpc_data->disp_event, EVENT_UPDATE_CLOCK);
    }

    olpc_data->screen_sta = SCREEN_OFF;
}

/**
 * Fingerprint refresh timer callback.
 */
static void olpc_fp_timeout(void *parameter)
{
    struct olpc_clock_data *olpc_data = (struct olpc_clock_data *)parameter;

    olpc_data->fp_id++;
    olpc_data->cmd |= UPDATE_FINGERP;
    rt_event_send(olpc_data->disp_event, EVENT_UPDATE_CLOCK);

    if (olpc_data->fp_id >= 6)
    {
        rt_timer_stop(olpc_data->fp_timer);
    }
}

#if defined(OLPC_APP_CLOCK_LOOP_LAMP)
/**
 * Fingerprint refresh timer callback.
 */
static void olpc_lamp_timeout(void *parameter)
{
    struct olpc_clock_data *olpc_data = (struct olpc_clock_data *)parameter;

    olpc_data->cmd |= MOVE_LAMP;
    rt_event_send(olpc_data->disp_event, EVENT_UPDATE_CLOCK);
}
#endif

/**
 * Display clock demo init.
 */
static rt_err_t olpc_clock_init(struct olpc_clock_data *olpc_data)
{
    rt_err_t    ret;
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

    olpc_data->home_id = 0;
    olpc_data->fp_id = 0;
    olpc_data->screen_sta = SCREEN_OFF;
    olpc_data->cmd = UPDATE_CLOCK | UPDATE_MSG;

    ret = rt_device_control(device, RTGRAPHIC_CTRL_GET_INFO, &info);
    RT_ASSERT(ret == RT_EOK);

#if defined(OLPC_APP_CLOCK_STYLE_ROUND_ROMAN565)
    olpc_data->lampfblen = LAMP_FB_W * LAMP_FB_H;
    olpc_data->lampfb    = (rt_uint8_t *)rt_malloc_large(olpc_data->lampfblen);
    RT_ASSERT(olpc_data->lampfb != RT_NULL);
#endif
    olpc_data->fblen = DISP_WIN_W * DISP_WIN_H;
    olpc_data->fb    = (rt_uint8_t *)rt_malloc_large(olpc_data->fblen);
    RT_ASSERT(olpc_data->fb != RT_NULL);

    rt_memset(&wincfg, 0, sizeof(struct rt_display_config));

    wincfg.winId = CLOCK_RGB332_WIN;
    wincfg.fb    = olpc_data->fb;
    wincfg.x     = 0;
    wincfg.y     = 0;
    wincfg.w     = 4;
    wincfg.h     = WIN_LAYERS_H;
    wincfg.fblen = wincfg.w * wincfg.h;

    RT_ASSERT((wincfg.w % 4) == 0);
    RT_ASSERT((wincfg.h % 2) == 0);
    RT_ASSERT((wincfg.fblen) <= olpc_data->fblen);

    rt_memset((void *)wincfg.fb, 0x00, wincfg.fblen);

    //refresh screen
    ret = rt_display_win_layers_set(&wincfg);
    RT_ASSERT(ret == RT_EOK);

    // create sreen touch timer
    olpc_data->src_timer = rt_timer_create("srctimer",
                                           olpc_screen_timeout,
                                           (void *)olpc_data,
                                           SCREEN_HOLD_TIME,
                                           RT_TIMER_FLAG_ONE_SHOT);
    RT_ASSERT(olpc_data->src_timer != RT_NULL);

    // create fp touch timer
    olpc_data->fp_timer = rt_timer_create("fptimer",
                                          olpc_fp_timeout,
                                          (void *)olpc_data,
                                          FP_LOOP_TIME,
                                          RT_TIMER_FLAG_PERIODIC);
    RT_ASSERT(olpc_data->fp_timer != RT_NULL);

#if defined(OLPC_APP_CLOCK_LOOP_LAMP)
    olpc_clock_lamp_init(olpc_data);
    // create lamp touch timer
    olpc_data->lamp_timer = rt_timer_create("lamptimer",
                                            olpc_lamp_timeout,
                                            (void *)olpc_data,
                                            LAMP_LOOP_TIME,
                                            RT_TIMER_FLAG_PERIODIC);
    RT_ASSERT(olpc_data->lamp_timer != RT_NULL);
    rt_timer_start(olpc_data->lamp_timer);
#endif
    // create clock timer
    olpc_data->clock_timer = rt_timer_create("clocktimer",
                             olpc_clock_timeout,
                             (void *)olpc_data,
                             CLOCK_UPDATE_TIME,
                             RT_TIMER_FLAG_PERIODIC);
    RT_ASSERT(olpc_data->clock_timer != RT_NULL);
    rt_timer_start(olpc_data->clock_timer);

    return RT_EOK;
}

/**
 * Display clock demo deinit.
 */
static void olpc_clock_deinit(struct olpc_clock_data *olpc_data)
{
    rt_err_t ret;

#if defined(OLPC_APP_CLOCK_LOOP_LAMP)
    rt_timer_stop(olpc_data->lamp_timer);
    ret = rt_timer_delete(olpc_data->lamp_timer);
    RT_ASSERT(ret == RT_EOK);
#endif

    rt_timer_stop(olpc_data->fp_timer);
    ret = rt_timer_delete(olpc_data->fp_timer);
    RT_ASSERT(ret == RT_EOK);

    rt_timer_stop(olpc_data->src_timer);
    ret = rt_timer_delete(olpc_data->src_timer);
    RT_ASSERT(ret == RT_EOK);

    ret = rt_timer_stop(olpc_data->clock_timer);
    RT_ASSERT(ret == RT_EOK);

    ret = rt_timer_delete(olpc_data->clock_timer);
    RT_ASSERT(ret == RT_EOK);

    rt_free_large((void *)olpc_data->fb);

#if defined(OLPC_APP_CLOCK_LOOP_LAMP)
    rt_free_large((void *)olpc_data->lampfb);
#endif
}

#if defined(OLPC_APP_CLOCK_LOOP_LAMP)
/**
 * lamp region refresh.
 */
static void olpc_clock_lamp_test(void)
{
    //test
    if (0)
    {
        rt_int16_t k;
        rt_kprintf("\n");
        for (k = 0; k < LAMP_HORIZONTAL_NUM; k++)
        {
            rt_kprintf(" %02x", (rt_int8_t)lamp.up[k]);
        }
        rt_kprintf("\n");

        for (k = 0; k < LAMP_VERTICAL_NUM; k++)
        {
            rt_kprintf(" %02x", (rt_int8_t)lamp.left[k]);
            rt_kprintf("                                             ");
            rt_kprintf(" %02x\n", (rt_int8_t)lamp.right[k]);
        }
        for (k = 0; k < LAMP_HORIZONTAL_NUM; k++)
        {
            rt_kprintf(" %02x", (rt_int8_t)lamp.down[k]);
        }
        rt_kprintf("\n");
    }
}

/**
 * lamp table init.
 */
static rt_err_t olpc_clock_lamp_init(void *parameter)
{
    rt_int16_t i;

    // up line
    for (i = 0; i < LAMP_HORIZONTAL_NUM; i++)
    {
        if (i < LAMP_MAX_NUM)
        {
            lamp.up[i] = i;
        }
        else
        {
            lamp.up[i] = LAMP_VALUE_NULL;
        }
    }

    // right line
    for (i = 0; i < LAMP_VERTICAL_NUM; i++)
    {
        if ((i + LAMP_HORIZONTAL_NUM) < LAMP_MAX_NUM)
        {
            lamp.right[i] = i;
        }
        else
        {
            lamp.right[i] = LAMP_VALUE_NULL;
        }
    }

    // down line
    for (i = 0; i < LAMP_HORIZONTAL_NUM; i++)
    {
        if ((i + LAMP_HORIZONTAL_NUM + LAMP_VERTICAL_NUM) < LAMP_MAX_NUM)
        {
            lamp.down[i] = i;
        }
        else
        {
            lamp.down[i] = LAMP_VALUE_NULL;
        }
    }

    // left line
    for (i = 0; i < LAMP_VERTICAL_NUM; i++)
    {
        if ((i + LAMP_HORIZONTAL_NUM + LAMP_VERTICAL_NUM + LAMP_HORIZONTAL_NUM) < LAMP_MAX_NUM)
        {
            lamp.left[i] = i;
        }
        else
        {
            lamp.left[i] = LAMP_VALUE_NULL;
        }
    }

    olpc_clock_lamp_test();

    return RT_EOK;
}

/**
 * lamp region refresh check.
 */
static rt_err_t olpc_clock_lamp_refresh(void *parameter)
{
    struct olpc_clock_data *olpc_data = (struct olpc_clock_data *)parameter;
    rt_int16_t i;

    // send msg
    olpc_data->cmd &= ~(UPDATE_LAMP_U | UPDATE_LAMP_R | UPDATE_LAMP_D | UPDATE_LAMP_L);

    for (i = 0; i < LAMP_HORIZONTAL_NUM; i++)
    {
        if (lamp.up[i] != LAMP_VALUE_NULL)
        {
            olpc_data->cmd |= UPDATE_LAMP_U;
            break;
        }
    }

    for (i = 0; i < LAMP_VERTICAL_NUM; i++)
    {
        if (lamp.right[i] != LAMP_VALUE_NULL)
        {
            olpc_data->cmd |= UPDATE_LAMP_R;
            break;
        }
    }

    for (i = 0; i < LAMP_HORIZONTAL_NUM; i++)
    {
        if (lamp.down[i] != LAMP_VALUE_NULL)
        {
            olpc_data->cmd |= UPDATE_LAMP_D;
            break;
        }
    }

    for (i = 0; i < LAMP_VERTICAL_NUM; i++)
    {
        if (lamp.left[i] != LAMP_VALUE_NULL)
        {
            olpc_data->cmd |= UPDATE_LAMP_L;
            break;
        }
    }

    return RT_EOK;
}

/**
 * lamp move.
 */
static rt_err_t olpc_clock_lamp_move(void *parameter)
{
    rt_int16_t i;
    rt_int8_t  temp = lamp.left[0];

    // left line
    for (i = 0; i < LAMP_VERTICAL_NUM - 1; i++)
    {
        lamp.left[i] = lamp.left[i + 1];
    }
    lamp.left[i] = lamp.down[0];

    // down line
    for (i = 0; i < LAMP_HORIZONTAL_NUM - 1; i++)
    {
        lamp.down[i] = lamp.down[i + 1];
    }
    lamp.down[i] = lamp.right[LAMP_VERTICAL_NUM - 1];

    // right line
    for (i = LAMP_VERTICAL_NUM - 1; i > 0 ; i--)
    {
        lamp.right[i] = lamp.right[i - 1];
    }
    lamp.right[i] = lamp.up[LAMP_HORIZONTAL_NUM - 1];

    // up line
    for (i = LAMP_HORIZONTAL_NUM - 1; i > 0 ; i--)
    {
        lamp.up[i] = lamp.up[i - 1];
    }
    lamp.up[i] = temp;

    olpc_clock_lamp_refresh(parameter);

    olpc_clock_lamp_test();

    return RT_EOK;
}

/**
 * lamp region overlay checkrefresh.
 */
static rt_err_t olpc_clock_lamp_overlay_check(rt_uint16_t y1, rt_uint16_t y2, rt_uint16_t yy1, rt_uint16_t yy2)
{
    if ((y2 <= yy1) || (y1 >= yy2))
    {
        return RT_EOK;
    }

    return RT_ERROR;
}

/**
 * lamp region top line refresh.
 */
static rt_err_t olpc_clock_lamp_top_refresh(struct olpc_clock_data *olpc_data,
        struct rt_display_config *wincfg)
{
    rt_err_t ret;
    rt_int16_t   i, len, startpos, endpos;
    rt_int16_t   xoffset, yoffset;
    rt_int8_t    lampup[LAMP_HORIZONTAL_NUM];
    image_info_t *img_info = NULL;
    rt_device_t  device = olpc_data->disp->device;
    struct rt_device_graphic_info info;

    ret = rt_device_control(device, RTGRAPHIC_CTRL_GET_INFO, &info);
    RT_ASSERT(ret == RT_EOK);

    rt_enter_critical();
    rt_memcpy(lampup, lamp.up, LAMP_HORIZONTAL_NUM);
    rt_exit_critical();

    startpos = 0;
    for (i = 0; i < LAMP_HORIZONTAL_NUM; i++)
    {
        if (lampup[i] != LAMP_VALUE_NULL)
        {
            break;
        }
        startpos ++;
    }
    endpos   = startpos;
    for (; i < LAMP_HORIZONTAL_NUM; i++)
    {
        if (lampup[i] == LAMP_VALUE_NULL)
        {
            break;
        }
        endpos ++;
    }
    len = endpos - startpos;
    RT_ASSERT(len != 0);
    RT_ASSERT(len <= LAMP_MAX_NUM);

    img_info = clock_lamp[0];
    wincfg->winId = CLOCK_RGB332_WIN;
    wincfg->fb    = olpc_data->lampfb;
    wincfg->x     = LAMP_REGION_X + startpos * LAMP_HORIZONTAL_STEP;
    wincfg->y     = LAMP_REGION_Y;
    wincfg->w     = (((len - 1) * LAMP_HORIZONTAL_STEP + img_info->w + 3) / 4) * 4;
    wincfg->h     = ((img_info->h + 1) / 2) * 2;
    wincfg->fblen = wincfg->w * wincfg->h;
    wincfg->ylast = wincfg->y;
    if (lampup[0] == 0)
    {
        wincfg->ylast = wincfg->y + LAMP_VERTICAL_STEP;
    }

    RT_ASSERT((wincfg->w % 4) == 0);
    RT_ASSERT((wincfg->y % 2) == 0);
    RT_ASSERT((wincfg->h % 2) == 0);
    RT_ASSERT(wincfg->fblen <= olpc_data->lampfblen);
    rt_memset(wincfg->fb, 0, wincfg->fblen);

    for (i = startpos; i < endpos; i ++)
    {
        img_info = clock_lamp[lampup[i]];

        xoffset = (i - startpos) * LAMP_HORIZONTAL_STEP;
        yoffset = 0;
        rt_display_img_fill(img_info, wincfg->fb, wincfg->w, xoffset, yoffset);
    }

    return RT_EOK;
}

/**
 * lamp region right line refresh.
 */
static rt_err_t olpc_clock_lamp_right_refresh(struct olpc_clock_data *olpc_data,
        struct rt_display_config *wincfg)
{
    rt_err_t ret;
    rt_int16_t   i, len, startpos, endpos;
    rt_int16_t   xoffset, yoffset;
    rt_int8_t    lampright[LAMP_VERTICAL_NUM];
    image_info_t *img_info = NULL;
    rt_device_t  device = olpc_data->disp->device;
    struct rt_device_graphic_info info;

    ret = rt_device_control(device, RTGRAPHIC_CTRL_GET_INFO, &info);
    RT_ASSERT(ret == RT_EOK);

    rt_enter_critical();
    rt_memcpy(lampright, lamp.right, LAMP_VERTICAL_NUM);
    rt_exit_critical();

    startpos = 0;
    for (i = 0; i < LAMP_VERTICAL_NUM; i++)
    {
        if (lampright[i] != LAMP_VALUE_NULL)
        {
            break;
        }
        startpos ++;
    }
    endpos   = startpos;
    for (; i < LAMP_VERTICAL_NUM; i++)
    {
        if (lampright[i] == LAMP_VALUE_NULL)
        {
            break;
        }
        endpos ++;
    }
    len = endpos - startpos;
    RT_ASSERT(len != 0);
    RT_ASSERT(len <= LAMP_MAX_NUM);

    img_info = clock_lamp[0];
    wincfg->winId = CLOCK_RGB332_WIN;
    wincfg->fb    = olpc_data->lampfb;
    wincfg->x     = LAMP_REGION_X + (LAMP_HORIZONTAL_NUM - 1) * LAMP_HORIZONTAL_STEP;
    wincfg->y     = LAMP_REGION_Y + startpos * LAMP_VERTICAL_STEP + LAMP_VERTICAL_STEP;
    wincfg->w     = ((img_info->w + 3) / 4) * 4;
    wincfg->h     = (((len - 1) * LAMP_VERTICAL_STEP + img_info->h + 1) / 2) * 2;
    wincfg->fblen = wincfg->w * wincfg->h;
    wincfg->ylast = wincfg->y;
    if (lampright[0] == 0)
    {
        wincfg->ylast = wincfg->y - LAMP_VERTICAL_STEP;
        olpc_data->lamp_ylast = wincfg->y;
    }
    else if (lampright[0] == LAMP_VALUE_NULL)
    {
        wincfg->ylast = olpc_data->lamp_ylast;
        olpc_data->lamp_ylast = wincfg->y;
    }

    RT_ASSERT((wincfg->w % 4) == 0);
    RT_ASSERT((wincfg->y % 2) == 0);
    RT_ASSERT((wincfg->h % 2) == 0);
    RT_ASSERT(wincfg->fblen <= olpc_data->lampfblen);
    rt_memset(wincfg->fb, 0, wincfg->fblen);

    for (i = startpos; i < endpos; i ++)
    {
        img_info = clock_lamp[lampright[i]];

        xoffset = 0;
        yoffset = (i - startpos) * LAMP_VERTICAL_STEP;
        rt_display_img_fill(img_info, wincfg->fb, wincfg->w, xoffset, yoffset);
    }

    return RT_EOK;
}

/**
 * lamp region bottom line refresh.
 */
static rt_err_t olpc_clock_lamp_bottom_refresh(struct olpc_clock_data *olpc_data,
        struct rt_display_config *wincfg)
{
    rt_err_t     ret;
    rt_int16_t   i, len, startpos, endpos;
    rt_int16_t   xoffset, yoffset;
    rt_int8_t    lampdown[LAMP_HORIZONTAL_NUM];
    image_info_t *img_info = NULL;
    rt_device_t  device = olpc_data->disp->device;
    struct rt_device_graphic_info info;

    ret = rt_device_control(device, RTGRAPHIC_CTRL_GET_INFO, &info);
    RT_ASSERT(ret == RT_EOK);

    rt_enter_critical();
    rt_memcpy(lampdown, lamp.down, LAMP_HORIZONTAL_NUM);
    rt_exit_critical();

    startpos = 0;
    for (i = 0; i < LAMP_HORIZONTAL_NUM; i++)
    {
        if (lampdown[i] != LAMP_VALUE_NULL)
        {
            break;
        }
        startpos ++;
    }
    endpos   = startpos;
    for (; i < LAMP_HORIZONTAL_NUM; i++)
    {
        if (lampdown[i] == LAMP_VALUE_NULL)
        {
            break;
        }
        endpos ++;
    }
    len = endpos - startpos;
    RT_ASSERT(len != 0);
    RT_ASSERT(len <= LAMP_MAX_NUM);

    img_info = clock_lamp[0];
    wincfg->winId = CLOCK_RGB332_WIN;
    wincfg->fb    = olpc_data->lampfb;
    wincfg->x     = LAMP_REGION_X + startpos * LAMP_HORIZONTAL_STEP;
    wincfg->y     = LAMP_REGION_Y + (LAMP_VERTICAL_NUM + 1) * LAMP_VERTICAL_STEP;
    wincfg->w     = (((len - 1) * LAMP_HORIZONTAL_STEP + img_info->w + 3) / 4) * 4;
    wincfg->h     = ((img_info->h + 1) / 2) * 2;
    wincfg->fblen = wincfg->w * wincfg->h;
    wincfg->ylast = wincfg->y;
    if (lampdown[LAMP_HORIZONTAL_NUM - 1] == 0)
    {
        wincfg->ylast = wincfg->y - LAMP_HORIZONTAL_STEP;
    }

    RT_ASSERT((wincfg->w % 4) == 0);
    RT_ASSERT((wincfg->y % 2) == 0);
    RT_ASSERT((wincfg->h % 2) == 0);
    RT_ASSERT(wincfg->fblen <= olpc_data->lampfblen);
    rt_memset(wincfg->fb, 0, wincfg->fblen);

    for (i = startpos; i < endpos; i ++)
    {
        img_info = clock_lamp[lampdown[i]];

        xoffset = (i - startpos) * LAMP_HORIZONTAL_STEP;
        yoffset = 0;
        rt_display_img_fill(img_info, wincfg->fb, wincfg->w, xoffset, yoffset);
    }

    return RT_EOK;
}

/**
 * lamp region left line refresh.
 */
static rt_err_t olpc_clock_lamp_left_refresh(struct olpc_clock_data *olpc_data,
        struct rt_display_config *wincfg)
{
    rt_err_t ret;
    rt_int16_t   i, len, startpos, endpos;
    rt_int16_t   xoffset, yoffset;
    rt_int8_t    lampleft[LAMP_VERTICAL_NUM];
    image_info_t *img_info = NULL;
    rt_device_t  device = olpc_data->disp->device;
    struct rt_device_graphic_info info;

    ret = rt_device_control(device, RTGRAPHIC_CTRL_GET_INFO, &info);
    RT_ASSERT(ret == RT_EOK);

    rt_enter_critical();
    rt_memcpy(lampleft, lamp.left, LAMP_VERTICAL_NUM);
    rt_exit_critical();

    startpos = 0;
    for (i = 0; i < LAMP_VERTICAL_NUM; i++)
    {
        if (lampleft[i] != LAMP_VALUE_NULL)
        {
            break;
        }
        startpos ++;
    }
    endpos   = startpos;
    for (; i < LAMP_VERTICAL_NUM; i++)
    {
        if (lampleft[i] == LAMP_VALUE_NULL)
        {
            break;
        }
        endpos ++;
    }
    len = endpos - startpos;
    RT_ASSERT(len != 0);
    RT_ASSERT(len <= LAMP_MAX_NUM);

    img_info = clock_lamp[0];
    wincfg->winId = CLOCK_RGB332_WIN;
    wincfg->fb    = olpc_data->lampfb;
    wincfg->x     = LAMP_REGION_X;
    wincfg->y     = LAMP_REGION_Y + startpos * LAMP_VERTICAL_STEP + LAMP_VERTICAL_STEP;
    wincfg->w     = ((img_info->w + 3) / 4) * 4;
    wincfg->h     = (((len - 1) * LAMP_VERTICAL_STEP + img_info->h + 1) / 2) * 2;
    wincfg->fblen = wincfg->w * wincfg->h;
    wincfg->ylast = wincfg->y;
    if (lampleft[LAMP_VERTICAL_NUM - 1] == 0)
    {
        wincfg->ylast = wincfg->y + LAMP_VERTICAL_STEP;
        olpc_data->lamp_ylast = wincfg->y;
    }
    else if (lampleft[LAMP_VERTICAL_NUM - 1] == LAMP_VALUE_NULL)
    {
        wincfg->ylast = olpc_data->lamp_ylast + LAMP_VERTICAL_STEP;
        olpc_data->lamp_ylast = wincfg->y;
    }

    RT_ASSERT((wincfg->w % 4) == 0);
    RT_ASSERT((wincfg->y % 2) == 0);
    RT_ASSERT((wincfg->h % 2) == 0);
    RT_ASSERT(wincfg->fblen <= olpc_data->lampfblen);
    rt_memset(wincfg->fb, 0, wincfg->fblen);

    for (i = startpos; i < endpos; i ++)
    {
        img_info = clock_lamp[lampleft[i]];

        xoffset = 0;
        yoffset = (i - startpos) * LAMP_VERTICAL_STEP;
        rt_display_img_fill(img_info, wincfg->fb, wincfg->w, xoffset, yoffset);
    }

    return RT_EOK;
}

#endif

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
static rt_err_t olpc_clock_clock_region_refresh(struct olpc_clock_data *olpc_data,
        struct rt_display_config *wincfg)
{
    rt_err_t ret;
    rt_int16_t   xoffset, yoffset;
    rt_device_t  device = olpc_data->disp->device;
    image_info_t *img_info = NULL;
    struct rt_device_graphic_info info;

    ret = rt_device_control(device, RTGRAPHIC_CTRL_GET_INFO, &info);
    RT_ASSERT(ret == RT_EOK);

#if defined(OLPC_APP_CLOCK_STYLE_ROUND_ROMAN565)
    wincfg->winId = CLOCK_RGB565_WIN;
#else
    wincfg->winId = CLOCK_RGB332_WIN;
#endif
    wincfg->fb    = olpc_data->fb;
    wincfg->w     = ((CLOCK_FB_W + 3) / 4) * 4;
    wincfg->h     = CLOCK_FB_H;
#if defined(OLPC_APP_CLOCK_STYLE_ROUND_ROMAN565)
    wincfg->fblen = wincfg->w * wincfg->h * 2;
#else
    wincfg->fblen = wincfg->w * wincfg->h;
#endif
    wincfg->x     = CLOCK_REGION_X + (CLOCK_REGION_W - CLOCK_FB_W) / 2 + olpc_data->clock_xoffset;
    wincfg->y     = CLOCK_REGION_Y + (CLOCK_REGION_H - CLOCK_FB_H) / 2 + olpc_data->clock_yoffset;
    wincfg->y     = (wincfg->y / 2) * 2;
    wincfg->ylast = olpc_data->clock_ylast;
    olpc_data->clock_ylast = wincfg->y;

    RT_ASSERT((wincfg->w % 4) == 0);
    RT_ASSERT((wincfg->y % 2) == 0);
    RT_ASSERT((wincfg->h % 2) == 0);
    RT_ASSERT(wincfg->fblen <= olpc_data->fblen);

    if (olpc_data->clock_flag)
    {
        olpc_data->clock_flag = 0;

        //draw background
        {
            xoffset = 0;
            yoffset = 0;
            img_info = &clock_bkg_info;

            rt_memset((void *)wincfg->fb, 0x00, wincfg->fblen);
            RT_ASSERT(img_info->w <= wincfg->w);
            RT_ASSERT(img_info->h <= wincfg->h);

            yoffset  += 0;
            xoffset  += (CLOCK_FB_W - img_info->w) / 2;
            rt_display_img_fill(img_info, wincfg->fb, wincfg->w, xoffset, yoffset);
        }

        // draw hour,min,sec
        {
            int32_t hour, angle;
            uint32_t background_w = wincfg->w;//img_info->w;

            xoffset += (img_info->w / 2);
            yoffset += (img_info->h / 2);

            //draw hour line
            img_info = &clock_hour_info;
            RT_ASSERT(img_info->w <= wincfg->w / 2);
            RT_ASSERT(img_info->h <= wincfg->h / 2);

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
#if defined(OLPC_APP_CLOCK_STYLE_ROUND_ROMAN565)
            rt_display_rotate_16bit((float)angle, img_info->w, img_info->h, (unsigned short *)img_info->data,
                                    (unsigned short *)((uint32_t)wincfg->fb + 2 * (yoffset * wincfg->w + xoffset)),
                                    background_w, 4, img_info->h / 2);
#elif defined(OLPC_APP_CLOCK_STYLE_ROUND_ROMAN332)
            rt_display_rotate_8bit((float)angle, img_info->w, img_info->h, img_info->data,
                                   (unsigned char *)((uint32_t)wincfg->fb + (yoffset * wincfg->w + xoffset)),
                                   background_w, 4, img_info->h / 2);
#else
            rt_display_rotate_8bit((float)angle, img_info->w, img_info->h, img_info->data,
                                   (unsigned char *)((uint32_t)wincfg->fb + yoffset * wincfg->w + xoffset),
                                   background_w, 16, img_info->h / 2);
#endif
            //draw min line
            img_info = &clock_min_info;
            RT_ASSERT(img_info->w <= wincfg->w / 2);
            RT_ASSERT(img_info->h <= wincfg->h / 2);

            angle = olpc_data->minute * (360 / 60);
            angle -= 90;
            if (angle < 0)
            {
                angle += 360;
            }
#if defined(OLPC_APP_CLOCK_STYLE_ROUND_ROMAN565)
            rt_display_rotate_16bit((float)angle, img_info->w, img_info->h, (unsigned short *)img_info->data,
                                    (unsigned short *)((uint32_t)wincfg->fb + 2 * (yoffset * wincfg->w + xoffset)),
                                    background_w, 4, img_info->h / 2);
#elif defined(OLPC_APP_CLOCK_STYLE_ROUND_ROMAN332)
            rt_display_rotate_8bit((float)angle, img_info->w, img_info->h, img_info->data,
                                   (unsigned char *)((uint32_t)wincfg->fb + (yoffset * wincfg->w + xoffset)),
                                   background_w, 4, img_info->h / 2);
#else
            rt_display_rotate_8bit((float)angle, img_info->w, img_info->h, img_info->data,
                                   (unsigned char *)((uint32_t)wincfg->fb + yoffset * wincfg->w + xoffset),
                                   background_w, 18, img_info->h / 2);
#endif
            //draw second line
            img_info = &clock_sec_info;
            RT_ASSERT(img_info->w <= wincfg->w / 2);
            RT_ASSERT(img_info->h <= wincfg->h / 2);

            angle = olpc_data->second * (360 / 60);
            angle -= 90;
            if (angle < 0)
            {
                angle += 360;
            }
#if defined(OLPC_APP_CLOCK_STYLE_ROUND_ROMAN565)
            rt_display_rotate_16bit((float)angle, img_info->w, img_info->h, (unsigned short *)img_info->data,
                                    (unsigned short *)((uint32_t)wincfg->fb + 2 * (yoffset * wincfg->w + xoffset)),
                                    background_w, 4, img_info->h / 2);
#elif defined(OLPC_APP_CLOCK_STYLE_ROUND_ROMAN332)
            rt_display_rotate_8bit((float)angle, img_info->w, img_info->h, img_info->data,
                                   (unsigned char *)((uint32_t)wincfg->fb + (yoffset * wincfg->w + xoffset)),
                                   background_w, 4, img_info->h / 2);
#else
            rt_display_rotate_8bit((float)angle, img_info->w, img_info->h, img_info->data,
                                   (unsigned char *)((uint32_t)wincfg->fb + yoffset * wincfg->w + xoffset),
                                   background_w, 20, img_info->h / 2);
#endif

#if defined(OLPC_APP_CLOCK_STYLE_ROUND_ROMAN332) || defined(OLPC_APP_CLOCK_STYLE_ROUND_ROMAN565)
            //draw centre
            img_info = &clock_centre_info;
            RT_ASSERT(img_info->w <= wincfg->w);
            RT_ASSERT(img_info->h <= wincfg->h);

            yoffset  -= img_info->h / 2;
            xoffset  -= img_info->w / 2;
            rt_display_img_fill(img_info, wincfg->fb, wincfg->w, xoffset, yoffset);
#endif
        }
    }

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
static rt_err_t olpc_clock_msg_region_refresh(struct olpc_clock_data *olpc_data,
        struct rt_display_config *wincfg)
{
    rt_err_t ret;
    rt_int16_t   xoffset, yoffset;
    rt_device_t  device = olpc_data->disp->device;
    image_info_t *img_info = NULL;
    struct rt_device_graphic_info info;

    ret = rt_device_control(device, RTGRAPHIC_CTRL_GET_INFO, &info);
    RT_ASSERT(ret == RT_EOK);

    wincfg->winId = CLOCK_RGB332_WIN;
    wincfg->fb    = olpc_data->fb;
    wincfg->w     = ((MSG_FB_W + 3) / 4) * 4;
    wincfg->h     = MSG_FB_H;
    wincfg->fblen = wincfg->w * wincfg->h;
    wincfg->x     = MSG_REGION_X + (MSG_REGION_W - MSG_FB_W) / 2 + olpc_data->msg_xoffset;
    wincfg->y     = MSG_REGION_Y + (MSG_REGION_H - MSG_FB_H) / 2 + olpc_data->msg_yoffset;
    wincfg->y     = (wincfg->y / 2) * 2;
    wincfg->ylast = olpc_data->msg_ylast;
    olpc_data->msg_ylast = wincfg->y;

    RT_ASSERT((wincfg->w % 4) == 0);
    RT_ASSERT((wincfg->y % 2) == 0);
    RT_ASSERT((wincfg->h % 2) == 0);
    RT_ASSERT(wincfg->fblen <= olpc_data->fblen);

    rt_memset((void *)wincfg->fb, 0x00, wincfg->fblen);

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
            rt_display_img_fill(img_info, wincfg->fb, wincfg->w, xoffset, yoffset);
        }
        xoffset  = xoffset + img_info->w + 0;
        img_info = msg_font_num[olpc_data->month % 10];
        RT_ASSERT((yoffset + img_info->h) <= MSG_FB_H);
        rt_display_img_fill(img_info, wincfg->fb, wincfg->w, xoffset, yoffset);

        /* month */
        xoffset  = xoffset + img_info->w + 0;
        img_info = &msg_font_CHN_month_info;
        RT_ASSERT((yoffset + img_info->h) <= MSG_FB_H);
        rt_display_img_fill(img_info, wincfg->fb, wincfg->w, xoffset, yoffset);

        /* day num */
        xoffset  = xoffset + img_info->w + 0;
        img_info = msg_font_num[(olpc_data->day / 10) % 10];
        RT_ASSERT((yoffset + img_info->h) <= MSG_FB_H);
        rt_display_img_fill(img_info, wincfg->fb, wincfg->w, xoffset, yoffset);

        xoffset  = xoffset + img_info->w + 0;
        img_info = msg_font_num[olpc_data->day % 10];
        rt_display_img_fill(img_info, wincfg->fb, wincfg->w, xoffset, yoffset);

        /* day */
        xoffset  = xoffset + img_info->w + 0;
        img_info = &msg_font_CHN_day_info;
        RT_ASSERT((yoffset + img_info->h) <= MSG_FB_H);
        rt_display_img_fill(img_info, wincfg->fb, wincfg->w, xoffset, yoffset);

        /* week */
        xoffset  = xoffset + img_info->w + 30;
        img_info = &msg_font_CN_week_info;
        RT_ASSERT((yoffset + img_info->h) <= MSG_FB_H);
        rt_display_img_fill(img_info, wincfg->fb, wincfg->w, xoffset, yoffset);

        /* week num */
        xoffset  = xoffset + img_info->w + 0;
        img_info = msg_week_num[olpc_data->week % 7];
        RT_ASSERT((yoffset + img_info->h) <= MSG_FB_H);
        rt_display_img_fill(img_info, wincfg->fb, wincfg->w, xoffset, yoffset);
    }

    /* draw battery & motion */
    yoffset = yoffset_bak + 80;
    {
        /* battary */
        xoffset = xoffset_bak + 48;
        img_info = msg_bat_num[olpc_data->batval / 20];
        RT_ASSERT((yoffset + img_info->h) <= MSG_FB_H);
        rt_display_img_fill(img_info, wincfg->fb, wincfg->w, xoffset, yoffset + 8);

        /* battary num */
        xoffset += img_info->w + 0;
        img_info = msg_font_num[(olpc_data->batval / 100) % 10];
        RT_ASSERT((yoffset + img_info->h) <= MSG_FB_H);
        if ((olpc_data->batval / 100) != 0)
        {
            rt_display_img_fill(img_info, wincfg->fb, wincfg->w, xoffset, yoffset + 3);
        }

        xoffset += img_info->w + 0;
        img_info = msg_font_num[(olpc_data->batval / 10) % 10];
        RT_ASSERT((yoffset + img_info->h) <= MSG_FB_H);
        if ((olpc_data->batval / 10) != 0)
        {
            rt_display_img_fill(img_info, wincfg->fb, wincfg->w, xoffset, yoffset + 3);
        }

        xoffset += img_info->w + 0;
        img_info = msg_font_num[olpc_data->batval % 10];
        RT_ASSERT((yoffset + img_info->h) <= MSG_FB_H);
        rt_display_img_fill(img_info, wincfg->fb, wincfg->w, xoffset, yoffset + 3);

        xoffset += img_info->w;
        img_info = &msg_font_percent_info;
        RT_ASSERT((yoffset + img_info->h) <= MSG_FB_H);
        rt_display_img_fill(img_info, wincfg->fb, wincfg->w, xoffset, yoffset + 3);

        /* motion */
        xoffset += img_info->w + 30;
        img_info = &msg_mov3_info;
        RT_ASSERT((yoffset + img_info->h) <= MSG_FB_H);
        rt_display_img_fill(img_info, wincfg->fb, wincfg->w, xoffset, yoffset + 0);

        /* motion num */
        uint8_t flag = 0;
        xoffset += img_info->w + 0;
        img_info = msg_font_num[(olpc_data->moval / 100000) % 10];
        RT_ASSERT((yoffset + img_info->h) <= MSG_FB_H);
        if (((olpc_data->moval / 100000) % 10) != 0)
        {
            flag = 1;
            rt_display_img_fill(img_info, wincfg->fb, wincfg->w, xoffset, yoffset + 3);
            xoffset += img_info->w + 0;
        }
        img_info = msg_font_num[(olpc_data->moval / 10000) % 10];
        RT_ASSERT((yoffset + img_info->h) <= MSG_FB_H);
        if (((olpc_data->moval / 10000) != 0) || (flag == 1))
        {
            flag = 1;
            rt_display_img_fill(img_info, wincfg->fb, wincfg->w, xoffset, yoffset + 3);
            xoffset += img_info->w + 0;
        }
        img_info = msg_font_num[(olpc_data->moval / 1000) % 10];
        RT_ASSERT((yoffset + img_info->h) <= MSG_FB_H);
        if (((olpc_data->moval / 1000) != 0) || (flag == 1))
        {
            flag = 1;
            rt_display_img_fill(img_info, wincfg->fb, wincfg->w, xoffset, yoffset + 3);
            xoffset += img_info->w + 0;
        }
        img_info = msg_font_num[(olpc_data->moval / 100) % 10];
        RT_ASSERT((yoffset + img_info->h) <= MSG_FB_H);
        if (((olpc_data->moval / 100) != 0) || (flag == 1))
        {
            flag = 1;
            rt_display_img_fill(img_info, wincfg->fb, wincfg->w, xoffset, yoffset + 3);
            xoffset += img_info->w + 0;
        }
        img_info = msg_font_num[(olpc_data->moval / 10) % 10];
        RT_ASSERT((yoffset + img_info->h) <= MSG_FB_H);
        if (((olpc_data->moval / 10) != 0) || (flag == 1))
        {
            rt_display_img_fill(img_info, wincfg->fb, wincfg->w, xoffset, yoffset + 3);
            xoffset += img_info->w + 0;
        }
        img_info = msg_font_num[olpc_data->moval % 10];
        RT_ASSERT((yoffset + img_info->h) <= MSG_FB_H);
        rt_display_img_fill(img_info, wincfg->fb, wincfg->w, xoffset, yoffset + 3);
    }

    /* draw message: music & web & qq & wx */
    yoffset = yoffset_bak + 160;
    {
        /* music */
        xoffset = xoffset_bak + 106;
        img_info = msg_music_num[olpc_data->musicval];
        RT_ASSERT((yoffset + img_info->h) <= MSG_FB_H);
        rt_display_img_fill(img_info, wincfg->fb, wincfg->w, xoffset, yoffset);

        /* qq */
        xoffset += img_info->w + 20;
        img_info = msg_qq_num[olpc_data->qqval];
        RT_ASSERT((yoffset + img_info->h) <= MSG_FB_H);
        rt_display_img_fill(img_info, wincfg->fb, wincfg->w, xoffset, yoffset);

        /* web */
        xoffset += img_info->w + 20;
        img_info = msg_web_num[olpc_data->webval];
        RT_ASSERT((yoffset + img_info->h) <= MSG_FB_H);
        rt_display_img_fill(img_info, wincfg->fb, wincfg->w, xoffset, yoffset);

        /* wx */
        xoffset += img_info->w + 20;
        img_info = msg_wx_num[olpc_data->wexval];
        RT_ASSERT((yoffset + img_info->h) <= MSG_FB_H);
        rt_display_img_fill(img_info, wincfg->fb, wincfg->w, xoffset, yoffset);
    }

    return RT_EOK;
}

/**
 * Clock region refresh.
 */
static rt_err_t olpc_clock_home_region_refresh(struct olpc_clock_data *olpc_data,
        struct rt_display_config *wincfg)
{
    rt_err_t ret;
    rt_int16_t   xoffset, yoffset;
    rt_device_t  device = olpc_data->disp->device;
    image_info_t *img_info = NULL;
    struct rt_device_graphic_info info;

    ret = rt_device_control(device, RTGRAPHIC_CTRL_GET_INFO, &info);
    RT_ASSERT(ret == RT_EOK);

    wincfg->winId = CLOCK_GRAY1_WIN;
    wincfg->fb    = olpc_data->fb;
    wincfg->w     = ((HOME_FB_W + 31) / 32) * 32;
    wincfg->h     = HOME_FB_H;
    wincfg->fblen = wincfg->w * wincfg->h / 8;
    wincfg->x     = HOME_REGION_X + (HOME_REGION_W - HOME_FB_W) / 2;
    wincfg->y     = HOME_REGION_Y + (HOME_REGION_H - HOME_FB_H) / 2;
    wincfg->y     = (wincfg->y / 2) * 2;
    wincfg->ylast = wincfg->y;

    RT_ASSERT((wincfg->w % 4) == 0);
    RT_ASSERT((wincfg->y % 2) == 0);
    RT_ASSERT((wincfg->h % 2) == 0);
    RT_ASSERT(wincfg->fblen <= olpc_data->fblen);

    rt_memset((void *)wincfg->fb, 0x00, wincfg->fblen);

    xoffset = 0;
    yoffset = 0;
    if (olpc_data->screen_sta == SCREEN_HOME)
    {
        /* home background */
        img_info = &home_backgroung_info;
        RT_ASSERT(img_info->w <= wincfg->w);
        RT_ASSERT(img_info->h <= wincfg->h);

        yoffset  += 0;
        xoffset  += (HOME_FB_W - img_info->w) / 2;
        rt_display_img_fill(img_info, wincfg->fb, wincfg->w, xoffset, yoffset);

        /* home arrow */
        img_info = &home_arrow1_info;
        rt_display_img_fill(img_info, wincfg->fb, wincfg->w, xoffset + img_info->x, yoffset + img_info->y);

        /* home lock */
        img_info = &home_lock1_info;
        rt_display_img_fill(img_info, wincfg->fb, wincfg->w, xoffset + img_info->x, yoffset + img_info->y);

        /* home ebook */
        img_info = home_item[olpc_data->home_id];
        if (img_info != NULL)
        {
            rt_display_img_fill(img_info, wincfg->fb, wincfg->w, xoffset + img_info->x, yoffset + img_info->y);
        }
    }

    return RT_EOK;
}

/**
 * Clock region refresh.
 */
static rt_err_t olpc_clock_fingerprint_region_refresh(struct olpc_clock_data *olpc_data,
        struct rt_display_config *wincfg)
{
    rt_err_t ret;
    rt_int16_t   xoffset, yoffset;
    rt_device_t  device = olpc_data->disp->device;
    image_info_t *img_info = NULL;
    struct rt_device_graphic_info info;

    ret = rt_device_control(device, RTGRAPHIC_CTRL_GET_INFO, &info);
    RT_ASSERT(ret == RT_EOK);

    wincfg->winId = CLOCK_RGB332_WIN;
    wincfg->fb    = olpc_data->fb;
    wincfg->w     = ((FP_FB_W + 3) / 4) * 4;
    wincfg->h     = FP_FB_H;
    wincfg->fblen = wincfg->w * wincfg->h;
    wincfg->x     = FP_REGION_X + (FP_REGION_W - FP_FB_W) / 2;
    wincfg->y     = FP_REGION_Y + (FP_REGION_H - FP_FB_H) / 2;
    wincfg->y     = (wincfg->y / 2) * 2;
    wincfg->ylast = wincfg->y;

    RT_ASSERT((wincfg->w % 4) == 0);
    RT_ASSERT((wincfg->h % 2) == 0);
    RT_ASSERT(wincfg->fblen <= olpc_data->fblen);

    rt_memset((void *)wincfg->fb, 0x00, wincfg->fblen);

    xoffset = 0;
    yoffset = 0;

    if (olpc_data->screen_sta == SCREEN_HOME)
    {
        // draw fingerprint img
        img_info = fingerprint_item[olpc_data->fp_id];
        RT_ASSERT(img_info->w <= wincfg->w);
        RT_ASSERT(img_info->h <= wincfg->h);

        yoffset  += 0;
        xoffset  += (FP_FB_W - img_info->w) / 2;
        rt_display_img_fill(img_info, wincfg->fb, wincfg->w, xoffset, yoffset);
    }

    return RT_EOK;
}

/**
 * Clock region refresh.
 */
static rt_uint8_t unlock_flag = 0;
static rt_err_t olpc_clock_lock_region_refresh(struct olpc_clock_data *olpc_data,
        struct rt_display_config *wincfg)
{
    rt_err_t ret;
    rt_int16_t   xoffset, yoffset;
    rt_device_t  device = olpc_data->disp->device;
    image_info_t *img_info = NULL;
    struct rt_device_graphic_info info;

    ret = rt_device_control(device, RTGRAPHIC_CTRL_GET_INFO, &info);
    RT_ASSERT(ret == RT_EOK);

    wincfg->winId = CLOCK_GRAY1_WIN;
    wincfg->fb    = olpc_data->fb;
    wincfg->w     = ((LOCK_FB_W + 31) / 32) * 32;
    wincfg->h     = LOCK_FB_H;
    wincfg->fblen = wincfg->w * wincfg->h / 8;
    wincfg->x     = LOCK_REGION_X + (LOCK_REGION_W - LOCK_FB_W) / 2;
    wincfg->y     = LOCK_REGION_Y + (LOCK_REGION_H - LOCK_FB_H) / 2;
    wincfg->y     = (wincfg->y / 2) * 2;
    wincfg->ylast = wincfg->y;

    RT_ASSERT((wincfg->w % 4) == 0);
    RT_ASSERT((wincfg->y % 2) == 0);
    RT_ASSERT((wincfg->h % 2) == 0);
    RT_ASSERT(wincfg->fblen <= olpc_data->fblen);

    rt_memset((void *)wincfg->fb, 0x00, wincfg->fblen);

    xoffset = 0;
    yoffset = 0;

    if (olpc_data->screen_sta == SCREEN_LOCK)
    {
        if (unlock_flag == 0)
        {
            /* lock bar */
            img_info = &lock_bar_info;
            RT_ASSERT(img_info->w <= wincfg->w);
            RT_ASSERT(img_info->h <= wincfg->h);

            yoffset  += 0;
            xoffset  += (wincfg->w - img_info->w) / 2;
            rt_display_img_fill(img_info, wincfg->fb, wincfg->w, xoffset, yoffset);

            /* lock block */
            img_info = &lock_block_info;
            rt_int16_t xoff = (olpc_data->lock_px - (wincfg->x + xoffset + img_info->x));
            if (xoff < 0)
            {
                xoff = 0;
            }
            if (xoff > (wincfg->w - img_info->w - img_info->x - 8))
            {
                xoff = wincfg->w - img_info->w - img_info->x - 8;
                unlock_flag = 1;
            }
            xoffset += xoff;
            rt_display_img_fill(img_info, wincfg->fb, wincfg->w, xoffset + img_info->x, yoffset + img_info->y);
        }
        else
        {
            unlock_flag = 0;
            rt_memset((void *)wincfg->fb, 0x00, wincfg->fblen);
#if defined(RT_USING_TOUCH)
            olpc_clock_lock_touch_unregister(olpc_data);
            olpc_clock_home_touch_register(olpc_data);
            olpc_clock_fingerprint_touch_register(olpc_data);
#endif
            olpc_data->home_id  = 8;
            olpc_data->fp_id    = 0;
            olpc_data->screen_sta = SCREEN_HOME;
            olpc_data->cmd = UPDATE_HOME | UPDATE_FINGERP;
            rt_event_send(olpc_data->disp_event, EVENT_UPDATE_CLOCK);
        }
    }

    return RT_EOK;
}

/**
 * Display clock demo task function.
 */
static rt_err_t olpc_clock_task_fun(struct olpc_clock_data *olpc_data)
{
    rt_err_t ret;
    struct rt_display_config  wincfg, wincfg1;
    struct rt_display_config *winhead = RT_NULL;

    //rt_tick_t ticks = rt_tick_get();

    rt_memset(&wincfg, 0, sizeof(struct rt_display_config));
    rt_memset(&wincfg1, 0, sizeof(struct rt_display_config));

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
#if defined(OLPC_APP_CLOCK_LOOP_LAMP)
    /* else */if ((olpc_data->cmd & MOVE_LAMP) == MOVE_LAMP)
    {
        olpc_data->cmd &= ~MOVE_LAMP;

        olpc_clock_lamp_move(olpc_data);
    }
#endif

    // draw msg & home & fp & lamp
    if ((olpc_data->cmd & UPDATE_MSG) == UPDATE_MSG)
    {
        olpc_data->cmd &= ~UPDATE_MSG;
        olpc_data->clock_flag = 1;

        ret = olpc_clock_msg_region_refresh(olpc_data, &wincfg);
        RT_ASSERT(ret == RT_EOK);
    }
    else if ((olpc_data->cmd & UPDATE_HOME) == UPDATE_HOME)
    {
        olpc_data->cmd &= ~UPDATE_HOME;
        olpc_data->clock_flag = 1;

        ret = olpc_clock_home_region_refresh(olpc_data, &wincfg);
        RT_ASSERT(ret == RT_EOK);
    }
    else if ((olpc_data->cmd & UPDATE_FINGERP) == UPDATE_FINGERP)
    {
        olpc_data->cmd &= ~UPDATE_FINGERP;
        olpc_data->clock_flag = 1;

        ret = olpc_clock_fingerprint_region_refresh(olpc_data, &wincfg);
        RT_ASSERT(ret == RT_EOK);
    }
    else if ((olpc_data->cmd & UPDATE_LOCK) == UPDATE_LOCK)
    {
        olpc_data->cmd &= ~UPDATE_LOCK;
        olpc_data->clock_flag = 1;

        ret = olpc_clock_lock_region_refresh(olpc_data, &wincfg);
        RT_ASSERT(ret == RT_EOK);
    }
#if defined(OLPC_APP_CLOCK_LOOP_LAMP)
    // draw lamp
    else if ((olpc_data->cmd & UPDATE_LAMP_U) == UPDATE_LAMP_U)
    {
        olpc_data->cmd &= ~UPDATE_LAMP_U;

        ret = olpc_clock_lamp_top_refresh(olpc_data, &wincfg1);
        RT_ASSERT(ret == RT_EOK);

        ret = olpc_clock_lamp_overlay_check(MIN(wincfg1.y, wincfg1.ylast),
                                            MAX(wincfg1.y, wincfg1.ylast) + wincfg1.h,
                                            MIN(CLOCK_REGION_Y + (CLOCK_REGION_H - CLOCK_FB_H) / 2 + olpc_data->clock_yoffset, olpc_data->clock_ylast),
                                            MAX(CLOCK_REGION_Y + (CLOCK_REGION_H - CLOCK_FB_H) / 2 + olpc_data->clock_yoffset, olpc_data->clock_ylast) + CLOCK_FB_H);
        if (ret != RT_EOK)
        {
            olpc_data->cmd |= UPDATE_CLOCK;
        }
    }
    else if ((olpc_data->cmd & UPDATE_LAMP_R) == UPDATE_LAMP_R)
    {
        olpc_data->cmd &= ~UPDATE_LAMP_R;

        ret = olpc_clock_lamp_right_refresh(olpc_data, &wincfg1);
        RT_ASSERT(ret == RT_EOK);

        ret = olpc_clock_lamp_overlay_check(MIN(wincfg1.y, wincfg1.ylast),
                                            MAX(wincfg1.y, wincfg1.ylast) + wincfg1.h,
                                            MIN(CLOCK_REGION_Y + (CLOCK_REGION_H - CLOCK_FB_H) / 2 + olpc_data->clock_yoffset, olpc_data->clock_ylast),
                                            MAX(CLOCK_REGION_Y + (CLOCK_REGION_H - CLOCK_FB_H) / 2 + olpc_data->clock_yoffset, olpc_data->clock_ylast) + CLOCK_FB_H);
        if (ret != RT_EOK)
        {
            olpc_data->cmd |= UPDATE_CLOCK;
        }
    }
    else if ((olpc_data->cmd & UPDATE_LAMP_D) == UPDATE_LAMP_D)
    {
        olpc_data->cmd &= ~UPDATE_LAMP_D;

        ret = olpc_clock_lamp_bottom_refresh(olpc_data, &wincfg1);
        RT_ASSERT(ret == RT_EOK);

        ret = olpc_clock_lamp_overlay_check(MIN(wincfg1.y, wincfg1.ylast),
                                            MAX(wincfg1.y, wincfg1.ylast) + wincfg1.h,
                                            MIN(CLOCK_REGION_Y + (CLOCK_REGION_H - CLOCK_FB_H) / 2 + olpc_data->clock_yoffset, olpc_data->clock_ylast),
                                            MAX(CLOCK_REGION_Y + (CLOCK_REGION_H - CLOCK_FB_H) / 2 + olpc_data->clock_yoffset, olpc_data->clock_ylast) + CLOCK_FB_H);
        if (ret != RT_EOK)
        {
            olpc_data->cmd |= UPDATE_CLOCK;
        }
    }
    else if ((olpc_data->cmd & UPDATE_LAMP_L) == UPDATE_LAMP_L)
    {
        olpc_data->cmd &= ~UPDATE_LAMP_L;

        ret = olpc_clock_lamp_left_refresh(olpc_data, &wincfg1);
        RT_ASSERT(ret == RT_EOK);

        ret = olpc_clock_lamp_overlay_check(MIN(wincfg1.y, wincfg1.ylast),
                                            MAX(wincfg1.y, wincfg1.ylast) + wincfg1.h,
                                            MIN(CLOCK_REGION_Y + (CLOCK_REGION_H - CLOCK_FB_H) / 2 + olpc_data->clock_yoffset, olpc_data->clock_ylast),
                                            MAX(CLOCK_REGION_Y + (CLOCK_REGION_H - CLOCK_FB_H) / 2 + olpc_data->clock_yoffset, olpc_data->clock_ylast) + CLOCK_FB_H);
        if (ret != RT_EOK)
        {
            olpc_data->cmd |= UPDATE_CLOCK;
        }
    }
#endif

    // draw clock
    if (wincfg.fb == 0)
    {
        if ((olpc_data->cmd & UPDATE_CLOCK) == UPDATE_CLOCK)
        {
            olpc_data->cmd &= ~UPDATE_CLOCK;

            ret = olpc_clock_clock_region_refresh(olpc_data, &wincfg);
            RT_ASSERT(ret == RT_EOK);
        }
    }

    //refresh screen
    if (wincfg.fb != 0)
    {
        rt_display_win_layers_list(&winhead, &wincfg);
    }
    if (wincfg1.fb != 0)
    {
        rt_display_win_layers_list(&winhead, &wincfg1);
    }
    if (winhead != RT_NULL)
    {
        ret = rt_display_win_layers_set(winhead);
        RT_ASSERT(ret == RT_EOK);
    }

    if (olpc_data->cmd != 0)
    {
        rt_event_send(olpc_data->disp_event, EVENT_UPDATE_CLOCK);
    }

    //rt_kprintf("clock ticks = %d\n", rt_tick_get() - ticks);

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
 * screen touch.
 */
static rt_err_t olpc_clock_screen_touch_callback(rt_int32_t touch_id, enum olpc_touch_event event, struct point_info *point, void *parameter)
{
    rt_err_t ret = RT_ERROR;
    struct olpc_clock_data *olpc_data = (struct olpc_clock_data *)parameter;

    switch (event)
    {
    case TOUCH_EVENT_SHORT_DOWN:
        if (olpc_data->screen_sta == SCREEN_OFF)
        {
            olpc_data->screen_sta = SCREEN_LOCK;

            olpc_clock_lock_touch_register(parameter);

            image_info_t *img = &lock_block_info;
            olpc_data->lock_px = img->x_scr;
            olpc_data->lock_py = img->y_scr;
            olpc_data->cmd |= UPDATE_LOCK;
            rt_event_send(olpc_data->disp_event, EVENT_UPDATE_CLOCK);


            ret = RT_EOK;
        }
        break;

    default:
        break;
    }

    rt_timer_start(olpc_data->src_timer);   // start & restart timer

    return ret;
}

static rt_err_t olpc_clock_screen_touch_register(void *parameter)
{
    struct olpc_clock_data *olpc_data = (struct olpc_clock_data *)parameter;
    struct rt_device_graphic_info info;

    rt_memcpy(&info, &olpc_data->disp->info, sizeof(struct rt_device_graphic_info));

    /* screen on button key register */
    {
        screen_item.w = WIN_LAYERS_W;
        screen_item.h = WIN_LAYERS_H;
        register_touch_item((struct olpc_touch_item *)(&screen_item.touch_item), (void *)olpc_clock_screen_touch_callback, (void *)olpc_data, 0);
        update_item_coord((struct olpc_touch_item *)(&screen_item.touch_item), 0, 0, 0, 0);
    }

    return RT_EOK;
}

static rt_err_t olpc_clock_screen_touch_unregister(void *parameter)
{
    image_info_t *img_info = &screen_item;

    unregister_touch_item((struct olpc_touch_item *)(&img_info->touch_item));

    return RT_EOK;
}

/**
 * home item touch.
 */
static rt_err_t olpc_clock_home_touch_callback(rt_int32_t touch_id, enum olpc_touch_event event, struct point_info *point, void *parameter)
{
    rt_err_t ret = RT_ERROR;
    struct olpc_clock_data *olpc_data = (struct olpc_clock_data *)parameter;

    switch (event)
    {
    case TOUCH_EVENT_SHORT_DOWN:
        olpc_data->home_id = touch_id;
        olpc_data->cmd |= UPDATE_HOME;
        rt_event_send(olpc_data->disp_event, EVENT_UPDATE_CLOCK);
        ret = RT_EOK;
        break;

    default:
        break;
    }

    return ret;
}

static rt_err_t olpc_clock_home_touch_register(void *parameter)
{
    rt_int16_t   i, x, y;
    struct olpc_clock_data *olpc_data = (struct olpc_clock_data *)parameter;
    struct rt_device_graphic_info info;

    rt_memcpy(&info, &olpc_data->disp->info, sizeof(struct rt_device_graphic_info));

    /* home button key register */
    {
        x  = HOME_REGION_X + (HOME_REGION_W - HOME_FB_W) / 2;
        y  = HOME_REGION_Y + (HOME_REGION_H - HOME_FB_H) / 2;
        for (i = 0; i < 8; i++)
        {
            image_info_t *img_info = home_item[i];
            register_touch_item((struct olpc_touch_item *)(&img_info->touch_item), (void *)olpc_clock_home_touch_callback, (void *)olpc_data, i);
            update_item_coord((struct olpc_touch_item *)(&img_info->touch_item), x, y, home_item[i]->x, home_item[i]->y);
        }
    }

    return RT_EOK;
}

static rt_err_t olpc_clock_home_touch_unregister(void *parameter)
{
    rt_int16_t   i;

    /* home button key register */
    {
        for (i = 0; i < 8; i++)
        {
            image_info_t *img_info = home_item[i];
            unregister_touch_item((struct olpc_touch_item *)(&img_info->touch_item));
        }
    }

    return RT_EOK;
}

/**
 * fingerprint touch.
 */
static rt_err_t olpc_clock_fingerprint_touch_callback(rt_int32_t touch_id, enum olpc_touch_event event, struct point_info *point, void *parameter)
{
    rt_err_t ret = RT_ERROR;
    struct olpc_clock_data *olpc_data = (struct olpc_clock_data *)parameter;

    switch (event)
    {
    case TOUCH_EVENT_SHORT_DOWN:
        olpc_data->fp_id  = 0;
        olpc_data->cmd |= UPDATE_FINGERP;
        rt_event_send(olpc_data->disp_event, EVENT_UPDATE_CLOCK);

        rt_timer_start(olpc_data->fp_timer);
        ret = RT_EOK;
        break;

    default:
        break;
    }

    return ret;
}

static rt_err_t olpc_clock_fingerprint_touch_register(void *parameter)
{
    rt_int16_t   x, y;
    image_info_t *img_info;
    struct olpc_clock_data *olpc_data = (struct olpc_clock_data *)parameter;
    struct rt_device_graphic_info info;

    rt_memcpy(&info, &olpc_data->disp->info, sizeof(struct rt_device_graphic_info));

    /* fingerprint button key register */
    {
        img_info = &fingerprint0_info;
        x  = FP_REGION_X + (FP_REGION_W - FP_FB_W) / 2 + (FP_FB_W - img_info->w) / 2;
        y  = FP_REGION_Y + (FP_REGION_H - FP_FB_H) / 2;
        register_touch_item((struct olpc_touch_item *)(&img_info->touch_item), (void *)olpc_clock_fingerprint_touch_callback, (void *)olpc_data, 0);
        update_item_coord((struct olpc_touch_item *)(&img_info->touch_item), x, y, img_info->x, img_info->y);
    }

    return RT_EOK;
}

static rt_err_t olpc_clock_fingerprint_touch_unregister(void *parameter)
{
    image_info_t *img_info = &fingerprint0_info;

    unregister_touch_item((struct olpc_touch_item *)(&img_info->touch_item));

    return RT_EOK;
}

/**
 * lock touch.
 */
static rt_err_t olpc_clock_lock_touch_callback(rt_int32_t touch_id, enum olpc_touch_event event, struct point_info *point, void *parameter)
{
    rt_err_t ret = RT_ERROR;
    image_info_t *img = RT_NULL;
    struct olpc_clock_data *olpc_data = (struct olpc_clock_data *)parameter;

    switch (event)
    {
    case TOUCH_EVENT_MOVE:
        img = &lock_bar_info;
        rt_uint16_t y  = LOCK_REGION_Y + (LOCK_REGION_H - LOCK_FB_H) / 2;
        if ((point->y <  y +  img->y - img->h) ||
                (point->y >  y + (img->y + img->h) + img->h))
        {
            img = &lock_block_info;
            olpc_data->lock_px = img->x_scr;
            olpc_data->lock_py = img->y_scr;
            olpc_touch_reset();
        }
        else
        {
            olpc_data->lock_px = point->x;
            olpc_data->lock_py = point->y;
        }

        olpc_data->cmd |= UPDATE_LOCK;
        rt_event_send(olpc_data->disp_event, EVENT_UPDATE_CLOCK);
        ret = RT_EOK;
        break;

    case TOUCH_EVENT_UP:
    {
        //reset lock state
        img = &lock_block_info;
        olpc_data->lock_px = img->x_scr;
        olpc_data->lock_py = img->y_scr;

        olpc_data->cmd |= UPDATE_LOCK;
        rt_event_send(olpc_data->disp_event, EVENT_UPDATE_CLOCK);
    }
    break;
    default:
        break;
    }

    return ret;
}

static rt_err_t olpc_clock_lock_touch_register(void *parameter)
{
    rt_int16_t   x, y;
    image_info_t *img_info;
    struct olpc_clock_data *olpc_data = (struct olpc_clock_data *)parameter;
    struct rt_device_graphic_info info;

    rt_memcpy(&info, &olpc_data->disp->info, sizeof(struct rt_device_graphic_info));

    /* fingerprint button key register */
    {
        img_info = &lock_block_info;
        x  = LOCK_REGION_X + (LOCK_REGION_W - LOCK_FB_W) / 2;
        y  = LOCK_REGION_Y + (LOCK_REGION_H - LOCK_FB_H) / 2;

        register_touch_item((struct olpc_touch_item *)(&img_info->touch_item), (void *)olpc_clock_lock_touch_callback, (void *)olpc_data, 0);
        update_item_coord((struct olpc_touch_item *)(&img_info->touch_item), x, y, img_info->x, img_info->y);
    }

    return RT_EOK;
}

static rt_err_t olpc_clock_lock_touch_unregister(void *parameter)
{
    image_info_t *img_info = &lock_block_info;

    unregister_touch_item((struct olpc_touch_item *)(&img_info->touch_item));

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
    struct rt_display_lut lut0, lut1, lut2;

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

    lut2.winId = CLOCK_RGB565_WIN;
    lut2.format = RTGRAPHIC_PIXEL_FORMAT_RGB565;
    lut2.lut  = RT_NULL;
    lut2.size = 0;

    olpc_data->disp = rt_display_init(&lut0, &lut1, &lut2);
    RT_ASSERT(olpc_data->disp != RT_NULL);

#if defined(RT_USING_TOUCH)
    olpc_clock_screen_touch_register(olpc_data);
#endif

    olpc_data->disp_event = rt_event_create("display_event", RT_IPC_FLAG_FIFO);
    RT_ASSERT(olpc_data->disp_event != RT_NULL);

    ret = olpc_clock_init(olpc_data);
    RT_ASSERT(ret == RT_EOK);

    rt_event_send(olpc_data->disp_event, EVENT_UPDATE_CLOCK);

    while (1)
    {
        ret = rt_event_recv(olpc_data->disp_event, EVENT_UPDATE_CLOCK,
                            RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR,
                            RT_WAITING_FOREVER, &event);
        if (ret != RT_EOK)
        {
            /* Reserved... */
        }

        if (event & EVENT_UPDATE_CLOCK)
        {
            ret = olpc_clock_task_fun(olpc_data);
            RT_ASSERT(ret == RT_EOK);
        }
    }

    /* Thread deinit */
#if defined(RT_USING_TOUCH)
    olpc_clock_screen_touch_unregister(olpc_data);
#endif

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
    rt_thread_t rtt_clock;

    rtt_clock = rt_thread_create("olpcclock", olpc_clock_thread, RT_NULL, 2048, 5, 10);
    RT_ASSERT(rtt_clock != RT_NULL);
    rt_thread_startup(rtt_clock);

    return RT_EOK;
}

INIT_APP_EXPORT(olpc_clock_app_init);
#endif
