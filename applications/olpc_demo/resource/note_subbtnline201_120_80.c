/**
  * Copyright (c) 2019 Fuzhou Rockchip Electronics Co., Ltd
  *
  * SPDX-License-Identifier: Apache-2.0
  */

#include <rtthread.h>
#if defined(OLPC_APP_NOTE_ENABLE) && (defined(OLPC_STATICLD_ENABLE) || defined(OLPC_OVERLAY_ENABLE))
#include "image_info.h"

static const unsigned char note_subbtnline201_120_80[220UL] =
{
    0x03, 0xFE, 0xFF, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD,
    0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF,
    0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0x3F, 0x73, 0x6D, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xE9, 0x33, 0xEF, 0xEF, 0xDF, 0xBF, 0x7F, 0xFE,
    0xF8, 0xFB, 0xFB, 0xF7, 0x8F, 0x7F, 0x3F, 0x7F, 0xFF, 0xFE, 0xD1, 0xEB, 0xE7, 0xEF, 0x1F, 0xBF, 0xFE, 0xFE, 0xFE, 0xD5, 0xEF, 0xEF, 0xEF, 0x1F, 0xBC, 0xFE, 0xFE, 0xFE, 0xAD, 0xEF, 0xEF, 0xEF, 0x9F, 0x3F, 0x7F, 0xFB, 0xFD, 0xF9, 0xC3, 0xE7,
    0xCF, 0x1F, 0x7D, 0x7F, 0xFE, 0xE2, 0xF9, 0xF3, 0xD7, 0xDE, 0x9F, 0x3F, 0x75, 0xFE, 0xFC, 0x9D, 0xE7, 0xFE, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F,
    0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0x3F, 0xE0, 0xFF, 0x01
};

image_info_t note_subbtnline201_info =
{
    .type  = IMG_TYPE_COMPRESS,
    .pixel = RTGRAPHIC_PIXEL_FORMAT_RGB332,
    .x = 534,
    .y = 0,
    .w = 120,
    .h = 80,
    .size = 220UL,
    .data = note_subbtnline201_120_80,
};

#endif
