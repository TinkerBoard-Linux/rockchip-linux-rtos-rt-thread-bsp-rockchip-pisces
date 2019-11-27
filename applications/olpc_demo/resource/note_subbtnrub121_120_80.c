/**
  * Copyright (c) 2019 Fuzhou Rockchip Electronics Co., Ltd
  *
  * SPDX-License-Identifier: Apache-2.0
  */

#include <rtthread.h>
#if defined(OLPC_APP_NOTE_ENABLE)
#include "image_info.h"

static const unsigned char note_subbtnrub121_120_80[206UL] =
{
    0x03, 0xFE, 0xFF, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD,
    0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF,
    0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0xFA, 0x6D, 0xFF, 0xFE, 0xF5, 0xEB, 0xD6, 0xFF, 0x5F, 0x5B, 0x3F, 0xEC, 0xFD, 0xFF, 0xF5, 0xEB, 0x47, 0xAD, 0xBF, 0xFE, 0xFE,
    0xD1, 0xFB, 0xEB, 0xEF, 0xEF, 0xAC, 0x7F, 0xFF, 0xFE, 0xCB, 0xFA, 0xF7, 0xEF, 0x7F, 0xBC, 0xFF, 0xFD, 0xFE, 0xFD, 0xFB, 0xBB, 0xEF, 0x3F, 0xAC, 0x7F, 0xFF, 0xFE, 0xC0, 0xFA, 0xBF, 0xEF, 0xEF, 0x7B, 0xBF, 0x3F, 0x7C, 0xF2, 0xFC, 0xF9, 0x73,
    0xEF, 0x6F, 0xF7, 0x3A, 0x7F, 0xBB, 0xC9, 0xFB, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF,
    0x7F, 0xFF, 0xFE, 0xC1, 0xFF, 0x0F
};

image_info_t note_subbtnrub121_info =
{
    .type  = IMG_TYPE_COMPRESS,
    .pixel = RTGRAPHIC_PIXEL_FORMAT_RGB332,
    .x = 270,
    .y = 0,
    .w = 120,
    .h = 80,
    .size = 206UL,
    .data = note_subbtnrub121_120_80,
};

#endif
