/**
  * Copyright (c) 2019 Fuzhou Rockchip Electronics Co., Ltd
  *
  * SPDX-License-Identifier: Apache-2.0
  */

#include <rtthread.h>
#if defined(OLPC_APP_NOTE_ENABLE)
#include "image_info.h"

static const unsigned char note_subbtnline320_120_80[247UL] =
{
    0x03, 0x6D, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE,
    0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF,
    0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0x0F, 0xDF, 0xB5, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xF4, 0xAD, 0xF3, 0xF7, 0xEF, 0xDF, 0x3F, 0x7F, 0xFC, 0xFD, 0xFD, 0xFB, 0xC7, 0xBF, 0x9F, 0xBF, 0x7F, 0xFF,
    0xE8, 0xF5, 0xF3, 0xF7, 0x8F, 0x5F, 0x7F, 0x7F, 0xFF, 0xEA, 0xF7, 0xF7, 0xF7, 0x0F, 0x5E, 0x7F, 0x7F, 0xFF, 0xD6, 0xF7, 0xF7, 0xF7, 0xCF, 0x9F, 0xBF, 0xFD, 0xFE, 0xFC, 0xE1, 0xF3, 0xE7, 0x8F, 0xBE, 0x3F, 0x7F, 0xF1, 0xFC, 0xF9, 0x6B, 0xEF,
    0xCF, 0x9F, 0x3A, 0x7F, 0xFE, 0xCE, 0xFB, 0xF3, 0xE7, 0xAE, 0x99, 0xBF, 0xF9, 0xFE, 0xFC, 0xCD, 0xF7, 0xE7, 0x6F, 0xBE, 0x3F, 0x7F, 0xF3, 0xFD, 0xF9, 0x9B, 0xEF, 0xCF, 0xDF, 0x7C, 0x7F, 0xFE, 0xE6, 0xFB, 0xF3, 0x37, 0x1F, 0xB8, 0xBF, 0xFC,
    0xFE, 0xFC, 0xE5, 0xF7, 0xE7, 0x2F, 0xBF, 0xF2, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB,
    0xF7, 0xEF, 0xDF, 0xBF, 0x4B, 0xFF, 0x01
};

image_info_t note_subbtnline320_info =
{
    .type  = IMG_TYPE_COMPRESS,
    .pixel = RTGRAPHIC_PIXEL_FORMAT_RGB332,
    .x = 930,
    .y = 0,
    .w = 120,
    .h = 80,
    .size = 247UL,
    .data = note_subbtnline320_120_80,
};

#endif
