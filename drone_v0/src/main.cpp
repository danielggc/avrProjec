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

using namespace std;

int main(){ 
    DDRD |= (1<<PORTD2);
    for(int d=0;d<7;d++){
        _delay_ms(1000);
        PORTD &= ~(1<<PORTD2);
        _delay_ms(1000);
        PORTD |= (1<<PORTD2);
    }
    DDRB |= ( 1<< PB1 ); 
    DDRB |= ( 1<< PB2 ); 
    ICR1 = 0xFFFF;
    TCCR1A |=  (1 << COM1A1) | (0 << COM1A0) ; 
    TCCR1A |=  (0 << WGM11) | (1 << WGM10) ;
    TCCR1B |= (0 << CS12) | (1 << CS11) | ( 0 << CS10 );
    OCR1A=255;
    TCCR1A |=  (1 << COM1B1)| (0 << COM1B0);
    OCR1B=255;
}











/*
      for(int d=0;d++;d<255){
           OCR1A=d;
           _delay_ms(100);
       }
       for(int d=255;d--;d>0){
           OCR1A=d;
           _delay_ms(100);
       }
       _delay_ms(10000);
 
*/