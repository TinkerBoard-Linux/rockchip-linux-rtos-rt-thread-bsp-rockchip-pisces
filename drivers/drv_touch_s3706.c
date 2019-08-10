/**************************************************************
 * Copyright (c)  2008- 2030  Oppo Mobile communication Corp.ltd
 * VENDOR_EDIT
 * File             : drv_touch_s3706.c
 * Description      : Source file for olpc touch driver
 * Version          : 1.0
 * Date             : 2019-05-14
 * Author           : zhoufeng@swdp
 * ---------------- Revision History: --------------------------
 *   <version>        <date>                  < author >                                                        <desc>
 * Revision 1.1, 2019-05-14, zhoufeng@swdp, initial olpc touch driver for s3706
 ****************************************************************/
#include <rtthread.h>
#include <soc.h>
#include <hal_base.h>
#include <rthw.h>

#ifdef RT_USING_TOUCH

#include "drv_touch.h"
#include "drv_touch_s3706.h"

static struct rt_i2c_bus_device *i2c_bus;
static s3706_reg_t s3706_reg;

static void print_s3706_reg()
{
    tp_dbg("s3706_reg.F12_2D_QUERY_BASE = 0x%x.\n", s3706_reg.F12_2D_QUERY_BASE);
    tp_dbg("s3706_reg.F12_2D_CMD_BASE = 0x%x.\n", s3706_reg.F12_2D_CMD_BASE);
    tp_dbg("s3706_reg.F12_2D_CTRL_BASE = 0x%x.\n", s3706_reg.F12_2D_CTRL_BASE);
    tp_dbg("s3706_reg.F12_2D_DATA_BASE = 0x%x.\n", s3706_reg.F12_2D_DATA_BASE);

    tp_dbg("s3706_reg.F01_RMI_QUERY_BASE = 0x%x.\n", s3706_reg.F01_RMI_QUERY_BASE);
    tp_dbg("s3706_reg.F01_RMI_CMD_BASE = 0x%x.\n", s3706_reg.F01_RMI_CMD_BASE);
    tp_dbg("s3706_reg.F01_RMI_CTRL_BASE = 0x%x.\n", s3706_reg.F01_RMI_CTRL_BASE);
    tp_dbg("s3706_reg.F01_RMI_DATA_BASE = 0x%x.\n", s3706_reg.F01_RMI_DATA_BASE);

    tp_dbg("s3706_reg.F34_FLASH_QUERY_BASE = 0x%x.\n", s3706_reg.F34_FLASH_QUERY_BASE);
    tp_dbg("s3706_reg.F34_FLASH_CMD_BASE = 0x%x.\n", s3706_reg.F34_FLASH_CMD_BASE);
    tp_dbg("s3706_reg.F34_FLASH_CTRL_BASE = 0x%x.\n", s3706_reg.F34_FLASH_CTRL_BASE);
    tp_dbg("s3706_reg.F34_FLASH_DATA_BASE = 0x%x.\n", s3706_reg.F34_FLASH_DATA_BASE);
}

static void s3706_int_handler(void)
{
    //HAL_NVIC_DisableIRQ(TP_IRQn);
    rt_interrupt_enter();

    HAL_NVIC_DisableIRQ(TP_IRQn);

    rt_sem_release(s3706_driver.isr_sem);

    rt_interrupt_leave();
    //HAL_NVIC_EnableIRQ(TP_IRQn);
}

rt_err_t s3706_touch_read(rt_uint16_t slaveaddr, void *cmd_buf, size_t cmd_len, void *data_buf, size_t data_len)
{
    struct rt_i2c_msg msgs[2];

    msgs[0].addr  = slaveaddr;
    msgs[0].flags = RT_I2C_WR;
    msgs[0].buf   = cmd_buf;
    msgs[0].len   = cmd_len;

    msgs[1].addr  = slaveaddr;
    msgs[1].flags = RT_I2C_RD;
    msgs[1].buf   = data_buf;
    msgs[1].len   = data_len;

    if (rt_i2c_transfer(i2c_bus, msgs, 2) == 2)
        return RT_EOK;
    else
        return RT_ERROR;
}

rt_err_t s3706_touch_read_word(uint16_t addr, int *value)
{
    rt_err_t retval = 0;
    uint16_t regaddr = addr;
    uint8_t buf[2] = {0};

    retval = s3706_touch_read(S3706_ADDR, &regaddr, 1, buf, 2);
    if (retval != RT_ERROR)
    {
        *value = buf[1] << 8 | buf[0];
        return RT_EOK;
    }
    else
    {
        *value = 0;
        return RT_ERROR;
    }
}

