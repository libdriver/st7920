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
 * @file      driver_st7920.h
 * @brief     driver st7920 header file
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

#ifndef DRIVER_ST7920_H
#define DRIVER_ST7920_H

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @defgroup st7920_driver st7920 driver function
 * @brief    st7920 driver modules
 * @{
 */

/**
 * @addtogroup st7920_basic_driver
 * @{
 */

/**
 * @brief st7920 bool enumeration definition
 */
typedef enum
{
    ST7920_BOOL_FALSE = 0x00,        /**< false */
    ST7920_BOOL_TRUE  = 0x01,        /**< true */
} st7920_bool_t;

/**
 * @brief st7920 address counter mode enumeration definition
 */
typedef enum
{
    ST7920_ADDRESS_COUNTER_MODE_DECREASE = 0x00,        /**< decrease */
    ST7920_ADDRESS_COUNTER_MODE_INCREASE = 0x01,        /**< increase */
} st7920_address_counter_mode_t;

/**
 * @brief st7920 display shift enumeration definition
 */
typedef enum
{
    ST7920_DISPLAY_SHIFT_RIGHT = 0x00,        /**< cursor moves right */
    ST7920_DISPLAY_SHIFT_LEFT  = 0x01,        /**< cursor moves left */
} st7920_display_shift_t;

/**
 * @brief st7920 display shift mode enumeration definition
 */
typedef enum
{
    ST7920_DISPLAY_SHIFT_MODE_LL = 0x00,        /**< cursor moves left by 1 position */
    ST7920_DISPLAY_SHIFT_MODE_LH = 0x01,        /**< cursor moves right by 1 position */
    ST7920_DISPLAY_SHIFT_MODE_HL = 0x02,        /**< display shift left by 1, cursor also follows to shift */
    ST7920_DISPLAY_SHIFT_MODE_HH = 0x03,        /**< display shift right by 1, cursor also follows to shift */
} st7920_display_shift_mode_t;

/**
 * @brief st7920 interface bus bit enumeration definition
 */
typedef enum
{
    ST7920_INTERFACE_BUS_BIT_4 = 0x00,        /**< 4 bit */
    ST7920_INTERFACE_BUS_BIT_8 = 0x01,        /**< 8 bit */
} st7920_interface_bus_bit_t;

/**
 * @brief st7920 command mode enumeration definition
 */
typedef enum
{
    ST7920_COMMAND_MODE_BASIC    = 0x00,        /**< basic mode */
    ST7920_COMMAND_MODE_EXTENDED = 0x01,        /**< extended mode */
} st7920_command_mode_t;

/**
 * @}
 */

/**
 * @addtogroup st7920_extended_driver
 * @{
 */

/**
 * @brief st7920 reverse line enumeration definition
 */
typedef enum
{
    ST7920_REVERSE_LINE_FIRST  = 0x00,        /**< first line normal or reverse */
    ST7920_REVERSE_LINE_SECOND = 0x01,        /**< second line normal or reverse */
    ST7920_REVERSE_LINE_THIRD  = 0x02,        /**< third line normal or reverse */
    ST7920_REVERSE_LINE_FOURTH = 0x03,        /**< fourth line normal or reverse */
} st7920_reverse_line_t;

/**
 * @}
 */

/**
 * @addtogroup st7920_basic_driver
 * @{
 */

/**
 * @brief st7920 handle structure definition
 */
typedef struct st7920_handle_s
{
    uint8_t (*cs_gpio_init)(void);                          /**< point to a cs_gpio_init function address */
    uint8_t (*cs_gpio_deinit)(void);                        /**< point to a cs_gpio_deinit function address */
    uint8_t (*cs_gpio_write)(uint8_t value);                /**< point to a cs_gpio_write function address */
    uint8_t (*sclk_gpio_init)(void);                        /**< point to a sclk_gpio_init function address */
    uint8_t (*sclk_gpio_deinit)(void);                      /**< point to a sclk_gpio_deinit function address */
    uint8_t (*sclk_gpio_write)(uint8_t value);              /**< point to a sclk_gpio_write function address */
    uint8_t (*sid_gpio_init)(void);                         /**< point to a sid_gpio_init function address */
    uint8_t (*sid_gpio_deinit)(void);                       /**< point to a sid_gpio_deinit function address */
    uint8_t (*sid_gpio_write)(uint8_t value);               /**< point to a sid_gpio_write function address */
    void (*debug_print)(const char *const fmt, ...);        /**< point to a debug_print function address */
    void (*delay_ms)(uint32_t ms);                          /**< point to a delay_ms function address */
    void (*delay_us)(uint32_t us);                          /**< point to a delay_us function address */
    uint8_t basic_extended;                                 /**< basic extended flag */
    uint8_t inited;                                         /**< inited flag */
    uint8_t scroll_address;                                 /**< scroll address */
    uint16_t gram[8][64];                                   /**< gram buffer */
} st7920_handle_t;

/**
 * @brief st7920 information structure definition
 */
typedef struct st7920_info_s
{
    char chip_name[32];                /**< chip name */
    char manufacturer_name[32];        /**< manufacturer name */
    char interface[8];                 /**< chip interface name */
    float supply_voltage_min_v;        /**< chip min supply voltage */
    float supply_voltage_max_v;        /**< chip max supply voltage */
    float max_current_ma;              /**< chip max current */
    float temperature_min;             /**< chip min operating temperature */
    float temperature_max;             /**< chip max operating temperature */
    uint32_t driver_version;           /**< driver version */
} st7920_info_t;

/**
 * @}
 */

/**
 * @defgroup st7920_link_driver st7920 link driver function
 * @brief    st7920 link driver modules
 * @ingroup  st7920_driver
 * @{
 */

/**
 * @brief     initialize st7920_handle_t structure
 * @param[in] HANDLE points to an st7920 handle structure
 * @param[in] STRUCTURE is st7920_handle_t
 * @note      none
 */
#define DRIVER_ST7920_LINK_INIT(HANDLE, STRUCTURE)          memset(HANDLE, 0, sizeof(STRUCTURE))

/**
 * @brief     link cs_gpio_init function
 * @param[in] HANDLE points to an st7920 handle structure
 * @param[in] FUC points to a cs_gpio_init function address
 * @note      none
 */
#define DRIVER_ST7920_LINK_CS_GPIO_INIT(HANDLE, FUC)        (HANDLE)->cs_gpio_init = FUC

/**
 * @brief     link cs_gpio_deinit function
 * @param[in] HANDLE points to an st7920 handle structure
 * @param[in] FUC points to a cs_gpio_deinit function address
 * @note      none
 */
#define DRIVER_ST7920_LINK_CS_GPIO_DEINIT(HANDLE, FUC)      (HANDLE)->cs_gpio_deinit = FUC

/**
 * @brief     link cs_gpio_write function
 * @param[in] HANDLE points to an st7920 handle structure
 * @param[in] FUC points to a cs_gpio_write function address
 * @note      none
 */
#define DRIVER_ST7920_LINK_CS_GPIO_WRITE(HANDLE, FUC)       (HANDLE)->cs_gpio_write = FUC

/**
 * @brief     link sclk_gpio_init function
 * @param[in] HANDLE points to an st7920 handle structure
 * @param[in] FUC points to a sclk_gpio_init function address
 * @note      none
 */
#define DRIVER_ST7920_LINK_SCLK_GPIO_INIT(HANDLE, FUC)      (HANDLE)->sclk_gpio_init = FUC

/**
 * @brief     link sclk_gpio_deinit function
 * @param[in] HANDLE points to an st7920 handle structure
 * @param[in] FUC points to a sclk_gpio_deinit function address
 * @note      none
 */
#define DRIVER_ST7920_LINK_SCLK_GPIO_DEINIT(HANDLE, FUC)    (HANDLE)->sclk_gpio_deinit = FUC

/**
 * @brief     link sclk_gpio_write function
 * @param[in] HANDLE points to an st7920 handle structure
 * @param[in] FUC points to a sclk_gpio_write function address
 * @note      none
 */
#define DRIVER_ST7920_LINK_SCLK_GPIO_WRITE(HANDLE, FUC)     (HANDLE)->sclk_gpio_write = FUC

/**
 * @brief     link sid_gpio_init function
 * @param[in] HANDLE points to an st7920 handle structure
 * @param[in] FUC points to a sid_gpio_init function address
 * @note      none
 */
#define DRIVER_ST7920_LINK_SID_GPIO_INIT(HANDLE, FUC)       (HANDLE)->sid_gpio_init = FUC

/**
 * @brief     link sid_gpio_deinit function
 * @param[in] HANDLE points to an st7920 handle structure
 * @param[in] FUC points to a sid_gpio_deinit function address
 * @note      none
 */
#define DRIVER_ST7920_LINK_SID_GPIO_DEINIT(HANDLE, FUC)     (HANDLE)->sid_gpio_deinit = FUC

/**
 * @brief     link sid_gpio_write function
 * @param[in] HANDLE points to an st7920 handle structure
 * @param[in] FUC points to a sid_gpio_write function address
 * @note      none
 */
#define DRIVER_ST7920_LINK_SID_GPIO_WRITE(HANDLE, FUC)      (HANDLE)->sid_gpio_write = FUC

/**
 * @brief     link debug_print function
 * @param[in] HANDLE points to an st7920 handle structure
 * @param[in] FUC points to a debug_print function address
 * @note      none
 */
#define DRIVER_ST7920_LINK_DEBUG_PRINT(HANDLE, FUC)         (HANDLE)->debug_print = FUC

/**
 * @brief     link delay_ms function
 * @param[in] HANDLE points to an st7920 handle structure
 * @param[in] FUC points to a delay_ms function address
 * @note      none
 */
#define DRIVER_ST7920_LINK_DELAY_MS(HANDLE, FUC)            (HANDLE)->delay_ms = FUC

/**
 * @brief     link delay_us function
 * @param[in] HANDLE points to an st7920 handle structure
 * @param[in] FUC points to a delay_us function address
 * @note      none
 */
#define DRIVER_ST7920_LINK_DELAY_US(HANDLE, FUC)            (HANDLE)->delay_us = FUC

/**
 * @}
 */

/**
 * @defgroup st7920_basic_driver st7920 basic driver function
 * @brief    st7920 basic driver modules
 * @ingroup  st7920_driver
 * @{
 */

/**
 * @brief      get chip's information
 * @param[out] *info points to an st7920 info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t st7920_info(st7920_info_t *info);

/**
 * @brief     initialize the chip
 * @param[in] *handle points to an st7920 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 gpio initialization failed
 *            - 2 handle is NULL
 *            - 3 linked functions is NULL
 * @note      none
 */
uint8_t st7920_init(st7920_handle_t *handle);

/**
 * @brief     close the chip
 * @param[in] *handle points to an st7920 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 deinit failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t st7920_deinit(st7920_handle_t *handle);

/**
 * @brief     show a string
 * @param[in] *handle points to an st7920 handle structure
 * @param[in] x is the coordinate x
 * @param[in] y is the coordinate y
 * @param[in] *str points to a write string address
 * @return    status code
 *            - 0 success
 *            - 1 write string failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 this command must be run in basic command mode
 *            - 5 x is over 3
 *            - 6 y is over 7
 * @note      0 <= x <= 3
 *            0 <= y <= 7
 */
uint8_t st7920_write_string(st7920_handle_t *handle, uint8_t x, uint8_t y, char *str);

/**
 * @brief     clear the display
 * @param[in] *handle points to an st7920 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 display clear failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t st7920_display_clear(st7920_handle_t *handle);

/**
 * @brief     return the home
 * @param[in] *handle points to an st7920 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 return home failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 this command must be run in basic command mode
 * @note      none
 */
uint8_t st7920_return_home(st7920_handle_t *handle);

/**
 * @brief     set the entry mode
 * @param[in] *handle points to an st7920 handle structure
 * @param[in] shift is the display shift
 * @param[in] mode is the address counter mode
 * @return    status code
 *            - 0 success
 *            - 1 set entry mode failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 this command must be run in basic command mode
 * @note      none
 */
uint8_t st7920_set_entry_mode(st7920_handle_t *handle, st7920_display_shift_t shift, st7920_address_counter_mode_t mode);

/**
 * @brief     set the display control
 * @param[in] *handle points to an st7920 handle structure
 * @param[in] display_on is a bool value
 * @param[in] cursor_on is a bool value
 * @param[in] character_blink_on is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set display control failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 this command must be run in basic command mode
 * @note      none
 */
uint8_t st7920_set_display_control(st7920_handle_t *handle, st7920_bool_t display_on, st7920_bool_t cursor_on, st7920_bool_t character_blink_on);

/**
 * @brief     set the display shift mode
 * @param[in] *handle points to an st7920 handle structure
 * @param[in] mode is the display shift mode
 * @return    status code
 *            - 0 success
 *            - 1 set display shift mode failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 this command must be run in basic command mode
 * @note      none
 */
uint8_t st7920_set_display_shift_mode(st7920_handle_t *handle, st7920_display_shift_mode_t mode);

/**
 * @brief     set the function
 * @param[in] *handle points to an st7920 handle structure
 * @param[in] bus_bit is the bus bit
 * @param[in] mode is the command mode
 * @return    status code
 *            - 0 success
 *            - 1 set function failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t st7920_set_function(st7920_handle_t *handle, st7920_interface_bus_bit_t bus_bit, st7920_command_mode_t mode);

/**
 * @brief     set the cgram address
 * @param[in] *handle points to an st7920 handle structure
 * @param[in] addr is the cgram address
 * @return    status code
 *            - 0 success
 *            - 1 set cgram address failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 this command must be run in basic command mode
 *            - 5 addr is over 0x3F
 * @note      0 <= addr <= 0x3F
 */
uint8_t st7920_set_cgram_address(st7920_handle_t *handle, uint8_t addr);

/**
 * @brief     set the ddram address
 * @param[in] *handle points to an st7920 handle structure
 * @param[in] addr is the ddram address
 * @return    status code
 *            - 0 success
 *            - 1 set ddram address failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 this command must be run in basic command mode
 *            - 5 addr is over 0x3F
 * @note      0 <= addr <= 0x7F
 */
uint8_t st7920_set_ddram_address(st7920_handle_t *handle, uint8_t addr);

/**
 * @brief     write the ram
 * @param[in] *handle points to an st7920 handle structure
 * @param[in] *data points to a data buffer
 * @param[in] len is the data length
 * @return    status code
 *            - 0 success
 *            - 1 write ram failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 this command must be run in basic command mode
 * @note      none
 */
uint8_t st7920_write_ram(st7920_handle_t *handle, uint8_t *data, uint8_t len);

/**
 * @}
 */

/**
 * @defgroup st7920_extended_driver st7920 extended driver function
 * @brief    st7920 extended driver modules
 * @ingroup  st7920_driver
 * @{
 */

/**
 * @brief     write a point
 * @param[in] *handle points to an st7920 handle structure
 * @param[in] x is the coordinate x
 * @param[in] y is the coordinate y
 * @param[in] data is the write data
 * @return    status code
 *            - 0 success
 *            - 1 write point failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 this command must be run in extended command mode
 *            - 5 x is over 127
 *            - 6 y is over 63
 * @note      0 <= x <= 127
 *            0 <= y <= 63
 */
uint8_t st7920_write_point(st7920_handle_t *handle, uint8_t x, uint8_t y, uint8_t data);

/**
 * @brief      read a point
 * @param[in]  *handle points to an st7920 handle structure
 * @param[in]  x is the coordinate x
 * @param[in]  y is the coordinate y
 * @param[out] *data points to a data buffer
 * @return     status code
 *             - 0 success
 *             - 1 write point failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 *             - 4 this command must be run in extended command mode
 *             - 5 x is over 127
 *             - 6 y is over 63
 * @note       0 <= x <= 127
 *             0 <= y <= 63
 */
uint8_t st7920_read_point(st7920_handle_t *handle, uint8_t x, uint8_t y, uint8_t *data);

/**
 * @brief     fill a rectangle
 * @param[in] *handle points to an st7920 handle structure
 * @param[in] left is the left coordinate x
 * @param[in] top is the top coordinate y
 * @param[in] right is the right coordinate x
 * @param[in] bottom is the bottom coordinate y
 * @param[in] color is the display color
 * @return    status code
 *            - 0 success
 *            - 1 fill rect failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 this command must be run in extended command mode
 *            - 5 left or top is invalid
 *            - 6 right or bottom is invalid
 *            - 7 left > right or top > bottom
 * @note      none
 */
uint8_t st7920_fill_rect(st7920_handle_t *handle, uint8_t left, uint8_t top, uint8_t right, uint8_t bottom, uint8_t color);

/**
 * @brief     draw a picture
 * @param[in] *handle points to an st7920 handle structure
 * @param[in] left is the left coordinate x
 * @param[in] top is the top coordinate y
 * @param[in] right is the right coordinate x
 * @param[in] bottom is the bottom coordinate y
 * @param[in] *img points to an image buffer
 * @return    status code
 *            - 0 success
 *            - 1 fill rect failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 this command must be run in extended command mode
 *            - 5 left or top is invalid
 *            - 6 right or bottom is invalid
 *            - 7 left > right or top > bottom
 * @note      none
 */
uint8_t st7920_draw_picture(st7920_handle_t *handle, uint8_t left, uint8_t top, uint8_t right, uint8_t bottom, uint8_t *img);

/**
 * @brief     terminate to the standby mode
 * @param[in] *handle points to an st7920 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 set standby failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 this command must be run in extended command mode
 * @note      none
 */
uint8_t st7920_set_standby(st7920_handle_t *handle);

/**
 * @brief     set the vertical scroll
 * @param[in] *handle points to an st7920 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set vertical scroll failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 this command must be run in extended command mode
 * @note      none
 */
uint8_t st7920_set_vertical_scroll(st7920_handle_t *handle, st7920_bool_t enable);

/**
 * @brief     set the reverse line
 * @param[in] *handle points to an st7920 handle structure
 * @param[in] l is the reverse line
 * @return    status code
 *            - 0 success
 *            - 1 set reverse line failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 this command must be run in extended command mode
 * @note      none
 */
uint8_t st7920_set_reverse_line(st7920_handle_t *handle, st7920_reverse_line_t l);

/**
 * @brief     set the extended function
 * @param[in] *handle points to an st7920 handle structure
 * @param[in] bus_bit is the bus bit
 * @param[in] mode is the command mode
 * @param[in] graphic_display_enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set extended function failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t st7920_set_extended_function(st7920_handle_t *handle, st7920_interface_bus_bit_t bus_bit,
                                     st7920_command_mode_t mode, st7920_bool_t graphic_display_enable);

/**
 * @brief     set the scroll address
 * @param[in] *handle points to an st7920 handle structure
 * @param[in] addr is the scroll address
 * @return    status code
 *            - 0 success
 *            - 1 set scroll address failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 this command must be run in extended command mode
 *            - 5 addr is over 0x3F
 * @note      0 <= addr <= 0x3F
 */
uint8_t st7920_set_scroll_address(st7920_handle_t *handle, uint8_t addr);

/**
 * @brief     set the graphic address
 * @param[in] *handle points to an st7920 handle structure
 * @param[in] vertical_addr is the vertical address
 * @param[in] horizontal_addr is the horizontal address
 * @return    status code
 *            - 0 success
 *            - 1 set graphic address failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 this command must be run in extended command mode
 *            - 5 vertical_addr is over 0x3F
 *            - 6 horizontal_addr is over 0xF
 * @note      0 <= vertical_addr <= 0x3F
 *            0 <= horizontal_addr <= 0xF
 */
uint8_t st7920_set_graphic_address(st7920_handle_t *handle, uint8_t vertical_addr, uint8_t horizontal_addr);

/**
 * @}
 */

/**
 * @defgroup st7920_extern_driver st7920 extern driver function
 * @brief    st7920 extern driver modules
 * @ingroup  st7920_driver
 * @{
 */

/**
 * @brief     write command
 * @param[in] *handle points to an st7920 handle structure
 * @param[in] cmd is the write command
 * @return    status code
 *            - 0 success
 *            - 1 write cmd failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t st7920_write_cmd(st7920_handle_t *handle, uint8_t cmd);

/**
 * @brief     write data
 * @param[in] *handle points to an st7920 handle structure
 * @param[in] data is the write data
 * @return    status code
 *            - 0 success
 *            - 1 write data failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t st7920_write_data(st7920_handle_t *handle, uint8_t data);

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
