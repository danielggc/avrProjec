#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h> 
#include <stdint.h> 
#include <stdlib.h>
#include "nRF24L01/mirf.hpp"
#include "library/UART/UART.hpp"
#include "library/SPI/spi.hpp"
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
uint8_t temp;
uint8_t q = 0;
uint8_t data_array[4];
uint8_t tx_address[5] = {0xD7,0xD7,0xD7,0xD7,0xD7};
uint8_t rx_address[5] = {0xE7,0xE7,0xE7,0xE7,0xE7};

int main(){
   char mensaje=' ';
    UART pantalla1;
    pantalla1.uart_init();
    nrf24_init();
         uint8_t estado= nrf24_getStatus();
        int_to_binario(estado);
    nrf24_config(2,4);
    nrf24_tx_address(tx_address);
          estado= nrf24_getStatus();
        int_to_binario(estado);
    pantalla1.UART_write_txt("hola");
    pantalla1.UART_write_txt("hola");
    pantalla1.UART_write_txt("hola");
    nrf24_rx_address(rx_address); 
    nrf24_tx_address(tx_address);
          estado= nrf24_getStatus();
        int_to_binario(estado);
    while(1){    
         estado= nrf24_getStatus();
        int_to_binario(estado);
        if(nrf24_dataReady()){
            nrf24_getData(data_array);        
            pantalla1.UART_write_txt("blalal");
        }
        _delay_ms(1000);
    }   
}
