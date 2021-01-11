#include "balanceo.hpp"





i2cCorte:: i2cCorte(){
    pantalla1.uart_init();
    mpu__6050.begin();
    twi_init();
    cambioDatoX =0;
    cambioDatoZ =0 ;
    cambioDatoY =0;
    desplasamientoX =0;
    desplasamientoZ =0;
    desplasamientoY =0;
}


bool i2cCorte::validarEstadoX(){
    mpu__6050.update();
    cambioDatoX=mpu__6050.getRawAccX();
    if(cambioDatoX!=desplasamientoX){
        int diferencia=(cambioDatoX-desplasamientoX);
        if(diferencia<9)diferencia=diferencia*-1;
        if(diferencia>8){
            desplasamientoX=cambioDatoX;
            return true;
        }
        else{
            return false;    
        }
    }
    else
    {
        return false;
    }
}
bool  i2cCorte::validarEstadoZ(){
    mpu__6050.update();
    cambioDatoZ=mpu__6050.getRawAccZ();
    if(cambioDatoZ!=desplasamientoZ){
        float diferencia (cambioDatoZ-desplasamientoZ);
        if(diferencia<9)diferencia=diferencia*-1;
        if(diferencia>8){
            desplasamientoZ=cambioDatoZ;
            return true;
        }
        else{
            return false;    
        }
    }
    else
    {
        return false;
    }
}
bool  i2cCorte::validarEstadoY(){
   mpu__6050.update();
   cambioDatoY = mpu__6050.getRawAccY();
   if(cambioDatoY!=desplasamientoY){
        int diferencia=(cambioDatoY-desplasamientoY);
        if(diferencia<9)diferencia=diferencia*-1;
        if(diferencia>8){
            desplasamientoY=cambioDatoY;
            return true;
        }
        else{
            return false;    
        }
    }
    else
    {
        return false;
    }
}




balanceo::balanceo(){
    struct PidData pid;
    i2cCorte mpu();
    motores drone();}

bool balanceo::estabilizarEjeX(){
    mpu.mpu__6050.update();
    estadoX = mpu.mpu__6050.getRawAccX();
    float nuevoEstadoB = drone.motorA();
    float nuevoEstadoA =  drone.motorB();
    const float estadoA = nuevoEstadoA;
    const float estadoB = nuevoEstadoB;
    while (estadoX > 50 || estadoX < -50){
        mpu.mpu__6050.update();
        estadoX = mpu.mpu__6050.getRawAccX();
        float correccion = ((pidController(0,estadoX/100,&pid)));
        float correccionMotor = (correccion/10000)*255;
        mpu.pantalla1.UART_WriteInt(nuevoEstadoA);
        mpu.pantalla1.UART_write_txt("\n\n\n\n");
        
        if(estadoX>0){
            nuevoEstadoA = ((estadoA +(-1*correccionMotor)));
            nuevoEstadoB = ((estadoB +(correccionMotor/2)));
            if(nuevoEstadoA == 255 || nuevoEstadoA > 255 ){
                nuevoEstadoA=drone.motorA(255);
            }else if(nuevoEstadoA == 0 || nuevoEstadoA <0){
                nuevoEstadoA=drone.motorA(0);
            }else{
                nuevoEstadoA=drone.motorA(nuevoEstadoA);
            }
            if(nuevoEstadoB == 255 || nuevoEstadoB > 255 ){
                nuevoEstadoB = drone.motorA(255);
            }else if(nuevoEstadoB == 0 || nuevoEstadoB <0){
                nuevoEstadoB = drone.motorA(0);
            }else{
                nuevoEstadoB = drone.motorB(nuevoEstadoB);
            }

        }
        if(estadoX<0){
            nuevoEstadoA = ((nuevoEstadoA +(-1*correccionMotor/2)));
            nuevoEstadoB = ((nuevoEstadoB +(correccionMotor)));
            if(nuevoEstadoA == 255 || nuevoEstadoA > 255 ){
                nuevoEstadoA=drone.motorA(255);
            }else if(nuevoEstadoA == 0 || nuevoEstadoA <0){
                nuevoEstadoA=drone.motorA(0);
            }else{
                nuevoEstadoA=drone.motorA(nuevoEstadoA);
            }
            if(nuevoEstadoB == 255 || nuevoEstadoB > 255 ){
                nuevoEstadoB = drone.motorA(255);
            }else if(nuevoEstadoB == 0 || nuevoEstadoB <0){
                nuevoEstadoB = drone.motorA(0);
            }else{
                nuevoEstadoB = drone.motorB(nuevoEstadoB);
            }

        }
        
        _delay_ms(800);    
        
    }

    pidResetIntegral(&pid);
    return true;
}

bool balanceo::restaurarAltura(int X,int Y){
    
}


bool balanceo::estabilisarDrone(){
    pidInit(Kp,KI,KD,&pid);
    mpu.mpu__6050.update();
    cambioestadoX = mpu.mpu__6050.getRawAccX();
    cambioestadoY = mpu.mpu__6050.getRawAccX();
    if(cambioestadoX>700 || cambioestadoX<-700){
        estabilizarEjeX();
    }
   
    if(cambioestadoY>700){
        //masY(cambioestadoY);
    }
    _delay_ms(5000);        

}




