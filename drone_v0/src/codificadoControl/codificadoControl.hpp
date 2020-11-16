#ifndef codificionControl_V01
#define  codificionControl_V01
#include <avr/io.h>
#ifndef __AVR_ATmega328P__
#define __AVR_ATmega328P__
#endif
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/interrupt.h> 
#include <stdint.h> 
#include <stdlib.h>
#include "../nRF24L01/mirf.hpp"
#include "../library/UART/UART.hpp"
#include "../library/SPI/spi.hpp"
#include "../library/pinMode/PIN.hpp"
#include "../library/tranformVar/transformVar.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct codigos{
        char* codificadoInicio;
        char* codificadoComlemento;
        char* coficadoJYx;
        char* coficadoJYy;
        char* coficadoJYz;
        char* coficadoJY0PP1;
        char* separador;
 

};
       
class codificadoControl{
    public:
        codificadoControl();
        bool codificadoEnvio(int _JoystickX,int _JoystickY ,int _JoystickZ,bool _JoystickPulsador0);
    private:
        struct codigos codigoControl;
        UART pantalla1;
        SPI iniciar;
        Nrf24 comunicacionDrone;
        uint8_t txDrone_address[5] = {0,0,0,0,1};
        uint8_t rxControl_address[5] = {0,0,0,0,1};

      
};

#endif