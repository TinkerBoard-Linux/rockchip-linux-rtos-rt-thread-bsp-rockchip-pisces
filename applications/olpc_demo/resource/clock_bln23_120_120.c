/**
  * Copyright (c) 2019 Fuzhou Rockchip Electronics Co., Ltd
  *
  * SPDX-License-Identifier: Apache-2.0
  */

#include <rtthread.h>
#if defined(OLPC_APP_CLOCK_BLN_ENABLE) && (defined(OLPC_STATICLD_ENABLE) || defined(OLPC_OVERLAY_ENABLE))
#include "image_info.h"

static const unsigned char clock_bln23_120_120[1751UL] =
{
    0x03, 0x00, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE,
    0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0x00, 0x08, 0xFC, 0x13, 0xFC,
    0xFB, 0xE7, 0x9F, 0xDF, 0xBF, 0xFD, 0xFB, 0xF2, 0x97, 0xDB, 0xFF, 0xCF, 0x7F, 0x01, 0x81, 0xFF, 0x7C, 0xD4, 0xF3, 0xE3, 0xFB, 0x97, 0x0F, 0x7B, 0xFE, 0xFC, 0x05, 0xFF, 0xF2, 0xC5, 0xEF, 0xFF, 0xCF, 0xFF, 0xFB, 0xF8, 0xF1, 0xEE, 0xC5, 0xBB,
    0xBF, 0xEC, 0x7E, 0x7E, 0xFF, 0xFF, 0xF2, 0xD9, 0xCF, 0xA7, 0x2F, 0x7E, 0xFE, 0x75, 0xF2, 0xDA, 0xEB, 0x67, 0xB7, 0xAE, 0x3F, 0xF9, 0xF7, 0x09, 0x09, 0xEE, 0xE3, 0x8F, 0x4F, 0xD7, 0x9D, 0x7C, 0x7E, 0xF9, 0xFF, 0xBA, 0xE3, 0xE3, 0x86, 0x3F,
    0x61, 0x3B, 0x7E, 0x75, 0xD5, 0xC8, 0xBB, 0x63, 0x67, 0xFD, 0x5B, 0xF5, 0xED, 0xDA, 0xF1, 0xAB, 0x57, 0x2F, 0x9F, 0xB9, 0x7C, 0x7B, 0xE4, 0x67, 0x4F, 0xDF, 0x0E, 0x9D, 0x20, 0x1F, 0x7B, 0xEF, 0xD4, 0x89, 0x43, 0x47, 0xD7, 0x1E, 0xFC, 0xAA,
    0x7A, 0xE7, 0xAC, 0x75, 0x2F, 0xD8, 0xB7, 0x6C, 0x5D, 0x37, 0x5D, 0xCA, 0xC0, 0x5F, 0xAB, 0x8F, 0x2F, 0xD4, 0xFC, 0xF3, 0xE3, 0x1D, 0xDA, 0xE1, 0x73, 0x4F, 0x2B, 0x1E, 0xFE, 0xE4, 0xCB, 0x43, 0xA9, 0x8B, 0xAE, 0x7C, 0x3A, 0xB7, 0x78, 0xF8,
    0xBB, 0xAD, 0x92, 0xE6, 0x7E, 0x59, 0x77, 0x4E, 0xE4, 0xA6, 0xFF, 0x2E, 0x70, 0x70, 0x60, 0x86, 0x9D, 0x9B, 0x28, 0x75, 0xF8, 0xE2, 0x63, 0x5A, 0x67, 0x1C, 0x7F, 0x82, 0x7A, 0xEC, 0xF9, 0x35, 0xA7, 0x66, 0x76, 0xCB, 0x97, 0x24, 0x79, 0xB3,
    0x85, 0xAF, 0xC6, 0x4F, 0x8E, 0xFC, 0xEE, 0x93, 0xE8, 0x1F, 0xE7, 0xD5, 0xFA, 0x11, 0xEF, 0x6D, 0xAA, 0xE2, 0xF3, 0x1B, 0x9D, 0xBF, 0xFC, 0x09, 0x1A, 0xFC, 0xB5, 0x4F, 0xA4, 0x6A, 0xF9, 0xEC, 0x13, 0x0F, 0x3B, 0xF6, 0x7C, 0x99, 0x6F, 0xBF,
    0x3E, 0x7E, 0x3D, 0xBF, 0xF1, 0xBE, 0xE6, 0x6F, 0x9E, 0x78, 0x21, 0x97, 0x37, 0x48, 0x9D, 0x99, 0xFD, 0xFC, 0xC3, 0xFE, 0x0D, 0x6C, 0x5E, 0x65, 0xC8, 0xE6, 0x85, 0x9F, 0x59, 0x7C, 0xFC, 0x6E, 0x57, 0xC7, 0x1F, 0x7E, 0xB5, 0x7D, 0xE3, 0xAF,
    0xB8, 0xBF, 0xDB, 0xF2, 0x23, 0xAF, 0x9E, 0xF5, 0xF3, 0xA9, 0xF7, 0x18, 0x3C, 0xF3, 0xD3, 0xDF, 0xD8, 0x5C, 0xFE, 0xDD, 0xD3, 0x5F, 0xD2, 0x6D, 0x7B, 0xE6, 0x1B, 0x0F, 0x7E, 0x73, 0x19, 0x3B, 0xFF, 0xCD, 0x8F, 0x71, 0x6F, 0x64, 0x95, 0x3F,
    0x5F, 0x3F, 0xFB, 0x79, 0x5F, 0x4C, 0x7D, 0xFB, 0xFA, 0xC1, 0x2C, 0xDD, 0x3D, 0xDD, 0x59, 0x0F, 0xBF, 0x34, 0xF7, 0x68, 0x73, 0xDE, 0xBB, 0xA8, 0x32, 0xE9, 0x5B, 0x9C, 0xBE, 0xFE, 0xCA, 0x8B, 0x8D, 0x7B, 0xC0, 0x0D, 0xE6, 0xBF, 0xAF, 0xF3,
    0xFC, 0xFD, 0x16, 0x9F, 0xBE, 0xCE, 0x2A, 0x32, 0x4E, 0x5F, 0x68, 0xFD, 0xC1, 0x1C, 0x4B, 0x5F, 0xFE, 0x78, 0x73, 0x8F, 0x5E, 0x44, 0xD1, 0xE9, 0xB3, 0xFE, 0x38, 0xF7, 0x94, 0xD7, 0x8B, 0x3E, 0xF1, 0xC7, 0x4B, 0x2F, 0x02, 0xE1, 0xF4, 0xC7,
    0xD4, 0x5F, 0xFF, 0xF1, 0xE3, 0x8A, 0xEC, 0x62, 0xED, 0xCB, 0x47, 0x9F, 0x7E, 0x4D, 0xE6, 0xC7, 0x4F, 0x5F, 0x6E, 0x8A, 0x55, 0x91, 0x47, 0x7E, 0x7D, 0xF0, 0xC1, 0x4F, 0x7E, 0x7D, 0x89, 0xF1, 0xFF, 0xF4, 0xEE, 0x9E, 0x27, 0x88, 0x00, 0x1C,
    0x7D, 0x36, 0xE9, 0x07, 0x2C, 0xF4, 0xCC, 0x8D, 0x9F, 0xDF, 0xB5, 0xF4, 0xBC, 0x23, 0x6F, 0x26, 0xEF, 0xF5, 0x23, 0x4F, 0xFA, 0x89, 0x9F, 0xA7, 0xC5, 0x59, 0xFE, 0xC7, 0xBD, 0xD4, 0x5F, 0xE2, 0x96, 0xA3, 0x8F, 0x76, 0xE9, 0x61, 0x4B, 0x2F,
    0x01, 0x3D, 0xFA, 0xDC, 0x47, 0x9F, 0xBE, 0xB1, 0xF4, 0x9B, 0x0E, 0xA1, 0x56, 0x0D, 0x24, 0x5C, 0x9F, 0xBF, 0x7B, 0xF9, 0xDF, 0x85, 0x36, 0xF3, 0xE1, 0x33, 0xB5, 0x50, 0xCE, 0xC0, 0xE7, 0x77, 0xBE, 0x7D, 0xC6, 0xE5, 0x97, 0x9F, 0xF1, 0xC6,
    0xEB, 0xC7, 0xDD, 0xF9, 0xF3, 0xCD, 0xAF, 0x9F, 0xC4, 0x88, 0xAF, 0x35, 0x43, 0x7E, 0xE5, 0x5D, 0x3F, 0x8F, 0x1F, 0xF0, 0x09, 0x8B, 0x20, 0xFF, 0xDC, 0x12, 0x1F, 0x8D, 0x3F, 0xFE, 0x0E, 0xEE, 0x8F, 0xDF, 0x6E, 0x8F, 0xC0, 0xD3, 0x5E, 0x3D,
    0x86, 0x5C, 0x9F, 0xF1, 0x1F, 0x7B, 0xEC, 0x41, 0x16, 0x0F, 0xC8, 0x8A, 0x49, 0xC8, 0xAF, 0x78, 0xF0, 0xE8, 0xCF, 0x3F, 0xB9, 0xD3, 0x21, 0xEF, 0x99, 0xFA, 0xF0, 0x5A, 0x0E, 0xF8, 0xF9, 0x19, 0x7B, 0xCC, 0x77, 0x6F, 0x7E, 0xCC, 0xDD, 0x0B,
    0xDD, 0x82, 0xF0, 0x5E, 0x51, 0xD7, 0x1B, 0xF8, 0xBA, 0xEC, 0x39, 0x2F, 0xF8, 0x83, 0xDA, 0xCB, 0x5E, 0x2E, 0x0B, 0xE0, 0x67, 0x2C, 0x5F, 0xD1, 0x7B, 0xF0, 0xCF, 0xEF, 0x35, 0xE3, 0xCD, 0x57, 0x0D, 0xE2, 0xFC, 0x10, 0x0B, 0x38, 0x3F, 0x07,
    0xF9, 0xC9, 0xFF, 0xBD, 0x3F, 0xDA, 0xEF, 0x96, 0x52, 0x83, 0xFC, 0xC8, 0xD6, 0x27, 0xBF, 0xF9, 0xB2, 0xCF, 0xDE, 0x3C, 0xF6, 0x95, 0xE5, 0x77, 0x3E, 0x0B, 0x87, 0xE5, 0x0F, 0xEE, 0x6B, 0xF9, 0x99, 0x4F, 0x1B, 0xF0, 0xED, 0xC9, 0x6C, 0xC1,
    0xC2, 0x61, 0xEE, 0xCE, 0xBF, 0x89, 0x76, 0xB4, 0xAB, 0x34, 0xFF, 0xFC, 0xB5, 0x8D, 0x96, 0xBF, 0x57, 0x34, 0x51, 0x13, 0xBC, 0xF0, 0xD3, 0xD1, 0x76, 0xDE, 0xF4, 0xF3, 0x99, 0x14, 0x21, 0xBF, 0xB5, 0xB3, 0x6D, 0x56, 0xE1, 0xE3, 0x76, 0x6B,
    0x0E, 0x25, 0xF9, 0x19, 0x3E, 0xB7, 0x6B, 0xE6, 0xE9, 0xBA, 0x57, 0x77, 0xE3, 0x82, 0x73, 0xDD, 0x60, 0xDF, 0x0E, 0xCA, 0x9F, 0xE5, 0xE6, 0xF3, 0x57, 0x37, 0xFF, 0xD7, 0x26, 0x5A, 0x6E, 0x37, 0xD2, 0x15, 0xE3, 0xB8, 0x6B, 0xF0, 0xF2, 0xEF,
    0x56, 0xD7, 0xC3, 0x42, 0x17, 0x4D, 0x7B, 0xED, 0x9D, 0x8F, 0xFA, 0x71, 0x0D, 0x56, 0x83, 0xB7, 0x19, 0xAB, 0xE6, 0x73, 0x46, 0xDD, 0x68, 0xE7, 0x71, 0xB6, 0x5B, 0x65, 0xE0, 0x09, 0x9E, 0x7D, 0x82, 0x56, 0xC2, 0xCA, 0x0F, 0xB9, 0xBB, 0xE6,
    0x63, 0x26, 0xAC, 0xF6, 0xDA, 0x9B, 0x9F, 0x20, 0xFD, 0x1C, 0x48, 0x20, 0x78, 0x7E, 0x98, 0x07, 0x3F, 0x5F, 0x7E, 0xDA, 0xCF, 0x0F, 0xAA, 0x59, 0xE7, 0xBB, 0xE7, 0x9E, 0x7B, 0xF1, 0xCC, 0x7C, 0x40, 0x83, 0x2D, 0x77, 0x9F, 0xBE, 0x49, 0xDA,
    0x6E, 0xFB, 0x5E, 0xFB, 0xC9, 0xC3, 0x4A, 0x3E, 0xF3, 0x6B, 0x13, 0x0D, 0x6C, 0xA3, 0x36, 0x1D, 0x49, 0xBD, 0xE2, 0xA5, 0x0B, 0x9B, 0xFF, 0x0A, 0xFB, 0x94, 0x40, 0x7E, 0x11, 0x00, 0xBB, 0x7A, 0xFC, 0x47, 0x8A, 0x3F, 0xB7, 0x2D, 0xCB, 0x0F,
    0x6D, 0xD2, 0x08, 0x76, 0x31, 0x78, 0xA2, 0xB1, 0xBF, 0x3A, 0x4D, 0xCF, 0x3A, 0xD0, 0x40, 0xF7, 0xEB, 0xEB, 0xFD, 0x39, 0xFC, 0x73, 0x08, 0xFF, 0xF1, 0x8F, 0x5F, 0xF9, 0x28, 0xD2, 0x69, 0x27, 0xFE, 0xC7, 0x9F, 0xFE, 0x52, 0xB9, 0xC7, 0xBD,
    0x43, 0x8B, 0x67, 0x81, 0x06, 0x12, 0xDC, 0x5F, 0xF8, 0xE9, 0xF7, 0x68, 0xFB, 0xF7, 0x4F, 0xC0, 0xF9, 0x6D, 0x87, 0xCF, 0xF9, 0xF8, 0x3A, 0x5E, 0x66, 0xF8, 0xA4, 0xBE, 0x7F, 0x9F, 0x30, 0xA1, 0x1F, 0xFE, 0xE9, 0x0F, 0xB3, 0x7E, 0x2B, 0xA7,
    0x9F, 0x7B, 0x16, 0x6C, 0x30, 0xF8, 0xF4, 0xB2, 0x8F, 0xFE, 0x96, 0x1A, 0x45, 0xFF, 0xEF, 0x4F, 0x77, 0xFF, 0x64, 0x0F, 0xB5, 0x36, 0x02, 0x0D, 0xF0, 0xB7, 0x7C, 0xE2, 0xCF, 0x6E, 0x25, 0xFC, 0xD1, 0x5B, 0x7E, 0x33, 0xCB, 0xDA, 0x5A, 0x52,
    0xD6, 0xF9, 0xDA, 0xC0, 0xFB, 0xDE, 0x7F, 0x3F, 0xF0, 0x0D, 0x4F, 0xA5, 0xFB, 0xA3, 0xD8, 0xBF, 0xE5, 0x2D, 0x4F, 0xD2, 0x03, 0xF5, 0x95, 0x00, 0x7D, 0xF0, 0x43, 0xDF, 0xE8, 0xB2, 0x4F, 0x11, 0xFE, 0x6C, 0x97, 0xBE, 0x4D, 0xF9, 0x5F, 0x1E,
    0xFA, 0x29, 0x96, 0x40, 0x03, 0xF8, 0x9F, 0xFF, 0xFE, 0xC0, 0x16, 0x40, 0x52, 0xEB, 0x1F, 0x0C, 0x7E, 0xEB, 0xCA, 0xDE, 0xE1, 0xE1, 0x8E, 0x8E, 0x5E, 0xE0, 0xDA, 0x75, 0xFF, 0x06, 0xD7, 0xAB, 0x9F, 0x06, 0xFF, 0x73, 0xBE, 0xF5, 0x41, 0x6A,
    0x95, 0xCF, 0x62, 0x93, 0x66, 0xF9, 0xE3, 0xAF, 0xAD, 0xFA, 0xDF, 0xDD, 0xBE, 0x7C, 0xCD, 0x6F, 0x7E, 0xFD, 0xFE, 0x37, 0xFD, 0xCC, 0xB3, 0x0F, 0xBF, 0x46, 0xD9, 0x87, 0xE2, 0xFB, 0xAF, 0xAD, 0x77, 0x53, 0x2C, 0x0F, 0x74, 0x5D, 0xF1, 0x77,
    0xB0, 0xFF, 0x0E, 0xFF, 0x53, 0xBF, 0xF6, 0x1A, 0xE8, 0x9E, 0x70, 0xF5, 0xAF, 0xBF, 0xF8, 0x5F, 0x66, 0xBF, 0xC4, 0xEC, 0xA7, 0x7B, 0xC7, 0xDA, 0x55, 0xFA, 0xFD, 0x36, 0xD8, 0xE1, 0x8B, 0xFF, 0xCD, 0xAF, 0x7E, 0xC0, 0x8F, 0xB5, 0xFE, 0x82,
    0x7B, 0x70, 0x79, 0xE2, 0x13, 0xDF, 0xE2, 0x39, 0xF5, 0x1B, 0x9F, 0x40, 0xD7, 0x80, 0x7D, 0xEB, 0xAF, 0xFF, 0x1E, 0x7B, 0x7C, 0x81, 0x3E, 0xDE, 0x57, 0x0D, 0x7C, 0x5C, 0x59, 0xBF, 0xFD, 0x8F, 0x43, 0x31, 0x82, 0x19, 0x6E, 0x4E, 0x34, 0x9D,
    0xE1, 0x1D, 0xA3, 0xC4, 0x18, 0x7D, 0x17, 0xFA, 0xEA, 0x37, 0xBF, 0x5F, 0x28, 0x2E, 0xFF, 0xF9, 0xFD, 0xDE, 0xDB, 0x36, 0x33, 0x9A, 0xE1, 0x11, 0x9D, 0xB5, 0x4F, 0xE3, 0xBE, 0x6F, 0x81, 0xF9, 0x7E, 0xF7, 0x3B, 0x43, 0x43, 0xBE, 0x7D, 0xE4,
    0x6F, 0xD0, 0xBD, 0xF9, 0xCD, 0x4F, 0xFE, 0xE6, 0x8B, 0xDE, 0xC8, 0x48, 0x47, 0x39, 0xBE, 0xFF, 0xCF, 0xE8, 0x5D, 0xFB, 0x1C, 0xDD, 0x3D, 0x57, 0x3A, 0xF7, 0x29, 0xCE, 0x5A, 0xD6, 0xAD, 0x97, 0x79, 0xF3, 0x81, 0xCC, 0xF9, 0xCF, 0xFF, 0x42,
    0x60, 0xF2, 0x2B, 0xFF, 0x17, 0xAE, 0x2F, 0x3D, 0xBF, 0xC1, 0xFE, 0x3F, 0xF9, 0xC5, 0x2F, 0x02, 0x07, 0x3C, 0xDD, 0x7A, 0xFB, 0xB2, 0x97, 0x3D, 0xCA, 0x3D, 0x95, 0x3D, 0xD5, 0x55, 0x9B, 0xE1, 0xC2, 0xC3, 0xBE, 0xFC, 0xCB, 0xC7, 0x3C, 0xF9,
    0x6F, 0x30, 0x3A, 0xC8, 0x73, 0x9B, 0xFC, 0x7D, 0xC6, 0x4F, 0x6A, 0xFE, 0x2B, 0xFB, 0xD4, 0xE7, 0x07, 0xF7, 0xEC, 0xE9, 0x39, 0xBF, 0xAE, 0x8B, 0x0E, 0x6E, 0xE6, 0x37, 0x9F, 0xB8, 0xB2, 0xF7, 0xBB, 0xDF, 0xFF, 0x9E, 0x70, 0x5D, 0xFF, 0x9F,
    0xFF, 0xCF, 0xF7, 0x71, 0xC0, 0xC1, 0x7D, 0xF1, 0x64, 0x9F, 0xFF, 0xFC, 0x11, 0x75, 0x3E, 0x45, 0xD1, 0x6D, 0x76, 0x3B, 0x8C, 0x9B, 0x79, 0xF2, 0x5B, 0x1E, 0xED, 0xCE, 0x17, 0xB7, 0xAC, 0xA7, 0x4F, 0xE7, 0xF4, 0x3F, 0x98, 0x9C, 0xBC, 0x4D,
    0xFF, 0x9C, 0xA7, 0xBD, 0x42, 0xF4, 0xA7, 0xCF, 0xFB, 0xEB, 0x43, 0x9D, 0xFD, 0xBC, 0x37, 0x3C, 0xEF, 0x11, 0xEA, 0xFA, 0x45, 0x47, 0x1C, 0xC4, 0x33, 0xC6, 0xFA, 0x1D, 0xE1, 0x32, 0x3D, 0xB5, 0x2D, 0x27, 0xFA, 0xCA, 0x2F, 0xDE, 0x7E, 0x65,
    0xFF, 0x9F, 0xDD, 0xED, 0x56, 0xB5, 0xF6, 0xB7, 0x5F, 0x31, 0xC4, 0x3F, 0xA7, 0x58, 0xEF, 0xDE, 0x6C, 0x3D, 0xA7, 0x57, 0xDE, 0x6D, 0xF6, 0x5B, 0xDE, 0x0E, 0xF6, 0x97, 0xBC, 0xE4, 0xD6, 0x97, 0xBD, 0xFA, 0x37, 0xEE, 0x65, 0x21, 0x1A, 0x7F,
    0x90, 0xE9, 0x66, 0x7C, 0xE6, 0x51, 0xBD, 0x7E, 0xF4, 0x67, 0x1A, 0xEA, 0x08, 0x17, 0x57, 0xF4, 0xA3, 0x6F, 0x20, 0xF7, 0x8C, 0xC4, 0x78, 0xFC, 0x9D, 0xFC, 0x65, 0x46, 0xE3, 0x5D, 0xE8, 0x2B, 0x5F, 0x3D, 0xBA, 0x9D, 0xEF, 0x7C, 0x7E, 0x53,
    0x5E, 0xE1, 0x6C, 0xA4, 0xFA, 0xFF, 0xDD, 0xBD, 0x78, 0xFA, 0x9F, 0xB6, 0x88, 0xF3, 0x27, 0x3E, 0xFE, 0xFD, 0x2F, 0x6D, 0x71, 0x6D, 0xAE, 0xC2, 0x2E, 0xA9, 0x95, 0x3F, 0xBE, 0xEA, 0xA7, 0x7F, 0xFD, 0xFB, 0xCA, 0x7E, 0xF6, 0x93, 0x57, 0x67,
    0xD6, 0xD7, 0x7F, 0xFD, 0xEA, 0x97, 0xE0, 0xFA, 0x93, 0xBF, 0x40, 0x36, 0xE5, 0x6F, 0xB1, 0xF0, 0xBF, 0xB8, 0x40, 0x7C, 0x36, 0x39, 0xFF, 0x74, 0x54, 0x53, 0xB1, 0xE7, 0x8F, 0x98, 0xFE, 0xF4, 0xBB, 0x7F, 0xEA, 0xC9, 0x54, 0x5A, 0xFF, 0xFF,
    0x87, 0x7F, 0x34, 0xB5, 0x16, 0xBD, 0xFE, 0xF1, 0xBF, 0x7F, 0x39, 0xD9, 0xAF, 0x7F, 0xFC, 0xEF, 0x1F, 0xA9, 0xF4, 0xDF, 0x3F, 0xCB, 0xB0, 0x5F, 0xBF, 0xFE, 0xF5, 0xEF, 0xDF, 0x6B, 0xB1, 0xE5, 0x9B, 0xFE, 0x19, 0xAE, 0x7F, 0x06, 0xC1, 0xAF,
    0x7F, 0xB8, 0xC5, 0x1F, 0x97, 0x30, 0x5B, 0xFF, 0xFC, 0xF5, 0x0F, 0x11, 0xF6, 0x54, 0x23, 0x90, 0xFF, 0xF4, 0xC7, 0xBF, 0xD9, 0xFC, 0xAF, 0xFF, 0xFD, 0xFF, 0xDF, 0xFF, 0x52, 0xFA, 0x3F
};

image_info_t clock_bln23_info =
{
    .type  = IMG_TYPE_COMPRESS,
    .pixel = RTGRAPHIC_PIXEL_FORMAT_RGB332,
    .x = 0,
    .y = 0,
    .w = 120,
    .h = 120,
    .size = 1751UL,
    .data =  clock_bln23_120_120,
};

#endif
