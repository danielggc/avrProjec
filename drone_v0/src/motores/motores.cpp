#include"motores.hpp"


void motores::initMotores(){
    DDRD |= (1<<PORTD5);
    DDRD |= (1<<PORTD6);
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

float motores::motorA(float velocidad){
    OCR1A=velocidad;
    return OCR1A;
}
float motores::motorB(float velocidad){
    OCR1B=velocidad;
    return OCR1B;
}

float motores::motorC(float velocidad){
    OCR0A=velocidad;
    return OCR1B;
}

float motores::motorD(float velocidad){
    OCR0B=velocidad;
    return OCR1B;
}


int motores::motorA(){
    return OCR1A;
}
int motores::motorB(){
    return OCR1B;
}

int motores::motorC(){
    return OCR1B;
}

int motores::motorD(){
    return OCR1B;
}