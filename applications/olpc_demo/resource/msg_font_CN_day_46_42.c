/**
  * Copyright (c) 2019 Fuzhou Rockchip Electronics Co., Ltd
  *
  * SPDX-License-Identifier: Apache-2.0
  */

#include <rtthread.h>
#include "image_info.h"

#if (defined(OLPC_APP_CLOCK_STYLE_ROUND_ROMAN332) || defined(OLPC_APP_CLOCK_STYLE_ROUND_ARABIC)) && (defined(OLPC_STATICLD_ENABLE) || defined(OLPC_OVERLAY_ENABLE))
// RGB332
static const unsigned char msg_font_CN_day_46_42[1932UL] =
{
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xDA, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x92, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xDA, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x92, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xDA, 0xFF, 0xDB, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0xDB, 0xFF, 0x92, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xDA, 0xFF, 0xDA, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xDA, 0xFF, 0x92, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xDA, 0xFF, 0xDA, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xDA, 0xFF, 0x92, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xDA, 0xFF, 0xDA, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0xDA, 0xFF, 0x92, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xDA, 0xFF, 0xDA, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xDA, 0xFF, 0x92, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xDA, 0xFF, 0xDA, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xDA, 0xFF, 0x92, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xDA, 0xFF, 0xDA, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xDA, 0xFF, 0x92, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0xDA, 0xFF, 0xDA, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xDA, 0xFF, 0x92, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xDA, 0xFF, 0xDA, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xDA, 0xFF, 0x92, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xDA, 0xFF, 0xDA, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xDA, 0xFF,
    0x92, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xDA, 0xFF, 0xDA, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0xDA, 0xFF, 0x92, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xDA, 0xFF, 0xDA, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xDA, 0xFF, 0x92, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xDA, 0xFF, 0xDA, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xDA, 0xFF, 0x92, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xDA, 0xFF,
    0xDB, 0x6D, 0x6D, 0x6D, 0x6D, 0x6D, 0x6D, 0x6D, 0x6D, 0x6D, 0x6D, 0x6D, 0x6D, 0x6D, 0x6D, 0x6D, 0x6D, 0x6D, 0x6D, 0x6D, 0x6D, 0x6D, 0xDB, 0xFF, 0x92, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0xDA, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x92, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xDA, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x92, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xDA, 0xFF, 0xDB, 0x6D, 0x6D, 0x6D, 0x6D, 0x6D, 0x6D, 0x6D, 0x6D, 0x6D, 0x6D, 0x6D, 0x6D, 0x6D, 0x6D, 0x6D, 0x6D, 0x6D, 0x6D, 0x6D, 0x6D, 0x6D,
    0xDB, 0xFF, 0x92, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xDA, 0xFF, 0xDA, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xDA, 0xFF, 0x92, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xDA, 0xFF, 0xDA, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xDA, 0xFF, 0x92, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xDA, 0xFF, 0xDA, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xDA, 0xFF, 0x92, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xDA, 0xFF, 0xDA, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xDA, 0xFF, 0x92, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xDA, 0xFF, 0xDA, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xDA, 0xFF, 0x92, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xDA, 0xFF, 0xDA, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xDA, 0xFF, 0x92, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xDA, 0xFF, 0xDA, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0xDA, 0xFF, 0x92, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xDA, 0xFF, 0xDA, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xDA, 0xFF, 0x92, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xDA, 0xFF, 0xDA, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xDA, 0xFF, 0x92, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xDA, 0xFF, 0xDA, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xDA, 0xFF, 0x92, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0xDA, 0xFF, 0xDA, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xDA, 0xFF, 0x92, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xDA, 0xFF, 0xDA, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xDA, 0xFF, 0x92, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xDA, 0xFF, 0xDA, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xDA, 0xFF,
    0x92, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xDA, 0xFF, 0xFF, 0xDA, 0xDA, 0xDA, 0xDA, 0xDA, 0xDA, 0xDA, 0xDA, 0xDA, 0xDA, 0xDA, 0xDA, 0xDA, 0xDA, 0xDA, 0xDA, 0xDA,
    0xDA, 0xDA, 0xDA, 0xDA, 0xFF, 0xFF, 0x92, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xDA, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x92, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xDA, 0xFF, 0xDB, 0x92, 0x92, 0x92, 0x92, 0x92,
    0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0xDB, 0xFF, 0x92, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xDA, 0xFF,
    0xDA, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xDA, 0xFF, 0x92, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0xDA, 0xFF, 0xDA, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xDA, 0xFF, 0x92, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xDA, 0xFF, 0xDA, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xDA, 0xFF, 0x92, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x6D, 0x6D, 0x6D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

image_info_t msg_font_CHN_day_info =
{
    .type  = IMG_TYPE_RAW,
    .pixel = RTGRAPHIC_PIXEL_FORMAT_RGB332,
    .x = 0,
    .y = 0,
    .w = 46,
    .h = 42,
    .size = 1932,
    .data = msg_font_CN_day_46_42,
};

#elif defined(OLPC_APP_CLOCK_STYLE_ROUND_ROMAN565) && (defined(OLPC_STATICLD_ENABLE) || defined(OLPC_OVERLAY_ENABLE))
// RGB565
static const unsigned char msg_font_CN_day_46_42[3864UL] =
{
    0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10,
    0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10,
    0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10,
    0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10,
    0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10,
    0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10,
    0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10,
    0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x9A, 0xD6, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF3, 0x9C, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10,
    0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x9A, 0xD6, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xF3, 0x9C, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10,
    0x9A, 0xD6, 0xFF, 0xFF, 0x5C, 0xE7, 0xF3, 0x9C, 0xF3, 0x9C, 0xF3, 0x9C, 0xF3, 0x9C, 0xF3, 0x9C, 0xF3, 0x9C, 0xF3, 0x9C, 0xF3, 0x9C, 0xF3, 0x9C, 0xF3, 0x9C, 0xF3, 0x9C, 0xF3, 0x9C, 0xF3, 0x9C, 0xF3, 0x9C, 0xF3, 0x9C, 0xF3, 0x9C, 0xF3, 0x9C,
    0xF3, 0x9C, 0xF3, 0x9C, 0xF3, 0x9C, 0xF3, 0x9C, 0x5C, 0xE7, 0xFF, 0xFF, 0xF3, 0x9C, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10,
    0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x9A, 0xD6, 0xFF, 0xFF, 0x9A, 0xD6, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10,
    0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x9A, 0xD6, 0xFF, 0xFF, 0xF3, 0x9C, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10,
    0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x9A, 0xD6, 0xFF, 0xFF, 0x9A, 0xD6, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10,
    0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x9A, 0xD6, 0xFF, 0xFF, 0xF3, 0x9C, 0x82, 0x10,
    0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x9A, 0xD6, 0xFF, 0xFF,
    0x9A, 0xD6, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10,
    0x82, 0x10, 0x82, 0x10, 0x9A, 0xD6, 0xFF, 0xFF, 0xF3, 0x9C, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10,
    0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x9A, 0xD6, 0xFF, 0xFF, 0x9A, 0xD6, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10,
    0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x9A, 0xD6, 0xFF, 0xFF, 0xF3, 0x9C, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10,
    0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x9A, 0xD6, 0xFF, 0xFF, 0x9A, 0xD6, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10,
    0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x9A, 0xD6, 0xFF, 0xFF, 0xF3, 0x9C, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10,
    0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x9A, 0xD6, 0xFF, 0xFF, 0x9A, 0xD6, 0x82, 0x10,
    0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10,
    0x9A, 0xD6, 0xFF, 0xFF, 0xF3, 0x9C, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10,
    0x82, 0x10, 0x82, 0x10, 0x9A, 0xD6, 0xFF, 0xFF, 0x9A, 0xD6, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10,
    0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x9A, 0xD6, 0xFF, 0xFF, 0xF3, 0x9C, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10,
    0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x9A, 0xD6, 0xFF, 0xFF, 0x9A, 0xD6, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10,
    0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x9A, 0xD6, 0xFF, 0xFF, 0xF3, 0x9C, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10,
    0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x9A, 0xD6, 0xFF, 0xFF, 0x9A, 0xD6, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10,
    0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x9A, 0xD6, 0xFF, 0xFF,
    0xF3, 0x9C, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10,
    0x9A, 0xD6, 0xFF, 0xFF, 0x9A, 0xD6, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10,
    0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x9A, 0xD6, 0xFF, 0xFF, 0xF3, 0x9C, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10,
    0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x9A, 0xD6, 0xFF, 0xFF, 0x9A, 0xD6, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10,
    0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x9A, 0xD6, 0xFF, 0xFF, 0xF3, 0x9C, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10,
    0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x9A, 0xD6, 0xFF, 0xFF, 0x9A, 0xD6, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10,
    0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x9A, 0xD6, 0xFF, 0xFF, 0xF3, 0x9C, 0x82, 0x10,
    0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x9A, 0xD6, 0xFF, 0xFF,
    0xFB, 0xDE, 0x8E, 0x73, 0x8E, 0x73, 0x8E, 0x73, 0x8E, 0x73, 0x8E, 0x73, 0x8E, 0x73, 0x8E, 0x73, 0x8E, 0x73, 0x8E, 0x73, 0x8E, 0x73, 0x8E, 0x73, 0x8E, 0x73, 0x8E, 0x73, 0x8E, 0x73, 0x8E, 0x73, 0x8E, 0x73, 0x8E, 0x73, 0x8E, 0x73, 0x8E, 0x73,
    0x8E, 0x73, 0x8E, 0x73, 0xFB, 0xDE, 0xFF, 0xFF, 0xF3, 0x9C, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10,
    0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x9A, 0xD6, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF3, 0x9C, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10,
    0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x9A, 0xD6, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF3, 0x9C, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10,
    0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x9A, 0xD6, 0xFF, 0xFF, 0xFB, 0xDE, 0x8E, 0x73,
    0x8E, 0x73, 0x8E, 0x73, 0x8E, 0x73, 0x8E, 0x73, 0x8E, 0x73, 0x8E, 0x73, 0x8E, 0x73, 0x8E, 0x73, 0x8E, 0x73, 0x8E, 0x73, 0x8E, 0x73, 0x8E, 0x73, 0x8E, 0x73, 0x8E, 0x73, 0x8E, 0x73, 0x8E, 0x73, 0x8E, 0x73, 0x8E, 0x73, 0x8E, 0x73, 0x8E, 0x73,
    0xFB, 0xDE, 0xFF, 0xFF, 0xF3, 0x9C, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10,
    0x82, 0x10, 0x82, 0x10, 0x9A, 0xD6, 0xFF, 0xFF, 0x9A, 0xD6, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10,
    0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x9A, 0xD6, 0xFF, 0xFF, 0xF3, 0x9C, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10,
    0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x9A, 0xD6, 0xFF, 0xFF, 0x9A, 0xD6, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10,
    0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x9A, 0xD6, 0xFF, 0xFF, 0xF3, 0x9C, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10,
    0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x9A, 0xD6, 0xFF, 0xFF, 0x9A, 0xD6, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10,
    0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x9A, 0xD6, 0xFF, 0xFF,
    0xF3, 0x9C, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10,
    0x9A, 0xD6, 0xFF, 0xFF, 0x9A, 0xD6, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10,
    0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x9A, 0xD6, 0xFF, 0xFF, 0xF3, 0x9C, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10,
    0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x9A, 0xD6, 0xFF, 0xFF, 0x9A, 0xD6, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10,
    0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x9A, 0xD6, 0xFF, 0xFF, 0xF3, 0x9C, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10,
    0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x9A, 0xD6, 0xFF, 0xFF, 0x9A, 0xD6, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10,
    0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x9A, 0xD6, 0xFF, 0xFF, 0xF3, 0x9C, 0x82, 0x10,
    0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x9A, 0xD6, 0xFF, 0xFF,
    0x9A, 0xD6, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10,
    0x82, 0x10, 0x82, 0x10, 0x9A, 0xD6, 0xFF, 0xFF, 0xF3, 0x9C, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10,
    0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x9A, 0xD6, 0xFF, 0xFF, 0x9A, 0xD6, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10,
    0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x9A, 0xD6, 0xFF, 0xFF, 0xF3, 0x9C, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10,
    0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x9A, 0xD6, 0xFF, 0xFF, 0x9A, 0xD6, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10,
    0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x9A, 0xD6, 0xFF, 0xFF, 0xF3, 0x9C, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10,
    0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x9A, 0xD6, 0xFF, 0xFF, 0x9A, 0xD6, 0x82, 0x10,
    0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10,
    0x9A, 0xD6, 0xFF, 0xFF, 0xF3, 0x9C, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10,
    0x82, 0x10, 0x82, 0x10, 0x9A, 0xD6, 0xFF, 0xFF, 0x9A, 0xD6, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10,
    0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x9A, 0xD6, 0xFF, 0xFF, 0xF3, 0x9C, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10,
    0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x9A, 0xD6, 0xFF, 0xFF, 0x9A, 0xD6, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10,
    0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x9A, 0xD6, 0xFF, 0xFF, 0xF3, 0x9C, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10,
    0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x9A, 0xD6, 0xFF, 0xFF, 0x9A, 0xD6, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10,
    0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x9A, 0xD6, 0xFF, 0xFF,
    0xF3, 0x9C, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10,
    0x9A, 0xD6, 0xFF, 0xFF, 0x9E, 0xF7, 0x9A, 0xD6, 0x9A, 0xD6, 0x9A, 0xD6, 0x9A, 0xD6, 0x9A, 0xD6, 0x9A, 0xD6, 0x9A, 0xD6, 0x9A, 0xD6, 0x9A, 0xD6, 0x9A, 0xD6, 0x9A, 0xD6, 0x9A, 0xD6, 0x9A, 0xD6, 0x9A, 0xD6, 0x9A, 0xD6, 0x9A, 0xD6, 0x9A, 0xD6,
    0x9A, 0xD6, 0x9A, 0xD6, 0x9A, 0xD6, 0x9A, 0xD6, 0x9E, 0xF7, 0xFF, 0xFF, 0xF3, 0x9C, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10,
    0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x9A, 0xD6, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF3, 0x9C, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10,
    0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x9A, 0xD6, 0xFF, 0xFF, 0x5C, 0xE7, 0xF3, 0x9C, 0xF3, 0x9C, 0xF3, 0x9C, 0xF3, 0x9C, 0xF3, 0x9C,
    0xF3, 0x9C, 0xF3, 0x9C, 0xF3, 0x9C, 0xF3, 0x9C, 0xF3, 0x9C, 0xF3, 0x9C, 0xF3, 0x9C, 0xF3, 0x9C, 0xF3, 0x9C, 0xF3, 0x9C, 0xF3, 0x9C, 0xF3, 0x9C, 0xF3, 0x9C, 0xF3, 0x9C, 0xF3, 0x9C, 0xF3, 0x9C, 0x5C, 0xE7, 0xFF, 0xFF, 0xF3, 0x9C, 0x82, 0x10,
    0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x9A, 0xD6, 0xFF, 0xFF,
    0x9A, 0xD6, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10,
    0x82, 0x10, 0x82, 0x10, 0x9A, 0xD6, 0xFF, 0xFF, 0xF3, 0x9C, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10,
    0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x9A, 0xD6, 0xFF, 0xFF, 0x9A, 0xD6, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10,
    0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x9A, 0xD6, 0xFF, 0xFF, 0xF3, 0x9C, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10,
    0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x9A, 0xD6, 0xFF, 0xFF, 0x9A, 0xD6, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10,
    0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x9A, 0xD6, 0xFF, 0xFF, 0xF3, 0x9C, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10,
    0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0xEC, 0x62, 0x8E, 0x73, 0xEC, 0x62, 0x82, 0x10,
    0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10,
    0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10
};

image_info_t msg_font_CHN_day_info =
{
    .type  = IMG_TYPE_RAW,
    .pixel = RTGRAPHIC_PIXEL_FORMAT_RGB565,
    .x = 0,
    .y = 0,
    .w = 46,
    .h = 42,
    .size = 3864UL,
    .data = msg_font_CN_day_46_42,
};

#endif
