/**
  * Copyright (c) 2019 Fuzhou Rockchip Electronics Co., Ltd
  *
  * SPDX-License-Identifier: Apache-2.0
  */

#include <rtthread.h>
#if defined(OLPC_APP_BLOCK_ENABLE)
#include "applications/common/image_info.h"

static const unsigned char block_small1_22_22[66UL] =
{
    0xFF, 0xFF, 0xFC, 0xFF, 0xFF, 0xFC, 0xFF, 0xFF, 0xFC, 0xFF, 0xFF, 0xFC, 0xFF, 0xFF, 0xFC, 0xFF, 0xFF, 0xFC, 0xFF, 0xFF, 0xFC, 0xFF, 0xFF, 0xFC, 0xFF, 0xFF, 0xFC, 0xFF, 0xFF, 0xFC, 0xFF, 0xFF, 0xFC, 0xFF, 0xFF, 0xFC, 0xFF, 0xFF, 0xFC, 0xFF,
    0xFF, 0xFC, 0xFF, 0xFF, 0xFC, 0xFF, 0xFF, 0xFC, 0xFF, 0xFF, 0xFC, 0xFF, 0xFF, 0xFC, 0xFF, 0xFF, 0xFC, 0xFF, 0xFF, 0xFC, 0xFF, 0xFF, 0xFC, 0xFF, 0xFF, 0xFC
};

image_info_t block_small1_info =
{
    .type  = IMG_TYPE_RAW,
    .pixel = RTGRAPHIC_PIXEL_FORMAT_GRAY1,
    .x = 833,
    .y = 482,
    .w = 22,
    .h = 22,
    .size = 66UL,
    .data = block_small1_22_22,
};

#endif
