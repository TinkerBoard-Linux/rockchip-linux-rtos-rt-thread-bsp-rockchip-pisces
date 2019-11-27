/**
  * Copyright (c) 2019 Fuzhou Rockchip Electronics Co., Ltd
  *
  * SPDX-License-Identifier: Apache-2.0
  */

#include <rtthread.h>
#if defined(OLPC_APP_NOTE_ENABLE)
#include "image_info.h"

static const unsigned char note_dot160_16_16[32UL] =
{
    0x07, 0xE0, 0x0F, 0xF0, 0x3F, 0xFC, 0x3F, 0xFC, 0x7F, 0xFE, 0xFF, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0x7F, 0xFE, 0x3F, 0xFC, 0x3F, 0xFC, 0x0F, 0xF0, 0x03, 0xC0
};

image_info_t note_dot160_info =
{
    .type  = IMG_TYPE_RAW,
    .pixel = RTGRAPHIC_PIXEL_FORMAT_GRAY1,
    .x = 0,
    .y = 0,
    .w = 16,
    .h = 16,
    .size = 32UL,
    .data = note_dot160_16_16,
    .colorkey = COLOR_KEY_EN | 0,
};

#endif
