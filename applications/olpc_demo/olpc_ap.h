/**
  * Copyright (c) 2019 Fuzhou Rockchip Electronics Co., Ltd
  *
  * SPDX-License-Identifier: Apache-2.0
  */

#ifndef __OLPC_AP_H__
#define __OLPC_AP_H__

#include <rtthread.h>
#include "hal_def.h"
#include "gcc_segment.h"

/* AP command */
#define FIRMWARE_INFO_REQ       0x494E464FU //"INFO"
#define FIRMWARE_DOWNLOAD_REQ   0x46524551U //"FREQ"

/* AP return status */
#define FIRMWARE_DOWNLOAD_ACK   0x4641434BU //"FACK"
#define FIRMWARE_DOWNLOAD_OK    0x0U
#define FIRMWARE_DOWNLOAD_ERROR 0x1U

/**
 * firmware request param
 */
typedef struct _FIRMWARE_REQ_PARAM
{
    /* request param*/
    rt_uint32_t id;             /* id */
    rt_uint32_t type;           /* type: text, data, bss */

    rt_uint8_t  *buf;           /* buffer address, load firmware data to a buffer*/
    rt_uint32_t offset;         /* if buffer used, offset is used */
    rt_uint32_t reqlen;         /* if buffer used, request len is used */

    /* return param*/
    SEGMENT_INFO_T info;        /* segment info returned */

} HAL_CACHELINE_ALIGNED FIRMWARE_REQ_PARAM;


/**
 * Send command with AP.
 */
rt_err_t olpc_ap_command(rt_uint32_t cmd, void *param, rt_uint32_t paramlen);

#endif
