#include <avr/io.h>
#include <util/delay.h>
int main(void){
DDRH |= (1 << PORTH5); 
    while (1){
        PORTH |= (1 << PORTH5);
        _delay_ms(2000); 
        PORTH &= ~(1 << PORTH5);
        _delay_ms(2000);
    }
}