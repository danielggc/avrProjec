#include <avr/io.h>
#ifndef __AVR_ATmega328P__
#define __AVR_ATmega328P__
#endif
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/interrupt.h> 
#include <stdint.h> 
#include <stdlib.h>
#include "nRF24L01/mirf.hpp"
#include "library/UART/UART.hpp"
#include "library/SPI/spi.hpp"
#include "library/pinMode/PIN.hpp"
#include "library/tranformVar/transformVar.hpp"

uint8_t temp;
uint8_t q = 0;
uint8_t data_array[]={' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '};
uint8_t tx_address[5] = {0,0,0,0,1};
uint8_t rx_address[5] = {0,0,0,0,1};


int main(){
   
    UART pantalla1;
    pantalla1.uart_init();
    char dato2[12];
    char *direccionDato=&dato2[0];
    adc_init();
    sei();
    SPI iniciar;
    iniciar.SPI_Init(Master);
    char mensaje=' ';
    while(1){ 
        pantalla1.UART_write_txt(" \n ");
        uint16_t dato =adc_read(5);
        pantalla1.UART_write_txt(" joystick1 Y::");
        pantalla1.UART_WriteInt(dato);        
        dato =adc_read(4);
        pantalla1.UART_write_txt(" joystick1 X::");
        pantalla1.UART_WriteInt(dato);
        pantalla1.UART_write_txt(" \n ");

        dato =adc_read(2);
        pantalla1.UART_write_txt(" joystick2 Y::");
        pantalla1.UART_WriteInt(dato);        
        dato =adc_read(3);
        pantalla1.UART_write_txt(" joystick2 X::");
        pantalla1.UART_WriteInt(dato);
        pantalla1.UART_write_txt(" \n ");
        _delay_ms(700) ;
        char *direccionDato=&dato2[0];
    }

}


