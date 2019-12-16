/**
  * Copyright (c) 2019 Fuzhou Rockchip Electronics Co., Ltd
  *
  * SPDX-License-Identifier: Apache-2.0
  */

#include <rtthread.h>
#if defined(RT_USING_OLPC_DEMO)

#include "drv_heap.h"
#include "image_info.h"
#include "gcc_segment.h"
#include "olpc_display.h"

#if defined(RT_USING_TOUCH)
#include "drv_touch.h"
#include "olpc_touch.h"
#endif

/**
 * color palette for 1bpp
 */
static uint32_t bpp1_lut[2] =
{
    0x00000000, 0x00ffffff
};

/*
 **************************************************************************************************
 *
 * Macro define
 *
 **************************************************************************************************
 */
/* display win layers */
#define CLOCK_GRAY1_WIN     0
#define CLOCK_RGB332_WIN    1
#define CLOCK_RGB565_WIN    2

#define FIRMWARE_INFO_REQ       0x494E464FU //"INFO"
#define FIRMWARE_DOWNLOAD_REQ   0x46524551U //"FREQ"
#define FIRMWARE_DOWNLOAD_ACK   0x4641434BU //"FACK"
#define FIRMWARE_DOWNLOAD_OK    0x0U
#define FIRMWARE_DOWNLOAD_ERROR 0x1U

/*
 **************************************************************************************************
 *
 * Declaration
 *
 **************************************************************************************************
 */
rt_event_t olpc_main_event;

/*
 **************************************************************************************************
 *
 * Global static struct & data define
 *
 **************************************************************************************************
 */

/**
 * Get firmware segment info.
 */
rt_err_t olpc_firmware_info_request(FIRMWARE_REQ_PARAM *param)
{
#ifdef OLPC_OVERLAY_ENABLE
    struct MBOX_CMD_DAT cmdData;
    struct MBOX_REG *pReg;
    uint32_t intc1;

    RT_ASSERT(param);
    RT_ASSERT(param->id < SEGMENT_ID_MAX);

    intc1 = INTC1_BASE;
    *(uint32_t *)intc1 = 0x10;

    pReg = (struct MBOX_REG *)MBOX1_BASE;
    pReg->B2A_STATUS  = 1;
    pReg->B2A_INTEN  |= 1;
    pReg->A2B[0].CMD  = 0;
    pReg->A2B[0].DATA = 0;

    // send request & wait load
    cmdData.DATA = (rt_uint32_t)param;
    cmdData.CMD  = FIRMWARE_INFO_REQ;

    HAL_DCACHE_CleanByRange((rt_uint32_t)param, sizeof(FIRMWARE_REQ_PARAM));

    HAL_MBOX_SendMsg2(pReg, 0, &cmdData, 0);
    do
    {
        rt_thread_delay(1);
        HAL_MBOX_RecvMsg(pReg, 0);
    }
    while (pReg->A2B[0].CMD != FIRMWARE_DOWNLOAD_ACK);

    // clear register
    pReg->B2A[0].CMD  = 0;
    pReg->B2A[0].DATA = 0;

    HAL_DCACHE_InvalidateByRange((rt_uint32_t)param, sizeof(FIRMWARE_REQ_PARAM));

#if 0
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

#endif //OLPC_OVERLAY_ENABLE

    return RT_EOK;
}

/**
 * Get firmware segment data by param.
 */
