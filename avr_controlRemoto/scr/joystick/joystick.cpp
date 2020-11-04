#include "joystick.hpp"



joystick::joystick(){
    adc_init();
    cambioDatoX =0;
    cambioDatoZ =0 ;
    cambioDatoY =0;
    desplasamientoX =0;
    desplasamientoZ =0;
    desplasamientoY =0;
}

bool joystick::validarEstadoX(){
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
bool joystick::validarEstadoZ(){
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
bool joystick::validarEstadoY(){
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


int joystick::datoX(){
    cambioDatoX=adc_read(pinEjeX);
    return cambioDatoX;
}
int joystick::datoZ(){
    cambioDatoZ=adc_read(pinEjeZ);
    return cambioDatoZ;
}
int joystick::datoY(){
    cambioDatoY=adc_read(pinEjeY);
    return cambioDatoY;
}



















/*
int main(){
    UART pantalla1;
    pantalla1.uart_init();
    SPI iniciar;
    iniciar.SPI_Init(Master);
    char mensaje=' ';
    joystick contrles;
    float dato=0;
    Nrf24 antenaRX;
    antenaRX.nrf24_init();
    antenaRX.nrf24_config(); 
    antenaRX.nrf24_rx_address(rx_address); 
    antenaRX.nrf24_tx_address(tx_address); 
    while(1){ 
        antenaRX.nrf24_powerUpTx();
        dato=contrles.datoZ();  
        if(contrles.validarEstadoZ()){
            int largo=numeroUnidades(dato);
            char numeroChar[largo++];
            char *dirNumerochar=&numeroChar[0];
            int_to_char(dato,dirNumerochar,largo);
            for(int b=0;b<largo;b++){
                data_array[b]=numeroChar[b];
            }
            antenaRX.nrf24_send(data_array);
        }        
        _delay_ms(1000);
        for(int b=0;b<12;b++){
            data_array[b]=' ';
        }
        antenaRX.nrf24_powerDown();
     
    }

}
*/