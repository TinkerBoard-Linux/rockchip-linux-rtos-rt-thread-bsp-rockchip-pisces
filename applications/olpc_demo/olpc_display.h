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
    rt_uint8_t  *fb;
    rt_uint32_t fblen;
    rt_uint32_t colorkey;

    rt_uint16_t x;
    rt_uint16_t y;
    rt_uint16_t ylast;
    rt_uint16_t w;
    rt_uint16_t h;
};

struct rt_display_data
{
    rt_device_t device;
    struct rt_device_graphic_info info;
    struct rt_display_lut lut[3];

    rt_uint16_t xres;
    rt_uint16_t yres;

    rt_uint16_t  blval;
};
typedef struct rt_display_data *rt_display_data_t;

/**
 * color palette for RGB332
 */
extern uint32_t bpp_lut[256];

/**
 * display rotate.
 */
void rt_display_rotate_4bit(float angle, int w, int h, unsigned char *src, unsigned char *dst, int dst_str, int xcen, int ycen);
void rt_display_rotate_8bit(float angle, int w, int h, unsigned char *src, unsigned char *dst, int dst_str, int xcen, int ycen);
void rt_display_rotate_16bit(float angle, int w, int h, unsigned short *src, unsigned short *dst, int dst_str, int xcen, int ycen);
void rt_display_rotate_24bit(float angle, int w, int h, unsigned char *src, unsigned char *dst, int dst_str, int xcen, int ycen);

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
 * Display application initial, initial screen and win layers.
 */
rt_display_data_t rt_display_init(struct rt_display_lut *lut0,
                                  struct rt_display_lut *lut1,
                                  struct rt_display_lut *lut2);

/**
 * Display application deinitial, free resources.
 */
void rt_display_deinit(rt_display_data_t disp_data);


/**
 * Get MAX value of backlight.
 */
rt_uint16_t rt_display_get_bl_max(rt_device_t device);

/**
 * screen protection API.
 */
int olpc_srcprotect_app_init(void);
void olpc_srcprotect_app_start(rt_err_t (*exithook)(void *parameter), void *parameter);

#endif
