#include "spi.hpp"
 void SPI::SPI_Init(int dispositivo){
   if(dispositivo==Master){
      ConfiguracionsalidasMasterSPI;
      MConfiguracionMISO;
      MasterSSHIGH;
      MConfiguracionSPCR;
      MConfiguracionVelocidadTrasmicion;
      //SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
	   //SPSR &= ~(1<<SPI2X);		
   }
   else if(dispositivo==Slave){
      ConfiguracionSalidasSlaveSPI;
      SlaveConfiguracionMISO;
      SlaveConfiguracionSPCR;   
   }
 }

 uint8_t SPI::SPI_uint8_tTransmit(uint8_t message){
    char flush_buffer;
    MasterSSHIGH;
    SPDR=message;
    while(!(SPDR & (1<<SPIF))){
    }
    flush_buffer =SPDR;
    MasterSSLOW;
}

 void SPI::SPI_CaracterTransmit(char message){
   char flush_buffer;
   MasterSSLOW;   
   SPDR = message;
   int contador = 0;
   bool validador = false;
   while(!(SPSR & (1<<SPIF)));
   flush_buffer = SPDR;
   MasterSSHIGH;
 }

 void SPI::SPI_TextTransmit(char *menssage){
    while(*menssage != 0x00){
        SPI_CaracterTransmit(*menssage);
        _delay_ms(20);
        menssage++;   
    }    
 }

 uint8_t SPI::SPI_received(){
   PinConfiguration SS('B');
   SS.pinMode(INTPUT|pin2);
   SPDR= 0XFF;
   int contador=0;
   bool validador=false;
   while (validador==false){
      if((SPSR & (1<<SPIF)))validador=true;
      if(contador==1000){
         unsigned char borrar=SPDR;
         contador=0;
         SPDR= 0XFF;
      }
      contador++;
   }  
   return SPDR;
 }
unsigned char SPI::SPI_receivedChar(){
    SPDR= 0XFF;
    while(!(SPSR & (1<<SPIF)));
    return SPDR;
 }