rt_err_t olpc_firmware_content_request(FIRMWARE_REQ_PARAM *param)
{
#ifdef OLPC_OVERLAY_ENABLE
    struct MBOX_CMD_DAT cmdData;
    struct MBOX_REG *pReg;
    uint32_t intc1;

    RT_ASSERT(param);
    RT_ASSERT(param->id < SEGMENT_ID_MAX);
    RT_ASSERT((param->type & SEGMENT_ALL) != 0);
    if (param->buf)
    {
        /* only one type can use buffer mode */
        RT_ASSERT(param->type != SEGMENT_ALL);
        RT_ASSERT(param->type != (SEGMENT_TEXT | SEGMENT_DATA));
        RT_ASSERT(param->type != (SEGMENT_TEXT | SEGMENT_BSS));
        RT_ASSERT(param->type != (SEGMENT_DATA | SEGMENT_BSS));

        /* buffer and len must align CACHE_LINE_SIZE */
        RT_ASSERT((rt_uint32_t)param->buf % CACHE_LINE_SIZE == 0);
        RT_ASSERT((rt_uint32_t)param->reqlen % CACHE_LINE_SIZE == 0);
    }

    intc1 = INTC1_BASE;
    *(uint32_t *)intc1 = 0x10;

    pReg = (struct MBOX_REG *)MBOX1_BASE;
    pReg->B2A_STATUS  = 1;
    pReg->B2A_INTEN  |= 1;
    pReg->A2B[0].CMD  = 0;
    pReg->A2B[0].DATA = 0;

    // send request & wait load
    cmdData.DATA = (rt_uint32_t)param;
    cmdData.CMD  = FIRMWARE_DOWNLOAD_REQ;

    HAL_DCACHE_CleanByRange((rt_uint32_t)param, sizeof(FIRMWARE_REQ_PARAM));

    HAL_MBOX_SendMsg2(pReg, 0, &cmdData, 0);
    do
    {
        rt_thread_delay(1);
        HAL_MBOX_RecvMsg(pReg, 0);
    }
    while (pReg->A2B[0].CMD != FIRMWARE_DOWNLOAD_ACK);

    // clear register
    pReg->B2A[0].CMD  = 0;
    pReg->B2A[0].DATA = 0;

    HAL_DCACHE_InvalidateByRange((rt_uint32_t)param, sizeof(FIRMWARE_REQ_PARAM));

    // invalidate cache
    if (param->buf == RT_NULL)
    {
        if (param->info.CodeImageLength)
        {
            HAL_ICACHE_InvalidateByRange((rt_uint32_t)param->info.CodeImageBase,
                                         (rt_uint32_t)param->info.CodeImageLength);
        }
        if (param->info.DataImageLength)
        {
            HAL_DCACHE_InvalidateByRange((rt_uint32_t)param->info.DataImageBase,
                                         (rt_uint32_t)param->info.DataImageLength);
        }
        if (param->info.BssImageLength)
        {
            HAL_DCACHE_InvalidateByRange((rt_uint32_t)param->info.BssImageBase,
                                         (rt_uint32_t)param->info.BssImageLength);
        }
    }
    else
    {
        if ((SRAM_IADDR_START <= (rt_uint32_t)param->buf) && ((rt_uint32_t)param->buf < SRAM_IADDR_START + SRAM_SIZE))
        {
            HAL_ICACHE_InvalidateByRange((rt_uint32_t)param->buf, param->reqlen);
        }
        else
        {
            HAL_DCACHE_InvalidateByRange((rt_uint32_t)param->buf, param->reqlen);
        }
    }

#if 0
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

#endif //OLPC_OVERLAY_ENABLE

    return RT_EOK;
}

/**
 * Get firmware segment data by id.
 */
rt_err_t olpc_firmware_request(rt_uint32_t id)
{
#ifdef OLPC_OVERLAY_ENABLE
    FIRMWARE_REQ_PARAM  Param;
    FIRMWARE_REQ_PARAM *pParam = &Param;

    rt_memset(pParam, 0, sizeof(FIRMWARE_REQ_PARAM));

    pParam->id   = id;
    pParam->type = SEGMENT_ALL;
    olpc_firmware_content_request(pParam);

#endif //OLPC_OVERLAY_ENABLE

    return RT_EOK;
}

/*
 **************************************************************************************************
 *
 * olpc clock demo init & thread
 *
 **************************************************************************************************
 */
/**
 * olpc clock dmeo thread.
 */
