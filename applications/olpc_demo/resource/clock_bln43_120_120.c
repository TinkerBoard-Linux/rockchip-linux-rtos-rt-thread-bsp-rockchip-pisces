/**
  * Copyright (c) 2019 Fuzhou Rockchip Electronics Co., Ltd
  *
  * SPDX-License-Identifier: Apache-2.0
  */

#include <rtthread.h>
#if defined(OLPC_APP_CLOCK_BLN_ENABLE) && (defined(OLPC_STATICLD_ENABLE) || defined(OLPC_OVERLAY_ENABLE))
#include "image_info.h"

static const unsigned char clock_bln43_120_120[1569UL] =
{
    0x03, 0x00, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE,
    0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xF8, 0x09, 0x00, 0xFC, 0xFF, 0xF3, 0xF7, 0xCF, 0xDF, 0xBE, 0x7F, 0xEC, 0xF9, 0x11, 0xFC, 0xFB, 0xF7, 0xEF, 0x5F, 0xBF, 0xFC, 0xFA, 0xFF, 0x85, 0xD3, 0xC7, 0xEF, 0xDF, 0x3F, 0x7C, 0xFC, 0xE0, 0xCB,
    0xEF, 0xF7, 0xEF, 0xDF, 0x7D, 0x7E, 0xE9, 0xFB, 0xFF, 0xFB, 0xD7, 0xAF, 0xFC, 0xFC, 0x7E, 0xFF, 0xEA, 0xA9, 0x7B, 0xBF, 0xDF, 0x9B, 0x3C, 0x7E, 0xFF, 0xF6, 0x97, 0xE7, 0x87, 0x4D, 0x1E, 0xFF, 0x7F, 0xF1, 0xC8, 0xF1, 0x93, 0xC6, 0x4F, 0x5E,
    0x01, 0x41, 0xC1, 0xBF, 0x7F, 0xFF, 0xFA, 0xE3, 0xCF, 0x97, 0x2F, 0xD9, 0x3C, 0x7E, 0xFB, 0x12, 0x12, 0x0A, 0xFC, 0xF9, 0xFB, 0x77, 0x5F, 0x1D, 0x7E, 0xFC, 0xC0, 0xE4, 0x79, 0xC3, 0x9F, 0x3F, 0xFF, 0xBF, 0x86, 0x04, 0xFF, 0xFE, 0xF8, 0xDB,
    0x73, 0xFF, 0xED, 0x3E, 0x6E, 0xEE, 0xEC, 0xF6, 0xE7, 0x6F, 0xF8, 0xE7, 0x3F, 0x22, 0xA2, 0xC1, 0xDF, 0x3F, 0x7E, 0xFB, 0xEA, 0x8F, 0x1F, 0x17, 0xBD, 0x1D, 0xB7, 0xFA, 0xEE, 0xD1, 0xE3, 0x97, 0xF8, 0x27, 0x51, 0xDF, 0x9F, 0x84, 0x85, 0x85,
    0xBF, 0xFD, 0xF2, 0xE9, 0xA9, 0x03, 0x47, 0x9F, 0x7A, 0x34, 0xEA, 0xC5, 0xAD, 0x93, 0x6B, 0xB8, 0x67, 0x63, 0x63, 0xEF, 0x5F, 0xBD, 0x7E, 0xFF, 0xFA, 0xCF, 0x87, 0x4F, 0x1F, 0x1C, 0x74, 0x75, 0xEA, 0xB1, 0xCB, 0xAA, 0x17, 0x5D, 0xDD, 0x7D,
    0xA7, 0x4E, 0x7A, 0xF6, 0xA8, 0xEF, 0xAF, 0x5E, 0x3D, 0xFA, 0xF5, 0xBE, 0xD5, 0xAB, 0x5F, 0x3B, 0x96, 0xF5, 0x6B, 0xE3, 0xED, 0xD9, 0xBB, 0x47, 0xA2, 0xBE, 0xFD, 0xF4, 0xF7, 0xB8, 0x3B, 0xDC, 0x7E, 0xBE, 0x61, 0xBD, 0x65, 0xA8, 0x50, 0xD7,
    0xB3, 0xC6, 0x6E, 0x61, 0x78, 0xED, 0xEB, 0xED, 0x58, 0xB2, 0xB4, 0xFE, 0xBD, 0x71, 0xF9, 0x9F, 0xE7, 0x17, 0xE7, 0x8C, 0x58, 0xB7, 0x50, 0xD3, 0x26, 0xA5, 0x4F, 0x3F, 0x8C, 0xD9, 0x7D, 0xE4, 0xEA, 0xD1, 0x47, 0xDF, 0x7F, 0xE7, 0x0D, 0x5F,
    0xCF, 0xF5, 0xE7, 0xDB, 0xED, 0xE1, 0xCE, 0x4B, 0x9F, 0x4E, 0x9F, 0x43, 0xA9, 0x5F, 0x8E, 0x70, 0x1C, 0xBD, 0xEF, 0xEA, 0xAB, 0x6F, 0x7A, 0xEF, 0xEB, 0xDB, 0x5C, 0xFF, 0x7F, 0xB4, 0xEB, 0xAB, 0x3F, 0xA7, 0x7A, 0x22, 0xBD, 0x5F, 0x0E, 0x78,
    0xFB, 0xBC, 0xB3, 0xA2, 0xFE, 0x7A, 0xCA, 0x5F, 0xC7, 0x9E, 0x7D, 0x8E, 0xD7, 0x8B, 0xFD, 0xFD, 0x7A, 0x65, 0x8D, 0x16, 0x0E, 0x2E, 0xBC, 0xF7, 0xAA, 0x0B, 0xEE, 0x3A, 0xE6, 0x88, 0xCB, 0xBC, 0x38, 0xB1, 0xE5, 0xFA, 0x2F, 0xA7, 0xBE, 0xBA,
    0xED, 0xE1, 0x9F, 0xB4, 0x9E, 0xAD, 0xF5, 0xE1, 0x93, 0x6F, 0x21, 0x78, 0xDC, 0x59, 0x27, 0x8D, 0x38, 0xFB, 0xFE, 0xAB, 0x7F, 0xF1, 0x6F, 0xC1, 0x0F, 0x2D, 0x79, 0x9B, 0x6B, 0xF6, 0x97, 0xDE, 0x7C, 0xEC, 0xED, 0xEB, 0x5D, 0x9A, 0x18, 0x5B,
    0xFB, 0x13, 0xF3, 0x2C, 0x82, 0xFD, 0xCF, 0x65, 0xDE, 0xF4, 0xAA, 0xCE, 0xE1, 0x1B, 0xCC, 0x76, 0x7A, 0x67, 0xD1, 0x09, 0xBE, 0x16, 0xA2, 0xCD, 0xFA, 0x13, 0xB3, 0x90, 0xDD, 0x73, 0x37, 0x47, 0x22, 0xB5, 0x3F, 0x31, 0xC3, 0x47, 0x8F, 0xDE,
    0xAF, 0x04, 0xF1, 0x75, 0xE5, 0xFD, 0xD8, 0x6F, 0x93, 0xD6, 0x5E, 0xD5, 0xFB, 0x77, 0xE4, 0x2D, 0x76, 0xC0, 0xE8, 0xD6, 0x3C, 0x75, 0xFB, 0xF7, 0xAB, 0x48, 0xDE, 0x7D, 0x60, 0xDF, 0x87, 0x1C, 0xF9, 0x1F, 0xB7, 0x2F, 0xEB, 0x7E, 0xBA, 0x5A,
    0xA7, 0x2E, 0xEB, 0xFB, 0x93, 0x7A, 0x8F, 0x6D, 0xAF, 0x2B, 0xBB, 0x1A, 0xA9, 0x9F, 0x70, 0x7E, 0xDF, 0x46, 0xDC, 0xA5, 0x9F, 0x27, 0x95, 0xEC, 0x2F, 0x3D, 0x0D, 0x5F, 0x75, 0xD1, 0x09, 0xAF, 0x13, 0xEE, 0x4C, 0x4B, 0xB8, 0x7F, 0x6B, 0xBA,
    0xE1, 0xFB, 0xD8, 0x6B, 0xF8, 0x93, 0x86, 0x1F, 0x3F, 0xFC, 0x3C, 0x86, 0x7F, 0x2E, 0x1B, 0x82, 0x57, 0x0D, 0xBF, 0xD0, 0xAD, 0x85, 0x94, 0xB5, 0x6A, 0xE2, 0x41, 0xEC, 0x1B, 0xF2, 0x16, 0x22, 0x3F, 0x3A, 0x23, 0x8E, 0xFA, 0x5A, 0x5F, 0xF3,
    0xCD, 0x10, 0xFA, 0x69, 0xFD, 0xFC, 0x8D, 0x66, 0x6C, 0xFE, 0x89, 0xF2, 0xAB, 0xDE, 0x67, 0xC5, 0xF2, 0x03, 0x48, 0x31, 0xB0, 0x82, 0x03, 0x4A, 0x34, 0x8B, 0xF2, 0x8F, 0xFC, 0xBC, 0xDF, 0xA8, 0xCB, 0xDF, 0xFC, 0x04, 0x48, 0xCD, 0x97, 0x13,
    0x58, 0xE7, 0xE7, 0xEF, 0x5B, 0x78, 0xED, 0xBF, 0x0E, 0x3F, 0x6C, 0x2F, 0xB5, 0xAF, 0x1B, 0x45, 0x03, 0x0F, 0x4F, 0xDC, 0xEE, 0xF1, 0x1A, 0x04, 0x32, 0x7D, 0x90, 0xA5, 0x0C, 0xBF, 0x3D, 0xED, 0x47, 0xCD, 0x9D, 0x78, 0xE2, 0xD1, 0x9F, 0x1E,
    0x59, 0x17, 0xD5, 0x67, 0x74, 0x7D, 0x04, 0x1F, 0xFC, 0xDE, 0x50, 0x09, 0x62, 0xDA, 0x3F, 0x7F, 0x8C, 0xF8, 0x0F, 0x4F, 0xF4, 0x70, 0xDE, 0xAF, 0x0F, 0xBE, 0xBC, 0x37, 0xAE, 0xCF, 0xBD, 0xF2, 0xB4, 0x85, 0xDF, 0x42, 0x5F, 0x05, 0x5D, 0xE4,
    0x8C, 0x7D, 0x79, 0x37, 0xBF, 0x7E, 0xF0, 0x20, 0xC7, 0x6F, 0x92, 0xF9, 0xD4, 0x0B, 0x5F, 0x50, 0x83, 0xBB, 0xD4, 0xA7, 0x5F, 0x7D, 0x70, 0x02, 0x3E, 0x5E, 0xE1, 0x8F, 0xE6, 0x0F, 0x87, 0xDB, 0x8A, 0x9B, 0xC7, 0x46, 0xF3, 0x6F, 0x3C, 0x73,
    0x98, 0x1E, 0xFD, 0xDC, 0xB3, 0x1F, 0xBB, 0xF4, 0x08, 0x0B, 0xAD, 0x40, 0xFB, 0x1F, 0xC1, 0xA3, 0x9F, 0x7E, 0x80, 0x2B, 0xC4, 0x53, 0x6F, 0xBA, 0x94, 0x9D, 0xFD, 0xE7, 0x44, 0xE5, 0x9F, 0x7F, 0xF1, 0x36, 0xDF, 0x3E, 0x5E, 0x6D, 0xEA, 0x29,
    0xB4, 0x5F, 0x7D, 0x35, 0x7B, 0x0F, 0x1F, 0xB1, 0xAD, 0xED, 0x97, 0xF5, 0x7D, 0xBD, 0xC5, 0x4C, 0xEE, 0xD0, 0xE0, 0x81, 0x07, 0x4C, 0x41, 0xE8, 0x64, 0x0B, 0x77, 0xFE, 0xD9, 0xA3, 0xE3, 0xD3, 0x75, 0xA5, 0x88, 0xA3, 0x5F, 0xD8, 0xF5, 0x99,
    0x4F, 0x60, 0xA4, 0xFA, 0xB8, 0x03, 0x7B, 0xBF, 0xD3, 0xF7, 0x43, 0xEF, 0x9A, 0xD5, 0x87, 0x8D, 0xCE, 0xAF, 0x71, 0xD7, 0xDA, 0x8F, 0x39, 0xDC, 0xA6, 0xEF, 0x8A, 0x7D, 0x64, 0xBE, 0xA1, 0x76, 0xBB, 0xF8, 0xF5, 0x8F, 0x5B, 0xBE, 0xB0, 0x9C,
    0xDF, 0x66, 0x3F, 0xFA, 0xD0, 0x37, 0xAE, 0xFF, 0xFE, 0xDB, 0x97, 0x77, 0x3F, 0xD6, 0xE4, 0x2B, 0x7E, 0xFF, 0xFD, 0x1D, 0xC9, 0x68, 0xFF, 0xF4, 0xE7, 0xDB, 0xDF, 0xBD, 0xE6, 0x9A, 0x2B, 0x3F, 0x81, 0x61, 0xC5, 0x37, 0x3D, 0xFD, 0xF7, 0x7D,
    0x4F, 0x08, 0xA9, 0xFB, 0xBC, 0x47, 0x7F, 0xF2, 0xFB, 0x1D, 0xAB, 0x53, 0x68, 0x7B, 0xED, 0xBF, 0x73, 0xF0, 0x2B, 0xBF, 0xFF, 0xFD, 0x85, 0x4A, 0xA0, 0x50, 0xF9, 0xE7, 0x6E, 0xFF, 0x32, 0xE5, 0x6F, 0xFF, 0x98, 0xF7, 0xFF, 0xFD, 0xFD, 0xBB,
    0x1F, 0x57, 0xF9, 0x47, 0x2F, 0xB8, 0xA4, 0xFB, 0xFF, 0xD3, 0xF0, 0x09, 0xEB, 0x9F, 0xFF, 0xD0, 0xED, 0xC6, 0x2C, 0x50, 0xF3, 0x8D, 0x7D, 0xBA, 0xF2, 0xF2, 0xE7, 0x71, 0x50, 0xE6, 0xDB, 0xFE, 0xFE, 0xB3, 0x8F, 0xBE, 0xFC, 0x87, 0xC5, 0x3C,
    0xB3, 0xE5, 0x7F, 0xFE, 0x13, 0xBB, 0x7F, 0xBF, 0x9A, 0xDD, 0xEF, 0x57, 0xFE, 0x7B, 0x6B, 0x7E, 0xF4, 0x89, 0xA7, 0x7E, 0x80, 0x15, 0xEB, 0xDF, 0xF9, 0x4E, 0xB5, 0x9F, 0xFD, 0x16, 0xB2, 0xFA, 0x37, 0xD0, 0xB5, 0xBE, 0x3F, 0xF2, 0xC8, 0xAE,
    0x3A, 0x75, 0x05, 0x28, 0x66, 0x7E, 0xF5, 0x47, 0x77, 0x6D, 0x65, 0x56, 0x69, 0x24, 0xE1, 0x62, 0xF6, 0x73, 0x9F, 0xDB, 0xF6, 0x73, 0xBD, 0xF8, 0xD4, 0xA7, 0x3A, 0x52, 0x3B, 0x67, 0x7F, 0xFD, 0xD2, 0x5F, 0x80, 0x02, 0x10, 0xB3, 0xDF, 0xF7,
    0xD3, 0xB7, 0x9F, 0xFE, 0x7B, 0x9A, 0xB0, 0xD2, 0xFA, 0xEB, 0xCE, 0xEB, 0x67, 0xD9, 0x5F, 0x7F, 0xFD, 0xFF, 0x7B, 0x7E, 0xFB, 0xFD, 0xCC, 0x7E, 0xE1, 0xE5, 0x56, 0x77, 0xF4, 0x23, 0x6B, 0xBD, 0xF1, 0xAB, 0x04, 0x3A, 0xD9, 0x45, 0xEF, 0x7E,
    0x11, 0x5E, 0x8F, 0x2D, 0xFB, 0x9B, 0xCF, 0xFB, 0xED, 0xFF, 0xFE, 0xFE, 0x38, 0x45, 0x3F, 0xFA, 0xC7, 0x2F, 0x3D, 0x57, 0x3F, 0xFE, 0x2B, 0x7F, 0xD6, 0x6E, 0x2F, 0xAE, 0x04, 0xEC, 0x87, 0x3F, 0xDA, 0x49, 0x0D, 0x57, 0xBC, 0x59, 0x3B, 0x1A,
    0x64, 0xDE, 0x8F, 0xDB, 0xF7, 0x34, 0xC7, 0x3E, 0x3F, 0xD9, 0x87, 0xBF, 0x7C, 0xF3, 0x76, 0x97, 0x02, 0xF0, 0xF3, 0x9E, 0xF8, 0xB7, 0x56, 0xAC, 0xFE, 0x5E, 0xDF, 0xD4, 0x5D, 0x6E, 0xE9, 0x6F, 0x60, 0xFA, 0xD7, 0xCE, 0x60, 0xFA, 0x33, 0x5D,
    0x7F, 0x2A, 0xE9, 0x4F, 0x7F, 0xEA, 0xE7, 0x38, 0xC2, 0xF7, 0x63, 0xAF, 0x7E, 0xC7, 0xD3, 0x48, 0xFF, 0x95, 0xE9, 0x1F, 0xFC, 0x24, 0x4D, 0xCC, 0xB5, 0xF3, 0x95, 0x4D, 0x7F, 0x15, 0xE9, 0x4F, 0x7F, 0xF0, 0x23, 0x99, 0xDC, 0x03, 0xD5, 0x9F,
    0xCE, 0x46, 0x7B, 0x7F, 0x44, 0xFA, 0x7B, 0xFF, 0xCA, 0xD4, 0x5F, 0x3E, 0x86, 0x71, 0xEF, 0x2F, 0xB8, 0xE8, 0xCF, 0xF5, 0xF7, 0x25, 0x1D, 0xF7, 0xB8, 0x9F, 0x3F, 0xC0, 0xC8, 0xA4, 0x0E, 0xFE, 0xC8, 0x92, 0x16, 0x78, 0x6C, 0x53, 0x2B, 0x9A,
    0xF3, 0x54, 0x3E, 0x3E, 0xF9, 0xA3, 0x8E, 0xFD, 0x3C, 0x7B, 0xDF, 0xFF, 0x3A, 0x8F, 0xD8, 0xF4, 0x14, 0xF8, 0xDF, 0xFF, 0x7E, 0x7E, 0x7F, 0xBB, 0xF1, 0x74, 0x7A, 0x7A, 0xBF, 0x0F, 0xFF, 0xD1, 0xC7, 0x7F, 0xFE, 0x15, 0x70, 0xE0, 0x7F, 0xFD,
    0x7F, 0x9D, 0xFD, 0x48, 0x1E, 0xBE, 0xEE, 0x17, 0x7D, 0x51, 0x99, 0x55, 0x76, 0x7F, 0xBE, 0xEE, 0x7F, 0x7F, 0x17, 0x64, 0xF8, 0x9F, 0xFF, 0x5D, 0x70, 0xC1, 0x01, 0xFB, 0x7D, 0x9F, 0x78, 0xED, 0x77, 0x9E, 0xE6, 0xA7, 0x37, 0xB8, 0xED, 0x87,
    0xAF, 0xFE, 0xE7, 0x73, 0x9F, 0x03, 0xF5, 0x93, 0x61, 0x48, 0x02, 0x65, 0x70, 0x81, 0x7D, 0x79, 0x89, 0x0F, 0x32, 0x97, 0xA7, 0x7D, 0x7D, 0xCE, 0x3E, 0x4C, 0x7E, 0x29, 0xAE, 0xDF, 0x7E, 0xEB, 0xB7, 0xBF, 0x1D, 0xF6, 0x67, 0x3F, 0xFA, 0xDA,
    0x57, 0xE7, 0xF4, 0x13, 0x45, 0x6D, 0xAF, 0xEA, 0xC7, 0xAA, 0xF3, 0xDB, 0xBF, 0x1F, 0xF9, 0xCB, 0x47, 0x7E, 0xFC, 0x11, 0xFF, 0x54, 0x1D, 0x33, 0x9F, 0xF9, 0xAE, 0x1F, 0xFA, 0xF5, 0xCF, 0x1F, 0x7E, 0xDE, 0x8F, 0x7F, 0xFB, 0xF2, 0x9F, 0x7F,
    0xF9, 0x53, 0xF7, 0x7C, 0xE8, 0x83, 0x1F, 0xFC, 0xD6, 0x67, 0x5F, 0xF7, 0x1E, 0xFC, 0x8A, 0x7D, 0xB3, 0x9A, 0x9F, 0xEE, 0x76, 0xFF, 0x7E, 0xE1, 0x9B, 0xAE, 0xB4, 0xFD, 0x29, 0x7F, 0x7F, 0x99, 0xD6, 0xFF, 0xEE, 0xF8, 0x27, 0xB1, 0xBA, 0x78,
    0xAA, 0x4A, 0xF5, 0xD8, 0xB7, 0x13, 0xED, 0x18, 0xDF, 0xBE, 0x2C, 0x91, 0x55, 0xFD, 0xB8, 0xE1, 0xFF, 0x64, 0x30, 0xF1, 0xBF, 0xFD, 0x67, 0xCE, 0x3F, 0xFF, 0xD8, 0x4E, 0x14, 0x57, 0x66, 0x61, 0x9B, 0xFF, 0x3E, 0xEB, 0x7F, 0xFC, 0xF7, 0x24,
    0x5D, 0xFE, 0xF8, 0x57, 0x7F, 0xDE, 0xF0, 0x8F, 0xF4, 0xA3, 0xF8, 0xC7, 0xBF, 0x87, 0xC2, 0x9F, 0x7A, 0xF5, 0xED, 0x9F, 0xFF, 0x62, 0xF2, 0x9F, 0xFE, 0xFB, 0xFF, 0xBF, 0xFF, 0xFD, 0xEF, 0x7F, 0xFF, 0xFB, 0xDF, 0xFF, 0xFE, 0xF7, 0xBF, 0xFF,
    0xFD, 0xEF, 0x7F, 0xFF, 0xFB, 0x9F, 0xFF, 0xFF, 0x0F
};

image_info_t clock_bln43_info =
{
    .type  = IMG_TYPE_COMPRESS,
    .pixel = RTGRAPHIC_PIXEL_FORMAT_RGB332,
    .x = 0,
    .y = 0,
    .w = 120,
    .h = 120,
    .size = 1569UL,
    .data =  clock_bln43_120_120,
};

#endif
