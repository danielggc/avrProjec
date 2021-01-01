DEVICE     = atmega328p
CLOCK      = 8000000
PROGRAMMER = arduino
PORT	   = /dev/ttyACM0 
BAUD       = 115200
FILENAME   = main
COMPILE    = avr-g++ -Wall  -Os -DF_CPU=$(CLOCK) -mmcu=$(DEVICE)
PIN 	   =./library/pinMode/PIN
UART	   =./library/UART/UART
SPI		   =./library/SPI/spi
TRANFORM_VAR =./library/tranformVar/transformVar
nRF24	   =./nRF24L01/mirf
I2C		   =./I2C/i2c
MPU6050    =./MPU_6050/mpu-6050
all:   build upload  clean
build:

	$(COMPILE) -c  $(MPU6050).cpp
	$(COMPILE) -c  $(I2C).cpp
	$(COMPILE) -c  $(TRANFORM_VAR).cpp
	$(COMPILE) -c  $(nRF24).cpp
	$(COMPILE) -c  $(SPI).cpp
	$(COMPILE) -c  $(UART).cpp
	$(COMPILE) -c  $(PIN).cpp
	$(COMPILE) -c  $(FILENAME).cpp 
	$(COMPILE) -o  $(FILENAME).elf $(FILENAME).o PIN.o UART.o spi.o mirf.o transformVar.o
	avr-objcopy -j .text -j .data -O ihex $(FILENAME).elf $(FILENAME).hex
	avr-size --format=avr --mcu=$(DEVICE) $(FILENAME).elf

upload:
	avrdude -v -p $(DEVICE) -c $(PROGRAMMER) -P $(PORT) -b $(BAUD) -U flash:w:$(FILENAME).hex:i 

clean:
	rm *.o
	rm main.elf
	rm main.hex
