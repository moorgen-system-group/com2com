/**
 * @file boards\win32\bsp\bsp_tim1.c
 *
 * Copyright (C) 2023
 *
 * bsp_tim1.c is free software: you can redistribute it and/or modify
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
#include "timer.h"
#include "options.h"

/*---------- macro ----------*/
/*---------- type define ----------*/
/*---------- variable prototype ----------*/
/*---------- function prototype ----------*/
static bool bsp_init(void);
static void bsp_deinit(void);
static bool bsp_enable(bool ctrl);

/*---------- variable ----------*/
static TimerHandle_t _timer;
static timer_describe_t tim = {
    .freq = 1,
    .ops.init = bsp_init,
    .ops.deinit = bsp_deinit,
    .ops.enable = bsp_enable,
    .ops.irq_handler = NULL
};
DEVICE_DEFINED(tim1, timer, &tim);

/*---------- function ----------*/
static void bsp_callback(TimerHandle_t timer)
{
    if(tim.ops.irq_handler) {
        tim.ops.irq_handler(0, NULL, 0);
    }
}

static bool bsp_init(void)
{
    uint32_t tick = 0;

    /* create a soft timer */
    if(tim.freq > configTICK_RATE_HZ) {
        tim.freq = configTICK_RATE_HZ;
    }
    tick = __ms2ticks(1000 / tim.freq);
    _timer = xTimerCreate("tim", tick, pdFALSE, NULL, bsp_callback);

    return (_timer != NULL);
}

static void bsp_deinit(void)
{
    xTimerDelete(_timer, portMAX_DELAY);
    _timer = NULL;
}

static bool bsp_enable(bool ctrl)
{
    if(ctrl) {
        if(_timer) {
            xTimerStart(_timer, portMAX_DELAY);
        }
    } else {
        if(_timer) {
            xTimerStop(_timer, portMAX_DELAY);
        }
    }

    return true;
}
