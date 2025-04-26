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
 * @file      driver_st7920_basic.c
 * @brief     driver st7920 basic source file
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

static st7920_handle_t gs_handle;        /**< st7920 handle */

/**
 * @brief  basic example init
 * @return status code
 *         - 0 success
 *         - 1 init failed
 * @note   none
 */
uint8_t st7920_basic_init(void)
{
    uint8_t res;
    
    /* link functions */
    DRIVER_ST7920_LINK_INIT(&gs_handle, st7920_handle_t);
    DRIVER_ST7920_LINK_CS_GPIO_INIT(&gs_handle, st7920_interface_cs_gpio_init);
    DRIVER_ST7920_LINK_CS_GPIO_DEINIT(&gs_handle, st7920_interface_cs_gpio_deinit);
    DRIVER_ST7920_LINK_CS_GPIO_WRITE(&gs_handle, st7920_interface_cs_gpio_write);
    DRIVER_ST7920_LINK_SCLK_GPIO_INIT(&gs_handle, st7920_interface_sclk_gpio_init);
    DRIVER_ST7920_LINK_SCLK_GPIO_DEINIT(&gs_handle, st7920_interface_sclk_gpio_deinit);
    DRIVER_ST7920_LINK_SCLK_GPIO_WRITE(&gs_handle, st7920_interface_sclk_gpio_write);
    DRIVER_ST7920_LINK_SID_GPIO_INIT(&gs_handle, st7920_interface_sid_gpio_init);
    DRIVER_ST7920_LINK_SID_GPIO_DEINIT(&gs_handle, st7920_interface_sid_gpio_deinit);
    DRIVER_ST7920_LINK_SID_GPIO_WRITE(&gs_handle, st7920_interface_sid_gpio_write);
    DRIVER_ST7920_LINK_DEBUG_PRINT(&gs_handle, st7920_interface_debug_print);
    DRIVER_ST7920_LINK_DELAY_MS(&gs_handle, st7920_interface_delay_ms);
    DRIVER_ST7920_LINK_DELAY_US(&gs_handle, st7920_interface_delay_us);
    
    /* st7920 init */
    res = st7920_init(&gs_handle);
    if (res != 0)
    {
        st7920_interface_debug_print("st7920: init failed.\n");
        
        return 1;
    }
    
    /* set basic function */
    res = st7920_set_function(&gs_handle, ST7920_BASIC_DEFAULT_BUS_BIT, ST7920_COMMAND_MODE_BASIC);
    if (res != 0)
    {
        st7920_interface_debug_print("st7920: set function failed.\n");
        (void)st7920_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set entry mode */
    res = st7920_set_entry_mode(&gs_handle, ST7920_BASIC_DEFAULT_DISPLAY_SHIFT, ST7920_BASIC_DEFAULT_ADDRESS_COUNTER_MODE);
    if (res != 0)
    {
        st7920_interface_debug_print("st7920: set entry mode failed.\n");
        (void)st7920_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set display shift mode */
    res = st7920_set_display_shift_mode(&gs_handle, ST7920_BASIC_DEFAULT_DISPLAY_SHIFT_MODE);
    if (res != 0)
    {
        st7920_interface_debug_print("st7920: set display shift mode failed.\n");
        (void)st7920_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set cgram address */
    res = st7920_set_cgram_address(&gs_handle, 0x00);
    if (res != 0)
    {
        st7920_interface_debug_print("st7920: set cgram address failed.\n");
        (void)st7920_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set ddram address */
    res = st7920_set_ddram_address(&gs_handle, 0x00);
    if (res != 0)
    {
        st7920_interface_debug_print("st7920: set ddram address failed.\n");
        (void)st7920_deinit(&gs_handle);
        
        return 1;
    }
    
    /* display clear */
    res = st7920_display_clear(&gs_handle);
    if (res != 0)
    {
        st7920_interface_debug_print("st7920: display clear failed.\n");
        (void)st7920_deinit(&gs_handle);
        
        return 1;
    }
    
    /* return home */
    res = st7920_return_home(&gs_handle);
    if (res != 0)
    {
        st7920_interface_debug_print("st7920: return home failed.\n");
        (void)st7920_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set display control */
    res = st7920_set_display_control(&gs_handle, ST7920_BOOL_TRUE, ST7920_BOOL_FALSE, ST7920_BOOL_FALSE);
    if (res != 0)
    {
        st7920_interface_debug_print("st7920: set display control failed.\n");
        (void)st7920_deinit(&gs_handle);
        
        return 1;
    }
    
    return 0;
}

/**
 * @brief  basic example deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t st7920_basic_deinit(void)
{
    /* deinit st7920 */
    if (st7920_deinit(&gs_handle) != 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief  basic example display on
 * @return status code
 *         - 0 success
 *         - 1 display on failed
 * @note   none
 */
uint8_t st7920_basic_display_on(void)
{
    uint8_t res;
    
    /* set basic function */
    res = st7920_set_function(&gs_handle, ST7920_BASIC_DEFAULT_BUS_BIT, ST7920_COMMAND_MODE_BASIC);
    if (res != 0)
    {
        return 1;
    }
    
    /* set display control */
    res = st7920_set_display_control(&gs_handle, ST7920_BOOL_TRUE, ST7920_BOOL_FALSE, ST7920_BOOL_FALSE);
    if (res != 0)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief  basic example display off
 * @return status code
 *         - 0 success
 *         - 1 display off failed
 * @note   none
 */
uint8_t st7920_basic_display_off(void)
{
    uint8_t res;
    
    /* set basic function */
    res = st7920_set_function(&gs_handle, ST7920_BASIC_DEFAULT_BUS_BIT, ST7920_COMMAND_MODE_BASIC);
    if (res != 0)
    {
        return 1;
    }
    
    /* set display control */
    res = st7920_set_display_control(&gs_handle, ST7920_BOOL_FALSE, ST7920_BOOL_FALSE, ST7920_BOOL_FALSE);
    if (res != 0)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief  basic example clear
 * @return status code
 *         - 0 success
 *         - 1 clear failed
 * @note   none
 */
uint8_t st7920_basic_clear(void)
{
    uint8_t res;
    
    /* display clear */
    res = st7920_display_clear(&gs_handle);
    if (res != 0)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief  basic example clear string
 * @return status code
 *         - 0 success
 *         - 1 clear failed
 * @note   none
 */
uint8_t st7920_basic_clear_string(void)
{
    uint8_t res;
    
    /* set basic function */
    res = st7920_set_function(&gs_handle, ST7920_INTERFACE_BUS_BIT_8, ST7920_COMMAND_MODE_BASIC);
    if (res != 0)
    {
        return 1;
    }
    
    /* display clear */
    res = st7920_display_clear(&gs_handle);
    if (res != 0)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief  basic example clear image
 * @return status code
 *         - 0 success
 *         - 1 clear failed
 * @note   none
 */
uint8_t st7920_basic_clear_image(void)
{
    uint8_t res;
    
    /* set extended function */
    res = st7920_set_extended_function(&gs_handle, ST7920_INTERFACE_BUS_BIT_8, ST7920_COMMAND_MODE_EXTENDED, ST7920_BOOL_TRUE);
    if (res != 0)
    {
        return 1;
    }
    
    /* display clear */
    res = st7920_display_clear(&gs_handle);
    if (res != 0)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief     basic example write a point
 * @param[in] x coordinate x
 * @param[in] y coordinate y
 * @param[in] data written data
 * @return    status code
 *            - 0 success
 *            - 1 write point failed
 * @note      none
 */
uint8_t st7920_basic_write_point(uint8_t x, uint8_t y, uint8_t data)
{
    uint8_t res;
    
    /* set extended function */
    res = st7920_set_extended_function(&gs_handle, ST7920_INTERFACE_BUS_BIT_8, ST7920_COMMAND_MODE_EXTENDED, ST7920_BOOL_TRUE);
    if (res != 0)
    {
        return 1;
    }
    
    /* write point */
    res = st7920_write_point(&gs_handle, x, y, data);
    if (res != 0)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief      basic example read a point
 * @param[in]  x coordinate x
 * @param[in]  y coordinate y
 * @param[out] *data pointer to a data buffer
 * @return     status code
 *             - 0 success
 *             - 1 read point failed
 * @note       none
 */
uint8_t st7920_basic_read_point(uint8_t x, uint8_t y, uint8_t *data)
{
    uint8_t res;
    
    /* set extended function */
    res = st7920_set_extended_function(&gs_handle, ST7920_INTERFACE_BUS_BIT_8, ST7920_COMMAND_MODE_EXTENDED, ST7920_BOOL_TRUE);
    if (res != 0)
    {
        return 1;
    }
    
    /* read point */
    res = st7920_read_point(&gs_handle, x, y, (uint8_t *)data);
    if (res != 0)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief     basic example write a string
 * @param[in] x coordinate x
 * @param[in] y coordinate y
 * @param[in] *str pointer to a written string address
 * @return    status code
 *            - 0 success
 *            - 1 write string failed
 * @note      none
 */
uint8_t st7920_basic_string(uint8_t x, uint8_t y, char *str)
{
    uint8_t res;
    
    /* set basic function */
    res = st7920_set_function(&gs_handle, ST7920_BASIC_DEFAULT_BUS_BIT, ST7920_COMMAND_MODE_BASIC);
    if (res != 0)
    {
        return 1;
    }
    
    /* write string */
    res = st7920_write_string(&gs_handle, x, y, (char *)str);
    if (res != 0)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief     basic example fill a rectangle
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
uint8_t st7920_basic_rect(int8_t left, uint8_t top, uint8_t right, uint8_t bottom, uint8_t color)
{
    uint8_t res;
    
    /* set extended function */
    res = st7920_set_extended_function(&gs_handle, ST7920_INTERFACE_BUS_BIT_8, ST7920_COMMAND_MODE_EXTENDED, ST7920_BOOL_TRUE);
    if (res != 0)
    {
        return 1;
    }
    
    /* fill a rect */
    res = st7920_fill_rect(&gs_handle, left, top, right, bottom, color);
    if (res != 0)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief     basic example draw a picture
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
uint8_t st7920_basic_picture(int8_t left, uint8_t top, uint8_t right, uint8_t bottom, uint8_t *img)
{
    uint8_t res;
    
    /* set extended function */
    res = st7920_set_extended_function(&gs_handle, ST7920_INTERFACE_BUS_BIT_8, ST7920_COMMAND_MODE_EXTENDED, ST7920_BOOL_TRUE);
    if (res != 0)
    {
        return 1;
    }
    
    /* draw picture */
    res = st7920_draw_picture(&gs_handle, left, top, right, bottom, (uint8_t *)img);
    if (res != 0)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief     basic example draw a compressed picture
 * @param[in] left left coordinate x
 * @param[in] top top coordinate y
 * @param[in] right right coordinate x
 * @param[in] bottom bottom coordinate y
 * @param[in] *img pointer to a image buffer
 * @return    status code
 *            - 0 success
 *            - 1 draw picture failed
 * @note      draw a compressed picture, one bit one pixel
 */
uint8_t st7920_basic_compress_picture(int8_t left, uint8_t top, uint8_t right, uint8_t bottom, uint8_t *img)
{
    uint8_t res;
    
    /* set extended function */
    res = st7920_set_extended_function(&gs_handle, ST7920_INTERFACE_BUS_BIT_8, ST7920_COMMAND_MODE_EXTENDED, ST7920_BOOL_TRUE);
    if (res != 0)
    {
        return 1;
    }
    
    /* draw picture */
    res = st7920_draw_compress_picture(&gs_handle, left, top, right, bottom, (uint8_t *)img);
    if (res != 0)
    {
        return 1;
    }
    
    return 0;
}
