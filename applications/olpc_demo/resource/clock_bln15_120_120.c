/**
  * Copyright (c) 2019 Fuzhou Rockchip Electronics Co., Ltd
  *
  * SPDX-License-Identifier: Apache-2.0
  */

#include <rtthread.h>
#if defined(OLPC_APP_CLOCK_BLN_ENABLE) && (defined(OLPC_STATICLD_ENABLE) || defined(OLPC_OVERLAY_ENABLE))
#include "image_info.h"

static const unsigned char clock_bln15_120_120[1485UL] =
{
    0x03, 0x00, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE,
    0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0x9F, 0x3B, 0x02, 0x7F, 0xFF, 0xD6, 0xF7, 0x27, 0xF8, 0xF7, 0xAF, 0xBF, 0x7F, 0xFE, 0xFB, 0xF0, 0xF7, 0x03, 0xE0, 0xFF, 0x4F, 0x5F, 0x7F, 0xFE, 0xF5, 0xF5, 0xBB,
    0xB7, 0xCF, 0x7F, 0xDF, 0xBF, 0x7F, 0xF6, 0xF7, 0xA3, 0xDB, 0xDF, 0xEF, 0x1F, 0xBF, 0x7A, 0xFC, 0xC4, 0xC1, 0xE7, 0xFF, 0x6F, 0x1F, 0x3F, 0x7E, 0xDC, 0xFA, 0xAD, 0x2B, 0x20, 0xF0, 0xFF, 0xCF, 0xDF, 0xBF, 0x7C, 0xF9, 0xF3, 0x4F, 0xCB, 0x5F,
    0xF0, 0xEF, 0x5F, 0x42, 0x7F, 0xFF, 0xFE, 0xF9, 0xDB, 0x73, 0x9F, 0x6F, 0x39, 0x7C, 0x7D, 0x09, 0xFF, 0xFE, 0x25, 0x34, 0x34, 0xF4, 0xEF, 0x87, 0x0F, 0x3F, 0x7E, 0x61, 0xE8, 0xBB, 0xCD, 0xDF, 0x97, 0x2F, 0x5F, 0x84, 0xFF, 0x88, 0x7F, 0xFE,
    0xED, 0xD9, 0x73, 0xBF, 0xDE, 0xBE, 0x7D, 0xDB, 0xDC, 0xEF, 0xC1, 0x6B, 0xC0, 0x2F, 0x21, 0x61, 0xF1, 0xCF, 0x7F, 0x7F, 0xFF, 0xFC, 0xF7, 0xD3, 0x4F, 0x27, 0x0E, 0x7B, 0x7D, 0x56, 0xCF, 0xEB, 0xDB, 0xCB, 0x77, 0xFF, 0x9F, 0x3D, 0x9B, 0xFA,
    0xFE, 0xFB, 0x59, 0x48, 0xB0, 0xDB, 0x66, 0x9F, 0xFB, 0x71, 0xF2, 0xED, 0xEF, 0xB7, 0x97, 0x88, 0xF0, 0xBF, 0xFE, 0xBE, 0x3D, 0x9B, 0x7F, 0x36, 0x8A, 0xA6, 0xFB, 0xC6, 0x4E, 0x1C, 0xEE, 0x65, 0xC1, 0xB3, 0xC9, 0x2A, 0x88, 0xDE, 0xB0, 0x2E,
    0xDB, 0x36, 0xEC, 0xE9, 0xE8, 0xD7, 0xA3, 0xB7, 0x43, 0xAB, 0x8E, 0xF3, 0xEE, 0xE7, 0xA7, 0x97, 0x95, 0x7E, 0xB5, 0xF0, 0x86, 0xEC, 0xFB, 0x9B, 0x57, 0x4F, 0x27, 0x6E, 0x5D, 0xCC, 0x7F, 0xFF, 0xFC, 0xA5, 0xAB, 0x67, 0xAD, 0xBE, 0x68, 0x75,
    0x9B, 0x4C, 0xD9, 0x5A, 0x67, 0x1B, 0x77, 0x76, 0xCD, 0xEE, 0x85, 0x6F, 0xF7, 0xFE, 0xDD, 0xD2, 0x7F, 0xE0, 0xC3, 0xD3, 0xB6, 0x4D, 0x9F, 0xF3, 0xE7, 0x3C, 0x95, 0xE6, 0x0D, 0x8D, 0x5B, 0xFD, 0xBE, 0xD5, 0x21, 0x6F, 0xDE, 0x6E, 0x21, 0x39,
    0x7D, 0xF4, 0x7F, 0x87, 0x1C, 0x34, 0xF6, 0xF4, 0x71, 0xA6, 0xBF, 0x52, 0xBA, 0x4D, 0xBE, 0xCB, 0xF7, 0xCE, 0xEF, 0x3F, 0x5F, 0xF9, 0x5B, 0xBB, 0x4E, 0x5E, 0x5F, 0x7A, 0xDE, 0x1F, 0x87, 0x3C, 0xF5, 0x73, 0xBD, 0x97, 0x49, 0x7D, 0x82, 0x08,
    0xB6, 0x11, 0xFF, 0xF7, 0x5F, 0xFD, 0xD4, 0xBD, 0x56, 0x1F, 0x7C, 0xFB, 0xED, 0xD3, 0x2D, 0xB2, 0x7D, 0x3A, 0x5D, 0xAE, 0x9F, 0xA0, 0x33, 0xFB, 0x7A, 0x7D, 0xB7, 0xAF, 0x7E, 0xC8, 0xB2, 0xD7, 0x2F, 0x5C, 0xF0, 0xAA, 0x5D, 0x67, 0x9F, 0x70,
    0xE2, 0x03, 0xB5, 0x1F, 0xF5, 0xFB, 0xED, 0x3F, 0x5C, 0x9B, 0xDC, 0xB9, 0x07, 0xBF, 0x52, 0xA7, 0x3C, 0x68, 0xD8, 0x99, 0x36, 0x9E, 0x73, 0x2A, 0x0B, 0xBB, 0x46, 0x9E, 0x7D, 0x8B, 0xDF, 0xB7, 0x58, 0xC4, 0xB0, 0xB6, 0x1B, 0x16, 0xBA, 0x63,
    0xE4, 0x41, 0xAE, 0xF4, 0x3E, 0x9D, 0xED, 0xBB, 0x75, 0xEF, 0x7E, 0xA4, 0x5D, 0x8B, 0xDB, 0xEE, 0x32, 0xCE, 0x85, 0x6F, 0x6B, 0xFA, 0x93, 0x9D, 0x77, 0x17, 0x21, 0x01, 0x81, 0xF2, 0x6F, 0x3A, 0xCF, 0x91, 0x6F, 0xD9, 0xFE, 0x86, 0xDC, 0xC2,
    0xEF, 0xB5, 0xFD, 0x6E, 0x3F, 0x4E, 0xFB, 0xDF, 0x63, 0x2F, 0x2B, 0xA1, 0x1E, 0xEB, 0x93, 0xCC, 0x2D, 0xC3, 0x8D, 0xB3, 0xD0, 0x96, 0x7B, 0xCB, 0x17, 0x35, 0x1A, 0xFE, 0xC1, 0xDC, 0xB3, 0x5F, 0xFD, 0x8F, 0xCA, 0x2F, 0xFE, 0xB7, 0x77, 0xF7,
    0x37, 0x47, 0x1C, 0xFE, 0x37, 0x1B, 0xF6, 0x7E, 0x70, 0xF0, 0x8D, 0x84, 0x2F, 0x33, 0xAF, 0x6F, 0xAF, 0x1A, 0xFD, 0xED, 0x49, 0xA2, 0x2F, 0x01, 0xBC, 0xE3, 0x99, 0x27, 0xD9, 0xAB, 0xF8, 0x61, 0xCF, 0xAE, 0x3E, 0xD1, 0xCB, 0x4F, 0xB9, 0xB5,
    0x06, 0x3C, 0x23, 0x8D, 0xBF, 0x47, 0x4E, 0xDB, 0x3E, 0xFE, 0xEC, 0xE7, 0xBF, 0x3C, 0x12, 0x55, 0xE4, 0x4B, 0xCF, 0x3F, 0xC6, 0xF9, 0x0B, 0x4D, 0x5A, 0xF8, 0xD5, 0xE7, 0x6F, 0x79, 0x73, 0xBF, 0x97, 0xBF, 0x3D, 0xC5, 0xF9, 0xB7, 0x47, 0xD6,
    0x7D, 0x27, 0x83, 0xAC, 0x93, 0x7B, 0xFA, 0x4D, 0x44, 0xFF, 0x51, 0xEF, 0xE9, 0x4F, 0x30, 0xFA, 0xF5, 0x45, 0x27, 0x7F, 0x67, 0x34, 0xF1, 0x94, 0x7E, 0xE1, 0x19, 0x01, 0x5C, 0x7D, 0x83, 0xC2, 0xC1, 0xC3, 0x5B, 0xBF, 0xCB, 0x2D, 0xD0, 0x7F,
    0xDF, 0xC5, 0xDD, 0xAB, 0xAC, 0x9A, 0x7C, 0x00, 0x99, 0xD6, 0x32, 0xFD, 0xED, 0xDD, 0xA3, 0xFF, 0xDE, 0xFB, 0xF1, 0xB3, 0x13, 0xEA, 0xD7, 0xF7, 0xD7, 0x0E, 0xEC, 0xF6, 0x2D, 0x4D, 0x5C, 0x52, 0x94, 0xB3, 0xA4, 0xB3, 0x7E, 0xFC, 0xAF, 0x2B,
    0xD7, 0x73, 0x0C, 0xAF, 0x97, 0xD0, 0xC4, 0x17, 0xE9, 0x54, 0xBD, 0xF0, 0xEB, 0xBD, 0xB6, 0x7E, 0x7A, 0xFD, 0xE4, 0x87, 0x58, 0x6E, 0xDD, 0xE7, 0x6E, 0x5E, 0xDF, 0xF5, 0xCF, 0x57, 0x3F, 0xC3, 0x45, 0x61, 0x34, 0x9C, 0x36, 0xBF, 0x5F, 0x66,
    0xFB, 0x45, 0xF6, 0xC5, 0xD7, 0xFA, 0xFC, 0xD4, 0x9A, 0xC3, 0xBB, 0xF9, 0xFD, 0xC5, 0xA7, 0xBF, 0x59, 0x92, 0xC5, 0x27, 0x1D, 0xB4, 0xF5, 0xC7, 0xA7, 0x3F, 0x7B, 0xF3, 0xB0, 0xC4, 0xBA, 0xFE, 0xC0, 0x31, 0x43, 0x95, 0xEA, 0xE2, 0xFD, 0xF3,
    0xCE, 0xDB, 0xDC, 0xEF, 0xA6, 0x3F, 0x7C, 0xB2, 0x3D, 0x5E, 0x3F, 0xFC, 0xAB, 0x05, 0x7D, 0x1E, 0xF9, 0xE7, 0x79, 0x67, 0xBF, 0xFD, 0xE5, 0x97, 0x4E, 0x5D, 0x7E, 0xE6, 0x46, 0xC3, 0xFC, 0xD5, 0x04, 0x13, 0xCC, 0xBE, 0xFE, 0xA7, 0xEB, 0xBF,
    0x76, 0x70, 0xDE, 0xEF, 0xF7, 0xAC, 0xE2, 0xF2, 0xCB, 0x5F, 0x7C, 0x7A, 0xEE, 0x4D, 0xAF, 0x9D, 0x72, 0x7E, 0x31, 0x97, 0x7E, 0xFA, 0xDA, 0xCB, 0xD5, 0xBF, 0xB5, 0x70, 0xED, 0x27, 0xBF, 0xFC, 0xA7, 0xDA, 0x2F, 0xBF, 0x7B, 0x72, 0x89, 0x33,
    0xBC, 0xEF, 0xC4, 0xF1, 0xF7, 0x2E, 0x7F, 0x39, 0x9B, 0x17, 0x5F, 0xF7, 0xFB, 0x9B, 0xBF, 0xDE, 0x7A, 0x22, 0xEF, 0x1F, 0xFF, 0x7A, 0xB2, 0xDD, 0xBF, 0xFE, 0x74, 0x1E, 0x05, 0xBE, 0xFF, 0x53, 0xAF, 0x1A, 0x7F, 0x9F, 0xF8, 0xEB, 0xE3, 0xC3,
    0xDC, 0xFB, 0xFC, 0x85, 0x8F, 0x5E, 0x50, 0xFC, 0xDD, 0x1F, 0x99, 0x2A, 0xBA, 0x99, 0x0F, 0xD1, 0xFE, 0xBA, 0xB3, 0x37, 0x6B, 0xE7, 0xB6, 0xF6, 0x7F, 0x7F, 0xD0, 0x1A, 0xED, 0x1E, 0xB7, 0x22, 0xB6, 0x89, 0x15, 0x7E, 0xF6, 0xAF, 0xEE, 0xAF,
    0x72, 0xC0, 0xB7, 0xC6, 0xFE, 0xFE, 0x9A, 0x52, 0x27, 0x6D, 0xD8, 0x6B, 0x07, 0x24, 0xFF, 0xFC, 0x73, 0x35, 0x3E, 0x8C, 0x0A, 0x77, 0x2F, 0x11, 0xA7, 0xAF, 0x3B, 0x7D, 0x9E, 0xFB, 0x49, 0x66, 0xBF, 0xF3, 0xF4, 0xC7, 0xBB, 0xFF, 0xFC, 0x5D,
    0xBE, 0x7A, 0xFF, 0xD7, 0x37, 0x3F, 0xBC, 0xE7, 0x67, 0xD4, 0xFC, 0xDE, 0xF7, 0x3E, 0xF1, 0x33, 0xCE, 0x3F, 0xFC, 0x6D, 0x2F, 0x01, 0x05, 0xAE, 0xB7, 0xF1, 0xFD, 0x27, 0x33, 0xBF, 0xF6, 0xFD, 0xDD, 0xD4, 0xC4, 0xF5, 0xB5, 0x3E, 0x7F, 0xE9,
    0xF7, 0xB4, 0x3B, 0x33, 0x11, 0x77, 0xF5, 0xFD, 0xDE, 0x9F, 0x5F, 0x4B, 0xA8, 0xEE, 0xFF, 0xFD, 0x80, 0x0F, 0xE5, 0xDC, 0xCB, 0xF3, 0x77, 0xFD, 0xF8, 0xC3, 0x2F, 0xEE, 0x57, 0xD3, 0x9B, 0xBF, 0xA1, 0xEB, 0x53, 0x3E, 0xF2, 0xB7, 0x4F, 0xBA,
    0xB9, 0xD6, 0x2F, 0x66, 0xFE, 0x01, 0xC3, 0x79, 0xFE, 0x9C, 0xDE, 0xFF, 0xFE, 0x26, 0x4D, 0xA7, 0xAA, 0x02, 0xD3, 0xCA, 0x9F, 0xE8, 0xA4, 0xB4, 0xEF, 0x7E, 0xFB, 0x77, 0x5E, 0xFD, 0xF6, 0xB7, 0xBF, 0xFB, 0xFF, 0x67, 0xFF, 0x90, 0xA6, 0xC3,
    0xCB, 0xEF, 0xBA, 0x9F, 0xBA, 0x9F, 0xF6, 0xE8, 0xAF, 0x3E, 0xAA, 0xAD, 0xAC, 0x3E, 0xFD, 0xAB, 0x4D, 0x7F, 0xEE, 0xFA, 0xDF, 0x6C, 0x59, 0x71, 0x41, 0xDF, 0x7E, 0xF6, 0x83, 0xB9, 0xFD, 0x54, 0xFF, 0x2F, 0x7E, 0x10, 0xD3, 0x1D, 0xAF, 0xFA,
    0x3F, 0xF7, 0x7C, 0xF4, 0xB9, 0xAF, 0x7E, 0xD5, 0x6B, 0xFB, 0x58, 0x6D, 0xC1, 0x6F, 0x7C, 0xE3, 0x93, 0x1F, 0xF8, 0xF4, 0x5F, 0xBE, 0xD3, 0xEB, 0x5F, 0xE9, 0xE0, 0xA9, 0xBD, 0xFE, 0xC1, 0x4B, 0xDE, 0xF7, 0xCF, 0x6F, 0x36, 0xDB, 0xD5, 0x6D,
    0x4F, 0xB8, 0xF2, 0xBA, 0x7E, 0xFE, 0x3C, 0x27, 0xD2, 0x4E, 0xD2, 0xD3, 0x33, 0xB0, 0xDC, 0xD5, 0x5F, 0x21, 0xEF, 0xFF, 0xFC, 0x30, 0xF4, 0xBD, 0xFF, 0x7A, 0xE3, 0xF3, 0x77, 0xFF, 0x7B, 0xF2, 0xD9, 0xA7, 0xFF, 0xE2, 0x7A, 0x4B, 0x01, 0xF9,
    0x4D, 0x75, 0x7B, 0xEE, 0xA3, 0xB9, 0x3F, 0xFD, 0x93, 0xEF, 0x76, 0xFD, 0xB7, 0x72, 0x7E, 0x19, 0x0B, 0xF5, 0x7E, 0xF9, 0xEB, 0x94, 0xBF, 0xFA, 0xB9, 0x5F, 0x7F, 0xF1, 0x57, 0x1F, 0x66, 0x6D, 0x39, 0x80, 0x7F, 0xF1, 0x9D, 0x8A, 0x5E, 0xFD,
    0x31, 0xBB, 0xF2, 0x7F, 0xFE, 0x6F, 0x5F, 0xFB, 0x0B, 0x05, 0x1F, 0x4B, 0xFA, 0x53, 0x14, 0xB1, 0xF4, 0xFF, 0xEF, 0x7F, 0x0A, 0x38, 0xE0, 0x3F, 0xF3, 0x0F, 0x0F, 0x30, 0xEA, 0xFA, 0x7F, 0x5A, 0x98, 0xFC, 0x79, 0x4F, 0x75, 0x98, 0x33, 0xD3,
    0xFE, 0x0E, 0xFC, 0x4F, 0x86, 0xFF, 0xF9, 0xDF, 0x0A, 0xFF, 0xC9, 0xB0, 0xFF, 0xF9, 0xD3, 0xCF, 0x34, 0xBD, 0x64, 0x17, 0x3C, 0xEE, 0x07, 0x1E, 0x7C, 0xDD, 0x0B, 0x5D, 0xFB, 0xEB, 0xFF, 0xA1, 0x82, 0xF6, 0xB3, 0xFF, 0xFD, 0xFE, 0xB2, 0x3F,
    0xFE, 0xB0, 0x77, 0x5E, 0xFB, 0x62, 0xDF, 0x77, 0xFA, 0xDD, 0x1F, 0x7E, 0xF8, 0x87, 0x1F, 0xFC, 0x7D, 0x67, 0x3E, 0xF3, 0x15, 0x1A, 0xBD, 0xEE, 0x95, 0x9F, 0xE2, 0xC7, 0x37, 0xFF, 0xF7, 0xFC, 0xE7, 0x3F, 0xEF, 0x8D, 0x9F, 0xFE, 0x81, 0x4D,
    0x85, 0xFF, 0xE1, 0xAF, 0x46, 0x79, 0xFD, 0x8D, 0x1F, 0x7C, 0xE2, 0xC7, 0xBF, 0xFB, 0xF5, 0xD4, 0x2A, 0xFF, 0x3D, 0xA9, 0x4E, 0x79, 0xCA, 0x67, 0xBD, 0xFC, 0x84, 0xA4, 0x3F, 0xFD, 0x97, 0x67, 0xB1, 0xCB, 0x1A, 0x4F, 0xA4, 0x9A, 0x66, 0xDD,
    0x0F, 0xEA, 0x77, 0xC9, 0xDD, 0x7D, 0x9E, 0xA7, 0x1C, 0xFE, 0x4B, 0x26, 0x90, 0x57, 0xFF, 0x1B, 0xBF, 0xCA, 0x68, 0xB2, 0xAC, 0x7F, 0x5E, 0x6D, 0x65, 0xBF, 0x78, 0x51, 0x95, 0x22, 0xFF, 0x2E, 0x9D, 0x7F, 0x76, 0x75, 0xFF, 0x7E, 0xFD, 0xD7,
    0x1B, 0xFE, 0x71, 0x85, 0xFF, 0xFE, 0x21, 0x04, 0xF1, 0xBF, 0x17, 0xC5, 0x7F, 0xFE, 0x2F, 0x44, 0x39, 0xCB, 0xDA, 0xD7, 0xBF, 0xFF, 0xFD, 0xEF, 0x7F, 0xFF, 0xFB, 0xDF, 0xFF, 0xFE, 0xF7, 0xBF, 0xFF, 0xFD, 0xEF, 0x7F, 0xFF, 0xFB, 0xDF, 0xFF,
    0xFE, 0x07, 0xD2, 0xFF, 0x01
};

image_info_t clock_bln15_info =
{
    .type  = IMG_TYPE_COMPRESS,
    .pixel = RTGRAPHIC_PIXEL_FORMAT_RGB332,
    .x = 0,
    .y = 0,
    .w = 120,
    .h = 120,
    .size = 1485UL,
    .data =  clock_bln15_120_120,
};

#endif
