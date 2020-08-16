#include <avr/io.h>
#include <util/delay.h>
#include"/home/dgc7/ejersiciosLibros/avr/pines/pinMode/pinMode.hpp"
int main(){
    //~PINB & (1<<PORTB6
    PinConfiguration dd('B');
    dd.pinMode(pin0|OUTPUT);
    PinConfiguration salida('H');
    salida.pinMode(pin5|INTPUT);
    dd.diguitalWrite(pin0|HIGHT);
    _delay_ms(2000); 
    while (1){ 
        if(salida.Pind(pin5)==1){ 
            dd.diguitalWrite(pin0|LOW);
        }
        else{
            dd.diguitalWrite(pin0|HIGHT);
        }
    }

}
