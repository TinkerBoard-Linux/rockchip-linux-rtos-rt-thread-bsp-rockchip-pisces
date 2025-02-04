/**
  * Copyright (c) 2019 Fuzhou Rockchip Electronics Co., Ltd
  *
  * SPDX-License-Identifier: Apache-2.0
  */

#include <rtthread.h>
#if defined(OLPC_APP_NOTE_ENABLE)
#include "applications/common/image_info.h"

static const unsigned char note_subbtnrub201_120_80[227UL] =
{
    0x03, 0xFE, 0xFF, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD,
    0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF,
    0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0x71, 0x6F, 0xFB, 0xF7, 0xAF, 0x5F, 0xB8, 0xFE, 0xFF, 0xFE, 0xF5, 0xE3, 0xD6, 0xFF, 0x9F, 0xFE, 0x7E, 0xD7, 0xFB, 0xFF, 0x6B, 0xEB, 0x47, 0xAD, 0x7F, 0xBF, 0xFE,
    0xF3, 0xFB, 0xF7, 0xEF, 0xCF, 0xBC, 0x7F, 0xBF, 0xFE, 0xCA, 0xFA, 0xE7, 0xEB, 0x7F, 0xBC, 0x7F, 0xFE, 0xFE, 0xC3, 0xFB, 0xEF, 0xEF, 0x1F, 0xAC, 0xFF, 0xFE, 0xFE, 0xFE, 0xDE, 0xF1, 0xE3, 0xD7, 0x5F, 0x7D, 0xFF, 0x5D, 0xFD, 0xFB, 0xF7, 0xF7,
    0x57, 0x9E, 0x9F, 0xED, 0xFE, 0xE0, 0xFA, 0xEB, 0xEB, 0xEF, 0x8F, 0x9F, 0x3F, 0x7F, 0xF9, 0xFA, 0xD1, 0x83, 0xEF, 0xAF, 0x5D, 0x3B, 0x7F, 0xB0, 0xD2, 0xFB, 0x7B, 0x45, 0xCE, 0x1F, 0x79, 0x79, 0xFE, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF,
    0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xCF, 0xD4, 0x7F
};

image_info_t note_subbtnrub201_info =
{
    .type  = IMG_TYPE_COMPRESS,
    .pixel = RTGRAPHIC_PIXEL_FORMAT_RGB332,
    .x = 534,
    .y = 0,
    .w = 120,
    .h = 80,
    .size = 227UL,
    .data = note_subbtnrub201_120_80,
};

#endif
