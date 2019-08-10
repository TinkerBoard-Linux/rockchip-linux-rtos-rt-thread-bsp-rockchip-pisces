/**************************************************************
 * Copyright (c)  2008- 2030  Oppo Mobile communication Corp.ltd
 * VENDOR_EDIT
 * File             : touch_test.c
 * Description      : Source file for olpc touch driver
 * Version          : 1.0
 * Date             : 2019-05-13
 * Author           : zhoufeng@swdp
 * ---------------- Revision History: --------------------------
 *   <version>    <date>   < author >    <desc>
 * Revision 1.1, 2019-05-13, zhoufeng@swdp, initial olpc touch driver
 ****************************************************************/
#include <rtdevice.h>
#include <rtthread.h>

#ifdef RT_USING_COMMON_TEST_TOUCH

#include <stdbool.h>
#include "hal_base.h"

#include <drv_touch.h>

static rt_device_t g_touch_dev = RT_NULL;

void touch_show_usage()
{
    /* touch test */
    rt_kprintf("touch test.\n");
}

void touch_test(int argc, char **argv)
{
    int i;

    if (argc > 1)
        goto out;

    /* register touch device for lvgl */
    g_touch_dev = rt_device_find("s3706");
    RT_ASSERT(g_touch_dev != RT_NULL);

    rt_device_control(g_touch_dev, TOUCH_CMD_EXSEM, RT_NULL);

#if 0
    rt_device_control(g_touch_dev, TOUCH_CMD_EXSEM, &sem_render);

    lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);  /*Basic initialization*/
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read = olpc_input_read;
    lv_indev_drv_register(&indev_drv);  /*Register the driver in LittlevGL*/
#endif

    rt_thread_t touch_thread; /* create touch thread */
    touch_thread = rt_thread_create("touch",
                                    touch_thread_entry, RT_NULL,
                                    1024, 10, 20);
    if (touch_thread != RT_NULL)
        rt_thread_startup(touch_thread);

    return;
out:
    touch_show_usage();
    return;
}

#ifdef RT_USING_FINSH
#include <finsh.h>
MSH_CMD_EXPORT(touch_test, touch test cmd);
#endif

#endif
