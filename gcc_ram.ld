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

ENTRY(Reset_Handler)
_ram_fs_size = 0x10000;
_large_heap_size = 0x80000;
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

    /*********************************************************************/
    /* remaining code */
    __text_ext_lma = __olpnote_text_lma + __olpnote_text_len;
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

    /*********************************************************************/
    /* remaining data */
    __data_ext_lma = __olpnote_data_lma + __olpnote_data_len;
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
    .large (COPY):
    {
        . = ALIGN(32);
        __large_start__ = .;
        . = . + _large_heap_size;
        . = ALIGN(32);
        __large_end__ = .;
    }
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
