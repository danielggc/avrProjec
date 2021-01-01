#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h> 
#include <stdint.h> 
#include <stdlib.h>
#include "nRF24L01/mirf.hpp"
#include "library/UART/UART.hpp"
#include "library/SPI/spi.hpp"
int int_to_binario(int8_t );
char int_to_char(int,char *);

uint8_t temp;
uint8_t q = 0;
uint8_t data_array[4];
uint8_t tx_address[5] = {0xD7,0xD7,0xD7,0xD7,0xD7};
uint8_t rx_address[5] = {0xE7,0xE7,0xE7,0xE7,0xE7};

int main(){
    UART pantalla;
    pantalla.uart_init();
    SPI comunicacion;
    comunicacion.SPI_Init(Master);
    pantalla.UART_write_txt("empesemos");
    int contador=0;
    while (1){
        contador++;
        comunicacion.SPI_TextTransmit("\nhaciendo una prueba \n ");
        _delay_ms(200);
        comunicacion.SPI_CaracterTransmit(contador+'0');
        _delay_ms(5000);

    }
    
}
char int_to_char(int numero,char *cadena){
    int respaldo=numero;
    int numeroDecenas=0;
    while (respaldo>0){
       respaldo=respaldo/10;
       numeroDecenas++;
    }
    for(int d=0;d<numeroDecenas;d++){
        
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