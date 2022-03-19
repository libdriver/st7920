CC     := gcc
SRC1   := $(wildcard ./interface/src/*.c) \
		  $(wildcard ./driver/src/*.c) \
		  $(wildcard ./src/main.c) \
		  $(wildcard ../../src/*.c) \
		  $(wildcard ../../test/*.c) \
		  $(wildcard ../../example/*.c)
LIBS   := -lgpiod
CFLAGS := -O3 \
		  -I ./interface/inc/ \
		  -I ../../interface/ \
		  -I ../../src/ \
		  -I ../../test/ \
		  -I ../../example/
all: st7920_server st7920
st7920_server : $(SRC1)
		 "$(CC)" $(CFLAGS) $^ $(LIBS) -o $@
SRC2   := $(wildcard ./src/client.c)
st7920 : $(SRC2)
		 "$(CC)" $(CFLAGS) $^ $(LIBS) -o $@