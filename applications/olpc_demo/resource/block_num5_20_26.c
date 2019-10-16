/**
  * Copyright (c) 2019 Fuzhou Rockchip Electronics Co., Ltd
  *
  * SPDX-License-Identifier: Apache-2.0
  */

#include <rtthread.h>
#if defined(OLPC_APP_BLOCK_ENABLE)
#include "image_info.h"

static unsigned char block_num5_20_26[78UL] =
{
    0xFF, 0xFF, 0xF0, 0xF8, 0x00, 0x70, 0xF0, 0x00, 0x30, 0xF0, 0x00, 0x30, 0xF0, 0x00, 0x70, 0xF0, 0xFF, 0xF0, 0xF1, 0xFF, 0xF0, 0xE1, 0xFF, 0xF0, 0xE1, 0xFF, 0xF0, 0xE1, 0x87, 0xF0, 0xE0, 0x00, 0xF0, 0xE0, 0x00, 0x70, 0xE0, 0xF0, 0x30, 0xE3,
    0xF8, 0x30, 0xFF, 0xFC, 0x30, 0xFF, 0xFC, 0x10, 0xFF, 0xFE, 0x10, 0xFF, 0xFC, 0x10, 0xC7, 0xFC, 0x10, 0xC3, 0xFC, 0x30, 0xC1, 0xF8, 0x30, 0xE0, 0xF0, 0x70, 0xF0, 0x00, 0xF0, 0xF8, 0x01, 0xF0, 0xFE, 0x07, 0xF0, 0xFF, 0xFF, 0xF0
};

image_info_t block_num5_info =
{
    .type  = IMG_TYPE_RAW,
    .pixel = RTGRAPHIC_PIXEL_FORMAT_GRAY1,
    .x = 830,
    .y = 92,
    .w = 20,
    .h = 26,
    .size = 78UL,
    .data = block_num5_20_26,
};

#endif
