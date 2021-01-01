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
   configAnalogPWM();
    DDRD |= (1<<PORTD2);
    for(int d=0;d<7;d++){
        _delay_ms(1000);
        PORTD &= ~(1<<PORTD2);
        _delay_ms(1000);
        PORTD |= (1<<PORTD2);
    }
   while (1){
       for(int d=0;d++;d<255){
           OCR2A=d;
           _delay_ms(100);
       }
       for(int d=255;d--;d>0){
           OCR2A=d;
           _delay_ms(100);
       }
   }
   

}

