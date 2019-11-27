/**
  * Copyright (c) 2019 Fuzhou Rockchip Electronics Co., Ltd
  *
  * SPDX-License-Identifier: Apache-2.0
  */

#include <rtthread.h>
#if defined(OLPC_APP_NOTE_ENABLE)
#include "image_info.h"

static const unsigned char note_dot321_32_32[128UL] =
{
    0xFF, 0xF0, 0x0F, 0xFF, 0xFF, 0x80, 0x01, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFC, 0x00, 0x00, 0x3F, 0xF8, 0x00, 0x00, 0x1F, 0xF0, 0x00, 0x00, 0x0F, 0xE0, 0x00, 0x00, 0x07, 0xE0, 0x00, 0x00, 0x07, 0xC0, 0x00, 0x00, 0x03, 0x80, 0x00, 0x00, 0x03,
    0x80, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x80, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x01, 0xC0, 0x00, 0x00, 0x03, 0xE0, 0x00, 0x00, 0x07, 0xE0, 0x00, 0x00, 0x07, 0xF0, 0x00, 0x00, 0x0F, 0xF8, 0x00, 0x00, 0x1F, 0xFC, 0x00, 0x00, 0x3F, 0xFF, 0x00, 0x00, 0xFF,
    0xFF, 0xC0, 0x01, 0xFF, 0xFF, 0xF0, 0x0F, 0xFF
};

image_info_t note_dot321_info =
{
    .type  = IMG_TYPE_RAW,
    .pixel = RTGRAPHIC_PIXEL_FORMAT_GRAY1,
    .x = 0,
    .y = 0,
    .w = 32,
    .h = 32,
    .size = 128UL,
    .data = note_dot321_32_32,
    .colorkey = COLOR_KEY_EN | 1,
};

#endif
