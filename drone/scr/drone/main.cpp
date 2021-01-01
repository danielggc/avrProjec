
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h> 
#include <stdint.h> 
#include <stdlib.h>
#include "nRF24L01/mirf.hpp"
#include "library/UART/UART.hpp"
#include "library/SPI/spi.hpp"
#include "tranformVar/transformVar.hpp"
#define  conversor 255/1023
uint8_t q = 0;
uint8_t data_array[18];
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
            if(antenaRX.nrf24_dataReady()){
                antenaRX.nrf24_getData(data_array); 
                pantalla1.USART0SendByte('\n');
                for (int i = 0; i < 13; i++){
                    pantalla1.USART0SendByte(data_array[i]);
                }
                for(int i=0;i<5;i++){
                    
                    velocidad[i]=data_array[i];
                }
                long dd=char_to_int(direccionDato);
                datosVelocidad=dd*conversor;
                if(datosVelocidad!=RespaldoDatosVelocidad)OCR2A =datosVelocidad;
                RespaldoDatosVelocidad=datosVelocidad;
                pantalla1.USART0SendByte('\n');
                direccionDato =&velocidad[0];
            }
   
            
    } 

    /*
    configAnalogPWM();
    while (1){
        if (char_to_int(direccionDato)==1234){
            pantalla1.UART_write_txt("funciono");
        }
        _delay_ms(1000);
       for(unsigned char d=0; d<255;d++){
            OCR2A =d;
            _delay_ms(100);

        }
        for(unsigned char d=255; d>0;d--){
            OCR2A =d;
            _delay_ms(100);

        }
        
    }

*/
}



