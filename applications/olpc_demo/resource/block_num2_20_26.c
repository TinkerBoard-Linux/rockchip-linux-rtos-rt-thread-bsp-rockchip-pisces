/**
  * Copyright (c) 2019 Fuzhou Rockchip Electronics Co., Ltd
  *
  * SPDX-License-Identifier: Apache-2.0
  */

#include <rtthread.h>
#if defined(OLPC_APP_BLOCK_ENABLE)
#include "image_info.h"

static unsigned char block_num2_20_26[78UL] =
{
    0xFF, 0xFF, 0xF0, 0xFF, 0x07, 0xF0, 0xF8, 0x00, 0xF0, 0xF0, 0x00, 0x70, 0xE0, 0xF0, 0x70, 0xE1, 0xF8, 0x30, 0xC3, 0xFC, 0x30, 0xC3, 0xFC, 0x30, 0xC7, 0xFC, 0x30, 0xFF, 0xFC, 0x30, 0xFF, 0xF8, 0x30, 0xFF, 0xF0, 0x70, 0xFF, 0xE0, 0x70, 0xFF,
    0xC0, 0xF0, 0xFF, 0x81, 0xF0, 0xFF, 0x07, 0xF0, 0xFC, 0x0F, 0xF0, 0xF8, 0x1F, 0xF0, 0xF0, 0x3F, 0xF0, 0xE0, 0x7F, 0xF0, 0xE0, 0xFF, 0xF0, 0xC0, 0x00, 0x30, 0xC0, 0x00, 0x10, 0xC0, 0x00, 0x10, 0xE0, 0x00, 0x30, 0xFF, 0xFF, 0xF0
};

image_info_t block_num2_info =
{
    .type  = IMG_TYPE_RAW,
    .pixel = RTGRAPHIC_PIXEL_FORMAT_GRAY1,
    .x = 830,
    .y = 92,
    .w = 20,
    .h = 26,
    .size = 78UL,
    .data = block_num2_20_26,
};

#endif
