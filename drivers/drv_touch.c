/**************************************************************
 * Copyright (c)  2008- 2030  Oppo Mobile communication Corp.ltd
 * VENDOR_EDIT
 * File             : drv_touch.c
 * Description      : Source file for olpc touch driver
 * Version          : 1.0
 * Date             : 2019-05-13
 * Author           : zhoufeng@swdp
 * ---------------- Revision History: --------------------------
 *   <version>        <date>                  < author >                                                        <desc>
 * Revision 1.1, 2019-05-13, zhoufeng@swdp, initial olpc touch driver
 ****************************************************************/
#include <rtthread.h>
#include <soc.h>
#include <rtdevice.h>
#include <hal_base.h>

#ifdef RT_USING_TOUCH

#include "drv_touch.h"
#include "drv_touch_s3706.h"

touch_driver_t *tp_driver = RT_NULL;

static void __writel(volatile uint32_t addr, uint32_t val)
{
    *((uint32_t *)addr) = val;
}

void touch_thread_entry(void *parameter)
{
    rt_err_t res = RT_EOK;
    rt_device_t touch_device = RT_NULL;
    rt_sem_t touch_sem;
    uint32_t cur_event = 0;

    rt_thread_delay(100); // wait for synaptics touch device to startup!

    touch_device = rt_device_find(tp_driver->name);
    if (!touch_device)
    {
        tp_dbg("find touch device failed!");
        return RT_ERROR;
    }

    res = rt_device_open(touch_device, RT_DEVICE_FLAG_RDWR);
    if (res != RT_EOK)
    {
        tp_dbg("open touch device failed!\n");
        return res;
    }

    tp_dbg("[TP] init end.\n");

    touch_sem = ((touch_driver_t *)(touch_device->user_data))->isr_sem;

    while (1)
    {
        if (rt_sem_take(touch_sem, RT_WAITING_FOREVER) != RT_EOK)
        {
            continue;
        }

        tp_dbg("touch thread take sem.\n");

        cur_event = tp_driver->ops->trigger_reason(0, 0);

        if (CHK_BIT(cur_event, IRQ_TOUCH) || CHK_BIT(cur_event, IRQ_BTN_KEY) || CHK_BIT(cur_event, IRQ_FW_HEALTH) || \
                CHK_BIT(cur_event, IRQ_FACE_STATE) || CHK_BIT(cur_event, IRQ_FINGERPRINT))
        {
            if (CHK_BIT(cur_event, IRQ_BTN_KEY))
            {
                // TODO tp_btnkey_handle(ts);
            }
            if (CHK_BIT(cur_event, IRQ_TOUCH))
            {
                tp_driver->ops->touch_handle();
            }
            if (CHK_BIT(cur_event, IRQ_FW_HEALTH) /*&& (!ts->is_suspended)*/)
            {
                // TODO health_monitor_handle(ts);
            }
            if (CHK_BIT(cur_event, IRQ_FACE_STATE) /*&& ts->fd_enable*/)
            {
                // TODO tp_face_detect_handle(ts);
            }
            if (CHK_BIT(cur_event, IRQ_FINGERPRINT) /*&& ts->fp_enable*/)
            {
                // TODO tp_fingerprint_handle(ts);
            }
        }
        else if (CHK_BIT(cur_event, IRQ_GESTURE))
        {
            // TODO tp_gesture_handle(ts);
        }
        else if (CHK_BIT(cur_event, IRQ_EXCEPTION))
        {
            // TODO tp_exception_handle(ts);
        }
        else if (CHK_BIT(cur_event, IRQ_FW_CONFIG))
        {
            // TODO tp_config_handle(ts);
        }
        else if (CHK_BIT(cur_event, IRQ_FW_AUTO_RESET))
        {
            // TODO tp_fw_auto_reset_handle(ts);
        }
        else
        {
            tp_dbg("unknown irq trigger reason.\n");
        }

        HAL_NVIC_EnableIRQ(TP_IRQn);
    }
}

rt_thread_t touch_thread;
int rt_hw_touch_init(void)
{
    static struct rt_device touch;

    tp_driver = &s3706_driver;

    /* init device structure */
    touch.type = RT_Device_Class_Unknown;
    touch.init = tp_driver->ops->init;
    touch.read = tp_driver->ops->read;
    touch.control = tp_driver->ops->control;
    touch.user_data = (void *)tp_driver;

    /* register touch device to RT-Thread */
    rt_device_register(&touch, tp_driver->name, RT_DEVICE_FLAG_RDWR);

    return RT_EOK;
}
INIT_APP_EXPORT(rt_hw_touch_init);

#endif /* RT_USING_TOUCH */
