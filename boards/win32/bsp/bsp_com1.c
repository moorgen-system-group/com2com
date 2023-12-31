/**
 * @file boards\win32\bsp\bsp_com1.c
 *
 * Copyright (C) 2023
 *
 * bsp_com1.c is free software: you can redistribute it and/or modify
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
#include "rs232.h"
#include "utils.h"
#include "options.h"
#include <stdio.h>
#include <string.h>

/*---------- macro ----------*/
/*---------- type define ----------*/
/*---------- variable prototype ----------*/
/*---------- function prototype ----------*/
static bool bsp_init(void);
static void bsp_deinit(void);
static uint16_t bsp_write(uint8_t *pbuf, uint16_t length);

/*---------- variable ----------*/
static serial_describe_t com = {
    .comport = 8,
    .baudrate = 19200,
    .ops.init = bsp_init,
    .ops.deinit = bsp_deinit,
    .ops.dir_change = NULL,
    .ops.write = bsp_write,
    .ops.irq_handler = NULL
};
DEVICE_DEFINED(com1, serial, &com);

/*---------- function ----------*/
static void _get_cfg(void)
{
    FILE *fp = NULL;
    char line[128] = {0};
    char *p = NULL;
    char *argv[3] = {NULL};
    uint32_t comport = 0;
    uint32_t baudrate = 0;

    fp = fopen("cfg.ini", "r");
    if(fp) {
        while(!feof(fp)) {
            memset(line, 0, ARRAY_SIZE(line));
            fgets(line, ARRAY_SIZE(line), fp);
            p = strstr(line, "com1");
            if(p) {
                utils_nsplit(line, ':', ARRAY_SIZE(argv), argv);
                if(argv[1]) {
                    comport = strtoul(argv[1], NULL, 10);
                    if(comport > 0 && comport < 65) {
                        com.comport = comport;
                    }
                }
                if(argv[2]) {
                    baudrate = strtoul(argv[2], NULL, 10);
                    if(baudrate) {
                        com.baudrate = baudrate;
                    }
                }
                break;
            }
        }
    }
}

static bool bsp_init(void)
{
    bool retval = true;
    char mode[] = {'8', 'N', '1', 0};
    uint32_t comport = 0;

    _get_cfg();
    comport = (com.comport == 0) ? com.comport : com.comport - 1;
    /* 0:COM1, 1:COM2... */
    if(RS232_OpenComport(comport, com.baudrate, mode) != 0) {
        retval = false;
        xlog_error("Can not open COM%d\n", com.comport);
    }

    return retval;
}

static void bsp_deinit(void)
{
    uint32_t comport = (com.comport == 0) ? com.comport : com.comport - 1;

    RS232_CloseComport(comport);
}

static uint16_t bsp_write(uint8_t *pbuf, uint16_t length)
{
    uint32_t comport = (com.comport == 0) ? com.comport : com.comport - 1;

    RS232_SendBuf(comport, (unsigned char *)pbuf, length);

    return length;
}
