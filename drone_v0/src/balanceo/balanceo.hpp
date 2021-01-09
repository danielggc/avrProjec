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
#include "../I2C/i2c.hpp"
#include "../MPU_6050/mpu-6050.hpp"
#include <util/twi.h>
#include "../motores/motores.hpp"
#define EEPROM_Write_Addess		0xA0
#define EEPROM_Read_Addess		0xA1





class i2cCorte{
    public:
        MPU6050 mpu__6050;
        UART pantalla1;
        i2cCorte();
        void init();
        void lecturaDatos();
        void difenciaRecorrido();
        bool validarEstadoX();
        bool validarEstadoY();
        bool validarEstadoZ();
        int datoX();
        int datoY();
        uint16_t datoZ();
        int cambioDatoX;
        int cambioDatoZ; 
        int cambioDatoY;
        int desplasamientoX;
        int desplasamientoZ; 
        int desplasamientoY;
};




class balanceo{
    public:
        motores drone;
        i2cCorte mpu;
        balanceo();
        bool validarEstadoAngular();
        int estadoX;
        int estadoY;
        int cambioestadoX;
        int cambioestadoY;
        int estadoZ;
        bool estabilisarDrone();
        bool masY(int);
        bool menosY(int);
        bool masX(int);
        bool menosX(int);
        bool restaurarAltura(int,int);
        


};