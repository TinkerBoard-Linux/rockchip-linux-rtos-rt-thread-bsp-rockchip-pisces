/**
  * Copyright (c) 2019 Fuzhou Rockchip Electronics Co., Ltd
  *
  * SPDX-License-Identifier: Apache-2.0
  */

#include <rtthread.h>
#include "image_info.h"

#if defined(OLPC_APP_CLOCK_STYLE_ROUND_ROMAN332) || defined(OLPC_APP_CLOCK_STYLE_ROUND_ARABIC)
// RGB332
static const unsigned char msg_font_2_22_38[836UL] =
{
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x6D, 0x6D, 0x6D, 0x25, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x92, 0xB6, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xDB,
    0xB6, 0x49, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x25, 0xDA, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x92, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x25, 0xDB, 0xFF, 0xFF, 0xDA, 0x92, 0x25,
    0x00, 0x00, 0x6D, 0x92, 0xFF, 0xFF, 0xFF, 0x92, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xB6, 0xFF, 0xFF, 0x92, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x25, 0xDB, 0xFF, 0xFF, 0x49, 0x00, 0x00, 0x00, 0x00, 0x00, 0x49, 0xFF, 0xFF, 0xB6,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x25, 0xFF, 0xFF, 0x92, 0x00, 0x00, 0x00, 0x00, 0x00, 0xB6, 0xFF, 0xFF, 0x25, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xB6, 0xFF, 0xDA, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xDA, 0xFF, 0xB6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x92, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x92, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x6D, 0xFF, 0xFF, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x6D, 0x6D, 0x25, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x6D, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x92, 0xFF, 0xDB, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xB6, 0xFF, 0xB6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x49, 0xFF, 0xFF, 0x92, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xB6, 0xFF, 0xFF, 0x25, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x92, 0xFF, 0xFF, 0x92, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x49, 0xFF, 0xFF, 0xDB, 0x25, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xDB, 0xFF, 0xFF, 0x6D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xB6, 0xFF, 0xFF, 0x92, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x92, 0xFF, 0xFF, 0xB6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x6D, 0xFF, 0xFF, 0xDB, 0x25, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x49, 0xFF, 0xFF, 0xFF, 0x6D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x25, 0xDB, 0xFF, 0xFF, 0x92, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xB6, 0xFF, 0xFF, 0x92, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xB6, 0xFF, 0xFF,
    0xB6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x92, 0xFF, 0xFF, 0xDB, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x6D,
    0xFF, 0xFF, 0xDB, 0x25, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x25, 0xDB, 0xFF, 0xFF, 0x6D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0xDA, 0xFF, 0xFF, 0x92, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x92, 0xFF, 0xFF, 0x92, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x92, 0xFF, 0xFF, 0xB6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x49, 0xFF, 0xFF, 0xFF, 0x6D, 0x6D, 0x6D, 0x6D, 0x6D, 0x6D, 0x6D, 0x6D, 0x6D, 0x6D, 0x6D,
    0x6D, 0x6D, 0x6D, 0x6D, 0x25, 0x00, 0x00, 0x92, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x6D, 0x00, 0x00, 0x25, 0xDA, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x6D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

image_info_t msg_font_2_info =
{
    .type  = IMG_TYPE_RAW,
    .pixel = RTGRAPHIC_PIXEL_FORMAT_RGB332,
    .x = 0,
    .y = 0,
    .w = 22,
    .h = 38,
    .size = 836,
    .data = msg_font_2_22_38,
};

#elif defined(OLPC_APP_CLOCK_STYLE_ROUND_ROMAN565)
// RGB565
static const unsigned char msg_font_2_22_38[1672UL] =
{
    0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10,
    0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10,
    0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x8E, 0x73, 0x8E, 0x73, 0x8E, 0x73, 0xA6, 0x31, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10,
    0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x92, 0x94, 0x38, 0xC6, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x5C, 0xE7,
    0xD7, 0xBD, 0x69, 0x4A, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0xA6, 0x31, 0x9A, 0xD6, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF3, 0x9C, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0xA6, 0x31, 0xFB, 0xDE, 0xFF, 0xFF, 0xFF, 0xFF, 0x9A, 0xD6, 0x10, 0x84, 0xA6, 0x31,
    0x82, 0x10, 0x82, 0x10, 0xEC, 0x62, 0xF3, 0x9C, 0x9E, 0xF7, 0xFF, 0xFF, 0xFF, 0xFF, 0xF3, 0x9C, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0xD7, 0xBD, 0xFF, 0xFF, 0xFF, 0xFF, 0xF3, 0x9C, 0x82, 0x10,
    0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0xA6, 0x31, 0xFB, 0xDE, 0xFF, 0xFF, 0xFF, 0xFF, 0x69, 0x4A, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x69, 0x4A, 0xFF, 0xFF, 0xFF, 0xFF, 0x75, 0xAD,
    0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0xA6, 0x31, 0x9E, 0xF7, 0xFF, 0xFF, 0xF3, 0x9C, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x75, 0xAD, 0xFF, 0xFF,
    0x9E, 0xF7, 0xA6, 0x31, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x75, 0xAD, 0xFF, 0xFF, 0x9A, 0xD6, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10,
    0x9A, 0xD6, 0xFF, 0xFF, 0x75, 0xAD, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x10, 0x84, 0xFF, 0xFF, 0xFF, 0xFF, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10,
    0x82, 0x10, 0x82, 0x10, 0xFF, 0xFF, 0xFF, 0xFF, 0x10, 0x84, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x8E, 0x73, 0xFF, 0xFF, 0xFF, 0xFF, 0x82, 0x10,
    0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x8E, 0x73, 0x8E, 0x73, 0xA6, 0x31, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x8E, 0x73, 0xFF, 0xFF,
    0xFF, 0xFF, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10,
    0xF3, 0x9C, 0xFF, 0xFF, 0xFB, 0xDE, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10,
    0x82, 0x10, 0x82, 0x10, 0x38, 0xC6, 0xFF, 0xFF, 0xD7, 0xBD, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10,
    0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x69, 0x4A, 0xFF, 0xFF, 0xFF, 0xFF, 0x92, 0x94, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10,
    0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x38, 0xC6, 0xFF, 0xFF, 0x9E, 0xF7, 0xA6, 0x31, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10,
    0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x10, 0x84, 0xFF, 0xFF, 0xFF, 0xFF, 0xF3, 0x9C, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10,
    0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x69, 0x4A, 0x9E, 0xF7, 0xFF, 0xFF, 0x5C, 0xE7, 0xA6, 0x31, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10,
    0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0xFB, 0xDE, 0xFF, 0xFF, 0xFF, 0xFF, 0xEC, 0x62, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10,
    0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0xD7, 0xBD, 0xFF, 0xFF, 0xFF, 0xFF, 0xF3, 0x9C, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10,
    0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x92, 0x94, 0xFF, 0xFF, 0xFF, 0xFF, 0x38, 0xC6, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10,
    0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0xEC, 0x62, 0xFF, 0xFF, 0xFF, 0xFF, 0x5C, 0xE7, 0xA6, 0x31, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10,
    0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x69, 0x4A, 0x9E, 0xF7, 0xFF, 0xFF, 0x9E, 0xF7, 0xEC, 0x62, 0x82, 0x10, 0x82, 0x10,
    0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0xA6, 0x31, 0xFB, 0xDE, 0xFF, 0xFF, 0xFF, 0xFF, 0x10, 0x84, 0x82, 0x10,
    0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x38, 0xC6, 0xFF, 0xFF, 0xFF, 0xFF, 0xF3, 0x9C,
    0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0xD7, 0xBD, 0xFF, 0xFF, 0xFF, 0xFF,
    0xD7, 0xBD, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x92, 0x94, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFB, 0xDE, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0xEC, 0x62,
    0xFF, 0xFF, 0xFF, 0xFF, 0x5C, 0xE7, 0xA6, 0x31, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10,
    0xA6, 0x31, 0x5C, 0xE7, 0xFF, 0xFF, 0x9E, 0xF7, 0xEC, 0x62, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10,
    0x82, 0x10, 0x82, 0x10, 0x9A, 0xD6, 0xFF, 0xFF, 0xFF, 0xFF, 0x10, 0x84, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10,
    0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0xF3, 0x9C, 0xFF, 0xFF, 0xFF, 0xFF, 0xF3, 0x9C, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10,
    0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x10, 0x84, 0xFF, 0xFF, 0xFF, 0xFF, 0xD7, 0xBD, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10,
    0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x69, 0x4A, 0x9E, 0xF7, 0xFF, 0xFF, 0x9E, 0xF7, 0x8E, 0x73, 0x8E, 0x73, 0x8E, 0x73, 0x8E, 0x73, 0x8E, 0x73, 0x8E, 0x73, 0x8E, 0x73, 0x8E, 0x73, 0x8E, 0x73, 0x8E, 0x73, 0x8E, 0x73,
    0x8E, 0x73, 0x8E, 0x73, 0x8E, 0x73, 0x8E, 0x73, 0xA6, 0x31, 0x82, 0x10, 0x82, 0x10, 0x10, 0x84, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x8E, 0x73, 0x82, 0x10, 0x82, 0x10, 0xA6, 0x31, 0x9A, 0xD6, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x8E, 0x73, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10,
    0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10,
    0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10,
    0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10
};

image_info_t msg_font_2_info =
{
    .type  = IMG_TYPE_RAW,
    .pixel = RTGRAPHIC_PIXEL_FORMAT_RGB565,
    .x = 0,
    .y = 0,
    .w = 22,
    .h = 38,
    .size = 1672UL,
    .data = msg_font_2_22_38,
};

#endif
