#ifndef SPI_HEADER
#define SPI_HEADER

#include "../pinMode/PIN.hpp"
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>
#define MasterMISO PORTB4 
#define MasterMOSI PORTB3
#define MasterSCK  PORTB5
#define MasterSS   PORTB2
//mosi sck ss salidas
#define SleveMISO PORTB4 
#define SleveMOSI PORTB3
#define SleveSCK  PORTB5
#define SleveSS   PORTB2

#define MasterSSHIGH (PORTB |= (1<<PB0))
#define MasterSSLOW (PORTB &= ~(1<<PB0))

#define ConfiguracionsalidasMasterSPI (DDRB |= ((1<<PORTB3)|(1<<PORTB5)|(1<<PORTB0)|(1<<PORTB1)))
// entrada miso
#define MConfiguracionMISO (DDRB &= ~(1<<PORTB4))
#define MConfiguracionSPCR (SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0))
#define MConfiguracionVelocidadTrasmicion (SPSR &= ~(1<<SPI2X))	
///slave
#define ConfiguracionSalidasSlaveSPI (DDRB &= ~(1<<PB3)|(1<<PB2)|(1<<PB5))
#define SlaveConfiguracionMISO (DDRB |= (1<<PB4))
#define SlaveConfiguracionSPCR (SPCR =  (1<<SPE)|(1<<SPR0))

#define Master 1
#define Slave 0



class SPI{
    public:
      void SPI_Init(int);
      void SPI_CaracterTransmit(char);  
      uint8_t SPI_received();
      void SPI_TextTransmit(char *);
      uint8_t SPI_uint8_tTransmit(uint8_t);
      unsigned char SPI_receivedChar();


};
extern void spi_init();
extern void spi_transfer_sync (uint8_t * dataout, uint8_t * datain, uint8_t len);
extern void spi_transmit_sync (uint8_t * dataout, uint8_t len);
extern uint8_t spi_fast_shift (uint8_t data);


#endif