rt_err_t s3706_touch_write(uint16_t slaveaddr, uint16_t regaddr, size_t cmd_len, uint32_t data_buf_arg, size_t data_len)
{
    char *data_buf = NULL;
    uint32_t data_buf_tmp;
    struct rt_i2c_msg msgs[1];
    int i, ret = 0;

    data_buf = (char *)rt_calloc(1, data_len + cmd_len);
    if (!data_buf)
    {
        tp_dbg("spi write alloc buf size %d fail\n", data_len);
        return;
    }

    for (i = 0; i < cmd_len; i++)
    {
        data_buf[i] = (regaddr >> (8 * i)) & 0xff;
        tp_dbg("send[%x]: 0x%x\n", i, data_buf[i]);
    }

    for (i = cmd_len; i < data_len + cmd_len; i++)
    {
        data_buf_tmp = (uint8_t)(data_buf_arg & 0x000000ff);
        data_buf[i] = data_buf_tmp;
        data_buf_arg = data_buf_arg >> 8;
    }

    msgs[0].addr  = slaveaddr;
    msgs[0].flags = RT_I2C_WR;
    msgs[0].buf   = data_buf;
    msgs[0].len   = data_len;

    ret = rt_i2c_transfer(i2c_bus, msgs, 1);

    rt_free(data_buf);

    if (ret == 1)
        return RT_EOK;
    else
        return RT_ERROR;
}

uint32_t s3706_trigger_reason(int32_t gesture_enable, int32_t is_suspended)
{
    rt_err_t ret_code = 0;
    int32_t ret_value = 0;
    uint8_t device_status = 0, interrupt_status = 0;
    uint32_t result_event = 0;

    ret_code = s3706_touch_write(S3706_ADDR, 0xff, 1, 0, 1);  /* page 0*/
    if (ret_code != RT_EOK)
    {
        tp_dbg("%s, s3706_touch_write error, ret_code = %d\n", __func__, ret_code);
        return IRQ_EXCEPTION;
    }

    ret_code = s3706_touch_read_word(s3706_reg.F01_RMI_DATA_BASE, &ret_value);
    if (ret_code != RT_EOK)
    {
        tp_dbg("%s, s3706_touch_write error, ret_code = %d\n", __func__, ret_code);
        return IRQ_EXCEPTION;
    }
    device_status = ret_value & 0xff;
    interrupt_status = (ret_value & 0x7f00) >> 8;
    tp_dbg("%s, interrupt_status = 0x%x, device_status = 0x%x\n", __func__, interrupt_status, device_status);

    if (device_status && device_status != 0x81)
    {
        tp_dbg("%s, interrupt_status = 0x%x, device_status = 0x%x\n", __func__, interrupt_status, device_status);
        return IRQ_EXCEPTION;
    }

    if (interrupt_status & 0x04)
    {
        if (gesture_enable && is_suspended)
        {
            return IRQ_GESTURE;
        }
        else if (is_suspended)
        {
            return IRQ_IGNORE;
        }
        SET_BIT(result_event, IRQ_TOUCH);
        SET_BIT(result_event, IRQ_FINGERPRINT);
    }
    if (interrupt_status & 0x10)
    {
        SET_BIT(result_event, IRQ_BTN_KEY);
    }
    if (interrupt_status & 0x20)
    {
        SET_BIT(result_event, IRQ_FACE_STATE);
        SET_BIT(result_event, IRQ_FW_HEALTH);
    }

    return result_event;
}

