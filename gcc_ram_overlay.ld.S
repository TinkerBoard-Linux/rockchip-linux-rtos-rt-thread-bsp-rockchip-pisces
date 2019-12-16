/* Linker script to place sections and symbol values. Should be used together
 * with other linker script that defines memory regions FLASH and RAM.
 * It references following symbols, which must be defined in code:
 *   Reset_Handler : Entry of reset handler
 *
 * It defines following symbols, which code can use without definition:
 *   __exidx_start
 *   __exidx_end
 *   __copy_table_start__
 *   __copy_table_end__
 *   __zero_table_start__
 *   __zero_table_end__
 *   __etext
 *   __data_start__
 *   __preinit_array_start
 *   __preinit_array_end
 *   __init_array_start
 *   __init_array_end
 *   __fini_array_start
 *   __fini_array_end
 *   __data_end__
 *   __bss_start__
 *   __bss_end__
 *   __end__
 *   end
 *   __HeapLimit
 *   __StackLimit
 *   __StackTop
 *   __stack
 */

#include "rtconfig.h"

ENTRY(Reset_Handler)
_ram_fs_size = 0x10000;
_system_stack_size = 0x400;
_code_start_addr = 0x04000000;
_data_start_off  = 0x1c000000;

_dtcm_start_addr = 0x30200000;
_dtcm_heap_size  = 0x80000;

