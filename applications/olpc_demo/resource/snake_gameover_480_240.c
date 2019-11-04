/**
  * Copyright (c) 2019 Fuzhou Rockchip Electronics Co., Ltd
  *
  * SPDX-License-Identifier: Apache-2.0
  */

#include <rtthread.h>
#if defined(OLPC_APP_SNAKE_ENABLE)
#include "image_info.h"

static const unsigned char snake_gameover_480_240[440UL] =
{
    0xFC, 0xA5, 0xA4, 0x63, 0x83, 0x2A, 0x3C, 0xE6, 0xEB, 0xF7, 0xD5, 0x47, 0x36, 0xE8, 0xCC, 0x67, 0xF0, 0xC4, 0x92, 0x54, 0x6D, 0xBF, 0xAC, 0x37, 0x6B, 0xE4, 0x75, 0x42, 0x9D, 0x03, 0x58, 0xBD, 0x48, 0xFC, 0x33, 0x6E, 0x18, 0x23, 0x70, 0x11,
    0xAC, 0x61, 0x53, 0x12, 0xC1, 0x9F, 0x9A, 0x75, 0xA2, 0xF7, 0xA4, 0x06, 0x99, 0x2C, 0xE3, 0x4A, 0x16, 0x70, 0xCE, 0xF9, 0xA4, 0xDF, 0xE0, 0x3E, 0xE7, 0x6F, 0x5F, 0xE5, 0xA2, 0x0F, 0x91, 0x33, 0xA8, 0xC8, 0x5A, 0x10, 0x8C, 0x7A, 0x9F, 0x66,
    0xFF, 0x7F, 0xFF, 0x7F, 0xFF, 0x7F, 0xFF, 0x7F, 0xFF, 0x7D, 0x44, 0xEF, 0x30, 0xB5, 0x74, 0xE5, 0x84, 0x53, 0x2F, 0x04, 0x3B, 0xF2, 0x18, 0xAD, 0x5A, 0xCD, 0xEE, 0x75, 0x08, 0x58, 0xB5, 0x74, 0xD1, 0x96, 0x43, 0x9A, 0xAE, 0x82, 0xEF, 0xC3,
    0x63, 0xFF, 0x53, 0x89, 0x62, 0x9F, 0x35, 0x5A, 0x85, 0x38, 0xDD, 0x77, 0x20, 0x5E, 0x9E, 0x1F, 0x36, 0x91, 0x58, 0x8D, 0x9F, 0x0B, 0x7D, 0xE2, 0xE6, 0xF5, 0x69, 0x6A, 0xC2, 0xCB, 0x48, 0xB0, 0x67, 0x8B, 0x6C, 0xB0, 0xDB, 0xA9, 0xA8, 0x23,
    0xD4, 0xFB, 0xBA, 0xE1, 0x54, 0x45, 0xCA, 0xE4, 0x25, 0x95, 0xAC, 0x9E, 0x36, 0x14, 0x80, 0x14, 0x41, 0xE5, 0x9B, 0xA3, 0xE7, 0xF9, 0xC9, 0x8B, 0xF9, 0x89, 0xD0, 0x16, 0x34, 0x20, 0x9D, 0xB0, 0xB9, 0x2B, 0x74, 0xA2, 0x43, 0x81, 0xE6, 0x2B,
    0xA5, 0x29, 0xB6, 0xF8, 0x3A, 0xF3, 0xFD, 0x26, 0x22, 0x5E, 0x4B, 0x48, 0xA5, 0xA2, 0xD6, 0xED, 0xED, 0x30, 0x4C, 0x5F, 0x02, 0x85, 0x6F, 0x38, 0xFC, 0x1D, 0x37, 0x98, 0x29, 0xB0, 0x0A, 0xF8, 0xD9, 0x1E, 0xC1, 0x38, 0xF4, 0xC5, 0x75, 0x88,
    0xD4, 0x15, 0xE6, 0xCA, 0x98, 0x2B, 0xBD, 0x33, 0xA1, 0xA3, 0x3B, 0x73, 0xA7, 0xEB, 0xA7, 0xAB, 0x06, 0x4C, 0xEA, 0x61, 0xBF, 0xDB, 0x88, 0x19, 0x68, 0xA6, 0xF5, 0x6B, 0xFF, 0x19, 0xE6, 0xF7, 0xA9, 0xF7, 0x29, 0xB3, 0x54, 0xD0, 0xF4, 0xB1,
    0x93, 0x7D, 0x8F, 0x77, 0x08, 0xCE, 0x51, 0xC2, 0xA1, 0xE2, 0x44, 0x7F, 0x82, 0x2B, 0x77, 0x13, 0x0F, 0x1B, 0xF4, 0x4C, 0x44, 0x50, 0xB8, 0xB1, 0xF9, 0xDA, 0x27, 0x96, 0xC0, 0x00, 0x0A, 0xB6, 0xD6, 0xAB, 0x3A, 0x88, 0xBD, 0x14, 0x02, 0x1D,
    0xA8, 0xB9, 0x07, 0x40, 0xAB, 0xA2, 0x14, 0x2F, 0x48, 0x3A, 0x3E, 0x74, 0xFB, 0x35, 0xDA, 0xAE, 0x27, 0xD9, 0x59, 0xD6, 0xE1, 0x3B, 0xAD, 0x1B, 0xAD, 0x76, 0x6E, 0xF8, 0x27, 0xBE, 0x3D, 0xF1, 0xCE, 0x27, 0x8E, 0x0E, 0x2A, 0xD7, 0x17, 0x8D,
    0x84, 0x63, 0x0D, 0x7E, 0x1C, 0xCE, 0x3D, 0xAE, 0x92, 0x65, 0xF4, 0x19, 0xB2, 0x7A, 0x7D, 0x32, 0x16, 0x7F, 0xF0, 0xEC, 0xE9, 0xFF, 0x7F, 0xFF, 0x7F, 0xFF, 0x0F, 0xFD, 0x32, 0x96, 0x4D, 0xC6, 0x0B, 0xA1, 0x09, 0x8B, 0x90, 0x3D, 0x06, 0x74,
    0xD2, 0xD3, 0x7B, 0x35, 0x96, 0x08, 0xFF, 0x67, 0x19, 0xB9, 0xA5, 0xDE, 0xBA, 0x05, 0xF8, 0x11, 0xC3, 0x7A, 0x78, 0xD4, 0x82, 0x1F, 0xFD, 0xF0, 0x8B, 0xA0, 0xEC, 0xF8, 0x9B, 0xE6, 0x91, 0xAA, 0xD0, 0x45, 0x77, 0xDD, 0x21, 0xCB, 0xFF, 0xAC
};

image_info_t snake_gameover_info =
{
    .type  = IMG_TYPE_COMPRESS,
    .pixel = RTGRAPHIC_PIXEL_FORMAT_GRAY1,
    .x = 240,
    .y = 660,
    .w = 480,
    .h = 240,
    .size = 440UL,
    .data = snake_gameover_480_240,
};

#endif
