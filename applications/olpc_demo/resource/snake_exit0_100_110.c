/**
  * Copyright (c) 2019 Fuzhou Rockchip Electronics Co., Ltd
  *
  * SPDX-License-Identifier: Apache-2.0
  */

#include <rtthread.h>
#if defined(OLPC_APP_SNAKE_ENABLE)
#include "image_info.h"

static const unsigned char snake_exit0_100_110[1430UL] =
{
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xFF, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x03, 0xFF, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xFF, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xFF, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x07, 0xFF, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xFF, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xFF, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x07, 0xFF, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xFF, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xFF, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x07, 0xFF, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xFF, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xFF, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x07, 0xFF, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xFF, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xFF, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07,
    0xFF, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xFF, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x80, 0x07, 0xFF, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3F, 0x80, 0x07, 0xFF,
    0xF0, 0x00, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0x80, 0x07, 0xFF, 0xF0, 0x00, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xFF, 0x80, 0x07, 0xFF, 0xF0, 0x00, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xFF, 0x80, 0x07, 0xFF, 0xF0,
    0x00, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xFF, 0x80, 0x07, 0xFF, 0xF0, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0xFF, 0x80, 0x07, 0xFF, 0xF0, 0x00, 0xFF, 0x80, 0x00, 0x00, 0x00, 0x00, 0x3F, 0xFF, 0x80, 0x07, 0xFF, 0xF0, 0x00,
    0xFF, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x7F, 0xFF, 0x80, 0x07, 0xFF, 0xF0, 0x00, 0xFF, 0xF0, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x80, 0x07, 0xFF, 0xF0, 0x00, 0xFF, 0xF8, 0x00, 0x00, 0x00, 0x01, 0xFF, 0xFF, 0x80, 0x07, 0xFF, 0xF0, 0x00, 0xFF,
    0xFC, 0x00, 0x00, 0x00, 0x03, 0xFF, 0xFF, 0x80, 0x07, 0xFF, 0xF0, 0x00, 0xFF, 0xFE, 0x00, 0x00, 0x00, 0x07, 0xFF, 0xFF, 0x80, 0x07, 0xFF, 0xF0, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x0F, 0xFF, 0xFF, 0x80, 0x07, 0xFF, 0xF0, 0x00, 0xFF, 0xFF,
    0x80, 0x00, 0x00, 0x1F, 0xFF, 0xFF, 0x80, 0x07, 0xFF, 0xF0, 0x00, 0xFF, 0xFF, 0xC0, 0x00, 0x00, 0x3F, 0xFF, 0xFF, 0x80, 0x07, 0xFF, 0xF0, 0x00, 0xFF, 0xFF, 0xC0, 0x00, 0x00, 0x7F, 0xFF, 0xFE, 0x00, 0x07, 0xFF, 0xF0, 0x00, 0xFF, 0xFF, 0xE0,
    0x00, 0x00, 0xFF, 0xFF, 0xFE, 0x00, 0x07, 0xFF, 0xF0, 0x00, 0xFF, 0xFF, 0xF0, 0x00, 0x00, 0xFF, 0xFF, 0xF0, 0x00, 0x07, 0xFF, 0xF0, 0x00, 0x7F, 0xFF, 0xF8, 0x00, 0x01, 0xFF, 0xFF, 0xE0, 0x00, 0x07, 0xFF, 0xF0, 0x00, 0x3F, 0xFF, 0xF8, 0x00,
    0x03, 0xFF, 0xFF, 0xC0, 0x00, 0x07, 0xFF, 0xF0, 0x00, 0x1F, 0xFF, 0xFC, 0x00, 0x03, 0xFF, 0xFF, 0x80, 0x00, 0x07, 0xFF, 0xF0, 0x00, 0x0F, 0xFF, 0xFE, 0x00, 0x07, 0xFF, 0xFF, 0x00, 0x00, 0x07, 0xFF, 0xF0, 0x00, 0x07, 0xFF, 0xFE, 0x00, 0x07,
    0xFF, 0xFE, 0x00, 0x00, 0x07, 0xFF, 0xF0, 0x00, 0x07, 0xFF, 0xFF, 0x00, 0x07, 0xFF, 0xFE, 0x00, 0x00, 0x07, 0xFF, 0xF0, 0x00, 0x07, 0xFF, 0xFF, 0x00, 0x1F, 0xFF, 0xFE, 0x00, 0x00, 0x07, 0xFF, 0xF0, 0x00, 0x03, 0xFF, 0xFF, 0x00, 0x1F, 0xFF,
    0xF8, 0x00, 0x00, 0x07, 0xFF, 0xF0, 0x00, 0x00, 0xFF, 0xFF, 0x80, 0x1F, 0xFF, 0xF8, 0x00, 0x00, 0x07, 0xFF, 0xF0, 0x00, 0x00, 0xFF, 0xFF, 0xC0, 0x1F, 0xFF, 0xF0, 0x00, 0x00, 0x07, 0xFF, 0xF0, 0x00, 0x00, 0xFF, 0xFF, 0xC0, 0x3F, 0xFF, 0xF0,
    0x00, 0x00, 0x07, 0xFF, 0xF0, 0x00, 0x00, 0x7F, 0xFF, 0xC0, 0x3F, 0xFF, 0xE0, 0x00, 0x00, 0x07, 0xFF, 0xF0, 0x00, 0x00, 0x7F, 0xFF, 0xE0, 0x3F, 0xFF, 0xE0, 0x00, 0x00, 0x07, 0xFF, 0xF0, 0x00, 0x00, 0x3F, 0xFF, 0xE0, 0x7F, 0xFF, 0xE0, 0x00,
    0x00, 0x07, 0xFF, 0xF0, 0x00, 0x00, 0x3F, 0xFF, 0xE0, 0x7F, 0xFF, 0xC0, 0x00, 0x00, 0x07, 0xFF, 0xF0, 0x00, 0x00, 0x3F, 0xFF, 0xE0, 0x7F, 0xFF, 0xC0, 0x00, 0x00, 0x03, 0xFF, 0xE0, 0x00, 0x00, 0x3F, 0xFF, 0xE0, 0x7F, 0xFF, 0xC0, 0x00, 0x00,
    0x01, 0xFF, 0xC0, 0x00, 0x00, 0x1F, 0xFF, 0xE0, 0x7F, 0xFF, 0xC0, 0x00, 0x00, 0x00, 0xFE, 0x00, 0x00, 0x00, 0x1F, 0xFF, 0xF0, 0x7F, 0xFF, 0x80, 0x00, 0x00, 0x00, 0x7C, 0x00, 0x00, 0x00, 0x1F, 0xFF, 0xF0, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x1F, 0xFF, 0xF0, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0xFF, 0xF0, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0xFF, 0xF0, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x1F, 0xFF, 0xF0, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0xFF, 0xF0, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0xFF, 0xF0, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x1F, 0xFF, 0xF0, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0xFF, 0xF0, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0xFF, 0xF0, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x1F, 0xFF, 0xF0, 0xFF, 0xFF, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0xFF, 0xF0, 0x7F, 0xFF, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0xFF, 0xF0, 0x7F, 0xFF, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x1F, 0xFF, 0xE0, 0x7F, 0xFF, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3F, 0xFF, 0xE0, 0x7F, 0xFF, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3F, 0xFF, 0xE0, 0x7F, 0xFF, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3F,
    0xFF, 0xE0, 0x3F, 0xFF, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3F, 0xFF, 0xE0, 0x3F, 0xFF, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0xFF, 0xC0, 0x3F, 0xFF, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0xFF,
    0xC0, 0x1F, 0xFF, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xC0, 0x1F, 0xFF, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x80, 0x1F, 0xFF, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00,
    0x1F, 0xFF, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xFF, 0xFF, 0x00, 0x07, 0xFF, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xFF, 0xFF, 0x00, 0x07, 0xFF, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xFF, 0xFF, 0x00, 0x07,
    0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xFF, 0xFE, 0x00, 0x03, 0xFF, 0xFF, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xFF, 0xFE, 0x00, 0x03, 0xFF, 0xFF, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0xFF, 0xFC, 0x00, 0x01, 0xFF,
    0xFF, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xF8, 0x00, 0x00, 0xFF, 0xFF, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x01, 0xFF, 0xFF, 0xF8, 0x00, 0x00, 0xFF, 0xFF, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x03, 0xFF, 0xFF, 0xF0, 0x00, 0x00, 0x7F, 0xFF,
    0xFE, 0x00, 0x00, 0x00, 0x00, 0x03, 0xFF, 0xFF, 0xE0, 0x00, 0x00, 0x3F, 0xFF, 0xFF, 0xC0, 0x00, 0x00, 0x00, 0x1F, 0xFF, 0xFF, 0xC0, 0x00, 0x00, 0x1F, 0xFF, 0xFF, 0xF0, 0x00, 0x00, 0x00, 0x7F, 0xFF, 0xFF, 0xC0, 0x00, 0x00, 0x0F, 0xFF, 0xFF,
    0xFC, 0x00, 0x00, 0x07, 0xFF, 0xFF, 0xFF, 0x80, 0x00, 0x00, 0x07, 0xFF, 0xFF, 0xFF, 0xC0, 0x00, 0x3F, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x03, 0xFF, 0xFF, 0xFF, 0xE0, 0x00, 0x7F, 0xFF, 0xFF, 0xFE, 0x00, 0x00, 0x00, 0x01, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x3F, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x1F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x80, 0x00, 0x00, 0x00, 0x00, 0x07, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3F, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0xFF, 0xFF, 0xFF, 0xE0,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xFF, 0xFF, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0xFF, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00
};

image_info_t snake_exit0_info =
{
    .type  = IMG_TYPE_RAW,
    .pixel = RTGRAPHIC_PIXEL_FORMAT_GRAY1,
    .x = 0,
    .y = 0,
    .w = 100,
    .h = 110,
    .size = 1430UL,
    .data = snake_exit0_100_110,
};

#endif
