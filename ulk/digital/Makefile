CROSS_COMPILE=/ulk/toolchain/CodeSourcery/Sourcery_G++_Lite/bin/arm-none-linux-gnueabi-

INCL = /usr/include/ulk

TOOLCHAIN=gcc

OUTFILE_SDRAM=digital

AS=$(CROSS_COMPILE)as
CC=$(CROSS_COMPILE)gcc
LD=$(CROSS_COMPILE)ld
NM= $(CROSS_COMPILE)nm
SIZE=$(CROSS_COMPILE)size
OBJCOPY=$(CROSS_COMPILE)objcopy
OBJDUMP=$(CROSS_COMPILE)objdump

CCFLAGS=-I$(INCL) -c -O3 -Wall -mcpu=arm9

LIBS_PATH1=/ulk/toolchain/CodeSourcery/Sourcery_G++_Lite/lib/gcc/arm-none-linux-gnueabi/4.2.1
LIBS_PATH2=/usr/lib
#LIBS_PATH1=/opt/mv_pro_4.0.1/montavista/pro/devkit/arm/v5t_le/lib/gcc/armv5tl-montavista-linuxeabi/3.4.3
LIBS = -L$(LIBS_PATH2) -lulk -L$(LIBS_PATH1) -lgcc
LDFLAGS+=-T project.lds -Map digital.map 


OBJS= main.o 

      

rebuild: clean all

all: sdram
sdram: $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) $(LIBS) -Ttext 0x82000000 -n -O elf32-arm -o $(OUTFILE_SDRAM).elf
	$(OBJCOPY) --strip-debug --strip-unneeded $(OUTFILE_SDRAM).elf -O binary $(OUTFILE_SDRAM).bin
	$(OBJCOPY) $(OUTFILE_SDRAM).elf -O srec $(OUTFILE_SDRAM).srec

main.o: main.c 
	 $(CC) -c $(CCFLAGS) main.c -o main.o

	

clean:
	 rm -rf *.bin
	rm -rf *.elf 
	 rm -rf *.map
	 rm -rf *.o
	
	
    