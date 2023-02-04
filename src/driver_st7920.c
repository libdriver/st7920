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
 * @file      driver_st7920.c
 * @brief     driver st7920 source file
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

#include "driver_st7920.h"

/**
 * @brief chip information definition
 */
#define CHIP_NAME                 "Sitronix ST7920"        /**< chip name */
#define MANUFACTURER_NAME         "Sitronix"               /**< manufacturer name */
#define SUPPLY_VOLTAGE_MIN        2.7f                     /**< chip min supply voltage */
#define SUPPLY_VOLTAGE_MAX        4.5f                     /**< chip max supply voltage */
#define MAX_CURRENT               0.45f                    /**< chip max current */
#define TEMPERATURE_MIN           -30.0f                   /**< chip min operating temperature */
#define TEMPERATURE_MAX           85.0f                    /**< chip max operating temperature */
#define DRIVER_VERSION            1000                     /**< driver version */

/**
 * @brief data type definition
 */
#define ST7920_CMD         0        /**< command type */
#define ST7920_DATA        1        /**< data type */

/**
 * @brief command type definition
 */
#define ST7920_WRITE        0        /**< write type */
#define ST7920_READ         1        /**< read type */

/**
 * @brief command definition
 */
#define ST7920_CMD_BASIC_DISPLAY_CLEAR                        0x01        /**< display clear command */ 
#define ST7920_CMD_BASIC_RETURN_HOME                          0x02        /**< return home command */ 
#define ST7920_CMD_BASIC_ENTRY_MODE_SET                       0x04        /**< entry mode set command */ 
#define ST7920_CMD_BASIC_DISPLAY_CONTROL                      0x08        /**< display control command */ 
#define ST7920_CMD_BASIC_CURSOR_DISPLAY_CONTROL               0x10        /**< cursor display control command */ 
#define ST7920_CMD_BASIC_FUNCTION_SET                         0x20        /**< function set command */
#define ST7920_CMD_BASIC_SET_CGRAM                            0x40        /**< set cgram command */
#define ST7920_CMD_BASIC_SET_DDRAM                            0x80        /**< set ddram command */
#define ST7920_CMD_EXT_STANFBY                                0x01        /**< standby command */
#define ST7920_CMD_EXT_SCROLL_RAM_ADDRESS_SELECT              0x02        /**< scroll or ram address select command */
#define ST7920_CMD_EXT_REVERSE                                0x04        /**< reverse command */
#define ST7920_CMD_EXT_FUNCTION_SET                           0x20        /**< extended function command */
#define ST7920_CMD_EXT_SET_SCROLL_ADDRESS                     0x40        /**< set scroll address command */
#define ST7920_CMD_EXT_SET_GRAPHIC_DISPLAY_RAM_ADDRESS        0x80        /**< set graphic display ram address command */

/**
 * @brief     serial write
 * @param[in] *handle points to an st7920 handle structure
 * @param[in] data is the write data
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 * @note      none
 */
static uint8_t a_st7920_serial_write(st7920_handle_t *handle, uint8_t data)
{
    uint8_t res;
    uint8_t i;
    
    for (i = 0; i < 8; i++)                         /* 8 bits */
    {
        if ((data & 0x80) != 0)                     /* if high */
        {
            res = handle->sid_gpio_write(1);        /* sid 1 */
            if (res != 0)                           /* check the result */
            {
                return 1;                           /* return error */
            }
        }
        else
        {
            res = handle->sid_gpio_write(0);        /* sid 0 */
            if (res != 0)                           /* check the result */
            {
                return 1;                           /* return error */
            }
        }
        
        res = handle->sclk_gpio_write(1);           /* sclk high */
        if (res != 0)                               /* check the result */
        {
            return 1;                               /* return error */
        }
        handle->delay_us(10);                       /* delay 10 */
        res = handle->sclk_gpio_write(0);           /* sclk low */
        if (res != 0)                               /* check the result */
        {
            return 1;                               /* return error */
        }
        data <<= 1;                                 /* << 1 bit */
    }
    
    return 0;                                       /* success return 0 */
}

/**
 * @brief     write one byte
 * @param[in] *handle points to an st7920 handle structure
 * @param[in] rw is the command type
 * @param[in] rs is the data type
 * @param[in] data is the write data
 * @param[in] us is the delay us
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 * @note      none
 */
