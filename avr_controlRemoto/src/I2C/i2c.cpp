# include "i2c.hpp"
#include <avr/iom2560.h>

uint8_t I2c::rxBuffer[BUFFER_LENGTH];
uint8_t I2c::rxBufferIndex = 0;
uint8_t I2c::rxBufferLength = 0;

uint8_t I2c::txAddress = 0;
uint8_t I2c::txBuffer[BUFFER_LENGTH];
uint8_t I2c::txBufferIndex = 0;
uint8_t I2c::txBufferLength = 0;

uint8_t I2c::transmitting = 0;

void I2c::iniciar(){
    DDRD  = ((1<<TW_SCL_PIN)|(1<<TW_SDA_PIN));
    PORTD = ((1<<TW_SCL_PIN)|(1<<TW_SDA_PIN));  
	TWBR  = 2;                  
	TWCR |= (1<<TWEN);         
}

void I2c::beginTransmission(uint8_t address)
{
    transmitting = 1;
    txAddress = address;
    txBufferIndex = 0;
    txBufferLength = 0;
}

uint8_t I2c::endTransmission(uint8_t sendStop){
    int8_t ret = twi_writeTo(txAddress, txBuffer, txBufferLength, sendStop);
    txBufferIndex = 0;
    txBufferLength = 0;
    transmitting = 0;
    return ret;
}


uint8_t twi_writeTo(uint8_t address, uint8_t* data, uint8_t length, uint8_t sendStop){
    


}

uint8_t I2c::enviarDatos(unsigned char dato){
    uint8_t status;
    TWDR = dato;
    TWDR = ((1<<TWINT)|(1<<TWEN));
    espera();
    status =estado();
    if(status==0x28){
        return 0;
    }
    else if(status==0x30){
        return 1;
    }
    else return 2;
}

uint8_t I2c::I2C_Start(unsigned char address) {
    uint8_t status;
    TWCR=(1<<TWSTA)|(1<<TWEN)|(1<<TWINT);
    espera();
    status=estado();
    if(status!=0x08){
        return 0;
    }
    TWDR = address;
    TWCR=(1<<TWEN)|(1<<TWINT);
    espera();
    status = estado();
    if(status==0x18){
        return 1;
    }
    else if (status==0x20){
        return 2;
    }
    return 3;
    
}
uint8_t I2c::I2C_Repeated_Start(unsigned char address) {
    uint8_t status;
    TWCR=(1<<TWSTA)|(1<<TWEN)|(1<<TWINT);
    espera();
    status=estado();
    if(status!=0x08){
        return 0;
    }
    TWDR = address;
    TWCR=(1<<TWEN)|(1<<TWINT);
    espera();
    status = estado();
    if(status==0x40){
        return 1;
    }
    else if (status==0x48){
        return 2;
    }
    return 3;
    
}

void I2c::I2C_Stop(){
    TWCR=(1<<TWSTO)|(1<<TWINT)|(1<<TWEN);
    while(TWCR&(1<<TWSTO));	
}




void I2c::setAddress(uint8_t address){
    TWAR=(address<<1);
}
void I2c::espera(){
    while((TWCR & (1<<TWINT))==0);
}
void I2c::iniciarComunicacion(){
    TWCR = (1<<TWINT)|(1<<TWSTO)|(1<<TWEN);
    espera();
}

unsigned char I2c::recibirDatos_ACK(){
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA);
	espera();
	return TWDR;
}

unsigned char  I2c::recibirDatos_nACK(){
    TWCR = (1<<TWINT)|(1<<TWEN);
    espera();
	return TWDR;
}
uint8_t I2c::estado(){
    uint8_t estadoI2c=TWSR&0xF8;
    return estadoI2c;
}


