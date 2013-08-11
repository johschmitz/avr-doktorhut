# MCU name
MCU = atmega168

# Compiler
CC = avr-gcc
CFLAGS = -mmcu=$(MCU) -Wall -Wstrict-prototypes -Os -mcall-prologues

OBJCOPY=avr-objcopy

all : doktorhut.hex

doktorhut.hex : doktorhut.elf
	$(OBJCOPY) -R .eeprom -O ihex doktorhut.elf doktorhut.hex
doktorhut.elf : doktorhut.o
	$(CC) $(CFLAGS) -o doktorhut.elf -Wl,-Map,doktorhut.map doktorhut.o
doktorhut.o : doktorhut.c
	$(CC) $(CFLAGS) -c doktorhut.c

clean :
	rm -f *.o *.map *.out *.hex *.elf

