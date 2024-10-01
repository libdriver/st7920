### 1. Chip

#### 1.1 Chip Info

Chip Name: STM32F407ZGT6.

Extern Oscillator: 8MHz.

UART Pin: TX/RX PA9/PA10.

GPIO Pin: RS/RW/E/PSB PB1/PA8/PA0/GND.

### 2. Development and Debugging

#### 2.1 Integrated Development Environment

LibDriver provides both Keil and IAR integrated development environment projects.

MDK is the Keil ARM project and your Keil version must be 5 or higher.Keil ARM project needs STMicroelectronics STM32F4 Series Device Family Pack and you can download from https://www.keil.com/dd2/stmicroelectronics/stm32f407zgtx.

EW is the IAR ARM project and your IAR version must be 9 or higher.

#### 2.2 Serial Port Parameter

Baud Rate: 115200.

Data Bits : 8.

Stop Bits: 1.

Parity: None.

Flow Control: None.

#### 2.3 Serial Port Assistant

We use '\n' to wrap lines.If your serial port assistant displays exceptions (e.g. the displayed content does not divide lines), please modify the configuration of your serial port assistant or replace one that supports '\n' parsing.

### 3. ST7920

#### 3.1 Command Instruction

1. Show st7920 chip and driver information.

   ```shell
   st7920 (-i | --information)
   ```

2. Show st7920 help.

   ```shell
   st7920 (-h | --help)
   ```

3. Show st7920 pin connections of the current board.

   ```shell
   st7920 (-p | --port)
   ```

4. Run st7920 display test.

   ```shell
   st7920 (-t display | --test=display)
   ```

5. Run st7920 basic init function.

   ```shell
   st7920 (-e basic-init | --example=basic-init)
   ```

6. Run st7920 basic deinit function.

   ```shell
   st7920 (-e basic-deinit | --example=basic-deinit)
   ```

7. Run st7920 show string function, string means the shown string.

   ```shell
   st7920 (-e basic-str | --example=basic-str) [--str=<string>]
   ```

8. Run st7920 display on function.

   ```shell
   st7920 (-e basic-display-on | --example=basic-display-on)
   ```

9. Run st7920 display off function.

   ```shell
   st7920 (-e basic-display-off | --example=basic-display-off)
   ```

10. Run st7920 clear screen function.

    ```shell
    st7920 (-e basic-clear | --example=basic-clear)
    ```

11. Run st7920 write pont function, x0 is the x of the point and y0 is the y of the point.

    ```shell
    st7920 (-e basic-point | --example=basic-point) --x0=<x0> --y0=<y0> [--color=<0 | 1>]
    ```

12. Run st7920 draw rectangle function, x1 is the top left x of the rect, y1 is the top left y of the rect, x2 is the bottom right x of the rect and y2 is the bottom right y of the rect.

    ```shell
    st7920 (-e basic-rect | --example=basic-rect) --x1=<x1> --y1=<y1> --x2=<x2> --y2=<y2> [--color=<0 | 1>]
    ```

13. Run st7920 advance init function.

    ```shell
    st7920 (-e advance-init | --example=advance-init)
    ```

14. Run st7920 advance deinit function.

    ```shell
    st7920 (-e advance-deinit | --example=advance-deinit)
    ```

15. Run st7920 show string function, string means the shown string. 

    ```shell
    st7920 (-e advance-str | --example=advance-str) [--str=<string>]
    ```

16. Run st7920 display on function.

    ```shell
    st7920 (-e advance-display-on | --example=advance-display-on)
    ```

17. Run st7920 display off function.

    ```shell
    st7920 (-e advance-display-off | --example=advance-display-off)
    ```

18. Run st7920 clear screen function.

    ```shell
    st7920 (-e advance-clear | --example=advance-clear)
    ```

19. Run st7920 write pont function, x0 is the x of the point and y0 is the y of the point.

    ```shell
    st7920 (-e advance-point | --example=advance-point) --x0=<x0> --y0=<y0> [--color=<0 | 1>]
    ```

20. Run st7920 draw rectangle function, x1 is the top left x of the rect, y1 is the top left y of the rect, x2 is the bottom right x of the rect and y2 is the bottom right y of the rect.

    ```shell
    st7920 (-e advance-rect | --example=advance-rect) --x1=<x1> --y1=<y1> --x2=<x2> --y2=<y2> [--color=<0 | 1>]
    ```

21. Run st7920 disable scroll function.

    ```shell
    st7920 (-e advance-disable-scroll | --example=advance-disable-scroll)
    ```

22. Run st7920 scroll function, addr is the scroll address and 0 <= addr <= 0x3F.

    ```shell
    st7920 (-e advance-scroll | --example=advance-scroll) [--scroll=<addr>]
    ```

23. Run st7920 reverse line function.

    ```shell
    st7920 (-e advance-reverse-line | --example=advance-reverse-line) [--line=<0 | 1>]
    ```

#### 3.2 Command Example

```shell
st7920 -i

st7920: chip is Sitronix ST7920.
st7920: manufacturer is Sitronix.
st7920: interface is GPIO.
st7920: driver version is 1.0.
st7920: min supply voltage is 2.7V.
st7920: max supply voltage is 4.5V.
st7920: max current is 0.45mA.
st7920: max temperature is 85.0C.
st7920: min temperature is -30.0C.
```

```shell
st7920 -p

st7920: RS connected to GPIOB PIN1.
st7920: RW connected to GPIOA PIN8.
st7920: E connected to GPIOA PIN0.
st7920: PSB connected to GND.
```

