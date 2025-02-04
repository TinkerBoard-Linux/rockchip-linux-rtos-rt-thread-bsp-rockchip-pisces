/**
  * Copyright (c) 2019 Fuzhou Rockchip Electronics Co., Ltd
  *
  * SPDX-License-Identifier: Apache-2.0
  */

#include <rtthread.h>
#if defined(OLPC_APP_BLOCK_ENABLE)
#include "applications/common/image_info.h"

static const unsigned char block_ctrl_1056_360[328UL] =
{
    0xAB, 0xF2, 0x2B, 0xEF, 0xA9, 0xC4, 0x31, 0xC9, 0x6E, 0x24, 0x50, 0x0E, 0x77, 0x91, 0xA9, 0xFD, 0x88, 0x18, 0x42, 0x16, 0x2A, 0xB8, 0xA0, 0x6B, 0x50, 0x9D, 0x72, 0xE3, 0xC1, 0xA0, 0x8A, 0x47, 0xB5, 0xB9, 0xC9, 0x28, 0x85, 0x38, 0xAD, 0x79,
    0x23, 0x06, 0xD7, 0xCB, 0xB8, 0x44, 0x11, 0xE7, 0x1F, 0x9E, 0xBE, 0x6D, 0x7A, 0x4D, 0xD0, 0xDB, 0xEC, 0x68, 0xCE, 0x85, 0x8E, 0xA6, 0x39, 0x26, 0xA5, 0xBC, 0xCC, 0x97, 0xD4, 0xDD, 0x9C, 0x03, 0xC1, 0x2D, 0xD3, 0x7F, 0x29, 0xDD, 0xFA, 0xDB,
    0xF0, 0x8A, 0x0C, 0x23, 0x77, 0x9C, 0x42, 0xA4, 0x3B, 0x20, 0x7D, 0xB6, 0xC1, 0x03, 0x8F, 0x9D, 0xF7, 0x65, 0x2B, 0xDE, 0x28, 0x86, 0xFF, 0x55, 0xF8, 0xBC, 0x0D, 0x60, 0x0F, 0x8C, 0xCB, 0x61, 0x76, 0x55, 0xE5, 0xE8, 0xDE, 0x04, 0x46, 0x54,
    0x82, 0xFA, 0xB5, 0x67, 0x0B, 0xA2, 0x8E, 0x9B, 0xA3, 0x83, 0xED, 0xCF, 0xC5, 0xE1, 0xED, 0xA0, 0xC5, 0x22, 0x3F, 0xC5, 0x03, 0x59, 0xD4, 0x54, 0xA9, 0x99, 0xC2, 0x1B, 0x1A, 0x75, 0xFA, 0xA2, 0xE6, 0xDD, 0x7E, 0xAA, 0x30, 0x28, 0x48, 0x96,
    0x5B, 0x15, 0xA1, 0xA1, 0x86, 0x4C, 0x37, 0x6B, 0x12, 0x37, 0x61, 0xE7, 0x87, 0x36, 0xA7, 0xB6, 0x31, 0x17, 0x81, 0x3A, 0x8A, 0x74, 0x74, 0xFC, 0x92, 0x36, 0x0D, 0xBC, 0xD2, 0x08, 0xC8, 0x2C, 0x58, 0x3A, 0x81, 0x26, 0xCF, 0xE4, 0x2F, 0x2C,
    0x8E, 0x9A, 0xB5, 0x1A, 0xF0, 0x9A, 0x54, 0x04, 0x05, 0xC8, 0x1B, 0xB3, 0x4E, 0x7D, 0x35, 0x88, 0x3E, 0xDB, 0x7C, 0x47, 0xF0, 0x98, 0xE6, 0xB6, 0x7A, 0x92, 0x97, 0x12, 0xF8, 0x75, 0x5C, 0x16, 0x69, 0xB5, 0xC9, 0xF9, 0xEF, 0xAF, 0x54, 0x3B,
    0x2C, 0x72, 0x44, 0xF7, 0xFF, 0x20, 0x3B, 0x58, 0x7C, 0xF6, 0x65, 0x4B, 0xEB, 0x7B, 0x93, 0xBB, 0x46, 0xDB, 0x49, 0x52, 0x43, 0x9F, 0x2B, 0x15, 0x09, 0x40, 0xBB, 0xDA, 0x3E, 0x7A, 0xBE, 0xA2, 0x6C, 0xC4, 0x39, 0x3B, 0x7B, 0x86, 0x0D, 0xFC,
    0x01, 0x19, 0xB4, 0x03, 0x70, 0x3A, 0xD8, 0xBB, 0xFF, 0x7F, 0xFF, 0x7F, 0xFF, 0x7F, 0xFF, 0x7E, 0x67, 0xBD, 0xDB, 0x92, 0x3C, 0x87, 0x26, 0x25, 0xFF, 0x7F, 0xFF, 0x44, 0xF2, 0xF7, 0x3F, 0x53, 0x78, 0xB9, 0xF6, 0x61, 0x3A, 0xA7, 0xFF, 0x56,
    0x85, 0xD5, 0x53, 0xFF, 0x7F, 0x64, 0xFF, 0xAC
};

image_info_t block_ctrl_info =
{
    .type  = IMG_TYPE_COMPRESS,
    .pixel = RTGRAPHIC_PIXEL_FORMAT_GRAY1,
    .x = 0,
    .y = 0,
    .w = 1056,
    .h = 360,
    .size = 328UL,
    .data = block_ctrl_1056_360,
};

#endif
