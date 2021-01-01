#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h> 
#include <stdint.h> 
#include <stdlib.h>
#include "library/libraryCommunication.hpp"
#include "328.hpp"
int main(){
   while(1){
    PinConfiguration led13('B');
    led13.pinMode(pin5|OUTPUT);
    led13.diguitalWrite(pin5|HIGHT);
    _delay_ms(200);
    led13.diguitalWrite(pin5|LOW);
    _delay_ms(200);
    led13.diguitalWrite(pin5|HIGHT);
   }
}
