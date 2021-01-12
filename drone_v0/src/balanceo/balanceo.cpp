#include "balanceo.hpp"





i2cCorte:: i2cCorte(){
    UART pantalla1;
    MPU6050 mpu__6050;
    twi_init();
    pantalla1.uart_init();
    
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
    i2cCorte mpu;
    motores drone;

    
    }
              //nuevoEstadoA = ((estadoA +(-1*correccionMotores)));
            //nuevoEstadoB = ((estadoB +(correccionMotores/1)));
              //nuevoEstadoA = ((nuevoEstadoA +(-1*correccionMotores/1)));
            //nuevoEstadoB = ((nuevoEstadoB +(correccionMotores)));

float balanceo::convercion510(float dato){
    float convertido=0.0;
    if(dato == 127.5){
        convertido = 0.0;
    }else {
        convertido =dato * 2;
    }
    return(convertido);
}
float balanceo::convercion255(float dato){
    float convertido=0.0;
    if(dato == 255){
        convertido = 510;
    }else if(dato == -255){
        convertido = 0;
    }
    else if(dato == 0){
        convertido = 255; 
    }else if( dato > 0 ){
        convertido = dato +255;
    }else{

        convertido =(255) + dato;
    }
    return(convertido);
}


bool balanceo::estabilizarEjeX(){
    mpu.mpu__6050.update();
    estadoX = mpu.mpu__6050.getRawAccX();
    const float estadoA = drone.motorA();
    const float estadoB = drone.motorB();
    pidA.sumError=estadoA;
    pidB.sumError=estadoB;
    while (estadoX > 200 || estadoX < -200){
        mpu.mpu__6050.update();
        estadoX = mpu.mpu__6050.getRawAccX();
        motorA(estadoX,estadoA);
        mpu.mpu__6050.update();
        estadoX = mpu.mpu__6050.getRawAccX();
        motorB(estadoX,estadoB);
        
    }

    pidResetIntegral(&pidA);
    pidResetIntegral(&pidB);
    return true;
}

bool balanceo::motorA(float estadoXA ,float estadoA ){
        float nuevoEstadoA =  drone.motorA();
        float correccion = ((pidController(0,estadoXA/100,&pidA)));
        float correccionMotores = (correccion/10000)*255;
        float correccionMotorA = ((convercion510(estadoA)+convercion255(correccionMotores))/(510+convercion510(estadoA)))*510;
        //mpu.pantalla1.UART_write_txt("\nA");
        //mpu.pantalla1.UART_WriteInt(nuevoEstadoA);
        if(estadoXA<0 || estadoXA > 0){
            float correccionA = correccionMotorA/2;
            nuevoEstadoA =  correccionA;
            if(nuevoEstadoA == 255 || nuevoEstadoA > 255 ){
                nuevoEstadoA=drone.motorA(255);
            }else if(nuevoEstadoA == 0 || nuevoEstadoA <0){
                nuevoEstadoA=drone.motorA(0);
            }else{
                nuevoEstadoA=drone.motorA(nuevoEstadoA);
            }
        }
        return true;
}
bool balanceo::motorB(float estadoXB ,float estadoB){
        float nuevoEstadoB = drone.motorB();
        float correccion = (pidController(0,(estadoXB*-1)/100,&pidB));
        float correccionMotores = (correccion/10000)*255;
        float correccionMotorB = ((convercion510(estadoB)+convercion255(correccionMotores))/(510+convercion510(estadoB)))*510;
        if(estadoXB<0 || estadoXB > 0){
            float correccionB = correccionMotorB/2;
            nuevoEstadoB =  correccionB;
            if(nuevoEstadoB == 255 || nuevoEstadoB > 255 ){
                nuevoEstadoB=drone.motorB(255);
            }else if(nuevoEstadoB == 0 || nuevoEstadoB <0){
                nuevoEstadoB=drone.motorB(0);
            }else{
                nuevoEstadoB=drone.motorB(nuevoEstadoB);
            }
        }
        return true;
}

bool balanceo::restaurarAltura(int X,int Y){
    
}


bool balanceo::estabilisarDrone(){
    mpu.mpu__6050.begin();
    pidInit(Kp,KI,KD,&pidA);
    pidInit(Kp,KI,KD,&pidB);
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




