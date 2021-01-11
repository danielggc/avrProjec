#ifndef motoresDrone
#define motoresDrone


#include <avr/io.h>
#ifndef __AVR_ATmega328P__
#define __AVR_ATmega328P__
#endif
class motores{
    public:
    void initMotores();
    float motorA(float);
    float motorB(float);
    float motorC(float);
    float motorD(float);
    int motorA();
    int motorB();
    int motorC();
    int motorD();

};

#endif