/**
  * Copyright (c) 2019 Fuzhou Rockchip Electronics Co., Ltd
  *
  * SPDX-License-Identifier: Apache-2.0
  */

#include <rtthread.h>
#if defined(OLPC_APP_NOTE_ENABLE) && (defined(OLPC_STATICLD_ENABLE) || defined(OLPC_OVERLAY_ENABLE))
#include "image_info.h"

static const unsigned char note_dot040_4_4[4UL] =
{
    0x60, 0xF0, 0xF0, 0x60
};

image_info_t note_dot040_info =
{
    .type  = IMG_TYPE_RAW,
    .pixel = RTGRAPHIC_PIXEL_FORMAT_GRAY1,
    .x = 0,
    .y = 0,
    .w = 4,
    .h = 4,
    .size = 4UL,
    .data = note_dot040_4_4,
    .colorkey = COLOR_KEY_EN | 0,
};

#endif
