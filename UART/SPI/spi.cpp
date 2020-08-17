#include "spi.hpp"
 void SPI::SPI_Init(int dispositivo){
    DDRB=(0<<PB3)|(1<<PB2)|(1<<PB1)|(1<<PB0);
    SPCR =(0<<SPIE)|(1<<SPE)|(1<<DORD)|(dispositivo<<MSTR)|(0<<CPOL)|(1<<SPR0)|(0<<SPR1); 
 }
 void SPI::SPI_CaracterTransmit(char message){
    PinConfiguration SS('B');
    SS.diguitalWrite(pin0|LOW);
    SPDR=message;
    while(!(SPDR & (1<<SPIF)));
    SS.diguitalWrite(pin0|HIGHT);
 }

 void SPI::SPI_TextTransmit(char *menssage){
    while(*menssage != 0x00){
        SPI_CaracterTransmit(*menssage);
        menssage++;
        
    }    
 }

 uint8_t SPI::SPI_received(uint8_t contrasena){
    //SPDR= 0XFF
    SPDR=contrasena;
    while(!(SPSR & (1<<SPIF)));
    return SPDR;
 }