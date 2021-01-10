#include "pid.hpp"

void pidInit(int16_t _Kp,int16_t _KI,int16_t _KD,struct PidData* pid){
    pid -> sumError = 0;
    pid -> lastProcessValue = 0;
    pid -> KP = _Kp;
    pid -> KI = _KI;
    pid -> KD = _KD;
    pid -> maxError = (MAX_INT/(pid->KP+1));
    pid -> maxSumError = (MAX_I_TERM)/(pid -> KI +1);
}

int16_t pidController(int16_t setPoint,int16_t processvalu,struct PidData *pid){
    int16_t error, p_term, d_term;   
    int32_t i_term, ret, temp;   
    error = setPoint-processvalu;
    if(error > pid ->maxError){
        p_term = MAX_INT;
    }else if(error < -(pid ->maxError)){
        p_term = -1*(MAX_INT);
    }else{
        p_term = (error*(pid ->KP));
    }

    temp = pid -> sumError + error;
    if(temp > pid ->maxSumError){
        i_term = MAX_I_TERM;
        pid -> sumError = pid -> maxSumError;
    }else if(temp < -(pid -> maxSumError)){
        i_term = -1*(MAX_I_TERM);
        pid -> sumError = -1*(pid -> maxSumError);
    }else{
        pid -> sumError = temp;
        i_term = pid ->KI*(pid -> sumError);
    }
    

    d_term = (pid -> KI *(pid ->lastProcessValue -processvalu));
    pid -> lastProcessValue = processvalu;
    
    ret = (p_term + i_term + d_term );
    
    if(ret > MAX_INT)ret =MAX_INT;
    else if(ret < MAX_INT*-1);
    
    return(ret);
}


bool pidResetIntegral(struct PidData *pid){
    pid->sumError=0;
    true;
}