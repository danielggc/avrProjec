#include "codificadoControl.hpp"

codificadoControl::codificadoControl(){
        codigoControl.codificadoInicio="dgc7";
        codigoControl.codificadoComlemento="dd7";
        codigoControl.coficadoJYx="JYy";
        codigoControl.coficadoJYy="JYy";
        codigoControl.coficadoJYz="JYZ";
        codigoControl.coficadoJY0PP1="JY0PP1";
        codigoControl.separador="_";
        pantalla1.uart_init();
        adc_init();
        sei();
        iniciar.SPI_Init(Master);
        comunicacionDrone.nrf24_init();
        comunicacionDrone.nrf24_config(); 
        comunicacionDrone.nrf24_rx_address(txDrone_address); 
        comunicacionDrone.nrf24_tx_address(rxControl_address); 
}
bool codificadoControl::codificadoEnvio(int _JoystickX,int _JoystickY ,int _JoystickZ,bool _JoystickPulsador0){
        char JoystickX[20];
        itoa(_JoystickX,JoystickX,10);
        char JoystickY[20];
        itoa(_JoystickY,JoystickY,10);
        char JoystickZ[20];
        itoa(_JoystickZ,JoystickZ,10);
        char codificacionInicio[50] ;
        char codificacionY[50];
        char codificacionX[50];
        char codificacionZ[50];
        for (uint8_t i = 0; i <50; i++){
            codificacionInicio[i]=' ';
            codificacionX[i]=' ';
            codificacionY[i]=' ';
            codificacionZ[i]=' ';
        }
        
        strcpy(codificacionInicio,codigoControl.codificadoInicio);
        char* codificadoComplemento = codigoControl.codificadoComlemento;
        
        strcpy(codificacionX,codificadoComplemento);
        strcat(codificacionX,JoystickX);
        strcat(codificacionX,codificadoComplemento);
        
        strcpy(codificacionY,codificadoComplemento);
        strcat(codificacionY,JoystickY);
        strcat(codificacionY,codificadoComplemento);
        
        strcpy(codificacionZ,codificadoComplemento);
        strcat(codificacionZ,JoystickZ);
        strcat(codificacionZ,codificadoComplemento);
      
        comunicacionDrone.nrf24_powerUpTx();
        comunicacionDrone.nrf24_send(codificacionInicio);
        _delay_ms(50);
        comunicacionDrone.nrf24_send(codificacionX);
        _delay_ms(50);
        comunicacionDrone.nrf24_send(codificacionY);
        _delay_ms(50);
        comunicacionDrone.nrf24_send(codificacionZ);
        _delay_ms(50);
        comunicacionDrone.nrf24_send(codificacionInicio);
        uint8_t temp =  comunicacionDrone.nrf24_lastMessageStatus();
        if(temp == NRF24_TRANSMISSON_OK){                    
            pantalla1.UART_write_txt("se envio bien la señal");
            _delay_ms(100);
        }
        else if(temp == NRF24_MESSAGE_LOST){                     
            pantalla1.UART_write_txt("esta en proceso");
            _delay_ms(100);  
        }
        temp = comunicacionDrone.nrf24_retransmissionCount();
        pantalla1.UART_write_txt("terminamos\n");
}


/*
        //comunicacionDrone.nrf24_send(codificacionInicio);
        //comunicacionDrone.nrf24_send(codificacionX);
        //comunicacionDrone.nrf24_send(codificacionInicio);
        uint8_t temp =  comunicacionDrone.nrf24_lastMessageStatus();
        if(temp == NRF24_TRANSMISSON_OK){                    
            pantalla1.UART_write_txt("se envio bien la señal");
            _delay_ms(100);
        }
        else if(temp == NRF24_MESSAGE_LOST){                     
            pantalla1.UART_write_txt("esta en proceso");
            _delay_ms(100);  
        }
        temp = comunicacionDrone.nrf24_retransmissionCount();
        comunicacionDrone.nrf24_powerDown();

*/        