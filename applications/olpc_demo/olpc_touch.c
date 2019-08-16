/**************************************************************
 * Copyright (c)  2008- 2030  Oppo Mobile communication Corp.ltd
 * VENDOR_EDIT
 * File             : olpc_touch.c
 * Description      : Source file for touch function
 * Version          : 1.0
 * Date             : 2019-08-01
 * Author           : zhoufeng@swdp
 * ---------------- Revision History: --------------------------
 *   <version>        <date>                  < author >                                                        <desc>
 * Revision 1.1, 2019-08-01, zhoufeng@swdp, initial touch function
 ****************************************************************/
#include <rtthread.h>
#if defined(RT_USING_OLPC_DEMO) && defined(RT_USING_TOUCH)
#include <rtdevice.h>

#include <drv_touch.h>
#include <drv_touch_s3706.h>
#include "olpc_touch.h"

#include "image_info.h"

static struct olpc_touch g_olpc_touch;

rt_err_t register_touch_item(struct olpc_touch_item *item,
                             void (*entry)(void *parameter),
                             void *parameter,
                             rt_int32_t touch_id)
{
    RT_ASSERT(item != RT_NULL);

    struct olpc_touch_item *touch_list = g_olpc_touch.touch_list;

    item->next = RT_NULL;
    item->prev = touch_list;

    touch_list->next = item;

    g_olpc_touch.touch_list = item;

    image_info_t *image = (image_info_t *)item;
    image->touch_callback = (void *)entry;
    image->parameter = parameter;
    image->touch_id = touch_id;

    return RT_EOK;
}

void update_item_coord(struct olpc_touch_item *item, rt_uint32_t fb_x, rt_uint32_t fb_y, rt_uint32_t x_offset, rt_uint32_t y_offset)
{
    RT_ASSERT(item != RT_NULL);

    image_info_t *image = (image_info_t *)item;

    image->x_scr = fb_x + x_offset;
    image->y_scr = fb_y + y_offset;

    //rt_kprintf("%s, x = %d, y = %d.\n", __func__, image->x_scr, image->y_scr);
}

rt_uint8_t is_tp_in_item(struct point_info *point, image_info_t *item)
{
    RT_ASSERT(point != RT_NULL);
    RT_ASSERT(item != RT_NULL);

    if ((item->x_scr < point->x) && (point->x < item->x_scr + item->w))
        if ((item->y_scr < point->y) && (point->y < item->y_scr + item->h))
        {
            return 1;
        }

    return 0;
}

rt_err_t iterate_touch_item_list(struct olpc_touch_item *header, struct point_info *point)
{
    RT_ASSERT(header != RT_NULL);
    RT_ASSERT(point != RT_NULL);

    struct olpc_touch_item *touch_item = header;

    image_info_t *image = RT_NULL;

    touch_item = touch_item->next;

    while (touch_item != RT_NULL)
    {
        //rt_kprintf("%s, item addr: 0x%x.\n", __func__, touch_item);

        image = (image_info_t *)touch_item;

        if (is_tp_in_item(point, image) != 0)
        {
            image->touch_state = TOUCH_EVENT_DOWN;
            image->touch_callback(image->touch_id, TOUCH_EVENT_DOWN, image->parameter);
        }
        else if (point->x == 0 && point->y == 0)
        {
            image->touch_state = TOUCH_EVENT_UP;
            image->touch_callback(image->touch_id, TOUCH_EVENT_UP, image->parameter);
        };

        touch_item = touch_item->next;
    }

    return RT_EOK;
}

static void touch_mgr_thread_entry(void *parameter)
{
    rt_err_t ret = RT_EOK;
    touch_device_t *touch_dev = RT_NULL;

    struct olpc_touch_item *touch_list = (struct olpc_touch_item *)parameter;

    touch_dev = (touch_device_t *)rt_device_find("s3706");
    RT_ASSERT(touch_dev != RT_NULL);

    struct point_info point;

    while (1)
    {
        ret = rt_mq_recv(&touch_dev->tp_mq, &point, sizeof(struct point_info), RT_WAITING_FOREVER);
        RT_ASSERT(ret == RT_EOK);

        //rt_kprintf("tp mgr point: x = 0x%x, y = 0x%x, z = 0x%x.\n", point.x, point.y, point.z);

        /* iterate touch item list */
        iterate_touch_item_list(touch_list, &point);
    }
}

int olpc_touch_init(void)
{
    struct olpc_touch_item *head = &g_olpc_touch.touch_header;

    head->next = head;
    head->prev = head;

    g_olpc_touch.touch_list = head;

    /* create touch manager thread */

    rt_thread_t touch_thread;
    touch_thread = rt_thread_create("tpmgr",
                                    touch_mgr_thread_entry, &g_olpc_touch.touch_header,
                                    1024, 10, 20);
    if (touch_thread != RT_NULL)
        rt_thread_startup(touch_thread);

    return RT_EOK;
}
INIT_APP_EXPORT(olpc_touch_init);

#endif
