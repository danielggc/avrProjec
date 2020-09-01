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
    pantalla1.uart_init();
    nrf24_init();
    nrf24_config(2,4);
    while(1){    
        uint8_t estado= nrf24_getStatus();
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
/*
  while(1){
      
        estado= antena1.nrf24_dataReady();
        if(estado==1){
            
            pantalla.UART_write_txt("configuracion terminada");
            antena1.nrf24_getData(payload);
            pantalla.USART_Uint8_tWrite(payload[2]);
            if(payload[0]=='t'){
                pantalla.UART_write_txt("funciono o solo sera mentira");
            }
            for(int d=0;d<5;d++){
                mensaje[d]=payload[d];
                payload[d]=' ';
            }
            pantalla.UART_write_txt(mensaje);
            _delay_ms(1000);
        }
        else if(estado==4){
            pantalla.UART_write_txt("esta en modo espera");
        }
        antena1.nrf24_powerUpTx();
    }
    */