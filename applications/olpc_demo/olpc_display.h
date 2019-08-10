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
struct rt_display_data
{
    rt_device_t device;
    struct rt_device_graphic_info info;

    rt_uint16_t xres;
    rt_uint16_t yres;
};
typedef struct rt_display_data *rt_display_data_t;

/**
 * display rotate.
 */
void rt_display_rotate(float angle, int w, int h,
                       unsigned char *src, unsigned char *dst,
                       int dst_str, int xcen, int ycen);

/**
 * fill image data to fb buffer
 */
void rt_display_img_fill(image_info_t *img_info, rt_uint8_t *fb,
                         rt_int32_t xVir, rt_int32_t xoffset, rt_int32_t yoffset);

/**
 * Configuration win layers.
 */
rt_err_t rt_display_win_layer_set(rt_device_t device,
                                  uint8_t   winId,    rt_bool_t winEn,
                                  uint8_t  *framebuf, uint32_t len,
                                  uint16_t srcW,      uint16_t srcH,
                                  uint16_t srcX,      uint16_t srcY,
                                  uint16_t dstY,      uint16_t dstH);

/**
 * Display screen scroll API.
 */
rt_err_t rt_display_screen_scroll(rt_device_t device, uint8_t winId, uint32_t mode,
                                  uint16_t srcW, uint16_t srcH,
                                  int16_t xoffset, int16_t yoffset);

/**
 * Clear screen for display initial.
 */
int rt_display_screen_clear(rt_device_t device);

/**
 * Display driver sync hook, wait for drv_display finish.
 */
rt_err_t rt_display_sync_hook(rt_device_t device, uint8_t winid);

/**
 * Display driver update hook, send update command to drv_display.
 */
rt_err_t rt_display_update_hook(rt_device_t device, uint8_t winid);

/**
 * Display application initial, initial screen and win layers.
 */
rt_display_data_t rt_display_init(void);

/**
 * Display application deinitial, free resources.
 */
void rt_display_deinit(rt_display_data_t disp_data);

#endif
