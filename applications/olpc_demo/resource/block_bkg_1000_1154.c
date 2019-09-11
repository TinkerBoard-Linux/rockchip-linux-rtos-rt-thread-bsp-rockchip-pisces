#include <rtthread.h>
#if defined(OLPC_APP_BLOCK_ENABLE)
#include "image_info.h"

static unsigned char block_bkg_1000_1154[869UL] =
{
    0xFF, 0x78, 0xC0, 0x37, 0xB9, 0xA3, 0x9D, 0x3F, 0xF1, 0xE6, 0x09, 0x10, 0xD5, 0x0F, 0x82, 0x30, 0x43, 0x72, 0x28, 0xCC, 0xF6, 0x37, 0xF8, 0x5A, 0xAD, 0x73, 0xB2, 0x8D, 0x47, 0xB7, 0x52, 0x69, 0xAD, 0xDD, 0xED, 0x85, 0x58, 0xF1, 0xF4, 0xCB,
    0xF7, 0xD4, 0xDD, 0xAA, 0x65, 0x3E, 0x42, 0x50, 0x8C, 0x97, 0x77, 0x53, 0xDD, 0xF9, 0x6B, 0x0E, 0x5A, 0xC4, 0xCC, 0x25, 0x24, 0x2C, 0x73, 0x06, 0xBD, 0x84, 0xC6, 0x39, 0x4E, 0x24, 0xFB, 0xAC, 0xFB, 0x92, 0xF5, 0xAF, 0xCB, 0x96, 0x3C, 0x16,
    0x08, 0xDA, 0xEC, 0x9A, 0x6E, 0xFC, 0xAF, 0x86, 0x53, 0x1E, 0xAC, 0xE9, 0xAA, 0xA1, 0xD1, 0x70, 0xA9, 0x2A, 0x2D, 0x3C, 0x16, 0x38, 0x25, 0x10, 0xC2, 0xD0, 0x00, 0x1D, 0x4C, 0x0F, 0xEC, 0xF4, 0x3B, 0x48, 0x71, 0x29, 0xDB, 0x70, 0x8A, 0xFE,
    0x9F, 0xC4, 0x7E, 0xDC, 0x43, 0x46, 0x51, 0x8E, 0x19, 0x84, 0x3E, 0x40, 0x9F, 0xEC, 0x00, 0x94, 0x83, 0x2D, 0x33, 0xAA, 0xDF, 0x72, 0xE6, 0x10, 0x3B, 0xFC, 0x44, 0x96, 0x70, 0x49, 0x33, 0x13, 0x84, 0x10, 0x18, 0xB6, 0xDE, 0x4E, 0x56, 0x32,
    0x85, 0x9B, 0x2B, 0xE5, 0xB8, 0x60, 0x04, 0xBA, 0xFB, 0x42, 0x87, 0xFF, 0x7F, 0xFF, 0x7F, 0xE1, 0xEC, 0xE7, 0x78, 0x31, 0x77, 0x90, 0xBF, 0x66, 0x23, 0xEB, 0x5D, 0xF9, 0x86, 0x2C, 0x04, 0xA4, 0x2B, 0x0D, 0x63, 0x72, 0xB7, 0xB6, 0x7C, 0xC7,
    0xC6, 0x7B, 0x83, 0x34, 0xAF, 0x99, 0xD4, 0x5B, 0x49, 0x2D, 0x4B, 0x57, 0x6E, 0x63, 0x19, 0x0E, 0xD7, 0x9A, 0xF2, 0xC8, 0x6F, 0x51, 0xBB, 0xC0, 0xFC, 0xD1, 0x46, 0x17, 0xBC, 0xFF, 0x7A, 0xBC, 0x61, 0x74, 0xAE, 0x01, 0x76, 0x50, 0x9B, 0xE7,
    0x26, 0xCA, 0x7A, 0x9C, 0xCA, 0xDA, 0x8C, 0xFA, 0xE6, 0xB7, 0xE5, 0x54, 0xF5, 0x0A, 0xB1, 0x31, 0x79, 0x40, 0x0D, 0x06, 0xF2, 0x04, 0x00, 0xE4, 0xAC, 0xD6, 0xA7, 0xEB, 0x58, 0x05, 0x35, 0xD7, 0x4A, 0xF5, 0x83, 0x51, 0x28, 0xEE, 0xD1, 0x34,
    0xB1, 0x0F, 0xA5, 0xF3, 0x87, 0xD6, 0x20, 0x3D, 0x01, 0x07, 0xEB, 0xEF, 0x81, 0x2A, 0xA0, 0x62, 0x30, 0xEF, 0xEC, 0xF8, 0x89, 0x85, 0xD2, 0x19, 0x25, 0x34, 0x51, 0x8B, 0xC3, 0x1E, 0x71, 0x73, 0x17, 0x89, 0x16, 0xDF, 0xFF, 0x7F, 0xFF, 0x7D,
    0x07, 0xAC, 0x5B, 0x9C, 0x17, 0x35, 0x1B, 0xC8, 0xCF, 0x68, 0x8E, 0xA4, 0x9E, 0xF7, 0x3B, 0x1D, 0x81, 0x0F, 0xDC, 0x64, 0x27, 0x84, 0x94, 0xD7, 0x99, 0x89, 0x9C, 0x4C, 0x8B, 0x49, 0xB8, 0x77, 0xD1, 0xF3, 0xC9, 0xF0, 0x41, 0xFE, 0xFB, 0x97,
    0x1E, 0x66, 0xB7, 0x08, 0x35, 0xFE, 0x94, 0x5A, 0x0E, 0x7B, 0x03, 0xB6, 0x4B, 0x36, 0xB8, 0x9D, 0x40, 0x54, 0xEE, 0x8F, 0x77, 0xB8, 0xB1, 0xBB, 0xFE, 0x5B, 0xC1, 0x7C, 0xC0, 0x42, 0x93, 0x38, 0xF6, 0x3F, 0x49, 0xD0, 0x0C, 0x7F, 0xA5, 0x36,
    0x18, 0x77, 0xFE, 0x22, 0x3F, 0x69, 0xD4, 0x77, 0x08, 0xDF, 0xEC, 0xA4, 0x5F, 0x79, 0x3F, 0xC3, 0x6A, 0x80, 0x4F, 0x97, 0x38, 0xF4, 0x8A, 0xF4, 0x7C, 0xA9, 0xA6, 0x84, 0x78, 0xAB, 0x7A, 0xD0, 0x84, 0x1B, 0x82, 0x2C, 0xBD, 0xEB, 0x52, 0x34,
    0x0F, 0x37, 0x30, 0xD5, 0x14, 0xE7, 0x99, 0x17, 0x0B, 0xF1, 0xD4, 0x01, 0x5F, 0x10, 0x90, 0x57, 0x46, 0xF8, 0x43, 0x5C, 0xA6, 0xB7, 0xA5, 0xAB, 0x31, 0xD2, 0xDF, 0x47, 0xEA, 0x85, 0x0A, 0x4D, 0xD2, 0x25, 0x5B, 0xC3, 0x82, 0xB0, 0xE9, 0x5D,
    0x2F, 0x1D, 0xFD, 0xBF, 0x38, 0xAC, 0x59, 0x5E, 0x38, 0x32, 0x6C, 0xB0, 0x1F, 0xC0, 0xAE, 0xF1, 0xE7, 0xB5, 0x11, 0xDC, 0xFB, 0x09, 0x47, 0x1F, 0xE8, 0xEB, 0x9D, 0x8F, 0x3B, 0x8C, 0x25, 0x33, 0xA2, 0xC3, 0x1B, 0x04, 0x7A, 0xE7, 0x6C, 0x8E,
    0xD3, 0xC3, 0x01, 0xA8, 0x10, 0xD6, 0x4A, 0xDA, 0xBA, 0xC5, 0xE6, 0x15, 0xAE, 0xAF, 0xA0, 0x27, 0x2D, 0xEF, 0x17, 0x8D, 0xCD, 0xB3, 0x98, 0xC4, 0x3A, 0x95, 0x5E, 0xCE, 0xBE, 0x34, 0xF2, 0xB3, 0x95, 0x9A, 0x7A, 0x1B, 0x0A, 0x7C, 0x6E, 0x82,
    0x1D, 0x33, 0x32, 0x54, 0x81, 0x71, 0xB2, 0x70, 0xBC, 0x34, 0x25, 0x0A, 0x21, 0xBF, 0xFF, 0x6E, 0x27, 0xEA, 0x2B, 0x22, 0x5F, 0x64, 0xAF, 0xDF, 0x56, 0xA3, 0x10, 0x30, 0x0F, 0x07, 0x51, 0xB0, 0x53, 0x2D, 0xAE, 0xCF, 0x58, 0x4F, 0x4F, 0x0F,
    0x59, 0xA3, 0x87, 0x52, 0x8A, 0xDC, 0xD7, 0xA6, 0x36, 0x96, 0xCD, 0xAD, 0x75, 0x62, 0xD5, 0xF9, 0x3D, 0x70, 0xD8, 0xC3, 0xCE, 0xD4, 0xED, 0x32, 0x0F, 0x7E, 0xB5, 0xFE, 0x69, 0xE5, 0xEE, 0x5E, 0xC4, 0x13, 0x34, 0xCA, 0x7A, 0xE9, 0x33, 0xD9,
    0x07, 0x16, 0x24, 0x14, 0x7E, 0x48, 0xDE, 0x36, 0x42, 0x6E, 0x52, 0x00, 0x4F, 0x4E, 0xEA, 0x4B, 0x57, 0x1C, 0xCB, 0x16, 0x4C, 0x9D, 0xFA, 0x20, 0xE0, 0x4E, 0x93, 0xB7, 0xE8, 0x53, 0x56, 0x5D, 0x3E, 0x60, 0xFC, 0x31, 0xC2, 0x5A, 0x76, 0x10,
    0xFD, 0x1E, 0x89, 0x3A, 0x3B, 0x5F, 0xE6, 0xFA, 0xAE, 0x7A, 0xA1, 0x5A, 0xE4, 0x46, 0xEB, 0x6E, 0x58, 0x64, 0xA2, 0x09, 0xA5, 0x76, 0xD5, 0x7A, 0xA0, 0x87, 0xDE, 0xA7, 0x11, 0xFF, 0x3D, 0x23, 0x12, 0x7A, 0xF3, 0xDE, 0xC5, 0xCB, 0x20, 0xE4,
    0x53, 0xB5, 0x5C, 0xD8, 0xB3, 0xB1, 0xD8, 0x06, 0x70, 0x96, 0xC0, 0xDE, 0xEF, 0x29, 0x97, 0x28, 0x42, 0xA3, 0xF7, 0x21, 0x33, 0x39, 0xCD, 0x47, 0x1F, 0x12, 0x48, 0xA7, 0xFA, 0x23, 0x36, 0x43, 0xF2, 0x53, 0x3A, 0xC1, 0x30, 0x25, 0xDD, 0x46,
    0x64, 0x17, 0x36, 0x44, 0x0F, 0xE3, 0x3D, 0x34, 0x0D, 0x8D, 0x1D, 0xD8, 0x82, 0x84, 0x72, 0x5B, 0x27, 0xF6, 0x76, 0xB8, 0xF6, 0x22, 0x91, 0x2F, 0xE7, 0x71, 0xC1, 0xE4, 0x45, 0x9E, 0x89, 0x30, 0xC5, 0xA5, 0x9A, 0xEE, 0x0C, 0xBF, 0x46, 0x04,
    0x4A, 0xA1, 0xE4, 0x73, 0x9D, 0x7B, 0xC7, 0x5D, 0x23, 0x8F, 0xDE, 0x39, 0xC8, 0xB9, 0xFA, 0x3E, 0x45, 0x81, 0xC1, 0x44, 0x20, 0xE1, 0x2D, 0xA5, 0xE5, 0x5D, 0x5E, 0xE2, 0x91, 0x5B, 0xC4, 0xF5, 0x8E, 0xBF, 0x8A, 0x20, 0x37, 0x97, 0x2B, 0x96,
    0xA2, 0xB8, 0x15, 0xF9, 0x23, 0x0F, 0xFF, 0x6E, 0x22, 0xBF, 0x99, 0x1C, 0xD7, 0xDC, 0xB1, 0x67, 0xE4, 0xC2, 0xBA, 0x18, 0x0D, 0xDF, 0xF2, 0x97, 0xC5, 0x41, 0x7F, 0xFF, 0xAC
};

image_info_t block_bkg_info =
{
    .type  = IMG_TYPE_COMPRESS,
    .pixel = RTGRAPHIC_PIXEL_FORMAT_GRAY1,
    .x = 0,
    .y = 0,
    .w = 1000,
    .h = 1154,
    .size = 869UL,
    .data = block_bkg_1000_1154,
};

#endif
