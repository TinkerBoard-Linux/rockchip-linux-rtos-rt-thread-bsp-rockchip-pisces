/**
  * Copyright (c) 2019 Fuzhou Rockchip Electronics Co., Ltd
  *
  * SPDX-License-Identifier: Apache-2.0
  */

#include <rtthread.h>
#if defined(OLPC_APP_SRCSAVER_ENABLE)
#include "image_info.h"

static const unsigned char screen_dog5_320_240[232UL] =
{
    0xAB, 0xF2, 0x8B, 0x9F, 0xC8, 0x9F, 0x00, 0x92, 0xF9, 0xD2, 0x5C, 0xEA, 0xFF, 0x70, 0xB1, 0xBB, 0x34, 0x46, 0x91, 0xFA, 0xC3, 0x46, 0x4C, 0x93, 0x2C, 0xE8, 0x67, 0xB0, 0xA8, 0x29, 0x3E, 0x45, 0x0B, 0xA7, 0xF8, 0x64, 0xBE, 0xA9, 0x21, 0xFE,
    0x3F, 0xE7, 0x92, 0xC4, 0x20, 0x5C, 0x19, 0x6E, 0x28, 0x42, 0x1D, 0x84, 0x96, 0xF7, 0x85, 0x5E, 0xFE, 0x8B, 0x20, 0xF9, 0x72, 0x55, 0xB9, 0xF2, 0x89, 0xE1, 0x66, 0xC9, 0xBA, 0x01, 0x1B, 0x22, 0x06, 0xC4, 0x73, 0x7F, 0xC4, 0x7D, 0xBD, 0xB4,
    0xD9, 0x6A, 0x56, 0x23, 0x2E, 0xBB, 0x2C, 0xE7, 0x36, 0xCB, 0xA4, 0x7B, 0xC3, 0xFC, 0xC0, 0x6E, 0x89, 0x9B, 0x56, 0x97, 0xD6, 0x99, 0x0D, 0xE1, 0x62, 0xFD, 0x41, 0xA5, 0x2D, 0x96, 0xDD, 0xED, 0xD7, 0xE4, 0xC9, 0x2B, 0xEC, 0xB3, 0x47, 0x7B,
    0x88, 0x6D, 0x1A, 0x25, 0x6A, 0x5E, 0x2D, 0x8C, 0x8D, 0xFA, 0xF6, 0xB0, 0x03, 0x53, 0x2B, 0x90, 0xAA, 0x0D, 0xDB, 0x71, 0x2D, 0xAC, 0xBF, 0xA5, 0xB3, 0x00, 0x24, 0x39, 0x02, 0xB7, 0x1C, 0xDE, 0xC1, 0x81, 0x49, 0x1F, 0xCD, 0x34, 0xE6, 0xCD,
    0xB6, 0x1C, 0x2F, 0x99, 0x09, 0x47, 0xBE, 0x7B, 0x49, 0xCF, 0x48, 0xBD, 0x52, 0xE3, 0xCD, 0xD9, 0x79, 0xBE, 0x58, 0x56, 0x55, 0xC9, 0x8F, 0x5D, 0xDF, 0x1E, 0x0D, 0x7E, 0x2C, 0x45, 0x05, 0x4E, 0xCC, 0x9D, 0x0D, 0x22, 0xDA, 0x58, 0x5B, 0x9E,
    0x8C, 0xAC, 0x73, 0x51, 0x72, 0x9D, 0xBA, 0xA6, 0x42, 0x71, 0x72, 0x6A, 0xE4, 0xFB, 0x98, 0xCD, 0x7E, 0xF0, 0x80, 0x61, 0x6B, 0x48, 0xD9, 0xBB, 0x1B, 0x8A, 0x12, 0x22, 0x9B, 0x1F, 0xFF, 0xAC
};

image_info_t screen_dog5_info =
{
    .type  = IMG_TYPE_COMPRESS,
    .pixel = RTGRAPHIC_PIXEL_FORMAT_GRAY1,
    .x = 0,
    .y = 0,
    .w = 320,
    .h = 240,
    .size = 232UL,
    .data = screen_dog5_320_240,
};

#endif
