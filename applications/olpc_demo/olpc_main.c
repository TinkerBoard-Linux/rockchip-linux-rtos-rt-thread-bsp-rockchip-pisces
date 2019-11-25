/**
  * Copyright (c) 2019 Fuzhou Rockchip Electronics Co., Ltd
  *
  * SPDX-License-Identifier: Apache-2.0
  */

#include <rtthread.h>
#if defined(RT_USING_OLPC_DEMO)

#include "drv_heap.h"
#include "image_info.h"
#include "olpc_display.h"
#include "gcc_segment.h"

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

/*
 **************************************************************************************************
 *
 * Global static struct & data define
 *
 **************************************************************************************************
 */
rt_event_t olpc_main_event;
extern FIRMWARE_INFO_T const FirmwareInfoCopy;
void olpc_firmware_request(rt_uint32_t id)
{
    struct MBOX_CMD_DAT cmdData;
    struct MBOX_REG *pReg;
    uint32_t intc1;

    intc1 = 0x40020000;
    *(uint32_t *)intc1 = 0x10;

    pReg = (struct MBOX_REG *)0x40110000;
    pReg->B2A_STATUS = 1;
    pReg->B2A_INTEN |= 1;

    // clear A2B register
    pReg->A2B[0].CMD  = 0;
    pReg->A2B[0].DATA = 0;

    // send firmware download request cmd
    cmdData.CMD  = FIRMWARE_DOWNLOAD_REQ;
    cmdData.DATA = id;
    HAL_MBOX_SendMsg2(pReg, 0, &cmdData, 0);

    // wait for download OK
    do
    {
        rt_thread_delay(1);
        HAL_MBOX_RecvMsg(pReg, 0);
    }
    while (pReg->A2B[0].CMD != FIRMWARE_DOWNLOAD_ACK);

    pReg->B2A[0].CMD  = 0;
    pReg->B2A[0].DATA = 0;

    RT_ASSERT(pReg->A2B[0].DATA == FIRMWARE_DOWNLOAD_OK);

    if (FirmwareInfoCopy.SegmentInfo.Segment[id].CodeImageLength)
    {
        HAL_ICACHE_InvalidateByRange((rt_uint32_t)FirmwareInfoCopy.SegmentInfo.Segment[id].CodeImageBase,
                                     (rt_uint32_t)FirmwareInfoCopy.SegmentInfo.Segment[id].CodeImageLength);
    }
    if (FirmwareInfoCopy.SegmentInfo.Segment[id].DataImageLength)
    {
        HAL_DCACHE_InvalidateByRange((rt_uint32_t)FirmwareInfoCopy.SegmentInfo.Segment[id].DataImageBase,
                                     (rt_uint32_t)FirmwareInfoCopy.SegmentInfo.Segment[id].DataImageLength);
    }
    if (FirmwareInfoCopy.SegmentInfo.Segment[id].BssImageLength)
    {
        HAL_DCACHE_InvalidateByRange((rt_uint32_t)FirmwareInfoCopy.SegmentInfo.Segment[id].BssImageBase,
                                     (rt_uint32_t)FirmwareInfoCopy.SegmentInfo.Segment[id].BssImageLength);
    }
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

    rt_event_send(olpc_main_event, EVENT_APP_CLOCK);

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
