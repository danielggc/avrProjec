#ifndef motoresDrone
#define motoresDrone


#include <avr/io.h>
#ifndef __AVR_ATmega328P__
#define __AVR_ATmega328P__
#endif
class motores{
    public:
    void initMotores();
    bool motorA(int);
    bool motorB(int);
    bool motorC(int);
    bool motorD(int);

};

#endif