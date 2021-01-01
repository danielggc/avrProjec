#include "UART.hpp"
#include "../tranformVar/transformVar.hpp"
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
void UART::USART_Uint8_tWrite(uint8_t caracter){
    while(!(UCSR0A&(1<<5)));
        UDR0 = caracter;
}
void UART::UART_write_txt(char *cadena){
    while(*cadena !=0x00){
        USART0SendByte(*cadena);
        cadena++;
        _delay_ms(10);
    }
}
uint8_t UART::USART0ReceiveByte(){ 
    if(UCSR0A&(1<<7))return UDR0;
    else return 0;
    
}


void UART::UART_WriteInt(int numero){
    int largo=numeroUnidades(numero);
    char buffer[largo+20];
    itoa(numero,buffer,10);
    UART_write_txt(buffer);

}