static void olpc_main_thread(void *p)
{
    rt_err_t ret;
    uint32_t event;
    struct rt_display_lut lut0, lut1, lut2;
    struct rt_display_data *disp;

    /* init bpp_lut[256] */
    rt_display_update_lut(FORMAT_RGB_332);

    lut0.winId = CLOCK_RGB332_WIN;
    lut0.format = RTGRAPHIC_PIXEL_FORMAT_RGB332;
    lut0.lut  = bpp_lut;
    lut0.size = sizeof(bpp_lut) / sizeof(bpp_lut[0]);

    lut1.winId = CLOCK_GRAY1_WIN;
    lut1.format = RTGRAPHIC_PIXEL_FORMAT_GRAY1;
    lut1.lut  = bpp1_lut;
    lut1.size = sizeof(bpp1_lut) / sizeof(bpp1_lut[0]);

    lut2.winId = CLOCK_RGB565_WIN;
    lut2.format = RTGRAPHIC_PIXEL_FORMAT_RGB565;
    lut2.lut  = RT_NULL;
    lut2.size = 0;

    disp = rt_display_init(&lut0, &lut1, &lut2);
    RT_ASSERT(disp != RT_NULL);

    olpc_main_event = rt_event_create("olpcmain_event", RT_IPC_FLAG_FIFO);
    RT_ASSERT(olpc_main_event != RT_NULL);

#if defined(OLPC_APP_CLOCK_ENABLE)
    rt_event_send(olpc_main_event, EVENT_APP_CLOCK);
#elif defined(OLPC_APP_EBOOK_ENABLE)
    rt_event_send(olpc_main_event, EVENT_APP_EBOOK);
#elif defined(OLPC_APP_BLOCK_ENABLE)
    rt_event_send(olpc_main_event, EVENT_APP_BLOCK);
#elif defined(OLPC_APP_SNAKE_ENABLE)
    rt_event_send(olpc_main_event, EVENT_APP_SNAKE);
#elif defined(OLPC_APP_NOTE_ENABLE)
    rt_event_send(olpc_main_event, EVENT_APP_NOTE);
#elif defined(OLPC_APP_XSCREEN_ENABLE)
    rt_event_send(olpc_main_event, EVENT_APP_XSCREEN);
#endif

    while (1)
    {
        ret = rt_event_recv(olpc_main_event,
                            EVENT_APP_CLOCK | EVENT_APP_EBOOK | EVENT_APP_BLOCK | EVENT_APP_SNAKE | EVENT_APP_NOTE | EVENT_APP_XSCREEN,
                            RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR,
                            RT_WAITING_FOREVER, &event);
        RT_ASSERT(ret == RT_EOK);

        if (event & EVENT_APP_CLOCK)
        {
#if defined(OLPC_APP_CLOCK_ENABLE)
            olpc_firmware_request(SEGMENT_ID_OLPC_CLOCK);
            ret = olpc_clock_app_init();
            RT_ASSERT(ret == RT_EOK);
#endif
        }
        else if (event & EVENT_APP_EBOOK)
        {
#if defined(OLPC_APP_EBOOK_ENABLE)
            olpc_firmware_request(SEGMENT_ID_OLPC_EBOOK);
            ret = olpc_ebook_app_init();
            RT_ASSERT(ret == RT_EOK);
#endif
        }
        else if (event & EVENT_APP_BLOCK)
        {
#if defined(OLPC_APP_BLOCK_ENABLE)
            olpc_firmware_request(SEGMENT_ID_OLPC_BLOCK);
            ret = olpc_block_app_init();
            RT_ASSERT(ret == RT_EOK);
#endif
        }
        else if (event & EVENT_APP_SNAKE)
        {
#if defined(OLPC_APP_SNAKE_ENABLE)
            olpc_firmware_request(SEGMENT_ID_OLPC_SNAKE);
            ret = olpc_snake_app_init();
            RT_ASSERT(ret == RT_EOK);
#endif
        }
        else if (event & EVENT_APP_NOTE)
        {
#if defined(OLPC_APP_NOTE_ENABLE)
            olpc_firmware_request(SEGMENT_ID_OLPC_NOTE);
            ret = olpc_note_app_init();
            RT_ASSERT(ret == RT_EOK);
#endif
        }
        else /*if (event & EVENT_APP_XSCREEN)*/
        {
#if defined(OLPC_APP_XSCREEN_ENABLE)
            olpc_firmware_request(SEGMENT_ID_OLPC_XSCREEN);
            ret = olpc_xscreen_app_init();
            RT_ASSERT(ret == RT_EOK);
#endif
        }
    }

    /* Thread deinit */

    rt_event_delete(olpc_main_event);
    olpc_main_event = RT_NULL;

    rt_display_deinit(disp);
    disp = RT_NULL;
}

/**
 * olpc clock demo application init.
 */
int olpc_main_init(void)
{
    rt_thread_t rtt_olpcmain;

    rtt_olpcmain = rt_thread_create("olpcmain", olpc_main_thread, RT_NULL, 2048, 5, 10);
    RT_ASSERT(rtt_olpcmain != RT_NULL);
    rt_thread_startup(rtt_olpcmain);

    return RT_EOK;
}

INIT_APP_EXPORT(olpc_main_init);
#endif
