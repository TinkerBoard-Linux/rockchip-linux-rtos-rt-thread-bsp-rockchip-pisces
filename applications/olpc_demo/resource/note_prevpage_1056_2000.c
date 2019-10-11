#include <rtthread.h>
#if defined(OLPC_APP_NOTE_ENABLE)
#include "image_info.h"

static unsigned char note_prevpage_1056_2000[2673UL] =
{
    0xAB, 0xFF, 0x0E, 0xB7, 0xD3, 0x6B, 0xA9, 0xE1, 0xCE, 0x5F, 0x07, 0x36, 0x28, 0x7C, 0x48, 0x86, 0x6D, 0x38, 0x8E, 0x1E, 0x54, 0xB7, 0x92, 0x92, 0xC5, 0xD9, 0x23, 0x2B, 0xB9, 0xFB, 0x80, 0x8F, 0xB1, 0x04, 0xA5, 0x5F, 0xF3, 0x66, 0xE4, 0x5F,
    0x0C, 0x81, 0x96, 0xBD, 0xA9, 0x28, 0xAA, 0xBC, 0x34, 0xFB, 0x90, 0xE1, 0xBE, 0x99, 0x21, 0xC9, 0xD6, 0x75, 0xA2, 0xFC, 0x75, 0xA4, 0x4A, 0x16, 0x02, 0xC1, 0xFC, 0x32, 0xA9, 0xB1, 0x32, 0xFE, 0x3B, 0x3E, 0xDB, 0x5A, 0xB8, 0xF2, 0x16, 0x06,
    0x59, 0xC5, 0x75, 0x97, 0x7F, 0x6B, 0xE7, 0x0E, 0x0E, 0x37, 0xEF, 0xEF, 0xED, 0xD4, 0x57, 0x0C, 0x79, 0x99, 0x38, 0xBC, 0xFE, 0x3B, 0x16, 0x48, 0x50, 0x2B, 0x37, 0x8C, 0x86, 0xBD, 0x52, 0xDD, 0xD8, 0xB2, 0xFF, 0x81, 0xAF, 0x28, 0x0A, 0x48,
    0xB9, 0x5B, 0xAC, 0x01, 0x06, 0x83, 0xB6, 0x22, 0xE9, 0xBA, 0x20, 0x46, 0x87, 0xEC, 0xAA, 0xE8, 0xC8, 0x9B, 0x2F, 0x14, 0x80, 0x61, 0x6F, 0xFD, 0xAD, 0x14, 0x22, 0x3B, 0x82, 0x31, 0x40, 0x5C, 0xFA, 0xE2, 0x48, 0x7E, 0x74, 0x0D, 0x9E, 0x5D,
    0xB8, 0x14, 0xFD, 0x0E, 0xD5, 0x27, 0x13, 0x65, 0xFD, 0x8A, 0x5A, 0x1B, 0xCD, 0x99, 0x94, 0xA7, 0x67, 0x14, 0x70, 0x57, 0x04, 0x8A, 0xC0, 0x5B, 0x08, 0xF1, 0x55, 0xCE, 0x92, 0xBA, 0x75, 0x58, 0xEE, 0x6B, 0x31, 0x8D, 0xFC, 0x0A, 0x57, 0x7F,
    0x9C, 0x49, 0xDA, 0x55, 0x30, 0x4E, 0xA2, 0x3A, 0xD6, 0xBD, 0xEB, 0xA1, 0x19, 0xA8, 0x43, 0xF3, 0x27, 0xF8, 0x16, 0xDD, 0xBF, 0x59, 0xC6, 0xD2, 0xE9, 0x7B, 0x32, 0x45, 0x1C, 0x82, 0xAC, 0xAD, 0xDC, 0x9F, 0x31, 0x07, 0xCE, 0xFC, 0x72, 0xC7,
    0x03, 0x2A, 0x5A, 0x5F, 0xD6, 0x7E, 0x5C, 0xE1, 0x0C, 0x7B, 0xC4, 0xCB, 0x03, 0x1B, 0x71, 0x92, 0xC2, 0x2A, 0x60, 0x90, 0x15, 0xD8, 0xD6, 0xCC, 0x3D, 0xA4, 0xBC, 0x57, 0x7B, 0xAE, 0x59, 0x9A, 0x1D, 0x55, 0x1B, 0x3A, 0xCA, 0x5C, 0x81, 0x73,
    0x32, 0x43, 0x55, 0x13, 0x15, 0xED, 0xF6, 0x4D, 0x7F, 0x05, 0x60, 0x98, 0xBE, 0x9E, 0x5C, 0x66, 0x62, 0xA7, 0xC4, 0xB5, 0x18, 0x9F, 0x69, 0x39, 0x0F, 0x74, 0x6E, 0x17, 0x78, 0x7A, 0x3C, 0x0A, 0x77, 0x8C, 0x5C, 0xB4, 0x9F, 0x34, 0x25, 0x1B,
    0xF8, 0xCB, 0x40, 0x57, 0x23, 0xAC, 0xAA, 0x3E, 0xF6, 0xB1, 0x0D, 0x62, 0xBD, 0x58, 0x19, 0x17, 0xFF, 0x68, 0x36, 0x8F, 0x12, 0x7D, 0x35, 0xD1, 0xFA, 0xB9, 0x81, 0x01, 0xB5, 0xA5, 0x86, 0x44, 0x1D, 0xC9, 0x31, 0x93, 0x0B, 0xE4, 0xB0, 0x5A,
    0xC8, 0x03, 0x01, 0x12, 0x7D, 0xD8, 0xD3, 0x71, 0xCA, 0x28, 0x81, 0xCC, 0x24, 0xEA, 0xFF, 0x52, 0xD8, 0x9D, 0xA0, 0xC4, 0xAC, 0x8E, 0xCF, 0xF5, 0x3E, 0x06, 0x7D, 0xA0, 0x74, 0x79, 0x80, 0x76, 0x19, 0x28, 0x01, 0xF0, 0x14, 0x4D, 0x1D, 0xEE,
    0x2F, 0x7F, 0x6A, 0xA3, 0x53, 0x50, 0x20, 0x17, 0x85, 0x32, 0x12, 0xA3, 0x20, 0x3A, 0xFD, 0x14, 0x94, 0x5F, 0x8C, 0x3B, 0x8B, 0x4E, 0x8A, 0x37, 0xC1, 0xB4, 0xCB, 0x65, 0x29, 0xA9, 0xEA, 0xC4, 0x3B, 0xC5, 0x46, 0x09, 0xD2, 0x74, 0x1D, 0xD4,
    0x1A, 0x94, 0x68, 0x4B, 0xED, 0x0C, 0xD9, 0x9B, 0x40, 0x9B, 0xDB, 0x1E, 0x19, 0x21, 0xF3, 0xFD, 0xDF, 0xFE, 0x16, 0x36, 0x43, 0xAD, 0x7E, 0x22, 0x21, 0x5E, 0xCB, 0x58, 0x9A, 0xF0, 0xE6, 0x87, 0xDE, 0xE6, 0x14, 0x3A, 0x67, 0x62, 0x86, 0x22,
    0x45, 0x5C, 0x6D, 0x6F, 0x6B, 0x0F, 0x06, 0x83, 0x37, 0x20, 0x35, 0xA1, 0xA7, 0x92, 0x11, 0x69, 0x74, 0x4E, 0x8A, 0x41, 0x43, 0x17, 0x92, 0x72, 0xBF, 0xFF, 0x7F, 0x54, 0x01, 0xAE, 0xC7, 0xB5, 0xE8, 0x93, 0x7F, 0xFD, 0x34, 0x6D, 0x20, 0xAF,
    0x4C, 0x5D, 0xE8, 0x0C, 0x1D, 0xF2, 0x00, 0x4F, 0x06, 0x4E, 0xF7, 0x7A, 0x72, 0x09, 0x3F, 0xFA, 0x59, 0x3D, 0x60, 0xB1, 0x12, 0x6E, 0x43, 0x6B, 0x8C, 0x7E, 0xC5, 0xA9, 0x18, 0xCA, 0xE7, 0xF4, 0xC6, 0xEC, 0xF8, 0xEE, 0x7D, 0xF6, 0x1A, 0xAC,
    0xBF, 0xDD, 0x72, 0x9C, 0x5F, 0x17, 0x46, 0xE7, 0x97, 0xC3, 0x5A, 0x8A, 0xF0, 0xE9, 0x41, 0xC1, 0x76, 0x52, 0x57, 0xDB, 0x87, 0x08, 0xEC, 0xF0, 0x55, 0xC8, 0xF0, 0x95, 0xB9, 0x4F, 0x23, 0x6D, 0x29, 0x83, 0xA0, 0x39, 0xC6, 0xF2, 0xA6, 0xF2,
    0x6F, 0x98, 0x52, 0x96, 0xFC, 0xCC, 0x5C, 0xA9, 0xCE, 0x8C, 0xD5, 0x16, 0xC3, 0x68, 0xC8, 0x56, 0xB2, 0xB1, 0x86, 0xCF, 0xAD, 0xBC, 0x0B, 0x06, 0xCE, 0x49, 0xD2, 0xEE, 0xF1, 0xEF, 0x54, 0x63, 0x82, 0xB6, 0xED, 0x0F, 0x9D, 0x1F, 0x0A, 0xCF,
    0xFA, 0x24, 0x39, 0x01, 0xB0, 0x36, 0x16, 0xE0, 0x88, 0xB6, 0x9B, 0x87, 0xD2, 0x4B, 0xCC, 0xD7, 0x10, 0x30, 0xD6, 0x7C, 0x3F, 0x14, 0x5B, 0x93, 0x02, 0xE4, 0x9E, 0x43, 0x42, 0x66, 0x14, 0xE6, 0x6D, 0x99, 0xD5, 0xA7, 0xE5, 0xC2, 0xE9, 0xBE,
    0x32, 0x2A, 0xB6, 0x05, 0x06, 0x66, 0xDD, 0xF0, 0xBD, 0xA9, 0x2F, 0x12, 0xEA, 0xA6, 0x1C, 0x78, 0x85, 0x90, 0x81, 0xA6, 0xBB, 0x5D, 0xDB, 0x0C, 0x09, 0x71, 0x02, 0x63, 0x21, 0x15, 0x7F, 0xD5, 0x1C, 0xB5, 0x46, 0x0E, 0x9D, 0x05, 0x27, 0x1B,
    0xA2, 0x14, 0xE0, 0xC6, 0x98, 0x61, 0x2B, 0x0A, 0xC0, 0x72, 0x56, 0x2F, 0x3C, 0x8E, 0x9A, 0x82, 0x53, 0x83, 0x9B, 0xC4, 0xF4, 0xF9, 0x03, 0x1C, 0x89, 0x1F, 0x5F, 0x1A, 0x6E, 0xD5, 0x29, 0xB8, 0xE4, 0x16, 0xC9, 0xD1, 0xCD, 0xAE, 0x25, 0x07,
    0x95, 0x8D, 0x1A, 0x6A, 0xAA, 0x24, 0x32, 0x32, 0xC3, 0xB2, 0x4B, 0x7A, 0xCF, 0x28, 0x16, 0x69, 0x50, 0x05, 0x6E, 0xAC, 0x5A, 0xD2, 0x2B, 0x03, 0x58, 0x10, 0xC3, 0xC6, 0x1B, 0xBD, 0x83, 0x94, 0x24, 0x51, 0xFC, 0x7F, 0x56, 0xE2, 0x5D, 0x74,
    0x05, 0x2C, 0x33, 0x49, 0x66, 0xB1, 0xFA, 0x31, 0x31, 0x41, 0xA2, 0x5B, 0x89, 0x30, 0xC6, 0x5B, 0x3B, 0xE4, 0x79, 0xBC, 0xA4, 0x89, 0xE1, 0x5B, 0x46, 0xD2, 0xFB, 0x76, 0x95, 0x75, 0x49, 0x6D, 0x97, 0x5D, 0x0D, 0x9A, 0x33, 0xC5, 0xCB, 0xC0,
    0x2B, 0x4D, 0x19, 0x61, 0x88, 0xFA, 0x80, 0xEE, 0x16, 0x2C, 0x01, 0x60, 0xD0, 0x43, 0x1E, 0x83, 0xC5, 0x20, 0x30, 0xE0, 0x4C, 0x23, 0x08, 0x37, 0xA3, 0xFC, 0x91, 0x3B, 0x3D, 0x34, 0x19, 0xF1, 0x09, 0x86, 0x3D, 0xF1, 0xE5, 0xCE, 0x28, 0x37,
    0x88, 0x18, 0x83, 0x30, 0x9E, 0xB8, 0xD3, 0xC7, 0x28, 0x19, 0xAB, 0x0E, 0x1F, 0x23, 0x23, 0xF4, 0x70, 0xCD, 0x7C, 0xE5, 0x5D, 0x2C, 0x34, 0x24, 0x11, 0xC0, 0x9D, 0x89, 0xC0, 0x25, 0x64, 0xD3, 0x7D, 0x8E, 0x69, 0xB6, 0x84, 0x14, 0xC2, 0x8E,
    0x04, 0x46, 0x7F, 0x3C, 0xCC, 0xEF, 0xAE, 0x5F, 0xED, 0xBD, 0xC7, 0x04, 0xA1, 0x70, 0x7D, 0xDA, 0x4C, 0xBB, 0x0A, 0x89, 0xEB, 0x43, 0x40, 0x52, 0xF8, 0x81, 0xB1, 0x4D, 0x19, 0x4B, 0xDD, 0x3A, 0xBB, 0xAC, 0x2B, 0xA8, 0xB1, 0x5D, 0x18, 0x3B,
    0xA0, 0xD9, 0xCA, 0x55, 0x32, 0x8F, 0x89, 0x0A, 0x4E, 0x59, 0x5F, 0x89, 0xE2, 0x68, 0x14, 0xAC, 0xA7, 0xBA, 0x9A, 0x69, 0xC8, 0xBC, 0xA1, 0x78, 0x09, 0x52, 0xCB, 0x08, 0x7D, 0x7B, 0x8C, 0x85, 0x99, 0x46, 0xEE, 0xF0, 0x0B, 0x75, 0x7A, 0xFA,
    0xF5, 0xCF, 0x9B, 0x61, 0x3F, 0xC4, 0x49, 0xD1, 0x45, 0x27, 0xFD, 0xC8, 0x51, 0x32, 0xD2, 0xB7, 0x12, 0xBB, 0xB3, 0xCE, 0x6C, 0x0E, 0x68, 0x6B, 0x7E, 0x55, 0xC3, 0x78, 0xB4, 0xF4, 0x94, 0x57, 0x45, 0xFF, 0x04, 0xDD, 0x04, 0x52, 0x8C, 0xC9,
    0x22, 0x1D, 0x97, 0x03, 0xB6, 0xCB, 0xC1, 0xD7, 0xCB, 0x6B, 0x69, 0xD5, 0x98, 0xB3, 0xFC, 0x26, 0x3E, 0x27, 0xFE, 0x37, 0xEB, 0xC6, 0xCE, 0x80, 0xD4, 0xDB, 0xFA, 0x56, 0xEF, 0x03, 0x35, 0xCD, 0xD7, 0xC7, 0x91, 0x27, 0xE8, 0xDB, 0xE5, 0x1B,
    0xA5, 0xAD, 0x5F, 0xC0, 0x18, 0xC9, 0x63, 0x33, 0x33, 0x78, 0x09, 0xAF, 0x4F, 0x96, 0x9A, 0x1A, 0x33, 0x3E, 0x1D, 0xE0, 0xAC, 0x85, 0xD3, 0xD4, 0x9D, 0xBD, 0xF6, 0x09, 0xD2, 0x72, 0x34, 0x5D, 0x84, 0xC3, 0xEE, 0x5B, 0xCF, 0xB9, 0x9F, 0xB5,
    0x92, 0xA5, 0xC9, 0xA2, 0xC5, 0x70, 0x2E, 0x52, 0x62, 0x04, 0x62, 0x91, 0xFB, 0xA0, 0x4F, 0x38, 0x7C, 0xB4, 0x7F, 0x11, 0xCB, 0x6F, 0x32, 0x04, 0xF2, 0x76, 0x0C, 0x64, 0x72, 0x17, 0x26, 0x11, 0xE4, 0xE6, 0x70, 0xC3, 0x30, 0x23, 0x15, 0x09,
    0x80, 0xE4, 0x13, 0x00, 0x16, 0x90, 0x8A, 0x7D, 0xE7, 0x47, 0xE5, 0x3C, 0x06, 0x25, 0x5D, 0x5B, 0x59, 0xD2, 0x84, 0x94, 0x2D, 0x5E, 0x6B, 0xAD, 0xDB, 0xC0, 0x9A, 0x6F, 0x0E, 0xE6, 0xC1, 0x34, 0xD0, 0xB0, 0x76, 0x82, 0x2C, 0x9A, 0xDE, 0x6F,
    0x7B, 0x37, 0x37, 0xE1, 0xF7, 0x37, 0x35, 0x55, 0xB4, 0xBB, 0xF7, 0x75, 0x9F, 0x61, 0x3E, 0x23, 0xD3, 0x87, 0xAC, 0xC7, 0x38, 0x65, 0x77, 0x47, 0x5A, 0x24, 0xCA, 0x51, 0xEC, 0x90, 0x80, 0xFA, 0x10, 0xDF, 0xB8, 0x80, 0xC0, 0xBE, 0x2E, 0x12,
    0x9C, 0x17, 0xE4, 0xF8, 0xF5, 0xE7, 0x60, 0x0F, 0xD4, 0x7C, 0x0A, 0x04, 0x1A, 0x40, 0x4D, 0xA4, 0x9D, 0xDA, 0x59, 0xA2, 0x99, 0xBD, 0x3F, 0x66, 0x68, 0x52, 0x30, 0xF4, 0xD2, 0x0D, 0xEE, 0x93, 0x65, 0x99, 0x16, 0xCE, 0x2E, 0xFE, 0xD6, 0xAB,
    0x2A, 0x4C, 0x2E, 0x81, 0x02, 0xA1, 0x7B, 0x31, 0x8F, 0x9A, 0xC1, 0x09, 0x60, 0xE7, 0x44, 0xB5, 0xF8, 0x4C, 0x53, 0x2D, 0x36, 0xA7, 0x78, 0xCB, 0xCF, 0xE5, 0xEE, 0xBE, 0xF2, 0x98, 0x7F, 0x56, 0x3A, 0x66, 0xB6, 0xFF, 0x74, 0xC4, 0x9E, 0x18,
    0xF1, 0xA4, 0xC4, 0xDD, 0x44, 0x1B, 0x77, 0xAE, 0xFC, 0xE1, 0xD1, 0xB0, 0x15, 0xEC, 0x20, 0x7D, 0x81, 0x16, 0x88, 0x98, 0x78, 0x1A, 0xE6, 0xE3, 0x0B, 0x6D, 0xE7, 0x89, 0xA1, 0x4C, 0x8D, 0x09, 0x27, 0x32, 0xBA, 0x3F, 0xF6, 0x39, 0x9A, 0x1B,
    0x15, 0xFA, 0xBF, 0x8F, 0xB7, 0xC9, 0x34, 0x88, 0xA5, 0x93, 0x83, 0xEC, 0xA4, 0x3C, 0x34, 0x93, 0x3C, 0x7B, 0x11, 0x0D, 0xE2, 0x37, 0xAA, 0x7B, 0x42, 0x98, 0x92, 0xB3, 0x19, 0x04, 0x46, 0xDB, 0x02, 0x05, 0x91, 0xB1, 0x2F, 0xFF, 0x7E, 0x07,
    0x3D, 0x3B, 0x02, 0x11, 0x66, 0x36, 0xC6, 0x10, 0xCF, 0x87, 0x83, 0x6C, 0x7E, 0x97, 0x62, 0x80, 0x0D, 0x89, 0x2A, 0x91, 0xF9, 0xC6, 0xF4, 0xE4, 0x79, 0x36, 0x45, 0x96, 0xC6, 0xB9, 0x02, 0x5A, 0xE0, 0x27, 0x77, 0xC6, 0xD8, 0x35, 0xCD, 0x04,
    0x23, 0x4A, 0x48, 0xAE, 0xEB, 0xD5, 0x2F, 0xD4, 0x28, 0x28, 0x79, 0x4C, 0xA7, 0x2B, 0xFE, 0x14, 0xD9, 0x04, 0xCD, 0xAE, 0x0C, 0x76, 0x9F, 0x8B, 0x19, 0x0C, 0xE4, 0x44, 0xA0, 0xB2, 0xD3, 0x3D, 0x36, 0x1D, 0x14, 0x8B, 0x60, 0x5F, 0x96, 0xED,
    0xB7, 0xFB, 0x78, 0xE4, 0x43, 0xC6, 0x94, 0x7C, 0x25, 0xDE, 0x92, 0xE7, 0x7C, 0x41, 0x72, 0x62, 0x97, 0xFA, 0x87, 0xB8, 0x40, 0x05, 0x5F, 0x67, 0xF2, 0x00, 0x8B, 0x47, 0x92, 0x6D, 0xF8, 0xAC, 0xBD, 0x89, 0x70, 0xEB, 0x74, 0x7F, 0xBE, 0x7F,
    0x09, 0x69, 0x70, 0x8E, 0xB5, 0x16, 0x13, 0x6C, 0xC1, 0x8D, 0xF9, 0x89, 0xC1, 0x46, 0xCD, 0x97, 0x8F, 0xBC, 0xA7, 0x0E, 0x1B, 0x35, 0xFB, 0x9B, 0x04, 0xB9, 0xB0, 0x06, 0x27, 0x3E, 0x77, 0x11, 0xDC, 0xA3, 0x67, 0xF8, 0x5A, 0xEA, 0x4B, 0xA3,
    0x8E, 0x18, 0xD6, 0x8E, 0x17, 0x61, 0xEA, 0xE0, 0xBB, 0x53, 0x26, 0xCD, 0x80, 0x39, 0x5D, 0x48, 0x95, 0x05, 0x48, 0xD1, 0x1D, 0x72, 0xAF, 0xBE, 0x12, 0x9A, 0x22, 0x23, 0x92, 0x4C, 0x02, 0x47, 0x2F, 0x22, 0x11, 0x54, 0xD8, 0xFA, 0x8B, 0x1D,
    0xF1, 0xB7, 0x5B, 0x66, 0x74, 0x94, 0x98, 0x91, 0x34, 0x7E, 0x1E, 0x20, 0x29, 0x10, 0xA7, 0xFE, 0xDB, 0xBB, 0x84, 0x4D, 0x32, 0x50, 0x0A, 0x66, 0xCF, 0x3F, 0x66, 0x51, 0xE7, 0xA8, 0x0F, 0x48, 0x0E, 0xFC, 0x52, 0x65, 0x62, 0x46, 0x8B, 0x4F,
    0xD5, 0x23, 0x0D, 0xF9, 0x11, 0x35, 0xC4, 0x15, 0xA2, 0x28, 0xE7, 0x7A, 0x60, 0x50, 0x4F, 0xD6, 0x07, 0xF7, 0x87, 0x55, 0xB6, 0xBB, 0xBB, 0x69, 0x59, 0x95, 0xE2, 0xA2, 0xCE, 0xAD, 0x60, 0x1D, 0xDB, 0xFD, 0xED, 0x05, 0x45, 0xA5, 0xE4, 0x74,
    0x5F, 0x66, 0x6E, 0x14, 0x46, 0x3C, 0x75, 0x72, 0xA5, 0x4A, 0x43, 0xC9, 0xA7, 0xA7, 0xF5, 0x1D, 0xF7, 0xDD, 0x9D, 0x1F, 0x0B, 0xDA, 0xD9, 0xE3, 0xDC, 0x01, 0x84, 0xB0, 0xD4, 0xC2, 0x4D, 0x70, 0xFC, 0x62, 0x37, 0x7B, 0x85, 0xF7, 0x02, 0x1E,
    0x81, 0x99, 0x54, 0x82, 0xCA, 0xE3, 0x3A, 0xCB, 0x23, 0x82, 0xCF, 0xAF, 0xF9, 0x6F, 0x7D, 0x70, 0x8B, 0xC5, 0xF8, 0x4C, 0x66, 0x5F, 0xFF, 0x6F, 0x98, 0xDC, 0x89, 0x72, 0x27, 0xF7, 0xC1, 0xE2, 0x4B, 0xD1, 0x03, 0x63, 0x09, 0x8F, 0x6D, 0x20,
    0x26, 0xC7, 0xF8, 0x0D, 0xFD, 0x27, 0x1C, 0xAB, 0xA1, 0xB0, 0x01, 0x33, 0x7A, 0x99, 0x91, 0x74, 0xC3, 0xFA, 0x19, 0xC0, 0x06, 0xB2, 0xEC, 0xD8, 0x4D, 0xDD, 0x38, 0x9A, 0x59, 0xE9, 0xA6, 0x3E, 0xD4, 0x6D, 0x3D, 0x28, 0x87, 0x2D, 0xA8, 0x8D,
    0x6B, 0xDA, 0xEB, 0x8F, 0x1D, 0x08, 0xC6, 0x56, 0x24, 0x0A, 0xF0, 0x83, 0x4A, 0x25, 0x5B, 0x37, 0x0E, 0x31, 0x85, 0xF3, 0xEB, 0xBA, 0xE2, 0x74, 0xD5, 0x82, 0xA0, 0x94, 0x0D, 0x28, 0x44, 0x4A, 0x91, 0x59, 0x31, 0xBE, 0x94, 0x3A, 0x40, 0x91,
    0xCD, 0x6B, 0x20, 0x98, 0x6C, 0x79, 0x73, 0x11, 0x8E, 0x98, 0x4F, 0x46, 0x84, 0xFA, 0xCD, 0x2B, 0x9F, 0x2F, 0x38, 0x30, 0x6A, 0xD4, 0x01, 0x9F, 0x17, 0x31, 0x96, 0x0F, 0x14, 0xC4, 0x1F, 0x3D, 0x6B, 0xAE, 0x20, 0x9D, 0x5F, 0x49, 0x1F, 0xB1,
    0x18, 0xD3, 0x42, 0xC5, 0xA7, 0x19, 0x05, 0x05, 0x0F, 0x5B, 0xF3, 0xB6, 0xDF, 0xB6, 0x87, 0x24, 0x16, 0xE4, 0xB2, 0xE2, 0x0F, 0xF2, 0x06, 0x88, 0xDE, 0xF6, 0x73, 0xE9, 0xF2, 0x8C, 0x71, 0xAD, 0x71, 0xB4, 0xC0, 0xAB, 0xCC, 0xB5, 0x8C, 0x02,
    0xEB, 0xFA, 0x02, 0x7B, 0x9F, 0x65, 0xD2, 0xD6, 0xB2, 0x82, 0x2D, 0x6E, 0x25, 0x6A, 0xC7, 0xBE, 0x0F, 0x74, 0x11, 0x56, 0xA4, 0xF1, 0xFE, 0x5D, 0xDB, 0x81, 0xEA, 0x6E, 0x3D, 0xB7, 0x30, 0x88, 0x55, 0x5D, 0x6D, 0x16, 0xFA, 0x1E, 0xDE, 0x9B,
    0x15, 0x45, 0xC0, 0x2C, 0xCF, 0xEF, 0xCD, 0xFC, 0xB4, 0x8E, 0x9E, 0xD5, 0x82, 0x0E, 0x39, 0xE4, 0x5F, 0xA7, 0x1A, 0x00, 0x47, 0xF2, 0x70, 0xC8, 0x96, 0x80, 0x7C, 0x73, 0x95, 0x63, 0xD7, 0xC4, 0x3B, 0xC8, 0x25, 0x92, 0xEB, 0xBE, 0x61, 0x8C,
    0xEC, 0x4F, 0x8C, 0xA9, 0x2E, 0xF2, 0x4B, 0x7B, 0x9F, 0xDF, 0xEA, 0x9A, 0x76, 0xE8, 0xB7, 0x74, 0x83, 0xB0, 0x0F, 0x61, 0x4F, 0x61, 0x70, 0xC3, 0xC5, 0x52, 0x06, 0xF6, 0xEE, 0xF4, 0xC3, 0x9A, 0xFB, 0x09, 0x01, 0x63, 0x99, 0xD9, 0xCE, 0x87,
    0xF6, 0x3A, 0xB2, 0x2A, 0x88, 0xB0, 0x5C, 0xA6, 0x3D, 0x75, 0x78, 0xF4, 0x66, 0xA7, 0x91, 0x93, 0xA5, 0xFF, 0x0B, 0x3D, 0x93, 0x50, 0xA3, 0xA0, 0x3F, 0xDE, 0xB6, 0x02, 0x1D, 0x8A, 0xA2, 0x79, 0xE1, 0x21, 0x6F, 0xC9, 0x5C, 0x76, 0x32, 0x97,
    0x7A, 0xCE, 0xE8, 0x48, 0xCA, 0x78, 0xA0, 0x70, 0x40, 0x7C, 0x07, 0xB8, 0x68, 0xB1, 0xED, 0xA0, 0x58, 0xE3, 0x4E, 0xCF, 0x92, 0x0F, 0xA4, 0xFA, 0xA1, 0xD7, 0x80, 0x98, 0x96, 0x94, 0x65, 0xEF, 0x25, 0x49, 0xDC, 0xCE, 0x10, 0xE5, 0xF2, 0x5E,
    0xC5, 0x66, 0xE0, 0x6F, 0xD7, 0x09, 0x7B, 0x27, 0xC3, 0x84, 0x5D, 0x15, 0x39, 0x04, 0x4E, 0x67, 0x9F, 0x88, 0x0E, 0x37, 0xC8, 0xD7, 0x81, 0x2F, 0xBE, 0x9A, 0xAB, 0x9B, 0x03, 0x10, 0x28, 0x31, 0xD7, 0x80, 0x39, 0x3E, 0xDA, 0x75, 0xAF, 0xB9,
    0xF0, 0xFB, 0x97, 0x83, 0x9E, 0x2B, 0x64, 0xD5, 0x9C, 0xF7, 0x2E, 0xE4, 0xDA, 0x1E, 0x4D, 0x9E, 0x56, 0x94, 0xD9, 0xF2, 0x88, 0x52, 0xAB, 0xF1, 0xE0, 0xB7, 0x13, 0x3A, 0x81, 0xF8, 0xCF, 0xFA, 0x6E, 0xC7, 0x4C, 0x17, 0x6C, 0x5B, 0x9A, 0x15,
    0x5F, 0x5E, 0x97, 0x4F, 0x66, 0x3B, 0x31, 0x7E, 0x10, 0x28, 0xCB, 0x7C, 0xD1, 0xA1, 0x9D, 0xBF, 0x0D, 0x8C, 0xFC, 0xF0, 0x63, 0x30, 0x9F, 0x00, 0xCA, 0x6E, 0x9D, 0x4B, 0x63, 0xC6, 0xEF, 0x1F, 0x90, 0xD0, 0x60, 0x3E, 0x30, 0xDE, 0xDE, 0x36,
    0x9E, 0x4A, 0xAE, 0x69, 0x11, 0x92, 0x3A, 0x88, 0x96, 0xFA, 0x78, 0xCC, 0x65, 0x58, 0x30, 0xD8, 0xC4, 0x1D, 0x15, 0xAB, 0x91, 0x23, 0x11, 0xBD, 0x67, 0x5A, 0x45, 0x0E, 0x8D, 0x42, 0x56, 0x4E, 0xE6, 0x23, 0x51, 0xA8, 0xD3, 0xFC, 0x55, 0x34,
    0x52, 0xEB, 0x74, 0x45, 0xF7, 0x70, 0x0A, 0x1F, 0x0D, 0x82, 0x78, 0x4B, 0xE0, 0x9D, 0x89, 0x50, 0xC5, 0x4E, 0xA3, 0x76, 0xF1, 0x9A, 0x20, 0xA0, 0xBB, 0xAC, 0xF5, 0x61, 0xA3, 0x96, 0xE0, 0x2A, 0x2C, 0x17, 0xD8, 0xFB, 0x87, 0x74, 0x80, 0x76,
    0x8E, 0xBF, 0xD7, 0xF3, 0x8C, 0x84, 0x33, 0xC3, 0x40, 0x7F, 0x78, 0x6B, 0xB7, 0x6A, 0xDE, 0x16, 0x7A, 0x43, 0xE3, 0x67, 0xFD, 0x18, 0xA9, 0x46, 0x6C, 0x74, 0xA5, 0xAE, 0x7B, 0xD3, 0x58, 0x7C, 0xCA, 0x36, 0x5D, 0xB3, 0x91, 0x15, 0x95, 0x25,
    0xDE, 0x8B, 0xF9, 0x90, 0x75, 0xE1, 0x00, 0x6E, 0x20, 0x14, 0x6F, 0x6F, 0x61, 0xED, 0xEC, 0x9C, 0xBA, 0x3D, 0x26, 0x0B, 0x8D, 0x49, 0x59, 0xF6, 0x77, 0x60, 0x65, 0x44, 0x8A, 0x63, 0x0C, 0x91, 0xD4, 0xD9, 0x54, 0x33, 0x63, 0xD0, 0xBA, 0x5C,
    0x77, 0xC5, 0x77, 0x7D, 0x0E, 0x2D, 0x61, 0x3C, 0x95, 0x7E, 0x7C, 0xA4, 0xFD, 0x72, 0x8D, 0xD9, 0x7F, 0xFB, 0x6B, 0x33, 0x8C, 0x5A, 0x19, 0x75, 0xC2, 0x0E, 0xCE, 0x7C, 0x80, 0x4D, 0x3F, 0x75, 0x95, 0xEB, 0x53, 0xFE, 0xA3, 0x68, 0x42, 0x47,
    0x3E, 0x9B, 0x6B, 0x48, 0x25, 0x00, 0x2F, 0x02, 0x74, 0xF1, 0x0E, 0xB2, 0x84, 0xEC, 0xBF, 0xF6, 0x50, 0x7D, 0x24, 0x81, 0x02, 0x3F, 0xBD, 0x09, 0x3D, 0xD2, 0x47, 0x3F, 0x0B, 0x5A, 0x17, 0x96, 0x04, 0xFF, 0x5F, 0x04, 0x0A, 0xE3, 0x1D, 0x79,
    0x0B, 0x9C, 0xB6, 0x69, 0x83, 0x73, 0x18, 0xFE, 0xFA, 0xFE, 0xF1, 0xF8, 0xF1, 0x4F, 0xE2, 0x8D, 0xF2, 0x8E, 0xF8, 0xCA, 0xCE, 0xB3, 0xE9, 0x14, 0x45, 0xAD, 0x55, 0xE6, 0x03, 0x39, 0x1E, 0xD2, 0xF0, 0x7C, 0x68, 0x69, 0xF5, 0x93, 0x4D, 0xD8,
    0x67, 0xC7, 0x53, 0x1B, 0x8F, 0x0F, 0x8D, 0x72, 0x48, 0xDA, 0xCD, 0x67, 0xB7, 0xE2, 0xCB, 0x64, 0x66, 0xFD, 0xBE, 0x7F, 0x44, 0xBB, 0x40, 0x2A, 0x88, 0x1B, 0xD9, 0xFE, 0x84, 0x62, 0x83, 0x86, 0x7E, 0x8B, 0xF0, 0xEC, 0xD6, 0xA6, 0x92, 0x28,
    0x23, 0xDC, 0xCE, 0xA3, 0x90, 0x3D, 0xE7, 0xAE, 0x41, 0x3D, 0x01, 0xA5, 0x25, 0x0F, 0x28, 0x9C, 0x92, 0x42, 0xF5, 0xB7, 0x7A, 0xF7, 0x48, 0x11, 0xDE, 0x0A, 0x66, 0x32, 0x5D, 0x9A, 0xDD, 0xED, 0xFA, 0x1B, 0x83, 0x05, 0x11, 0xB3, 0x23, 0xE8,
    0x4A, 0xF4, 0x9A, 0x34, 0x66, 0xE2, 0x8C, 0x60, 0x31, 0xC9, 0x82, 0x73, 0xF7, 0x54, 0x89, 0xFF, 0x2C, 0x40, 0xEB, 0x3A, 0x0B, 0x16, 0xAD, 0x4D, 0x6D, 0xF6, 0xC5, 0xF4, 0x84, 0x7E, 0x53, 0x5E, 0x7B, 0xAD, 0xE4, 0xD9, 0x4E, 0x17, 0x48, 0x4C,
    0x46, 0x60, 0x86, 0xDE, 0x62, 0x1B, 0xF6, 0xCA, 0x05, 0x77, 0x60, 0xEB, 0xAE, 0xA9, 0xD9, 0xF3, 0xF9, 0x36, 0x79, 0x40, 0x9B, 0x85, 0xA1, 0xE9, 0x3F, 0x68, 0x77, 0x5F, 0xA6, 0x75, 0xEF, 0xFF, 0xAC
};

image_info_t note_prevpage_info =
{
    .type  = IMG_TYPE_COMPRESS,
    .pixel = RTGRAPHIC_PIXEL_FORMAT_GRAY1,
    .x = 0,
    .y = 0,
    .w = 1056,
    .h = 2000,
    .size = 2673UL,
    .data = note_prevpage_1056_2000,
};

#endif
