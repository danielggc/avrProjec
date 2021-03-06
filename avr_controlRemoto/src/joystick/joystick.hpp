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

#define pinEjeY 5
#define pinEjeX 4
#define pinEjeZ 3
#define A1 1
#define A0 0

class joystick{
    public:
        joystick();
        void lecturaDatos();
        void difenciaRecorrido();
        bool validarEstadoX();
        bool validarEstadoY();
        bool validarEstadoZ();
        int datoX();
        int datoY();
        uint16_t datoZ();
        int cambioDatoX;
        uint16_t cambioDatoZ; 
        int cambioDatoY;
        int desplasamientoX;
        int desplasamientoZ; 
        int desplasamientoY;
};


class pulsadorJoystinck0{
    private:
        PinConfiguration pulsadorPD4();  
    public:
        pulsadorJoystinck0();
        bool pulsador1();
        bool pulsador2();
};
class pulsadorJoystinck1{
    bool pulsador1();
    bool pulsador2();
};