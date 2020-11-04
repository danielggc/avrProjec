#include <avr/io.h>
#ifndef __AVR_ATmega328P__
#define __AVR_ATmega328P__
#endif


#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h> 
#include <stdint.h> 
#include <stdlib.h>
#include <avr/interrupt.h>
#include <util/twi.h>
#include "library/UART/UART.hpp"
#include "library/SPI/spi.hpp"
#include "I2C/i2c.hpp"
#include "MPU_6050/mpu-6050.hpp"
#define EEPROM_Write_Addess		0xA0
#define EEPROM_Read_Addess		0xA1
MPU6050 mpu__6050;
int main(){
    uint8_t data[] = "test";
	uint8_t *dir=&data[0];
    UART pantalla1;
    pantalla1.uart_init();
    pantalla1.UART_write_txt(" que empieze lo bueno \n"); 
	twi_init();
	mpu__6050.begin();
	while (1){
		mpu__6050.update();
		int gyroX=mpu__6050.getGyroX();
		int accX= mpu__6050.getRawAccX();
		pantalla1.UART_write_txt("\naceleracion\n");
		pantalla1.UART_WriteInt(accX);
		_delay_ms(1000);
	}
    /*uint8_t data[] = "test";
	uint8_t *dir=&data[0];
    UART pantalla1;
    pantalla1.uart_init();
    pantalla1.UART_write_txt(" que empieze lo bueno \n"); 
	twi_init();
	while (1){	
		twi_write(0x05,dir,5, NULL);
		_delay_ms(5000);
	}
	*/
}



