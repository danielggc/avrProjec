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
     i2cCorte mpu();
     motores drone();
}

bool balanceo::masX(int c){
    mpu.mpu__6050.update();
    estadoX = mpu.mpu__6050.getRawAccX();
    const int estadoActualA = drone.motorA();
    const int estadoActualB = drone.motorB();
    mpu.pantalla1.UART_write_txt("que vamos mas X =)");
    int Ma = estadoActualA;
    int Mb = estadoActualB;   
    while (estadoX > 50 ){
        mpu.mpu__6050.update();
        estadoX=mpu.mpu__6050.getRawAccX();
        mpu.pantalla1.UART_WriteInt(drone.motorA(Ma));
        mpu.pantalla1.UART_write_txt("\n");
        if(drone.motorA() < 2){
            estadoX = 1;
        }
        _delay_ms(500);        
        Ma= Ma - 2;
        Mb= Mb + 2;
        
    }
    return true;
}
bool balanceo::menosX(int c){
    mpu.mpu__6050.update();
    estadoX = mpu.mpu__6050.getRawAccX();
    const int estadoActualA =drone.motorA();
    const int estadoActualB =drone.motorB();
    mpu.pantalla1.UART_write_txt("que vamos menos X =)");
    int Ma = estadoActualA;
    int Mb = estadoActualB;   
    while (estadoX<0 ){
        mpu.mpu__6050.update();
        estadoX = mpu.mpu__6050.getRawAccX();
        mpu.pantalla1.UART_WriteInt(drone.motorA(Ma));
        mpu.pantalla1.UART_write_txt("\n");
        if(drone.motorA()>255){
            estadoX = 1;
        }
        _delay_ms(500);        
        Ma = Ma + 2;
        Mb = Mb - 2;
        
    }
    return true;
    
}
bool balanceo::restaurarAltura(int X,int Y){
    
}
bool balanceo::masY(int){

}
bool balanceo::menosY(int){

}
bool balanceo::validarEstadoAngular(){
    if(mpu.validarEstadoX()){
        cambioestadoX =mpu.cambioDatoX;
    }
    if(mpu.validarEstadoY()){
        cambioestadoY =mpu.cambioDatoY;
    }    
}

bool balanceo::estabilisarDrone(){
    validarEstadoAngular();
    if(cambioestadoX>700){
        masX(cambioestadoX);
    }
    if(cambioestadoX<-700){
        menosX(cambioestadoX);
    }
    if(cambioestadoY>700){
        //masY(cambioestadoY);
    }
    if(cambioestadoY<-700){
        //menosY(cambioestadoY);
    }
        _delay_ms(5000);        

}




