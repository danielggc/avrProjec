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
uint8_t data_array[]={'a','a','a','a','b',' ',' ',' ',' ',' ',' ',' ',' ',' '};
uint8_t tx_address[5] = {0,0,0,0,1};
uint8_t rx_address[5] = {0,0,0,0,1};

#define pinEjeY 5
#define pinEjeX 4
#define pinEjeZ 2
#define A1 1
#define A0 0
class cabiosVelocidad{
    public:
        cabiosVelocidad();
        void lecturaDatos();
        void difenciaRecorrido();
        bool validarEstadoX();
        bool validarEstadoY();
        bool validarEstadoZ();
        float datoX();
        float datoY();
        float datoZ();

        float cambioDatoX;
        float cambioDatoZ; 
        float cambioDatoY;
        float desplasamientoX;
        float desplasamientoZ; 
        float desplasamientoY;
};

cabiosVelocidad::cabiosVelocidad(){
    adc_init();
    cambioDatoX =0.0;
    cambioDatoZ =0.0 ;
    cambioDatoY =0.0;
    desplasamientoX =0.0;
    desplasamientoZ =0.0;
    desplasamientoY =0.0;
}

bool cabiosVelocidad::validarEstadoX(){
    if(cambioDatoX!=desplasamientoX){
        int diferencia=(cambioDatoX-desplasamientoX);
        if(diferencia<9)diferencia=diferencia*-1;
        if(diferencia>8){
            desplasamientoX=cambioDatoX;
            return true;
        }
        else{
            return false;    
        }
    }
    else
    {
        return false;
    }
}
bool cabiosVelocidad::validarEstadoZ(){
    if(cambioDatoZ!=desplasamientoZ){
        float diferencia (cambioDatoZ-desplasamientoZ);
        if(diferencia<9)diferencia=diferencia*-1;
        if(diferencia>8){
            desplasamientoZ=cambioDatoZ;
            return true;
        }
        else{
            return false;    
        }
    }
    else
    {
        return false;
    }
}
bool cabiosVelocidad::validarEstadoY(){
   if(cambioDatoY!=desplasamientoY){
        int diferencia=(cambioDatoY-desplasamientoY);
        if(diferencia<9)diferencia=diferencia*-1;
        if(diferencia>8){
            desplasamientoY=cambioDatoY;
            return true;
        }
        else{
            return false;    
        }
    }
    else
    {
        return false;
    }
}


float cabiosVelocidad::datoX(){
    cambioDatoX=adc_read(pinEjeX);
    return cambioDatoX;
}
float cabiosVelocidad::datoZ(){
    cambioDatoZ=adc_read(pinEjeZ);
    return cambioDatoZ;
}
float cabiosVelocidad::datoY(){
    cambioDatoY=adc_read(pinEjeY);
    return cambioDatoY;
}
int main(){
    UART pantalla1;
    pantalla1.uart_init();
    SPI iniciar;
    iniciar.SPI_Init(Master);
    char mensaje=' ';
    cabiosVelocidad contrles;
    float dato=0;
    Nrf24 antenaRX;
    antenaRX.nrf24_init();
    antenaRX.nrf24_config(); 
    antenaRX.nrf24_rx_address(rx_address); 
    antenaRX.nrf24_tx_address(tx_address); 
    while(1){ 
        antenaRX.nrf24_powerUpTx();
        dato=contrles.datoZ();  
        if(contrles.validarEstadoZ()){
            int largo=numeroUnidades(dato);
            char numeroChar[largo++];
            char *dirNumerochar=&numeroChar[0];
            int_to_char(dato,dirNumerochar,largo);
            for(int b=0;b<largo;b++){
                data_array[b]=numeroChar[b];
            }
            antenaRX.nrf24_send(data_array);
        }        
        _delay_ms(1000);
        for(int b=0;b<12;b++){
            data_array[b]=' ';
        }
        antenaRX.nrf24_powerDown();
     
    }

}

/*
dato=contrles.datoZ();
        pantalla1.UART_write_txt(" esto es X:: ");
        pantalla1.UART_WriteInt(dato);
        pantalla1.UART_write_txt("\n");

   dato=contrles.datoY();
        if(contrles.validarEstadoY()){
            pantalla1.UART_write_txt(" esto es X:: ");
            pantalla1.UART_WriteInt(dato);
            pantalla1.UART_write_txt("\n");
        }



 int largo=numeroUnidades(dato);
            char numeroChar[largo++];
            char *dirNumerochar=&numeroChar[0];
            int_to_char(dato,dirNumerochar,largo);
            numeroChar[largo++]=0x00; 
            dirNumerochar=&numeroChar[1];
            pantalla1.UART_write_txt(dirNumerochar);
     
     
     
     
     dato=contrles.datoX();
        if(contrles.validarEstadoX()){
           
        }
        dato=contrles.datoY();
        if(contrles.validarEstadoY()){
            
        }
        pantalla1.UART_WriteInt(1);
        pantalla1.UART_write_txt(" \n");
     
    
     
     
     
     
        */