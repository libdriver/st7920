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
#include "getopt.h"
#include <stdlib.h>

/**
 * @brief global var definition
 */
uint8_t g_buf[256];        /**< uart buffer */
volatile uint16_t g_len;   /**< uart buffer length */

/**
 * @brief     st7920 full function
 * @param[in] argc arg numbers
 * @param[in] **argv arg address
 * @return    status code
 *             - 0 success
 *             - 1 run failed
 *             - 5 param is invalid
 * @note      none
 */
uint8_t st7920(uint8_t argc, char **argv)
{
    int c;
    int longindex = 0;
    const char short_options[] = "hipe:t:";
    const struct option long_options[] =
    {
        {"help", no_argument, NULL, 'h'},
        {"information", no_argument, NULL, 'i'},
        {"port", no_argument, NULL, 'p'},
        {"example", required_argument, NULL, 'e'},
        {"test", required_argument, NULL, 't'},
        {"color", required_argument, NULL, 1},
        {"line", required_argument, NULL, 2},
        {"scroll", required_argument, NULL, 3},
        {"str", required_argument, NULL, 4},
        {"x0", required_argument, NULL, 5},
        {"x1", required_argument, NULL, 6},
        {"x2", required_argument, NULL, 7},
        {"y0", required_argument, NULL, 8},
        {"y1", required_argument, NULL, 9},
        {"y2", required_argument, NULL, 10},
        {NULL, 0, NULL, 0},
    };
    char type[33] = "unknow";
    uint8_t color = 1;
    uint8_t line = 16;
    uint8_t scroll = 1;
    uint8_t x0 = 0;
    uint8_t x1 = 0;
    uint8_t x2 = 0;
    uint8_t y0 = 0;
    uint8_t y1 = 0;
    uint8_t y2 = 0;
    uint8_t x0_flag = 0;
    uint8_t x1_flag = 0;
    uint8_t x2_flag = 0;
    uint8_t y0_flag = 0;
    uint8_t y1_flag = 0;
    uint8_t y2_flag = 0;
    char str[49] = "libdriver";
    
    /* if no params */
    if (argc == 1)
    {
        /* goto the help */
        goto help;
    }
    
    /* init 0 */
    optind = 0;
    
    /* parse */
    do
    {
        /* parse the args */
        c = getopt_long(argc, argv, short_options, long_options, &longindex);
        
        /* judge the result */
        switch (c)
        {
            /* help */
            case 'h' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "h");
                
                break;
            }
            
            /* information */
            case 'i' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "i");
                
                break;
            }
            
            /* port */
            case 'p' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "p");
                
                break;
            }
            
            /* example */
            case 'e' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "e_%s", optarg);
                
                break;
            }
            
            /* test */
            case 't' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "t_%s", optarg);
                
                break;
            }
            
            /* color */
            case 1 :
            {
                /* set the color */
                color = atol(optarg);
                
                break;
            }
            
            /* line */
            case 2 :
            {
                /* set the line */
                line = atol(optarg);
                
                break;
            }
            
            /* scroll */
            case 3 :
            {
                /* set the scroll */
                scroll = atol(optarg);
                
                break;
            }
            
            /* str */
            case 4 :
            {
                /* set the str */
                memset(str, 0, sizeof(char) * 49);
                strncpy(str, optarg, 48);
                
                break;
            }
            
            /* x0 */
            case 5 :
            {
                /* convert */
                x0 = atol(optarg);
                x0_flag = 1;
                
                break;
            }
            
            /* x1 */
            case 6 :
            {
                /* convert */
                x1 = atol(optarg);
                x1_flag = 1;
                
                break;
            }
            
            /* x2 */
            case 7 :
            {
                /* convert */
                x2 = atol(optarg);
                x2_flag = 1;
                
                break;
            }
            /* y0 */
            case 8 :
            {
                /* convert */
                y0 = atol(optarg);
                y0_flag = 1;
                
                break;
            }
            
            /* y1 */
            case 9 :
            {
                /* convert */
                y1 = atol(optarg);
                y1_flag = 1;
                
                break;
            }
            
            /* y2 */
            case 10 :
            {
                /* convert */
                y2 = atol(optarg);
                y2_flag = 1;
                
                break;
            }
            
            /* the end */
            case -1 :
            {
                break;
            }
            
            /* others */
            default :
            {
                return 5;
            }
        }
    } while (c != -1);
    
    /* run the function */
    if (strcmp("t_display", type) == 0)
    {
        /* run display test */
        if (st7920_display_test() != 0)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else if (strcmp("e_basic-str", type) == 0)
    {
        uint8_t res;

        /* basic clear */
        res = st7920_basic_clear();
        if (res != 0)
        {
            st7920_interface_debug_print("st7920: clear screen failed.\n");
            (void)st7920_basic_deinit();
            
            return 1;
        }

        /* basic string */
        res = st7920_basic_string(0, 0, str);
        if (res != 0)
        {
            st7920_interface_debug_print("st7920: show string failed.\n");
            (void)st7920_basic_deinit();
            
            return 1;
        }

        /* output */
        st7920_interface_debug_print("st7920: %s.\n", str);
        
        return 0;
    }
    else if (strcmp("e_basic-init", type) == 0)
    {
        uint8_t res;

        /* basic init */
        res = st7920_basic_init();
        if (res != 0)
        {
            st7920_interface_debug_print("st7920: init failed.\n");
            
            return 1;
        }

        /* output */
        st7920_interface_debug_print("st7920: init success.\n");
        
        return 0;
    }
    else if (strcmp("e_basic-display-off", type) == 0)
    {
        uint8_t res;

        /* basic display off */
        res = st7920_basic_display_off();
        if (res != 0)
        {
            st7920_interface_debug_print("st7920: display off failed.\n");
            (void)st7920_basic_deinit();
            
            return 1;
        }

        /* output */
        st7920_interface_debug_print("st7920: display off.\n");
        
        return 0;
    }
    else if (strcmp("e_basic-display-on", type) == 0)
    {
        uint8_t res;

        /* basic display on */
        res = st7920_basic_display_on();
        if (res != 0)
        {
            st7920_interface_debug_print("st7920: display on failed.\n");
            (void)st7920_basic_deinit();
            
            return 1;
        }

        /* output */
        st7920_interface_debug_print("st7920: display on.\n");
        
        return 0;
    }
    else if (strcmp("e_basic-clear", type) == 0)
    {
        uint8_t res;

        /* basic clear */
        res = st7920_basic_clear();
        if (res != 0)
        {
            st7920_interface_debug_print("st7920: clear screen failed.\n");
            (void)st7920_basic_deinit();
            
            return 1;
        }

        /* output */
        st7920_interface_debug_print("st7920: clear screen.\n");
        
        return 0;
    }
    else if (strcmp("e_basic-deinit", type) == 0)
    {
        uint8_t res;

        /* basic deinit */
        res = st7920_basic_deinit();
        if (res != 0)
        {
            st7920_interface_debug_print("st7920: deinit failed.\n");
            
            return 1;
        }

        /* output */
        st7920_interface_debug_print("st7920: deinit st7920.\n");
        
        return 0;
    }
    else if (strcmp("e_basic-point", type) == 0)
    {
        uint8_t res;
        
        /* check the params */
        if ((x0_flag != 1) || (y0_flag != 1))
        {
            return 5;
        }

        /* write point */
        res = st7920_basic_write_point(x0, y0, color);
        if (res != 0)
        {
            (void)st7920_basic_deinit();
            
            return 1;
        }

        /* output */
        st7920_interface_debug_print("st7920: write point %d %d %d.\n", x0, y0, color);
        
        return 0;
    }
    else if (strcmp("e_basic-rect", type) == 0)
    {
        uint8_t res;
        
        /* check the params */
        if ((x1_flag != 1) || (y1_flag != 1) || (x2_flag != 1) || (y2_flag != 1))
        {
            return 5;
        }

        /* basic rect */
        res = st7920_basic_rect(x1, y1, x2, y2, color);
        if (res != 0)
        {
            (void)st7920_basic_deinit();
            
            return 1;
        }

        /* output */
        st7920_interface_debug_print("st7920: draw rect %d %d %d %d.\n", x1, y1, x2, y2);
        
        return 0;
    }
    else if (strcmp("e_advance-init", type) == 0)
    {
        uint8_t res;

        /* advance init */
        res = st7920_advance_init();
        if (res != 0)
        {
            st7920_interface_debug_print("st7920: init failed.\n");
            
            return 1;
        }

        /* output */
        st7920_interface_debug_print("st7920: init success.\n");
        
        return 0;
    }
    else if (strcmp("e_advance-str", type) == 0)
    {
        uint8_t res;

        /* advance clear */
        res = st7920_advance_clear();
        if (res != 0)
        {
            st7920_interface_debug_print("st7920: clear screen failed.\n");
            (void)st7920_advance_deinit();
            
            return 1;
        }

        /* advance string */
        res = st7920_advance_string(0, 0, str);
        if (res != 0)
        {
            st7920_interface_debug_print("st7920: show string failed.\n");
            (void)st7920_advance_deinit();
            
            return 1;
        }

        /* output */
        st7920_interface_debug_print("st7920: %s.\n", str);
        
        return 0;
    }
    else if (strcmp("e_advance-display-off", type) == 0)
    {
        uint8_t res;

        /* advance display off */
        res = st7920_advance_display_off();
        if (res != 0)
        {
            st7920_interface_debug_print("st7920: display off failed.\n");
            (void)st7920_advance_deinit();
            
            return 1;
        }

        /* output */
        st7920_interface_debug_print("st7920: display off.\n");
        
        return 0;
    }
    else if (strcmp("e_advance-display-on", type) == 0)
    {
        uint8_t res;

        /* advance display on */
        res = st7920_advance_display_on();
        if (res != 0)
        {
            st7920_interface_debug_print("st7920: display on failed.\n");
            (void)st7920_advance_deinit();
            
            return 1;
        }

        /* output */
        st7920_interface_debug_print("st7920: display on.\n");
        
        return 0;
    }
    else if (strcmp("e_advance-clear", type) == 0)
    {
        uint8_t res;

        /* advance clear */
        res = st7920_advance_clear();
        if (res != 0)
        {
            st7920_interface_debug_print("st7920: clear screen failed.\n");
            (void)st7920_advance_deinit();
            
            return 1;
        }

        /* output */
        st7920_interface_debug_print("st7920: clear screen.\n");
        
        return 0;
    }
    else if (strcmp("e_advance-point", type) == 0)
    {
        uint8_t res;
        
        /* check the params */
        if ((x0_flag != 1) || (y0_flag != 1))
        {
            return 5;
        }

        /* advance write */
        res = st7920_advance_write_point(x0, y0, color);
        if (res != 0)
        {
            (void)st7920_advance_deinit();
            
            return 1;
        }

        /* output */
        st7920_interface_debug_print("st7920: write point %d %d %d.\n", x0, y0, color);
        
        return 0;
    }
    else if (strcmp("e_advance-rect", type) == 0)
    {
        uint8_t res;

        /* check the params */
        if ((x1_flag != 1) || (y1_flag != 1) || (x2_flag != 1) || (y2_flag != 1))
        {
            return 5;
        }

        /* advance rect */
        res = st7920_advance_rect(x1, y1, x2, y2, color);
        if (res != 0)
        {
            (void)st7920_advance_deinit();
            
            return 1;
        }

        /* output */
        st7920_interface_debug_print("st7920: draw rect %d %d %d %d.\n", x1, y1, x2, y2);
        
        return 0;
    }
    else if (strcmp("e_advance-deinit", type) == 0)
    {
        uint8_t res;

        /* advance deinit */
        res = st7920_advance_deinit();
        if (res != 0)
        {
            st7920_interface_debug_print("st7920: deinit failed.\n");
            
            return 1;
        }

        /* output */
        st7920_interface_debug_print("st7920: deinit st7920.\n");
        
        return 0;
    }
    else if (strcmp("e_advance-disable-scroll", type) == 0)
    {
        uint8_t res;

        /* advance disable scroll */
        res = st7920_advance_disable_scroll();
        if (res != 0)
        {
            st7920_interface_debug_print("st7920: disable scroll failed.\n");
            
            return 1;
        }

        /* output */
        st7920_interface_debug_print("st7920: disable scroll.\n");
        
        return 0;
    }
    else if (strcmp("e_advance-scroll", type) == 0)
    {
        uint8_t res;

        /* enable scroll */
        res = st7920_advance_enable_scroll();
        if (res != 0)
        {
            (void)st7920_advance_deinit();
            
            return 1;
        }
        
        /* set scroll */
        res = st7920_advance_set_scroll(scroll);
        if (res != 0)
        {
            st7920_interface_debug_print("st7920: set scroll failed.\n");
            (void)st7920_advance_deinit();
            
            return 1;
        }
        
        /* output */
        st7920_interface_debug_print("st7920: set scroll %d.\n", scroll);
        
        return 0;
    }
    else if (strcmp("e_advance-reverse-line", type) == 0)
    {
        uint8_t res;

        /* set reverse line */
        res = st7920_advance_set_reverse_line((st7920_reverse_line_t)(line));
        if (res != 0)
        {
            (void)st7920_advance_deinit();
            
            return 1;
        }
        
        /* output */
        st7920_interface_debug_print("st7920: set reverse line %d.\n", line);
        
        return 0;
    }
    else if (strcmp("h", type) == 0)
    {
        help:
        st7920_interface_debug_print("Usage:\n");
        st7920_interface_debug_print("  st7920 (-i | --information)\n");
        st7920_interface_debug_print("  st7920 (-h | --help)\n");
        st7920_interface_debug_print("  st7920 (-p | --port)\n");
        st7920_interface_debug_print("  st7920 (-t display | --test=display)\n");
        st7920_interface_debug_print("  st7920 (-e basic-init | --example=basic-init)\n");
        st7920_interface_debug_print("  st7920 (-e basic-deinit | --example=basic-deinit)\n");
        st7920_interface_debug_print("  st7920 (-e basic-str | --example=basic-str) [--str=<string>]\n");
        st7920_interface_debug_print("  st7920 (-e basic-display-on | --example=basic-display-on)\n");
        st7920_interface_debug_print("  st7920 (-e basic-display-off | --example=basic-display-off)\n");
        st7920_interface_debug_print("  st7920 (-e basic-clear | --example=basic-clear)\n");
        st7920_interface_debug_print("  st7920 (-e basic-point | --example=basic-point) --x0=<x0> --y0=<y0> [--color=<0 | 1>]\n");
        st7920_interface_debug_print("  st7920 (-e basic-rect | --example=basic-rect) --x1=<x1> --y1=<y1> --x2=<x2> --y2=<y2> [--color=<0 | 1>]\n");
        st7920_interface_debug_print("  st7920 (-e advance-init | --example=advance-init)\n");
        st7920_interface_debug_print("  st7920 (-e advance-deinit | --example=advance-deinit)\n");
        st7920_interface_debug_print("  st7920 (-e advance-str | --example=advance-str) [--str=<string>]\n");
        st7920_interface_debug_print("  st7920 (-e advance-display-on | --example=advance-display-on)\n");
        st7920_interface_debug_print("  st7920 (-e advance-display-off | --example=advance-display-off)\n");
        st7920_interface_debug_print("  st7920 (-e advance-clear | --example=advance-clear)\n");
        st7920_interface_debug_print("  st7920 (-e advance-point | --example=advance-point) --x0=<x0> --y0=<y0> [--color=<0 | 1>]\n");
        st7920_interface_debug_print("  st7920 (-e advance-rect | --example=advance-rect) --x1=<x1> --y1=<y1> --x2=<x2> --y2=<y2> [--color=<0 | 1>]\n");
        st7920_interface_debug_print("  st7920 (-e advance-disable-scroll | --example=advance-disable-scroll)\n");
        st7920_interface_debug_print("  st7920 (-e advance-scroll | --example=advance-scroll) [--scroll=<addr>]\n");
        st7920_interface_debug_print("  st7920 (-e advance-reverse-line | --example=advance-reverse-line) [--line=<0 | 1>]\n");
        st7920_interface_debug_print("\n");
        st7920_interface_debug_print("Options:\n");
        st7920_interface_debug_print("      --color=<0 | 1>     Set the chip color.([default: 1])\n");
        st7920_interface_debug_print("  -e <basic-init | basic-deinit | basic-str | basic-display-on | basic-display-off | basic-clear\n");
        st7920_interface_debug_print("     | basic-point | basic-rect>, --example=<advance-init | advance-deinit | advance-str | advance-display-on\n");
        st7920_interface_debug_print("     | advance-display-off | advance-clear | advance-point | advance-rect | advance-disable-scroll\n");
        st7920_interface_debug_print("     | advance-scroll | advance-reverse-line>\n");
        st7920_interface_debug_print("                          Run the driver example.\n");
        st7920_interface_debug_print("  -h, --help              Show the help.\n");
        st7920_interface_debug_print("  -i, --information       Show the chip information.\n");
        st7920_interface_debug_print("      --line=<0 | 1>      Set the reverse line.([default: 0])\n");
        st7920_interface_debug_print("  -p, --port              Display the pin connections of the current board.\n");
        st7920_interface_debug_print("      --scroll            Set the scrolling address and 0 <= scroll <= 63.([default: 16])\n");
        st7920_interface_debug_print("      --str=<string>      Set the display string.([default: libdriver])\n");
        st7920_interface_debug_print("  -t <display>, --test=<display>\n");
        st7920_interface_debug_print("                          Run the driver test.\n");
        st7920_interface_debug_print("      --x0=<x0>           Set the x0 and it is the x of the point.\n");
        st7920_interface_debug_print("      --x1=<x1>           Set the x1 and it is the top left x of the rect.\n");
        st7920_interface_debug_print("      --x2=<x2>           Set the x2 and it is the bottom right x of the rect.\n");
        st7920_interface_debug_print("      --y0=<y0>           Set the y0 and it is the y of the point.\n");
        st7920_interface_debug_print("      --y1=<y1>           Set the y1 and it is the top left y of the rect.\n");
        st7920_interface_debug_print("      --y2=<y2>           Set the y2 and it is the bottom right y of the rect.\n");
        
        return 0;
    }
    else if (strcmp("i", type) == 0)
    {
        st7920_info_t info;
        
        /* print st7920 info */
        st7920_info(&info);
        st7920_interface_debug_print("st7920: chip is %s.\n", info.chip_name);
        st7920_interface_debug_print("st7920: manufacturer is %s.\n", info.manufacturer_name);
        st7920_interface_debug_print("st7920: interface is %s.\n", info.interface);
        st7920_interface_debug_print("st7920: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        st7920_interface_debug_print("st7920: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        st7920_interface_debug_print("st7920: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        st7920_interface_debug_print("st7920: max current is %0.2fmA.\n", info.max_current_ma);
        st7920_interface_debug_print("st7920: max temperature is %0.1fC.\n", info.temperature_max);
        st7920_interface_debug_print("st7920: min temperature is %0.1fC.\n", info.temperature_min);
        
        return 0;
    }
    else if (strcmp("p", type) == 0)
    {
        /* print pin connection */
        st7920_interface_debug_print("st7920: RS connected to GPIOB PIN1.\n");
        st7920_interface_debug_print("st7920: RW connected to GPIOA PIN8.\n");
        st7920_interface_debug_print("st7920: E connected to GPIOA PIN0.\n");
        st7920_interface_debug_print("st7920: PSB connected to GND.\n");
        
        return 0;
    }
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
    uint8_t res;
    
    /* stm32f407 clock init and hal init */
    clock_init();
    
    /* delay init */
    delay_init();
    
    /* uart init */
    uart_init(115200);
    
    /* shell init && register st7920 fuction */
    shell_init();
    shell_register("st7920", st7920);
    uart_print("st7920: welcome to libdriver st7920.\n");
    
    while (1)
    {
        /* read uart */
        g_len = uart_read(g_buf, 256);
        if (g_len != 0)
        {
            /* run shell */
            res = shell_parse((char *)g_buf, g_len);
            if (res == 0)
            {
                /* run success */
            }
            else if (res == 1)
            {
                uart_print("st7920: run failed.\n");
            }
            else if (res == 2)
            {
                uart_print("st7920: unknow command.\n");
            }
            else if (res == 3)
            {
                uart_print("st7920: length is too long.\n");
            }
            else if (res == 4)
            {
                uart_print("st7920: pretreat failed.\n");
            }
            else if (res == 5)
            {
                uart_print("st7920: param is invalid.\n");
            }
            else
            {
                uart_print("st7920: unknow status code.\n");
            }
            uart_flush();
        }
        delay_ms(100);
    }
}
