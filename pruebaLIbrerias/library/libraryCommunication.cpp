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

//// pinConfiguration


PinConfiguration::PinConfiguration(char _portType){
    portType=_portType;
}
int PinConfiguration::Pind(unsigned int _pinRead){
    unsigned int pinRead =_pinRead;    
    if(portType == 'B'){
        if(pinRead & pin7){
            if (~PINB & (1 << PB7)){
                return 1;
            }                
        }
        else if(pinRead & pin6){
            if (~PINB & (1 << PB6)){
                return 1;
            }                
        }
        else if(pinRead & pin5){
            if (~PINB & (1 << PB5)){
                return 1;
            }        
        }            
        else if(pinRead & pin4){
            if (~PINB & (1 << PB4)){
                return 1;
            }        
        }
        else if(pinRead & pin3){
            if (~PINB & (1 << PB3)){
                return 1;
            }                
        }        
        else if(pinRead & pin2){
            if (~PINB & (1 << PB2)){
                return 1;
            }        
        }        
        else if(pinRead & pin1){
            if (~PINB & (1 << PB1)){
                return 1;
            }                
        }
        else if(pinRead & pin0){
            if (~PINB & (1 << PB0)){
                return 1;
            }                
        }  
        return 0;                  
    }
    if(portType == 'H'){
        if(pinRead & pin7){
            if (~PINH & (1 << PH7)){
                return 1;
            }                
        }
        else if(pinRead & pin6){
            if (~PINH & (1 << PH6)){
                return 1;
            }                
        }
        else if(pinRead & pin5){
            if (~PINH & (1 << PH5)){
                return 1;
            }                
        }            
        else if(pinRead & pin4){
            if (~PINH & (1 << PH4)){
                return 1;
            }        
        }
        else if(pinRead & pin3){
            if (~PINH & (1 << PH3)){
                return 1;
            }                
        }        
        else if(pinRead & pin2){
            if (~PINH & (1 << PH2)){
                return 1;
            }                
        }        
        else if(pinRead & pin1){
            if (~PINH & (1 << PH1)){
                return 1;
            }                
        }
        else if(pinRead & pin0){
            if (~PINH & (1 << PH0)){
                return 1;
            }
                
        }
        return 0;                    
    }
    return 0;
}
void PinConfiguration::pinMode(unsigned int _operaciones){
    unsigned int operaciones = _operaciones;
    if(operaciones & LOW){
        if(portType == 'E'){
            if(operaciones & pin7){
                DDRE |= (1 << PORTE7); 
            }
            else if(operaciones & pin6){
                DDRE |= (1 << PORTE6); 
            }
            else if (operaciones & pin5){
                DDRE |= (1 << PORTE5); 
            }
            else if (operaciones & pin4){
                DDRE |= (1 << PORTE4); 
            }
            else if (operaciones & pin3){
                DDRE |= (1 << PORTE3); 
            }
            else if (operaciones & pin2){
                DDRE |= (1 << PORTE2); 
            }
            else if (operaciones & pin1){
                DDRE |= (1 << PORTE1); 
            }
            else if (operaciones & pin0){
                DDRE |= (1 << PORTE0); 
            }
        }
        if(portType == 'H'){
            if(operaciones & pin7){
                DDRH |= (1 << PORTH7); 
            }
            else if(operaciones & pin6){
                DDRH |= (1 << PORTH6); 
            }
            else if (operaciones & pin5){
                DDRH |= (1 << PORTH5); 
            }
            else if (operaciones & pin4){
                DDRH |= (1 << PORTH4); 
            }
            else if (operaciones & pin3){
                DDRH |= (1 << PORTH3); 
            }
            else if (operaciones & pin2){
                DDRH |= (1 << PORTH2); 
            }
            else if (operaciones & pin1){
                DDRH |= (1 << PORTH1); 
            }
            else if (operaciones & pin0){
                DDRH |= (1 << PORTH0); 
            }
        }
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
            if(portType == 'E'){
            if(operaciones & pin7){
                DDRE &= ~(1 << PORTE7); 
            }
            else if(operaciones & pin6){
                DDRE &= ~(1 << PORTE6); 
            }
            else if (operaciones & pin5){
                DDRE &= ~(1 << PORTE5); 
            }
            else if (operaciones & pin4){
                DDRE &= ~(1 << PORTE4); 
            }
            else if (operaciones & pin3){
                DDRE &= ~(1 << PORTE3); 
            }
            else if (operaciones & pin2){
                DDRE &= ~(1 << PORTE2); 
            }
            else if (operaciones & pin1){
                DDRE &= ~(1 << PORTE1); 
            }
            else if (operaciones & pin0){
                DDRE &= ~(1 << PORTE0); 
            }
        }
        if(portType == 'H'){
            if(operaciones & pin7){
                DDRH &= ~(1 << PORTH7); 
            }
            else if(operaciones & pin6){
                DDRH &= ~(1 << PORTH6); 
            }
            else if (operaciones & pin5){
                DDRH &= ~(1 << PORTH5); 
            }
            else if (operaciones & pin4){
                DDRH &= ~(1 << PORTH4); 
            }
            else if (operaciones & pin3){
                DDRH &= ~(1 << PORTH3); 
            }
            else if (operaciones & pin2){
                DDRH &= ~(1 << PORTH2); 
            }
            else if (operaciones & pin1){
                DDRH &= ~(1 << PORTH1); 
            }
            else if (operaciones & pin0){
                DDRH &= ~(1 << PORTH0); 
            }
        }
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
    if(portType == 'H'){
        if(operaciones & pin7){
            if(operaciones & HIGHT){ 
                PORTH |= (1 << PORTH7);
            }
            else{
                PORTH &= ~(1 << PORTH7);
            }
        }
        else if(operaciones & pin6){
            if(operaciones & HIGHT ){
                PORTH |= (1 << PORTH6);
            }
            else{
                PORTH &= ~(1 << PORTH6);
            }
        }
        else if(operaciones & pin5 ){
            if(operaciones & HIGHT ){
                PORTH |= (1 << PORTH5);
            }
            else{
                PORTH &= ~(1 << PORTH5);
            }
        }
        else if(operaciones & pin4){
            if(operaciones & HIGHT ){
                PORTH |= (1 << PORTH4);
            }
            else{
                PORTH &= ~(1 << PORTH4);
            }
        }
        else if(operaciones & pin3){
            if(operaciones & HIGHT ){
                PORTH |= (1 << PORTH3);
            }
            else{
                PORTH &= ~(1 << PORTH3);
            }
        }
        else if(operaciones & pin2){
            if(operaciones & HIGHT ){
                PORTH |= (1 << PORTH2);
            }
            else{
                PORTH &= ~(1 << PORTH2);
            }
        }
        else if(operaciones & pin1){
            if(operaciones & HIGHT ){
                PORTH |= (1 << PORTH1);
            }
            else{
                PORTH &= ~(1 << PORTH1);
            }
        }
        else if(operaciones & pin0){
            if(operaciones & HIGHT ){
                PORTH |= (1 << PORTH0);
            }
            else{
                PORTH &= ~(1 << PORTH0);
            }
        }
    }

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