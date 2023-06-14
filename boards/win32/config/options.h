/**
 * @file boards\win32\config\options.h
 *
 * Copyright (C) 2022
 *
 * options.h is free software: you can redistribute it and/or modify
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
#ifndef __WIN32_OPTIONS_H
#define __WIN32_OPTIONS_H

#ifdef __cplusplus
extern "C"
{
#endif

/*---------- includes ----------*/
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <windows.h>
#include "misc.h"
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "queue.h"
#include "semphr.h"

/*---------- macro ----------*/
/* system delay function
 */
#define __delay_ms(ms)                  vTaskDelay(pdMS_TO_TICKS(ms))
#define __delay_us(us)
#define __get_ticks()                   (ticks_get())
#define __get_ticks_from_isr()          (ticks_get_from_isr())
#define __reset_system()
#define __enter_critical()              taskENTER_CRITICAL()
#define __exit_critical()               taskEXIT_CRITICAL()
#define __enter_critical_from_isr()     taskENTER_CRITICAL_FROM_ISR()
#define __exit_critical_from_isr()      taskEXIT_CRITICAL_FROM_ISR()
#define __malloc(size)                  pvPortMalloc(size)
#define __free(ptr)                     vPortFree(ptr)
#define __ticks2ms(ticks)               ((ticks * (TickType_t)1000U) / (TickType_t)configTICK_RATE_HZ)
#define __ms2ticks(ms)                  (pdMS_TO_TICKS(ms))

/* print for kernel
 */
#ifndef CONFIG_SILECE
#include <stdio.h>
#define xlog_error(x, y...)             printf(COLOR_RED x, ##y)
#define xlog_warn(x, y...)              printf(COLOR_YELLOW x, ##y)
#define xlog_message(x, y...)           printf(COLOR_GREEN x, ##y)
#define xlog_info(x, y...)              printf(COLOR_WHITE x, ##y)
#define xlog_cont(x, y...)              printf(x, ##y)
#define xlog_tag_error(tag, x, y...)    printf(COLOR_RED "(" tag ")" x, ##y)
#define xlog_tag_warn(tag, x, y...)     printf(COLOR_YELLOW "(" tag ")" x, ##y)
#define xlog_tag_message(tag, x, y...)  printf(COLOR_GREEN "(" tag ")" x, ##y)
#define xlog_tag_info(tag, x, y...)     printf(COLOR_WHITE "(" tag ")" x, ##y)
#else
#define xlog_error(x, y...)
#define xlog_warn(x, y...)
#define xlog_message(x, y...)
#define xlog_info(x, y...)
#define xlog_cont(x, y...)
#define xlog_tag_error(tag, x, y...)
#define xlog_tag_warn(tag, x, y...)
#define xlog_tag_message(tag, x, y...)
#define xlog_tag_info(tag, x, y...)
#endif

/* protocol debug definition
 */
#ifndef CONFIG_SILECE
#define CONFIG_SERIAL_MAC_DEBUG
#endif

/*---------- type define ----------*/
/*---------- variable prototype ----------*/
/*---------- function prototype ----------*/
extern uint64_t ticks_get(void);
extern uint64_t ticks_get_from_isr(void);

#ifdef __cplusplus
}
#endif
#endif /* __WIN32_OPTIONS_H */
