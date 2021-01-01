#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h> 
#include <stdint.h> 
#include <stdlib.h>
#include "nRF24L01/mirf.h"
#include "library/UART/UART.hpp"
#include "library/SPI/spi.hpp"
int main(){
    UART pantalla;
    pantalla.uart_init();
    for(int i=0;i<5;i++){
        pantalla.UART_write_txt("hola");
    }
    SPI comunicacionMaestro;
    comunicacionMaestro.SPI_Init(Slave);
    while (1){        
        unsigned char mensaje = comunicacionMaestro.SPI_receivedChar();   
        pantalla.USART0SendByte(mensaje);
    }
    
}
