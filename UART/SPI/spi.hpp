#include "/home/dgc7/ejersiciosLibros/avr/UART/pinMode/pinMode.hpp"
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>
class SPI{
    public:
      void SPI_Init(int);
      void SPI_CaracterTransmit(char);  
      uint8_t SPI_received(uint8_t);
      void SPI_TextTransmit(char *);
};