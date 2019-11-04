/**
  * Copyright (c) 2019 Fuzhou Rockchip Electronics Co., Ltd
  *
  * SPDX-License-Identifier: Apache-2.0
  */

#include <rtthread.h>
#if defined(OLPC_APP_SRCSAVER_ENABLE)
#include "image_info.h"

static const unsigned char screen_dog3_320_240[252UL] =
{
    0xAB, 0xF2, 0xE0, 0x98, 0x10, 0xB1, 0xB2, 0x32, 0xCF, 0xF4, 0x32, 0x9C, 0x39, 0x4C, 0x2A, 0x62, 0x84, 0xA3, 0xCE, 0x16, 0xC4, 0x6F, 0x6C, 0xC8, 0xD9, 0x27, 0xDA, 0x21, 0x5B, 0x68, 0xB6, 0x41, 0xB0, 0x41, 0x84, 0x81, 0xCE, 0x2C, 0x43, 0xE4,
    0x65, 0x5F, 0x3F, 0x08, 0xD8, 0xD0, 0x58, 0x68, 0x4D, 0xAE, 0xDB, 0xF6, 0x32, 0x23, 0x03, 0x8A, 0x51, 0xD6, 0x5E, 0xA3, 0x59, 0x82, 0x0C, 0x78, 0xB2, 0x0E, 0x76, 0x77, 0x51, 0xA7, 0xFE, 0x9C, 0x20, 0x67, 0x62, 0xF3, 0x80, 0xFA, 0x8A, 0x15,
    0x15, 0x50, 0xCB, 0x09, 0x4A, 0x04, 0x68, 0x84, 0x0C, 0x6C, 0x3E, 0x64, 0x33, 0xCC, 0xD0, 0x98, 0xCE, 0x9B, 0x0B, 0xDA, 0xED, 0x95, 0xF8, 0xC4, 0x02, 0x7B, 0xB7, 0x51, 0x7C, 0xB0, 0xCE, 0xD7, 0x94, 0x85, 0x7E, 0x89, 0x6B, 0xB6, 0x00, 0x87,
    0x7B, 0x0E, 0xB9, 0x47, 0xE0, 0x89, 0xCC, 0x99, 0xC6, 0xEE, 0xF2, 0x5F, 0xE2, 0xF6, 0x04, 0xAF, 0x76, 0x4D, 0x99, 0xEF, 0x44, 0x1E, 0xBB, 0x82, 0xE4, 0x7A, 0xA0, 0x69, 0x99, 0x9C, 0x3A, 0x23, 0x27, 0x67, 0x4E, 0x7F, 0x68, 0x42, 0x0F, 0x85,
    0xC1, 0x89, 0x54, 0x1B, 0xFD, 0xD3, 0x7E, 0x91, 0x60, 0xB6, 0x71, 0xE1, 0x7F, 0x1A, 0x48, 0xCF, 0x65, 0x24, 0x2C, 0x65, 0xB9, 0xEE, 0x4A, 0xF0, 0xAA, 0xBE, 0xC5, 0x78, 0x5F, 0x1B, 0x04, 0xF3, 0x67, 0xA5, 0xB8, 0x95, 0xE1, 0x70, 0x45, 0xC2,
    0x0E, 0x35, 0x6A, 0xFF, 0x13, 0x33, 0x35, 0x0B, 0x2A, 0x1E, 0x49, 0x17, 0xAF, 0x85, 0xE1, 0x77, 0x2D, 0x50, 0x95, 0xF7, 0x66, 0xB2, 0x97, 0x56, 0x23, 0x72, 0xE6, 0x90, 0xAA, 0xAF, 0x68, 0xF5, 0x4D, 0xB7, 0xF0, 0xDF, 0xC2, 0x24, 0x88, 0x82,
    0xB9, 0xD2, 0xB2, 0xB9, 0x08, 0xC6, 0x67, 0xA0, 0xC8, 0x9F, 0xFF, 0xAC
};

image_info_t screen_dog3_info =
{
    .type  = IMG_TYPE_COMPRESS,
    .pixel = RTGRAPHIC_PIXEL_FORMAT_GRAY1,
    .x = 0,
    .y = 0,
    .w = 320,
    .h = 240,
    .size = 252UL,
    .data = screen_dog3_320_240,
};

#endif
