#
#       !!!! Do NOT edit this makefile with an editor which replace tabs by spaces !!!!
#
##############################################################################################
#
# On command line:
#
# make all = Create project
#
# make clean = Clean project files.
#
# To rebuild project do "make clean" and "make all".
#
# Included originally in the yagarto projects. Original Author : Michael Fischer
# Modified to suit our purposes by Hussam Al-Hertani
# Use at your own risk!!!!!
##############################################################################################
# Start of default section
#
TRGT = arm-none-eabi-
CC   = $(TRGT)gcc
CP   = $(TRGT)objcopy
AS   = $(TRGT)gcc -x assembler-with-cpp
HEX  = $(CP) -O ihex
BIN  = $(CP) -O binary -S
MCU  = cortex-m0

# List all default C defines here, like -D_DEBUG=1
#para el micro STM32F051C8T6
# DDEFS = -DSTM32F051
#para el micro STM32F030K6T6
DDEFS = -DSTM32F030

# List all default ASM defines here, like -D_DEBUG=1
DADEFS =

# List all default directories to look for include files here
DINCDIR = ./src

# List the default directory to look for the libraries here
DLIBDIR =

# List all default libraries here
DLIBS =

#
# End of default section
##############################################################################################

##############################################################################################
# Start of user section
#

#
# Define project name and Ram = 0/Flash = 1 mode here
PROJECT        = Template_F030

# List all user C define here, like -D_DEBUG=1
UDEFS =

# Define ASM defines here
UADEFS =

# List C source files here
CORELIBDIR = ./cmsis_core
BOOTDIR = ./cmsis_boot

LINKER = ./cmsis_boot/startup

SRC  = ./src/main.c
SRC += $(BOOTDIR)/system_stm32f0xx.c
SRC += $(BOOTDIR)/syscalls/syscalls.c

SRC += ./src/adc.c
SRC += ./src/dma.c
SRC += ./src/dsp.c
SRC += ./src/gpio.c
SRC += ./src/it.c
SRC += ./src/tim.c
# SRC += ./src/spi.c
# SRC += ./src/uart.c
# SRC += ./src/flash_program.c
SRC += ./src/test_functions.c
SRC += ./src/hard.c



## Core Support
SRC += $(CORELIBDIR)/core_cm0.c


## Other Peripherals libraries

# List ASM source files here
ASRC = ./cmsis_boot/startup/startup_stm32f0xx.s

# List User Directories for Libs Headers
UINCDIR = $(BOOTDIR) \
          $(CORELIBDIR)
	#../paho.mqtt.embedded-c/MQTTPacket/src

# List the user directory to look for the libraries here
ULIBDIR =

# List all user libraries here
ULIBS =

# Define optimisation level here
# O1 optimiza size no significativo
# O2 size mas fuerte
# Os (size mas fuerte que O2)
# O3 el mas fuerte, seguro despues no corre
# O0 (no optimiza casi nada, mejor para debug)
OPT = -O0

#
# End of user defines
##############################################################################################
#
# Define linker script file here
#
LDSCRIPT = $(LINKER)/stm32_flash.ld
FULL_PRJ = $(PROJECT)_rom

INCDIR  = $(patsubst %,-I%,$(DINCDIR) $(UINCDIR))
LIBDIR  = $(patsubst %,-L%,$(DLIBDIR) $(ULIBDIR))

ADEFS   = $(DADEFS) $(UADEFS)

LIBS    = $(DLIBS) $(ULIBS)
MCFLAGS = -mcpu=$(MCU)

ASFLAGS = $(MCFLAGS) -g -gdwarf-2 -mthumb  -Wa,-amhls=$(<:.s=.lst) $(ADEFS)

# SIN INFO DEL DEBUGGER
#CPFLAGS = $(MCFLAGS) $(OPT) -gdwarf-2 -mthumb   -fomit-frame-pointer -Wall -Wstrict-prototypes -fverbose-asm -Wa,-ahlms=$(<:.c=.lst) $(DEFS)

# INFO PARA DEBUGGER + STRIP CODE + DUPLICATE GLOBALS ERROR
# CPFLAGS = $(MCFLAGS) $(OPT) -g -gdwarf-2 -fno-common -mthumb -fomit-frame-pointer -Wall -fdata-sections -ffunction-sections -fverbose-asm -Wa,-ahlms=$(<:.c=.lst) $(DDEFS)

# CON INFO PARA DEBUGGER + STRIP CODE
CPFLAGS = $(MCFLAGS) $(OPT) -g -gdwarf-2 -mthumb -fomit-frame-pointer -Wall -fdata-sections -ffunction-sections -fverbose-asm -Wa,-ahlms=$(<:.c=.lst) $(DDEFS)

