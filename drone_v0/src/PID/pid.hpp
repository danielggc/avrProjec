#ifndef PID_H 
#define PID_H 
#define SCALING_FACTOR  128 
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h> 
#include <stdint.h> 
#include <stdlib.h>
#include <avr/interrupt.h>
#include "stdint.h"
#define MAX_INT         0x7ffffff 
#define MAX_LONG        0x7ffffffffL 
#define MAX_I_TERM      (MAX_LONG / 2) 
#define FALSE           0 
#define TRUE            1 
typedef struct PidData{
    int16_t lastProcessValue;
    int16_t sumError;
    int16_t KP;
    int16_t KI;
    int16_t KD;
    int16_t maxSumError;
    int16_t maxError;
}pidData;

void pidInit(int16_t,int16_t,int16_t,struct PidData*);
int16_t pidController(int16_t,int16_t,struct PidData*);
bool pidResetIntegral(struct PidData*);
#endif 
