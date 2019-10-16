/**
  * Copyright (c) 2019 Fuzhou Rockchip Electronics Co., Ltd
  *
  * SPDX-License-Identifier: Apache-2.0
  */

#include <rtthread.h>
#if defined(OLPC_APP_BLOCK_ENABLE)
#include "image_info.h"

static unsigned char block_exit1_81_81[88UL] =
{
    0xFE, 0xA4, 0x12, 0x1D, 0xFE, 0x31, 0x37, 0xB6, 0x70, 0x6E, 0xF1, 0xBB, 0xEC, 0xEE, 0xEC, 0xF9, 0x52, 0x05, 0xF8, 0xAB, 0x33, 0x70, 0x48, 0x41, 0xF0, 0x7C, 0x80, 0xB0, 0xF1, 0x00, 0x3C, 0x2A, 0x00, 0xE4, 0x83, 0x55, 0xB4, 0xA7, 0xB2, 0x46,
    0x10, 0x05, 0xF7, 0x41, 0x62, 0xDE, 0x94, 0x05, 0x87, 0x4C, 0x1E, 0x3F, 0xC2, 0x64, 0x7D, 0x2B, 0x32, 0xBF, 0x6D, 0x0D, 0x3E, 0x0C, 0xD0, 0xEC, 0xC6, 0x3E, 0xB0, 0x8E, 0x94, 0x5B, 0x2B, 0x7D, 0x79, 0xF4, 0xD8, 0x43, 0x0C, 0x93, 0x14, 0x74,
    0x25, 0x87, 0x32, 0xDA, 0xC1, 0x20, 0xFF, 0xAC
};

image_info_t block_exit1_info =
{
    .type  = IMG_TYPE_COMPRESS,
    .pixel = RTGRAPHIC_PIXEL_FORMAT_GRAY1,
    .x = 610,
    .y = 13,
    .w = 81,
    .h = 81,
    .size = 88UL,
    .data = block_exit1_81_81,
};

#endif
