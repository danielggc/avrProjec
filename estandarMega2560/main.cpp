#include "library/libraryCommunication.hpp"
#include <util/delay.h>
#include <avr/interrupt.h> 
#include <stdint.h> 
#include <stdlib.h>
int main(){
   PinConfiguration blink('B');
   blink.pinMode(OUTPUT|pin5);
   blink.diguitalWrite(HIGHT|pin5);
    
}
