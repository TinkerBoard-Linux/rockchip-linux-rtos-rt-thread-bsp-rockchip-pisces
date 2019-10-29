/**
  * Copyright (c) 2019 Fuzhou Rockchip Electronics Co., Ltd
  *
  * SPDX-License-Identifier: Apache-2.0
  */

#include <rtthread.h>
#if defined(OLPC_APP_SNAKE_ENABLE)
#include "image_info.h"

static unsigned char snake_num0_20_26[78UL] =
{
    0xFF, 0xFF, 0xF0, 0xFF, 0x0F, 0xF0, 0xF8, 0x01, 0xF0, 0xF0, 0x00, 0xF0, 0xE0, 0xF0, 0x70, 0xE1, 0xF8, 0x70, 0xC1, 0xF8, 0x30, 0xC3, 0xFC, 0x30, 0xC3, 0xFC, 0x30, 0xC3, 0xFC, 0x30, 0xC3, 0xFC, 0x30, 0xC3, 0xFC, 0x30, 0xC3, 0xFC, 0x30, 0xC3,
    0xFC, 0x30, 0xC3, 0xFC, 0x30, 0xC3, 0xFC, 0x30, 0xC3, 0xFC, 0x30, 0xC3, 0xFC, 0x30, 0xC1, 0xFC, 0x30, 0xE1, 0xF8, 0x30, 0xE1, 0xF8, 0x70, 0xF0, 0xF0, 0x70, 0xF0, 0x00, 0xF0, 0xFC, 0x01, 0xF0, 0xFF, 0x0F, 0xF0, 0xFF, 0xFF, 0xF0
};

image_info_t snake_num0_info =
{
    .type  = IMG_TYPE_RAW,
    .pixel = RTGRAPHIC_PIXEL_FORMAT_GRAY1,
    .x = 415,
    .y = 45,
    .w = 20,
    .h = 26,
    .size = 78UL,
    .data = snake_num0_20_26,
};

#endif
