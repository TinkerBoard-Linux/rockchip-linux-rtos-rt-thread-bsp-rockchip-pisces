/**
  * Copyright (c) 2019 Fuzhou Rockchip Electronics Co., Ltd
  *
  * SPDX-License-Identifier: Apache-2.0
  */

#include <rtthread.h>
#if defined(OLPC_APP_NOTE_ENABLE)
#include "image_info.h"

static unsigned char note_btnclear_199_80[2000UL] =
{
    0x00, 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x1F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xE0, 0x00, 0x00, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF8, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0x00, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x07, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xFF, 0x80, 0x07, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3F, 0xC0, 0x0F, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xE0,
    0x1F, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xF0, 0x3F, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xF8, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xF8, 0x7E, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFC, 0x7E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0xFC, 0x7C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7C, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7E, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3E,
    0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3E, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3E, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3E, 0xF8, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3E, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x3E, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3E, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3E, 0xF8, 0x00, 0x00, 0x00, 0x0F, 0xFF, 0xC0, 0x3F, 0x00, 0x00, 0x0F, 0xFF, 0xFE, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x1F, 0xFF, 0xF0, 0x00, 0x00, 0x00, 0x3E,
    0xF8, 0x00, 0x00, 0x00, 0x7F, 0xFF, 0xC0, 0x3F, 0x00, 0x00, 0x0F, 0xFF, 0xFE, 0x00, 0x00, 0xFF, 0x80, 0x00, 0x1F, 0xFF, 0xFE, 0x00, 0x00, 0x00, 0x3E, 0xF8, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xC0, 0x3F, 0x00, 0x00, 0x0F, 0xFF, 0xFE, 0x00, 0x01,
    0xFF, 0x80, 0x00, 0x1F, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x3E, 0xF8, 0x00, 0x00, 0x03, 0xFF, 0xFF, 0xC0, 0x3F, 0x00, 0x00, 0x0F, 0xFF, 0xFE, 0x00, 0x01, 0xFF, 0x80, 0x00, 0x1F, 0xFF, 0xFF, 0x80, 0x00, 0x00, 0x3E, 0xF8, 0x00, 0x00, 0x07, 0xFF,
    0xFF, 0xC0, 0x3F, 0x00, 0x00, 0x0F, 0xFF, 0xFE, 0x00, 0x01, 0xFF, 0xC0, 0x00, 0x1F, 0xFF, 0xFF, 0xC0, 0x00, 0x00, 0x3E, 0xF8, 0x00, 0x00, 0x0F, 0xFF, 0x87, 0xC0, 0x3F, 0x00, 0x00, 0x0F, 0xFF, 0xFE, 0x00, 0x03, 0xFF, 0xC0, 0x00, 0x1F, 0x80,
    0x7F, 0xC0, 0x00, 0x00, 0x3E, 0xF8, 0x00, 0x00, 0x1F, 0xF8, 0x00, 0x40, 0x3F, 0x00, 0x00, 0x0F, 0xC0, 0x00, 0x00, 0x03, 0xE7, 0xC0, 0x00, 0x1F, 0x80, 0x1F, 0xE0, 0x00, 0x00, 0x3E, 0xF8, 0x00, 0x00, 0x1F, 0xE0, 0x00, 0x00, 0x3F, 0x00, 0x00,
    0x0F, 0xC0, 0x00, 0x00, 0x07, 0xE7, 0xE0, 0x00, 0x1F, 0x80, 0x0F, 0xE0, 0x00, 0x00, 0x3E, 0xF8, 0x00, 0x00, 0x3F, 0xC0, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x0F, 0xC0, 0x00, 0x00, 0x07, 0xE7, 0xE0, 0x00, 0x1F, 0x80, 0x0F, 0xE0, 0x00, 0x00, 0x3E,
    0xF8, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x0F, 0xC0, 0x00, 0x00, 0x07, 0xC7, 0xE0, 0x00, 0x1F, 0x80, 0x0F, 0xE0, 0x00, 0x00, 0x3E, 0xF8, 0x00, 0x00, 0x7F, 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x0F, 0xC0, 0x00, 0x00, 0x0F,
    0xC3, 0xF0, 0x00, 0x1F, 0x80, 0x0F, 0xE0, 0x00, 0x00, 0x3E, 0xF8, 0x00, 0x00, 0x7F, 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x0F, 0xC0, 0x00, 0x00, 0x0F, 0xC3, 0xF0, 0x00, 0x1F, 0x80, 0x0F, 0xE0, 0x00, 0x00, 0x3E, 0xF8, 0x00, 0x00, 0xFE, 0x00,
    0x00, 0x00, 0x3F, 0x00, 0x00, 0x0F, 0xC0, 0x00, 0x00, 0x0F, 0x83, 0xF8, 0x00, 0x1F, 0x80, 0x0F, 0xE0, 0x00, 0x00, 0x3E, 0xF8, 0x00, 0x00, 0xFE, 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x0F, 0xC0, 0x00, 0x00, 0x1F, 0x81, 0xF8, 0x00, 0x1F, 0x80,
    0x0F, 0xC0, 0x00, 0x00, 0x3E, 0xF8, 0x00, 0x00, 0xFE, 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x0F, 0xC0, 0x00, 0x00, 0x1F, 0x81, 0xF8, 0x00, 0x1F, 0x80, 0x1F, 0xC0, 0x00, 0x00, 0x3E, 0xF8, 0x00, 0x00, 0xFE, 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00,
    0x0F, 0xFF, 0xFC, 0x00, 0x1F, 0x01, 0xFC, 0x00, 0x1F, 0x80, 0x3F, 0x80, 0x00, 0x00, 0x3E, 0xF8, 0x00, 0x00, 0xFC, 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x0F, 0xFF, 0xFC, 0x00, 0x3F, 0x00, 0xFC, 0x00, 0x1F, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x3E,
    0xF8, 0x00, 0x00, 0xFC, 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x0F, 0xFF, 0xFC, 0x00, 0x3F, 0x00, 0xFC, 0x00, 0x1F, 0xFF, 0xFE, 0x00, 0x00, 0x00, 0x3E, 0xF8, 0x00, 0x00, 0xFC, 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x0F, 0xFF, 0xFC, 0x00, 0x7E,
    0x00, 0xFE, 0x00, 0x1F, 0xFF, 0xF8, 0x00, 0x00, 0x00, 0x3E, 0xF8, 0x00, 0x00, 0xFC, 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x0F, 0xFF, 0xFC, 0x00, 0x7E, 0x00, 0x7E, 0x00, 0x1F, 0xFF, 0xE0, 0x00, 0x00, 0x00, 0x3E, 0xF8, 0x00, 0x00, 0xFC, 0x00,
    0x00, 0x00, 0x3F, 0x00, 0x00, 0x0F, 0xE0, 0x00, 0x00, 0x7E, 0x00, 0x7E, 0x00, 0x1F, 0xFF, 0xF0, 0x00, 0x00, 0x00, 0x3E, 0xF8, 0x00, 0x00, 0xFE, 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x0F, 0xC0, 0x00, 0x00, 0xFC, 0x00, 0x7F, 0x00, 0x1F, 0xFF,
    0xFC, 0x00, 0x00, 0x00, 0x3E, 0xF8, 0x00, 0x00, 0xFE, 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x0F, 0xC0, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0x1F, 0x81, 0xFE, 0x00, 0x00, 0x00, 0x3E, 0xF8, 0x00, 0x00, 0xFE, 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00,
    0x0F, 0xC0, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0x1F, 0x80, 0xFE, 0x00, 0x00, 0x00, 0x3E, 0xF8, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x0F, 0xC0, 0x00, 0x01, 0xFF, 0xFF, 0xFF, 0x80, 0x1F, 0x80, 0x7F, 0x00, 0x00, 0x00, 0x3E,
    0xF8, 0x00, 0x00, 0x7F, 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x0F, 0xC0, 0x00, 0x01, 0xFF, 0xFF, 0xFF, 0x80, 0x1F, 0x80, 0x3F, 0x80, 0x00, 0x00, 0x3E, 0xF8, 0x00, 0x00, 0x7F, 0x80, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x0F, 0xC0, 0x00, 0x01, 0xFF,
    0xFF, 0xFF, 0xC0, 0x1F, 0x80, 0x3F, 0x80, 0x00, 0x00, 0x3E, 0xF8, 0x00, 0x00, 0x3F, 0xC0, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x0F, 0xC0, 0x00, 0x03, 0xF8, 0x00, 0x1F, 0xC0, 0x1F, 0x80, 0x1F, 0xC0, 0x00, 0x00, 0x3E, 0xF8, 0x00, 0x00, 0x3F, 0xE0,
    0x00, 0x00, 0x3F, 0x00, 0x00, 0x0F, 0xC0, 0x00, 0x03, 0xF0, 0x00, 0x0F, 0xC0, 0x1F, 0x80, 0x1F, 0xE0, 0x00, 0x00, 0x3E, 0xF8, 0x00, 0x00, 0x1F, 0xF8, 0x00, 0xC0, 0x3F, 0x00, 0x00, 0x0F, 0xC0, 0x00, 0x07, 0xF0, 0x00, 0x0F, 0xE0, 0x1F, 0x80,
    0x0F, 0xE0, 0x00, 0x00, 0x3E, 0xF8, 0x00, 0x00, 0x1F, 0xFF, 0xFF, 0xC0, 0x3F, 0xFF, 0xFC, 0x0F, 0xFF, 0xFF, 0x07, 0xF0, 0x00, 0x0F, 0xE0, 0x1F, 0x80, 0x07, 0xF0, 0x00, 0x00, 0x3E, 0xF8, 0x00, 0x00, 0x0F, 0xFF, 0xFF, 0xC0, 0x3F, 0xFF, 0xFC,
    0x0F, 0xFF, 0xFF, 0x07, 0xE0, 0x00, 0x07, 0xE0, 0x1F, 0x80, 0x07, 0xF8, 0x00, 0x00, 0x3E, 0xF8, 0x00, 0x00, 0x07, 0xFF, 0xFF, 0xC0, 0x3F, 0xFF, 0xFC, 0x0F, 0xFF, 0xFF, 0x0F, 0xE0, 0x00, 0x07, 0xF0, 0x1F, 0x80, 0x03, 0xF8, 0x00, 0x00, 0x3E,
    0xF8, 0x00, 0x00, 0x01, 0xFF, 0xFF, 0xC0, 0x3F, 0xFF, 0xFC, 0x0F, 0xFF, 0xFF, 0x0F, 0xE0, 0x00, 0x07, 0xF0, 0x1F, 0x80, 0x03, 0xFC, 0x00, 0x00, 0x3E, 0xF8, 0x00, 0x00, 0x00, 0x7F, 0xFF, 0xC0, 0x3F, 0xFF, 0xFC, 0x0F, 0xFF, 0xFF, 0x0F, 0xC0,
    0x00, 0x03, 0xF0, 0x1F, 0x80, 0x01, 0xFC, 0x00, 0x00, 0x3E, 0xF8, 0x00, 0x00, 0x00, 0x1F, 0xFF, 0x00, 0x3F, 0xFF, 0xFC, 0x0F, 0xFF, 0xFF, 0x1F, 0xC0, 0x00, 0x03, 0xF8, 0x1F, 0x80, 0x00, 0xFE, 0x00, 0x00, 0x3E, 0xF8, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3E, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x3E, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3E, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3E, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3E,
    0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3E, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7E, 0x7C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7C, 0x7C, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7C, 0x7E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0xFC, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xF8, 0x3F, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xF8, 0x1F, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xF0,
    0x0F, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xE0, 0x0F, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3F, 0xC0, 0x07, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xC0, 0x01, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFE, 0x00, 0x00, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF8, 0x00, 0x00, 0x1F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF0, 0x00, 0x00, 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00
};

image_info_t note_btnclear_info =
{
    .type  = IMG_TYPE_RAW,
    .pixel = RTGRAPHIC_PIXEL_FORMAT_GRAY1,
    .x = 296,
    .y = 0,
    .w = 199,
    .h = 80,
    .size = 2000UL,
    .data = note_btnclear_199_80,
};

#endif
