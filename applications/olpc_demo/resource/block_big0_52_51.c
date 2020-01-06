/**
  * Copyright (c) 2019 Fuzhou Rockchip Electronics Co., Ltd
  *
  * SPDX-License-Identifier: Apache-2.0
  */

#include <rtthread.h>
#if defined(OLPC_APP_BLOCK_ENABLE) && (defined(OLPC_STATICLD_ENABLE) || defined(OLPC_OVERLAY_ENABLE))
#include "image_info.h"

static const unsigned char block_big0_52_51[357UL] =
{
    0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x8F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x10, 0x1F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x80, 0x1F, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0x80, 0x1F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x80, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x07, 0x80, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x07, 0x80, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x07, 0x80, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x07, 0x80, 0x1E, 0x00, 0x00,
    0x00, 0x00, 0x07, 0x80, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x07, 0x80, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x07, 0x80, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x07, 0x80, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x07, 0x80, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x07, 0x80, 0x1E,
    0x00, 0x00, 0x00, 0x00, 0x07, 0x80, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x07, 0x80, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x07, 0x80, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x07, 0x80, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x07, 0x80, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x07,
    0x80, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x07, 0x80, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x07, 0x80, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x07, 0x80, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x07, 0x80, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x07, 0x80, 0x1E, 0x00, 0x00, 0x00,
    0x00, 0x07, 0x80, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x07, 0x80, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x07, 0x80, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x07, 0x80, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x07, 0x80, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x07, 0x80, 0x1E, 0x00,
    0x00, 0x00, 0x00, 0x07, 0x80, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x07, 0x80, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x07, 0x80, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x07, 0x80, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x07, 0x80, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x07, 0x80,
    0x1E, 0x00, 0x00, 0x00, 0x00, 0x07, 0x80, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x07, 0x80, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x07, 0x80, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x07, 0x80, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x07, 0x80, 0x1F, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0x80, 0x1F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x80, 0x1F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x80, 0x8F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x10, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30
};

image_info_t block_big0_info =
{
    .type  = IMG_TYPE_RAW,
    .pixel = RTGRAPHIC_PIXEL_FORMAT_GRAY1,
    .x = 23,
    .y = 41,
    .w = 52,
    .h = 51,
    .size = 357UL,
    .data = block_big0_52_51,
};

#endif