SECTIONS
{
    /*
     * Firmware table, used for code overlay
     * Must stored at top of firmware bin.
     */
    . = _code_start_addr;
    __firmware_table_lma = .;
    __firmware_table_vma = .;
    .firmware_table (__firmware_table_vma) : AT (__firmware_table_lma)
    {
        . = ALIGN(4);
        KEEP(*(_FirmwareTable_))
        . = ALIGN(4);
    }
    __firmware_lma = LOADADDR(.firmware_table);
    __firmware_len = SIZEOF(.firmware_table);

/*
*************************************************************************
*
* Code region: start at 0x04000000
*
*************************************************************************
*/
    /* start & text code region */
    . = _code_start_addr;
    _stext = .;
    _stext_ext = .;
    __text_lma = __firmware_lma + __firmware_len;
    __text_vma = .;
    .text (_code_start_addr) : AT (__text_lma)
    {
        . = ALIGN(32);
        KEEP(*(.vectors))               /* Startup code */
        . = ALIGN(4);
        *(.text)                        /* remaining code */
        *(.rodata)                      /* read-only data (constants) */
        *(.glue_7)
        *(.glue_7t)
        *(.gnu.linkonce.t*)

        /* section information for finsh shell */
        . = ALIGN(4);
        __fsymtab_start = .;
        KEEP(*(FSymTab))
        __fsymtab_end = .;
        . = ALIGN(4);
        __vsymtab_start = .;
        KEEP(*(VSymTab))
        __vsymtab_end = .;
        . = ALIGN(4);

        /* section information for initial. */
        . = ALIGN(4);
        __rt_init_start = .;
        KEEP(*(SORT(.rti_fn*)))
        __rt_init_end = .;
        . = ALIGN(32);
    }
    __text_len = SIZEOF(.text);

    /*********************************************************************/
    /* olpc applications code region */
    __olpapps_text_vma = .;

    /* olpc clock */
    __olpclock_text_lma = __text_lma + __text_len;
    __olpclock_text_vma = __olpapps_text_vma;
    .olpc_clock_text (__olpclock_text_vma) : AT (__olpclock_text_lma)
    {
        . = ALIGN(32);
        */olpc_demo/olpc_clock.o(.text*)
        */olpc_demo/resource/clock_*_*_*.o(.text*)
        */olpc_demo/resource/fingerprint*_*_*.o(.text*)
        */olpc_demo/resource/home_*_*_*.o(.text*)
        */olpc_demo/resource/lock_*_*_*.o(.text*)
        */olpc_demo/resource/msg_*_*_*.o(.text*)

        */olpc_demo/olpc_clock.o(.rodata*)
        */olpc_demo/resource/clock_*_*_*.o(.rodata*)
        */olpc_demo/resource/fingerprint*_*_*.o(.rodata*)
        */olpc_demo/resource/home_*_*_*.o(.rodata*)
        */olpc_demo/resource/lock_*_*_*.o(.rodata*)
        */olpc_demo/resource/msg_*_*_*.o(.rodata*)
        . = ALIGN(32);
    }
    __olpclock_text_len = SIZEOF(.olpc_clock_text);
    __olpapps_text_len = MAX(0, __olpclock_text_len);

    /* olpc ebook */
    __olpebook_text_lma = __olpclock_text_lma + __olpclock_text_len;
    __olpebook_text_vma = __olpapps_text_vma;
    .olpc_ebook_text (__olpebook_text_vma) : AT (__olpebook_text_lma)
    {
        . = ALIGN(32);
        */olpc_demo/olpc_ebook.o(.text*)
        */olpc_demo/resource/ebook_*_*_*.o(.text*)

        */olpc_demo/olpc_ebook.o(.rodata*)
        */olpc_demo/resource/ebook_*_*_*.o(.rodata*)
        . = ALIGN(32);
    }
    __olpebook_text_len = SIZEOF(.olpc_ebook_text);
    __olpapps_text_len  = MAX(__olpapps_text_len, __olpebook_text_len);

    /* olpc block */
    __olpblock_text_lma = __olpebook_text_lma + __olpebook_text_len;
    __olpblock_text_vma = __olpapps_text_vma;
    .olpc_block_text (__olpblock_text_vma) : AT (__olpblock_text_lma)
    {
        . = ALIGN(32);
        */olpc_demo/olpc_block.o(.text*)
        */olpc_demo/resource/block_*_*_*.o(.text*)

        */olpc_demo/olpc_block.o(.rodata*)
        */olpc_demo/resource/block_*_*_*.o(.rodata*)
        . = ALIGN(32);
    }
    __olpblock_text_len = SIZEOF(.olpc_block_text);
    __olpapps_text_len  = MAX(__olpapps_text_len, __olpblock_text_len);

    /* olpc snake */
    __olpsnake_text_lma = __olpblock_text_lma + __olpblock_text_len;
    __olpsnake_text_vma = __olpapps_text_vma;
    .olpc_snake_text (__olpsnake_text_vma) : AT (__olpsnake_text_lma)
    {
        . = ALIGN(32);
        */olpc_demo/olpc_snake.o(.text*)
        */olpc_demo/resource/snake_*_*_*.o(.text*)

        */olpc_demo/olpc_snake.o(.rodata*)
        */olpc_demo/resource/snake_*_*_*.o(.rodata*)
        . = ALIGN(32);
    }
    __olpsnake_text_len = SIZEOF(.olpc_snake_text);
    __olpapps_text_len  = MAX(__olpapps_text_len, __olpsnake_text_len);

    /* olpc note */
    __olpnote_text_lma = __olpsnake_text_lma + __olpsnake_text_len;
    __olpnote_text_vma = __olpapps_text_vma;
    .olpc_note_text (__olpnote_text_vma) : AT (__olpnote_text_lma)
    {
        . = ALIGN(32);
        */olpc_demo/olpc_note.o(.text*)
        */olpc_demo/resource/note_*_*_*.o(.text*)

        */olpc_demo/olpc_note.o(.rodata*)
        */olpc_demo/resource/note_*_*_*.o(.rodata*)
        . = ALIGN(32);
    }
    __olpnote_text_len = SIZEOF(.olpc_note_text);
    __olpapps_text_len  = MAX(__olpapps_text_len, __olpnote_text_len);

    /* olpc xscreen */
    __olpxscreen_text_lma = __olpnote_text_lma + __olpnote_text_len;
    __olpxscreen_text_vma = __olpapps_text_vma;
    .olpc_xscreen_text (__olpxscreen_text_vma) : AT (__olpxscreen_text_lma)
    {
        . = ALIGN(32);
        */olpc_demo/olpc_xscreen.o(.text*)
        */olpc_demo/resource/x_screen*_*_*.o(.text*)

        */olpc_demo/olpc_xscreen.o(.rodata*)
        . = ALIGN(32);
    }
    __olpxscreen_text_len = SIZEOF(.olpc_xscreen_text);
    __olpapps_text_len    = MAX(__olpapps_text_len, __olpxscreen_text_len);

    /* olpc xscreen : resource pic00*/
    __olpxscreen00_res_lma = __olpxscreen_text_lma + __olpxscreen_text_len;
    __olpxscreen00_res_vma = __olpxscreen_text_vma + __olpxscreen_text_len;
    .olpc_xscreen00_res (__olpxscreen00_res_vma) : AT (__olpxscreen00_res_lma)
    {
        . = ALIGN(32);
        */olpc_demo/resource/x_screen00_*_*.o(.rodata*)
        . = ALIGN(32);
    }
    __olpxscreen00_res_len = SIZEOF(.olpc_xscreen00_res);
    __olpapps_text_len    = MAX(__olpapps_text_len, __olpxscreen_text_len + __olpxscreen00_res_len);

    /* olpc xscreen : resource pic01*/
    __olpxscreen01_res_lma = __olpxscreen00_res_lma + __olpxscreen00_res_len;
    __olpxscreen01_res_vma = __olpxscreen_text_vma + __olpxscreen_text_len;
    .olpc_xscreen01_res (__olpxscreen01_res_vma) : AT (__olpxscreen01_res_lma)
    {
        . = ALIGN(32);
        */olpc_demo/resource/x_screen01_*_*.o(.rodata*)
        . = ALIGN(32);
    }
    __olpxscreen01_res_len = SIZEOF(.olpc_xscreen01_res);
    __olpapps_text_len    = MAX(__olpapps_text_len, __olpxscreen_text_len + __olpxscreen01_res_len);

    /* olpc xscreen : resource pic02*/
    __olpxscreen02_res_lma = __olpxscreen01_res_lma + __olpxscreen01_res_len;
    __olpxscreen02_res_vma = __olpxscreen_text_vma + __olpxscreen_text_len;
    .olpc_xscreen02_res (__olpxscreen02_res_vma) : AT (__olpxscreen02_res_lma)
    {
        . = ALIGN(32);
        */olpc_demo/resource/x_screen02_*_*.o(.rodata*)
        . = ALIGN(32);
    }
    __olpxscreen02_res_len = SIZEOF(.olpc_xscreen02_res);
    __olpapps_text_len    = MAX(__olpapps_text_len, __olpxscreen_text_len + __olpxscreen02_res_len);

    /* olpc xscreen : resource pic03*/
    __olpxscreen03_res_lma = __olpxscreen02_res_lma + __olpxscreen02_res_len;
    __olpxscreen03_res_vma = __olpxscreen_text_vma + __olpxscreen_text_len;
    .olpc_xscreen03_res (__olpxscreen03_res_vma) : AT (__olpxscreen03_res_lma)
    {
        . = ALIGN(32);
        */olpc_demo/resource/x_screen03_*_*.o(.rodata*)
        . = ALIGN(32);
    }
    __olpxscreen03_res_len = SIZEOF(.olpc_xscreen03_res);
    __olpapps_text_len    = MAX(__olpapps_text_len, __olpxscreen_text_len + __olpxscreen03_res_len);

    /* olpc xscreen : resource pic04*/
    __olpxscreen04_res_lma = __olpxscreen03_res_lma + __olpxscreen03_res_len;
    __olpxscreen04_res_vma = __olpxscreen_text_vma + __olpxscreen_text_len;
    .olpc_xscreen04_res (__olpxscreen04_res_vma) : AT (__olpxscreen04_res_lma)
    {
        . = ALIGN(32);
        */olpc_demo/resource/x_screen04_*_*.o(.rodata*)
        . = ALIGN(32);
    }
    __olpxscreen04_res_len = SIZEOF(.olpc_xscreen04_res);
    __olpapps_text_len    = MAX(__olpapps_text_len, __olpxscreen_text_len + __olpxscreen04_res_len);

    /* olpc xscreen : resource pic05*/
    __olpxscreen05_res_lma = __olpxscreen04_res_lma + __olpxscreen04_res_len;
    __olpxscreen05_res_vma = __olpxscreen_text_vma + __olpxscreen_text_len;
    .olpc_xscreen05_res (__olpxscreen05_res_vma) : AT (__olpxscreen05_res_lma)
    {
        . = ALIGN(32);
        */olpc_demo/resource/x_screen05_*_*.o(.rodata*)
        . = ALIGN(32);
    }
    __olpxscreen05_res_len = SIZEOF(.olpc_xscreen05_res);
    __olpapps_text_len    = MAX(__olpapps_text_len, __olpxscreen_text_len + __olpxscreen05_res_len);

    /* olpc xscreen : resource pic06*/
    __olpxscreen06_res_lma = __olpxscreen05_res_lma + __olpxscreen05_res_len;
    __olpxscreen06_res_vma = __olpxscreen_text_vma + __olpxscreen_text_len;
    .olpc_xscreen06_res (__olpxscreen06_res_vma) : AT (__olpxscreen06_res_lma)
    {
        . = ALIGN(32);
        */olpc_demo/resource/x_screen06_*_*.o(.rodata*)
        . = ALIGN(32);
    }
    __olpxscreen06_res_len = SIZEOF(.olpc_xscreen06_res);
    __olpapps_text_len    = MAX(__olpapps_text_len, __olpxscreen_text_len + __olpxscreen06_res_len);

    /* olpc xscreen : resource pic07*/
    __olpxscreen07_res_lma = __olpxscreen06_res_lma + __olpxscreen06_res_len;
    __olpxscreen07_res_vma = __olpxscreen_text_vma + __olpxscreen_text_len;
    .olpc_xscreen07_res (__olpxscreen07_res_vma) : AT (__olpxscreen07_res_lma)
    {
        . = ALIGN(32);
        */olpc_demo/resource/x_screen07_*_*.o(.rodata*)
        . = ALIGN(32);
    }
    __olpxscreen07_res_len = SIZEOF(.olpc_xscreen07_res);
    __olpapps_text_len    = MAX(__olpapps_text_len, __olpxscreen_text_len + __olpxscreen07_res_len);

    /* olpc xscreen : resource pic08*/
    __olpxscreen08_res_lma = __olpxscreen07_res_lma + __olpxscreen07_res_len;
    __olpxscreen08_res_vma = __olpxscreen_text_vma + __olpxscreen_text_len;
    .olpc_xscreen08_res (__olpxscreen08_res_vma) : AT (__olpxscreen08_res_lma)
    {
        . = ALIGN(32);
        */olpc_demo/resource/x_screen08_*_*.o(.rodata*)
        . = ALIGN(32);
    }
    __olpxscreen08_res_len = SIZEOF(.olpc_xscreen08_res);
    __olpapps_text_len    = MAX(__olpapps_text_len, __olpxscreen_text_len + __olpxscreen08_res_len);

    /* olpc xscreen : resource pic09*/
    __olpxscreen09_res_lma = __olpxscreen08_res_lma + __olpxscreen08_res_len;
    __olpxscreen09_res_vma = __olpxscreen_text_vma + __olpxscreen_text_len;
    .olpc_xscreen09_res (__olpxscreen09_res_vma) : AT (__olpxscreen09_res_lma)
    {
        . = ALIGN(32);
        */olpc_demo/resource/x_screen09_*_*.o(.rodata*)
        . = ALIGN(32);
    }
    __olpxscreen09_res_len = SIZEOF(.olpc_xscreen09_res);
    __olpapps_text_len    = MAX(__olpapps_text_len, __olpxscreen_text_len + __olpxscreen09_res_len);

    /* olpc xscreen : resource pic10*/
    __olpxscreen10_res_lma = __olpxscreen09_res_lma + __olpxscreen09_res_len;
    __olpxscreen10_res_vma = __olpxscreen_text_vma + __olpxscreen_text_len;
    .olpc_xscreen10_res (__olpxscreen10_res_vma) : AT (__olpxscreen10_res_lma)
    {
        . = ALIGN(32);
        */olpc_demo/resource/x_screen10_*_*.o(.rodata*)
        . = ALIGN(32);
    }
    __olpxscreen10_res_len = SIZEOF(.olpc_xscreen10_res);
    __olpapps_text_len    = MAX(__olpapps_text_len, __olpxscreen_text_len + __olpxscreen10_res_len);

    /* olpc xscreen : resource pic11*/
    __olpxscreen11_res_lma = __olpxscreen10_res_lma + __olpxscreen10_res_len;
    __olpxscreen11_res_vma = __olpxscreen_text_vma + __olpxscreen_text_len;
    .olpc_xscreen11_res (__olpxscreen11_res_vma) : AT (__olpxscreen11_res_lma)
    {
        . = ALIGN(32);
        */olpc_demo/resource/x_screen11_*_*.o(.rodata*)
        . = ALIGN(32);
    }
    __olpxscreen11_res_len = SIZEOF(.olpc_xscreen11_res);
    __olpapps_text_len    = MAX(__olpapps_text_len, __olpxscreen_text_len + __olpxscreen11_res_len);

    /* olpc xscreen : resource pic12*/
    __olpxscreen12_res_lma = __olpxscreen11_res_lma + __olpxscreen11_res_len;
    __olpxscreen12_res_vma = __olpxscreen_text_vma + __olpxscreen_text_len;
    .olpc_xscreen12_res (__olpxscreen12_res_vma) : AT (__olpxscreen12_res_lma)
    {
        . = ALIGN(32);
        */olpc_demo/resource/x_screen12_*_*.o(.rodata*)
        . = ALIGN(32);
    }
    __olpxscreen12_res_len = SIZEOF(.olpc_xscreen12_res);
    __olpapps_text_len    = MAX(__olpapps_text_len, __olpxscreen_text_len + __olpxscreen12_res_len);

    /* olpc xscreen : resource pic13*/
    __olpxscreen13_res_lma = __olpxscreen12_res_lma + __olpxscreen12_res_len;
    __olpxscreen13_res_vma = __olpxscreen_text_vma + __olpxscreen_text_len;
    .olpc_xscreen13_res (__olpxscreen13_res_vma) : AT (__olpxscreen13_res_lma)
    {
        . = ALIGN(32);
        */olpc_demo/resource/x_screen13_*_*.o(.rodata*)
        . = ALIGN(32);
    }
    __olpxscreen13_res_len = SIZEOF(.olpc_xscreen13_res);
    __olpapps_text_len    = MAX(__olpapps_text_len, __olpxscreen_text_len + __olpxscreen13_res_len);

    /* olpc xscreen : resource pic14*/
    __olpxscreen14_res_lma = __olpxscreen13_res_lma + __olpxscreen13_res_len;
    __olpxscreen14_res_vma = __olpxscreen_text_vma + __olpxscreen_text_len;
    .olpc_xscreen14_res (__olpxscreen14_res_vma) : AT (__olpxscreen14_res_lma)
    {
        . = ALIGN(32);
        */olpc_demo/resource/x_screen14_*_*.o(.rodata*)
        . = ALIGN(32);
    }
    __olpxscreen14_res_len = SIZEOF(.olpc_xscreen14_res);
    __olpapps_text_len    = MAX(__olpapps_text_len, __olpxscreen_text_len + __olpxscreen14_res_len);

    /* olpc xscreen : resource pic15*/
    __olpxscreen15_res_lma = __olpxscreen14_res_lma + __olpxscreen14_res_len;
    __olpxscreen15_res_vma = __olpxscreen_text_vma + __olpxscreen_text_len;
    .olpc_xscreen15_res (__olpxscreen15_res_vma) : AT (__olpxscreen15_res_lma)
    {
        . = ALIGN(32);
        */olpc_demo/resource/x_screen15_*_*.o(.rodata*)
        . = ALIGN(32);
    }
    __olpxscreen15_res_len = SIZEOF(.olpc_xscreen15_res);
    __olpapps_text_len    = MAX(__olpapps_text_len, __olpxscreen_text_len + __olpxscreen15_res_len);

    /* olpc xscreen : resource pic16*/
    __olpxscreen16_res_lma = __olpxscreen15_res_lma + __olpxscreen15_res_len;
    __olpxscreen16_res_vma = __olpxscreen_text_vma + __olpxscreen_text_len;
    .olpc_xscreen16_res (__olpxscreen16_res_vma) : AT (__olpxscreen16_res_lma)
    {
        . = ALIGN(32);
        */olpc_demo/resource/x_screen16_*_*.o(.rodata*)
        . = ALIGN(32);
    }
    __olpxscreen16_res_len = SIZEOF(.olpc_xscreen16_res);
    __olpapps_text_len    = MAX(__olpapps_text_len, __olpxscreen_text_len + __olpxscreen16_res_len);

    /* olpc xscreen : resource pic17*/
    __olpxscreen17_res_lma = __olpxscreen16_res_lma + __olpxscreen16_res_len;
    __olpxscreen17_res_vma = __olpxscreen_text_vma + __olpxscreen_text_len;
    .olpc_xscreen17_res (__olpxscreen17_res_vma) : AT (__olpxscreen17_res_lma)
    {
        . = ALIGN(32);
        */olpc_demo/resource/x_screen17_*_*.o(.rodata*)
        . = ALIGN(32);
    }
    __olpxscreen17_res_len = SIZEOF(.olpc_xscreen17_res);
    __olpapps_text_len    = MAX(__olpapps_text_len, __olpxscreen_text_len + __olpxscreen17_res_len);

    /* olpc xscreen : resource pic18*/
    __olpxscreen18_res_lma = __olpxscreen17_res_lma + __olpxscreen17_res_len;
    __olpxscreen18_res_vma = __olpxscreen_text_vma + __olpxscreen_text_len;
    .olpc_xscreen18_res (__olpxscreen18_res_vma) : AT (__olpxscreen18_res_lma)
    {
        . = ALIGN(32);
        */olpc_demo/resource/x_screen18_*_*.o(.rodata*)
        . = ALIGN(32);
    }
    __olpxscreen18_res_len = SIZEOF(.olpc_xscreen18_res);
    __olpapps_text_len    = MAX(__olpapps_text_len, __olpxscreen_text_len + __olpxscreen18_res_len);

    /* olpc xscreen : resource pic19*/
    __olpxscreen19_res_lma = __olpxscreen18_res_lma + __olpxscreen18_res_len;
    __olpxscreen19_res_vma = __olpxscreen_text_vma + __olpxscreen_text_len;
    .olpc_xscreen19_res (__olpxscreen19_res_vma) : AT (__olpxscreen19_res_lma)
    {
        . = ALIGN(32);
        */olpc_demo/resource/x_screen19_*_*.o(.rodata*)
        . = ALIGN(32);
    }
    __olpxscreen19_res_len = SIZEOF(.olpc_xscreen19_res);
    __olpapps_text_len    = MAX(__olpapps_text_len, __olpxscreen_text_len + __olpxscreen19_res_len);

    /*********************************************************************/
    /* remaining code */
    __text_ext_lma = __olpxscreen19_res_lma + __olpxscreen19_res_len;
    __text_ext_vma = __olpapps_text_vma + __olpapps_text_len;
    .text_ext (__text_ext_vma) : AT (__text_ext_lma)
    {
        . = ALIGN(32);
        *(.text.*)
        *(.rodata*)
        . = ALIGN(32);
    }
    __text_ext_len = SIZEOF(.text_ext);

    __arm_extab_lma = __text_ext_lma + __text_ext_len;
    __arm_extab_vma = .; /*__text_ext_vma + __text_ext_len;*/
    .ARM.extab : /* AT (__arm_extab_lma) */
    {
        *(.ARM.extab* .gnu.linkonce.armextab.*)
    }
    __arm_extab_len = SIZEOF(.ARM.extab);

    __arm_exidx_lma = __arm_extab_lma + __arm_extab_len;
    __arm_exidx_vma = .; /*__arm_extab_vma + __arm_extab_len;*/
    __exidx_start = .;
    .ARM.exidx : /* AT (__arm_exidx_lma) */
    {
        *(.ARM.exidx* .gnu.linkonce.armexidx.*)
    }
    __exidx_end = .;
    __arm_exidx_len = SIZEOF(.ARM.exidx);

/*
*************************************************************************
*
* unknow region...
*
*************************************************************************
*/
    /* To copy multiple ROM to RAM sections,
     * uncomment .copy.table section and,
     * define __STARTUP_COPY_MULTIPLE in startup_ARMCMx.S */
    /*
    .copy.table :
    {
        . = ALIGN(4);
        __copy_table_start__ = .;
        LONG (__etext)
        LONG (__data_start__)
        LONG (__data_end__ - __data_start__)
        LONG (__etext2)
        LONG (__data2_start__)
        LONG (__data2_end__ - __data2_start__)
        __copy_table_end__ = .;
    }
    */

    /* To clear multiple BSS sections,
     * uncomment .zero.table section and,
     * define __STARTUP_CLEAR_BSS_MULTIPLE in startup_ARMCMx.S */
    /*
    .zero.table :
    {
        . = ALIGN(4);
        __zero_table_start__ = .;
        LONG (__bss_start__)
        LONG (__bss_end__ - __bss_start__)
        LONG (__bss2_start__)
        LONG (__bss2_end__ - __bss2_start__)
        __zero_table_end__ = .;
    }
    */

/*
*************************************************************************
*
* data region
*
*************************************************************************
*/
    /* must be cacheline align */
    __etext = ALIGN(32);
    _etext = .;
    _etext_ext = .;

    __data_lma = __arm_exidx_lma + __arm_exidx_len;
    __data_vma = _data_start_off + __etext;
    .data (__data_vma) : AT (__data_lma)
    {
        __data_start__ = .;
        . = ALIGN(32);
        *(vtable)
        *(.data)
        . = ALIGN(4);
        /* preinit data */
        PROVIDE_HIDDEN (__preinit_array_start = .);
        KEEP(*(.preinit_array))
        PROVIDE_HIDDEN (__preinit_array_end = .);

        . = ALIGN(4);
        /* init data */
        PROVIDE_HIDDEN (__init_array_start = .);
        KEEP(*(SORT(.init_array.*)))
        KEEP(*(.init_array))
        PROVIDE_HIDDEN (__init_array_end = .);


        . = ALIGN(4);
        /* finit data */
        PROVIDE_HIDDEN (__fini_array_start = .);
        KEEP(*(SORT(.fini_array.*)))
        KEEP(*(.fini_array))
        PROVIDE_HIDDEN (__fini_array_end = .);

        KEEP(*(.jcr*))
        . = . + 4;
        . = ALIGN(32);
        /* All data end */
        __data_end__ = .;
    }
    __data_len = SIZEOF(.data);

    /*********************************************************************/
    /* olpc applications data region */
    __olpapps_data_vma = .;

    /* olpc clock */
    __olpclock_data_lma = __data_lma + __data_len;
    __olpclock_data_vma = __olpapps_data_vma;
    .olpc_clock_data (__olpclock_data_vma) : AT (__olpclock_data_lma)
    {
        . = ALIGN(32);
        */olpc_demo/olpc_clock.o(.data*)
        */olpc_demo/resource/clock_*_*_*.o(.data*)
        */olpc_demo/resource/fingerprint*_*_*.o(.data*)
        */olpc_demo/resource/home_*_*_*.o(.data*)
        */olpc_demo/resource/lock_*_*_*.o(.data*)
        */olpc_demo/resource/msg_*_*_*.o(.data*)
        . = ALIGN(32);
    }
    __olpclock_data_len = SIZEOF(.olpc_clock_data);
    __olpapps_data_len  = MAX(0, __olpclock_data_len);

    /* olpc ebook */
    __olpebook_data_lma = __olpclock_data_lma + __olpclock_data_len;
    __olpebook_data_vma = __olpapps_data_vma;
    .olpc_ebook_data (__olpebook_data_vma) : AT (__olpebook_data_lma)
    {
        . = ALIGN(32);
        */olpc_demo/olpc_ebook.o(.data*)
        */olpc_demo/resource/ebook_*_*_*.o(.data*)
        . = ALIGN(32);
    }
    __olpebook_data_len = SIZEOF(.olpc_ebook_data);
    __olpapps_data_len  = MAX(__olpapps_data_len, __olpebook_data_len);

    /* olpc block */
    __olpblock_data_lma = __olpebook_data_lma + __olpebook_data_len;
    __olpblock_data_vma = __olpapps_data_vma;
    .olpc_block_data (__olpblock_data_vma) : AT (__olpblock_data_lma)
    {
        . = ALIGN(32);
        */olpc_demo/olpc_block.o(.data*)
        */olpc_demo/resource/block_*_*_*.o(.data*)
        . = ALIGN(32);
    }
    __olpblock_data_len = SIZEOF(.olpc_block_data);
    __olpapps_data_len  = MAX(__olpapps_data_len, __olpblock_data_len);

    /* olpc snake */
    __olpsnake_data_lma = __olpblock_data_lma + __olpblock_data_len;
    __olpsnake_data_vma = __olpapps_data_vma;
    .olpc_snake_data (__olpsnake_data_vma) : AT (__olpsnake_data_lma)
    {
        . = ALIGN(32);
        */olpc_demo/olpc_snake.o(.data*)
        */olpc_demo/resource/snake_*_*_*.o(.data*)
        . = ALIGN(32);
    }
    __olpsnake_data_len = SIZEOF(.olpc_snake_data);
    __olpapps_data_len  = MAX(__olpapps_data_len, __olpsnake_data_len);

    /* olpc note */
    __olpnote_data_lma = __olpsnake_data_lma + __olpsnake_data_len;
    __olpnote_data_vma = __olpapps_data_vma;
    .olpc_note_data (__olpnote_data_vma) : AT (__olpnote_data_lma)
    {
        . = ALIGN(32);
        */olpc_demo/olpc_note.o(.data*)
        */olpc_demo/resource/note_*_*_*.o(.data*)
        . = ALIGN(32);
    }
    __olpnote_data_len = SIZEOF(.olpc_note_data);
    __olpapps_data_len  = MAX(__olpapps_data_len, __olpnote_data_len);


    /* olpc xscreen */
    __olpxscreen_data_lma = __olpnote_data_lma + __olpnote_data_len;
    __olpxscreen_data_vma = __olpapps_data_vma;
    .olpc_xscreen_data (__olpxscreen_data_vma) : AT (__olpxscreen_data_lma)
    {
        . = ALIGN(32);
        */olpc_demo/olpc_xscreen.o(.data*)
        */olpc_demo/resource/x_screen*_*_*.o(.data*)
        . = ALIGN(32);
    }
    __olpxscreen_data_len = SIZEOF(.olpc_xscreen_data);
    __olpapps_data_len    = MAX(__olpapps_data_len, __olpxscreen_data_len);

    /*********************************************************************/
    /* remaining data */
    __data_ext_lma = __olpxscreen_data_lma + __olpxscreen_data_len;
    __data_ext_vma = __olpapps_data_vma + __olpapps_data_len;
    .data_ext (__data_ext_vma) : AT (__data_ext_lma)
    {
        . = ALIGN(32);
        *(.data*)
        . = ALIGN(32);
    }
    __data_ext_len = SIZEOF(.data_ext);

/*
*************************************************************************
*
* bss region
*
*************************************************************************
*/
    /*********************************************************************/
    /* olpc applications bss region */
    __olpapps_bss_vma = .;

    /* olpc clock */
    . = __olpapps_bss_vma;
    __olpclock_bss_vma = .;
    .olpc_clock_bss (NOLOAD):
    {
        . = ALIGN(32);
        */olpc_demo/olpc_clock.o(.bss*)
        */olpc_demo/resource/clock_*_*_*.o(.bss*)
        */olpc_demo/resource/fingerprint*_*_*.o(.bss*)
        */olpc_demo/resource/home_*_*_*.o(.bss*)
        */olpc_demo/resource/lock_*_*_*.o(.bss*)
        */olpc_demo/resource/msg_*_*_*.o(.bss*)
        . = ALIGN(32);
    }
    __olpclock_bss_len = SIZEOF(.olpc_clock_bss);
    __olpapps_bss_len  = MAX(0, __olpclock_bss_len);

    /* olpc ebook */
    . = __olpapps_bss_vma;
    __olpebook_bss_vma = .;
    .olpc_ebook_bss (NOLOAD):
    {
        . = ALIGN(32);
        */olpc_demo/olpc_ebook.o(.bss*)
        */olpc_demo/resource/ebook_*_*_*.o(.bss*)
        . = ALIGN(32);
    }
    __olpebook_bss_len = SIZEOF(.olpc_ebook_bss);
    __olpapps_bss_len  = MAX(__olpapps_bss_len, __olpebook_bss_len);

    /* olpc block */
    . = __olpapps_bss_vma;
    __olpblock_bss_vma = .;
    .olpc_block_bss (NOLOAD):
    {
        . = ALIGN(32);
        */olpc_demo/olpc_block.o(.bss*)
        */olpc_demo/resource/block_*_*_*.o(.bss*)
        . = ALIGN(32);
    }
    __olpblock_bss_len = SIZEOF(.olpc_block_bss);
    __olpapps_bss_len  = MAX(__olpapps_bss_len, __olpblock_bss_len);

    /* olpc snake */
    . = __olpapps_bss_vma;
    __olpsnake_bss_vma = .;
    .olpc_snake_bss (NOLOAD):
    {
        . = ALIGN(32);
        */olpc_demo/olpc_snake.o(.bss*)
        */olpc_demo/resource/snake_*_*_*.o(.bss*)
        . = ALIGN(32);
    }
    __olpsnake_bss_len = SIZEOF(.olpc_snake_bss);
    __olpapps_bss_len  = MAX(__olpapps_bss_len, __olpsnake_bss_len);

    /* olpc note */
    . = __olpapps_bss_vma;
    __olpnote_bss_vma = .;
    .olpc_note_bss (NOLOAD):
    {
        . = ALIGN(32);
        */olpc_demo/olpc_note.o(.bss*)
        */olpc_demo/resource/note_*_*_*.o(.bss*)
        . = ALIGN(32);
    }
    __olpnote_bss_len = SIZEOF(.olpc_note_bss);
    __olpapps_bss_len  = MAX(__olpapps_bss_len, __olpnote_bss_len);

    /* olpc xscreen */
    . = __olpapps_bss_vma;
    __olpxscreen_bss_vma = .;
    .olpc_xscreen_bss (NOLOAD):
    {
        . = ALIGN(32);
        */olpc_demo/olpc_xscreen.o(.bss*)
        */olpc_demo/resource/x_screen*_*_*.o(.bss*)
        . = ALIGN(32);
    }
    __olpxscreen_bss_len = SIZEOF(.olpc_xscreen_bss);
    __olpapps_bss_len    = MAX(__olpapps_bss_len, __olpxscreen_bss_len);

    /*********************************************************************/
    /* bss & remain region */
    . = __olpapps_bss_vma + __olpapps_bss_len;
    __bss_vma = .;
    .bss (NOLOAD):
    {
        . = ALIGN(32);
        __bss_start__ = .;
        *(.bss*)
        *(COMMON)
        . = ALIGN(32);
        __bss_end__ = .;
    }
    __bss_len = SIZEOF(.bss);

/*
*************************************************************************
*
* heap & stack region
*
*************************************************************************
*/
    /* region for ramfs, enable if you need */
    /*.ramfs :
    {
        . = ALIGN(4);
        __ramfs_start__ = .;
        . = . + _ram_fs_size;
        __ramfs_end__ = .;
    }*/

    /* region for large memory allocate */
#ifdef RT_LARGE_HEAP_SIZE
    .large (COPY):
    {
        . = ALIGN(32);
        __large_start__ = .;
        . = . + RT_LARGE_HEAP_SIZE;
        . = ALIGN(32);
        __large_end__ = .;
    }
#endif

    /* address for stack */
    _stack_start_addr = .;

    /* region for dtcm memory allocate */
    . = _dtcm_start_addr;
    .dtcm (COPY):
    {
        . = ALIGN(32);
        __dtcm_start__ = .;
        . = . + _dtcm_heap_size;
        . = ALIGN(32);
        __dtcm_end__ = .;
    }
    _dtcm_end_addr = .;

    . = _stack_start_addr;
    .stack (COPY):
    {
        . = ALIGN(32);
        _sstack = .;
        *(.stack*)
        . = ALIGN(32);
        _estack = .;
    }

    __heap_start__ = .;

    /* Limt heap size >= 64KB */
    ASSERT(__heap_start__ < (0x20100000 - 0x10000),  "error: memory overflow (heap size < 64KB)!!!")
}
