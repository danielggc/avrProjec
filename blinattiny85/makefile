DEVICE     = attiny85
CLOCK      = 8000000
PROGRAMMER = usbasp
PORT	   = /dev/ttyS0
BAUD       = 9600
FILENAME   = main
COMPILE    = avr-g++ -Wall  -Os -DF_CPU=$(CLOCK) -mmcu=$(DEVICE) 
libraryCommunication =./library/libraryCommunication
SRC     := src
OUT_DIR := target
OBJ_DIR := obj
all:   build upload 
build:
	$(COMPILE) -c  $(FILENAME).cpp 
	$(COMPILE) -o  $(FILENAME).elf $(FILENAME).o 
	avr-objcopy -j .text -j .data -O ihex $(FILENAME).elf $(FILENAME).hex 
	avr-size --format=avr --mcu=$(DEVICE) $(FILENAME).elf

upload:
	mkdir -p $(OUT_DIR)/$(OBJ_DIR)
	avrdude -v -p $(DEVICE) -c $(PROGRAMMER) -P $(PORT) -b $(BAUD) -U flash:w:$(FILENAME).hex:i 
	mv *.o $(OUT_DIR)/$(OBJ_DIR)/
	mv *.elf $(OUT_DIR)/$(OBJ_DIR)/
clean:
	rm -rf $(OBJ_DIR)

