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
 * @file      driver_st7920_basic.h
 * @brief     driver st7920 basic header file
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

#ifndef _DRIVER_ST7920_BASIC_H_
#define _DRIVER_ST7920_BASIC_H_

#include "driver_st7920_interface.h"

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @defgroup st7920_example_driver st7920 example driver function
 * @brief    st7920 example driver modules
 * @ingroup  st7920_driver
 * @{
 */

/**
 * @brief st7920 basic example default definition
 */
#define ST7920_BASIC_DEFAULT_BUS_BIT                 ST7920_INTERFACE_BUS_BIT_8                  /**< 8 bits */
#define ST7920_BASIC_DEFAULT_DISPLAY_SHIFT           ST7920_DISPLAY_SHIFT_RIGHT                  /**< shift right */
#define ST7920_BASIC_DEFAULT_ADDRESS_COUNTER_MODE    ST7920_ADDRESS_COUNTER_MODE_INCREASE        /**< increase */
#define ST7920_BASIC_DEFAULT_DISPLAY_SHIFT_MODE      ST7920_DISPLAY_SHIFT_MODE_LH                /**< cursor moves right by 1 position */

/**
 * @brief  basic example init
 * @return status code
 *         - 0 success
 *         - 1 init failed
 * @note   none
 */
uint8_t st7920_basic_init(void);

/**
 * @brief  basic example deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t st7920_basic_deinit(void);

/**
 * @brief  basic example display on
 * @return status code
 *         - 0 success
 *         - 1 display on failed
 * @note   none
 */
uint8_t st7920_basic_display_on(void);

/**
 * @brief  basic example display off
 * @return status code
 *         - 0 success
 *         - 1 display off failed
 * @note   none
 */
uint8_t st7920_basic_display_off(void);

/**
 * @brief  basic example clear
 * @return status code
 *         - 0 success
 *         - 1 clear failed
 * @note   none
 */
uint8_t st7920_basic_clear(void);

/**
 * @brief     basic example write a point
 * @param[in] x is the coordinate x
 * @param[in] y is the coordinate y
 * @param[in] data is the written data
 * @return    status code
 *            - 0 success
 *            - 1 write point failed
 * @note      none
 */
uint8_t st7920_basic_write_point(uint8_t x, uint8_t y, uint8_t data);

/**
 * @brief      basic example read a point
 * @param[in]  x is the coordinate x
 * @param[in]  y is the coordinate y
 * @param[out] *data points to a data buffer
 * @return     status code
 *             - 0 success
 *             - 1 read point failed
 * @note       none
 */
uint8_t st7920_basic_read_point(uint8_t x, uint8_t y, uint8_t *data);

/**
 * @brief     basic example write a string
 * @param[in] x is the coordinate x
 * @param[in] y is the coordinate y
 * @param[in] *str points to a written string address
 * @return    status code
 *            - 0 success
 *            - 1 write string failed
 * @note      none
 */
uint8_t st7920_basic_string(uint8_t x, uint8_t y, char *str);

/**
 * @brief     basic example fill a rectangle
 * @param[in] left is the left coordinate x
 * @param[in] top is the top coordinate y
 * @param[in] right is the right coordinate x
 * @param[in] bottom is the bottom coordinate y
 * @param[in] color is the display color
 * @return    status code
 *            - 0 success
 *            - 1 fill rect failed
 * @note      none
 */
uint8_t st7920_basic_rect(int8_t left, uint8_t top, uint8_t right, uint8_t bottom, uint8_t color);

/**
 * @brief     basic example draw a picture
 * @param[in] left is the left coordinate x
 * @param[in] top is the top coordinate y
 * @param[in] right is the right coordinate x
 * @param[in] bottom is the bottom coordinate y
 * @param[in] *img points to a image buffer
 * @return    status code
 *            - 0 success
 *            - 1 draw picture failed
 * @note      none
 */
uint8_t st7920_basic_picture(int8_t left, uint8_t top, uint8_t right, uint8_t bottom, uint8_t *img);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
