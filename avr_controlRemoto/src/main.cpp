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

int main(){ 
    UART pantalla1;
    SPI iniciar;
    joystick control;
    
    pantalla1.uart_init();
    adc_init();
    sei();
    int datosZJoystick=10000;    
    iniciar.SPI_Init(Master);
    while (1){
        datosZJoystick=control.datoZ();
        if(control.validarEstadoZ()){
            pantalla1.UART_WriteInt(datosZJoystick);
            pantalla1.USART0SendByte('\n');
        }
        _delay_ms(100);
        pantalla1.UART_write_txt("este es el eje X");
        }
    

}