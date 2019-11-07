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

#endif /* _SEGMENT_INTO_H_ */
