#define SPI_MOSI    PB2
#define SPI_MISO    PB3
#define SPI_SCK     PB1
#define SPI_CS      PB0
#define SPI_FREQ    8000 // 8 KHz
#define pb0 (1<<0)
#define pb1 (1<<1)
#define pb2 (1<<2)
#define pb3 (1<<3)
#define pb4 (1<<4)
#define pb5 (1<<5)
#define pb6 (1<<6)
#define pb7 (1<<7)
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>
#include <avr/iom2560.h>
#include "PIN.hpp"
    class SPI{
      public:
        void SPI_Init(int,unsigned int);
        void SPI_CaracterTransmit(char); 
        uint8_t SPI_uint8_tTransmit(uint8_t);
        uint8_t SPI_received(uint8_t);
        void SPI_TextTransmit(char *);
    };

