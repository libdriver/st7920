[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver ST7920

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/st7920/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

ST7920 LCD controller/driver IC can display alphabets, numbers, Chinese fonts and self-defined characters. It supports 3 kinds of bus interface, namely 8-bit, 4-bit and serial. All functions, including display RAM, Character Generation ROM, LCD display drivers and control circuits are all in a one-chip solution. With a minimum system configuration, a Chinese character display system can be easily achieved.ST7920 includes character ROM with 8192 16x16 dots Chinese fonts and 126 16x8 dots half-width alphanumerical fonts. Besides, it supports 64x256 dots graphic display area for graphic display (GDRAM). Mix-mode display with
both character and graphic data is possible. ST7920 has built-in CGRAM and provide 4 sets software programmable 16x16 fonts.ST7920 has wide operating voltage range (2.7V to 5.5V). It also has low power consumption. So ST7920 is suitable for battery-powered portable device.ST7920 LCD driver consists of 32-common and 64-segment. 

LibDriver ST7920 is the full function driver of ST7920 launched by LibDriver.It provides the functions of drawing single point, filling block, image display, etc. LibDriver is MISRA compliant.

### Table of Contents

  - [Instruction](#Instruction)
  - [Install](#Install)
  - [Usage](#Usage)
    - [example basic](#example-basic)
    - [example advance](#example-advance)
  - [Document](#Document)
  - [Contributing](#Contributing)
  - [License](#License)
  - [Contact Us](#Contact-Us)

### Instruction

/src includes LibDriver ST7920 source files.

/interface includes LibDriver ST7920 GPIO platform independent template.

/test includes LibDriver ST7920 driver test code and this code can test the chip necessary function simply.

/example includes LibDriver ST7920 sample code.

/doc includes LibDriver ST7920 offline document.

/datasheet includes ST7920 datasheet.

/project includes the common Linux and MCU development board sample code. All projects use the shell script to debug the driver and the detail instruction can be found in each project's README.md.

### Install

Reference /interface GPIO platform independent template and finish your platform GPIO driver.

Add /src, /interface and /example to your project.

### Usage

#### example basic

```C
#include "driver_st7920_basic.h"

uint8_t res;

res = st7920_basic_init();
if (res != 0)
{
    st7920_interface_debug_print("st7920: init failed.\n");

    return 1;
}

res = st7920_basic_write_point(0, 0, 1);
if (res != 0)
{
    st7920_interface_debug_print("st7920: write point failed.\n");
    (void)st7920_basic_deinit();

    return 1;
}

res = st7920_basic_clear();
if (res != 0)
{
    st7920_interface_debug_print("st7920: clear screen failed.\n");
    (void)st7920_basic_deinit();

    return 1;
}

res = st7920_basic_string(0, 0, "LibDriver");
if (res != 0)
{
    st7920_interface_debug_print("st7920: show string failed.\n");
    (void)st7920_basic_deinit();

    return 1;
}

res = st7920_basic_rect(0, 0, 32, 32, 1);
if (res != 0)
{
    st7920_interface_debug_print("st7920: draw rect failed.\n");
    (void)st7920_basic_deinit();

    return 1;
}

res = st7920_basic_deinit();
if (res != 0)
{
    st7920_interface_debug_print("st7920: deinit failed.\n");

    return 1;
}

return 0;
```

#### example advance

The image extraction format is as follows and every pixel stored in one byte.

<div align=center>
<img src="/doc/image/image_format.svg" width="220" height="220"/>
</div>

```C
#include "driver_st7920_advance.h"

uint8_t res;
uint8_t gs_image[8192];

res = st7920_advance_init();
if (res != 0)
{
    st7920_interface_debug_print("st7920: init failed.\n");

    return 1;
}

res = st7920_advance_clear();
if (res != 0)
{
    st7920_interface_debug_print("st7920: clear screen failed.\n");
    (void)st7920_advance_deinit();

    return 1;
}

res = st7920_advance_string(0, 0, "LibDriver");
if (res != 0)
{
    st7920_interface_debug_print("st7920: show string failed.\n");
    (void)st7920_advance_deinit();

    return 1;
}

res = st7920_advance_write_point(0, 0, 1);
if (res != 0)
{
    st7920_interface_debug_print("st7920: write point failed.\n");
    (void)st7920_advance_deinit();

    return 1;
}

res = st7920_advance_rect(0, 0, 32, 32, 1);
if (res != 0)
{
    st7920_interface_debug_print("st7920: draw rect failed.\n");
    (void)st7920_advance_deinit();

    return 1;
}

res = st7920_advance_picture(0, 0, 127, 63, gs_image);
if (res != 0)
{
    st7920_interface_debug_print("st7920: draw picture failed.\n");
    (void)st7920_advance_deinit();

    return 1;
}

res = st7920_advance_deinit();
if (res != 0)
{
    st7920_interface_debug_print("st7920: deinit failed.\n");

    return 1;
}

return 0;
```

### Document

Online documents: [https://www.libdriver.com/docs/st7920/index.html](https://www.libdriver.com/docs/st7920/index.html).

Offline documents: /doc/html/index.html.

### Contributing

Please refer to CONTRIBUTING.md.

### License

Copyright (c) 2015 - present LibDriver All rights reserved



The MIT License (MIT) 



Permission is hereby granted, free of charge, to any person obtaining a copy

of this software and associated documentation files (the "Software"), to deal

in the Software without restriction, including without limitation the rights

to use, copy, modify, merge, publish, distribute, sublicense, and/or sell

copies of the Software, and to permit persons to whom the Software is

furnished to do so, subject to the following conditions: 



The above copyright notice and this permission notice shall be included in all

copies or substantial portions of the Software. 



THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR

IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,

FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE

AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER

LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,

OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE

SOFTWARE. 

### Contact Us

Please sent an e-mail to lishifenging@outlook.com.