#include "spi.hpp"
#include "../UART/UART.hpp"
#include <avr/interrupt.h>
#ifndef __AVR_ATmega328P__
#define __AVR_ATmega328P__
#endif

 void SPI::SPI_Init(int dispositivo){
    UART pantalla;
    pantalla.uart_init();
   if(dispositivo==Master){
      ConfiguracionsalidasMasterSPI;
      MConfiguracionMISO;
      SPCR = (1<<SPE) | (1<<MSTR) | (1<<SPR0) | (1<<SPIE) ;
      //SPCR = ((1<<SPE)|(0<<SPIE)|(0<<DORD)|(1<<MSTR)|(0<<SPR1)|(1<<SPR0)|(0<<CPOL)|(0<<CPHA));    
      //SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
	   //SPSR &= ~(1<<SPI2X);		
      SPSR = (1<<SPI2X);   
   }
   else if(dispositivo==Slave){
      pantalla.UART_write_txt("\nconfiguracion esclavo\n");
      ConfiguracionSalidasSlaveSPI;
      SlaveConfiguracionMISO;
      SlaveConfiguracionSPCR; 
   }
 }

uint8_t SPI::SPI_uint8_tTransmit(uint8_t message){
   UART pantalla1;
   pantalla1.uart_init();
   SPDR=message;
   char flush_buffer;
   int contador=0;
   pantalla1.UART_write_txt("\nhola llegue al SPI_UINT8\n");
   while((SPSR & (1<<SPIF))==0){
  
   };
   flush_buffer=SPDR;
    return flush_buffer;
}

  void SPI::SPI_CaracterTransmit(char message){
   char flush_buffer;
   SPDR = message;
   int contador = 0;
   bool validador = false;
   while (validador == false){
      if((SPDR & (1<<SPIF)))validador=true;
      if(contador == 1000){
         contador=0;
         SPDR = message;
      }
      contador++;
   }
   flush_buffer = SPDR;
 }

 void SPI::SPI_TextTransmit(char *menssage){
    while(*menssage != 0x00){
        SPI_CaracterTransmit(*menssage);
        _delay_ms(20);
        menssage++;   
    }    
 }



 uint8_t SPI::SPI_received(){
   SPDR= 0XFF;
   int contador=0;
   bool validador=false;
   while( (SPSR & (1<<SPIF))==0 ){
     
   }  
   return SPDR;
 }

unsigned char SPI::SPI_receivedChar(){
    SPDR= 0XFF;
    while((SPSR & (1<<SPIF)==0));
    return SPDR;
 }



