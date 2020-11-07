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
#include "codificadoControl/codificadoControl.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
using namespace std;

int main(){ 
    uint8_t data_array[]={'1','2','3','4',' ','  ',' ',' ',' ',' ',' ',' ',' '};
    uint8_t tx_address[5] = {0,0,0,0,1};
    uint8_t rx_address[5] = {0,0,0,0,1};
    UART pantalla1;
    SPI iniciar;
    joystick control;
    codificadoControl droneR2;
    pulsadorJoystinck0 pulsador ;
    pantalla1.uart_init();
    adc_init();
    sei();
    uint16_t datosYJoystick=0;    
    uint16_t datosXJoystick=0;
    while (1){
        if(control.validarEstadoY()){
            control.validarEstadoX();
            datosYJoystick=control.cambioDatoY;
            datosXJoystick =control.cambioDatoX;
            droneR2.codificadoEnvio(datosXJoystick,datosYJoystick,0,true);          
        }
        _delay_ms(10);
    }
}



/*


    if(control.validarEstadoY()){
            control.validarEstadoX();
            pantalla1.UART_write_txt("   Y:");
            datosYJoystick=control.cambioDatoY;
            pantalla1.UART_WriteInt(datosYJoystick);
            datosXJoystick =control.cambioDatoX;
            pantalla1.UART_write_txt("   X:");
            pantalla1.UART_WriteInt(datosXJoystick);
            if(pulsador.pulsador1()==true){
                pantalla1.UART_write_txt("      Pulsado");
            }
            else{
                pantalla1.UART_write_txt("      Suelto");
            }
            pantalla1.USART0SendByte('\n');
        }


*/