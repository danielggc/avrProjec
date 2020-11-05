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
#include "tranformVar/transformVar.hpp"

uint8_t temp;
uint8_t q = 0;
uint8_t data_array[]={'1','2','3','4',' ','  ',' ',' ',' ',' ',' ',' ',' '};
uint8_t tx_address[5] = {0,0,0,0,1};
uint8_t rx_address[5] = {0,0,0,0,1};


int main(){
    DDRD |= (1<<PORTD2);
    for(int d=0;d<7;d++){
        _delay_ms(1000);
        PORTD &= ~(1<<PORTD2);
        _delay_ms(1000);
        PORTD |= (1<<PORTD2);
    }
    PORTD &= ~(1<<PORTD2);
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
    pantalla1.UART_write_txt("empezando la trasmicion");
    while(1){ 
       
        antenaRX.nrf24_powerUpTx();
        uint16_t dato =adc_read(5);
        int largo=numeroUnidades(dato);
        antenaRX.nrf24_send(data_array);
        temp =  antenaRX.nrf24_lastMessageStatus();
        pantalla1.USART0SendByte(temp+'0');
        pantalla1.USART0SendByte('\n');
        if(temp == NRF24_TRANSMISSON_OK){                    
            pantalla1.UART_write_txt("se envio bien la señal");
            _delay_ms(100);
        }
        else if(temp == NRF24_MESSAGE_LOST){                     
            pantalla1.UART_write_txt("esta en proceso");
            _delay_ms(100);  
        }
        temp = antenaRX.nrf24_retransmissionCount();
        DDRD |= (1<<PORTD2);
    for(int d=0;d<7;d++){
        _delay_ms(100);
        PORTD &= ~(1<<PORTD2);
        _delay_ms(100);
        PORTD |= (1<<PORTD2);
    }
        _delay_ms(1000);
        antenaRX.nrf24_powerDown();
    }

}

