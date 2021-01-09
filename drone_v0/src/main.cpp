#include <avr/io.h>
#ifndef __AVR_ATmega328P__
#define __AVR_ATmega328P__
#endif
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdint.h> 
#include <stdlib.h>
#include "nRF24L01/mirf.hpp"
#include "library/UART/UART.hpp"
#include "library/SPI/spi.hpp"
#include "library/pinMode/PIN.hpp"
#include "library/tranformVar/transformVar.hpp"
#include "joystick/joystick.hpp"
#include "codificadoControl/codificadoControl.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "motores/motores.hpp"
#include "I2C/i2c.hpp"
#include "MPU_6050/mpu-6050.hpp"
#include <util/twi.h>
#include "balanceo/balanceo.hpp"
using namespace std;
#define EEPROM_Write_Addess		0xA0
#define EEPROM_Read_Addess		0xA1


int main(){ 
    balanceo drone_v0;    
    UART pantalla1;
    motores motoresABCD;
    pantalla1.uart_init();
    pantalla1.UART_write_txt(" que empieze lo bueno \n"); 
    motoresABCD.motorA(30);
    motoresABCD.motorB(30);
    motoresABCD.motorC(30);
    motoresABCD.motorD(30);
    while (1){
        drone_v0.estabilisarDrone();
        _delay_ms(500);       
        pantalla1.UART_WriteInt(motoresABCD.motorA());
        pantalla1.UART_write_txt("\n");
   }
    
}

