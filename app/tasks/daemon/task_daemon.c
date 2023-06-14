/**
 * @file app\tasks\daemon\task_daemon.c
 *
 * Copyright (C) 2023
 *
 * task_daemon.c is free software: you can redistribute it and/or modify
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
#include "tasks_def.h"

/*---------- macro ----------*/
/*---------- type define ----------*/
/*---------- variable prototype ----------*/
/*---------- function prototype ----------*/
/*---------- variable ----------*/
/*---------- function ----------*/
static void _task(void *argv)
{
    for(;;) {
        __delay_ms(1000);
    }
}

void task_daemon_create(void)
{
    xTaskCreate(_task, "Daemon", TASK_DAEMON_STACKSIZE, NULL, TASK_DAEMON_PRIO, NULL);
}