static uint8_t a_st7920_write_byte(st7920_handle_t *handle, uint8_t rw, uint8_t rs, uint8_t data, uint32_t us)
{
    uint8_t res;
    uint8_t reg;
    
    res = handle->cs_gpio_write(1);                            /* set high */
    if (res != 0)                                              /* check the result */
    {
        handle->debug_print("st7920: write failed.\n");        /* write failed */
        
        return 1;                                              /* return error */
    }
    handle->delay_us(10);                                      /* delay */
    
    reg = 0xF8;                                                /* set synchronizing bit string */
    reg |= rw << 2;                                            /* set rw */
    reg |= rs << 1;                                            /* set rs */
    res = a_st7920_serial_write(handle, reg);                  /* serial write */
    if (res != 0)                                              /* check the result */
    {
        handle->debug_print("st7920: write failed.\n");        /* write failed */
        (void)handle->cs_gpio_write(0);                        /* set low */
        
        return 1;                                              /* return error */
    }
    
    reg = 0;                                                   /* set 0 */
    reg |= ((data >> 4) & 0xF) << 4;                           /* set higher data */
    res = a_st7920_serial_write(handle, reg);                  /* serial write */
    if (res != 0)                                              /* check the result */
    {
        handle->debug_print("st7920: write failed.\n");        /* write failed */
        (void)handle->cs_gpio_write(0);                        /* set low */
        
        return 1;                                              /* return error */
    }
    
    reg = 0;                                                   /* set 0 */
    reg |= ((data >> 0) & 0xF) << 4;                           /* set lower data */
    res = a_st7920_serial_write(handle, reg);                  /* serial write */
    if (res != 0)                                              /* check the result */
    {
        handle->debug_print("st7920: write failed.\n");        /* write failed */
        (void)handle->cs_gpio_write(0);                        /* set low */
        
        return 1;                                              /* return error */
    }
    
    res = handle->cs_gpio_write(0);                            /* set low */
    if (res != 0)                                              /* check the result */
    {
        handle->debug_print("st7920: write failed.\n");        /* write failed */
        
        return 1;                                              /* return error */
    }
    
    handle->delay_us(us);                                      /* delay us */
    
    return 0;                                                  /* success return 0 */
}

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
uint8_t st7920_init(st7920_handle_t *handle)
{
    uint8_t i, j;
    
    if (handle == NULL)                                                    /* check handle */
    {
        return 2;                                                          /* return error */
    }
    if (handle->debug_print == NULL)                                       /* check debug_print */
    {
        return 3;                                                          /* return error */
    }
    if (handle->cs_gpio_init == NULL)                                      /* check cs_gpio_init */
    {
        handle->debug_print("st7920: cs_gpio_init is null.\n");            /* cs_gpio_init is null */
       
        return 3;                                                          /* return error */
    }
    if (handle->cs_gpio_deinit == NULL)                                    /* check cs_gpio_deinit */
    {
        handle->debug_print("st7920: cs_gpio_deinit is null.\n");          /* cs_gpio_deinit is null */
       
        return 3;                                                          /* return error */
    }
    if (handle->cs_gpio_write == NULL)                                     /* check cs_gpio_write */
    {
        handle->debug_print("st7920: cs_gpio_write is null.\n");           /* cs_gpio_write is null */
       
        return 3;                                                          /* return error */
    }
    if (handle->sclk_gpio_init == NULL)                                    /* check sclk_gpio_init */
    {
        handle->debug_print("st7920: sclk_gpio_init is null.\n");          /* sclk_gpio_init is null */
       
        return 3;                                                          /* return error */
    }
    if (handle->sclk_gpio_deinit == NULL)                                  /* check sclk_gpio_deinit */
    {
        handle->debug_print("st7920: sclk_gpio_deinit is null.\n");        /* sclk_gpio_deinit is null */
       
        return 3;                                                          /* return error */
    }
    if (handle->sclk_gpio_write == NULL)                                   /* check sclk_gpio_write */
    {
        handle->debug_print("st7920: sclk_gpio_write is null.\n");         /* sclk_gpio_write is null */
       
        return 3;                                                          /* return error */
    }
    if (handle->sid_gpio_init == NULL)                                     /* check sid_gpio_init */
    {
        handle->debug_print("st7920: sid_gpio_init is null.\n");           /* sid_gpio_init is null */
       
        return 3;                                                          /* return error */
    }
    if (handle->sid_gpio_deinit == NULL)                                   /* check sid_gpio_deinit */
    {
        handle->debug_print("st7920: sid_gpio_deinit is null.\n");         /* sid_gpio_deinit is null */
       
        return 3;                                                          /* return error */
    }
    if (handle->sid_gpio_write == NULL)                                    /* check sid_gpio_write */
    {
        handle->debug_print("st7920: sid_gpio_write is null.\n");          /* sid_gpio_write is null */
       
        return 3;                                                          /* return error */
    }
    if (handle->delay_ms == NULL)                                          /* check delay_ms */
    {
        handle->debug_print("st7920: delay_ms is null.\n");                /* delay_ms is null */
       
        return 3;                                                          /* return error */
    }
    if (handle->delay_us == NULL)                                          /* check delay_us */
    {
        handle->debug_print("st7920: delay_us is null.\n");                /* delay_us is null */
       
        return 3;                                                          /* return error */
    }
    
    if (handle->cs_gpio_init() != 0)                                       /* cs gpio init */
    {
        handle->debug_print("st7920: cs gpio init failed.\n");             /* cs gpio init failed */
       
        return 1;                                                          /* return error */
    }
    if (handle->sclk_gpio_init() != 0)                                     /* sclk gpio init */
    {
        handle->debug_print("st7920: sclk gpio init failed.\n");           /* sclk gpio init failed */
        (void)handle->cs_gpio_deinit();                                    /* cs gpio deinit */
       
        return 1;                                                          /* return error */
    }
    if (handle->sid_gpio_init() != 0)                                      /* sid gpio init */
    {
        handle->debug_print("st7920: sid gpio init failed.\n");            /* sid gpio init failed */
        (void)handle->cs_gpio_deinit();                                    /* cs gpio deinit */
        (void)handle->sclk_gpio_deinit();                                  /* sclk gpio deinit */
       
        return 1;                                                          /* return error */
    }
    handle->delay_ms(50);                                                  /* delay 50ms */
    for (i = 0; i < 8; i++)                                                /* x */
    {
        for (j = 0; j < 64; j++)                                           /* y */
        {
            handle->gram[i][j] = 0;                                        /* set 0 */
        }
    }
    handle->inited = 1;                                                    /* flag finish initialization */
    
    return 0;                                                              /* success return 0 */
}

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
uint8_t st7920_deinit(st7920_handle_t *handle)
{
    if (handle == NULL)                                                      /* check handle */
    {
        return 2;                                                            /* return error */
    }
    if (handle->inited != 1)                                                 /* check handle initialization */
    {
        return 3;                                                            /* return error */
    }
    
    if (a_st7920_write_byte(handle, ST7920_WRITE, ST7920_CMD,
                            ST7920_CMD_BASIC_FUNCTION_SET,
                            100) != 0)                                       /* write command */
    {
        handle->debug_print("st7920: set function failed.\n");               /* set function failed */
        
        return 1;                                                            /* return error */
    }
    if (a_st7920_write_byte(handle, ST7920_WRITE, ST7920_CMD,
                            ST7920_CMD_BASIC_DISPLAY_CONTROL,
                            100) != 0)                                       /* write command */
    {
        handle->debug_print("st7920: set display control failed.\n");        /* set display control failed */
        
        return 1;                                                            /* return error */
    }
    if (handle->cs_gpio_deinit() != 0)                                       /* cs gpio deinit */
    {
        handle->debug_print("st7920: cs gpio deinit failed.\n");             /* cs gpio deinit failed */
       
        return 1;                                                            /* return error */
    }
    if (handle->sclk_gpio_deinit() != 0)                                     /* sclk gpio deinit */
    {
        handle->debug_print("st7920: sclk gpio deinit failed.\n");           /* sclk gpio deinit failed */
       
        return 1;                                                            /* return error */
    }
    if (handle->sid_gpio_deinit() != 0)                                      /* sid gpio deinit */
    {
        handle->debug_print("st7920: sid gpio deinit failed.\n");            /* sid gpio deinit failed */
       
        return 1;                                                            /* return error */
    }
    handle->inited = 0;                                                      /* flag closed */
    
    return 0;                                                                /* success return 0 */
}

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
uint8_t st7920_write_point(st7920_handle_t *handle, uint8_t x, uint8_t y, uint8_t data)
{
    if (handle == NULL)                                                                             /* check handle */
    {
        return 2;                                                                                   /* return error */
    }
    if (handle->inited != 1)                                                                        /* check handle initialization */
    {
        return 3;                                                                                   /* return error */
    }
    if (handle->basic_extended != 1)                                                                /* check command type */
    {
        handle->debug_print("st7920: this command must be run in extended command mode.\n");        /* this command must be run in extended command mode */
        
        return 4;                                                                                   /* return error */
    }
    if (x > 127)                                                                                    /* check the x range */
    {
        handle->debug_print("st7920: x is over 127.\n");                                            /* x is over 127 */
        
        return 5;                                                                                   /* return error */
    }
    if (y > 63)                                                                                     /* check the y range */
    {
        handle->debug_print("st7920: y is over 63.\n");                                             /* y is over 63 */
        
        return 6;                                                                                   /* return error */
    }
    
    if (data != 0)                                                                                  /* if 1 */
    {
        handle->gram[x / 16][y] |= 1 << (15 - (x % 16));                                            /* set data */
    }
    else                                                                                            /* if 0 */
    {
        handle->gram[x / 16][y] &= ~(1 << (15 - (x % 16)));                                         /* set data */
    }
    
    y += handle->scroll_address;                                                                    /* y += scroll address */
    if (a_st7920_write_byte(handle, ST7920_WRITE, ST7920_CMD,
                           (uint8_t)(ST7920_CMD_EXT_SET_GRAPHIC_DISPLAY_RAM_ADDRESS + 
                           ((y - handle->scroll_address) % 32 + handle->scroll_address) % 64),
                            100) != 0)                                                              /* set vertical addr */
    {
        handle->debug_print("st7920: set graphic address failed.\n");                               /* set graphic address failed */
        
        return 1;                                                                                   /* return error */
    }
    if (a_st7920_write_byte(handle, ST7920_WRITE, ST7920_CMD,
                           (uint8_t)(ST7920_CMD_EXT_SET_GRAPHIC_DISPLAY_RAM_ADDRESS +
                            8 * ((y - handle->scroll_address) / 32) + x / 16),
                            100) != 0)                                                              /* set horizontal addr */
    {
        handle->debug_print("st7920: set graphic address failed.\n");                               /* set graphic address failed */
        
        return 1;                                                                                   /* return error */
    }
    if (a_st7920_write_byte(handle, ST7920_WRITE, ST7920_DATA,
                           (uint8_t)((handle->gram[x / 16][y % 64] >> 8) & 0xFF), 100) != 0)        /* write data */
    {
        handle->debug_print("st7920: write data failed.\n");                                        /* write data failed */
        
        return 1;                                                                                   /* return error */
    }
    if (a_st7920_write_byte(handle, ST7920_WRITE, ST7920_DATA,
                           (uint8_t)((handle->gram[x / 16][y % 64] >> 0) & 0xFF), 100) != 0)        /* write data */
    {
        handle->debug_print("st7920: write data failed.\n");                                        /* write data failed */
        
        return 1;                                                                                   /* return error */
    }
    
    return 0;                                                                                       /* success return 0 */
}

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
uint8_t st7920_read_point(st7920_handle_t *handle, uint8_t x, uint8_t y, uint8_t *data)
{
    if (handle == NULL)                                                                             /* check handle */
    {
        return 2;                                                                                   /* return error */
    }
    if (handle->inited != 1)                                                                        /* check handle initialization */
    {
        return 3;                                                                                   /* return error */
    }
    if (handle->basic_extended != 1)                                                                /* check command type */
    {
        handle->debug_print("st7920: this command must be run in extended command mode.\n");        /* this command must be run in extended command mode */
        
        return 4;                                                                                   /* return error */
    }
    if (x > 127)                                                                                    /* check the x range */
    {
        handle->debug_print("st7920: x is over 127.\n");                                            /* x is over 127 */
        
        return 5;                                                                                   /* return error */
    }
    if (y > 63)                                                                                     /* check the y range */
    {
        handle->debug_print("st7920: y is over 63.\n");                                             /* y is over 63 */
        
        return 6;                                                                                   /* return error */
    }
    *data = (handle->gram[x / 16][y] >> (15 - (x % 16))) & 0x01;                                    /* set data */
    
    return 0;                                                                                       /* success return 0 */
}

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
uint8_t st7920_write_string(st7920_handle_t *handle, uint8_t x, uint8_t y, char *str)
{
    uint16_t i;
    uint8_t pos;
    
    if (handle == NULL)                                                                          /* check handle */
    {
        return 2;                                                                                /* return error */
    }
    if (handle->inited != 1)                                                                     /* check handle initialization */
    {
        return 3;                                                                                /* return error */
    }
    if (handle->basic_extended != 0)                                                             /* check command type */
    {
        handle->debug_print("st7920: this command must be run in basic command mode.\n");        /* this command must be run in basic command mode */
        
        return 4;                                                                                /* return error */
    }
    if (x > 3)                                                                                   /* check the x range */
    {
        handle->debug_print("st7920: x is over 3.\n");                                           /* x is over 3 */
        
        return 5;                                                                                /* return error */
    }
    if (y > 7)                                                                                   /* check the y range */
    {
        handle->debug_print("st7920: y is over 7.\n");                                           /* y is over 7 */
        
        return 6;                                                                                /* return error */
    }
    
    if (x == 0)                                                                                  /* if x == 0 */
    {
        pos = 0x80 + y;                                                                          /* set pos */
    }
    else if (x == 1)                                                                             /* if x == 1 */
    {
        pos = 0x90 + y;                                                                          /* set pos */
    }
    else if (x == 2)                                                                             /* if x == 2 */
    {
        pos = 0x88 + y;                                                                          /* set pos */
    }
    else                                                                                         /* x == 3 */
    {
        pos = 0x98 + y;                                                                          /* set pos */
    }
    if (a_st7920_write_byte(handle, ST7920_WRITE, ST7920_CMD, pos, 100) != 0)                    /* write command */
    {
        handle->debug_print("st7920: set ddram address failed.\n");                              /* set ddram address failed */
        
        return 1;                                                                                /* return error */
    }
    
    for (i = 0; str[i] != 0; i++)                                                                /* write the string */
    {
        if (a_st7920_write_byte(handle, ST7920_WRITE, ST7920_DATA, (uint8_t)str[i], 100) != 0)      /* write data */
        {
            handle->debug_print("st7920: write data failed.\n");                                 /* write data failed */
            
            return 1;                                                                            /* return error */
        }
    }
    
    return 0;                                                                                    /* success return 0 */
}

