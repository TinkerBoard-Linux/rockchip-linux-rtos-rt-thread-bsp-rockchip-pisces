/**
  * Copyright (c) 2019 Fuzhou Rockchip Electronics Co., Ltd
  *
  * SPDX-License-Identifier: Apache-2.0
  */

#include <rtthread.h>
#if defined(RT_USING_OLPC_DEMO)
#include "hal_base.h"
#include "olpc_ap.h"

/*
 **************************************************************************************************
 *
 * Macro define
 *
 **************************************************************************************************
 */

/*
 **************************************************************************************************
 *
 * Declaration
 *
 **************************************************************************************************
 */

/*
 **************************************************************************************************
 *
 * Global static struct & data define
 *
 **************************************************************************************************
 */
#ifdef OLPC_OVERLAY_ENABLE
static rt_err_t olpc_firmware_info_show(void *p)
{
#if 0
    FIRMWARE_REQ_PARAM *param = (FIRMWARE_REQ_PARAM *)p;

    rt_kprintf("%d code lma = 0x%08x, vma = 0x%08x, size = 0x%08x, %s\n", param->id,
               param->info.CodeLoadBase,
               param->info.CodeImageBase,
               param->info.CodeImageLength,
               param->info.Name);
    rt_kprintf("%d data lma = 0x%08x, vma = 0x%08x, size = 0x%08x, %s\n", param->id,
               param->info.DataLoadBase,
               param->info.DataImageBase,
               param->info.DataImageLength,
               param->info.Name);
    rt_kprintf("%d  bss lma = 0x%08x, vma = 0x%08x, size = 0x%08x, %s\n", param->id,
               0,
               param->info.BssImageBase,
               param->info.BssImageLength,
               param->info.Name);
#endif
    return RT_EOK;
}

static rt_err_t olpc_firmware_cache_invalidate(void *p)
{
    FIRMWARE_REQ_PARAM *param = (FIRMWARE_REQ_PARAM *)p;

    // invalidate cache
    if (param->buf == RT_NULL)
    {
        if (param->info.CodeImageLength)
            rt_hw_cpu_icache_ops(RT_HW_CACHE_INVALIDATE, param->info.CodeImageBase, (rt_uint32_t)param->info.CodeImageLength);
        if (param->info.DataImageLength)
            rt_hw_cpu_dcache_ops(RT_HW_CACHE_INVALIDATE, param->info.DataImageBase, (rt_uint32_t)param->info.DataImageLength);
        if (param->info.BssImageLength)
            rt_hw_cpu_dcache_ops(RT_HW_CACHE_INVALIDATE, param->info.BssImageBase, (rt_uint32_t)param->info.BssImageLength);
    }
    else
    {
        if ((SRAM_IADDR_START <= (rt_uint32_t)param->buf) && ((rt_uint32_t)param->buf < SRAM_IADDR_START + SRAM_SIZE))
            rt_hw_cpu_icache_ops(RT_HW_CACHE_INVALIDATE, param->buf, (rt_uint32_t)param->reqlen);
        else
            rt_hw_cpu_dcache_ops(RT_HW_CACHE_INVALIDATE, param->buf, (rt_uint32_t)param->reqlen);
    }

    return RT_EOK;
}
#endif

static rt_err_t olpc_send_ap_command(rt_uint32_t cmd, void *param, rt_uint32_t paramlen)
{
    struct MBOX_CMD_DAT cmdData;
    struct MBOX_REG *pReg;
    uint32_t intc1, timeout, status = FIRMWARE_DOWNLOAD_OK;

    RT_ASSERT(param);

    intc1 = INTC1_BASE;
    *(uint32_t *)intc1 = 0x10;

    pReg = (struct MBOX_REG *)MBOX1_BASE;
    pReg->B2A_STATUS  = 1;
    pReg->B2A_INTEN  |= 1;
    pReg->A2B[0].CMD  = 0;
    pReg->A2B[0].DATA = 0;

    // send request & wait load
    cmdData.DATA = (rt_uint32_t)param;
    cmdData.CMD  = cmd;

    rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, param, paramlen);

    HAL_MBOX_SendMsg2(pReg, 0, &cmdData, 0);
    timeout = 1000;
    do
    {
        rt_thread_delay(1);

        HAL_MBOX_RecvMsg(pReg, 0);
        if (pReg->A2B[0].CMD == FIRMWARE_DOWNLOAD_ACK)
        {
            status = pReg->A2B[0].DATA;
            break;
        }
    }
    while (--timeout);
    // clear register
    pReg->B2A[0].CMD  = 0;
    pReg->B2A[0].DATA = 0;

    rt_hw_cpu_dcache_ops(RT_HW_CACHE_INVALIDATE, param, paramlen);

    if (timeout == 0)
    {
        return RT_ETIMEOUT;
    }

    if (status != FIRMWARE_DOWNLOAD_OK)
    {
        return RT_ERROR;
    }

    return RT_EOK;
}

rt_err_t olpc_ap_command(rt_uint32_t cmd, void *param, rt_uint32_t paramlen)
{
    rt_err_t ret = RT_EOK;
    switch (cmd)
    {
#ifdef OLPC_OVERLAY_ENABLE
    case FIRMWARE_INFO_REQ:
        ret = olpc_send_ap_command(FIRMWARE_INFO_REQ, param, paramlen);
        if (ret == RT_EOK)
        {
            olpc_firmware_info_show(param);
        }
        break;
    case FIRMWARE_DOWNLOAD_REQ:
        ret = olpc_send_ap_command(FIRMWARE_DOWNLOAD_REQ, param, paramlen);
        if (ret == RT_EOK)
        {
            olpc_firmware_cache_invalidate(param);
        }
        break;
#endif
    default:
        rt_kprintf("olpc_ap_command: Undefined command!!!\n");
        break;
    }
    return ret;
}

#endif
