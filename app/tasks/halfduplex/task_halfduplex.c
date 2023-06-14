/**
 * @file app\tasks\halfduplex\task_halfduplex.c
 *
 * Copyright (C) 2023
 *
 * task_halfduplex.c is free software: you can redistribute it and/or modify
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
#include "tasks_def.h"
#include "resources.h"
#include "serial.h"
#include "timer.h"
#include "systicks.h"
#include "options.h"

/*---------- macro ----------*/
#define TAG                                         "HalfDuplex"

/*---------- type define ----------*/
/*---------- variable prototype ----------*/
/*---------- function prototype ----------*/
/*---------- variable ----------*/
static SemaphoreHandle_t mutex;
static serial_transport_t halfduplex;

/*---------- function ----------*/
static void __lock(void)
{
    xSemaphoreTake(mutex, portMAX_DELAY);
}

static void __unlock(void)
{
    xSemaphoreGive(mutex);
}

static void __called_in_systick(void)
{
    assert(halfduplex);
    serial_transport_called_per_tick(halfduplex);
}

static int32_t __serial_irq_handler(uint32_t irq, void *args, uint32_t length)
{
    uint8_t *bytes = (uint8_t *)args;

    assert(args);
    assert(halfduplex);
    for(uint32_t i = 0; i < length; ++i) {
        serial_transport_recv_byte(halfduplex, bytes[i]);
    }

    return CY_EOK;
}

static int32_t __timer_irq_handler(uint32_t irq, void *args, uint32_t length)
{
    assert(halfduplex);
    serial_transport_timer_expired(halfduplex);

    return CY_EOK;
}

static void __recv(const uint8_t *recv_buf, uint32_t recv_len, const uint8_t *trans_buf, uint32_t trans_len)
{
    extern void fullduplex_set_transmitter(const uint8_t *pbuf, uint32_t length);

    fullduplex_set_transmitter(recv_buf, recv_len);
}

static void _init(void)
{
    struct serial_transport_ops ops = {0};
    void *serial = resources_get("dev_com1");
    void *tim = resources_get("dev_tim1");

    assert(serial);
    assert(tim);
    mutex = xSemaphoreCreateMutex();
    assert(mutex);
    halfduplex_ops_get(&ops.mac_ops);
    ops.mac_ops.receive_packet_parse = __recv;
    ops.lock = __lock;
    ops.unlock = __unlock;
    halfduplex = serial_transport_new(SERIAL_MAC_TYPE_HALFDUPLEX, 19200, 256, 256, 20, &ops);
    assert(halfduplex);
    device_ioctl(serial, IOCTL_SERIAL_SET_IRQ_HANDLER, __serial_irq_handler);
    device_ioctl(tim, IOCTL_TIMER_SET_IRQ_HANDLER, __timer_irq_handler);
    systicks_add(__called_in_systick);
}

static void _task(void *argv)
{
    _init();
    for(;;) {
        serial_transport_poll(halfduplex);
    }
}

void task_halfduplex_create(void)
{
    xTaskCreate(_task, TAG, TASK_HALFDUPLEX_STACKSIZE, NULL, TASK_HALFDUPLEX_PRIO, NULL);
}

void halfduplex_set_transmitter(const uint8_t *pbuf, uint32_t length)
{
    assert(halfduplex);
    serial_transport_set_transmitter(halfduplex, pbuf, length);
}
