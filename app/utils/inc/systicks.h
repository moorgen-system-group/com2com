/**
 * @file app\utils\inc\systicks.h
 *
 * Copyright (C) 2023
 *
 * systicks.h is free software: you can redistribute it and/or modify
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
#ifndef __SYSTICKS_H
#define __SYSTICKS_H

#ifdef __cplusplus
extern "C"
{
#endif

/*---------- includes ----------*/
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

/*---------- macro ----------*/
/*---------- type define ----------*/
typedef void (*systick_cb_t)(void);

/*---------- variable prototype ----------*/
/*---------- function prototype ----------*/
extern bool systicks_add(systick_cb_t cb);
extern void systicks_del(systick_cb_t cb);
extern void systicks_polling(void);

#ifdef __cplusplus
}
#endif
#endif /* __SYSTICKS_H */
