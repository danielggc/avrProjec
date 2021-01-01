#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h> 
#include <stdint.h> 
#include <stdlib.h>
int main(){
    DDRB|=(1<<PORTB3);
    while (1){
        PORTB |= (1<<PORTB3);
        _delay_ms(200);
        PORTB &= ~(1<<PORTB3);
        _delay_ms(200);
    }
    
    
}
