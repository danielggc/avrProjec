#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>
#include <avr/iom2560.h>
#define USART_BAUDRATE 9600
#define UBRR_VALUE  (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)
class UART{
    public:
        void uart_init ();
        void USART0SendByte(unsigned char);
        uint8_t USART0ReceiveByte();
        void UART_write_txt(char *);
        
};
