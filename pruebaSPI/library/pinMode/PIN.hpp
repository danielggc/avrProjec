#ifndef PIN_HEADER
#define PIN_HEADER

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>
#include <avr/iom2560.h>
#define A 'A'
#define B 'B'
#define C 'C'
#define D 'D'
#define E 'E'
#define F 'F'
#define OUTPUT 1<<0
#define INTPUT 1<<1
#define LOW   1<<0
#define HIGHT 1<<1
#define  pin7 1<<2
#define  pin6 1<<3
#define  pin5 1<<4
#define  pin4 1<<5
#define  pin3 1<<6
#define  pin2 1<<7
#define  pin1 1<<8
#define  pin0 1<<9

class PinConfiguration{
  private:
    char portType;
  public:
    PinConfiguration(char);
    void pinMode(unsigned int) ;
    void diguitalWrite(unsigned int);
    int Pind(unsigned int);
};
#endif