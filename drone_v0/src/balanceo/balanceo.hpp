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
#include "../PID/pid.hpp"

#define Kp 1
#define KI 1
#define KD 1
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
        struct PidData pid;
        balanceo();
        bool validarEstadoAngular();
        int estadoX;
        int estadoY;
        int cambioestadoX;
        int cambioestadoY;
        int estadoZ;
        bool estabilisarDrone();
        bool estabilizarEjeY();
        bool estabilizarEjeX();
        bool restaurarAltura(int,int);
        


};