# SIN DEAD CODE, hace el STRIP
LDFLAGS = $(MCFLAGS) -mthumb -lm --specs=nano.specs -Wl,--gc-sections -nostartfiles -T$(LDSCRIPT) -Wl,-Map=$(FULL_PRJ).map,--cref,--no-warn-mismatch $(LIBDIR)
# CON DEAD CODE
#LDFLAGS = $(MCFLAGS) -mthumb --specs=nano.specs -nostartfiles -T$(LDSCRIPT) -Wl,-Map=$(FULL_PRJ).map,--cref,--no-warn-mismatch $(LIBDIR)
#LDFLAGS = $(MCFLAGS) -mthumb -T$(LDSCRIPT) -Wl,-Map=$(FULL_PRJ).map,--cref,--no-warn-mismatch $(LIBDIR)

#
# makefile rules
#

assemblersources = $(ASRC)
sources = $(SRC)
OBJS  = $(SRC:.c=.o) $(ASRC:.s=.o)

objects = $(sources:.c=.o)
assobjects = $(assemblersources:.s=.o)

all: $(objects) $(assobjects) $(FULL_PRJ).elf $(FULL_PRJ).bin
	arm-none-eabi-size $(FULL_PRJ).elf
	gtags -q

$(objects): %.o: %.c
	$(CC) -c $(CPFLAGS) -I. $(INCDIR) $< -o $@

$(assobjects): %.o: %.s
	$(AS) -c $(ASFLAGS) $< -o $@

%elf: $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) $(LIBS) -o $@

%hex: %elf
	$(HEX) $< $@

%bin: %elf
	$(BIN)  $< $@

flash:
	sudo openocd -f stm32f0_flash.cfg

flash_lock:
	sudo openocd -f stm32f0_flash_lock.cfg

gdb:
	sudo openocd -f stm32f0_gdb.cfg

reset:
	sudo openocd -f stm32f0_reset.cfg

clean:
	rm -f $(OBJS)
	rm -f $(FULL_PRJ).elf
	rm -f $(FULL_PRJ).map
	rm -f $(FULL_PRJ).hex
	rm -f $(FULL_PRJ).bin
	rm -f $(SRC:.c=.lst)
	rm -f $(ASRC:.s=.lst)
	rm -f *.o
	rm -f *.out
	rm -f *.gcov
	rm -f *.gcda
	rm -f *.gcno


tests:
	# simple functions tests, copy functions to tests module into main
	gcc src/tests.c
	./a.out


tests_pwm:
	# first compile common modules (modules to test and dependencies)
	gcc -c --coverage src/pwm.c -I. $(INCDIR) -DSTM32F030
	# second auxiliary helper modules
	gcc -c src/tests_ok.c -I $(INCDIR)
	gcc --coverage src/tests_pwm.c pwm.o tests_ok.o
	./a.out
	# process coverage
	gcov pwm.c -m


tests_pwm_simul:
	# first compile common modules (modules to test and dependencies)
	gcc -c src/dsp.c -I. $(INCDIR)
	gcc -c src/pwm.c -I. $(INCDIR) -DSTM32F030
	# second auxiliary helper modules
	gcc -c src/tests_ok.c -I $(INCDIR)
	gcc -c src/tests_vector_utils.c -I $(INCDIR)
	gcc src/tests_pwm_simul.c dsp.o pwm.o tests_ok.o tests_vector_utils.o
	./a.out


tests_pwm_mapping:
	# first compile common modules (modules to test and dependencies)
	gcc -c src/pwm.c -I. $(INCDIR) -DSTM32F030
	# second auxiliary helper modules
	gcc -c src/tests_ok.c -I $(INCDIR)
	gcc -c src/tests_vector_utils.c -I $(INCDIR)
	gcc src/tests_pwm_mapping.c pwm.o tests_ok.o tests_vector_utils.o
	./a.out

tests_pwm_pre_post_simul:
	# first compile common modules (modules to test and dependencies)
	gcc -c src/dsp.c -I. $(INCDIR)
	gcc -c src/pwm.c -I. $(INCDIR) -DSTM32F030
	gcc -c src/filters_and_offsets.c -I. $(INCDIR) -DSTM32F030
	# second auxiliary helper modules
	gcc -c src/tests_ok.c -I $(INCDIR)
	gcc -c src/tests_vector_utils.c -I $(INCDIR)
	gcc src/tests_pwm_pre_post_simul.c filters_and_offsets.o dsp.o pwm.o tests_ok.o tests_vector_utils.o
	./a.out



# *** EOF ***
