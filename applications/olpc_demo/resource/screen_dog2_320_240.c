#include <rtthread.h>
#if defined(OLPC_APP_SRCSAVER_ENABLE)
#include "image_info.h"

static unsigned char screen_dog2_320_240[250UL] =
{
    0xAB, 0xF4, 0x6F, 0xEF, 0xC0, 0xEC, 0xEC, 0x04, 0x85, 0xE9, 0x2F, 0xFD, 0x2A, 0x97, 0xDE, 0xEC, 0x99, 0x90, 0xFA, 0x63, 0xFA, 0x5D, 0xC7, 0x8F, 0x27, 0xE6, 0xCF, 0x24, 0x65, 0x2B, 0xF9, 0x39, 0x92, 0xDF, 0x17, 0x0D, 0x3F, 0x37, 0x0C, 0x51,
    0xBE, 0xF5, 0x47, 0x75, 0x2D, 0x93, 0x69, 0x81, 0x0A, 0x78, 0x0D, 0x45, 0xBB, 0x77, 0x9B, 0x31, 0xC9, 0x83, 0xE1, 0x68, 0x07, 0x96, 0xFE, 0x94, 0xCB, 0x90, 0x9D, 0xD7, 0xDD, 0x23, 0x72, 0xBF, 0x0F, 0x26, 0x9A, 0x28, 0x52, 0x21, 0x5B, 0xD8,
    0x63, 0x2B, 0x90, 0xF8, 0x14, 0xE9, 0x49, 0x4F, 0x13, 0xB9, 0x19, 0xBF, 0xF9, 0xB7, 0x18, 0xD3, 0x04, 0xD5, 0x9B, 0xBD, 0x8A, 0x5E, 0x42, 0x82, 0x0A, 0xF6, 0x0C, 0x20, 0x67, 0x9A, 0x7C, 0x2E, 0x56, 0xBD, 0xDF, 0x02, 0x79, 0xC7, 0xB9, 0x99,
    0xB7, 0x0B, 0x84, 0xE2, 0xC8, 0x83, 0x06, 0x47, 0x15, 0x70, 0xA5, 0x4E, 0x7D, 0x83, 0x80, 0x51, 0x1D, 0x22, 0xDF, 0x4F, 0x65, 0x72, 0x44, 0x25, 0x08, 0x67, 0x70, 0xC3, 0xC1, 0x19, 0xD8, 0x25, 0x5F, 0xD7, 0xE7, 0x7C, 0xBB, 0xB3, 0x02, 0x98,
    0xF6, 0xA2, 0x35, 0x75, 0xB7, 0x51, 0x8E, 0x9F, 0xE1, 0xDA, 0x2D, 0x94, 0xED, 0xED, 0x2C, 0x10, 0xAB, 0x20, 0x5D, 0x02, 0x4F, 0x4E, 0x32, 0x3E, 0x25, 0xEA, 0x6B, 0x4D, 0x91, 0x6B, 0xA3, 0x91, 0xEB, 0x21, 0x34, 0x48, 0x74, 0xDB, 0x47, 0x5E,
    0x4B, 0x1B, 0x8A, 0xD3, 0x78, 0xAD, 0x7F, 0x34, 0xB1, 0xB7, 0xEC, 0x65, 0xD5, 0x88, 0x79, 0x72, 0x1F, 0x8B, 0x00, 0x93, 0xB5, 0xC8, 0x8C, 0x5C, 0x4E, 0xA6, 0x01, 0xC7, 0xC3, 0xE3, 0x8C, 0xFF, 0x62, 0x76, 0xB0, 0x11, 0xB4, 0x12, 0x04, 0x35,
    0x9C, 0x22, 0x95, 0x17, 0xC5, 0xC1, 0xFF, 0x7F, 0xFF, 0xAC
};

image_info_t screen_dog2_info =
{
    .type  = IMG_TYPE_COMPRESS,
    .pixel = RTGRAPHIC_PIXEL_FORMAT_GRAY1,
    .x = 0,
    .y = 0,
    .w = 320,
    .h = 240,
    .size = 250UL,
    .data = screen_dog2_320_240,
};

#endif
