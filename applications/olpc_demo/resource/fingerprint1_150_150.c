/**
  * Copyright (c) 2019 Fuzhou Rockchip Electronics Co., Ltd
  *
  * SPDX-License-Identifier: Apache-2.0
  */

#include <rtthread.h>
#if defined(OLPC_APP_CLOCK_ENABLE)
#include "image_info.h"

static unsigned char fingerprint1_150_150[1865UL] =
{
    0x03, 0x00, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE,
    0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0x5F, 0x79, 0x82, 0x7F, 0x04, 0xFD, 0xFE, 0x91, 0x43,
    0x68, 0x88, 0x88, 0x60, 0x40, 0xD0, 0xBF, 0xEF, 0xDF, 0x36, 0x82, 0x8A, 0x7F, 0xFE, 0xF3, 0x33, 0xE8, 0xDF, 0xA7, 0x0F, 0x01, 0x01, 0x80, 0x41, 0xDF, 0xBF, 0x8A, 0x08, 0xFA, 0xFA, 0xDE, 0x37, 0x54, 0x30, 0x00, 0x44, 0xE8, 0xCB, 0xE7, 0x9E,
    0xBE, 0x3E, 0xF2, 0x04, 0xFB, 0x2B, 0x1A, 0x00, 0xEE, 0xE7, 0x6F, 0x9F, 0x5F, 0xDF, 0x77, 0xF8, 0xEA, 0xDD, 0x23, 0x94, 0x67, 0x60, 0x18, 0x37, 0x0F, 0x7D, 0x7E, 0x6C, 0x08, 0xEA, 0xCD, 0x73, 0xD3, 0xDE, 0x0D, 0x7D, 0x3A, 0xFD, 0xD2, 0xBE,
    0x83, 0x1B, 0xDF, 0x1D, 0xA1, 0x9D, 0x37, 0x75, 0xFA, 0x95, 0xB1, 0xC7, 0x6F, 0x6B, 0xDF, 0xB7, 0x86, 0x7D, 0xFB, 0x86, 0xC7, 0x5B, 0x37, 0x6B, 0x1F, 0x7D, 0x7E, 0xC2, 0xC4, 0xCF, 0x4B, 0x4D, 0x50, 0xAD, 0x19, 0x36, 0x54, 0xF8, 0xE2, 0xE5,
    0xD7, 0x6D, 0xEF, 0x5A, 0xFE, 0x71, 0xED, 0x22, 0x1A, 0xF2, 0x01, 0x10, 0x70, 0x3F, 0xAE, 0x0F, 0x5F, 0x6C, 0xE3, 0x9D, 0xDE, 0x41, 0xB3, 0x0E, 0xFF, 0x5E, 0x7A, 0xFD, 0xA9, 0xD2, 0xF7, 0xD6, 0x1F, 0x0D, 0x39, 0x70, 0xFC, 0xF5, 0xF5, 0x97,
    0x9A, 0x2F, 0x79, 0x9D, 0x7E, 0x5D, 0xD2, 0xDE, 0xBD, 0x8F, 0xA0, 0x9F, 0x7F, 0x33, 0xFD, 0xF5, 0xD2, 0x18, 0x1A, 0x5C, 0xF9, 0xFE, 0x06, 0x9C, 0x5B, 0x7E, 0x4C, 0xBB, 0x9E, 0x43, 0x1F, 0x5F, 0x6A, 0xFC, 0x78, 0x67, 0xB2, 0x5B, 0xCB, 0x93,
    0x8F, 0x9F, 0x51, 0xE4, 0x80, 0xC1, 0xBF, 0x13, 0x64, 0x3C, 0x15, 0xF4, 0xF2, 0xF7, 0xF9, 0x77, 0xEC, 0x7A, 0x36, 0x72, 0x05, 0xD6, 0x06, 0x09, 0xD4, 0x2D, 0x5D, 0xBF, 0xF7, 0xFC, 0x3C, 0x4A, 0x1D, 0xBA, 0x37, 0x7F, 0xA8, 0xCC, 0xB7, 0xDF,
    0x6D, 0x5F, 0x3F, 0x89, 0x51, 0x23, 0x04, 0x34, 0x2E, 0xD0, 0xB5, 0xD6, 0x82, 0xC8, 0x27, 0xC7, 0xCF, 0x3E, 0xFE, 0x17, 0xBB, 0x36, 0x15, 0x3F, 0xB7, 0xE5, 0xD0, 0xB3, 0xA9, 0x93, 0xEF, 0xB9, 0xFC, 0x31, 0x4A, 0x15, 0xC8, 0xD9, 0x3A, 0xAF,
    0x93, 0xA9, 0xB3, 0x3C, 0x5F, 0x5C, 0xFC, 0xF2, 0xAB, 0x18, 0x75, 0xAE, 0xF1, 0xDC, 0x7F, 0xED, 0xCB, 0x19, 0x80, 0x7C, 0x02, 0xBD, 0x17, 0x1F, 0x7F, 0x88, 0x87, 0xBF, 0x37, 0xCF, 0xB9, 0xA9, 0x43, 0xD3, 0xE2, 0x97, 0xFF, 0xFA, 0x66, 0xF3,
    0xA3, 0x98, 0xB6, 0xBE, 0x0A, 0x02, 0x57, 0x93, 0x0B, 0x58, 0x78, 0xD1, 0xF7, 0x97, 0xDA, 0xDE, 0x79, 0xD8, 0xDF, 0x2F, 0x51, 0x2E, 0xDA, 0xFB, 0x6D, 0x77, 0xAC, 0xB7, 0xF0, 0x98, 0x0B, 0xD8, 0x78, 0x53, 0xFF, 0xF1, 0x87, 0x18, 0x95, 0x29,
    0xD8, 0x80, 0x71, 0x7D, 0x87, 0xCE, 0x2F, 0xF5, 0xB5, 0x87, 0x2E, 0xBF, 0x85, 0x5D, 0xD5, 0xA3, 0xBB, 0xFD, 0xD9, 0x7D, 0x63, 0xFF, 0xFE, 0xC4, 0xF3, 0xCF, 0x3F, 0x61, 0x52, 0xF6, 0xBE, 0x4B, 0xBE, 0x70, 0xF6, 0xAA, 0xAB, 0xD0, 0x54, 0x2D,
    0xE4, 0x99, 0x8B, 0x0E, 0xBF, 0x85, 0xDB, 0xB1, 0x17, 0x57, 0x53, 0xBF, 0x91, 0x36, 0x38, 0xFD, 0xAF, 0xC0, 0x56, 0x6F, 0xDB, 0xFE, 0xD9, 0xEF, 0xAF, 0x3C, 0x28, 0xEA, 0xDC, 0xAD, 0x6F, 0x56, 0x5D, 0xDF, 0xF9, 0x9E, 0xB7, 0xDD, 0xF9, 0xC5,
    0xF7, 0x55, 0x52, 0xEC, 0xC7, 0x97, 0xD7, 0x71, 0xCF, 0xCF, 0x27, 0x9A, 0x76, 0xD3, 0xD1, 0x2F, 0x3F, 0x42, 0x9C, 0x91, 0x32, 0xCD, 0x6A, 0xDC, 0x37, 0xB7, 0x2B, 0x3A, 0xD2, 0xE4, 0xAF, 0x9F, 0x75, 0xFC, 0x0D, 0xAE, 0x0D, 0xE0, 0x78, 0xA0,
    0x5B, 0xCA, 0x6B, 0xE9, 0x9C, 0xC8, 0xBB, 0x1D, 0xFF, 0xF8, 0x85, 0xDA, 0xFE, 0x7E, 0x82, 0x8D, 0xB5, 0x2C, 0x7E, 0xEF, 0xA7, 0xA5, 0x94, 0x75, 0x64, 0xBD, 0xA9, 0x9F, 0x93, 0x78, 0xB6, 0xE3, 0x27, 0x39, 0x74, 0xE1, 0x03, 0x6D, 0x1C, 0x73,
    0x52, 0x11, 0xAE, 0x5F, 0x6D, 0xB1, 0x7D, 0x86, 0x1E, 0xFE, 0xF8, 0x8B, 0x0F, 0x33, 0x72, 0xB1, 0x65, 0x66, 0x4F, 0x6B, 0x38, 0x37, 0xB5, 0x53, 0xF1, 0xBE, 0x8B, 0xB7, 0x13, 0x49, 0x29, 0xC9, 0x06, 0x74, 0x66, 0xB3, 0xC3, 0x9E, 0x57, 0x75,
    0x30, 0x03, 0x2D, 0x1F, 0x65, 0x7C, 0x8D, 0xA7, 0x99, 0xC6, 0xA1, 0x19, 0x3D, 0xF1, 0xD8, 0xD4, 0xBF, 0x95, 0x9F, 0x78, 0x4F, 0x8D, 0x8F, 0xF1, 0xF8, 0xEB, 0xAD, 0xF5, 0xB2, 0x4F, 0xB7, 0x5D, 0xAC, 0xFE, 0xF8, 0x6B, 0x15, 0x57, 0x1D, 0xFE,
    0x08, 0x3F, 0xD6, 0x50, 0xE3, 0x93, 0x1D, 0x15, 0xB1, 0xEA, 0xEA, 0x87, 0x37, 0x37, 0xF7, 0x69, 0xA9, 0xA7, 0x2F, 0xE7, 0xA2, 0x15, 0xCC, 0x51, 0x43, 0xC7, 0x6B, 0x9F, 0x7D, 0xF6, 0x21, 0xD7, 0xE7, 0xFC, 0x78, 0xB8, 0xFB, 0x0D, 0x5C, 0x6D,
    0xFB, 0x2C, 0xF6, 0xD9, 0x76, 0x86, 0x59, 0xCF, 0x5C, 0x77, 0xE4, 0x27, 0x0E, 0xD8, 0x74, 0x06, 0x21, 0x55, 0xD9, 0xC9, 0xDE, 0x59, 0xA7, 0xDA, 0x75, 0x54, 0x97, 0x77, 0x71, 0xEA, 0xF3, 0xAA, 0xF3, 0x8D, 0xC7, 0x0E, 0x15, 0x2C, 0x36, 0xF7,
    0xB2, 0x33, 0xFF, 0x78, 0x4D, 0xD7, 0x75, 0xDE, 0xEF, 0xC5, 0xC2, 0x4B, 0x87, 0x6B, 0xD9, 0x74, 0x1F, 0x5C, 0x15, 0xFE, 0x81, 0xC9, 0xD3, 0x5A, 0x67, 0x64, 0x23, 0x94, 0x93, 0x76, 0xF7, 0x5D, 0x3F, 0x19, 0xEB, 0x9E, 0x99, 0x16, 0x32, 0xB5,
    0xBB, 0x75, 0xDE, 0x53, 0x65, 0x3D, 0x4F, 0x05, 0xFD, 0x39, 0xF1, 0x5B, 0x4F, 0x94, 0x67, 0xDD, 0x29, 0x8B, 0x35, 0x77, 0x5F, 0xFD, 0x1B, 0xD0, 0x4F, 0x1B, 0xF5, 0x3C, 0xB1, 0x3C, 0x45, 0xCB, 0x65, 0xDD, 0x32, 0xB3, 0x7F, 0x5D, 0x1D, 0x61,
    0xD2, 0x85, 0xDC, 0x7A, 0x43, 0xDC, 0xF1, 0xBF, 0xF7, 0xD0, 0xC8, 0x84, 0x8B, 0xB5, 0xD0, 0xD9, 0x20, 0x2B, 0x70, 0x60, 0x4E, 0x6F, 0x0B, 0x8C, 0xFF, 0xC7, 0xBB, 0xB4, 0x59, 0x60, 0xC0, 0x3C, 0x9B, 0x98, 0xD5, 0x3A, 0x2D, 0x36, 0xD8, 0xB3,
    0x45, 0x55, 0xFF, 0x1F, 0x49, 0xB9, 0xC3, 0xD7, 0x92, 0x56, 0xDA, 0x67, 0xF5, 0x14, 0xAE, 0x63, 0xBF, 0x12, 0xEF, 0x3D, 0xB8, 0xF0, 0xBA, 0x0C, 0xC2, 0x31, 0xD5, 0x15, 0xBB, 0x5A, 0xEF, 0x5B, 0x95, 0x74, 0x89, 0x9D, 0x8A, 0xEC, 0x73, 0x9E,
    0x9F, 0x96, 0xE8, 0x1E, 0x6E, 0xF7, 0x7F, 0xD3, 0xFB, 0xFB, 0xC3, 0x55, 0x7B, 0xC4, 0x58, 0x8F, 0xF9, 0xE6, 0x50, 0xA5, 0xBD, 0x5C, 0xB2, 0xE1, 0xCA, 0xB7, 0x1B, 0x30, 0xA9, 0xD0, 0xDB, 0x0E, 0xF2, 0x5C, 0x66, 0xC7, 0xEF, 0xCE, 0xAD, 0xBA,
    0xBA, 0x37, 0xDA, 0xC3, 0x1D, 0x04, 0x1F, 0x8F, 0xF7, 0x47, 0xFA, 0xE3, 0xA8, 0xCE, 0xEA, 0x94, 0xCF, 0xAD, 0xE4, 0x7B, 0xB3, 0xE4, 0xFB, 0x4D, 0x7C, 0xFF, 0x87, 0x6D, 0x17, 0x1E, 0xE0, 0x84, 0x96, 0xBB, 0x3D, 0x0D, 0x5D, 0x1E, 0x93, 0x34,
    0xCA, 0xE7, 0xAC, 0xEB, 0xF8, 0xE8, 0x93, 0xF7, 0xFE, 0x1E, 0x53, 0xD7, 0xF2, 0x59, 0xB2, 0x9E, 0x79, 0x56, 0x57, 0x73, 0x99, 0x77, 0xBE, 0xD5, 0xDD, 0xDF, 0xED, 0xE8, 0xA1, 0xF5, 0xFE, 0xFB, 0x17, 0x8A, 0x3E, 0x6C, 0xED, 0xC4, 0xDF, 0xF7,
    0xF6, 0x6A, 0x7F, 0xE7, 0x8C, 0xC6, 0xBF, 0xEC, 0x58, 0x4E, 0x3E, 0xFE, 0x23, 0x26, 0x71, 0x69, 0xEC, 0x97, 0xAE, 0xE7, 0x28, 0xD5, 0x2F, 0x7F, 0x8F, 0xE1, 0xDE, 0x9E, 0xE7, 0xF2, 0x4F, 0xFB, 0xFC, 0x37, 0x7F, 0x5A, 0xA1, 0x54, 0x26, 0x3F,
    0xE6, 0xE7, 0xDF, 0x3D, 0x4F, 0xF3, 0xDF, 0x6A, 0x69, 0xF3, 0x1F, 0xBE, 0xDD, 0x4D, 0x84, 0xEB, 0x79, 0xE4, 0xB2, 0x3A, 0xD7, 0xEB, 0xF2, 0x97, 0xBB, 0xFC, 0xCD, 0x0F, 0xE7, 0xF9, 0xE7, 0x1F, 0xD9, 0xFC, 0x87, 0x4F, 0x62, 0x7B, 0xF3, 0x04,
    0x77, 0x7B, 0x06, 0x87, 0x5F, 0xF9, 0xB4, 0xCB, 0x3F, 0xCB, 0xBB, 0x2F, 0x51, 0xC6, 0x72, 0xD1, 0x5C, 0x56, 0xF8, 0x94, 0x37, 0x1C, 0xFB, 0x05, 0x2A, 0x1D, 0xDE, 0xE2, 0x8E, 0xFF, 0xB4, 0xE7, 0x8F, 0x76, 0x69, 0x15, 0xBE, 0x57, 0x8D, 0xF3,
    0x67, 0x3E, 0xCB, 0x4B, 0xF8, 0xB9, 0xFF, 0x49, 0x2A, 0xFF, 0xCA, 0x7F, 0x9A, 0xBF, 0xE3, 0xC1, 0xFC, 0xFD, 0x07, 0xD3, 0x43, 0xBC, 0xDC, 0x30, 0x87, 0x66, 0xC1, 0xD8, 0x37, 0x19, 0x72, 0x79, 0xE2, 0x5F, 0xFE, 0xC0, 0x17, 0x5C, 0xE2, 0xF3,
    0x27, 0xB1, 0xFC, 0x85, 0x96, 0x7F, 0xBD, 0x09, 0x7E, 0x7E, 0x4A, 0x0B, 0xFE, 0xFC, 0x23, 0x7E, 0x39, 0xFD, 0xF4, 0x27, 0x71, 0xFA, 0xD5, 0x1D, 0x6B, 0xE0, 0x57, 0xAA, 0x75, 0x44, 0xCF, 0xFF, 0xF6, 0x7B, 0xCD, 0xFF, 0x50, 0x65, 0xF9, 0x7D,
    0xC7, 0xAE, 0x98, 0x26, 0xAE, 0x7A, 0xF8, 0x97, 0x7E, 0xB2, 0xE7, 0x5D, 0x7E, 0x7E, 0x05, 0x3F, 0x3C, 0xDE, 0x5A, 0xF3, 0x0D, 0x78, 0x81, 0xE5, 0x2F, 0x6F, 0x3E, 0xA3, 0x5D, 0xE4, 0x23, 0x97, 0xFF, 0x70, 0x15, 0xFF, 0x68, 0x65, 0xFA, 0xA3,
    0xEB, 0xF8, 0xCA, 0x4E, 0x6E, 0x7E, 0x83, 0x23, 0x5C, 0xED, 0xB6, 0x9F, 0x9B, 0xFE, 0xAC, 0x95, 0x31, 0x75, 0x18, 0xEB, 0x7B, 0xB2, 0x7E, 0xE3, 0x5D, 0xF2, 0xCA, 0xAD, 0xED, 0xF0, 0x33, 0x2C, 0xFF, 0xF4, 0xD7, 0x5F, 0xE4, 0x7C, 0xAD, 0xDF,
    0x8A, 0xF9, 0xD2, 0xFF, 0xFB, 0x79, 0x4D, 0x3C, 0xF7, 0x7A, 0xD5, 0x9F, 0xF2, 0xF5, 0x27, 0x9B, 0x78, 0x23, 0x7B, 0x9F, 0xFA, 0xF4, 0xA7, 0xBE, 0xF7, 0x9B, 0xDD, 0xFB, 0xE4, 0x23, 0x9F, 0xFE, 0xE8, 0xFF, 0x3D, 0xF8, 0xC5, 0xAD, 0xFE, 0xDA,
    0xAE, 0x0C, 0xF4, 0x11, 0xDB, 0x79, 0xFD, 0xDE, 0xEF, 0xF8, 0xE7, 0xAB, 0x1F, 0x7C, 0x3B, 0xB3, 0x1A, 0xC3, 0x78, 0x07, 0x1C, 0xF5, 0xCB, 0x6F, 0x73, 0xE7, 0x6B, 0x1F, 0x7C, 0xDC, 0xC6, 0x57, 0xEA, 0x90, 0x12, 0xF6, 0xE0, 0xE9, 0x3F, 0x26,
    0x70, 0x95, 0xCA, 0xBF, 0xFA, 0x84, 0xA5, 0x3E, 0x3A, 0xC5, 0x75, 0x2A, 0xC8, 0x9B, 0xAB, 0xEF, 0x10, 0x4B, 0x9F, 0xFB, 0xE9, 0xA7, 0x3F, 0x32, 0x6D, 0x97, 0x75, 0xDB, 0x9F, 0x77, 0x2D, 0xFD, 0xBF, 0x0F, 0xDD, 0xFA, 0x07, 0xD9, 0xD3, 0x7F,
    0x64, 0x18, 0xE8, 0x8C, 0x4F, 0xFE, 0xA4, 0x61, 0x9D, 0x5B, 0xEA, 0x6B, 0x9D, 0xFE, 0x1D, 0xB6, 0xF9, 0x81, 0xEA, 0xCF, 0xB4, 0x83, 0xD7, 0x3F, 0x49, 0x0D, 0x65, 0x06, 0x67, 0xC4, 0x5B, 0x2E, 0x36, 0xFD, 0xED, 0xAB, 0x2E, 0xFD, 0x41, 0xBC,
    0xDF, 0x33, 0xD3, 0x7F, 0xA1, 0xF9, 0xF5, 0x7A, 0xF3, 0x81, 0xBF, 0xF8, 0x6C, 0xD7, 0x7A, 0xC9, 0x82, 0x4F, 0xEB, 0xAD, 0x5A, 0xB6, 0x7B, 0xFD, 0xEF, 0xCE, 0xE9, 0x3E, 0x0F, 0x13, 0xF3, 0x60, 0xF5, 0x6A, 0xFD, 0xF3, 0xCE, 0xDB, 0xAB, 0xE7,
    0xD2, 0xFF, 0xEE, 0xAC, 0x34, 0x5B, 0xFD, 0x6F, 0xF2, 0xF0, 0xD7, 0xBF, 0xE0, 0x99, 0x2F, 0x2B, 0x2B, 0x77, 0x2D, 0x74, 0x8D, 0xAF, 0x9C, 0xC5, 0xEA, 0xC7, 0x3D, 0xD3, 0xB7, 0xCA, 0x59, 0xAC, 0xEF, 0x3A, 0x80, 0x64, 0xF7, 0x5B, 0xA4, 0xEB,
    0x87, 0x37, 0xFB, 0xF7, 0xF8, 0xCC, 0x8B, 0xC7, 0xBA, 0xFE, 0x0B, 0xA7, 0xFF, 0xFA, 0x73, 0x1E, 0x70, 0xC4, 0xDA, 0x1F, 0xCF, 0xEC, 0x17, 0x76, 0x84, 0xED, 0xCF, 0xED, 0x74, 0x4A, 0xFE, 0x56, 0x1E, 0xEE, 0xB9, 0xFE, 0x75, 0xAC, 0xFF, 0xD9,
    0x85, 0xDF, 0xD5, 0xB4, 0x63, 0x59, 0xC9, 0x15, 0x67, 0xBF, 0x8A, 0x39, 0x7F, 0xC4, 0xDD, 0xFF, 0xBD, 0xD1, 0xC5, 0xEC, 0x32, 0xF6, 0x18, 0x6D, 0xC0, 0x66, 0xEB, 0x9E, 0xE5, 0x9C, 0x45, 0xF3, 0xFB, 0xE8, 0xBF, 0x5C, 0x06, 0x62, 0xD6, 0xE3,
    0x97, 0x3C, 0x36, 0x34, 0x2B, 0x7F, 0xF1, 0x30, 0x4B, 0x32, 0xA8, 0x4A, 0xA5, 0x7F, 0x09, 0x79, 0x0F, 0x64, 0xE3, 0xB1, 0x9C, 0xF7, 0xD3, 0x44, 0x76, 0xC3, 0xB9, 0x3C, 0xCD, 0x21, 0x5E, 0xBE, 0xF6, 0xC1, 0x1D, 0xAA, 0xFB, 0xA5, 0x3A, 0x75,
    0xA4, 0x13, 0x9B, 0xE4, 0x6C, 0xBD, 0xFF, 0xFD, 0xDB, 0xBC, 0x61, 0xC8, 0x3E, 0xB1, 0xE3, 0xC9, 0xFD, 0xBF, 0xFD, 0x4B, 0x89, 0x78, 0x54, 0xC3, 0x13, 0xED, 0xF6, 0x8F, 0xF0, 0xFD, 0x77, 0xFA, 0x79, 0x32, 0x3F, 0x9F, 0xD8, 0x1C, 0x74, 0xBA,
    0xFD, 0x6F, 0x79, 0x5B, 0x4A, 0xA7, 0x5E, 0xC6, 0xAF, 0x8C, 0x36, 0x32, 0x4F, 0xBF, 0x48, 0x0F, 0x9F, 0x8B, 0xDF, 0x2F, 0x6E, 0x5D, 0x8C, 0xEF, 0x17, 0x9A, 0xFC, 0xD4, 0xBD, 0xAC, 0xF3, 0x55, 0x48, 0x5A, 0xD0, 0x97, 0xFF, 0xB8, 0x99, 0x76,
    0xBD, 0xE3, 0x47, 0x0E, 0x7F, 0x89, 0x7E, 0x70, 0xDE, 0xC9, 0x36, 0x34, 0x11, 0x4F, 0xFD, 0xFC, 0xE9, 0x06, 0x19, 0x91, 0xA9, 0x07, 0x1A, 0xEA, 0x81, 0x8F, 0xF6, 0x29, 0xEF, 0xD8, 0x66, 0xD4, 0xB7, 0xE4, 0xED, 0xBA, 0x2B, 0xE9, 0xA7, 0x95,
    0xFF, 0x42, 0x7A, 0x99, 0x5D, 0xBF, 0x69, 0xC7, 0xFF, 0x83, 0xC2, 0xE2, 0x3B, 0x0A, 0xE7, 0x9F, 0xFF, 0xF5, 0x55, 0x5F, 0xB2, 0xC5, 0xDF, 0xBF, 0xBC, 0xF6, 0x5F, 0x48, 0x1B, 0xEE, 0x1F, 0x43, 0xEC, 0x1D, 0x1E, 0x7E, 0xFA, 0x97, 0x97, 0xF5,
    0xF9, 0xEF, 0x7F, 0xFF, 0xFB, 0xDF, 0xFF, 0xFE, 0xF7, 0xBF, 0xFF, 0xFD, 0xEF, 0x7F, 0xFF, 0xFB, 0xDF, 0xFF, 0xFE, 0xF7, 0xBF, 0xFF, 0x0D, 0xF4, 0x7F
};

image_info_t fingerprint1_info =
{
    .type  = IMG_TYPE_COMPRESS,
    .pixel = RTGRAPHIC_PIXEL_FORMAT_RGB332,
    .x = 0,
    .y = 0,
    .w = 150,
    .h = 150,
    .size = 1865,
    .data = fingerprint1_150_150,
};

#endif
