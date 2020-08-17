#include "UART/UART.hpp"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h> 
#include <stdint.h> 
#include <stdlib.h>
int main(){
    unsigned char u8TempData;
    UART comunicacion;
    PinConfiguration dd('B');
    dd.pinMode(LOW|pin7);
    comunicacion.uart_init();
    comunicacion.UART_write_txt("hola como estas");
    while(1){
        u8TempData = comunicacion.USART0ReceiveByte();
        comunicacion.USART0SendByte(u8TempData);
    }
    
}