static char point_buf[8 * MAX_FINGER_NUM];
int32_t s3706_get_touch_points(struct point_info *points, int32_t max_num)
{
    rt_err_t ret_code = 0;
    int32_t i, obj_attention;
    uint8_t fingers_to_process = max_num;
    char *buf;
    register rt_base_t temp;

    buf = point_buf;
    memset(buf, 0, sizeof(buf));

    ret_code = s3706_touch_read_word(s3706_reg.F12_2D_DATA15, &obj_attention);
    if (ret_code != RT_EOK)
    {
        rt_kprintf("%s, s3706_touch_read_word error, ret_code = %d\n", __func__, ret_code);
        return -RT_ERROR;
    }
    tp_dbg("%s, obj_attention = 0x%x\n", __func__, obj_attention);

    for (i = 9;  ; i--)
    {
        if ((obj_attention & 0x03FF) >> i  || i == 0)
            break;
        else
            fingers_to_process--;
    }
    tp_dbg("%s, fingers to process = 0x%x\n", __func__, fingers_to_process);

    ret_code = s3706_touch_read(S3706_ADDR, &s3706_reg.F12_2D_DATA_BASE, 1, buf, 8 * fingers_to_process);
    if (ret_code == RT_ERROR)
    {
        rt_kprintf("touch i2c read block failed\n");
        return -RT_ERROR;
    }
    tp_dbg("buf[0] = 0x%x, buf[1]= 0x%x, buf[2] = 0x%x.\n", buf[0], buf[1], buf[2]);
    rt_mutex_take(s3706_driver.read_mutex, RT_WAITING_FOREVER);
    for (i = 0; i < fingers_to_process; i++)
    {
        points[i].x = ((buf[i * 8 + 2] & 0x0f) << 8) | (buf[i * 8 + 1] & 0xff);
        points[i].y = ((buf[i * 8 + 4] & 0x0f) << 8) | (buf[i * 8 + 3] & 0xff);
        points[i].z = buf[i * 8 + 5];
        points[i].touch_major = max(buf[i * 8 + 6], buf[i * 8 + 7]);
        points[i].width_major = ((buf[i * 8 + 6] & 0x0f) + (buf[i * 8 + 7] & 0x0f)) / 2;
        points[i].status = buf[i * 8];
    }
    rt_mutex_release(s3706_driver.read_mutex);

    return obj_attention;
}

static struct point_info points[MAX_FINGER_NUM];
void s3706_touch_handle()
{
    int obj_attention = 0;

    obj_attention = s3706_get_touch_points(points, MAX_FINGER_NUM);
    if (obj_attention == -EINVAL)
    {
        tp_dbg("Invalid points, ignore..\n");
        return;
    }

    /* external caller, ie lvgl, must ensure initialize ex_sem before touch init*/
    if (s3706_driver.ex_sem != RT_NULL)
    {
        rt_sem_release(s3706_driver.ex_sem);
    }

    tp_dbg("%s, points: x = 0x%x, y = 0x%x, z = 0x%x.\n", __func__, points[0].x, points[0].y, points[0].z);
}

