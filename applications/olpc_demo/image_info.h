/**
  * Copyright (c) 2019 Fuzhou Rockchip Electronics Co., Ltd
  *
  * SPDX-License-Identifier: Apache-2.0
  ******************************************************************************
  * @file    image_info.h
  * @version V0.1
  * @brief   image info
  *
  * Change Logs:
  * Date           Author          Notes
  * 2019-07-18     Tony.zheng      first implementation
  *
  ******************************************************************************
  */

#ifndef __IMAGE_INFO_H__
#define __IMAGE_INFO_H__

/**
 * Image info for display
 */
typedef struct
{
    uint8_t  type;
    uint8_t  pixel;

    uint16_t x;
    uint16_t y;
    uint16_t w;
    uint16_t h;
    uint32_t size;
    uint8_t  *data;
} image_info_t;

/**
 * image_info_t "type" define
 */
#define IMG_TYPE_RAW        0
#define IMG_TYPE_COMPRESS   1

#endif
