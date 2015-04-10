# name of executable - change this to change the executables name
ELF=demo.elf

###################################################################################
# All object files

OBJS=  $(STARTUP) $(RTOSOBJ) $(PERIPHOBJ) partest.o main.o

# Object files with OBJDIR path
OBJSP= $(patsubst %.o, $(OBJDIR)/%.o, $(OBJS))
OBJDIR= ./objects

#FreeRTOS object files
RTOSOBJ= tasks.o queue.o list.o timers.o heap_1.o port.o

#Processor specific object files
STARTUP= startup_stm32f10x.o system_stm32f10x.o

#STM Peripheral object files
PERIPHOBJ= stm32f10x_rcc.o stm32f10x_gpio.o misc.o

###################################################################################

# All paths

# Library path
LIBROOT=../STM32F10x_StdPeriph_Lib_V3.5.0

#FreeRTOS path
FreeRTOS=../FreeRTOSV8.2.0/FreeRTOS/Source

# Code Paths
DEVICE=$(LIBROOT)/Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x
CORE=$(LIBROOT)/Libraries/CMSIS/CM3/CoreSupport
PERIPH=$(LIBROOT)/Libraries/STM32F10x_StdPeriph_Driver

# Search paths for perpheral library
vpath %.c $(CORE)
vpath %.c $(PERIPH)/src
vpath %.c $(DEVICE)

#FreeRTOS search paths
vpath %.c $(FreeRTOS)/
vpath %.c $(FreeRTOS)/portable/MemMang
vpath %.c $(FreeRTOS)/portable/GCC/ARM_CM3

###################################################################################

# Tools
GCCVER=4.9.1
GCCROOT=/home/rob/fyp/gcc-cross
GCCBIN=$(GCCROOT)/bin
GCCPREFIX=arm-unknown-eabi

CC=$(GCCBIN)/$(GCCPREFIX)-gcc
LD=$(GCCBIN)/$(GCCPREFIX)-gcc   #gcc acts as a wrapper
AR=$(GCCBIN)/$(GCCPREFIX)-ar
AS=$(GCCBIN)/$(GCCPREFIX)-as

###################################################################################

# Flags

# Processor specific
PTYPE= STM32F10X_CL
LDSCRIPT= stm32f100.ld

# compilation flags for gdb
CFLAGS  = -O0 -g

# Compilation Flags
FULLASSERT = -DUSE_FULL_ASSERT 
LDFLAGS+= -T$(LDSCRIPT) -mthumb -mcpu=cortex-m3 -nostdlib
LDLIBS+= $(GCCROOT)/lib/gcc/$(GCCPREFIX)/$(GCCVER)/libgcc.a
#LDLIBS+= ../newlib-arm-none-eabi/arm-none-eabi/newlib/libc.a
LDLIBS+= $(GCCROOT)/$(GCCPREFIX)/lib/libc.a
#LDLIBS+= ../arm-none-eabi-toolchain/lib/gcc/arm-none-eabi/4.9.3/armv7-m/libgcc.a
CFLAGS+= -mcpu=cortex-m3 -mthumb 
CFLAGS+= -I. -I$(DEVICE) -I$(CORE) -I$(PERIPH)/inc
CFLAGS+= -D$(PTYPE) -DUSE_STDPERIPH_DRIVER $(FULLASSERT)
CFLAGS+= -I$(FreeRTOS)/include -I$(FreeRTOS)/portable/MemMang -DGCC_ARMCM3=
CFLAGS+= -I$(GCCROOT)/$(GCCPREFIX)/include
#CFLAGS+= -I../newlib-arm-none-eabi/arm-none-eabi/newlib/libc/include

# Build executable 
$(ELF) : $(OBJSP)
	$(LD) $(LDFLAGS) -o $@ $(OBJSP) $(LDLIBS)

# compile and generate dependency info
$(OBJDIR)/%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@
	$(CC) -MM $(CFLAGS) $< > $(OBJDIR)/$*.d 

$(OBJDIR)/%.o: %.s
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJDIR)/*.o $(OBJSP:.o=.d) $(ELF) *~

debug: $(ELF)
	arm-none-eabi-gdb $(ELF)

#-include $(OBJSP:.o=.d)




