/**
 *Copyright (c) 2015 - present LibDriver All rights reserved
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
 * @file      stm32f407_driver_st7920_interface.c
 * @brief     stm32f407 driver st7920 interface source file
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

#include "driver_st7920_interface.h"
#include "delay.h"
#include "uart.h"
#include "wire.h"
#include <stdarg.h>

/**
 * @brief  interface cs gpio init
 * @return status code
 *         - 0 success
 *         - 1 init failed
 * @note   none
 */
uint8_t st7920_interface_cs_gpio_init(void)
{
    return wire_cs_init();
}

/**
 * @brief  interface cs gpio deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t st7920_interface_cs_gpio_deinit(void)
{
    return wire_cs_deinit();
}

/**
 * @brief     interface cs gpio write
 * @param[in] value is the written value
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 * @note      none
 */
uint8_t st7920_interface_cs_gpio_write(uint8_t value)
{
    return wire_cs_write(value);
}

/**
 * @brief  interface sclk gpio init
 * @return status code
 *         - 0 success
 *         - 1 init failed
 * @note   none
 */
uint8_t st7920_interface_sclk_gpio_init(void)
{
    return wire_clock_init();
}

/**
 * @brief  interface sclk gpio deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t st7920_interface_sclk_gpio_deinit(void)
{
    return wire_clock_deinit();
}

/**
 * @brief     interface sclk gpio write
 * @param[in] value is the written value
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 * @note      none
 */
uint8_t st7920_interface_sclk_gpio_write(uint8_t value)
{
    return wire_clock_write(value);
}

/**
 * @brief  interface sid gpio init
 * @return status code
 *         - 0 success
 *         - 1 init failed
 * @note   none
 */
uint8_t st7920_interface_sid_gpio_init(void)
{
    return wire_init();
}

/**
 * @brief  interface sid gpio deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t st7920_interface_sid_gpio_deinit(void)
{
    return wire_deinit();
}

/**
 * @brief     interface sid gpio write
 * @param[in] value is the written value
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 * @note      none
 */
uint8_t st7920_interface_sid_gpio_write(uint8_t value)
{
    return wire_write(value);
}

/**
 * @brief     interface delay ms
 * @param[in] ms
 * @note      none
 */
void st7920_interface_delay_ms(uint32_t ms)
{
    delay_ms(ms);
}

/**
 * @brief     interface delay us
 * @param[in] us
 * @note      none
 */
void st7920_interface_delay_us(uint32_t us)
{
    delay_us(us);
}

/**
 * @brief     interface print format data
 * @param[in] fmt is the format data
 * @return    length of the send data
 * @note      none
 */
uint16_t st7920_interface_debug_print(char *fmt, ...)
{
    volatile char str[256];
    volatile uint8_t len;
    va_list args;
    
    memset((char *)str, 0, sizeof(char) * 256); 
    va_start(args, fmt);
    vsnprintf((char *)str, 256, (char const *)fmt, args);
    va_end(args);
        
    len = strlen((char *)str);
    if (uart1_write((uint8_t *)str, len))
    {
        return 0;
    }
    else
    { 
        return len;
    }
}
