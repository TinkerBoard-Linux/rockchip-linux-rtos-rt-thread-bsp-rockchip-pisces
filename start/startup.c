/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-12-10     Cliff      first implementation
 *
 */

#include <rthw.h>
#include <rtthread.h>

#include "board.h"
#include "drv_heap.h"

/*@{*/

extern int  rt_application_init(void);

#if defined(__CC_ARM) || defined(__CLANG_ARM)
extern int Image$$RW_RAM$$ZI$$Limit;
#define RK_SRAM_BEGIN    (&Image$$RW_RAM$$ZI$$Limit)
#elif __ICCARM__
#pragma section="HEAP"
#define RK_SRAM_BEGIN    (__segment_end("HEAP"))
#else
extern int __heap_start__;
#define RK_SRAM_BEGIN    (&__heap_start__)
#ifdef RT_USING_LARGE_HEAP
extern int __large_start__, __large_end__;
#define RK_LARGE_BEGIN   (&__large_start__)
#define RK_LARGE_END     (&__large_end__)
#endif
#endif

/*******************************************************************************
* Function Name  : Firmware info table
* Description    : Firmware info table for code overlay
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
#include "gcc_segment.h"

extern rt_uint32_t __firmware_lma;

extern rt_uint32_t __text_lma;
extern rt_uint32_t __text_vma;
extern rt_uint32_t __text_len;
extern rt_uint32_t __data_lma;
extern rt_uint32_t __data_vma;
extern rt_uint32_t __data_len;
extern rt_uint32_t __bss_vma;
extern rt_uint32_t __bss_len;

extern rt_uint32_t __text_ext_lma;
extern rt_uint32_t __text_ext_vma;
extern rt_uint32_t __text_ext_len;
extern rt_uint32_t __data_ext_lma;
extern rt_uint32_t __data_ext_vma;
extern rt_uint32_t __data_ext_len;

extern rt_uint32_t __arm_extab_lma;
extern rt_uint32_t __arm_extab_vma;
extern rt_uint32_t __arm_extab_len;

extern rt_uint32_t __arm_exidx_lma;
extern rt_uint32_t __arm_exidx_vma;
extern rt_uint32_t __arm_exidx_len;

extern rt_uint32_t __olpclock_text_lma;
extern rt_uint32_t __olpclock_text_vma;
extern rt_uint32_t __olpclock_text_len;
extern rt_uint32_t __olpclock_data_lma;
extern rt_uint32_t __olpclock_data_vma;
extern rt_uint32_t __olpclock_data_len;
extern rt_uint32_t __olpclock_bss_vma;
extern rt_uint32_t __olpclock_bss_len;

extern rt_uint32_t __olpebook_text_lma;
extern rt_uint32_t __olpebook_text_vma;
extern rt_uint32_t __olpebook_text_len;
extern rt_uint32_t __olpebook_data_lma;
extern rt_uint32_t __olpebook_data_vma;
extern rt_uint32_t __olpebook_data_len;
extern rt_uint32_t __olpebook_bss_vma;
extern rt_uint32_t __olpebook_bss_len;

extern rt_uint32_t __olpblock_text_lma;
extern rt_uint32_t __olpblock_text_vma;
extern rt_uint32_t __olpblock_text_len;
extern rt_uint32_t __olpblock_data_lma;
extern rt_uint32_t __olpblock_data_vma;
extern rt_uint32_t __olpblock_data_len;
extern rt_uint32_t __olpblock_bss_vma;
extern rt_uint32_t __olpblock_bss_len;

extern rt_uint32_t __olpsnake_text_lma;
extern rt_uint32_t __olpsnake_text_vma;
extern rt_uint32_t __olpsnake_text_len;
extern rt_uint32_t __olpsnake_data_lma;
extern rt_uint32_t __olpsnake_data_vma;
extern rt_uint32_t __olpsnake_data_len;
extern rt_uint32_t __olpsnake_bss_vma;
extern rt_uint32_t __olpsnake_bss_len;

extern rt_uint32_t __olpnote_text_lma;
extern rt_uint32_t __olpnote_text_vma;
extern rt_uint32_t __olpnote_text_len;
extern rt_uint32_t __olpnote_data_lma;
extern rt_uint32_t __olpnote_data_vma;
extern rt_uint32_t __olpnote_data_len;
extern rt_uint32_t __olpnote_bss_vma;
extern rt_uint32_t __olpnote_bss_len;

__attribute__((section("_FirmwareTable_")))
FIRMWARE_INFO_T const FirmwareInfo  =
{
    &__firmware_lma,

    // SEGMENT_INFO_TABLE
    {
        (rt_uint32_t)(SEGMENT_ID_MAX),

        // SEGMENT_INFO_T
        {
            // .text
            {
                &__text_lma,
                &__text_vma,
                &__text_len,

                &__data_lma,
                &__data_vma,
                &__data_len,

                &__bss_vma,
                &__bss_len,

                "TEXT",             // string len must < 16
            },

            // .text_ext
            {
                &__text_ext_lma,
                &__text_ext_vma,
                &__text_ext_len,

                &__data_ext_lma,
                &__data_ext_vma,
                &__data_ext_len,

                0,
                0,

                "TEXT_EXT",         // string len must < 16
            },

            // .ARM.extab
            {
                &__arm_extab_lma,
                &__arm_extab_vma,
                &__arm_extab_len,

                0,
                0,
                0,

                0,
                0,

                "ARMEXTAB",         // string len must < 16
            },

            // .ARM.exidx
            {
                &__arm_exidx_lma,
                &__arm_exidx_vma,
                &__arm_exidx_len,

                0,
                0,
                0,

                0,
                0,

                "ARMEXIDX",         // string len must < 16
            },

            // .olpc_clock
            {
                &__olpclock_text_lma,
                &__olpclock_text_vma,
                &__olpclock_text_len,

                &__olpclock_data_lma,
                &__olpclock_data_vma,
                &__olpclock_data_len,

                &__olpclock_bss_vma,
                &__olpclock_bss_len,

                "OLPC_CLOCK",       // string len must < 16
            },

            // .olpc_ebook
            {
                &__olpebook_text_lma,
                &__olpebook_text_vma,
                &__olpebook_text_len,

                &__olpebook_data_lma,
                &__olpebook_data_vma,
                &__olpebook_data_len,

                &__olpebook_bss_vma,
                &__olpebook_bss_len,

                "OLPC_EBOOK",       // string len must < 16
            },

            // .olpc_block
            {
                &__olpblock_text_lma,
                &__olpblock_text_vma,
                &__olpblock_text_len,

                &__olpblock_data_lma,
                &__olpblock_data_vma,
                &__olpblock_data_len,

                &__olpblock_bss_vma,
                &__olpblock_bss_len,

                "OLPC_BLOCK",       // string len must < 16
            },

            // .olpc_snake
            {
                &__olpsnake_text_lma,
                &__olpsnake_text_vma,
                &__olpsnake_text_len,

                &__olpsnake_data_lma,
                &__olpsnake_data_vma,
                &__olpsnake_data_len,

                &__olpsnake_bss_vma,
                &__olpsnake_bss_len,

                "OLPC_SNAKE",       // string len must < 16
            },

            // .olpc_note
            {
                &__olpnote_text_lma,
                &__olpnote_text_vma,
                &__olpnote_text_len,

                &__olpnote_data_lma,
                &__olpnote_data_vma,
                &__olpnote_data_len,

                &__olpnote_bss_vma,
                &__olpnote_bss_len,

                "OLPC_NOTE",        // string len must < 16
            },
        },
    },
};

// The copy of FirmwareInfo table
FIRMWARE_INFO_T const FirmwareInfoCopy  =
{
    &__firmware_lma,

    // SEGMENT_INFO_TABLE
    {
        (rt_uint32_t)(SEGMENT_ID_MAX),

        // SEGMENT_INFO_T
        {
            // .text
            {
                &__text_lma,
                &__text_vma,
                &__text_len,

                &__data_lma,
                &__data_vma,
                &__data_len,

                &__bss_vma,
                &__bss_len,

                "TEXT",             // string len must < 16
            },

            // .text_ext
            {
                &__text_ext_lma,
                &__text_ext_vma,
                &__text_ext_len,

                &__data_ext_lma,
                &__data_ext_vma,
                &__data_ext_len,

                0,
                0,

                "TEXT_EXT",         // string len must < 16
            },

            // .ARM.extab
            {
                &__arm_extab_lma,
                &__arm_extab_vma,
                &__arm_extab_len,

                0,
                0,
                0,

                0,
                0,

                "ARMEXTAB",         // string len must < 16
            },

            // .ARM.exidx
            {
                &__arm_exidx_lma,
                &__arm_exidx_vma,
                &__arm_exidx_len,

                0,
                0,
                0,

                0,
                0,

                "ARMEXIDX",         // string len must < 16
            },

            // .olpc_clock
            {
                &__olpclock_text_lma,
                &__olpclock_text_vma,
                &__olpclock_text_len,

                &__olpclock_data_lma,
                &__olpclock_data_vma,
                &__olpclock_data_len,

                &__olpclock_bss_vma,
                &__olpclock_bss_len,

                "OLPC_CLOCK",       // string len must < 16
            },

            // .olpc_ebook
            {
                &__olpebook_text_lma,
                &__olpebook_text_vma,
                &__olpebook_text_len,

                &__olpebook_data_lma,
                &__olpebook_data_vma,
                &__olpebook_data_len,

                &__olpebook_bss_vma,
                &__olpebook_bss_len,

                "OLPC_EBOOK",       // string len must < 16
            },

            // .olpc_block
            {
                &__olpblock_text_lma,
                &__olpblock_text_vma,
                &__olpblock_text_len,

                &__olpblock_data_lma,
                &__olpblock_data_vma,
                &__olpblock_data_len,

                &__olpblock_bss_vma,
                &__olpblock_bss_len,

                "OLPC_BLOCK",       // string len must < 16
            },

            // .olpc_snake
            {
                &__olpsnake_text_lma,
                &__olpsnake_text_vma,
                &__olpsnake_text_len,

                &__olpsnake_data_lma,
                &__olpsnake_data_vma,
                &__olpsnake_data_len,

                &__olpsnake_bss_vma,
                &__olpsnake_bss_len,

                "OLPC_SNAKE",       // string len must < 16
            },

            // .olpc_note
            {
                &__olpnote_text_lma,
                &__olpnote_text_vma,
                &__olpnote_text_len,

                &__olpnote_data_lma,
                &__olpnote_data_vma,
                &__olpnote_data_len,

                &__olpnote_bss_vma,
                &__olpnote_bss_len,

                "OLPC_NOTE",        // string len must < 16
            },
        },
    },
};

#if 1
static void firmware_info(int argc, char **argv)
{
    rt_uint32_t i;

    rt_kprintf("SegmentNum   = %d\n", FirmwareInfoCopy.SegmentInfo.SegmentNum);
    rt_kprintf("FirmwareBase = 0x%08x\n", FirmwareInfoCopy.LoadStartBase);
    rt_kprintf("FirmwareTabeSize = %d, %d\n", sizeof(FirmwareInfoCopy), sizeof(FIRMWARE_INFO_T));
    rt_kprintf("******************************************************************************\n");
    rt_kprintf("         text_LMA    text_VMA    text_len    data_LMA    data_VMA    data_len    bss_VMA     bss_len     Name\n");
    for (i = 0; i < FirmwareInfoCopy.SegmentInfo.SegmentNum; i++)
    {
        rt_kprintf("ID = %d, 0x%08x, 0x%08x, 0x%08x, 0x%08x, 0x%08x, 0x%08x, 0x%08x, 0x%08x, %s\n", i,
                   FirmwareInfoCopy.SegmentInfo.Segment[i].CodeLoadBase,
                   FirmwareInfoCopy.SegmentInfo.Segment[i].CodeImageBase,
                   FirmwareInfoCopy.SegmentInfo.Segment[i].CodeImageLength,
                   FirmwareInfoCopy.SegmentInfo.Segment[i].DataLoadBase,
                   FirmwareInfoCopy.SegmentInfo.Segment[i].DataImageBase,
                   FirmwareInfoCopy.SegmentInfo.Segment[i].DataImageLength,
                   FirmwareInfoCopy.SegmentInfo.Segment[i].BssImageBase,
                   FirmwareInfoCopy.SegmentInfo.Segment[i].BssImageLength,
                   FirmwareInfoCopy.SegmentInfo.Segment[i].Name);
    }
    rt_kprintf("******************************************************************************\n");
}

#ifdef RT_USING_FINSH
#include <finsh.h>
MSH_CMD_EXPORT(firmware_info, firmware info. e.g: firmware_info);
#endif
#endif

/*******************************************************************************
* Function Name  : assert_failed
* Description    : Reports the name of the source file and the source line number
*                  where the assert error has occurred.
* Input          : - file: pointer to the source file name
*                  - line: assert error line source number
* Output         : None
* Return         : None
*******************************************************************************/
void assert_failed(uint8_t *file, uint32_t line)
{
    rt_kprintf("\n\r Wrong parameter value detected on\r\n");
    rt_kprintf("       file  %s\r\n", file);
    rt_kprintf("       line  %d\r\n", line);

    while (1)
        ;
}

