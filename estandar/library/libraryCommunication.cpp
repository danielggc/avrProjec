#include "libraryCommunication.hpp"

//UART
void UART::uart_init(){
    PinConfiguration rx('E');
    PinConfiguration txt('E');
    rx.pinMode(pin0|INTPUT);
    txt.pinMode(pin1|OUTPUT);
	UCSR0A = (0<<TXC0)|(0<<U2X0)|(0<<MPCM0);
	UCSR0B = (1<<RXCIE0)|(0<<TXCIE0)|(0<<UDRIE0)|(1<<RXEN0)|(1<<TXEN0)|(0<<UCSZ02)|(0<<TXB80);
	UCSR0C = (0<<UMSEL01)|(0<<UMSEL00)|(0<<UPM01)|(0<<UPM00)|(0<<USBS0)|(1<<UCSZ01)|(1<<UCSZ00)|(0<<UCPOL0);
	UBRR0 = 103;								//NO DUPLICA VELOCIDAD 9600B A 160000

}
void UART::USART0SendByte(unsigned char caracter){
    while(!(UCSR0A&(1<<5)));
        UDR0 = caracter;
}
void UART::UART_write_txt(char *cadena){
    while(*cadena !=0x00){
        USART0SendByte(*cadena);
        cadena++;
    }
}
uint8_t UART::USART0ReceiveByte(){ 
    if(UCSR0A&(1<<7))return UDR0;
    else return 0;
    
}


////SPI


void SPI::SPI_Init(int dispositivo){
    // si es 1 es el maestro si es 0 el esclavo
    DDRB |= (1 << SPI_MOSI) | (1 << SPI_SCK) | (1 << SPI_CS) | (0 << SPI_MISO);
    //DDRB=(0<<PB3)|(1<<PB2)|(1<<PB1)|(1<<PB0);
    SPCR =(0<<SPIE)|(1<<SPE)|(1<<DORD)|(dispositivo<<MSTR)|(0<<CPOL)|(1<<SPR0)|(0<<SPR1); 
 }
 uint8_t SPI::SPI_uint8_tTransmit(uint8_t message){
    PinConfiguration SS('B');
    SS.diguitalWrite(pin0|LOW);
    SPDR=message;
    while(!(SPDR & (1<<SPIF)));
    SS.diguitalWrite(pin0|HIGHT);
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

//// pinConfiguration


PinConfiguration::PinConfiguration(char _portType){
    portType=_portType;
}
void PinConfiguration::pinMode(unsigned int _operaciones){
    unsigned int operaciones = _operaciones;
    if(operaciones & LOW){
         if(portType == 'B'){
            if(operaciones & pin7){
                DDRB |= (1 << PORTB7); 
            }
            else if(operaciones & pin6){
                DDRB |= (1 << PORTB6); 
            }
            else if (operaciones & pin5){
                DDRB |= (1 << PORTB5); 
            }
            else if (operaciones & pin4){
                DDRB |= (1 << PORTB4); 
            }
            else if (operaciones & pin3){
                DDRB |= (1 << PORTB3); 
            }
            else if (operaciones & pin2){
                DDRB |= (1 << PORTB2); 
            }
            else if (operaciones & pin1){
                DDRB |= (1 << PORTB1); 
            }
            else if (operaciones & pin0){
                DDRB |= (1 << PORTB0); 
            }
        }
    }
    if(operaciones & HIGHT){
        if(portType == 'B'){
            if(operaciones & pin7){
                DDRB &= ~(1 << PORTB7); 
            }
            else if(operaciones & pin6){
                DDRB &= ~(1 << PORTB6); 
            }
            else if (operaciones & pin5){
                DDRB &= ~(1 << PORTB5); 
            }
            else if (operaciones & pin4){
                DDRB &= ~(1 << PORTB4); 
            }
            else if (operaciones & pin3){
                DDRB &= ~(1 << PORTB3); 
            }
            else if (operaciones & pin2){
                DDRB &= ~(1 << PORTB2); 
            }
            else if (operaciones & pin1){
                DDRB &= ~(1 << PORTB1); 
            }
            else if (operaciones & pin0){
                DDRB &= ~(1 << PORTB0); 
            }
        }
    }
}

void PinConfiguration::diguitalWrite(unsigned int _operaciones){
    unsigned int operaciones = _operaciones;
if(portType  ==  'B'){
        if(operaciones & pin7){
            if(operaciones & HIGHT ){
                PORTB |= (1 << PORTB7);
            }
            else{
                PORTB &= ~(1 << PORTB7);
            }
        }    
        else if(operaciones & pin6){
            if(operaciones & HIGHT ){
                PORTB |= (1 << PORTB6);
            }
            else{
                PORTB &= ~(1 << PORTB6);
            }
        }
        else if(operaciones & pin5){
            if(operaciones & HIGHT ){
                PORTB |= (1 << PORTB5);
            }
            else{
                PORTB &= ~(1 << PORTB5);
            }
        }
        else if(operaciones & pin4){
            if(operaciones & HIGHT ){
                PORTB |= (1 << PORTB4);
            }
            else{
                PORTB &= ~(1 << PORTB4);
            }
        }            
        else if(operaciones & pin3){
            if(operaciones & HIGHT ){
                PORTB |= (1 << PORTB3);
            }
            else{
                PORTB &= ~(1 << PORTB3);
            }
        }
        else if(operaciones & pin2){
            if(operaciones & HIGHT ){
                PORTB |= (1 << PORTB2);
            }
            else{
                PORTB &= ~(1 << PORTB2);
            }
        }
        else if(operaciones & pin1){
            if(operaciones & HIGHT ){
                PORTB |= (1 << PORTB1);
            }
            else{
                PORTB &= ~(1 << PORTB1);
            }
        }
        else if(operaciones & pin0){
            if(operaciones & HIGHT ){
                PORTB |= (1 << PORTB0);
            }
            else{
                PORTB &= ~(1 << PORTB0);
            }
        }
    }
}






