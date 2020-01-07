/**
  * Copyright (c) 2019 Fuzhou Rockchip Electronics Co., Ltd
  *
  * SPDX-License-Identifier: Apache-2.0
  */

#include <rtthread.h>
#if defined(OLPC_APP_NOTE_ENABLE) && (defined(OLPC_STATICLD_ENABLE) || defined(OLPC_OVERLAY_ENABLE))
#include "image_info.h"

static const unsigned char note_btnline0_160_80[244UL] =
{
    0x03, 0x49, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE,
    0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF,
    0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0x2F, 0xDC, 0xB2, 0x7F, 0xFF,
    0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0x4F, 0xFF, 0x74, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0x6F, 0xDF, 0x7E, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0x27, 0x9F, 0x9F, 0xBF, 0x7F, 0xFF, 0xFE, 0xC9, 0xE3, 0xEF,
    0xEF, 0xDF, 0xBF, 0x7D, 0xFD, 0xFC, 0xFD, 0xFB, 0x17, 0xBF, 0x9F, 0xBF, 0x7F, 0xFF, 0xD2, 0xF5, 0xF3, 0xF7, 0xAF, 0x5F, 0x7F, 0x7F, 0xFF, 0xEE, 0xF7, 0xF7, 0xF7, 0x2F, 0x9E, 0xF7, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F,
    0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB,
    0xF7, 0x6F, 0xD3, 0x7F
};

image_info_t note_btnline0_info =
{
    .type  = IMG_TYPE_COMPRESS,
    .pixel = RTGRAPHIC_PIXEL_FORMAT_RGB332,
    .x = 104,
    .y = 5,
    .w = 160,
    .h = 80,
    .size = 244UL,
    .data = note_btnline0_160_80,
};

#endif
