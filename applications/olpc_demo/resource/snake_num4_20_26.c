/**
  * Copyright (c) 2019 Fuzhou Rockchip Electronics Co., Ltd
  *
  * SPDX-License-Identifier: Apache-2.0
  */

#include <rtthread.h>
#if defined(OLPC_APP_SNAKE_ENABLE)
#include "image_info.h"

static const unsigned char snake_num4_20_26[78UL] =
{
    0xFF, 0xFF, 0xF0, 0xFF, 0xF1, 0xF0, 0xFF, 0xE0, 0xF0, 0xFF, 0xE0, 0xF0, 0xFF, 0xC0, 0xF0, 0xFF, 0x80, 0xF0, 0xFF, 0x00, 0xF0, 0xFE, 0x10, 0xF0, 0xFE, 0x30, 0xF0, 0xFC, 0x70, 0xF0, 0xF8, 0x70, 0xF0, 0xF0, 0xF0, 0xF0, 0xE1, 0xF0, 0xF0, 0xC3,
    0xF0, 0xF0, 0xC3, 0xF0, 0xF0, 0x87, 0xF0, 0xF0, 0x80, 0x00, 0x10, 0x80, 0x00, 0x10, 0xC0, 0x00, 0x10, 0xFF, 0xF0, 0xF0, 0xFF, 0xF0, 0xF0, 0xFF, 0xF0, 0xF0, 0xFF, 0xF0, 0xF0, 0xFF, 0xF0, 0xF0, 0xFF, 0xF9, 0xF0, 0xFF, 0xFF, 0xF0
};

image_info_t snake_num4_info =
{
    .type  = IMG_TYPE_RAW,
    .pixel = RTGRAPHIC_PIXEL_FORMAT_GRAY1,
    .x = 415,
    .y = 45,
    .w = 20,
    .h = 26,
    .size = 78UL,
    .data = snake_num4_20_26,
};

#endif
