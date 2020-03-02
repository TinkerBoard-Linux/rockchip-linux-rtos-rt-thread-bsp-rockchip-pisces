/**
  * Copyright (c) 2019 Fuzhou Rockchip Electronics Co., Ltd
  *
  * SPDX-License-Identifier: Apache-2.0
  ******************************************************************************
  * @file    olpc_display.h
  * @version V0.1
  * @brief   olpc display
  *
  * Change Logs:
  * Date           Author          Notes
  * 2019-08-01     Tony.zheng      first implementation
  *
  ******************************************************************************
  */

#ifndef __OLPC_DISPLAY_H__
#define __OLPC_DISPLAY_H__
#include <rtthread.h>
#include "color_palette.h"
#include "drv_display.h"

/* Macro define */
#define MIN(X, Y)           ((X)<(Y)?(X):(Y))
#define MAX(X, Y)           ((X)>(Y)?(X):(Y))
#define ABS(X)              (((X) < 0) ? (-(X)) : (X))

#define SCREEN_HALIGN       65

#define WIN_LAYERS_X        0
#define WIN_LAYERS_Y        0
#define WIN_LAYERS_W        (info.width  / 1)
#define WIN_LAYERS_H        (info.height / 1)

#define WIN_SCALED_X        0
#define WIN_SCALED_Y        0
#define WIN_SCALED_W        (info.width  / 1)
#define WIN_SCALED_H        (info.height / 1)

#define WSCALE              (WIN_SCALED_W / WIN_LAYERS_W)
#define HSCALE              (WIN_SCALED_H / WIN_LAYERS_H)

#define EVENT_APP_CLOCK     (0x01UL << 0)
#define EVENT_APP_EBOOK     (0x01UL << 1)
#define EVENT_APP_BLOCK     (0x01UL << 2)
#define EVENT_APP_SNAKE     (0x01UL << 3)
#define EVENT_APP_NOTE      (0x01UL << 4)
#define EVENT_APP_XSCREEN   (0x01UL << 5)
#define EVENT_APP_BLN       (0x01UL << 6)

/**
 * Global data struct for olpc display demo
 */
struct rt_display_lut
{
    rt_uint8_t  winId;
    rt_uint8_t  format;
    rt_uint32_t *lut;
    rt_uint32_t size;
};

struct rt_display_config
{
    struct rt_display_config *next;

    rt_uint8_t  winId;
    rt_uint8_t  zpos;
    rt_uint8_t  format;
    rt_uint32_t *lut;
    rt_uint32_t lutsize;

    rt_uint8_t  *fb;
    rt_uint32_t fblen;
    rt_uint32_t colorkey;

    rt_uint16_t x;
    rt_uint16_t y;
    rt_uint16_t ylast;
    rt_uint16_t w;
    rt_uint16_t h;

    rt_uint8_t  alphaEn;
    rt_uint8_t  alphaMode;
    rt_uint8_t  alphaPreMul;
    rt_uint8_t  globalAlphaValue;
};

typedef enum
{
    WIN_BOTTOM_LAYER = 0,
    WIN_MIDDLE_LAYER,
    WIN_TOP_LAYER,
    WIN_MAX_LAYER
} WINLAYER_ID;

struct rt_display_mq_t
{
    rt_uint8_t cfgsta;                              // config status(bit 2-0), 0: unused, 1 used;
    struct rt_display_config win[WIN_MAX_LAYER];    // layers(bottom --> top): 0 --> 1 --> 2
    rt_err_t (*disp_finish)(void);
};

struct rt_display_data
{
    rt_device_t device;
    rt_mq_t     disp_mq;
    struct rt_device_graphic_info info;
    struct rt_display_lut lut[3];

    rt_uint16_t xres;
    rt_uint16_t yres;
    rt_uint16_t blval;
};
typedef struct rt_display_data *rt_display_data_t;

/**
 * color palette for RGB332
 */
extern uint32_t bpp_lut[256];

extern rt_event_t olpc_main_event;

/**
 * display rotate.
 */
