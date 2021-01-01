#if defined(__AVR__)
#include <avr/iom2560.h>

#include <math.h>
#include <stdlib.h>
#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <compat/twi.h>
#include "twi.hpp"

#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif

#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif


static volatile uint8_t twi_state;
static volatile uint8_t twi_slarw;
static volatile uint8_t twi_sendStop;			
static volatile uint8_t twi_inRepStart;			

static void (*twi_onSlaveTransmit)(void);
static void (*twi_onSlaveReceive)(uint8_t*, int);

static uint8_t twi_masterBuffer[TWI_BUFFER_LENGTH];
static volatile uint8_t twi_masterBufferIndex;
static volatile uint8_t twi_masterBufferLength;

static uint8_t twi_txBuffer[TWI_BUFFER_LENGTH];
static volatile uint8_t twi_txBufferIndex;
static volatile uint8_t twi_txBufferLength;

static uint8_t twi_rxBuffer[TWI_BUFFER_LENGTH];
static volatile uint8_t twi_rxBufferIndex;

static volatile uint8_t twi_error;


void twi_init(void)
{
    twi_state = TWI_READY;
    twi_sendStop = true;		
    twi_inRepStart = false;
    DDRD  = ((1<<TW_SCL_PIN)|(1<<TW_SDA_PIN));
    PORTD = ((1<<TW_SCL_PIN)|(1<<TW_SDA_PIN));  
    cbi(TWSR, TWPS0);
    cbi(TWSR, TWPS1);
    TWBR  = 2;                  
    TWCR |= (1<<TWEN);     
}


void twi_setAddress(uint8_t address)
{
  TWAR = address << 1;
}


uint8_t twi_readFrom(uint8_t address, uint8_t* data, uint8_t length, uint8_t sendStop)
{
  uint8_t i;
  if(TWI_BUFFER_LENGTH < length){
    return 0;
  }
  while(TWI_READY != twi_state){
    continue;
  }
  twi_state = TWI_MRX;
  twi_sendStop = sendStop;
  twi_error = 0xFF;
  twi_masterBufferIndex = 0;
  twi_masterBufferLength = length-1;  
  twi_slarw = TW_READ;
  twi_slarw |= address << 1;
  if (true == twi_inRepStart) {
    twi_inRepStart = false;			
    TWDR = twi_slarw;
    TWCR = _BV(TWINT) | _BV(TWEA) | _BV(TWEN) | _BV(TWIE);	
  }
  else
    TWCR = _BV(TWEN) | _BV(TWIE) | _BV(TWEA) | _BV(TWINT) | _BV(TWSTA);
  while(TWI_MRX == twi_state){
    continue;
  }

  if (twi_masterBufferIndex < length)
    length = twi_masterBufferIndex;

  for(i = 0; i < length; ++i){
    data[i] = twi_masterBuffer[i];
  }
	
  return length;
}


uint8_t twi_writeTo(uint8_t address, uint8_t* data, uint8_t length, uint8_t wait, uint8_t sendStop)
{
  uint8_t i;

  if(TWI_BUFFER_LENGTH < length){
    return 1;
  }

  while(TWI_READY != twi_state){
    continue;
  }
  twi_state = TWI_MTX;
  twi_sendStop = sendStop;
  twi_error = 0xFF;

  twi_masterBufferIndex = 0;
  twi_masterBufferLength = length;
  
  for(i = 0; i < length; ++i){
    twi_masterBuffer[i] = data[i];
  }
  
  twi_slarw = TW_WRITE;
  twi_slarw |= address << 1;
  
  if (true == twi_inRepStart) {
  
    twi_inRepStart = false;			
    TWDR = twi_slarw;				
    TWCR = _BV(TWINT) | _BV(TWEA) | _BV(TWEN) | _BV(TWIE);	
  }
  else
    TWCR = _BV(TWINT) | _BV(TWEA) | _BV(TWEN) | _BV(TWIE) | _BV(TWSTA);	

  while(wait && (TWI_MTX == twi_state)){
    continue;
  }
  
  if (twi_error == 0xFF)
    return 0;	
  else if (twi_error == TW_MT_SLA_NACK)
    return 2;	
  else if (twi_error == TW_MT_DATA_NACK)
    return 3;	
  else
    return 4;
}









void espera(){
    while((TWCR & (1<<TWINT))==0);
}
void iniciarComunicacion(){
    TWCR = (1<<TWINT)|(1<<TWSTO)|(1<<TWEN);
    espera();
}
void enviarDatos(unsigned char dato){
    TWDR = dato;
    TWDR = ((1<<TWINT)|(1<<TWEN));
    espera();
}
unsigned char recibirDatos_ACK(){
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA);
	espera();
	return TWDR;
}

unsigned char  recibirDatos_nACK(){
    TWCR = (1<<TWINT)|(1<<TWEN);
    espera();
	return TWDR;
}
uint8_t estado(){
    uint8_t estadoI2c=TWSR & 0Xf8;
    return estadoI2c;
}
/*
void twi_reply(uint8_t ack)
{
  if(ack){
    TWCR = _BV(TWEN) | _BV(TWIE) | _BV(TWINT) | _BV(TWEA);
  }else{
	  TWCR = _BV(TWEN) | _BV(TWIE) | _BV(TWINT);
  }
}


void twi_stop(void)
{
  TWCR = _BV(TWEN) | _BV(TWIE) | _BV(TWEA) | _BV(TWINT) | _BV(TWSTO);

 
  while(TWCR & _BV(TWSTO)){
    continue;
  }

  twi_state = TWI_READY;
}


void twi_releaseBus(void)
{
  TWCR = _BV(TWEN) | _BV(TWIE) | _BV(TWEA) | _BV(TWINT);

  twi_state = TWI_READY;
}

*/