#ifdef RT_USING_CMBACKTRACE
extern int rt_cm_backtrace_init(void);
#endif

/**
 * This function will startup RT-Thread RTOS.
 */
void rtthread_startup(void)
{
#ifdef RT_USING_CMBACKTRACE
    /* init cmbacktrace */
    rt_cm_backtrace_init();
#endif

    /* init interrupt */
    rt_hw_interrupt_init();

    /* init board */
    rt_hw_board_init();

    /* show version */
    rt_show_version();

    /* init tick */
    rt_system_tick_init();

    /* init kernel object */
    rt_system_object_init();

    /* init timer system */
    rt_system_timer_init();

#ifdef RT_USING_HEAP
    rt_system_heap_init((void *)RK_SRAM_BEGIN, (void *)RK_SYS_HEAP_END);
#endif

#ifdef RT_USING_UNCACHE_HEAP
    rt_uncache_heap_init((void *)RK_UNCACHE_HEAP_START, (void *)RK_SRAM_END);
#endif

#ifdef RT_USING_LARGE_HEAP
    rt_large_heap_init((void *)RK_LARGE_BEGIN, (void *)RK_LARGE_END);
#endif

    /* init scheduler system */
    rt_system_scheduler_init();

    /* init application */
    rt_application_init();

    /* init timer thread */
    rt_system_timer_thread_init();

    /* init idle thread */
    rt_thread_idle_init();

    /* start scheduler */
    rt_system_scheduler_start();

    /* never reach here */
    return;
}

int _start(void)
{
    /* disable interrupt first */
    rt_hw_interrupt_disable();

    /* startup RT-Thread RTOS */
    rtthread_startup();

    return 0;
}