void rt_display_rotate_4bit(float angle, int w, int h, unsigned char *src, unsigned char *dst, int dst_str, int xcen, int ycen);
void rt_display_rotate_8bit(float angle, int w, int h, unsigned char *src, unsigned char *dst, int dst_str, int xcen, int ycen);
void rt_display_rotate_16bit(float angle, int w, int h, unsigned short *src, unsigned short *dst, int dst_str, int xcen, int ycen);
void rt_display_rotate_24bit(float angle, int w, int h, unsigned char *src, unsigned char *dst, int dst_str, int xcen, int ycen);
void rt_display_rotate_32bit(float angle, int w, int h, unsigned int *src, unsigned int *dst, int dst_str, int xcen, int ycen);

/**
 * color palette for RGB332 and BGR233,default format is RGB332.
 */
void rt_display_update_lut(int format);

/**
 * Check is if two display region overlapped
 */
rt_err_t olpc_display_overlay_check(rt_uint16_t y1, rt_uint16_t y2, rt_uint16_t yy1, rt_uint16_t yy2);

/**
 * fill image data to fb buffer
 */
void rt_display_img_fill(image_info_t *img_info, rt_uint8_t *fb,
                         rt_int32_t xVir, rt_int32_t xoffset, rt_int32_t yoffset);

/**
 * Configuration win layers.
 */
rt_err_t rt_display_win_layers_set(struct rt_display_config *wincfg);

/**
 * list win layers.
 */
rt_err_t rt_display_win_layers_list(struct rt_display_config **head, struct rt_display_config *tail);

/**
 * Display screen scroll API.
 */
rt_err_t rt_display_screen_scroll(rt_device_t device, uint8_t winId, uint32_t mode,
                                  uint16_t srcW, uint16_t srcH,
                                  int16_t xoffset, int16_t yoffset);

/**
 * backlight set.
 */
rt_err_t rt_display_win_backlight_set(rt_uint16_t val);

/**
 * Clear screen for display initial.
 */
int rt_display_screen_clear(rt_device_t device);

/**
 * Display driver sync hook, wait for drv_display finish.
 */
rt_err_t rt_display_sync_hook(rt_device_t device);

/**
 * Display driver update hook, send update command to drv_display.
 */
rt_err_t rt_display_update_hook(rt_device_t device, uint8_t winid);

/**
 * Display lut set.
 */
rt_err_t rt_display_win_clear(rt_uint8_t winid, rt_uint8_t fmt,
                              rt_uint16_t y, rt_uint16_t h, rt_uint8_t data);

/**
 * Display lut set.
 */
rt_err_t rt_display_lutset(struct rt_display_lut *lutA,
                           struct rt_display_lut *lutB,
                           struct rt_display_lut *lutC);
/**
 * Display application initial, initial screen and win layers.
 */
rt_display_data_t rt_display_init(struct rt_display_lut *lut0,
                                  struct rt_display_lut *lut1,
                                  struct rt_display_lut *lut2);

/**
 * Get global display data struct.
 */
rt_display_data_t rt_display_get_disp(void);

/**
 * Display application deinitial, free resources.
 */
void rt_display_deinit(rt_display_data_t disp_data);

/**
 * Get MAX value of backlight.
 */
rt_uint16_t rt_display_get_bl_max(rt_device_t device);

/**
 * olpc clock demo application init.
 */
int olpc_clock_app_init(void);

/**
 * olpc ebook demo application init.
 */
int olpc_ebook_app_init(void);

/**
 * olpc block demo application init.
 */
int olpc_block_app_init(void);

/**
 * olpc note demo application init.
 */
int olpc_note_app_init(void);

/**
 * olpc snake demo application init.
 */
int olpc_snake_app_init(void);

/**
 * olpc xscreen demo application init.
 */
int olpc_xscreen_app_init(void);
/**
 * olpc bln demo application init.
 */
int olpc_bln_app_init(void);

/**
 * screen protection API.
 */
void olpc_srcprotect_app_init(rt_err_t (*exithook)(void *parameter), void *parameter);

#endif