/**
 * @brief     draw a point
 * @param[in] *handle points to an st7920 handle structure
 * @param[in] x is the coordinate x
 * @param[in] y is the coordinate y
 * @param[in] data is the written data
 * @note      none
 */
static void a_st7920_draw_point(st7920_handle_t *handle, uint8_t x, uint8_t y, uint8_t data)
{
    if (data != 0)                                                 /* if 1 */
    {
        handle->gram[x / 16][y] |= 1 << (15 - (x % 16));           /* set data */
    }
    else                                                           /* if 0 */
    {
        handle->gram[x / 16][y] &= ~(1 << (15 - (x % 16)));        /* set data */
    }
}

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
uint8_t st7920_fill_rect(st7920_handle_t *handle, uint8_t left, uint8_t top, uint8_t right, uint8_t bottom, uint8_t color)
{
    uint8_t x, y;
    uint8_t i, j;
    uint8_t pos_start, pos_end;
    
    if (handle == NULL)                                                                                 /* check handle */
    {
        return 2;                                                                                       /* return error */
    }
    if (handle->inited != 1)                                                                            /* check handle initialization */
    {
        return 3;                                                                                       /* return error */
    }
    if (handle->basic_extended != 1)                                                                    /* check command type */
    {
        handle->debug_print("st7920: this command must be run in extended command mode.\n");            /* this command must be run in extended command mode */
        
        return 4;                                                                                       /* return error */
    }
    if ((left > 127) || (top > 63))                                                                     /* check left top */
    {
        handle->debug_print("st7920: left or top is invalid.\n");                                       /* left or top is invalid */
        
        return 5;                                                                                       /* return error */
    }
    if ((right > 127) || (bottom > 63))                                                                 /* check right bottom */
    {
        handle->debug_print("st7920: right or bottom is invalid.\n");                                   /* right or bottom is invalid */
        
        return 6;                                                                                       /* return error */
    }
    if ((left > right) || (top > bottom))                                                               /* check left right top bottom */
    {
        handle->debug_print("st7920: left > right or top > bottom.\n");                                 /* left > right or top > bottom */
        
        return 7;                                                                                       /* return error */
    }
    
    for (x = left; x <= right; x++)                                                                     /* write x */
    {
        for (y = top; y <= bottom; y++)                                                                 /* write y */
        {
            a_st7920_draw_point(handle, x, y, color);                                                   /* draw point */
        }
    }
    
    pos_start = handle->scroll_address;                                                                 /* set start */
    pos_end = 32 + handle->scroll_address;                                                              /* set end */
    for (i = pos_start; i < pos_end; i++)                                                               /* 32 line */
    {
        if (a_st7920_write_byte(handle, ST7920_WRITE, ST7920_CMD,
                               (uint8_t)(ST7920_CMD_EXT_SET_GRAPHIC_DISPLAY_RAM_ADDRESS + i % 64),
                                100) != 0)                                                              /* set vertical addr */
        {
            handle->debug_print("st7920: set graphic address failed.\n");                               /* set graphic address failed */
            
            return 1;                                                                                   /* return error */
        }
        if (a_st7920_write_byte(handle, ST7920_WRITE, ST7920_CMD,
                                ST7920_CMD_EXT_SET_GRAPHIC_DISPLAY_RAM_ADDRESS,
                                100) != 0)                                                              /* set horizontal addr */
        {
            handle->debug_print("st7920: set graphic address failed.\n");                               /* set graphic address failed */
            
            return 1;                                                                                   /* return error */
        }
        for (j = 0; j < 8; j++)                                                                         /* 8 times */
        {
            if (a_st7920_write_byte(handle, ST7920_WRITE, ST7920_DATA,
                                   (uint8_t)((handle->gram[j][i % 64] >> 8) & 0xFF), 100) != 0)         /* write data */
            {
                handle->debug_print("st7920: write data failed.\n");                                    /* write data failed */
                
                return 1;                                                                               /* return error */
            }
            if (a_st7920_write_byte(handle, ST7920_WRITE, ST7920_DATA,
                                   (uint8_t)((handle->gram[j][i % 64] >> 0) & 0xFF), 100) != 0)         /* write data */
            {
                handle->debug_print("st7920: write data failed.\n");                                    /* write data failed */
                
                return 1;                                                                               /* return error */
            }
        }
    }
    for (i = pos_start; i < pos_end; i++)                                                               /* 32 line */
    {
        if (a_st7920_write_byte(handle, ST7920_WRITE, ST7920_CMD,
                               (uint8_t)(ST7920_CMD_EXT_SET_GRAPHIC_DISPLAY_RAM_ADDRESS + i % 64),
                                100) != 0)                                                              /* set vertical addr */
        {
            handle->debug_print("st7920: set graphic address failed.\n");                               /* set graphic address failed */
            
            return 1;                                                                                   /* return error */
        }
        if (a_st7920_write_byte(handle, ST7920_WRITE, ST7920_CMD,
                               (uint8_t)(ST7920_CMD_EXT_SET_GRAPHIC_DISPLAY_RAM_ADDRESS + 8),
                                100) != 0)                                                              /* set horizontal addr */
        {
            handle->debug_print("st7920: set graphic address failed.\n");                               /* set graphic address failed */
            
            return 1;                                                                                   /* return error */
        }
        for (j = 0; j < 8; j++)                                                                         /* 8 times */
        {
            if (a_st7920_write_byte(handle, ST7920_WRITE, ST7920_DATA,
                                   (uint8_t)((handle->gram[j][(i + 32) % 64] >> 8) & 0xFF), 100) != 0)  /* write data */
            {
                handle->debug_print("st7920: write data failed.\n");                                    /* write data failed */
                
                return 1;                                                                               /* return error */
            }
            if (a_st7920_write_byte(handle, ST7920_WRITE, ST7920_DATA,
                                   (uint8_t)((handle->gram[j][(i + 32) % 64] >> 0) & 0xFF), 100) != 0)  /* write data */
            {
                handle->debug_print("st7920: write data failed.\n");                                    /* write data failed */
                
                return 1;                                                                               /* return error */
            }
        }
    }
    
    return 0;                                                                                           /* return error */
}

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
uint8_t st7920_draw_picture(st7920_handle_t *handle, uint8_t left, uint8_t top, uint8_t right, uint8_t bottom, uint8_t *img)
{
    uint8_t x, y;
    uint8_t i, j;
    uint8_t pos_start, pos_end;
    
    if (handle == NULL)                                                                                 /* check handle */
    {
        return 2;                                                                                       /* return error */
    }
    if (handle->inited != 1)                                                                            /* check handle initialization */
    {
        return 3;                                                                                       /* return error */
    }
    if (handle->basic_extended != 1)                                                                    /* check command type */
    {
        handle->debug_print("st7920: this command must be run in extended command mode.\n");            /* this command must be run in extended command mode */
        
        return 4;                                                                                       /* return error */
    }
    if ((left > 127) || (top > 63))                                                                     /* check left top */
    {
        handle->debug_print("st7920: left or top is invalid.\n");                                       /* left or top is invalid */
        
        return 5;                                                                                       /* return error */
    }
    if ((right > 127) || (bottom > 63))                                                                 /* check right bottom */
    {
        handle->debug_print("st7920: right or bottom is invalid.\n");                                   /* right or bottom is invalid */
        
        return 6;                                                                                       /* return error */
    }
    if ((left > right) || (top > bottom))                                                               /* check left right top bottom */
    {
        handle->debug_print("st7920: left > right or top > bottom.\n");                                 /* left > right or top > bottom */
        
        return 7;                                                                                       /* return error */
    }
    
    for (x = left; x <= right; x++)                                                                     /* write x */
    {
        for (y = top; y <= bottom; y++)                                                                 /* write y */
        {
            a_st7920_draw_point(handle, x, y, *img);                                                    /* draw point */
            img++;                                                                                      /* img++ */
        }
    }
    
    pos_start = handle->scroll_address;                                                                 /* set start */
    pos_end = 32 + handle->scroll_address;                                                              /* set end */
    for (i = pos_start; i < pos_end; i++)                                                               /* 32 line */
    {
        if (a_st7920_write_byte(handle, ST7920_WRITE, ST7920_CMD,
                               (uint8_t)(ST7920_CMD_EXT_SET_GRAPHIC_DISPLAY_RAM_ADDRESS + i % 64),
                                100) != 0)                                                              /* set vertical addr */
        {
            handle->debug_print("st7920: set graphic address failed.\n");                               /* set graphic address failed */
            
            return 1;                                                                                   /* return error */
        }
        if (a_st7920_write_byte(handle, ST7920_WRITE, ST7920_CMD,
                                ST7920_CMD_EXT_SET_GRAPHIC_DISPLAY_RAM_ADDRESS,
                                100) != 0)                                                              /* set horizontal addr */
        {
            handle->debug_print("st7920: set graphic address failed.\n");                               /* set graphic address failed */
            
            return 1;                                                                                   /* return error */
        }
        for (j = 0; j < 8; j++)                                                                         /* 8 times */
        {
            if (a_st7920_write_byte(handle, ST7920_WRITE, ST7920_DATA,
                                   (uint8_t)((handle->gram[j][i % 64] >> 8) & 0xFF), 100) != 0)         /* write data */
            {
                handle->debug_print("st7920: write data failed.\n");                                    /* write data failed */
                
                return 1;                                                                               /* return error */
            }
            if (a_st7920_write_byte(handle, ST7920_WRITE, ST7920_DATA,
                                   (uint8_t)((handle->gram[j][i % 64] >> 0) & 0xFF), 100) != 0)         /* write data */
            {
                handle->debug_print("st7920: write data failed.\n");                                    /* write data failed */
                
                return 1;                                                                               /* return error */
            }
        }
    }
    for (i = pos_start; i < pos_end; i++)                                                               /* 32 line */
    {
        if (a_st7920_write_byte(handle, ST7920_WRITE, ST7920_CMD,
                               (uint8_t)(ST7920_CMD_EXT_SET_GRAPHIC_DISPLAY_RAM_ADDRESS + i % 64),
                                100) != 0)                                                              /* set vertical addr */
        {
            handle->debug_print("st7920: set graphic address failed.\n");                               /* set graphic address failed */
            
            return 1;                                                                                   /* return error */
        }
        if (a_st7920_write_byte(handle, ST7920_WRITE, ST7920_CMD,
                               (uint8_t)(ST7920_CMD_EXT_SET_GRAPHIC_DISPLAY_RAM_ADDRESS + 8),
                                100) != 0)                                                              /* set horizontal addr */
        {
            handle->debug_print("st7920: set graphic address failed.\n");                               /* set graphic address failed */
            
            return 1;                                                                                   /* return error */
        }
        for (j = 0; j < 8; j++)                                                                         /* 8 times */
        {
            if (a_st7920_write_byte(handle, ST7920_WRITE, ST7920_DATA,
                                   (uint8_t)((handle->gram[j][(i + 32) % 64] >> 8) & 0xFF), 100) != 0)  /* write data */
            {
                handle->debug_print("st7920: write data failed.\n");                                    /* write data failed */
                
                return 1;                                                                               /* return error */
            }
            if (a_st7920_write_byte(handle, ST7920_WRITE, ST7920_DATA,
                                   (uint8_t)((handle->gram[j][(i + 32) % 64] >> 0) & 0xFF), 100) != 0)  /* write data */
            {
                handle->debug_print("st7920: write data failed.\n");                                    /* write data failed */
                
                return 1;                                                                               /* return error */
            }
        }
    }
    
    return 0;                                                                                           /* return error */
}

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
uint8_t st7920_display_clear(st7920_handle_t *handle)
{
    uint8_t i, j;
    
    if (handle == NULL)                                                                                     /* check handle */
    {
        return 2;                                                                                           /* return error */
    }
    if (handle->inited != 1)                                                                                /* check handle initialization */
    {
        return 3;                                                                                           /* return error */
    }
    
    for (i = 0; i < 8; i++)                                                                                 /* x */
    {
        for (j = 0; j < 64; j++)                                                                            /* y */
        {
            handle->gram[i][j] = 0;                                                                         /* set 0 */
        }
    }
    
    if (handle->basic_extended == 0)
    {
        if (a_st7920_write_byte(handle, ST7920_WRITE, ST7920_CMD,
                                ST7920_CMD_BASIC_DISPLAY_CLEAR, 2000) != 0)                                 /* write command */
        {
            handle->debug_print("st7920: display clear failed.\n");                                         /* display clear failed */
            
            return 1;                                                                                       /* return error */
        }
    }
    else
    {
        for (i = 0; i < 64; i++)
        {
            if (a_st7920_write_byte(handle, ST7920_WRITE, ST7920_CMD,
                                   (uint8_t)(ST7920_CMD_EXT_SET_GRAPHIC_DISPLAY_RAM_ADDRESS + i),
                                    100) != 0)                                                              /* set vertical addr */
            {
                handle->debug_print("st7920: set graphic address failed.\n");                               /* set graphic address failed */
                
                return 1;                                                                                   /* return error */
            }
            if (a_st7920_write_byte(handle, ST7920_WRITE, ST7920_CMD,
                                    ST7920_CMD_EXT_SET_GRAPHIC_DISPLAY_RAM_ADDRESS,
                                    100) != 0)                                                              /* set horizontal addr */
            {
                handle->debug_print("st7920: set graphic address failed.\n");                               /* set graphic address failed */
                
                return 1;                                                                                   /* return error */
            }
            for (j = 0; j < 8; j++)
            {
                if (a_st7920_write_byte(handle, ST7920_WRITE, ST7920_DATA,
                                        0x00, 100) != 0)                                                    /* write data */
                {
                    handle->debug_print("st7920: write data failed.\n");                                    /* write data failed */
                    
                    return 1;                                                                               /* return error */
                }
                if (a_st7920_write_byte(handle, ST7920_WRITE, ST7920_DATA,
                                        0x00, 100) != 0)                                                    /* write data */
                {
                    handle->debug_print("st7920: write data failed.\n");                                    /* write data failed */
                    
                    return 1;                                                                               /* return error */
                }
            }
        }
        for (i = 0; i < 64; i++)
        {
            if (a_st7920_write_byte(handle, ST7920_WRITE, ST7920_CMD,
                                   (uint8_t)(ST7920_CMD_EXT_SET_GRAPHIC_DISPLAY_RAM_ADDRESS + i),
                                    100) != 0)                                                              /* set vertical addr */
            {
                handle->debug_print("st7920: set graphic address failed.\n");                               /* set graphic address failed */
                
                return 1;                                                                                   /* return error */
            }
            if (a_st7920_write_byte(handle, ST7920_WRITE, ST7920_CMD,
                                   (uint8_t)(ST7920_CMD_EXT_SET_GRAPHIC_DISPLAY_RAM_ADDRESS + 8),
                                    100) != 0)                                                              /* set horizontal addr */
            {
                handle->debug_print("st7920: set graphic address failed.\n");                               /* set graphic address failed */
                
                return 1;                                                                                   /* return error */
            }
            for (j = 0; j < 8; j++)
            {
                if (a_st7920_write_byte(handle, ST7920_WRITE, ST7920_DATA,
                                        0x00, 100) != 0)                                                    /* write data */
                {
                    handle->debug_print("st7920: write data failed.\n");                                    /* write data failed */
                    
                    return 1;                                                                               /* return error */
                }
                if (a_st7920_write_byte(handle, ST7920_WRITE, ST7920_DATA,
                                        0x00, 100) != 0)                                                    /* write data */
                {
                    handle->debug_print("st7920: write data failed.\n");                                    /* write data failed */
                    
                    return 1;                                                                               /* return error */
                }
            }
        }
    }

    return 0;                                                                                               /* success return 0 */
}

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
uint8_t st7920_return_home(st7920_handle_t *handle)
{
    if (handle == NULL)                                                                          /* check handle */
    {
        return 2;                                                                                /* return error */
    }
    if (handle->inited != 1)                                                                     /* check handle initialization */
    {
        return 3;                                                                                /* return error */
    }
    if (handle->basic_extended != 0)                                                             /* check command type */
    {
        handle->debug_print("st7920: this command must be run in basic command mode.\n");        /* this command must be run in basic command mode */
        
        return 4;                                                                                /* return error */
    }
    
    if (a_st7920_write_byte(handle, ST7920_WRITE, ST7920_CMD,
                            ST7920_CMD_BASIC_RETURN_HOME, 100) != 0)                             /* write command */
    {
        handle->debug_print("st7920: return home failed.\n");                                    /* return home failed */
        
        return 1;                                                                                /* return error */
    }

    return 0;                                                                                    /* success return 0 */
}

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
uint8_t st7920_set_entry_mode(st7920_handle_t *handle, st7920_display_shift_t shift, st7920_address_counter_mode_t mode)
{
    if (handle == NULL)                                                                          /* check handle */
    {
        return 2;                                                                                /* return error */
    }
    if (handle->inited != 1)                                                                     /* check handle initialization */
    {
        return 3;                                                                                /* return error */
    }
    if (handle->basic_extended != 0)                                                             /* check command type */
    {
        handle->debug_print("st7920: this command must be run in basic command mode.\n");        /* this command must be run in basic command mode */
        
        return 4;                                                                                /* return error */
    }
    
    if (a_st7920_write_byte(handle, ST7920_WRITE, ST7920_CMD,
                           (uint8_t)(ST7920_CMD_BASIC_ENTRY_MODE_SET |
                           (mode << 1) | (shift << 0)),
                            100) != 0)                                                           /* write command */
    {
        handle->debug_print("st7920: set entry mode failed.\n");                                 /* set entry mode failed */
        
        return 1;                                                                                /* return error */
    }

    return 0;                                                                                    /* success return 0 */
}

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
uint8_t st7920_set_display_control(st7920_handle_t *handle, st7920_bool_t display_on, st7920_bool_t cursor_on, st7920_bool_t character_blink_on)
{
    if (handle == NULL)                                                                          /* check handle */
    {
        return 2;                                                                                /* return error */
    }
    if (handle->inited != 1)                                                                     /* check handle initialization */
    {
        return 3;                                                                                /* return error */
    }
    if (handle->basic_extended != 0)                                                             /* check command type */
    {
        handle->debug_print("st7920: this command must be run in basic command mode.\n");        /* this command must be run in basic command mode */
        
        return 4;                                                                                /* return error */
    }
    
    if (a_st7920_write_byte(handle, ST7920_WRITE, ST7920_CMD,
                           (uint8_t)(ST7920_CMD_BASIC_DISPLAY_CONTROL | (display_on << 2) | 
                           (cursor_on << 1) | (character_blink_on << 0)),
                            100) != 0)                                                           /* write command */
    {
        handle->debug_print("st7920: set display control failed.\n");                            /* set display control failed */
        
        return 1;                                                                                /* return error */
    }

    return 0;                                                                                    /* success return 0 */
}

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
uint8_t st7920_set_display_shift_mode(st7920_handle_t *handle, st7920_display_shift_mode_t mode)
{
    if (handle == NULL)                                                                          /* check handle */
    {
        return 2;                                                                                /* return error */
    }
    if (handle->inited != 1)                                                                     /* check handle initialization */
    {
        return 3;                                                                                /* return error */
    }
    if (handle->basic_extended != 0)                                                             /* check command type */
    {
        handle->debug_print("st7920: this command must be run in basic command mode.\n");        /* this command must be run in basic command mode */
        
        return 4;                                                                                /* return error */
    }
    
    if (a_st7920_write_byte(handle, ST7920_WRITE, ST7920_CMD,
                           (uint8_t)(ST7920_CMD_BASIC_CURSOR_DISPLAY_CONTROL |
                           ((mode & 0x3) << 2)),
                            100) != 0)                                                           /* write command */
    {
        handle->debug_print("st7920: set display shift mode failed.\n");                         /* set display shift mode failed */
        
        return 1;                                                                                /* return error */
    }

    return 0;                                                                                    /* success return 0 */
}

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
uint8_t st7920_set_function(st7920_handle_t *handle, st7920_interface_bus_bit_t bus_bit, st7920_command_mode_t mode)
{
    if (handle == NULL)                                                                          /* check handle */
    {
        return 2;                                                                                /* return error */
    }
    if (handle->inited != 1)                                                                     /* check handle initialization */
    {
        return 3;                                                                                /* return error */
    }
    
    if (a_st7920_write_byte(handle, ST7920_WRITE, ST7920_CMD,
                           (uint8_t)(ST7920_CMD_BASIC_FUNCTION_SET | bus_bit << 4 | mode << 2),
                           100) != 0)                                                            /* write command */
    {
        handle->debug_print("st7920: set function failed.\n");                                   /* set function failed */
        
        return 1;                                                                                /* return error */
    }
    handle->basic_extended = mode;                                                               /* set mode */
    
    return 0;                                                                                    /* success return 0 */
}

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
uint8_t st7920_set_cgram_address(st7920_handle_t *handle, uint8_t addr)
{
    if (handle == NULL)                                                                          /* check handle */
    {
        return 2;                                                                                /* return error */
    }
    if (handle->inited != 1)                                                                     /* check handle initialization */
    {
        return 3;                                                                                /* return error */
    }
    if (handle->basic_extended != 0)                                                             /* check command type */
    {
        handle->debug_print("st7920: this command must be run in basic command mode.\n");        /* this command must be run in basic command mode */
        
        return 4;                                                                                /* return error */
    }
    if (addr > 0x3F)                                                                             /* check addr */
    {
        handle->debug_print("st7920: addr is over 0x3F.\n");                                     /* addr is over 0x3F */
        
        return 5;                                                                                /* return error */
    }
    
    if (a_st7920_write_byte(handle, ST7920_WRITE, ST7920_CMD,
                           (uint8_t)(ST7920_CMD_BASIC_SET_CGRAM | (addr & 0x3F)),
                            100) != 0)                                                           /* write command */
    {
        handle->debug_print("st7920: set cgram address failed.\n");                              /* set cgram address failed */
        
        return 1;                                                                                /* return error */
    }
    
    return 0;                                                                                    /* success return 0 */
}

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
uint8_t st7920_set_ddram_address(st7920_handle_t *handle, uint8_t addr)
{
    if (handle == NULL)                                                                          /* check handle */
    {
        return 2;                                                                                /* return error */
    }
    if (handle->inited != 1)                                                                     /* check handle initialization */
    {
        return 3;                                                                                /* return error */
    }
    if (handle->basic_extended != 0)                                                             /* check command type */
    {
        handle->debug_print("st7920: this command must be run in basic command mode.\n");        /* this command must be run in basic command mode */
        
        return 4;                                                                                /* return error */
    }
    if (addr > 0x7F)                                                                             /* check addr */
    {
        handle->debug_print("st7920: addr is over 0x7F.\n");                                     /* addr is over 0x7F */
        
        return 5;                                                                                /* return error */
    }
    
    if (a_st7920_write_byte(handle, ST7920_WRITE, ST7920_CMD,
                           (uint8_t)(ST7920_CMD_BASIC_SET_DDRAM | (addr & 0x7F)),
                            100) != 0)                                                           /* write command */
    {
        handle->debug_print("st7920: set ddram address failed.\n");                              /* set ddram address failed */
        
        return 1;                                                                                /* return error */
    }
    
    return 0;                                                                                    /* success return 0 */
}

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
uint8_t st7920_write_ram(st7920_handle_t *handle, uint8_t *data, uint8_t len)
{
    uint8_t i;
    
    if (handle == NULL)                                                                          /* check handle */
    {
        return 2;                                                                                /* return error */
    }
    if (handle->inited != 1)                                                                     /* check handle initialization */
    {
        return 3;                                                                                /* return error */
    }
    if (handle->basic_extended != 0)                                                             /* check command type */
    {
        handle->debug_print("st7920: this command must be run in basic command mode.\n");        /* this command must be run in basic command mode */
        
        return 4;                                                                                /* return error */
    }
    
    for (i = 0; i < len; i++)                                                                    /* write length */
    {
        if (a_st7920_write_byte(handle, ST7920_WRITE, ST7920_DATA,
                                data[i], 100) != 0)                                              /* write data */
        {
            handle->debug_print("st7920: write ram failed.\n");                                  /* set ddram address failed */
            
            return 1;                                                                            /* write ram failed */
        }
    }
    
    return 0;                                                                                    /* success return 0 */
}

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
uint8_t st7920_set_standby(st7920_handle_t *handle)
{
    if (handle == NULL)                                                                             /* check handle */
    {
        return 2;                                                                                   /* return error */
    }
    if (handle->inited != 1)                                                                        /* check handle initialization */
    {
        return 3;                                                                                   /* return error */
    }
    if (handle->basic_extended != 1)                                                                /* check command type */
    {
        handle->debug_print("st7920: this command must be run in extended command mode.\n");        /* this command must be run in extended command mode */
        
        return 4;                                                                                   /* return error */
    }
    
    if (a_st7920_write_byte(handle, ST7920_WRITE, ST7920_CMD,
                            ST7920_CMD_EXT_STANFBY, 100) != 0)                                      /* write command */
    {
        handle->debug_print("st7920: set standby failed.\n");                                       /* set standby failed */
        
        return 1;                                                                                   /* return error */
    }

    return 0;                                                                                       /* success return 0 */
}

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
uint8_t st7920_set_vertical_scroll(st7920_handle_t *handle, st7920_bool_t enable)
{
    if (handle == NULL)                                                                             /* check handle */
    {
        return 2;                                                                                   /* return error */
    }
    if (handle->inited != 1)                                                                        /* check handle initialization */
    {
        return 3;                                                                                   /* return error */
    }
    if (handle->basic_extended != 1)                                                                /* check command type */
    {
        handle->debug_print("st7920: this command must be run in extended command mode.\n");        /* this command must be run in extended command mode */
        
        return 4;                                                                                   /* return error */
    }
    
    if (a_st7920_write_byte(handle, ST7920_WRITE, ST7920_CMD,
                           (uint8_t)(ST7920_CMD_EXT_SCROLL_RAM_ADDRESS_SELECT |
                           (enable & 0x01) << 0),
                            100) != 0)                                                              /* write command */
    {
        handle->debug_print("st7920: set vertical scroll failed.\n");                               /* set vertical scroll failed */
        
        return 1;                                                                                   /* return error */
    }

    return 0;                                                                                       /* success return 0 */
}

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
uint8_t st7920_set_reverse_line(st7920_handle_t *handle, st7920_reverse_line_t l)
{
    if (handle == NULL)                                                                             /* check handle */
    {
        return 2;                                                                                   /* return error */
    }
    if (handle->inited != 1)                                                                        /* check handle initialization */
    {
        return 3;                                                                                   /* return error */
    }
    if (handle->basic_extended != 1)                                                                /* check command type */
    {
        handle->debug_print("st7920: this command must be run in extended command mode.\n");        /* this command must be run in extended command mode */
        
        return 4;                                                                                   /* return error */
    }
    
    if (a_st7920_write_byte(handle, ST7920_WRITE, ST7920_CMD,
                           (uint8_t)(ST7920_CMD_EXT_REVERSE | (l & 0x03) << 0),
                            100) != 0)                                                              /* write command */
    {
        handle->debug_print("st7920: set reverse line failed.\n");                                  /* set reverse line failed */
        
        return 1;                                                                                   /* return error */
    }

    return 0;                                                                                       /* success return 0 */
}

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
                                     st7920_command_mode_t mode, st7920_bool_t graphic_display_enable)
{
    if (handle == NULL)                                                                             /* check handle */
    {
        return 2;                                                                                   /* return error */
    }
    if (handle->inited != 1)                                                                        /* check handle initialization */
    {
        return 3;                                                                                   /* return error */
    }
    
    if (a_st7920_write_byte(handle, ST7920_WRITE, ST7920_CMD,
                           (uint8_t)(ST7920_CMD_EXT_FUNCTION_SET | bus_bit << 4 | mode << 2 |
                            graphic_display_enable << 1),
                            100) != 0)                                                              /* write command */
    {
        handle->debug_print("st7920: set extended function failed.\n");                             /* set extended function failed */
        
        return 1;                                                                                   /* return error */
    }
    handle->basic_extended = mode;                                                                  /* set mode */
    
    return 0;                                                                                       /* success return 0 */
}

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
uint8_t st7920_set_scroll_address(st7920_handle_t *handle, uint8_t addr)
{
    if (handle == NULL)                                                                             /* check handle */
    {
        return 2;                                                                                   /* return error */
    }
    if (handle->inited != 1)                                                                        /* check handle initialization */
    {
        return 3;                                                                                   /* return error */
    }
    if (handle->basic_extended != 1)                                                                /* check command type */
    {
        handle->debug_print("st7920: this command must be run in extended command mode.\n");        /* this command must be run in extended command mode */
        
        return 4;                                                                                   /* return error */
    }
    if (addr > 0x3F)                                                                                /* check addr */
    {
        handle->debug_print("st7920: addr is over 0x3F.\n");                                        /* addr is over 0x3F */
        
        return 5;                                                                                   /* return error */
    }
    
    if (a_st7920_write_byte(handle, ST7920_WRITE, ST7920_CMD,
                           (uint8_t)(ST7920_CMD_EXT_SET_SCROLL_ADDRESS | (addr & 0x3F)),
                            100) != 0)                                                              /* write command */
    {
        handle->debug_print("st7920: set scroll address failed.\n");                                /* set scroll address failed */
        
        return 1;                                                                                   /* return error */
    }
    handle->scroll_address = addr;                                                                  /* set addr */

    return 0;                                                                                       /* success return 0 */
}

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
uint8_t st7920_set_graphic_address(st7920_handle_t *handle, uint8_t vertical_addr, uint8_t horizontal_addr)
{
    if (handle == NULL)                                                                             /* check handle */
    {
        return 2;                                                                                   /* return error */
    }
    if (handle->inited != 1)                                                                        /* check handle initialization */
    {
        return 3;                                                                                   /* return error */
    }
    if (handle->basic_extended != 1)                                                                /* check command type */
    {
        handle->debug_print("st7920: this command must be run in extended command mode.\n");        /* this command must be run in extended command mode */
        
        return 4;                                                                                   /* return error */
    }
    if (vertical_addr > 0x3F)                                                                       /* check vertical_addr */
    {
        handle->debug_print("st7920: vertical_addr is over 0x3F.\n");                               /* vertical_addr is over 0x3F */
        
        return 5;                                                                                   /* return error */
    }
    if (horizontal_addr > 0xF)                                                                      /* check horizontal_addr */
    {
        handle->debug_print("st7920: horizontal_addr is over 0xF.\n");                              /* horizontal_addr is over 0xF */
        
        return 6;                                                                                   /* return error */
    }
    
    if (a_st7920_write_byte(handle, ST7920_WRITE, ST7920_CMD,
                           (uint8_t)(ST7920_CMD_EXT_SET_GRAPHIC_DISPLAY_RAM_ADDRESS |
                            vertical_addr),
                            100) != 0)                                                              /* set vertical addr */
    {
        handle->debug_print("st7920: set graphic address failed.\n");                               /* set graphic address failed */
        
        return 1;                                                                                   /* return error */
    }
    if (a_st7920_write_byte(handle, ST7920_WRITE, ST7920_CMD,
                           (uint8_t)(ST7920_CMD_EXT_SET_GRAPHIC_DISPLAY_RAM_ADDRESS |
                            horizontal_addr),
                            100) != 0)                                                              /* set horizontal addr */
    {
        handle->debug_print("st7920: set graphic address failed.\n");                               /* set graphic address failed */
        
        return 1;                                                                                   /* return error */
    }
    
    return 0;                                                                                       /* success return 0 */
}

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
uint8_t st7920_write_cmd(st7920_handle_t *handle, uint8_t cmd)
{
    if (handle == NULL)                                              /* check handle */
    {
        return 2;                                                    /* return error */
    }
    if (handle->inited != 1)                                         /* check handle initialization */
    {
        return 3;                                                    /* return error */
    }
    
    if (a_st7920_write_byte(handle, ST7920_WRITE, ST7920_CMD,
                            cmd, 100) != 0)                          /* write command */
    {
        handle->debug_print("st7920: write cmd failed.\n");          /* write cmd failed */
        
        return 1;                                                    /* return error */
    }

    return 0;                                                        /* success return 0 */
}

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
uint8_t st7920_write_data(st7920_handle_t *handle, uint8_t data)
{
    if (handle == NULL)                                              /* check handle */
    {
        return 2;                                                    /* return error */
    }
    if (handle->inited != 1)                                         /* check handle initialization */
    {
        return 3;                                                    /* return error */
    }
    
    if (a_st7920_write_byte(handle, ST7920_WRITE, ST7920_DATA,
                            data, 100) != 0)                         /* write command */
    {
        handle->debug_print("st7920: write data failed.\n");         /* write data failed */
        
        return 1;                                                    /* return error */
    }

    return 0;                                                        /* success return 0 */
}

/**
 * @brief      get chip's information
 * @param[out] *info points to an st7920 info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t st7920_info(st7920_info_t *info)
{
    if (info == NULL)                                               /* check handle */
    {
        return 2;                                                   /* return error */
    }
    
    memset(info, 0, sizeof(st7920_info_t));                         /* initialize st7920 info structure */
    strncpy(info->chip_name, CHIP_NAME, 32);                        /* copy chip name */
    strncpy(info->manufacturer_name, MANUFACTURER_NAME, 32);        /* copy manufacturer name */
    strncpy(info->interface, "GPIO", 8);                            /* copy interface name */
    info->supply_voltage_min_v = SUPPLY_VOLTAGE_MIN;                /* set minimal supply voltage */
    info->supply_voltage_max_v = SUPPLY_VOLTAGE_MAX;                /* set maximum supply voltage */
    info->max_current_ma = MAX_CURRENT;                             /* set maximum current */
    info->temperature_max = TEMPERATURE_MAX;                        /* set minimal temperature */
    info->temperature_min = TEMPERATURE_MIN;                        /* set maximum temperature */
    info->driver_version = DRIVER_VERSION;                          /* set driver version */
    
    return 0;                                                       /* success return 0 */
}
