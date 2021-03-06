
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h> 
#include <stdint.h> 
#include <stdlib.h>
#include "nRF24L01/mirf.hpp"
#include "library/UART/UART.hpp"
#include "library/SPI/spi.hpp"
#include "library/pinMode/PIN.hpp"
#include "library/tranformVar/transformVar.hpp"
#define  conversor 255/1023
uint8_t temp;
uint8_t q = 0;
uint8_t data_array[]={'a','s','a','a','D','a','a','a','f','D','G','E','Q','L'};
uint8_t tx_address[5] = {0,0,0,0,1};
uint8_t rx_address[5] = {0,0,0,0,1};
long  datosVelocidad;
long  RespaldoDatosVelocidad;
char velocidad[18];
int main(){
    UART pantalla1;
    Nrf24 antenaRX ;
    pantalla1.uart_init();
    antenaRX.nrf24_init();
    configAnalogPWM();
    uint8_t estado;
    char mensaje=' ';
    estado= antenaRX.nrf24_getStatus();
    int_to_binario(estado);
    antenaRX.nrf24_config();
    estado= antenaRX.nrf24_getStatus();
    int_to_binario(estado);
    antenaRX.nrf24_rx_address(rx_address); 
    antenaRX.nrf24_tx_address(tx_address);
    estado=  antenaRX.nrf24_getStatus();
    int_to_binario(estado);  
    char *direccionDato =&velocidad[0];
    while(1){  
        antenaRX.nrf24_powerUpTx();
        _delay_ms(100);
        antenaRX.nrf24_send(data_array);
        temp =  antenaRX.nrf24_lastMessageStatus();
        if(temp == NRF24_TRANSMISSON_OK){                    
            pantalla1.UART_write_txt("> Tranmission went OK\r\n");
            _delay_ms(100);
        }
        else if(temp == NRF24_MESSAGE_LOST){                    
            pantalla1.UART_write_txt("> Message is lost ...\r\n");  
            _delay_ms(100);  
        }
        temp = antenaRX.nrf24_retransmissionCount();
		pantalla1.UART_write_txt("> Retranmission count: %d\r\n");
        pantalla1.USART_Uint8_tWrite(temp);
        _delay_ms(100);
        antenaRX.nrf24_powerDown();
    }

            
} 



