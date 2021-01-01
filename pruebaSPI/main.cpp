#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h> 
#include <stdint.h> 
#include <stdlib.h>
#include "nRF24L01/mirf.h"
#include "library/UART/UART.hpp"
#include "library/SPI/spi.hpp"
int main(){
    PinConfiguration led('B');
    led.pinMode(OUTPUT|pin7);
    led.diguitalWrite(pin7|HIGHT);
    _delay_ms(2000);
    led.diguitalWrite(pin7|LOW);
    _delay_ms(2000);
    SPI Comunicacion;
    Comunicacion.SPI_Init(Master);
    while (1){
        led.diguitalWrite(pin7|HIGHT);
        _delay_ms(1000);
        Comunicacion.SPI_TextTransmit("hola esclavo");
        led.diguitalWrite(pin7|LOW);
        _delay_ms(1000);
    }
    
}
