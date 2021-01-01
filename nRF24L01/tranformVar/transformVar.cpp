#include "transformVar.hpp"
#include "../library/UART/UART.hpp"
int int_to_binario(int8_t numero){
    UART pantalla1;
    pantalla1.uart_init();
    for(int i=7;i!=-1;i--){
        if(numero & (1<<i)){
            pantalla1.USART0SendByte('1');
        }
        else{
            pantalla1.USART0SendByte('0');
        }
    }
    pantalla1.USART0SendByte('\n');
}
int char_to_int(char *direccionCaracter){
    UART pantalla1;   
    long numero=0;
    int contador=0;
    pantalla1.USART0SendByte('\n');
    while (*direccionCaracter!=' '){
        pantalla1.USART0SendByte(*direccionCaracter);
        direccionCaracter++;
        contador++;
    }
    pantalla1.USART0SendByte('\n');
    direccionCaracter--;
    int multiplicador=10;
    for(int a=0;a<contador;a++){
        if(a==0){
            numero=(*direccionCaracter-'0');
        }
        else
        {
            numero=(*direccionCaracter-'0')*multiplicador+numero;
            multiplicador=multiplicador*10;
        }
        direccionCaracter--;
    }
    pantalla1.USART0SendByte('\n');
    char dato[6];
    char *direcciondato=&dato[0];
    int largo=numeroUnidades(numero);
    int_to_char(numero,direcciondato,largo);
    for(int d=0;d<largo;d++){
        pantalla1.USART0SendByte(dato[d]);
    }
    pantalla1.USART0SendByte('\n');

    return numero;

}

int numeroUnidades(long _numero){
    long numero=_numero;  
    if (numero==0){
        return 1;
    }
    int contador=0;    
    while (numero>0){
        numero=numero/10;
        contador++;
    }
    return contador;
}
int int_to_char(long numero ,char* cadenaChar , int largo){
    UART pantalla1;
    if(largo>0){
        long respaldo=numero;    
        int contador=0;    
        respaldo=numero;
        int d=largo-1;
        int inicio=largo-1;
        for(;d>-1;d--){
            long divisor=1;
            for(int i=0;i<d;i++){
                divisor=divisor*10;
            }
            int respaldoResta=respaldo;
            respaldo=numero/divisor;
            if(d==inicio){
                cadenaChar[contador]=respaldo+'0';
            }
            else{
                long resta=(respaldoResta*10);
                int numeroSeparado=respaldo-resta;
                cadenaChar[contador]=numeroSeparado+'0';
            }
            contador++;
        }
    }
    else if(largo==0){
        cadenaChar[0]=numero;
    }
    
}