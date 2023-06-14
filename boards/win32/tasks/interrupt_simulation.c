/**
 * @file boards\win32\tasks\interrupt_simulation.c
 *
 * Copyright (C) 2023
 *
 * interrupt_simulation.c is free software: you can redistribute it and/or modify
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
#include "serial.h"
#include "options.h"
#include "rs232.h"

/*---------- macro ----------*/
/*---------- type define ----------*/
/*---------- variable prototype ----------*/
/*---------- function prototype ----------*/
/*---------- variable ----------*/
static uint8_t com0_buffer[1024];
static uint64_t ticks;
static SemaphoreHandle_t mutex;

/*---------- function ----------*/
static void _init(void)
{
    mutex = xSemaphoreCreateMutex();
}

static void _ticks_inc(void)
{
    xSemaphoreTake(mutex, portMAX_DELAY);
    ticks++;
    xSemaphoreGive(mutex);
}

static void _com0_irq(void)
{
    static int8_t comport = -1;
    int32_t count = 0;

    if(comport < 0) {
        device_ioctl(NULL, IOCTL_SERIAL_GET_COMPORT, &comport);
        if(comport > 0) {
            comport -= 1;
        }
    }
    if((count = RS232_PollComport(comport, com0_buffer, ARRAY_SIZE(com0_buffer))) > 0) {
        device_irq_process(NULL, (uint32_t)_com0_irq, com0_buffer, count);
        memset(com0_buffer, 0, count);
    }
}

static void _task(void *argv)
{
    _init();
    for(;;) {
        __delay_ms(1);
        _ticks_inc();
        _com0_irq();
    }
}

void task_interrupt_create(void)
{
    xTaskCreate(_task, "Interrupt", 512, NULL, configMAX_PRIORITIES - 2, NULL);
}

uint64_t ticks_get(void)
{
    uint64_t t = 0;

    xSemaphoreTake(mutex, portMAX_DELAY);
    t = ticks;
    xSemaphoreGive(mutex);

    return t;
}

uint64_t ticks_get_from_isr(void)
{
    return ticks;
}
