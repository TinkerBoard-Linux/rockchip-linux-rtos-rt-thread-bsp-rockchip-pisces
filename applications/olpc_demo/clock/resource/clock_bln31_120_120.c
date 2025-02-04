/**
  * Copyright (c) 2019 Fuzhou Rockchip Electronics Co., Ltd
  *
  * SPDX-License-Identifier: Apache-2.0
  */

#include <rtthread.h>
#if defined(OLPC_APP_CLOCK_BLN_ENABLE)
#include "applications/common/image_info.h"

static const unsigned char clock_bln31_120_120[1824UL] =
{
    0x03, 0x00, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE,
    0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xCF, 0x1F, 0x01, 0x80, 0xFF, 0x7F, 0x04, 0xFE, 0xFA, 0xF1, 0xE3, 0xA7, 0xEF, 0xDF, 0xB8, 0x7D, 0xFD, 0xF4, 0xFF, 0xD3, 0xEF, 0x1F, 0x7F, 0xBE, 0xFC, 0xFA, 0xE2, 0xEB,
    0xD3, 0xFF, 0xEF, 0xDF, 0xBF, 0x7D, 0xFA, 0xE8, 0xE9, 0x47, 0xB7, 0xCF, 0xFE, 0xBE, 0x7F, 0xFF, 0xDE, 0xB9, 0xDF, 0x07, 0x9E, 0xDD, 0x3F, 0x7E, 0xFF, 0xF6, 0xB9, 0xDF, 0xBF, 0xAD, 0x1E, 0xFF, 0x7F, 0xFF, 0xE2, 0xB9, 0xDB, 0x2F, 0xBD, 0x3E,
    0xFF, 0x7F, 0xFE, 0xF9, 0xF1, 0x63, 0x4E, 0x9F, 0xFF, 0xBF, 0x7B, 0xFC, 0xF8, 0x19, 0xA7, 0xCF, 0xFF, 0x7C, 0x01, 0x81, 0xFF, 0x7F, 0xF6, 0xCD, 0xE5, 0xCF, 0xEF, 0x5B, 0x1F, 0xB7, 0x82, 0x7F, 0x09, 0xFF, 0xFE, 0xFD, 0xEB, 0xCF, 0x6F, 0xBF,
    0x7A, 0x7C, 0xE7, 0xF0, 0xD3, 0xCB, 0xA7, 0x1F, 0x7F, 0x43, 0x03, 0x3E, 0xFF, 0xF7, 0xF1, 0xAD, 0x8B, 0xEF, 0x1C, 0x7D, 0xBE, 0x79, 0xF9, 0xF3, 0x45, 0xFC, 0x8B, 0x90, 0xF8, 0xD7, 0xAF, 0x21, 0x42, 0x7F, 0x7D, 0x77, 0xE5, 0xAC, 0x35, 0x97,
    0x56, 0xBF, 0x3E, 0xBC, 0x84, 0x7C, 0xF6, 0x2D, 0x2C, 0x24, 0xFC, 0xD5, 0xAF, 0x6F, 0xEF, 0x5F, 0xFD, 0x72, 0xF6, 0xEC, 0x17, 0x57, 0x26, 0x8E, 0x1D, 0xBB, 0x7B, 0xFF, 0xDE, 0xCD, 0x17, 0x2F, 0xEE, 0xBE, 0x3B, 0xE2, 0xB8, 0x9A, 0xFB, 0xD2,
    0x5E, 0xE0, 0x8D, 0x1C, 0x3C, 0x0D, 0xF7, 0xF7, 0xD6, 0x73, 0x37, 0x67, 0x6F, 0x3A, 0x39, 0x7B, 0xB2, 0x6E, 0x8B, 0xEA, 0xE5, 0x3E, 0x7F, 0x35, 0xFB, 0x13, 0xDD, 0xE7, 0xF7, 0xDE, 0xBC, 0x98, 0xB5, 0x76, 0xEB, 0xB9, 0xD9, 0xB6, 0x7F, 0x89,
    0x76, 0xF9, 0xEB, 0x09, 0x16, 0x70, 0x7F, 0x6F, 0xFF, 0x7E, 0x7A, 0xEC, 0xD0, 0xCB, 0x9B, 0x7D, 0x69, 0x5C, 0x2F, 0x7F, 0xEB, 0x1B, 0x58, 0xD8, 0xB0, 0xDB, 0xFD, 0x04, 0x93, 0xFF, 0xB3, 0x6F, 0x6C, 0xFE, 0xD9, 0x13, 0x0C, 0x0F, 0xDA, 0x3E,
    0xC9, 0xEA, 0x49, 0x6B, 0x93, 0xAF, 0x41, 0x83, 0x04, 0xF2, 0x12, 0x5F, 0xC7, 0x97, 0x66, 0x7D, 0x6B, 0xED, 0x0B, 0xCD, 0x39, 0xAA, 0xEC, 0x92, 0xF1, 0xA3, 0xF7, 0x7B, 0x7D, 0xF6, 0x7C, 0x0B, 0x77, 0xCE, 0xAF, 0xE4, 0xC9, 0xF7, 0x29, 0xAE,
    0xAF, 0x7D, 0x90, 0xF7, 0x5B, 0x66, 0xBD, 0xFD, 0xFD, 0xBB, 0xE9, 0x1F, 0xDF, 0xF9, 0xF2, 0x19, 0xD4, 0x4F, 0xFB, 0xF7, 0x82, 0xBE, 0xDF, 0x95, 0x72, 0x6C, 0xB2, 0xBF, 0x8F, 0x7A, 0x65, 0xF5, 0x26, 0x56, 0x3D, 0x6C, 0x7D, 0xFD, 0x80, 0xA1,
    0x7A, 0x37, 0xDE, 0xF9, 0x9F, 0x4B, 0xE8, 0x5E, 0x78, 0xDD, 0xD4, 0x5B, 0xFD, 0xE2, 0x7D, 0xBD, 0xDF, 0xFF, 0x38, 0x47, 0xD5, 0xF0, 0xCB, 0x6C, 0x83, 0xEC, 0x98, 0xD3, 0x96, 0x18, 0xFA, 0x16, 0xA9, 0xB2, 0x4E, 0x1C, 0x7C, 0x1E, 0xD1, 0x17,
    0xAC, 0x41, 0xE4, 0xF0, 0x11, 0x7F, 0x3F, 0x7A, 0xF8, 0x85, 0x2D, 0x0D, 0x3D, 0xF8, 0xFB, 0x73, 0x6F, 0x33, 0xC1, 0xF0, 0xD7, 0xD0, 0xFB, 0xE8, 0x86, 0xE5, 0xA5, 0xBF, 0x46, 0xFC, 0x3C, 0xF3, 0x3E, 0xFB, 0xAC, 0xE9, 0xCD, 0xED, 0xDA, 0xE2,
    0xF8, 0x91, 0x8E, 0x5F, 0x5C, 0xF8, 0xE9, 0xBF, 0xDB, 0xF1, 0xAB, 0x87, 0x4F, 0x31, 0x7B, 0xE3, 0x07, 0x2B, 0xCC, 0x35, 0xCA, 0xE0, 0x63, 0x2C, 0x01, 0xCA, 0xD4, 0xD2, 0xF3, 0xDC, 0x69, 0xD3, 0xA5, 0x67, 0x3C, 0x7C, 0xBE, 0x7F, 0xE0, 0x67,
    0x3A, 0x7C, 0x40, 0xE1, 0x4F, 0x1C, 0xCF, 0xF1, 0x41, 0x4C, 0xBF, 0x2E, 0xF5, 0xD4, 0x53, 0x9D, 0x39, 0x97, 0xD7, 0x9B, 0x2D, 0x73, 0xED, 0xA4, 0x77, 0xCD, 0xF7, 0x1F, 0x92, 0x35, 0x47, 0x1A, 0x5B, 0x27, 0xCF, 0x57, 0xDB, 0xFC, 0x0E, 0xCB,
    0xBB, 0x9A, 0x31, 0x0D, 0x3F, 0x8C, 0x2B, 0x9E, 0xFC, 0xF2, 0x4C, 0x92, 0x4F, 0x72, 0xD0, 0xB6, 0x63, 0xD8, 0x9B, 0xF3, 0x8D, 0xE1, 0xBF, 0xA1, 0xFA, 0xAC, 0x19, 0x67, 0xDB, 0x24, 0xE0, 0x18, 0x6B, 0x68, 0x3D, 0xC1, 0xE2, 0xFF, 0x11, 0x7F,
    0x7C, 0x5A, 0x49, 0x38, 0xBA, 0x00, 0xD5, 0xF8, 0xE1, 0x6C, 0xB8, 0x75, 0xA6, 0xC5, 0xF7, 0xBC, 0xDF, 0x5F, 0xEE, 0xBB, 0xFF, 0x38, 0xF5, 0x36, 0xE6, 0xDE, 0xFA, 0xF1, 0xEE, 0xCD, 0x0F, 0x2F, 0x0B, 0xF9, 0xE5, 0x27, 0x9B, 0x4E, 0xE6, 0xA9,
    0xFD, 0xF2, 0x6A, 0x5F, 0xC9, 0x0F, 0x3B, 0x79, 0x1B, 0xE4, 0xFF, 0x12, 0xFF, 0xE2, 0xF2, 0xAF, 0x9F, 0x1F, 0x49, 0xEB, 0xCF, 0xDE, 0xAE, 0x7C, 0xC3, 0xE7, 0x9F, 0x9F, 0xF0, 0xCF, 0xCB, 0x3F, 0x9C, 0xEF, 0xF9, 0x25, 0x74, 0x4E, 0xDB, 0x52,
    0x77, 0xFF, 0xE5, 0xCF, 0x1F, 0xF2, 0xC6, 0x92, 0x4F, 0xA4, 0xF5, 0xBD, 0xEB, 0x17, 0xFF, 0xDA, 0xD6, 0x5E, 0xEF, 0x07, 0x7E, 0xF8, 0xDF, 0x2D, 0x1F, 0xBA, 0xD7, 0xAF, 0x7F, 0x96, 0x77, 0xD2, 0xAE, 0x9F, 0xFC, 0x1F, 0x5F, 0x7A, 0xFD, 0xD2,
    0x54, 0x83, 0x8D, 0xE8, 0x4D, 0xCE, 0x69, 0xFB, 0x32, 0x32, 0xA8, 0xA1, 0xB5, 0xA0, 0xBF, 0xDF, 0x16, 0xD3, 0x79, 0x56, 0x9F, 0x9F, 0xE4, 0x0C, 0x56, 0x00, 0xFF, 0x69, 0x8E, 0x67, 0x16, 0x3C, 0x79, 0xF0, 0xFB, 0xC9, 0x5D, 0x84, 0xF9, 0xD2,
    0xAF, 0xBE, 0x00, 0x7E, 0xA5, 0xBD, 0xE3, 0xFC, 0xE7, 0xE3, 0x7F, 0xC1, 0x8F, 0x34, 0xDD, 0xD4, 0xBB, 0x97, 0x3B, 0xFC, 0xC5, 0x07, 0xAF, 0xBA, 0xA6, 0x82, 0x0F, 0xB5, 0x3A, 0xF1, 0xD2, 0x6F, 0x58, 0x3D, 0xF5, 0xF0, 0x97, 0xA7, 0xBA, 0x59,
    0xBB, 0xB6, 0xCA, 0xF3, 0xFC, 0xD4, 0x6F, 0x2B, 0xFF, 0xFC, 0xE5, 0x91, 0x07, 0x39, 0xCC, 0xD8, 0xEB, 0x1E, 0x79, 0xF6, 0x05, 0x42, 0x8D, 0xFD, 0x61, 0xC2, 0x5A, 0x59, 0x19, 0xEF, 0x6B, 0x0B, 0x3B, 0xAD, 0xDA, 0xDB, 0x13, 0x5E, 0xC2, 0x77,
    0x85, 0xE9, 0x9D, 0x40, 0x01, 0x31, 0xC8, 0x9F, 0x4E, 0xD4, 0x6B, 0xD0, 0x67, 0x2E, 0x41, 0xFE, 0xEF, 0xA9, 0x91, 0x16, 0x7F, 0xC9, 0x93, 0x8B, 0x6A, 0x2B, 0xF9, 0x62, 0x08, 0x3E, 0x3A, 0x88, 0xF0, 0x07, 0x60, 0x2E, 0xD3, 0x0E, 0xCA, 0x2B,
    0x0C, 0xFF, 0xC9, 0x31, 0x5C, 0xBC, 0xB5, 0xF5, 0x22, 0xE0, 0xDF, 0x51, 0xC4, 0x09, 0xF0, 0x57, 0x1E, 0x7F, 0x78, 0x92, 0x81, 0xAB, 0x75, 0xD7, 0xE2, 0x91, 0x6F, 0x7D, 0x64, 0xF2, 0x03, 0x29, 0x76, 0xD9, 0xE9, 0xA5, 0xBA, 0xE5, 0x90, 0xDD,
    0x57, 0x55, 0xFF, 0xA4, 0x6F, 0x1C, 0x35, 0x83, 0x46, 0xAA, 0xEF, 0x72, 0x84, 0xF4, 0xEF, 0x15, 0x3B, 0x07, 0x2C, 0x2F, 0x9D, 0xEF, 0x04, 0x42, 0xFD, 0xC2, 0xFC, 0x02, 0xCF, 0x5F, 0x7A, 0xD7, 0x91, 0xCB, 0xDF, 0xFC, 0xE0, 0x9A, 0x5F, 0xE6,
    0x16, 0x0C, 0x2C, 0x70, 0xD9, 0xC5, 0xAF, 0xA4, 0xEA, 0xE1, 0x88, 0xE7, 0x2F, 0x21, 0xE6, 0xF3, 0x6F, 0xEF, 0xB9, 0xF9, 0x6F, 0xBE, 0xFE, 0x1C, 0xA0, 0xB9, 0xE6, 0xF9, 0x73, 0x39, 0xAF, 0xFE, 0xED, 0xED, 0xAD, 0x81, 0xDB, 0xCF, 0x6E, 0x5F,
    0x63, 0xE6, 0x37, 0xBF, 0xF9, 0x17, 0x24, 0x72, 0x7E, 0x0F, 0x52, 0x8A, 0x2F, 0xED, 0xCE, 0xD7, 0x62, 0xFE, 0xDB, 0x0F, 0x17, 0xF2, 0xC1, 0x2F, 0xC1, 0xFC, 0xFE, 0x93, 0xBF, 0xD9, 0x92, 0xEB, 0xA8, 0xE1, 0xF3, 0x9E, 0x37, 0x3F, 0x5C, 0xD9,
    0xAF, 0x9B, 0x9D, 0xCD, 0x85, 0x0F, 0xA5, 0xFC, 0x17, 0xE0, 0x40, 0xDE, 0xFD, 0x76, 0xBD, 0xD3, 0xE2, 0xAB, 0x65, 0x7F, 0x39, 0x5A, 0xCD, 0x67, 0x17, 0xFB, 0x0C, 0xFB, 0x1E, 0x90, 0xAE, 0xB3, 0x56, 0x34, 0x59, 0x63, 0xE5, 0x16, 0xB3, 0xB3,
    0x37, 0x77, 0xBC, 0x2F, 0x83, 0x34, 0xDF, 0xFC, 0x23, 0x98, 0x74, 0xB9, 0xFC, 0xE7, 0x2B, 0x58, 0xFE, 0x15, 0xD0, 0xDE, 0xDC, 0x6D, 0x67, 0xFE, 0xEF, 0xDA, 0xCF, 0xDB, 0xFC, 0xE7, 0x6F, 0x97, 0x7A, 0x0A, 0x68, 0xD8, 0xBE, 0xE9, 0xE7, 0x4F,
    0x5A, 0x22, 0xB3, 0xCD, 0xCD, 0x44, 0xF0, 0x8D, 0x44, 0x99, 0x02, 0x67, 0xCB, 0x7E, 0x8A, 0xA2, 0x17, 0xBD, 0xFC, 0xC0, 0xB7, 0xC1, 0x69, 0xF2, 0x43, 0xEC, 0x2D, 0x0C, 0xE5, 0xC7, 0xB9, 0xF5, 0x37, 0x0C, 0xF8, 0xFC, 0x49, 0x90, 0xED, 0xA0,
    0x06, 0x3B, 0x17, 0xFF, 0x8F, 0x66, 0x46, 0x4C, 0x7A, 0xFE, 0x6F, 0x31, 0x7E, 0xB7, 0x8F, 0x5F, 0xFC, 0xBA, 0xAF, 0x41, 0x99, 0x26, 0xB6, 0x8D, 0xA5, 0x02, 0xBB, 0x8F, 0x3F, 0x07, 0xE0, 0xDF, 0x3B, 0xFC, 0x8F, 0x8F, 0x59, 0xF8, 0xFB, 0x76,
    0xE2, 0x53, 0xD8, 0x8D, 0x3F, 0xFF, 0xAA, 0xAB, 0xBE, 0x92, 0xBC, 0x6F, 0xD9, 0xBF, 0xD9, 0x8D, 0xC8, 0x1A, 0xB7, 0x97, 0xEA, 0x44, 0xC0, 0xDA, 0xE3, 0xC7, 0x3B, 0xE7, 0x4D, 0xFF, 0xF8, 0x7B, 0x2E, 0x3B, 0xA8, 0xF8, 0x6A, 0x54, 0x4C, 0xA7,
    0xF1, 0xC7, 0xBF, 0xF6, 0xEA, 0x8F, 0xFF, 0xD8, 0x33, 0x66, 0x32, 0xAA, 0xED, 0x8E, 0xFA, 0xAB, 0x39, 0x80, 0xA7, 0x4B, 0x5D, 0x27, 0xDF, 0x0C, 0x33, 0xD8, 0x3F, 0x7E, 0x76, 0xBB, 0x5E, 0xA0, 0xD9, 0xD5, 0x49, 0x1A, 0x9E, 0xAD, 0x47, 0x09,
    0x7F, 0x0E, 0xE0, 0x0F, 0x7F, 0xE1, 0x83, 0xDF, 0xF6, 0x7C, 0x0F, 0xE2, 0xAB, 0xE9, 0xB3, 0xE0, 0x32, 0xF8, 0x6D, 0xA6, 0xD2, 0xFD, 0x67, 0xF8, 0xE3, 0xFD, 0xD9, 0x83, 0x9F, 0xED, 0x5B, 0x95, 0x53, 0x66, 0x1B, 0x10, 0x1F, 0x7F, 0x3F, 0xC2,
    0x4F, 0xF5, 0xF8, 0x2B, 0x18, 0xFC, 0xC0, 0xCF, 0xD9, 0xD2, 0xD8, 0x04, 0xFF, 0xCE, 0x1A, 0x90, 0xDE, 0x6D, 0xF7, 0x3F, 0x91, 0x77, 0xCB, 0x06, 0xDF, 0xFB, 0x15, 0x76, 0xFE, 0xEF, 0x2B, 0xB9, 0xFB, 0x3F, 0xA3, 0xF7, 0x3E, 0xCB, 0x46, 0xC4,
    0xAC, 0x01, 0xFB, 0x6F, 0x6A, 0xFF, 0x85, 0x82, 0xB7, 0x7B, 0x84, 0x9B, 0xAF, 0x7B, 0xB1, 0x47, 0x51, 0xF5, 0x7B, 0x3A, 0xDF, 0xF9, 0x9B, 0x86, 0xD0, 0x7E, 0xED, 0xC7, 0xFB, 0x5E, 0x80, 0xDA, 0xDF, 0xF9, 0xED, 0xA7, 0x7E, 0xF3, 0xBB, 0xAF,
    0x32, 0xF9, 0x0D, 0x44, 0xA0, 0xCF, 0xB8, 0xBB, 0x5F, 0x8E, 0x8E, 0x71, 0x04, 0x3B, 0xEE, 0x97, 0xCF, 0x78, 0xD5, 0x63, 0x3C, 0xA8, 0x41, 0x8D, 0x68, 0xF7, 0xE7, 0x2C, 0xDE, 0xF7, 0xFB, 0xAE, 0xEE, 0xAB, 0xB3, 0x7F, 0x45, 0x8E, 0x06, 0xFD,
    0xF4, 0xED, 0xCF, 0x3C, 0xE2, 0x1F, 0xFB, 0xD0, 0x73, 0x2E, 0xD0, 0x81, 0x11, 0x9B, 0xB6, 0xDE, 0x89, 0x99, 0x92, 0x88, 0x6F, 0xF7, 0x7B, 0xDF, 0xF2, 0xA9, 0x4F, 0x7D, 0xB7, 0x2F, 0xFF, 0x38, 0xA9, 0x3D, 0x9A, 0x44, 0xEA, 0x35, 0x30, 0x38,
    0x3A, 0xF3, 0x3C, 0x7D, 0x77, 0xE9, 0x9F, 0xF3, 0x95, 0x13, 0x9E, 0xEE, 0xD3, 0x4F, 0xF1, 0x30, 0xCF, 0xA8, 0x64, 0xA6, 0x83, 0xA7, 0x80, 0x66, 0x34, 0xFB, 0xDF, 0xFF, 0x18, 0xA4, 0xBC, 0xE6, 0x0D, 0xF7, 0xB6, 0xF2, 0x95, 0x2F, 0x4B, 0xCB,
    0x4F, 0x57, 0x02, 0x6F, 0x2E, 0xDF, 0x6D, 0xF6, 0x23, 0xFF, 0xFD, 0xEA, 0x9F, 0xD8, 0xE0, 0x55, 0xA7, 0x39, 0xF7, 0xA7, 0x3E, 0xC6, 0x17, 0xDE, 0x5C, 0x81, 0x9D, 0xDD, 0x8F, 0xFB, 0xD4, 0xBB, 0x7F, 0xDD, 0xF9, 0xF6, 0x75, 0xF7, 0x61, 0xDF,
    0xCB, 0x5E, 0x8D, 0xF4, 0xA5, 0x42, 0xA5, 0xEC, 0x5F, 0xCB, 0xDD, 0xEF, 0x3B, 0xF7, 0xBF, 0xA6, 0xFC, 0xF7, 0xDD, 0xEF, 0x7C, 0xEE, 0x2B, 0xFF, 0xFC, 0x88, 0x43, 0xB1, 0xFB, 0x5B, 0x76, 0xBF, 0xDD, 0xEE, 0x67, 0x99, 0xFD, 0x4F, 0xB7, 0x7D,
    0xA4, 0x47, 0xBF, 0xDB, 0xE5, 0xE3, 0x3E, 0xE4, 0x2E, 0x77, 0xE9, 0xD8, 0x9F, 0x89, 0xFB, 0x85, 0xB5, 0x8F, 0xDD, 0x33, 0x3B, 0x9C, 0x7F, 0xC5, 0x5B, 0xEC, 0x7D, 0x70, 0x17, 0x7F, 0x83, 0x52, 0x0F, 0xE8, 0xF5, 0x3E, 0x9C, 0x49, 0x0E, 0xDC,
    0x5C, 0x82, 0xE7, 0x9B, 0x18, 0x7F, 0xDE, 0xD7, 0x5C, 0xF0, 0x4B, 0xB6, 0x7B, 0xFB, 0xAC, 0xF5, 0x5D, 0x8A, 0x45, 0xEE, 0xFE, 0xA8, 0xF9, 0xFF, 0x78, 0xFF, 0x9B, 0x7A, 0xFC, 0xD2, 0x07, 0xBE, 0x61, 0x51, 0x67, 0xBE, 0xF4, 0x16, 0x4D, 0x6C,
    0xF9, 0x0F, 0x9F, 0xD5, 0xF2, 0x9F, 0xFF, 0xF1, 0x41, 0x69, 0xFC, 0x6A, 0x97, 0xDF, 0xF2, 0xFE, 0xB7, 0xFF, 0xE6, 0x85, 0x79, 0xFF, 0xFB, 0xAF, 0x1F, 0xFF, 0x6C, 0x97, 0x32, 0xF5, 0x59, 0xB5, 0xBF, 0xBC, 0x94, 0xB3, 0xBF, 0xFB, 0xDD, 0x7D,
    0xFF, 0x3F, 0x21, 0xDA, 0xD2, 0x92, 0x71, 0xCF, 0x7A, 0xFA, 0x5B, 0x5F, 0xE7, 0xDD, 0x2F, 0xBD, 0x8E, 0x7E, 0xCF, 0x56, 0xAC, 0xF8, 0x77, 0x3F, 0xAB, 0x09, 0x76, 0xFF, 0xCC, 0xC9, 0x65, 0x9A, 0x5C, 0xB3, 0xEF, 0xBB, 0x88, 0x85, 0xF5, 0x41,
    0xFD, 0xEF, 0x1F, 0x60, 0xFA, 0x47, 0x1E, 0xFD, 0xF3, 0x9F, 0x7A, 0xFD, 0xB3, 0x3B, 0x9C, 0xFB, 0x17, 0x26, 0xFE, 0xF3, 0x9F, 0xFF, 0xFD, 0x7B, 0xCE, 0xFD, 0xFB, 0x97, 0x96, 0xFD, 0xD8, 0x07, 0x9B, 0xD3, 0xA4, 0x3F, 0xFF, 0x4E, 0x7D, 0x4F,
    0x2C, 0x40, 0x11, 0xC5, 0x3F, 0xFC, 0xBB, 0xEF, 0x7E, 0xFD, 0xEF, 0xFF, 0xFF, 0xFE, 0xF7, 0xBF, 0xFF, 0xFD, 0xEF, 0x7F, 0xFF, 0xD3, 0xE9, 0xFF
};

image_info_t clock_bln31_info =
{
    .type  = IMG_TYPE_COMPRESS,
    .pixel = RTGRAPHIC_PIXEL_FORMAT_RGB332,
    .x = 0,
    .y = 0,
    .w = 120,
    .h = 120,
    .size = 1824UL,
    .data =  clock_bln31_120_120,
};

#endif
