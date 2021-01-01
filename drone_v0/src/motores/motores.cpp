#include"motores.hpp"


void motores::initMotores(){
    PORTD |= (1<<PORTD5);
    PORTD |= (1<<PORTD6);
    DDRB  |= ( 1<< PORTB1 ); 
    DDRB  |= ( 1<< PORTB2 ); 
    ICR1 = 0xFFFF;

    TCCR0A |=  (1 << COM1A1) | (0 << COM1A0) ;
    TCCR0A |=  (0 << WGM11) | (1 << WGM10) ;
    TCCR0B |=  (0 << CS12) | (1 << CS11) | ( 0 << CS10 );
    TCCR0A |=  (1 << COM1B1)| (0 << COM1B0);


    TCCR1A |=  (1 << COM1A1) | (0 << COM1A0) ; 
    TCCR1A |=  (0 << WGM11) | (1 << WGM10) ;
    TCCR1B |=  (0 << CS12) | (1 << CS11) | ( 0 << CS10 );
    TCCR1A |=  (1 << COM1B1)| (0 << COM1B0);
}

bool motores::motorA(int velocidad){
    OCR1A=velocidad;
    true;
}
bool motores::motorB(int velocidad){
    OCR1B=velocidad;
    true;
}

bool motores::motorC(int velocidad){
    OCR0A=velocidad;
    true;
}

bool motores::motorD(int velocidad){
    OCR0B=velocidad;
    true;
}