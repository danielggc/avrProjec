
#ifndef UART_HEADER
#define UART_HEADER
#include"../pinMode/PIN.hpp"
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>

#define USART_BAUDRATE 9600
#define UBRR_VALUE  (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)
class UART{
    public:
        void uart_init ();
        void USART0SendByte(unsigned char);
        uint8_t USART0ReceiveByte();
        void UART_write_txt(char *);
        void USART_Uint8_tWrite(uint8_t);
        void UART_WriteInt(long);
    private:
         
};
#endif