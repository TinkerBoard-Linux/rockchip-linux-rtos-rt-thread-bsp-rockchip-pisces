/**
  * Copyright (c) 2019 Fuzhou Rockchip Electronics Co., Ltd
  *
  * SPDX-License-Identifier: Apache-2.0
  */

#include <rtthread.h>
#if defined(OLPC_APP_SRCSAVER_ENABLE)
#include "applications/common/image_info.h"

static const unsigned char screen_dog1_320_240[229UL] =
{
    0xAB, 0xF4, 0xD0, 0x8F, 0xAF, 0x1E, 0x82, 0xD2, 0x6C, 0x34, 0xD1, 0xBE, 0x95, 0xE5, 0x49, 0x7E, 0xEE, 0xDC, 0x23, 0xF2, 0xE5, 0xAF, 0x12, 0xCA, 0x56, 0xDC, 0xB1, 0x5F, 0xFC, 0x58, 0x36, 0x53, 0x90, 0x9A, 0x48, 0x85, 0x42, 0xEB, 0xD6, 0x8E,
    0x1D, 0x46, 0xFD, 0xB2, 0xCD, 0xA5, 0xA7, 0xF4, 0xC4, 0x0A, 0xC2, 0xA3, 0xE9, 0x2C, 0x81, 0x4C, 0xBD, 0x49, 0x31, 0x81, 0xFE, 0xB8, 0x1F, 0x1A, 0x3E, 0x3B, 0xEE, 0xBA, 0x55, 0x70, 0xC1, 0x50, 0x35, 0x6B, 0x4E, 0xEA, 0x8A, 0xDF, 0x98, 0xD2,
    0xC7, 0x6B, 0xA6, 0x26, 0x6C, 0x69, 0x85, 0x61, 0x42, 0x32, 0x6F, 0xB1, 0x2D, 0xB6, 0x83, 0xB5, 0x59, 0x2C, 0xF5, 0x69, 0xEE, 0x9E, 0xA0, 0x7B, 0xC7, 0xEE, 0x1E, 0x92, 0x78, 0xC7, 0x16, 0x54, 0xDB, 0xA5, 0x4F, 0x63, 0x30, 0xFC, 0x53, 0x33,
    0x61, 0x74, 0xB4, 0x69, 0x10, 0x99, 0x38, 0x81, 0x4F, 0x70, 0xAA, 0x47, 0xA3, 0xA0, 0xF0, 0x03, 0x42, 0xF2, 0x52, 0x98, 0xC1, 0xA4, 0x58, 0x5E, 0x09, 0x3C, 0x84, 0x39, 0xF1, 0xB1, 0x07, 0x54, 0x61, 0x9C, 0x0B, 0x7C, 0xB9, 0x9B, 0x90, 0x28,
    0x77, 0xC7, 0x51, 0xC8, 0x77, 0x7D, 0xBB, 0xC7, 0xD5, 0x95, 0xC4, 0x22, 0x84, 0x89, 0x85, 0x5A, 0xFC, 0x59, 0x1A, 0x50, 0xB4, 0xBF, 0x3B, 0x9A, 0x83, 0x04, 0xCC, 0x4A, 0xD4, 0x3F, 0x1A, 0xA4, 0xD4, 0xF0, 0xEF, 0xC9, 0x6D, 0xA5, 0x5A, 0x42,
    0x4B, 0x27, 0xB7, 0x60, 0x08, 0x81, 0xA0, 0xC7, 0x98, 0x4B, 0x78, 0x11, 0x6F, 0x1E, 0x61, 0xE4, 0x5A, 0xD6, 0xF0, 0x70, 0xD9, 0x34, 0x19, 0x46, 0x0F, 0x2B, 0x6F, 0xFF, 0xAC
};

image_info_t screen_dog1_info =
{
    .type  = IMG_TYPE_COMPRESS,
    .pixel = RTGRAPHIC_PIXEL_FORMAT_GRAY1,
    .x = 0,
    .y = 0,
    .w = 320,
    .h = 240,
    .size = 229UL,
    .data = screen_dog1_320_240,
};

#endif
