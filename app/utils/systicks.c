/**
 * @file app\utils\systicks.c
 *
 * Copyright (C) 2023
 *
 * systicks.c is free software: you can redistribute it and/or modify
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
#include "systicks.h"
#include "lists.h"
#include "options.h"

/*---------- macro ----------*/
/*---------- type define ----------*/
typedef struct node *node_t;
struct node {
    struct list_head n;
    systick_cb_t cb;
};

/*---------- variable prototype ----------*/
/*---------- function prototype ----------*/
/*---------- variable ----------*/
static LIST_HEAD(head);

/*---------- function ----------*/
static inline bool _search_pool(systick_cb_t cb)
{
    bool searched = false;
    node_t p = NULL;

    list_for_each_entry(p, struct node, &head, n) {
        if(p->cb == cb) {
            searched = true;
            break;
        }
    }

    return searched;
}

bool systicks_add(systick_cb_t cb)
{
    node_t p = NULL;
    bool err = false;

    do {
        if(_search_pool(cb)) {
            err = true;
            break;
        }
        if(!cb) {
            break;
        }
        p = __malloc(sizeof(*p));
        if(!p) {
            break;
        }
        p->cb = cb;
        __enter_critical();
        list_add_tail(&p->n, &head);
        __exit_critical();
        err = true;
    } while(0);

    return err;
}

void systicks_del(systick_cb_t cb)
{
    node_t p = NULL;

    list_for_each_entry(p, struct node, &head, n) {
        if(p->cb == cb) {
            __enter_critical();
            list_del(&p->n);
            __exit_critical();
            __free(p);
            break;
        }
    }
}

void systicks_polling(void)
{
    node_t p = NULL;

    list_for_each_entry(p, struct node, &head, n) {
        p->cb();
    }
}
