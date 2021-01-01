#include <avr/io.h>
#include "../328.hpp"
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>
#define A 'A'
#define B 'B'
#define C 'C'
#define D 'D'
#define E 'E'
#define F 'F'
#define OUTPUT 1<<0
#define INTPUT 1<<1
#define LOW   1<<0
#define HIGHT 1<<1
#define  pin7 1<<2
#define  pin6 1<<3
#define  pin5 1<<4
#define  pin4 1<<5
#define  pin3 1<<6
#define  pin2 1<<7
#define  pin1 1<<8
#define  pin0 1<<9
#define USART_BAUDRATE 9600
#define UBRR_VALUE  (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

//spi 
#define SPI_MOSI    PB2
#define SPI_MISO    PB3
#define SPI_SCK     PB1
#define SPI_CS      PB0
#define SPI_FREQ    8000 // 8 KHz

class SPI{
    public:
      void SPI_Init(int);
      void SPI_CaracterTransmit(char); 
      uint8_t SPI_uint8_tTransmit(uint8_t);
      uint8_t SPI_received(uint8_t);
      void SPI_TextTransmit(char *);
};
class UART{
    public:
        void uart_init ();
        void USART0SendByte(unsigned char);
        uint8_t USART0ReceiveByte();
        void UART_write_txt(char *);
        
};

class PinConfiguration{
  private:
    char portType;
  public:
    PinConfiguration(char);
    void pinMode(unsigned int) ;
    void diguitalWrite(unsigned int);
    int Pind(unsigned int);
};