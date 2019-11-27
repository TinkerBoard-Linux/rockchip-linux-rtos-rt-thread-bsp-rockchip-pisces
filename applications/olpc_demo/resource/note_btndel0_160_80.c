/**
  * Copyright (c) 2019 Fuzhou Rockchip Electronics Co., Ltd
  *
  * SPDX-License-Identifier: Apache-2.0
  */

#include <rtthread.h>
#if defined(OLPC_APP_NOTE_ENABLE)
#include "image_info.h"

static const unsigned char note_btndel0_160_80[1159UL] =
{
    0x03, 0x49, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE,
    0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xAD, 0x97, 0x52, 0xF6,
    0xCF, 0x7F, 0x6C, 0x3A, 0xB9, 0x7E, 0xFC, 0x8A, 0xA7, 0xE5, 0x73, 0x27, 0x55, 0xFD, 0x9F, 0xFF, 0x7C, 0xE1, 0x95, 0x64, 0xF3, 0xDF, 0xAF, 0x2B, 0x5F, 0xF5, 0x4B, 0xFE, 0xFF, 0xF0, 0x2D, 0xAB, 0xC7, 0xBF, 0x5F, 0xBE, 0xFC, 0xCE, 0xE6, 0xDF,
    0xA3, 0x9F, 0xDC, 0x9D, 0xBB, 0x7F, 0xED, 0x62, 0x2B, 0xC3, 0x27, 0x6F, 0x38, 0x62, 0x79, 0xFC, 0xEB, 0xBF, 0x9B, 0x97, 0xA4, 0xBF, 0xDF, 0x7C, 0x44, 0xFF, 0x0E, 0xB5, 0x25, 0xC5, 0x37, 0x17, 0x3F, 0x69, 0xEE, 0x9E, 0x3A, 0x5A, 0xBC, 0xF6,
    0x9D, 0xEF, 0x2F, 0x3F, 0x17, 0x7D, 0x74, 0xF2, 0xFD, 0x91, 0x0B, 0xE7, 0x14, 0xBA, 0xDE, 0x7C, 0xF0, 0xF4, 0xE8, 0xD3, 0xDF, 0x6E, 0xFF, 0x75, 0x36, 0x79, 0xE0, 0xE8, 0xB3, 0xB6, 0xA7, 0x8D, 0x7E, 0x7E, 0x54, 0xF4, 0xEB, 0x45, 0xAF, 0xB7,
    0xFD, 0x54, 0xBD, 0x7D, 0xA3, 0xEB, 0x91, 0x06, 0x84, 0xBF, 0x7C, 0xBD, 0xFA, 0xDD, 0xA3, 0xD7, 0xB7, 0xC7, 0xAE, 0x1C, 0x67, 0x76, 0xF7, 0x8A, 0xDD, 0xDB, 0x44, 0x5F, 0xDD, 0x5B, 0xF6, 0x99, 0xC2, 0xEB, 0xB2, 0x47, 0x5D, 0xB8, 0xE4, 0x7E,
    0xBE, 0xE8, 0xAF, 0xA7, 0x5F, 0xCF, 0x37, 0x9F, 0xB5, 0x6B, 0xD8, 0x0B, 0x87, 0x3C, 0xFF, 0x16, 0xA3, 0xAA, 0xBF, 0xE4, 0xC9, 0x4B, 0x5E, 0x2B, 0x3F, 0x62, 0xEF, 0xFA, 0x86, 0x51, 0x93, 0xA7, 0xD2, 0x5F, 0xFC, 0xE9, 0xDE, 0x7C, 0xF9, 0x66,
    0xF7, 0xAA, 0xBE, 0x39, 0x7A, 0xC4, 0xCD, 0xF2, 0x86, 0xAA, 0x3E, 0x20, 0x7B, 0xF7, 0xFF, 0xEC, 0xCE, 0x87, 0xED, 0xDA, 0xBF, 0xE1, 0xF3, 0x0B, 0x5C, 0xBE, 0x5F, 0x12, 0xF6, 0xD8, 0x7B, 0x3A, 0x1F, 0x66, 0x81, 0xFC, 0x53, 0x95, 0xC6, 0x5F,
    0x57, 0xF9, 0xF2, 0xA3, 0x2A, 0x9F, 0xFC, 0xE8, 0xCD, 0xE7, 0x7F, 0xD2, 0xEC, 0xCE, 0xA3, 0xBA, 0xFF, 0x7B, 0xEF, 0x05, 0x54, 0x8D, 0xBB, 0x74, 0x58, 0x7D, 0x8D, 0xF0, 0xD2, 0x77, 0x1E, 0xF0, 0xED, 0xD2, 0xDB, 0xEA, 0x3F, 0x71, 0xB2, 0x39,
    0x9F, 0xBF, 0x7D, 0xFF, 0xB1, 0x9D, 0xA8, 0x27, 0x56, 0xFD, 0x80, 0xED, 0x81, 0xB5, 0xD6, 0x1F, 0xD0, 0xF9, 0xD1, 0x9F, 0x7F, 0xBB, 0xE7, 0xB6, 0x17, 0x6E, 0x7E, 0xF4, 0xE9, 0x43, 0xFF, 0xAE, 0x5F, 0xBB, 0x72, 0xCE, 0x0B, 0xAF, 0x39, 0x82,
    0xF3, 0x83, 0x95, 0x35, 0x7F, 0xCF, 0xF9, 0xDF, 0x4B, 0x6E, 0x7E, 0xF4, 0xE9, 0xEB, 0x0E, 0x7A, 0xEA, 0xC8, 0x8F, 0x5E, 0x5F, 0x7A, 0xE2, 0x1F, 0xAC, 0x1F, 0x7E, 0xA1, 0xF6, 0x37, 0x6F, 0xFF, 0xF5, 0xBB, 0x51, 0x17, 0xBE, 0xF7, 0xEB, 0xDD,
    0x96, 0x9F, 0x5E, 0xD6, 0x59, 0xFF, 0xEF, 0xBF, 0xD5, 0xF1, 0xFE, 0xDC, 0x67, 0xFD, 0xCA, 0x85, 0x6F, 0x5F, 0x6F, 0xED, 0x41, 0x6E, 0x9F, 0x77, 0xBD, 0x3B, 0xCA, 0x7A, 0xF9, 0x7F, 0xF2, 0x05, 0xBD, 0x3F, 0x3B, 0xF7, 0x9A, 0x77, 0x4F, 0xBB,
    0xF2, 0xAD, 0x6F, 0x8B, 0xAE, 0xC7, 0xF0, 0x4F, 0x8B, 0x36, 0xFC, 0xE6, 0x2B, 0xCE, 0xBC, 0xF7, 0xEF, 0x7F, 0xDF, 0x3C, 0xCA, 0x31, 0x57, 0x04, 0x7F, 0xDF, 0xB4, 0x35, 0xBD, 0xCD, 0x3E, 0xCA, 0x1D, 0x45, 0x5E, 0x3E, 0x4F, 0x39, 0xB6, 0xF6,
    0x43, 0x5A, 0x1B, 0xE3, 0xB2, 0x2F, 0xCE, 0x7F, 0x51, 0x89, 0xDF, 0xBA, 0xDA, 0x96, 0x1B, 0xF8, 0xD0, 0xBB, 0x6C, 0xF5, 0xC4, 0xA1, 0xDF, 0x3C, 0xD6, 0x79, 0x6F, 0x5D, 0x0E, 0xFC, 0x64, 0x30, 0x0D, 0xD6, 0xFE, 0xD0, 0xFE, 0x1C, 0xD9, 0x47,
    0xBC, 0x7D, 0x7F, 0xCB, 0x37, 0xBB, 0x40, 0x49, 0xA4, 0x3B, 0x69, 0x2E, 0x7D, 0xAF, 0xFD, 0xCB, 0xFD, 0xE4, 0xFA, 0xEA, 0xB3, 0xA9, 0xBE, 0xFA, 0x9B, 0xA3, 0xDE, 0xDF, 0x2C, 0x99, 0xAB, 0x36, 0x68, 0x29, 0xFF, 0xCE, 0xC2, 0x0F, 0xBF, 0xC9,
    0xDC, 0x23, 0x0C, 0x3F, 0xF7, 0x9A, 0x5B, 0x39, 0xAF, 0x9B, 0xD4, 0x06, 0x5B, 0xB8, 0xFC, 0xE2, 0xCF, 0x2F, 0xEE, 0xFC, 0xFC, 0x4A, 0xD4, 0x18, 0xD6, 0xF9, 0xCA, 0x97, 0x5F, 0x7E, 0xF9, 0xC9, 0xBF, 0xFE, 0xE3, 0xEB, 0xAF, 0x04, 0xB6, 0xD8,
    0x6D, 0xFE, 0xFB, 0xCF, 0x7F, 0x9B, 0xA4, 0xF5, 0xFF, 0x5F, 0x9B, 0xF0, 0x0C, 0x76, 0x22, 0x29, 0x2E, 0x68, 0x4E, 0x42, 0x5B, 0x16, 0xFF, 0x11, 0xFB, 0x27, 0x09, 0xAD, 0x66, 0x23, 0x21, 0x37, 0xDE, 0xFB, 0xE3, 0x8D, 0x9D, 0x3E, 0x59, 0x3D,
    0x31, 0xC7, 0x1D, 0x3F, 0xA9, 0xC7, 0xFE, 0x38, 0x5E, 0xA2, 0xE1, 0x2F, 0xFE, 0x5B, 0x37, 0xE7, 0x37, 0x7B, 0x7E, 0x9B, 0xA9, 0x8E, 0x9C, 0xC3, 0xA2, 0x97, 0x1D, 0x7E, 0x6B, 0xE1, 0x8B, 0x06, 0xED, 0x29, 0xF8, 0x89, 0x8E, 0x5F, 0x3B, 0x57,
    0x0F, 0x75, 0xFF, 0x61, 0x5D, 0x03, 0x3E, 0x9A, 0xD7, 0x83, 0xD9, 0x8C, 0x3F, 0xE5, 0xF8, 0x97, 0x8B, 0x3F, 0xD2, 0xF8, 0x87, 0x8D, 0x7F, 0xFA, 0xF8, 0x33, 0xBE, 0xB4, 0xD9, 0x9A, 0xE2, 0xC7, 0x38, 0x7E, 0xDD, 0xE2, 0xA7, 0x99, 0xDE, 0xF8,
    0xEC, 0x7B, 0x3F, 0x63, 0xAD, 0x89, 0x97, 0x77, 0xFE, 0xC6, 0x19, 0x97, 0x6B, 0x76, 0x2C, 0x35, 0xC6, 0x78, 0x7E, 0xE2, 0x0B, 0x46, 0x7D, 0x4C, 0x25, 0x9F, 0xDB, 0x84, 0xAC, 0xFB, 0x65, 0x9D, 0x27, 0xDF, 0xFB, 0xD0, 0x17, 0xEB, 0xBE, 0xAB,
    0xD0, 0xA7, 0xDC, 0xA3, 0xE3, 0xB3, 0xFE, 0xE6, 0xE0, 0x4A, 0x86, 0x82, 0xB8, 0xF4, 0x54, 0x92, 0x8A, 0x0F, 0x99, 0x9B, 0x5D, 0x02, 0xEA, 0x35, 0x76, 0xD9, 0x0F, 0xFE, 0xF9, 0xE0, 0x29, 0x8B, 0xB6, 0x98, 0x98, 0x71, 0x36, 0xEE, 0xA1, 0x22,
    0xF6, 0x5F, 0x1E, 0xDB, 0x71, 0xEB, 0x17, 0xAA, 0xFE, 0x9E, 0xD7, 0xE3, 0x2E, 0x74, 0x69, 0x29, 0xB3, 0x08, 0xDC, 0x8C, 0x86, 0x29, 0x4A, 0x5A, 0x5E, 0xB6, 0xF1, 0xAF, 0x65, 0xE6, 0x6D, 0xBB, 0xDF, 0x76, 0x65, 0xF1, 0xBE, 0xA6, 0xA9, 0xA6,
    0x32, 0xDF, 0x2B, 0xEF, 0x55, 0xE2, 0xE1, 0xB6, 0xE4, 0x68, 0x7B, 0xB5, 0x7F, 0x33, 0x44, 0xB5, 0x0B, 0xD6, 0xF1, 0x81, 0x8D, 0xC3, 0x09, 0xA7, 0x90, 0x48, 0xBB, 0x89, 0x94, 0x85, 0xED, 0x43, 0xC9, 0x9C, 0x55, 0xB6, 0x2F, 0x08, 0xFE, 0x14,
    0x67, 0xDD, 0xAB, 0xB9, 0xF2, 0x5B, 0x5F, 0xB8, 0xD4, 0x5E, 0x79, 0x0A, 0xFA, 0x34, 0x1B, 0xFD, 0x42, 0xCF, 0xFE, 0x04, 0xD9, 0xFF, 0x3D, 0xDD, 0xB6, 0xB1, 0x46, 0xFE, 0x5C, 0xE2, 0xB6, 0xF9, 0x65, 0xE3, 0xD7, 0x49, 0x6F, 0x0C, 0x9D, 0x64,
    0x2F, 0xEF, 0xD1, 0xD3, 0x3A, 0x1C, 0xC8, 0x82, 0x88, 0xE4, 0xAF, 0xFC, 0xA7, 0x4D, 0x8F, 0xE5, 0x9C, 0x10, 0x0F, 0x5C, 0x1F, 0x9E, 0xBF, 0xDF, 0xFE, 0xD4, 0xEE, 0x37, 0xAD, 0xFF, 0x20, 0x6B, 0x64, 0x64, 0x37, 0x88, 0xDC, 0x97, 0x5B, 0xBF,
    0x6F, 0xF2, 0xCB, 0xFE, 0xDE, 0xF9, 0x4E, 0x1F, 0x39, 0xB4, 0x92, 0x86, 0xD0, 0x63, 0x17, 0xAC, 0x78, 0x1F, 0x00, 0xD5, 0x96, 0xBE, 0x40, 0xA5, 0xEA, 0x43, 0xBC, 0xBF, 0x06, 0x72, 0x3E, 0xAA, 0xD7, 0xA7, 0xF5, 0x36, 0x3A, 0xF5, 0x89, 0x5D,
    0x2C, 0x71, 0x8A, 0xAE, 0xB5, 0x84, 0xC9, 0xDF, 0x16, 0x97, 0xB1, 0x04, 0x2A, 0xDF, 0x40, 0xC4, 0x29, 0xF9, 0x93, 0xDE, 0xC2, 0xBF, 0x8D, 0x56, 0xBB, 0xE2, 0xB4, 0x0A, 0x6A, 0xD7, 0x6D, 0x5D, 0x10, 0x5D, 0x91, 0xC5, 0xE9, 0xF3, 0xE3, 0x29,
    0xBF, 0x7B, 0xAA, 0x5A, 0xB1, 0xDF, 0xF8, 0xC6, 0xBA, 0x2C, 0x42, 0x80, 0x2F, 0x47, 0xB8, 0x83, 0xB6, 0x8C, 0x70, 0xE8, 0xF9, 0x83, 0x5F, 0x9B, 0xC5, 0xEF, 0xED, 0x7F, 0xFF, 0xFB, 0xDF, 0xFF, 0xFE, 0xF7, 0xBF, 0xFF, 0xFD, 0xEF, 0x7F, 0xFF,
    0xFB, 0xDF, 0xFF, 0xFE, 0xF7, 0xBF, 0xFF, 0xFD, 0xEF, 0x7F, 0xFF, 0xFB, 0xDF, 0xFF, 0xFE, 0xF7, 0xBF, 0xFF, 0xFD, 0xEF, 0x7F, 0xFF, 0xFB, 0xDF, 0xFF, 0xFE, 0xF7, 0xBF, 0xFF, 0xFD, 0xEF, 0x7F, 0xFF, 0xFB, 0xDF, 0xFF, 0x54, 0xFA, 0x3F
};

image_info_t note_btndel0_info =
{
    .type  = IMG_TYPE_COMPRESS,
    .pixel = RTGRAPHIC_PIXEL_FORMAT_RGB332,
    .x = 620,
    .y = 5,
    .w = 160,
    .h = 80,
    .size = 1159UL,
    .data = note_btndel0_160_80,
};

#endif
