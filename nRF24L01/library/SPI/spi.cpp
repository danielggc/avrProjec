#include "spi.hpp"
 void SPI::SPI_Init(int dispositivo){
   
   if(dispositivo==Master){
      ConfiguracionsalidasMasterSPI;
      MConfiguracionMISO;
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
    SPDR=message;
    while(!(SPSR & (1<<SPIF))){
    }
    return SPDR;
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


#define PORT_SPI    PORTB
#define DDR_SPI     DDRB
#define DD_MISO     DDB4
#define DD_MOSI     DDB3
#define DD_SS       DDB2
#define DD_SCK      DDB5


