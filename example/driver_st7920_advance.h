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
 * @file      driver_st7920_advance.h
 * @brief     driver st7920 advance header file
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

#ifndef DRIVER_ST7920_ADVANCE_H
#define DRIVER_ST7920_ADVANCE_H

#include "driver_st7920_interface.h"

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @addtogroup st7920_example_driver
 * @{
 */

/**
 * @brief st7920 advance example default definition
 */
#define ST7920_ADVANCE_DEFAULT_BUS_BIT                 ST7920_INTERFACE_BUS_BIT_8                  /**< 8 bits */
#define ST7920_ADVANCE_DEFAULT_DISPLAY_SHIFT           ST7920_DISPLAY_SHIFT_RIGHT                  /**< shift right */
#define ST7920_ADVANCE_DEFAULT_ADDRESS_COUNTER_MODE    ST7920_ADDRESS_COUNTER_MODE_INCREASE        /**< increase */
#define ST7920_ADVANCE_DEFAULT_DISPLAY_SHIFT_MODE      ST7920_DISPLAY_SHIFT_MODE_LH                /**< cursor moves right by 1 position */

/**
 * @brief  advance example init
 * @return status code
 *         - 0 success
 *         - 1 init failed
 * @note   none
 */
uint8_t st7920_advance_init(void);

/**
 * @brief  advance example deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t st7920_advance_deinit(void);

/**
 * @brief  advance example display on
 * @return status code
 *         - 0 success
 *         - 1 display on failed
 * @note   none
 */
uint8_t st7920_advance_display_on(void);

/**
 * @brief  advance example display off
 * @return status code
 *         - 0 success
 *         - 1 display off failed
 * @note   none
 */
uint8_t st7920_advance_display_off(void);

/**
 * @brief  advance example clear
 * @return status code
 *         - 0 success
 *         - 1 clear failed
 * @note   none
 */
uint8_t st7920_advance_clear(void);

/**
 * @brief     advance example write a point
 * @param[in] x coordinate x
 * @param[in] y coordinate y
 * @param[in] data written data
 * @return    status code
 *            - 0 success
 *            - 1 write point failed
 * @note      none
 */
uint8_t st7920_advance_write_point(uint8_t x, uint8_t y, uint8_t data);

/**
 * @brief      advance example read a point
 * @param[in]  x coordinate x
 * @param[in]  y coordinate y
 * @param[out] *data pointer to a data buffer
 * @return     status code
 *             - 0 success
 *             - 1 read point failed
 * @note       none
 */
uint8_t st7920_advance_read_point(uint8_t x, uint8_t y, uint8_t *data);

/**
 * @brief     advance example write a string
 * @param[in] x coordinate x
 * @param[in] y coordinate y
 * @param[in] *str pointer to a written string address
 * @return    status code
 *            - 0 success
 *            - 1 write string failed
 * @note      none
 */
uint8_t st7920_advance_string(uint8_t x, uint8_t y, char *str);

/**
 * @brief     advance example fill a rectangle
 * @param[in] left left coordinate x
 * @param[in] top top coordinate y
 * @param[in] right right coordinate x
 * @param[in] bottom bottom coordinate y
 * @param[in] color display color
 * @return    status code
 *            - 0 success
 *            - 1 fill rect failed
 * @note      none
 */
uint8_t st7920_advance_rect(uint8_t left, uint8_t top, uint8_t right, uint8_t bottom, uint8_t color);

/**
 * @brief     advance example draw a picture
 * @param[in] left left coordinate x
 * @param[in] top top coordinate y
 * @param[in] right right coordinate x
 * @param[in] bottom bottom coordinate y
 * @param[in] *img pointer to a image buffer
 * @return    status code
 *            - 0 success
 *            - 1 draw picture failed
 * @note      none
 */
uint8_t st7920_advance_picture(uint8_t left, uint8_t top, uint8_t right, uint8_t bottom, uint8_t *img);

/**
 * @brief     advance example set scroll
 * @param[in] addr scroll address
 * @return    status code
 *            - 0 success
 *            - 1 set scroll failed
 * @note      0 <= addr <= 0x3F
 */
uint8_t st7920_advance_set_scroll(uint8_t addr);

/**
 * @brief  advance example enable scroll
 * @return status code
 *         - 0 success
 *         - 1 enable scroll failed
 * @note   none
 */
uint8_t st7920_advance_enable_scroll(void);

/**
 * @brief  advance example disable scroll
 * @return status code
 *         - 0 success
 *         - 1 disable scroll failed
 * @note   none
 */
uint8_t st7920_advance_disable_scroll(void);

/**
 * @brief     advance example set reverse line
 * @param[in] l reverse line
 * @return    status code
 *            - 0 success
 *            - 1 set reverse line failed
 * @note      none
 */
uint8_t st7920_advance_set_reverse_line(st7920_reverse_line_t l);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
