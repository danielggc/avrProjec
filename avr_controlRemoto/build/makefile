DEVICE     = atmega328p
CLOCK      = 8000000
PROGRAMMER = arduino
PORT	   = /dev/ttyACM0 
BAUD       = 115200
FILENAME   = ../src/main
COMPILE    = avr-g++ -Wall  -Os -DF_CPU=$(CLOCK) -mmcu=$(DEVICE)
PIN 	   =../src/library/pinMode/PIN
UART	   =../src/library/UART/UART
SPI		   =../src/library/SPI/spi
TRANFORM_VAR =../src/library/tranformVar/transformVar
nRF24	   =../src/nRF24L01/mirf
Joystick = ../src/joystick/joystick
codificadoControl= ../src/codificadoControl/codificadoControl
all:   build upload clean 
build:
	$(COMPILE) -c  $(codificadoControl).cpp
	$(COMPILE) -c  $(Joystick).cpp
	$(COMPILE) -c  $(TRANFORM_VAR).cpp
	$(COMPILE) -c  $(nRF24).cpp
	$(COMPILE) -c  $(SPI).cpp
	$(COMPILE) -c  $(UART).cpp
	$(COMPILE) -c  $(PIN).cpp
	$(COMPILE) -c  $(FILENAME).cpp 
	$(COMPILE) -o  $(FILENAME).elf main.o PIN.o  UART.o spi.o mirf.o transformVar.o joystick.o codificadoControl.o

		
	avr-objcopy -j .text -j .data -O ihex $(FILENAME).elf $(FILENAME).hex
	avr-size --format=avr --mcu=$(DEVICE) $(FILENAME).elf

	


upload:
	avrdude -v -p $(DEVICE) -c $(PROGRAMMER) -P $(PORT) -b $(BAUD) -D -F -U flash:w:$(FILENAME).hex:i 

clean:
	#chmod +x limpiarCompilacion.sh
	sh limpiarCompilacion.sh
	
	



