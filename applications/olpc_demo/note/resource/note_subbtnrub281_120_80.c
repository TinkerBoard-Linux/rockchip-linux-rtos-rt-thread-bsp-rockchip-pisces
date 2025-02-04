/**
  * Copyright (c) 2019 Fuzhou Rockchip Electronics Co., Ltd
  *
  * SPDX-License-Identifier: Apache-2.0
  */

#include <rtthread.h>
#if defined(OLPC_APP_NOTE_ENABLE)
#include "applications/common/image_info.h"

static const unsigned char note_subbtnrub281_120_80[245UL] =
{
    0x03, 0xFE, 0xFF, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD,
    0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF,
    0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xD7, 0xBD, 0xED, 0xDF, 0x3F, 0x7F, 0xFC, 0xCB, 0xF7, 0xFF, 0xE7, 0xBF, 0x1F, 0xF8, 0xFE, 0xFF, 0xF2, 0xF7, 0xE3, 0xD6, 0xFF, 0x5F, 0xBF, 0x7E, 0xD7, 0xFA, 0xFF, 0x6B, 0xEB, 0x37, 0xBD, 0x7F, 0xBF, 0xFE,
    0xD0, 0xFA, 0xF7, 0xEB, 0xDF, 0xAC, 0xFF, 0xFE, 0xFE, 0xC9, 0xFB, 0xEF, 0xEF, 0x6F, 0xAC, 0x7F, 0xFF, 0xFE, 0xC3, 0xFA, 0xF7, 0xEF, 0xEF, 0x0F, 0x9F, 0x3F, 0x7F, 0xFE, 0xEC, 0xFB, 0xF3, 0x37, 0xCF, 0x1F, 0xFB, 0xFB, 0xB9, 0xFB, 0xA3, 0xEF,
    0xEF, 0xCF, 0xBC, 0x3F, 0x7F, 0xE2, 0xFD, 0xF9, 0xFB, 0x4E, 0xDF, 0xDF, 0xB6, 0xFB, 0xF7, 0xFB, 0x67, 0xEF, 0xEF, 0xCF, 0x5F, 0x3E, 0xFD, 0xFB, 0x5C, 0xED, 0xF3, 0x97, 0x9E, 0xBE, 0x3F, 0x7F, 0xF1, 0xFD, 0xF9, 0x5B, 0xE7, 0x2F, 0xD5, 0x3A,
    0x7F, 0xE1, 0xCB, 0xF9, 0x3B, 0xED, 0xCD, 0x5F, 0xF2, 0xF2, 0xFE, 0xF8, 0xAB, 0xF7, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD,
    0xFB, 0xF7, 0x4F, 0xD6, 0x7F
};

image_info_t note_subbtnrub281_info =
{
    .type  = IMG_TYPE_COMPRESS,
    .pixel = RTGRAPHIC_PIXEL_FORMAT_RGB332,
    .x = 798,
    .y = 0,
    .w = 120,
    .h = 80,
    .size = 245UL,
    .data = note_subbtnrub281_120_80,
};

#endif
