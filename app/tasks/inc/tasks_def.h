/**
 * @file app\tasks\inc\tasks_def.h
 *
 * Copyright (C) 2023
 *
 * tasks_def.h is free software: you can redistribute it and/or modify
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
#ifndef __TASKS_DEF_H
#define __TASKS_DEF_H

#ifdef __cplusplus
extern "C"
{
#endif

/*---------- includes ----------*/
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "options.h"

/*---------- macro ----------*/
/* task stack size definition
 */
#define TASK_DAEMON_STACKSIZE                       (1024)

/* task priority definition
 */
#define TASK_DAEMON_PRIO                            (tskIDLE_PRIORITY + 1)

/*---------- type define ----------*/
/*---------- variable prototype ----------*/
/*---------- function prototype ----------*/
extern void task_daemon_create(void);

#ifdef __cplusplus
}
#endif
#endif /* __TASKS_DEF_H */