/*
* s3706 initialization
*/
rt_err_t s3706_touch_device_init(rt_device_t dev)
{
    uint32_t current_firmware = 0;

    uint16_t regaddr = 0;
    char *data_buf = NULL;
    uint32_t data_len = 0;

    i2c_bus = (struct rt_i2c_bus_device *)rt_i2c_bus_device_find("i2c0");
    if (i2c_bus == RT_NULL)
    {
        tp_dbg("Did not find device: i2c bus ...\n");
        return RT_ERROR;
    }

    /* page 0 */
    s3706_touch_write(S3706_ADDR, 0xff, 1, 0, 1);

    /* read register info */
    data_len = 4;
    data_buf = (char *)rt_calloc(1, data_len);

    /* read register info */
    regaddr = 0xdd;
    s3706_touch_read(S3706_ADDR, &regaddr, 1, data_buf, data_len);
    s3706_reg.F12_2D_QUERY_BASE = data_buf[0];
    s3706_reg.F12_2D_CMD_BASE = data_buf[1];
    s3706_reg.F12_2D_CTRL_BASE = data_buf[2];
    s3706_reg.F12_2D_DATA_BASE = data_buf[3];

    regaddr = 0xe3;
    s3706_touch_read(S3706_ADDR, &regaddr, 1, data_buf, data_len);
    s3706_reg.F01_RMI_QUERY_BASE = data_buf[0];
    s3706_reg.F01_RMI_CMD_BASE = data_buf[1];
    s3706_reg.F01_RMI_CTRL_BASE = data_buf[2];
    s3706_reg.F01_RMI_DATA_BASE = data_buf[3];

    regaddr = 0xe9;
    s3706_touch_read(S3706_ADDR, &regaddr, 1, data_buf, data_len);
    s3706_reg.F34_FLASH_QUERY_BASE = data_buf[0];
    s3706_reg.F34_FLASH_CMD_BASE = data_buf[1];
    s3706_reg.F34_FLASH_CTRL_BASE =  data_buf[2];
    s3706_reg.F34_FLASH_DATA_BASE = data_buf[3];

    s3706_reg.F01_RMI_QUERY11 = s3706_reg.F01_RMI_QUERY_BASE + 0x0b;    // product id
    s3706_reg.F01_RMI_CTRL00 = s3706_reg.F01_RMI_CTRL_BASE;
    s3706_reg.F01_RMI_CTRL01 = s3706_reg.F01_RMI_CTRL_BASE + 1;
    s3706_reg.F01_RMI_CTRL02 = s3706_reg.F01_RMI_CTRL_BASE + 2;
    s3706_reg.F01_RMI_CMD00  = s3706_reg.F01_RMI_CMD_BASE;
    s3706_reg.F01_RMI_DATA01 = s3706_reg.F01_RMI_DATA_BASE + 1;

    s3706_reg.F12_2D_CTRL08 = s3706_reg.F12_2D_CTRL_BASE;               // max XY Coordinate
    s3706_reg.F12_2D_CTRL23 = s3706_reg.F12_2D_CTRL_BASE + 9;           //glove enable
    s3706_reg.F12_2D_CTRL32 = s3706_reg.F12_2D_CTRL_BASE + 0x0f;        //moisture enable
    s3706_reg.F12_2D_DATA04 = s3706_reg.F12_2D_DATA_BASE + 1;           //gesture type
    s3706_reg.F12_2D_DATA15 = s3706_reg.F12_2D_DATA_BASE + 3;           //object attention
    s3706_reg.F12_2D_CMD00  = s3706_reg.F12_2D_CMD_BASE;
    s3706_reg.F12_2D_CTRL20 = s3706_reg.F12_2D_CTRL_BASE + 0x07;        //motion suppression
    s3706_reg.F12_2D_CTRL27 = s3706_reg.F12_2D_CTRL_BASE + 0x0b;        // wakeup Gesture enable

    print_s3706_reg();

    s3706_touch_write(S3706_ADDR, 0xff, 1, 0x4, 1); /* page 4*/

    /* read firmware info */
    regaddr = s3706_reg.F34_FLASH_CTRL_BASE;
    tp_dbg("F34_FLASH_CTRL_BASE = 0x%x.\n", regaddr);
    s3706_touch_read(S3706_ADDR, &regaddr, 1, data_buf, 4);
    current_firmware = (data_buf[0] << 24) | (data_buf[1] << 16) | (data_buf[2] << 8) | data_buf[3];
    tp_dbg("S3706 init CURRENT_FIRMWARE_ID = 0x%x\n", current_firmware);

    s3706_driver.isr_sem = rt_sem_create("s3706_isr_sem", 0, RT_IPC_FLAG_FIFO);
    RT_ASSERT(s3706_driver.isr_sem != RT_NULL);
    s3706_driver.read_mutex = rt_mutex_create("s3706_read_mutex", RT_IPC_FLAG_FIFO);
    RT_ASSERT(s3706_driver.read_mutex != RT_NULL);

    //HAL_NVIC_ConfigExtIRQ(TP_IRQn, (NVIC_IRQHandler)s3706_int_handler, NVIC_PERIPH_PRIO_DEFAULT);
    rt_hw_interrupt_install(TP_IRQn,
                            (NVIC_IRQHandler)s3706_int_handler,
                            RT_NULL,
                            RT_NULL);
    rt_hw_interrupt_umask(TP_IRQn);

    return RT_EOK;
}

rt_size_t s3706_touch_device_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size)
{
    rt_mutex_take(s3706_driver.read_mutex, RT_WAITING_FOREVER);
    rt_memcpy(buffer, points, sizeof(struct point_info));
    tp_dbg("touch device is read by other task.\n");
    rt_mutex_release(s3706_driver.read_mutex);

    return sizeof(struct point_info);
}

rt_err_t s3706_touch_device_control(rt_device_t dev, int cmd, void *args)
{
    if (cmd == (int)TOUCH_CMD_EXSEM)
    {
        s3706_driver.ex_sem = args;
        if (s3706_driver.ex_sem == RT_NULL)
            tp_dbg("ex_sem is null.\n");
    }

    return RT_EOK;
}

touchpanel_ops_t s3706_ops =
{
    .init = s3706_touch_device_init,
    .read = s3706_touch_device_read,
    .control = s3706_touch_device_control,
    .get_chip_info = RT_NULL,
    .mode_switch = RT_NULL,
    .get_touch_points = s3706_get_touch_points,
    .ftm_process = RT_NULL,
    .reset = RT_NULL,
    .reinit_device = RT_NULL,
    .power_control = RT_NULL,
    .reset_gpio_control = RT_NULL,
    .trigger_reason = s3706_trigger_reason,
    .touch_handle = s3706_touch_handle,
};

touch_driver_t s3706_driver =
{
    .name = "s3706",
    .isr_sem = RT_NULL,
    .ex_sem = RT_NULL,
    .read_mutex = RT_NULL,
    .ops = &s3706_ops,
};

#endif /* RT_USING_TOUCH*/
