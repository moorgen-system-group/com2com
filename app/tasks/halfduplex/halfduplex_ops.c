/**
 * @file app\tasks\halfduplex\halfduplex_ops.c
 *
 * Copyright (C) 2023
 *
 * halfduplex_ops.c is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * @author HinsShum hinsshum@qq.com
 *
 * @encoding utf-8
 */

/*---------- includes ----------*/
#include "inc/halfduplex_ops.h"
#include "resources.h"
#include "serial.h"
#include "timer.h"
#include "options.h"

/*---------- macro ----------*/
#define TAG                                         "HalfDuplexOps"

/*---------- type define ----------*/
/*---------- variable prototype ----------*/
/*---------- function prototype ----------*/
/*---------- variable ----------*/
static QueueHandle_t q_event;
static void *serial;
static void *timer;

/*---------- function ----------*/
static bool _serial_init(uint32_t baudrate)
{
    bool retval = false;
    uint32_t old_baudrate = 0;

    do {
        serial = resources_get("dev_com1");
        assert(serial);
        if(!serial) {
            break;
        }
        device_ioctl(serial, IOCTL_SERIAL_GET_BAUDRATE, &old_baudrate);
        if(old_baudrate != baudrate) {
            /* configure serial baudrate */
            if(device_ioctl(serial, IOCTL_SERIAL_SET_BAUDRATE, &baudrate) != CY_EOK) {
                xlog_tag_error(TAG, "Reconfigure serial baudrate to %dbps failure\n", baudrate);
                break;
            }
        }
        retval = true;
    } while(0);

    return retval;
}

static void _serial_post(const uint8_t *pbuf, uint32_t length)
{
    device_write(serial, (void *)pbuf, SERIAL_WRITE_CHANGE_DIR_AUTOMATICALLY, length);
}

static bool _timer_init(uint32_t t35_50us)
{
    bool retval = false;
    uint32_t us = t35_50us * 50;
    uint32_t freq = 0;

    do {
        timer = resources_get("dev_tim1");
        assert(timer);
        if(!timer) {
            break;
        }
        freq = (uint32_t)((float)1000000 / us);
        if(device_ioctl(timer, IOCTL_TIMER_SET_FREQ, &freq) != CY_EOK) {
            xlog_tag_error(TAG, "Reconfigure timer freq to %dHz failure\n", freq);
            break;
        }
        retval = true;
    } while(0);

    return retval;
}

static void _timer_ctrl(bool enable)
{
    uint32_t iocmd = (enable ? IOCTL_TIMER_ENABLE : IOCTL_TIMER_DISABLE);

    assert(timer);
    device_ioctl(timer, iocmd, NULL);
}

static bool _event_init(void)
{
    q_event = xQueueCreate(10, sizeof(serial_mac_evt_t));
    assert(q_event);

    return (q_event != NULL);
}

static bool _event_post(serial_mac_evt_t evt)
{
    bool err = false;
    portBASE_TYPE yield = pdFALSE;

    assert(q_event);
    if(xQueueSendFromISR(q_event, &evt, &yield) == pdPASS) {
        err = true;
    }
    portYIELD_FROM_ISR(yield);

    return err;
}

static bool _event_get(serial_mac_evt_t *evt)
{
    bool err = false;

    assert(q_event);
    assert(evt);
    if(xQueueReceive(q_event, evt, __ms2ticks(10)) == pdPASS) {
        err = true;
    }

    return err;
}

void halfduplex_ops_get(struct serial_mac_ops *ops)
{
    assert(ops);
    ops->halfduplex.serial_init = _serial_init;
    ops->halfduplex.serial_post = _serial_post;
    ops->halfduplex.timer_init = _timer_init;
    ops->halfduplex.timer_ctrl = _timer_ctrl;
    ops->halfduplex.event_init = _event_init;
    ops->halfduplex.event_post = _event_post;
    ops->halfduplex.event_get = _event_get;
}
