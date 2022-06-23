#
# Makefile
#

# 1. gcc 

#CC = gcc
CC = /home/f1c200s/buildroot-2021.02.6/buildroot-2021.02.6/output/host/bin/arm-buildroot-linux-uclibcgnueabi-gcc
CFLAGS = -Wall -Wshadow -Wundef -Wmaybe-uninitialized -fbounds-check 

LVGL_DIR = ${shell pwd}

CFLAGS += -O3 -g3 -I$(LVGL_DIR)/


# 2.add lts

#LDFLAGS += -lSDL2 -lm
LDFLAGS += -L/home/f1c200s/lvgl/tslib-1.22/build/lib/libts.so -lpthread

BIN = lvgl_7110_demo


#Collect the files to compile
MAINSRC = ./main.c

LVGL_DIR_NAME = lvgl

include $(LVGL_DIR)/lvgl/lvgl.mk
include $(LVGL_DIR)/lv_drivers/lv_drivers.mk
include $(LVGL_DIR)/lv_examples/lv_examples.mk

# 3.
# CSRCS +=$(LVGL_DIR)/mouse_cursor_icon.c

OBJEXT ?= .o

AOBJS = $(ASRCS:.S=$(OBJEXT))
COBJS = $(CSRCS:.c=$(OBJEXT))

MAINOBJ = $(MAINSRC:.c=$(OBJEXT))

SRCS = $(ASRCS) $(CSRCS) $(MAINSRC)
OBJS = $(AOBJS) $(COBJS)

## MAINOBJ -> OBJFILES


.PHONY: all

all: clean default

%.o: %.c
	@$(CC)  $(CFLAGS) -c $< -o $@
	@echo "CC $<"
    
default: $(AOBJS) $(COBJS) $(MAINOBJ)
	@echo "hello"
	$(CC) -o $(BIN) $(MAINOBJ) $(AOBJS) $(COBJS) $(LDFLAGS)

clean: 
	rm -f $(BIN) $(AOBJS) $(COBJS) $(MAINOBJ)

