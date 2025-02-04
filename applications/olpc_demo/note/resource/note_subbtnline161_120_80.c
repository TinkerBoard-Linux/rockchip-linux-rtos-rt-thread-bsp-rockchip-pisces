/**
  * Copyright (c) 2019 Fuzhou Rockchip Electronics Co., Ltd
  *
  * SPDX-License-Identifier: Apache-2.0
  */

#include <rtthread.h>
#if defined(OLPC_APP_NOTE_ENABLE)
#include "applications/common/image_info.h"

static const unsigned char note_subbtnline161_120_80[211UL] =
{
    0x03, 0xFE, 0xFF, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD,
    0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF,
    0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0x5D, 0x6B, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0x4F, 0x5F, 0x39, 0x7F, 0xFF,
    0xFE, 0xFD, 0xF3, 0xC7, 0xDF, 0xDF, 0xBF, 0x7F, 0xFC, 0xFB, 0xF9, 0xFB, 0xF7, 0x8F, 0x5E, 0x3F, 0x7F, 0xFF, 0xF8, 0xF5, 0xF7, 0xF7, 0xAF, 0x7E, 0x7F, 0x7F, 0xFF, 0xE0, 0xF5, 0xF7, 0xF7, 0x6F, 0x7D, 0x7F, 0x7F, 0xFF, 0xFC, 0xF9, 0xDB, 0xEF,
    0xCF, 0x1F, 0x3E, 0x7F, 0xFE, 0xE8, 0x8B, 0xFF, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F,
    0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x63, 0xFF, 0x01
};

image_info_t note_subbtnline161_info =
{
    .type  = IMG_TYPE_COMPRESS,
    .pixel = RTGRAPHIC_PIXEL_FORMAT_RGB332,
    .x = 402,
    .y = 0,
    .w = 120,
    .h = 80,
    .size = 211UL,
    .data = note_subbtnline161_120_80,
};

#endif
