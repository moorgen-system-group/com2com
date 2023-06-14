/**
 * @file app\utils\resources.c
 *
 * Copyright (C) 2023
 *
 * resources.c is free software: you can redistribute it and/or modify
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
#include "resources.h"
#include "resource_manager.h"
#include "device.h"
#include "driver.h"
#include "options.h"

/*---------- macro ----------*/
#define IMPORT_DEVICE(name)                                                 \
        do {                                                                \
            void *dev = device_open(#name);                                 \
            assert(dev);                                                    \
            resources->add_resource(resources, "dev_" #name, dev);          \
        } while(0)

#define EXPORT_DEVICE(name)                                                 \
        do {                                                                \
            void *dev = resources->get_resource(resources, "dev_" #name);   \
            assert(dev);                                                    \
            device_close(dev);                                              \
            resources->remove_resource(resources, "dev_" #name);            \
        } while(0)

/*---------- type define ----------*/
/*---------- variable prototype ----------*/
/*---------- function prototype ----------*/
/*---------- variable ----------*/
static resource_manager_base_t resources;

/*---------- function ----------*/
static void _resources_init(void)
{
    IMPORT_DEVICE(com0);
}

static void _resources_deinit(void)
{
    EXPORT_DEVICE(com0);
}

void resources_init(void)
{
    driver_search_device();
    resources_deinit();
    resources = resource_manager_create();
    _resources_init();
}

void resources_deinit(void)
{
    if(resources) {
        _resources_deinit();
        resource_manager_destroy(resources);
        resources = NULL;
    }
}

void *resources_get(const char *name)
{
    void *handle = NULL;

    if(resources) {
        handle = resources->get_resource_careful(resources, name);
    }

    return handle;
}

bool resources_set(const char *name, void *handle)
{
    bool retval = false;

    if(resources) {
        retval = resources->add_resource(resources, name, handle);
    }

    return retval;
}
