/**
  * Copyright (c) 2019 Fuzhou Rockchip Electronics Co., Ltd
  *
  * SPDX-License-Identifier: Apache-2.0
  */

#include <rtthread.h>
#if defined(OLPC_APP_BLOCK_ENABLE)
#include "applications/common/image_info.h"

static const unsigned char block_small0_22_22[66UL] =
{
    0xC0, 0x00, 0x0C, 0x80, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0xFC, 0x00, 0x01, 0xFE, 0x00, 0x01, 0xFE, 0x00, 0x01, 0xFE, 0x00, 0x01, 0xFE, 0x00, 0x00,
    0xFC, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x04, 0xC0, 0x00, 0x0C
};

image_info_t block_small0_info =
{
    .type  = IMG_TYPE_RAW,
    .pixel = RTGRAPHIC_PIXEL_FORMAT_GRAY1,
    .x = 833,
    .y = 482,
    .w = 22,
    .h = 22,
    .size = 66UL,
    .data = block_small0_22_22,
};

#endif
