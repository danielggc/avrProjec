#ifndef motoresDrone
#define motoresDrone


#include <avr/io.h>
#ifndef __AVR_ATmega328P__
#define __AVR_ATmega328P__
#endif
class motores{
    public:
    void initMotores();
    int motorA(int);
    int motorB(int);
    int motorC(int);
    int motorD(int);
    int motorA();
    int motorB();
    int motorC();
    int motorD();

};

#endif