```shell
st7920 -t display

st7920: chip is Sitronix ST7920.
st7920: manufacturer is Sitronix.
st7920: interface is GPIO.
st7920: driver version is 1.0.
st7920: min supply voltage is 2.7V.
st7920: max supply voltage is 4.5V.
st7920: max current is 0.45mA.
st7920: max temperature is 85.0C.
st7920: min temperature is -30.0C.
st7920: start display test.
st7920: write string test.
st7920: write gb2312 string test.
st7920: cursor on.
st7920: character blink on.
st7920: read / write point test.
st7920: x = 7, y = 3 write 1.
st7920: read / write point check ok.
st7920: x = 1, y = 63 write 1.
st7920: read / write point check ok.
st7920: fill rect test.
st7920: draw picture test.
st7920: vertical scroll test.
st7920: reverse line test.
st7920: finish display test.
```

```shell
st7920 -e basic-str --str=12345abcdEFGH

st7920: 12345abcdEFGH.
```

```shell
st7920 -e basic-init

st7920: init success.
```

```shell
st7920 -e basic-display-off

st7920: display off.
```

```shell
st7920 -e basic-display-on

st7920: display on.
```

```shell
st7920 -e basic-clear

st7920: clear screen.
```

```shell
st7920 -e basic-deinit

st7920: deinit st7920.
```

```shell
st7920 -e basic-point --x0=16 --y0=16 --color=1

st7920: write point 16 16 1.
```

```shell
st7920 -e basic-rect --x1=0 --y1=0 --x2=32 --y2=32 --color=1

st7920: draw rect 0 0 32 32.
```

```shell
st7920 -e advance-init

st7920: init success.
```

```shell
st7920 -e advance-str --str=12345abcdEFGH

st7920: 12345abcdEFGH.
```

```shell
st7920 -e advance-display-off

st7920: display off.
```

```shell
st7920 -e advance-display-on

st7920: display on.
```

```shell
st7920 -e advance-clear

st7920: clear screen.
```

```shell
st7920 -e advance-point --x0=16 --y0=16 --color=1

st7920: write point 16 16 1.
```

```shell
st7920 -e advance-rect --x1=0 --y1=0 --x2=32 --y2=32 --color=1

st7920: draw rect 0 0 32 32.
```

```shell
st7920 -e advance-deinit

st7920: deinit st7920.
```

```shell
st7920 -e advance-disable-scroll

st7920: disable scroll.
```

```shell
st7920 -e advance-scroll --scroll=16

st7920: set scroll 16.
```

```shell
st7920 -e advance-reverse-line --line=0

st7920: set reverse line 0.
```

```shell
st7920 -h

Usage:
  st7920 (-i | --information)
  st7920 (-h | --help)
  st7920 (-p | --port)
  st7920 (-t display | --test=display)
  st7920 (-e basic-init | --example=basic-init)
  st7920 (-e basic-deinit | --example=basic-deinit)
  st7920 (-e basic-str | --example=basic-str) [--str=<string>]
  st7920 (-e basic-display-on | --example=basic-display-on)
  st7920 (-e basic-display-off | --example=basic-display-off)
  st7920 (-e basic-clear | --example=basic-clear)
  st7920 (-e basic-point | --example=basic-point) --x0=<x0> --y0=<y0> [--color=<0 | 1>]
  st7920 (-e basic-rect | --example=basic-rect) --x1=<x1> --y1=<y1> --x2=<x2> --y2=<y2> [--color=<0 | 1>]
  st7920 (-e advance-init | --example=advance-init)
  st7920 (-e advance-deinit | --example=advance-deinit)
  st7920 (-e advance-str | --example=advance-str) [--str=<string>]
  st7920 (-e advance-display-on | --example=advance-display-on)
  st7920 (-e advance-display-off | --example=advance-display-off)
  st7920 (-e advance-clear | --example=advance-clear)
  st7920 (-e advance-point | --example=advance-point) --x0=<x0> --y0=<y0> [--color=<0 | 1>]
  st7920 (-e advance-rect | --example=advance-rect) --x1=<x1> --y1=<y1> --x2=<x2> --y2=<y2> [--color=<0 | 1>]
  st7920 (-e advance-disable-scroll | --example=advance-disable-scroll)
  st7920 (-e advance-scroll | --example=advance-scroll) [--scroll=<addr>]
  st7920 (-e advance-reverse-line | --example=advance-reverse-line) [--line=<0 | 1>]

Options:
      --color=<0 | 1>     Set the chip color.([default: 1])
  -e <basic-init | basic-deinit | basic-str | basic-display-on | basic-display-off | basic-clear
     | basic-point | basic-rect>, --example=<advance-init | advance-deinit | advance-str | advance-display-on
     | advance-display-off | advance-clear | advance-point | advance-rect | advance-disable-scroll
     | advance-scroll | advance-reverse-line>
                          Run the driver example.
  -h, --help              Show the help.
  -i, --information       Show the chip information.
      --line=<0 | 1>      Set the reverse line.([default: 0])
  -p, --port              Display the pin connections of the current board.
      --scroll            Set the scrolling address and 0 <= scroll <= 63.([default: 16])
      --str=<string>      Set the display string.([default: libdriver])
  -t <display>, --test=<display>
                          Run the driver test.
      --x0=<x0>           Set the x0 and it is the x of the point.
      --x1=<x1>           Set the x1 and it is the top left x of the rect.
      --x2=<x2>           Set the x2 and it is the bottom right x of the rect.
      --y0=<y0>           Set the y0 and it is the y of the point.
      --y1=<y1>           Set the y1 and it is the top left y of the rect.
      --y2=<y2>           Set the y2 and it is the bottom right y of the rect.
```

