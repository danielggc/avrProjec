#include "SPI.hpp"
void SPI::SPI_Init(int dispositivo,unsigned int puertos){
    if(puertos & pb0){
        PinConfiguration salidas('B');
        salidas.pinMode(pin0|OUTPUT);
        salidas.pinMode(pin1|OUTPUT);
        salidas.pinMode(pin2|OUTPUT);
        PinConfiguration MISO('B');
        MISO.pinMode(pin3|INTPUT);
        salidas.diguitalWrite(pin0|HIGHT);
    }
    SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
    SPSR &= ~(1<<SPI2X); 
 }
 uint8_t SPI::SPI_uint8_tTransmit(uint8_t message){
    PinConfiguration ss('B');
    char flush_buffer;
    ss.pinMode(pin0|OUTPUT);
    ss.diguitalWrite(pin0|LOW);
    PinConfiguration led13('B');
    led13.pinMode(pin7|OUTPUT);
    led13.diguitalWrite(pin7|HIGHT);
    SPDR=message;
    while(!(SPDR & (1<<SPIF))){
       
    }    
    flush_buffer =SPDR;
    ss.diguitalWrite(pin7|HIGHT);
    led13.diguitalWrite(pin7|LOW);
}
 void SPI::SPI_CaracterTransmit(char message){
    char flush_buffer;
    PinConfiguration led13('B');
    led13.pinMode(pin7|OUTPUT);
    PinConfiguration ss('B');
    ss.pinMode(pin0|OUTPUT);
    ss.diguitalWrite(pin0|LOW);
    led13.diguitalWrite(pin7|HIGHT);
    _delay_ms(2000);
    SPDR=message;
    while(!(SPDR & (1<<SPIF))){
    }
    led13.diguitalWrite(pin7|LOW);
    ss.diguitalWrite(pin0|HIGHT);
    flush_buffer =SPDR;
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
