DEVICE     = atmega2560
CLOCK      = 8000000
PROGRAMMER = usbasp
PORT	   = /dev/ttyS0
BAUD       = 19200
FILENAME   = main
COMPILE    = avr-g++ -Wall  -Os -DF_CPU=$(CLOCK) -mmcu=$(DEVICE)
PINMODEDIR   =./pinMode/pinMode
PINMODE      =pinMode
INCLUDE_PATH =./UART/pinMode/
UART		 =./UART/UART
SPI			 =./SPI/spi
all:   build upload 
build:
	$(COMPILE) -c  $(SPI).cpp
	$(COMPILE) -c  $(UART).cpp
	$(COMPILE) -c  $(FILENAME).cpp 
	$(COMPILE) -c  $(PINMODEDIR).cpp
	$(COMPILE) -o  $(FILENAME).elf $(FILENAME).o $(PINMODE).o UART.o spi.o
	avr-objcopy -j .text -j .data -O ihex $(FILENAME).elf $(FILENAME).hex
	avr-size --format=avr --mcu=$(DEVICE) $(FILENAME).elf

upload:
	avrdude -v -p $(DEVICE) -c $(PROGRAMMER) -P $(PORT) -b $(BAUD) -U flash:w:$(FILENAME).hex:i 

clean:
	rm main.o
	rm main.elf
	rm main.hex


