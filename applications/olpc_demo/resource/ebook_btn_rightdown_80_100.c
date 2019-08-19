#include <rtthread.h>
#if defined(OLPC_EBOOK_ENABLE)
#include "image_info.h"

static unsigned char ebook_btn_rightdown_80_100[1101UL] =
{
    0x03, 0x00, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE,
    0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0x3F, 0xFC, 0x8A, 0x52, 0xFD, 0xFF, 0xD5, 0xA7, 0x28, 0x4D, 0x53, 0xE2, 0xFF, 0xEF, 0x9D, 0x35, 0x4E,
    0x49, 0xCA, 0xA4, 0x7D, 0xFB, 0xFF, 0x9D, 0xDB, 0xB7, 0x3F, 0x8A, 0x31, 0x65, 0xDF, 0xFE, 0x7F, 0xDF, 0xE6, 0xB1, 0xA2, 0xD4, 0x0F, 0x43, 0x58, 0x7F, 0xDF, 0x3F, 0x6C, 0x55, 0xA4, 0xEB, 0xE9, 0x63, 0xD4, 0xA7, 0x7F, 0xDF, 0xBF, 0xE7, 0x94,
    0x47, 0xD3, 0x68, 0x8E, 0xA5, 0x3E, 0x5F, 0xFE, 0xF7, 0xFA, 0xFE, 0x15, 0xFF, 0x15, 0x1A, 0x7F, 0xBE, 0xFC, 0xE9, 0xE6, 0x0B, 0x02, 0xA7, 0xEF, 0x1F, 0x40, 0x0E, 0x29, 0xFC, 0xF2, 0x6A, 0x22, 0xE3, 0x9F, 0xB7, 0x57, 0xCD, 0x5A, 0x3E, 0x76,
    0x74, 0x42, 0xE3, 0x8B, 0x7D, 0xF9, 0xB1, 0x63, 0xF2, 0xE5, 0xC0, 0xE1, 0xC3, 0x8F, 0x7F, 0x5B, 0x23, 0xCD, 0x7C, 0x32, 0x67, 0x51, 0xC6, 0x78, 0x7C, 0x58, 0xD1, 0xBD, 0x71, 0xF7, 0x8C, 0xDF, 0x7F, 0x56, 0xD9, 0x32, 0xE1, 0xCA, 0xF5, 0xDD,
    0x9D, 0x83, 0x84, 0xAF, 0x1A, 0xBE, 0xF0, 0xF8, 0xF0, 0xFD, 0xC6, 0xF7, 0xCF, 0xB1, 0xFD, 0x77, 0xEF, 0xF1, 0xC7, 0xDF, 0xA6, 0x0C, 0x6E, 0x3A, 0xFC, 0xB4, 0x2F, 0x21, 0xB2, 0xBC, 0x88, 0x43, 0xB1, 0xFF, 0x7E, 0xEE, 0xEC, 0xCF, 0x71, 0xFA,
    0xDE, 0x1E, 0x55, 0x7B, 0xF6, 0xED, 0xFF, 0xC5, 0x77, 0xBF, 0xA5, 0x21, 0xFF, 0xF5, 0xC9, 0x7B, 0x43, 0x76, 0xEF, 0x7A, 0xF2, 0xAF, 0x36, 0xEF, 0x85, 0x7E, 0xF7, 0xBE, 0x84, 0x1E, 0x9A, 0x7D, 0x86, 0xF2, 0xE9, 0xCF, 0x4F, 0xFB, 0x0F, 0xE2,
    0xEC, 0xAF, 0xEA, 0x95, 0x92, 0x7D, 0x99, 0x16, 0x10, 0xED, 0x5D, 0xBE, 0x3F, 0x17, 0xBE, 0xBE, 0x9F, 0x7B, 0x9E, 0xEE, 0xCD, 0x17, 0x9E, 0x3E, 0xFA, 0xAF, 0xD7, 0x57, 0xBF, 0x7D, 0xF6, 0xAF, 0xB4, 0xFF, 0xBE, 0x77, 0xF8, 0xF9, 0xB2, 0xFF,
    0x5E, 0x7D, 0xF7, 0x79, 0x5B, 0x3F, 0x7C, 0xF6, 0xD8, 0x5F, 0xCC, 0x7E, 0x7B, 0xF6, 0x9D, 0xB4, 0x6F, 0x7C, 0xFB, 0xEE, 0xFD, 0xFA, 0xF7, 0xED, 0x1F, 0x7D, 0xEB, 0xD7, 0x57, 0xBF, 0x78, 0xED, 0x2D, 0x5E, 0xC7, 0xBE, 0x7D, 0x24, 0xED, 0x2B,
    0xAF, 0xFD, 0xFB, 0xFF, 0xFB, 0x57, 0xDF, 0x7D, 0xEF, 0xC8, 0x6B, 0xEF, 0x3E, 0xCD, 0xF7, 0xB5, 0x7F, 0x1F, 0xC8, 0xFB, 0xEE, 0xDD, 0xE7, 0xFE, 0xBF, 0xFF, 0xDA, 0xB7, 0xFF, 0x9E, 0x7B, 0xDB, 0x93, 0xEF, 0x3B, 0x3B, 0x31, 0xF6, 0xDB, 0xCF,
    0xD1, 0xFE, 0xFB, 0xEE, 0xFF, 0xCF, 0xBE, 0xFB, 0xF1, 0x7B, 0xBF, 0xFB, 0xCB, 0xF1, 0x0B, 0x81, 0x00, 0xBF, 0x8D, 0xF8, 0xDD, 0xFB, 0x0E, 0xBF, 0xFB, 0xDF, 0xFF, 0x67, 0xFE, 0x79, 0xDE, 0xDF, 0xE7, 0x97, 0xC1, 0x18, 0xFB, 0xEF, 0xC3, 0x78,
    0xDF, 0xFD, 0xF7, 0xDF, 0xEF, 0xFD, 0xFD, 0xE7, 0xBF, 0x0B, 0xAD, 0x7A, 0x3B, 0xB5, 0xBA, 0xB7, 0xCF, 0x7E, 0xF7, 0xEC, 0xA7, 0x68, 0xFF, 0x7D, 0xFF, 0xBD, 0x67, 0x7D, 0xE6, 0x7B, 0xF3, 0x7D, 0x3F, 0x7E, 0x5C, 0xDD, 0x7F, 0x0F, 0xBF, 0x88,
    0xF8, 0xE1, 0x87, 0xDF, 0xFB, 0xB2, 0x97, 0x7E, 0xBF, 0xB5, 0xFB, 0xE1, 0x33, 0xFF, 0x2A, 0x16, 0x63, 0x82, 0xBC, 0x67, 0x7F, 0x43, 0xFB, 0xED, 0xB7, 0xFF, 0xB9, 0xFB, 0xBC, 0xBD, 0x57, 0xEC, 0xBD, 0xFB, 0x08, 0xDD, 0x77, 0x3F, 0x7E, 0x0C,
    0xF1, 0xC3, 0x0F, 0xBF, 0xEF, 0xF1, 0xC3, 0x1F, 0x7C, 0xA3, 0xBF, 0x6E, 0xB1, 0x06, 0x7F, 0xFC, 0x11, 0xE2, 0x8F, 0x3F, 0xFE, 0xE8, 0x67, 0x17, 0x1F, 0xFA, 0xF1, 0xD5, 0xBA, 0x5F, 0xE7, 0x18, 0x8C, 0xEC, 0xBF, 0xEF, 0x3E, 0x82, 0xF7, 0xDD,
    0x77, 0xDF, 0x3D, 0xF8, 0xEE, 0x87, 0xAF, 0xD4, 0x4D, 0xF7, 0x33, 0x6A, 0xF2, 0x1E, 0xF8, 0xF7, 0x03, 0xB8, 0xFF, 0xFE, 0xFB, 0xF1, 0xCB, 0x3E, 0x3E, 0x46, 0xF1, 0xE5, 0x17, 0x7F, 0x7A, 0xFA, 0xE9, 0xA7, 0x9F, 0x7A, 0xE3, 0xAD, 0x27, 0x3F,
    0x4C, 0xF9, 0xCF, 0xCF, 0x9E, 0x7E, 0xFA, 0xE9, 0xE7, 0x1C, 0xFD, 0xFA, 0xBB, 0xE7, 0x7E, 0x18, 0xF7, 0x6D, 0xD3, 0x4F, 0x3F, 0xFD, 0xBE, 0x37, 0x3A, 0x65, 0xEC, 0xE2, 0xB8, 0xC7, 0xC8, 0xCD, 0x1C, 0xFC, 0x7E, 0xC7, 0x1F, 0x7F, 0xFC, 0x6D,
    0xC2, 0xBF, 0xFD, 0x59, 0x9C, 0xF0, 0x9B, 0x08, 0x7F, 0x31, 0x10, 0xE2, 0x7F, 0x7A, 0x2D, 0x6F, 0x0D, 0xF3, 0xDC, 0xFE, 0xFF, 0x5E, 0xB7, 0x7E, 0x1B, 0xA5, 0x66, 0xA2, 0xFF, 0xA3, 0x8C, 0xDB, 0x77, 0x35, 0xA7, 0x3E, 0xC7, 0xDC, 0xBF, 0xDF,
    0xF5, 0xFB, 0xAB, 0xC6, 0xCF, 0x18, 0x1C, 0x2D, 0xD5, 0x84, 0x2F, 0xC4, 0x10, 0x41, 0x20, 0x24, 0x88, 0x7D, 0xB5, 0xEC, 0xB7, 0xDF, 0x7E, 0xBE, 0x7B, 0xD3, 0x99, 0xA7, 0x91, 0xED, 0x37, 0x78, 0xE7, 0x9D, 0xC4, 0xFF, 0xF4, 0x7E, 0xA2, 0xEE,
    0xBF, 0xDF, 0x35, 0xF7, 0x85, 0xE5, 0x39, 0x17, 0x95, 0x61, 0x51, 0xB8, 0xBD, 0x84, 0x19, 0x47, 0x05, 0xC3, 0xFD, 0xDC, 0xD7, 0xD4, 0x1D, 0xE1, 0xF6, 0xFD, 0x37, 0xB7, 0xD8, 0x4F, 0x15, 0xBD, 0x33, 0x4A, 0xFF, 0x99, 0x9C, 0xF2, 0xFD, 0x2D,
    0x55, 0x47, 0x56, 0x75, 0xF8, 0xFD, 0xB7, 0x5C, 0x44, 0xAB, 0x9C, 0xED, 0xB0, 0x7A, 0xFC, 0xED, 0xC7, 0x11, 0x7F, 0x40, 0xF1, 0xCF, 0xBF, 0xF7, 0x0A, 0x93, 0xB2, 0xFE, 0xF6, 0xEB, 0xCF, 0x1F, 0xD6, 0x7E, 0xFF, 0x61, 0xA5, 0xFF, 0x7E, 0x4B,
    0xDD, 0xCF, 0x7F, 0x67, 0x02, 0x8F, 0x1F, 0x1C, 0x7B, 0xE4, 0xF3, 0xD7, 0x1E, 0x40, 0xFC, 0xBD, 0x95, 0x1F, 0xFF, 0x5E, 0xD3, 0x53, 0x67, 0xFD, 0xFC, 0xC5, 0x87, 0xFF, 0xFE, 0xBB, 0xC5, 0xB3, 0xFF, 0x68, 0xFC, 0x89, 0xA7, 0xDD, 0xFE, 0x8E,
    0xB7, 0xD3, 0xDC, 0xE4, 0x93, 0xEF, 0x97, 0xFE, 0xFE, 0x7B, 0x85, 0xB3, 0xFF, 0xFE, 0xFB, 0xB3, 0x7F, 0xDF, 0xFE, 0x77, 0x45, 0xDC, 0xDB, 0xFE, 0x94, 0xB0, 0x77, 0xDD, 0x38, 0xFC, 0xF3, 0xCF, 0x3F, 0xFD, 0xD3, 0xE1, 0xFF, 0xF3, 0xFE, 0xBE,
    0xEF, 0xCF, 0x28, 0xFE, 0xB6, 0xBD, 0x8E, 0x3F, 0xFF, 0x8A, 0xF2, 0x9F, 0x19, 0xEB, 0xA7, 0xF3, 0x8F, 0x28, 0xFF, 0x84, 0x5D, 0x33, 0x39, 0xFF, 0x86, 0xF0, 0xBF, 0x16, 0x35, 0x7E, 0xF3, 0x0F, 0x37, 0xF8, 0xC3, 0x47, 0x8E, 0x17, 0xFF, 0xF8,
    0xC7, 0x3F, 0xE9, 0x97, 0x57, 0xDC, 0x36, 0xFE, 0xF1, 0x8F, 0x7F, 0x30, 0xEF, 0xCE, 0xBF, 0x5E, 0xF8, 0xC7, 0x3F, 0xFE, 0xD9, 0x7D, 0x78, 0xE4, 0xA7, 0xF1, 0x8F, 0x7F, 0xF8, 0x9F, 0x4F, 0xC1, 0x17, 0x13, 0x67, 0xEB, 0xD3, 0xFD, 0x2F, 0x64,
    0xE0, 0x7C, 0x0C, 0xB2, 0x5F, 0xE4, 0xFD, 0x45, 0xBC, 0xBF, 0x84, 0xF6, 0xD7, 0x62, 0xDE, 0xD7, 0xDD, 0x9F, 0x7F, 0xC2, 0x9A, 0x13, 0x5F, 0x7D, 0xF3, 0x23, 0x7A, 0x7F, 0xF7, 0xDF, 0x9F, 0x42, 0x85, 0x33, 0x68, 0xB5, 0x58, 0x8E, 0xF3, 0xAF,
    0x21, 0xE8, 0xE6, 0xC3, 0x1F, 0xC5, 0x88, 0xED, 0x7F, 0xFF, 0x0D, 0x85, 0x87, 0x3F, 0x91, 0x7F, 0xE2, 0x1F, 0xFF, 0x1A, 0x52, 0x30, 0x7D, 0xC4, 0xF2, 0x8F, 0xFF, 0x15, 0xD9, 0x6F, 0x5E, 0xFF, 0xFA, 0x77, 0x11, 0xC5, 0x46, 0xF5, 0x1F, 0x23,
    0x7F, 0xE1, 0xEA, 0x7F, 0x46, 0xE3, 0x9E, 0xDC, 0x7F, 0x8D, 0x88, 0x45, 0xAA, 0xFF, 0x1B, 0x8D, 0x2A, 0x07, 0x25, 0xFD, 0xE3, 0x68, 0x50, 0x8D, 0xFB, 0xDF, 0x11, 0x99, 0x51, 0xF5, 0xDF, 0xA3, 0x29, 0xB9, 0xED, 0xFF, 0x47, 0x5C, 0xF9, 0xEF,
    0x7F, 0xFF, 0xFB, 0xDF, 0xFF, 0xFE, 0xF7, 0xBF, 0xFF, 0xFD, 0xEF, 0x7F, 0xFF, 0xFB, 0xDF, 0xFF, 0xFE, 0x47, 0xD2, 0xFF, 0x01
};

image_info_t ebook_btn_rightdown_info =
{
    .type  = IMG_TYPE_COMPRESS,
    .pixel = RTGRAPHIC_PIXEL_FORMAT_RGB565,
    .x = 936,
    .y = 0,
    .w = 80,
    .h = 100,
    .size = 1101,
    .data = ebook_btn_rightdown_80_100,
};

#endif
