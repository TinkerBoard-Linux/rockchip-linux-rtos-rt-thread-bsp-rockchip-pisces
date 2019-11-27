/**
  * Copyright (c) 2019 Fuzhou Rockchip Electronics Co., Ltd
  *
  * SPDX-License-Identifier: Apache-2.0
  */

#include <rtthread.h>
#if defined(OLPC_APP_NOTE_ENABLE)
#include "image_info.h"

static const unsigned char note_btnprev1_90_90[508UL] =
{
    0x03, 0xFE, 0xFF, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0x00, 0xFF, 0xFE, 0xFD, 0xFB, 0x07, 0xB0, 0xFF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xE1, 0xDB, 0xF7, 0xEF, 0x1F, 0x3E, 0xFE, 0xFF, 0xFE, 0xFD, 0x83, 0xC7, 0xEF, 0xDF, 0xBF, 0xFA, 0xFC,
    0xFF, 0xED, 0xEF, 0xF7, 0x6F, 0x7F, 0xBF, 0x7F, 0xF2, 0xFB, 0xFD, 0xE3, 0xDF, 0xEF, 0xDF, 0x79, 0x7D, 0xF3, 0xFD, 0xF7, 0xB3, 0x4F, 0x7F, 0x9F, 0xFF, 0x7E, 0xEF, 0xF0, 0xFB, 0x7B, 0xCF, 0xCE, 0x1F, 0x3A, 0x7F, 0xFE, 0xBE, 0xB3, 0xF7, 0xE7,
    0x9D, 0xBF, 0x3F, 0x7F, 0xE5, 0xFD, 0xC5, 0xF7, 0xE7, 0x6F, 0xBB, 0xB8, 0x7D, 0xFD, 0xFA, 0x71, 0xF7, 0x17, 0xCF, 0x7F, 0xBF, 0x7E, 0xD8, 0xE1, 0xF5, 0xEB, 0xD7, 0xAF, 0x7A, 0xFA, 0x7B, 0xFD, 0xD6, 0xE9, 0x0F, 0xDF, 0xAF, 0x5F, 0x3F, 0xFD,
    0xDE, 0xF9, 0xF5, 0x13, 0xE7, 0xAF, 0xBA, 0xFF, 0x7E, 0xFA, 0x97, 0x5D, 0xCF, 0xDF, 0xCF, 0x5F, 0xBF, 0xFC, 0xFE, 0xFB, 0x49, 0xCF, 0x57, 0x5D, 0x7F, 0x3F, 0xFD, 0xCA, 0x8F, 0xF1, 0xEB, 0x97, 0x0F, 0x58, 0x31, 0xFD, 0xFD, 0xF4, 0xF7, 0xC3,
    0x57, 0xBF, 0x5F, 0x7D, 0x7F, 0xDE, 0xEE, 0xF5, 0x53, 0xD7, 0xAF, 0xBA, 0xFF, 0x7E, 0xEA, 0xFC, 0xC9, 0xAA, 0xDF, 0xAF, 0x3E, 0xFE, 0x7A, 0xDF, 0xFD, 0x37, 0xDB, 0x2F, 0xBD, 0xFE, 0x75, 0xFC, 0xC6, 0xEA, 0xAD, 0x5F, 0xEE, 0x5F, 0x7B, 0xBF,
    0xFD, 0xF8, 0xFB, 0xC1, 0xC3, 0x7F, 0xBF, 0x7E, 0xB2, 0x68, 0xD2, 0xD3, 0xED, 0xF3, 0x37, 0x6F, 0x59, 0xBF, 0xFB, 0xFD, 0xFA, 0xF9, 0x6F, 0x7D, 0xDF, 0x3F, 0xB1, 0x7C, 0xFC, 0xD1, 0xE9, 0x83, 0xDF, 0xEF, 0x35, 0x33, 0xFC, 0xFE, 0xFA, 0xE9,
    0x9F, 0xFD, 0x2E, 0xB8, 0xF1, 0x73, 0xCE, 0xF5, 0xAF, 0xBF, 0x97, 0x3E, 0x5A, 0xBF, 0x6B, 0xF8, 0xDA, 0x1F, 0xEB, 0x97, 0xDD, 0x3F, 0x6B, 0x5C, 0xFE, 0x9C, 0xD5, 0xFF, 0x85, 0xAB, 0xDF, 0x69, 0x7C, 0xDD, 0xF0, 0xD1, 0x33, 0xAE, 0x9F, 0xB7,
    0xFE, 0x7E, 0xC9, 0xF2, 0xEB, 0x6F, 0xE4, 0x2F, 0xB4, 0xFE, 0xE4, 0xFD, 0xF9, 0x07, 0x51, 0x37, 0x5A, 0xFC, 0xAE, 0x77, 0xE7, 0x0F, 0xBB, 0xFE, 0xFD, 0xF5, 0xE7, 0xBF, 0xF6, 0xFE, 0x70, 0x4F, 0x77, 0xAF, 0xFA, 0xFC, 0xEC, 0xF5, 0xBF, 0x1A,
    0xFC, 0x7D, 0xEC, 0xF5, 0x57, 0x1F, 0xF3, 0xFB, 0x9C, 0xE7, 0xEF, 0xBD, 0x68, 0xFF, 0xF0, 0xF3, 0xFF, 0xB0, 0x71, 0xFF, 0xCE, 0xBB, 0xAF, 0xBF, 0x81, 0xFD, 0xF5, 0x77, 0x1F, 0x7C, 0xB8, 0xFB, 0x3B, 0xEF, 0xFB, 0xF4, 0xFB, 0xCB, 0x6F, 0xAE,
    0xFF, 0xFC, 0x49, 0xD6, 0x1F, 0x3F, 0xF4, 0xF1, 0x13, 0xAE, 0xFD, 0xFE, 0xA3, 0x5B, 0x2F, 0xFE, 0x8A, 0xF8, 0xDF, 0x8F, 0xDD, 0xFE, 0xFC, 0x2D, 0x8F, 0x7D, 0xFE, 0xC1, 0xFB, 0xAF, 0x5C, 0x7F, 0xFD, 0xED, 0xA7, 0x39, 0x38, 0xF9, 0xF8, 0xC2,
    0xC6, 0xFF, 0xE2, 0xE1, 0xF8, 0x37, 0xCE, 0x3F, 0xFF, 0xBC, 0xFA, 0xBE, 0x1F, 0xFF, 0xCD, 0xFB, 0xC7, 0x59, 0xF2, 0xFE, 0x51, 0xBD, 0x7E, 0xFC, 0xCB, 0xE0, 0x83, 0xCF, 0xBC, 0xFE, 0x23, 0xC3, 0x7E, 0x7F, 0xF9, 0xED, 0xF3, 0xEF, 0xFD, 0xFB,
    0xFD, 0x23, 0xCE, 0xFF, 0xD9, 0xC8, 0x5B, 0xFE, 0x7D, 0xFB, 0xAC, 0xCB, 0x6C, 0x7F, 0x9B, 0xBE, 0x95, 0xA7, 0x3F, 0x76, 0xFC, 0x27, 0x9F, 0xFF, 0xED, 0xFE, 0x17, 0x4D, 0x5F, 0xBF, 0xFA, 0xFC, 0x7F, 0x9A, 0x33, 0xAF, 0xFE, 0x75, 0x37, 0x79,
    0x1F, 0xFF, 0xDC, 0xB5, 0xFC, 0x2F, 0x3E, 0xB7, 0xFD, 0x63, 0x69, 0x3E, 0x7D, 0xFD, 0xF3, 0xD7, 0x3F, 0x7B, 0x34, 0xFD, 0x63, 0xBF, 0x3E, 0xFF, 0xFE, 0x83, 0xF8, 0x3F
};

image_info_t note_btnprev1_info =
{
    .type  = IMG_TYPE_COMPRESS,
    .pixel = RTGRAPHIC_PIXEL_FORMAT_RGB332,
    .x = 2,
    .y = 0,
    .w = 90,
    .h = 90,
    .size = 508UL,
    .data = note_btnprev1_90_90,
};

#endif
