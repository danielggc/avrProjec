#include <avr/io.h>

#include <util/delay.h>
#include <avr/interrupt.h> 
#include <stdint.h> 
#include <stdlib.h>
#include "nRF24L01/mirf.hpp"
#include "library/UART/UART.hpp"
#include "library/SPI/spi.hpp"
int int_to_binario(int8_t );
uint8_t temp;
uint8_t q = 0;
uint8_t data_array[4];
uint8_t tx_address[5] = {0xD7,0xD7,0xD7,0xD7,0xD7};
uint8_t rx_address[5] = {0xE7,0xE7,0xE7,0xE7,0xE7};
int main(){
    char mensaje=' ';
    UART pantalla1;
    Nrf24 antenaRX;
    pantalla1.uart_init();
    
    antenaRX.nrf24_init();
    antenaRX.nrf24_config();
    
    while(1){    
        uint8_t estado= antenaRX.nrf24_getStatus();
        int_to_binario(estado);    
        _delay_ms(1000);
    }
}
int int_to_binario(int8_t numero){
    UART pantalla1;
    pantalla1.uart_init();
    for(int i=7;i!=-1;i--){
        if(numero & (1<<i)){
            pantalla1.USART0SendByte('1');
        }
        else{
            pantalla1.USART0SendByte('0');
        }
    }
    pantalla1.USART0SendByte('\n');
}
