/**
  * Copyright (c) 2019 Fuzhou Rockchip Electronics Co., Ltd
  *
  * SPDX-License-Identifier: Apache-2.0
  */

#include <rtthread.h>
#if defined(OLPC_APP_BLOCK_ENABLE) && (defined(OLPC_STATICLD_ENABLE) || defined(OLPC_OVERLAY_ENABLE))
#include "image_info.h"

static const unsigned char block_num9_20_26[78UL] =
{
    0xFF, 0xFF, 0xF0, 0xFE, 0x0F, 0xF0, 0xF8, 0x03, 0xF0, 0xE0, 0x00, 0xF0, 0xE1, 0xE0, 0xF0, 0xC3, 0xF0, 0x70, 0xC3, 0xF8, 0x70, 0x83, 0xF8, 0x30, 0x87, 0xFC, 0x30, 0x87, 0xFC, 0x30, 0x87, 0xF8, 0x30, 0xC3, 0xF8, 0x30, 0xC3, 0xF8, 0x30, 0xC1,
    0xE0, 0x30, 0xE0, 0x00, 0x30, 0xF0, 0x04, 0x30, 0xFC, 0x1C, 0x30, 0xFF, 0xFC, 0x30, 0xFF, 0xF8, 0x70, 0xC3, 0xF8, 0x70, 0xC3, 0xF0, 0x70, 0xC1, 0xE0, 0xF0, 0xE0, 0x01, 0xF0, 0xF0, 0x03, 0xF0, 0xFE, 0x0F, 0xF0, 0xFF, 0xFF, 0xF0
};

image_info_t block_num9_info =
{
    .type  = IMG_TYPE_RAW,
    .pixel = RTGRAPHIC_PIXEL_FORMAT_GRAY1,
    .x = 830,
    .y = 92,
    .w = 20,
    .h = 26,
    .size = 78UL,
    .data = block_num9_20_26,
};

#endif
