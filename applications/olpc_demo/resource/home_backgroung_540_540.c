#include <rtthread.h>
#if defined(OLPC_CLOCK_ENABLE)
#include "image_info.h"

static unsigned char home_backgroung_540_540[785UL] =
{
    0x97, 0x4A, 0x42, 0x32, 0x0D, 0x0A, 0x1A, 0x0A, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x01, 0x00, 0x00, 0x00, 0x13, 0x00, 0x00, 0x02, 0x1C, 0x00, 0x00, 0x02, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x26, 0x00, 0x01, 0x00, 0x00, 0x02, 0xC5, 0x00, 0x00, 0x02, 0x1C, 0x00, 0x00, 0x02, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xFF, 0xFD, 0xFF, 0x02, 0xFE, 0xFE, 0xFE,
    0xAB, 0xEA, 0x9E, 0x88, 0x24, 0x9B, 0x82, 0x2C, 0x75, 0x35, 0x08, 0x3B, 0x5C, 0x45, 0x43, 0xD8, 0x3F, 0x36, 0x1E, 0xB9, 0x8E, 0x61, 0xAA, 0x8D, 0x20, 0x6D, 0xC9, 0x02, 0x56, 0xAF, 0x1F, 0x61, 0xB7, 0xC4, 0x06, 0xFE, 0xD2, 0x05, 0x9E, 0x1E,
    0x25, 0x0C, 0x36, 0x37, 0xDB, 0x2C, 0x29, 0x62, 0x4D, 0x1B, 0x9C, 0xA1, 0x41, 0xD7, 0x58, 0xDC, 0x77, 0xA6, 0x94, 0x25, 0xC6, 0x97, 0x3B, 0xD6, 0x16, 0xBB, 0x2E, 0xA3, 0x29, 0x47, 0x5B, 0xC6, 0x20, 0x62, 0xB1, 0x6F, 0x3A, 0x7D, 0xA4, 0x90,
    0x1A, 0x8A, 0xF8, 0xE6, 0xD6, 0x6E, 0xF8, 0x15, 0x24, 0x8C, 0x14, 0x4E, 0xE9, 0x71, 0xE7, 0x8B, 0x8E, 0xAD, 0xD2, 0x25, 0xE6, 0xDE, 0x1A, 0x03, 0x38, 0x17, 0x67, 0x22, 0x5F, 0x5E, 0xB4, 0x44, 0x62, 0x85, 0xDE, 0xD4, 0x6C, 0xC6, 0x98, 0x66,
    0x20, 0xBE, 0x3A, 0x75, 0x6D, 0x38, 0xC3, 0x09, 0xA3, 0xFD, 0x7C, 0xA6, 0xA8, 0x61, 0x27, 0x04, 0xAA, 0x06, 0xB6, 0x7C, 0x6D, 0x36, 0x14, 0x55, 0x13, 0xA5, 0xEF, 0x63, 0x63, 0x62, 0x7D, 0xFF, 0x71, 0x5D, 0xEE, 0x00, 0x35, 0x6F, 0xFE, 0x19,
    0x54, 0xA3, 0x7F, 0x24, 0xDC, 0xDE, 0x1C, 0x1E, 0x85, 0xF9, 0x6B, 0x1F, 0x97, 0x94, 0x2F, 0x9F, 0x8A, 0x26, 0x79, 0xB8, 0x9F, 0x56, 0x1B, 0x22, 0x15, 0x58, 0xF9, 0xD2, 0x89, 0x66, 0x66, 0xB7, 0x62, 0xB1, 0x1A, 0x00, 0x52, 0x92, 0x25, 0x0D,
    0x73, 0x44, 0x3D, 0x02, 0x7D, 0xBC, 0x7F, 0x2D, 0x8B, 0xC8, 0x49, 0x09, 0x83, 0xAB, 0xB6, 0x51, 0x3F, 0x8E, 0x9A, 0xD0, 0xAC, 0x87, 0x58, 0x54, 0xC3, 0xD9, 0xDF, 0x6C, 0x35, 0x16, 0xBD, 0x14, 0xB9, 0xC3, 0x45, 0x06, 0x48, 0x2E, 0xCA, 0x3B,
    0xB5, 0xF3, 0xEC, 0xE3, 0x52, 0x7A, 0xA7, 0x6D, 0x6C, 0x9A, 0xB5, 0x9C, 0xD7, 0xBB, 0xEA, 0x84, 0x0D, 0xEA, 0x92, 0xAF, 0xFF, 0x3D, 0x7E, 0x78, 0x4B, 0x64, 0xB0, 0xC3, 0x7C, 0x20, 0x2E, 0xA8, 0x22, 0x9E, 0x66, 0x7F, 0x6F, 0xFA, 0x78, 0x11,
    0x75, 0x15, 0x9E, 0x63, 0x9A, 0x61, 0x54, 0x84, 0xC7, 0xAD, 0x4B, 0xEA, 0x39, 0x3A, 0x23, 0xD6, 0xEB, 0x47, 0x63, 0xFF, 0x23, 0x6F, 0xDA, 0x51, 0xBB, 0xA8, 0x7E, 0x3F, 0xC1, 0xF3, 0x9D, 0x70, 0x7E, 0xBD, 0xF3, 0x51, 0x17, 0x37, 0x97, 0x4C,
    0x8B, 0x95, 0x6B, 0x60, 0x99, 0xE2, 0x79, 0x45, 0xF2, 0x1A, 0x35, 0xC2, 0xB5, 0x41, 0xE0, 0xC9, 0x0B, 0xA7, 0x95, 0xD1, 0x14, 0x57, 0x60, 0xDC, 0x58, 0x92, 0x3A, 0x0B, 0xD2, 0x9E, 0x99, 0x39, 0xE6, 0xDE, 0x71, 0x70, 0x20, 0x39, 0x0A, 0xC3,
    0x4C, 0xD6, 0x09, 0xC9, 0x3D, 0x2B, 0xF5, 0xFF, 0x41, 0x00, 0xA9, 0xED, 0xE3, 0xA7, 0x3E, 0x97, 0x3E, 0xB5, 0xC5, 0x30, 0xC4, 0x28, 0x89, 0x07, 0x00, 0x88, 0x9A, 0x72, 0x0F, 0x62, 0x00, 0x66, 0x60, 0xB9, 0x75, 0x02, 0x8C, 0xC7, 0xE8, 0x89,
    0x32, 0x47, 0xD0, 0x69, 0x84, 0xA4, 0x08, 0xC2, 0xB2, 0xE8, 0x44, 0xBE, 0xBD, 0xA1, 0x1F, 0x25, 0x34, 0x4E, 0x71, 0x19, 0xE6, 0x0B, 0x0E, 0x4A, 0xD6, 0x2C, 0x39, 0xC9, 0x20, 0x2A, 0x05, 0xB0, 0x15, 0x4F, 0x7E, 0x4D, 0x5C, 0x76, 0x0B, 0xFC,
    0x4D, 0x91, 0x2A, 0x24, 0x39, 0x70, 0x5B, 0x66, 0x6E, 0x9F, 0xE1, 0x83, 0x7B, 0x55, 0x4E, 0xC0, 0x3A, 0x98, 0x83, 0x73, 0x15, 0x8E, 0x31, 0x61, 0x59, 0x40, 0x8D, 0x8B, 0xD9, 0x5B, 0x92, 0xD7, 0x1F, 0x72, 0x16, 0x1E, 0xA4, 0x2E, 0x4C, 0x43,
    0xD6, 0xA8, 0x5F, 0x90, 0x64, 0x85, 0x22, 0xA7, 0xD0, 0xA0, 0xD3, 0x6D, 0xBB, 0x6A, 0xD3, 0x2D, 0x0F, 0x40, 0x37, 0x70, 0x65, 0xE4, 0x25, 0xF3, 0xAC, 0xD2, 0xC3, 0x4B, 0xE3, 0x8B, 0xB7, 0xFB, 0x2B, 0x41, 0x3D, 0x94, 0x44, 0x5E, 0x35, 0x31,
    0x34, 0x88, 0x66, 0x6C, 0x23, 0x87, 0x4B, 0x10, 0x6C, 0x66, 0x46, 0x5C, 0xBA, 0xDD, 0xD2, 0xAF, 0xD4, 0xAE, 0x57, 0x54, 0x1E, 0xCE, 0xE7, 0xE6, 0x6A, 0xE9, 0x24, 0xDF, 0xB4, 0xF8, 0x54, 0x07, 0xF1, 0xD2, 0xEB, 0xFD, 0x89, 0x04, 0x93, 0x30,
    0xA7, 0x2B, 0x11, 0x6B, 0xFD, 0x88, 0x70, 0xF1, 0x94, 0x09, 0xEB, 0x4E, 0x7E, 0xF7, 0xF5, 0xC2, 0xDF, 0x25, 0x5E, 0xF2, 0xF3, 0xAD, 0xEC, 0x0B, 0x42, 0xBC, 0x37, 0xFB, 0x28, 0xC6, 0x1A, 0x6D, 0x29, 0x7E, 0x45, 0x67, 0x6A, 0xC4, 0x9A, 0x5A,
    0x01, 0xA4, 0x78, 0xD3, 0xBA, 0x0A, 0x4B, 0x2D, 0x25, 0x70, 0x79, 0xB2, 0x39, 0xAC, 0x58, 0x0D, 0x12, 0x10, 0xF6, 0xC3, 0x11, 0x0D, 0xD3, 0x07, 0xBF, 0x32, 0x5E, 0xE8, 0x4F, 0xA4, 0x6C, 0xC8, 0x26, 0x65, 0x48, 0x07, 0xB7, 0xB0, 0xB3, 0x72,
    0xBA, 0x5E, 0x2A, 0xE4, 0x9A, 0xB1, 0x50, 0xE0, 0xA3, 0x91, 0x4B, 0x33, 0x25, 0xB4, 0x80, 0xA5, 0x4E, 0xE5, 0x16, 0x85, 0xCB, 0xCA, 0x62, 0x4F, 0x37, 0xDA, 0xB5, 0x88, 0x30, 0xBD, 0x31, 0x9C, 0x83, 0x98, 0x2C, 0x9C, 0x7D, 0x4E, 0x2D, 0xFF,
    0x7F, 0xFF, 0xAC, 0x00, 0x00, 0x00, 0x02, 0x31, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x33, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00
};

image_info_t home_backgroung_info =
{
    .type  = IMG_TYPE_COMPRESS,
    .pixel = RTGRAPHIC_PIXEL_FORMAT_GRAY1,
    .x = 0,
    .y = 0,
    .w = 540,
    .h = 540,
    .size = 785,
    .data = home_backgroung_540_540,
};

#endif
