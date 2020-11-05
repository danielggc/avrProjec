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
#include "joystick/joystick.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
using namespace std;

int main(){ 
    
    UART pantalla1;
    SPI iniciar;
    joystick control;  
    pantalla1.uart_init();
    adc_init();
    sei();
    uint16_t datosZJoystick=0;    
    iniciar.SPI_Init(Master);
    uint16_t datosXJoystick=0;

    int dato =52 ;
    char buffer[33];
    itoa(dato,buffer,10);
    pantalla1.UART_write_txt(buffer);
      while (1){
        if(control.validarEstadoZ()){
            control.validarEstadoX();
            pantalla1.UART_write_txt("   Y:");
            datosZJoystick=control.cambioDatoZ;
            pantalla1.UART_WriteInt(datosZJoystick);
            datosXJoystick =control.cambioDatoX;
            pantalla1.UART_write_txt("   X:");
            pantalla1.UART_WriteInt(datosXJoystick);
            pantalla1.USART0SendByte('\n');
        }
    }
    

}





/*

      datosZJoystick=control.cambioDatoZ;
            datosXJoystick =control.cambioDatoX;
            pantalla1.UART_WriteInt(datosZJoystick);
            pantalla1.USART0SendByte(' ');
            _delay_ms(50);
            pantalla1.UART_WriteInt(datosXJoystick);
            pantalla1.USART0SendByte('\n');
            _delay_ms(50);



            pantalla1.UART_write_txt("   Y:");
            datosZJoystick=control.cambioDatoZ;
            datosXJoystick =control.cambioDatoX;
            itoa(datosZJoystick,buffer,10);
            pantalla1.UART_write_txt(buffer);
            pantalla1.UART_write_txt("   X:");
            _delay_ms(50);
            control.validarEstadoX();
            itoa(datosXJoystick,buffer,10);
            pantalla1.UART_write_txt(buffer);
            pantalla1.USART0SendByte('\n');
            _delay_ms(50);

*/