/**
 * Copyright (c) 2015 - present LibDriver All rights reserved
 * 
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE. 
 *
 * @file      main.c
 * @brief     main souce file
 * @version   1.0.0
 * @author    Shifeng Li
 * @date      2022-03-19
 *
 * <h3>history</h3>
 * <table>
 * <tr><th>Date        <th>Version  <th>Author      <th>Description
 * <tr><td>2022/03/19  <td>1.0      <td>Shifeng Li  <td>first upload
 * </table>
 */

#include "driver_st7920_basic.h"
#include "driver_st7920_advance.h"
#include "driver_st7920_display_test.h"
#include "clock.h"
#include "delay.h"
#include "uart.h"
#include "shell.h"
#include <stdlib.h>

/**
 * @brief global var definition
 */
uint8_t g_buf[256];        /**< uart buffer */
uint16_t g_len;            /**< uart buffer length */

/**
 * @brief     st7920 full function
 * @param[in] argc is arg numbers
 * @param[in] **argv is the arg address
 * @return    status code
 *             - 0 success
 *             - 1 run failed
 *             - 5 param is invalid
 * @note      none
 */
uint8_t st7920(uint8_t argc, char **argv)
{
    if (argc == 1)
    {
        goto help;
    }
    else if (argc == 2)
    {
        if (strcmp("-i", argv[1]) == 0)
        {
            st7920_info_t info;
            
            /* print st7920 info */
            st7920_info(&info);
            st7920_interface_debug_print("st7920: chip is %s.\n", info.chip_name);
            st7920_interface_debug_print("st7920: manufacturer is %s.\n", info.manufacturer_name);
            st7920_interface_debug_print("st7920: interface is %s.\n", info.interface);
            st7920_interface_debug_print("st7920: driver version is %d.%d.\n", info.driver_version/1000, (info.driver_version%1000)/100);
            st7920_interface_debug_print("st7920: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
            st7920_interface_debug_print("st7920: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
            st7920_interface_debug_print("st7920: max current is %0.2fmA.\n", info.max_current_ma);
            st7920_interface_debug_print("st7920: max temperature is %0.1fC.\n", info.temperature_max);
            st7920_interface_debug_print("st7920: min temperature is %0.1fC.\n", info.temperature_min);
            
            return 0;
        }
        else if (strcmp("-p", argv[1]) == 0)
        {
            /* print pin connection */
            st7920_interface_debug_print("st7920: RS connected to GPIOB PIN1.\n");
            st7920_interface_debug_print("st7920: RW connected to GPIOA PIN8.\n");
            st7920_interface_debug_print("st7920: E connected to GPIOB PIN0.\n");
            st7920_interface_debug_print("st7920: PSB connected to GND.\n");
            
            return 0;
        }
        else if (strcmp("-h", argv[1]) == 0)
        {
            /* show st7920 help */
            
            help:
            
            st7920_interface_debug_print("st7920 -i\n\tshow st7920 chip and driver information.\n");
            st7920_interface_debug_print("st7920 -h\n\tshow st7920 help.\n");
            st7920_interface_debug_print("st7920 -p\n\tshow st7920 pin connections of the current board.\n");
            st7920_interface_debug_print("st7920 -t display\n\trun st7920 display test.\n");
            st7920_interface_debug_print("st7920 -c basic -init\n\trun st7920 basic init function.\n");
            st7920_interface_debug_print("st7920 -c basic -deinit\n\trun st7920 basic deinit function.\n");
            st7920_interface_debug_print("st7920 -c basic -str <string>\n\trun st7920 show string function.string means the shown string.\n");
            st7920_interface_debug_print("st7920 -c basic -displayon\n\trun st7920 display on function.\n");
            st7920_interface_debug_print("st7920 -c basic -displayoff\n\trun st7920 display off function.\n");
            st7920_interface_debug_print("st7920 -c basic -clear\n\trun st7920 clear screen function.\n");
            st7920_interface_debug_print("st7920 -c basic -writepoint <x> <y> <color>\n\trun st7920 write pont function."
                                          "x and y mean coordinate in screen.color means the filled color.\n");
            st7920_interface_debug_print("st7920 -c basic -rect <x1> <y1> <x2> <y2> <color>\n\trun st7920 draw rectangle function."
                                          "x1 means x start.y1 means y start.x2 means x end.y2 means y end.color means the filled color.\n");
            st7920_interface_debug_print("st7920 -c advance -init\n\trun st7920 advance init function.\n");
            st7920_interface_debug_print("st7920 -c advance -deinit\n\trun st7920 advance deinit function.\n");
            st7920_interface_debug_print("st7920 -c advance -str <string>\n\trun st7920 show string function."
                                          "string means the shown string.\n");
            st7920_interface_debug_print("st7920 -c advance -displayon\n\trun st7920 display on function.\n");
            st7920_interface_debug_print("st7920 -c advance -displayoff\n\trun st7920 display off function.\n");
            st7920_interface_debug_print("st7920 -c advance -clear\n\trun st7920 clear screen function.\n");
            st7920_interface_debug_print("st7920 -c advance -writepoint <x> <y> <color>\n\trun st7920 write pont function."
                                          "x and y mean coordinate in screen.color means the filled color.\n");
            st7920_interface_debug_print("st7920 -c advance -rect <x1> <y1> <x2> <y2> <color>\n\trun st7920 draw rectangle function."
                                          "x1 means x start.y1 means y start.x2 means x end.y2 means y end.color means the filled color.\n");
            st7920_interface_debug_print("st7920 -c advance -disable_scroll\n\trun st7920 disable scroll function.\n");
            st7920_interface_debug_print("st7920 -c advance -scroll <addr>\n\trun st7920 scroll function.addr is the scroll address and 0 <= addr <= 0x3F.\n");
            st7920_interface_debug_print("st7920 -c advance -reverse_line <line>\n\trun st7920 reverse line function."
                                         "line is the reverse line and it can be \"0\" or \"1\".\n");
            
            return 0;
        }
        else
        {
            return 5;
        }
    }
    else if (argc == 3)
    {
        /* run test */
        if (strcmp("-t", argv[1]) == 0)
        {
            /* display test */
            if (strcmp("display", argv[2]) == 0)
            {
                /* run reg test */
                if (st7920_display_test())
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
            }
            /* param is invalid */
            else
            {
                return 5;
            }
        }
        /* param is invalid */
        else
        {
            return 5;
        }
    }
    else if (argc == 4)
    {
        if (strcmp("-c", argv[1]) == 0)
        {
            /* basic test */
            if (strcmp("basic", argv[2]) == 0)
            {
                volatile uint8_t res;

                if (strcmp("-displayon", argv[3]) == 0)
                {
                    res = st7920_basic_display_on();
                    if (res)
                    {
                        st7920_interface_debug_print("st7920: display on failed.\n");
                        st7920_basic_deinit();
                        
                        return 1;
                    }
                    st7920_interface_debug_print("st7920: display on.\n");
                    
                    return 0;
                }
                else if (strcmp("-displayoff", argv[3]) == 0)
                {
                    res = st7920_basic_display_off();
                    if (res)
                    {
                        st7920_interface_debug_print("st7920: display off failed.\n");
                        st7920_basic_deinit();
                        
                        return 1;
                    }
                    st7920_interface_debug_print("st7920: display off.\n");
                    
                    return 0;
                }
                else if (strcmp("-clear", argv[3]) == 0)
                {
                    res = st7920_basic_clear();
                    if (res)
                    {
                        st7920_interface_debug_print("st7920: clear screen failed.\n");
                        st7920_basic_deinit();
                        
                        return 1;
                    }
                    st7920_interface_debug_print("st7920: clear screen.\n");
                    
                    return 0;
                }
                else if (strcmp("-init", argv[3]) == 0)
                {
                    res = st7920_basic_init();
                    if (res)
                    {
                        st7920_interface_debug_print("st7920: init failed.\n");
                        
                        return 1;
                    }
                    st7920_interface_debug_print("st7920: init success.\n");
                    
                    return 0;
                }
                else if (strcmp("-deinit", argv[3]) == 0)
                {
                    res = st7920_basic_deinit();
                    if (res)
                    {
                        st7920_interface_debug_print("st7920: deinit failed.\n");
                        
                        return 1;
                    }
                    st7920_interface_debug_print("st7920: deinit st7920.\n");
                    
                    return 0;
                }
                else
                {
                    return 5;
                }
            }
            /* advance test */
            else if (strcmp("advance", argv[2]) == 0)
            {
                volatile uint8_t res;

                if (strcmp("-displayon", argv[3]) == 0)
                {
                    res = st7920_advance_display_on();
                    if (res)
                    {
                        st7920_interface_debug_print("st7920: display on failed.\n");
                        st7920_advance_deinit();
                        
                        return 1;
                    }
                    st7920_interface_debug_print("st7920: display on.\n");
                    
                    return 0;
                }
                else if (strcmp("-displayoff", argv[3]) == 0)
                {
                    res = st7920_advance_display_off();
                    if (res)
                    {
                        st7920_interface_debug_print("st7920: display off failed.\n");
                        st7920_advance_deinit();
                        
                        return 1;
                    }
                    st7920_interface_debug_print("st7920: display off.\n");
                    
                    return 0;
                }
                else if (strcmp("-clear", argv[3]) == 0)
                {
                    res = st7920_advance_clear();
                    if (res)
                    {
                        st7920_interface_debug_print("st7920: clear screen failed.\n");
                        st7920_advance_deinit();
                        
                        return 1;
                    }
                    st7920_interface_debug_print("st7920: clear screen.\n");
                    
                    return 0;
                }
                else if (strcmp("-init", argv[3]) == 0)
                {
                    res = st7920_advance_init();
                    if (res)
                    {
                        st7920_interface_debug_print("st7920: init failed.\n");
                        
                        return 1;
                    }
                    st7920_interface_debug_print("st7920: init success.\n");
                    
                    return 0;
                }
                else if (strcmp("-deinit", argv[3]) == 0)
                {
                    res = st7920_advance_deinit();
                    if (res)
                    {
                        st7920_interface_debug_print("st7920: deinit failed.\n");
                        
                        return 1;
                    }
                    st7920_interface_debug_print("st7920: deinit st7920.\n");
                    
                    return 0;
                }
                else if (strcmp("-disable_scroll", argv[3]) == 0)
                {
                    res = st7920_advance_disable_scroll();
                    if (res)
                    {
                        st7920_interface_debug_print("st7920: disable scroll failed.\n");
                        
                        return 1;
                    }
                    st7920_interface_debug_print("st7920: disable scroll.\n");
                    
                    return 0;
                }
                else
                {
                    return 5;
                }
            }
            /* param is invalid */
            else
            {
                return 5;
            }
        }
        /* param is invalid */
        else
        {
            return 5;
        }
    }
    else if (argc == 5)
    {
        /* run functions */
        if (strcmp("-c", argv[1]) == 0)
        {
            /* basic test */
            if (strcmp("basic", argv[2]) == 0)
            {
                volatile uint8_t res;
                
                if (strcmp("-str", argv[3]) == 0)
                {
                    res = st7920_basic_clear();
                    if (res)
                    {
                        st7920_interface_debug_print("st7920: clear screen failed.\n");
                        st7920_basic_deinit();
                        
                        return 1;
                    }
                    res = st7920_basic_string(0, 0, argv[4]);
                    if (res)
                    {
                        st7920_interface_debug_print("st7920: show string failed.\n");
                        st7920_basic_deinit();
                        
                        return 1;
                    }
                    st7920_interface_debug_print("st7920: %s.\n", argv[4]);
                    
                    return 0;
                }
                else
                {
                    return 5;
                }
            }
            /* advance test */
            else if (strcmp("advance", argv[2]) == 0)
            {
                volatile uint8_t res;
                
                if (strcmp("-str", argv[3]) == 0)
                {
                    res = st7920_advance_clear();
                    if (res)
                    {
                        st7920_interface_debug_print("st7920: clear screen failed.\n");
                        st7920_advance_deinit();
                        
                        return 1;
                    }
                    res = st7920_advance_string(0, 0, argv[4]);
                    if (res)
                    {
                        st7920_interface_debug_print("st7920: show string failed.\n");
                        st7920_advance_deinit();
                        
                        return 1;
                    }
                    st7920_interface_debug_print("st7920: %s.\n", argv[4]);
                    
                    return 0;
                }
                else if (strcmp("-scroll", argv[3]) == 0)
                {
                    /* enable scroll */
                    res = st7920_advance_enable_scroll();
                    if (res)
                    {
                        st7920_advance_deinit();
                        
                        return 1;
                    }
                    
                    /* set scroll */
                    res = st7920_advance_set_scroll(atoi(argv[4]));
                    if (res)
                    {
                        st7920_interface_debug_print("st7920: set scroll failed.\n");
                        st7920_advance_deinit();
                        
                        return 1;
                    }
                    
                    st7920_interface_debug_print("st7920: set scroll %s.\n", argv[4]);
                    
                    return 0;
                }
                else if (strcmp("-reverse_line", argv[3]) == 0)
                {
                    if (atoi(argv[4]) > 1)
                    {
                        st7920_interface_debug_print("st7920: reverse line > 1.\n");
                    }
                    
                    /* set reverse line */
                    res = st7920_advance_set_reverse_line((st7920_reverse_line_t)(atoi(argv[4])));
                    if (res)
                    {
                        st7920_advance_deinit();
                        
                        return 1;
                    }
                    
                    st7920_interface_debug_print("st7920: set reverse line %s.\n", argv[4]);
                    
                    return 0;
                }
                else
                {
                    return 5;
                }
            }
            /* param is invalid */
            else
            {
                return 5;
            }
        }
        /* param is invalid */
        else
        {
            return 5;
        }
    }
    else if (argc == 7)
    {
        /* run functions */
        if (strcmp("-c", argv[1]) == 0)
        {
            /* basic test */
            if (strcmp("basic", argv[2]) == 0)
            {
                volatile uint8_t res;
                
                if (strcmp("-writepoint", argv[3]) == 0)
                {
                    volatile uint8_t res;
                    
                    res = st7920_basic_write_point(atoi(argv[4]), atoi(argv[5]), atoi(argv[6]));
                    if (res)
                    {
                        st7920_basic_deinit();
                        
                        return 1;
                    }
                    st7920_interface_debug_print("st7920: write point %d %d %d.\n", (uint8_t)atoi(argv[4]), (uint8_t)atoi(argv[5]), (uint16_t)atoi(argv[6]));
                    
                    return 0;
                }
                else
                {
                    return 5;
                }
            }
            /* advance test */
            else if (strcmp("advance", argv[2]) == 0)
            {
                volatile uint8_t res;

                if (strcmp("-writepoint", argv[3]) == 0)
                {
                    volatile uint8_t res;
                    
                    res = st7920_advance_write_point(atoi(argv[4]), atoi(argv[5]), atoi(argv[6]));
                    if (res)
                    {
                        st7920_advance_deinit();
                        
                        return 1;
                    }
                    st7920_interface_debug_print("st7920: write point %d %d %d.\n", (uint8_t)atoi(argv[4]), (uint8_t)atoi(argv[5]), (uint16_t)atoi(argv[6]));
                    
                    return 0;
                }
                else
                {
                    return 5;
                }
            }
            /* param is invalid */
            else
            {
                return 5;
            }
        }
        /* param is invalid */
        else
        {
            return 5;
        }
    }
    else if (argc == 9)
    {
        /* run functions */
        if (strcmp("-c", argv[1]) == 0)
        {
            /* basic test */
            if (strcmp("basic", argv[2]) == 0)
            {
                if (strcmp("-rect", argv[3]) == 0)
                {
                    volatile uint8_t res;
                    
                    res = st7920_basic_rect(atoi(argv[4]), atoi(argv[5]), atoi(argv[6]), atoi(argv[7]), atoi(argv[8]));
                    if (res)
                    {
                        st7920_basic_deinit();
                        
                        return 1;
                    }
                    st7920_interface_debug_print("st7920: draw rect %d %d %d %d.\n", (uint8_t)atoi(argv[4]), (uint8_t)atoi(argv[5]), (uint8_t)atoi(argv[6]), (uint16_t)atoi(argv[7]));
                    
                    return 0;
                }
                else
                {
                    return 5;
                }
            }
            /* advance fucntion */
            else if (strcmp("advance", argv[2]) == 0)
            {
                if (strcmp("-rect", argv[3]) == 0)
                {
                    volatile uint8_t res;
                    
                    res = st7920_advance_rect(atoi(argv[4]), atoi(argv[5]), atoi(argv[6]), atoi(argv[7]), atoi(argv[8]));
                    if (res)
                    {
                        st7920_advance_deinit();
                        
                        return 1;
                    }
                    st7920_interface_debug_print("st7920: draw rect %d %d %d %d.\n", (uint8_t)atoi(argv[4]), (uint8_t)atoi(argv[5]), (uint8_t)atoi(argv[6]), (uint16_t)atoi(argv[7]));
                    
                    return 0;
                }
                else
                {
                    return 5;
                }
            }
            /* param is invalid */
            else
            {
                return 5;
            }
        }
        /* param is invalid */
        else
        {
            return 5;
        }
    }
    /* param is invalid */
    else
    {
        return 5;
    }
}

/**
 * @brief main function
 * @note  none
 */
int main(void)
{
    volatile uint8_t res;
    
    /* stm32f407 clock init and hal init */
    clock_init();
    
    /* delay init */
    delay_init();
    
    /* uart1 init */
    uart1_init(115200);
    
    /* shell init && register st7920 fuction */
    shell_init();
    shell_register("st7920", st7920);
    uart1_print("st7920: welcome to libdriver st7920.\n");
    
    while (1)
    {
        /* read uart */
        g_len = uart1_read(g_buf, 256);
        if (g_len)
        {
            /* run shell */
            res = shell_parse((char *)g_buf, g_len);
            if (res == 0)
            {
                /* run success */
            }
            else if (res == 1)
            {
                uart1_print("st7920: run failed.\n");
            }
            else if (res == 2)
            {
                uart1_print("st7920: unknow command.\n");
            }
            else if (res == 3)
            {
                uart1_print("st7920: length is too long.\n");
            }
            else if (res == 4)
            {
                uart1_print("st7920: pretreat failed.\n");
            }
            else if (res == 5)
            {
                uart1_print("st7920: param is invalid.\n");
            }
            else
            {
                uart1_print("st7920: unknow status code.\n");
            }
            uart1_flush();
        }
        delay_ms(100);
    }
}
