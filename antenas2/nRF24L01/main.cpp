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
    UART pantalla1;
    char dato2[12];
    char *direccionDato=&dato2[0];
    adc_init();
    sei();
    SPI iniciar;
    iniciar.SPI_Init(Master);
    char mensaje=' ';
    Nrf24 antenaRX;
    pantalla1.uart_init();
    antenaRX.nrf24_init();
    antenaRX.nrf24_config(); 
    antenaRX.nrf24_rx_address(rx_address); 
    antenaRX.nrf24_tx_address(tx_address); 
    antenaRX.nrf24_powerUpRx();
    while(1){ 
        if(antenaRX.nrf24_dataReady()){
            antenaRX.nrf24_getData(data_array); 
            pantalla1.USART0SendByte('\n');
            for (int i = 0; i < 13; i++){
                pantalla1.USART0SendByte(data_array[i]);
            }
            pantalla1.USART0SendByte('\n');
            for(int i=0;i<13;i++){                    
                data_array[i]=' ';
            }
            _delay_ms(10);
        }
   
    }

}

