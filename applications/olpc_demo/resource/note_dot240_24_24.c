/**
  * Copyright (c) 2019 Fuzhou Rockchip Electronics Co., Ltd
  *
  * SPDX-License-Identifier: Apache-2.0
  */

#include <rtthread.h>
#if defined(OLPC_APP_NOTE_ENABLE)
#include "image_info.h"

static const unsigned char note_dot240_24_24[72UL] =
{
    0x00, 0x7E, 0x00, 0x03, 0xFF, 0xC0, 0x07, 0xFF, 0xE0, 0x0F, 0xFF, 0xF0, 0x1F, 0xFF, 0xF8, 0x3F, 0xFF, 0xFC, 0x7F, 0xFF, 0xFE, 0x7F, 0xFF, 0xFE, 0x7F, 0xFF, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0xFF, 0xFE, 0x7F, 0xFF, 0xFE, 0x7F, 0xFF, 0xFE, 0x3F, 0xFF, 0xFC, 0x1F, 0xFF, 0xF8, 0x0F, 0xFF, 0xF0, 0x07, 0xFF, 0xE0, 0x03, 0xFF, 0xC0, 0x00, 0x7E, 0x00
};

image_info_t note_dot240_info =
{
    .type  = IMG_TYPE_RAW,
    .pixel = RTGRAPHIC_PIXEL_FORMAT_GRAY1,
    .x = 0,
    .y = 0,
    .w = 24,
    .h = 24,
    .size = 72UL,
    .data = note_dot240_24_24,
    .colorkey = COLOR_KEY_EN | 0,
};

#endif
