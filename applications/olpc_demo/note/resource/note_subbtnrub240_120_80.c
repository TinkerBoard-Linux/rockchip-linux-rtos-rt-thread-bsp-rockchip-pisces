/**
  * Copyright (c) 2019 Fuzhou Rockchip Electronics Co., Ltd
  *
  * SPDX-License-Identifier: Apache-2.0
  */

#include <rtthread.h>
#if defined(OLPC_APP_NOTE_ENABLE)
#include "applications/common/image_info.h"

static const unsigned char note_subbtnrub240_120_80[236UL] =
{
    0x03, 0x6D, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE,
    0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF,
    0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0x77, 0xEB, 0xFF, 0xFE, 0x55, 0xE3, 0x3F, 0xAE, 0xFF, 0x3F, 0x7E, 0xFD, 0xBC, 0xF5, 0xFF, 0xD7, 0xAF, 0x5F, 0xB6, 0xFE, 0xFF, 0xF0, 0xF5, 0xAB, 0xD7, 0x9F, 0x7F, 0x7F, 0x69, 0xFD,
    0xFB, 0xF5, 0x77, 0xDE, 0xBF, 0x5F, 0xFF, 0xE5, 0xFD, 0xF7, 0xF7, 0x47, 0xD6, 0x7F, 0x7F, 0xFF, 0x62, 0xFD, 0xF7, 0xF7, 0x17, 0xD6, 0x3F, 0x5E, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xF7, 0xE7, 0x4F, 0x9F, 0x3F, 0xF7, 0xFC, 0xFD, 0x9D, 0xCF, 0xD7,
    0xD6, 0xBF, 0x3F, 0x3F, 0x7F, 0xDF, 0xF9, 0xF9, 0xF3, 0xA7, 0x5F, 0x7F, 0x7F, 0x72, 0xFC, 0xFC, 0xF1, 0x8F, 0xA5, 0xDF, 0x9F, 0xBF, 0xFB, 0xFE, 0xFC, 0xC5, 0xF3, 0xC7, 0x9E, 0xBD, 0x3F, 0x56, 0xFE, 0xFC, 0xF9, 0x1B, 0xEF, 0x4F, 0x1C, 0x79,
    0x7F, 0xA9, 0xA3, 0xFB, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xAF, 0xFD, 0x7F
};

image_info_t note_subbtnrub240_info =
{
    .type  = IMG_TYPE_COMPRESS,
    .pixel = RTGRAPHIC_PIXEL_FORMAT_RGB332,
    .x = 666,
    .y = 0,
    .w = 120,
    .h = 80,
    .size = 236UL,
    .data = note_subbtnrub240_120_80,
};

#endif