DEVICE     = atmega2560
CLOCK      = 8000000
PROGRAMMER = stk500v2
PORT	   = /dev/ttyUSB0
BAUD       = 115200
FILENAME   = main
COMPILE    = avr-g++ -Wall  -Os -DF_CPU=$(CLOCK) -mmcu=$(DEVICE)
PIN 	   =./library/pinMode/PIN
UART	   =./library/UART/UART
SPI		   =./library/SPI/spi
nRF24	   =./nRF24L01/mirf
all:   build upload 
build:
	$(COMPILE) -c  $(nRF24).cpp
	$(COMPILE) -c  $(SPI).cpp
	$(COMPILE) -c  $(UART).cpp
	$(COMPILE) -c  $(PIN).cpp
	$(COMPILE) -c  $(FILENAME).cpp 
	$(COMPILE) -o  $(FILENAME).elf $(FILENAME).o PIN.o UART.o spi.o mirf.o
	avr-objcopy -j .text -j .data -O ihex $(FILENAME).elf $(FILENAME).hex
	avr-size --format=avr --mcu=$(DEVICE) $(FILENAME).elf

upload:
	avrdude -v -p $(DEVICE) -c $(PROGRAMMER) -P $(PORT) -b $(BAUD) -D -F -U flash:w:$(FILENAME).hex:i 

clean:
	rm main.o
	rm main.elf
	rm main.hex

