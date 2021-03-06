# Name: Makefile
# Author: <insert your name here>
# Copyright: <insert your copyright message here>
# License: <insert your license reference here>

# DEVICE ....... The AVR device you compile for
# CLOCK ........ Target AVR clock rate in Hertz
# OBJECTS ...... The object files created from your source files. This list is
#                usually the same as the list of source files with suffix ".o".
# PROGRAMMER ... Options to avrdude which define the hardware you use for
#                uploading to the AVR and the interface where this hardware
#                is connected.
# FUSES ........ Parameters for avrdude to flash the fuses appropriately.

DEVICE     = attiny2313
CLOCK      = 8000000
#CLOCK      = 1000000
PROGRAMMER = -c usbasp 
OBJECTS    = main.o
#FUSES      = -U lfuse:w:0x64:m -U hfuse:w:0xdd:m -U efuse:w:0xff:m
FUSES      = -U lfuse:w:0xe4:m -U hfuse:w:0xdf:m -U efuse:w:0xff:m



######################################################################
######################################################################

# Tune the lines below only if you know what you are doing:
#BINPATH = /home/nico/.arduino15/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/
BINPATH =
#AVRDUDE_PATH= /home/nico/.arduino15/packages/arduino/tools/avrdude/6.3.0-arduino9/bin/
AVRDUDE_PATH=
#AVRDUDE = avrdude $(PROGRAMMER) -p $(DEVICE)
AVRDUDE = $(AVRDUDE_PATH)avrdude $(PROGRAMMER) -p attiny2313
COMPILE = $(BINPATH)avr-gcc -Wall -Os -DF_CPU=$(CLOCK) -mmcu=$(DEVICE)
SIZE    = $(BINPATH)avr-size -C --mcu=$(DEVICE) main.elf

# symbolic targets:
all:	main.hex size

.c.o:
	$(COMPILE) -c $< -o $@
.cpp.o:
	$(COMPILE) -c $< -o $@

.S.o:
	$(COMPILE) -x assembler-with-cpp -c $< -o $@
# "-x assembler-with-cpp" should not be necessary since this is the default
# file type for the .S (with capital S) extension. However, upper case
# characters are not always preserved on Windows. To ensure WinAVR
# compatibility define the file type manually.

.c.s:
	$(COMPILE) -S $< -o $@

flash:	all
	$(AVRDUDE) -U flash:w:main.hex:i
size:
	$(SIZE)
fuse:
	$(AVRDUDE) $(FUSES)

install: flash fuse

# if you use a bootloader, change the command below appropriately:
load: all
	bootloadHID main.hex

clean:
	rm -f main.hex main.elf $(OBJECTS)

# file targets:
main.elf: $(OBJECTS)
	$(COMPILE) -o main.elf $(OBJECTS)

main.hex: main.elf
	rm -f main.hex
	avr-objcopy -j .text -j .data -O ihex main.elf main.hex
# If you have an EEPROM section, you must also create a hex file for the
# EEPROM and add it to the "flash" target.

# Targets for code debugging and analysis:
disasm:	main.elf
	avr-objdump -d main.elf

cpp:
	$(COMPILE) -E main.c