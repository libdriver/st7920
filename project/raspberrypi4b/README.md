### 1. Chip

#### 1.1 Chip Info

chip name : Raspberry Pi 4B.

gpio pin: RS/RW/E GPIO22/GPIO17/GPIO27.

gpio pin: PSB GND.

### 2. Install

#### 2.1 Dependencies

Install the necessary dependencies.

```shell
sudo apt-get install libgpiod-dev pkg-config cmake -y
```

#### 2.2 Makefile

Build the project.

```shell
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

#### 2.3 CMake

Build the project.

```shell
mkdir build && cd build 
cmake .. 
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

Test the project and this is optional.

```shell
# open another terminal
./st7920_server 

# use the CMake terminal
make test
```

Find the compiled library in CMake. 

```cmake
find_package(st7920 REQUIRED)
```
#### 2.4 How to run

```shell
# open one terminal and run the server
./st7920_server 
```
```shell
# open another terminal and sent the command
./st7920 xxx xxx xxx ...
```

### 3. ST7920

#### 3.1 Command Instruction

​          st7920 is a basic command which can test all st7920 driver function:

​           -i        show st7920 chip and driver information.

​           -h       show st7920 help.

​           -p       show st7920 pin connections of the current board.

​           -t display        run st7920 display test. 

​           -c (basic (-init | -deinit | -str <string> | -displayon | -displayoff | -clear | -writepoint <x> <y> <color> | -rect <x1> <y1> <x2> <y2> <color>) | advance (-init | -deinit | -str <string> | -displayon | -displayoff | -clear | -writepoint <x> <y> <color> | -rect <x1> <y1> <x2> <y2> <color> | -disable_scroll | -scroll <addr> | -reverse_line <line>)))

​           -c basic -init        run st7920 basic init function. 

​           -c basic -deinit        run st7920 basic deinit function. 

​           -c basic -str <string>        run st7920 show string function. string means the shown string. 

​           -c basic -displayon        run st7920 display on function. 

​           -c basic -displayoff        run st7920 display off function. 

​           -c basic -clear        run st7920 clear screen function. 

​           -c basic -writepoint  <x> <y> <color>        run st7920 write pont function. x and y mean coordinate in screen. color means the filled color.

​           -c basic -rect <x1> <y1> <x2> <y2> <color>        run st7920 draw rectangle function . x1 means x start. y1 means y start. x2 means x end. y2 means y end. color means the filled color.

​           -c advance -init        run st7920 advance init function. 

​           -c advance -deinit        run st7920 advance deinit function. 

​           -c advance -str <string>        run st7920 show string function. string means the shown string. 

​           -c advance -displayon        run st7920 display on function. 

​           -c advance -displayoff        run st7920 display off function. 

​           -c advance -clear        run st7920 clear screen function. 

​           -c advance -writepoint  <x> <y> <color>        run st7920 write pont function. x and y mean coordinate in screen. color means the filled color.

​           -c advance -rect <x1> <y1> <x2> <y2> <color>        run st7920 draw rectangle function . x1 means x start. y1 means y start. x2 means x end. y2 means y end. color means the filled color.

​           -c advance -disable_scroll        run st7920 disable scroll function. 

​           -c advance -scroll <addr>        run st7920 scroll function. addr is the scroll address and 0 <= addr <= 0x3F.

​           -c advance -reverse_line <line>        run st7920 reverse line function.line is the reverse line and it can be "0" or "1".

#### 3.2 Command Example

```shell
./st7920 -i

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
./st7920 -p

st7920: RS connected to GPIO22(BCM).
st7920: RW connected to GPIO17(BCM).
st7920: E connected to GPIO27(BCM).
st7920: PSB connected to GND.
```

```shell
./st7920 -t display

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
./st7920 -c basic -str 12345abcdEFGH

st7920: 12345abcdEFGH.
```

```shell
./st7920 -c basic -init

st7920: init success.
```

```shell
./st7920 -c basic -displayoff

st7920: display off.
```

```shell
./st7920 -c basic -displayon

st7920: display on.
```

```shell
./st7920 -c basic -clear

st7920: clear screen.
```

```shell
./st7920 -c basic -deinit

st7920: deinit st7920.
```

```shell
./st7920 -c basic -writepoint 16 16 1

st7920: write point 16 16 1.
```

```shell
./st7920 -c basic -rect 0 0 32 32 1

st7920: draw rect 0 0 32 32.
```

```shell
./st7920 -c advance -init

st7920: init success.
```

```shell
./st7920 -c advance -str 12345abcdEFGH

st7920: 12345abcdEFGH.
```

```shell
./st7920 -c advance -displayoff

st7920: display off.
```

```shell
./st7920 -c advance -displayon

st7920: display on.
```

```shell
./st7920 -c advance -clear

st7920: clear screen.
```

```shell
./st7920 -c advance -writepoint 16 16 1

st7920: write point 16 16 1.
```

```shell
./st7920 -c advance -rect 0 0 32 32 1

st7920: draw rect 0 0 32 32.
```

```shell
./st7920 -c advance -deinit

st7920: deinit st7920.
```

```shell
./st7920 -c advance -disable_scroll

st7920: disable scroll.
```

```shell
./st7920 -c advance -scroll 16

st7920: set scroll 16.
```

```shell
./st7920 -c advance -reverse_line 0

st7920: set reverse line 0.
```

```shell
./st7920 -h

st7920 -i
	show st7920 chip and driver information.
st7920 -h
	show st7920 help.
st7920 -p
	show st7920 pin connections of the current board.
st7920 -t display
	run st7920 display test.
st7920 -c basic -init
	run st7920 basic init function.
st7920 -c basic -deinit
	run st7920 basic deinit function.
st7920 -c basic -str <string>
	run st7920 show string function.string means the shown string.
st7920 -c basic -displayon
	run st7920 display on function.
st7920 -c basic -displayoff
	run st7920 display off function.
st7920 -c basic -clear
	run st7920 clear screen function.
st7920 -c basic -writepoint <x> <y> <color>
	run st7920 write pont function.x and y mean coordinate in screen.color means the filled color.
st7920 -c basic -rect <x1> <y1> <x2> <y2> <color>
	run st7920 draw rectangle function.x1 means x start.y1 means y start.x2 means x end.y2 means y end.color means the filled color.
st7920 -c advance -init
	run st7920 advance init function.
st7920 -c advance -deinit
	run st7920 advance deinit function.
st7920 -c advance -str <string>
	run st7920 show string function.string means the shown string.
st7920 -c advance -displayon
	run st7920 display on function.
st7920 -c advance -displayoff
	run st7920 display off function.
st7920 -c advance -clear
	run st7920 clear screen function.
st7920 -c advance -writepoint <x> <y> <color>
	run st7920 write pont function.x and y mean coordinate in screen.color means the filled color.
st7920 -c advance -rect <x1> <y1> <x2> <y2> <color>
	run st7920 draw rectangle function.x1 means x start.y1 means y start.x2 means x end.y2 means y end.color means the filled color.
st7920 -c advance -disable_scroll
	run st7920 disable scroll function.
st7920 -c advance -scroll <addr>
	run st7920 scroll function.addr is the scroll address and 0 <= addr <= 0x3F.
st7920 -c advance -reverse_line <line>
	run st7920 reverse line function.line is the reverse line and it can be "0" or "1".
```
