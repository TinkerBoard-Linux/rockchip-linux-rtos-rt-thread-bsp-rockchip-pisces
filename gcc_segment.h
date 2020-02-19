/* SPDX-License-Identifier: Apache-2.0 */
/*
 * Copyright (c) 2019 Fuzhou Rockchip Electronics Co., Ltd
 */

#ifndef _SEGMENT_INTO_H_
#define _SEGMENT_INTO_H_

/**
 * segment ID
 */
typedef enum
{
    SEGMENT_ID_TEXT,
    SEGMENT_ID_TEXT_EXT,
    SEGMENT_ID_ARMEXTAB,
    SEGMENT_ID_ARMEXIDX,
    SEGMENT_ID_OLPC_CLOCK,
    SEGMENT_ID_OLPC_EBOOK,
    SEGMENT_ID_OLPC_BLOCK,
    SEGMENT_ID_OLPC_SNAKE,
    SEGMENT_ID_OLPC_NOTE,
    SEGMENT_ID_OLPC_BLN,
    SEGMENT_ID_OLPC_XSCREEN,
    SEGMENT_ID_OLPC_XSCREEN_RES00,
    SEGMENT_ID_OLPC_XSCREEN_RES01,
    SEGMENT_ID_OLPC_XSCREEN_RES02,
    SEGMENT_ID_OLPC_XSCREEN_RES03,
    SEGMENT_ID_OLPC_XSCREEN_RES04,
    SEGMENT_ID_OLPC_XSCREEN_RES05,
    SEGMENT_ID_OLPC_XSCREEN_RES06,
    SEGMENT_ID_OLPC_XSCREEN_RES07,
    SEGMENT_ID_OLPC_XSCREEN_RES08,
    SEGMENT_ID_OLPC_XSCREEN_RES09,
    SEGMENT_ID_OLPC_XSCREEN_RES10,
    SEGMENT_ID_OLPC_XSCREEN_RES11,
    SEGMENT_ID_OLPC_XSCREEN_RES12,
    SEGMENT_ID_OLPC_XSCREEN_RES13,
    SEGMENT_ID_OLPC_XSCREEN_RES14,
    SEGMENT_ID_OLPC_XSCREEN_RES15,
    SEGMENT_ID_OLPC_XSCREEN_RES16,
    SEGMENT_ID_OLPC_XSCREEN_RES17,
    SEGMENT_ID_OLPC_XSCREEN_RES18,
    SEGMENT_ID_OLPC_XSCREEN_RES19,
    SEGMENT_ID_MAX

} SEGMENT_ID;

/**
 * segment info
 */
typedef struct _SEGMENT_INFO_T
{
    rt_uint32_t *CodeLoadBase;
    rt_uint32_t *CodeImageBase;
    rt_uint32_t *CodeImageLength;

    rt_uint32_t *DataLoadBase;
    rt_uint32_t *DataImageBase;
    rt_uint32_t *DataImageLength;

    rt_uint32_t *BssImageBase;
    rt_uint32_t *BssImageLength;

    char         Name[16];

} SEGMENT_INFO_T;

/**
 * segment info table
 */
typedef struct _SEGMENT_INFO_TABLE
{
    rt_uint32_t      SegmentNum;
    SEGMENT_INFO_T   Segment[SEGMENT_ID_MAX];

} SEGMENT_INFO_TABLE;

/**
 * segment info table
 */
typedef struct _FIRMWARE_INFO_T
{
    rt_uint32_t            *LoadStartBase;
    SEGMENT_INFO_TABLE     SegmentInfo;

} FIRMWARE_INFO_T;

/**
 * firmware request type define
 */
#define SEGMENT_TEXT   (0x01UL << 0)
#define SEGMENT_DATA   (0x01UL << 1)
#define SEGMENT_BSS    (0x01UL << 2)
#define SEGMENT_ALL    (SEGMENT_TEXT | SEGMENT_DATA | SEGMENT_BSS)

#endif /* _SEGMENT_INTO_H_ */
