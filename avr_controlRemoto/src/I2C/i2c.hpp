
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h> 

#include <util/twi.h>
#include <stdbool.h>

#define DEBUG_LOG			0
#define SUCCESS				0

#define TW_SCL_PIN			PORTD0
#define TW_SDA_PIN			PORTD1

#define TW_SLA_W(ADDR)		((ADDR << 1) | TW_WRITE)
#define TW_SLA_R(ADDR)		((ADDR << 1) | TW_READ)
#define TW_READ_ACK			1
#define TW_READ_NACK		0
#define BUFFER_LENGTH 128


typedef uint16_t ret_code_t;

class I2c{
    private:
    static uint8_t rxBuffer[];
    static uint8_t rxBufferIndex;
    static uint8_t rxBufferLength;
    static uint8_t txAddress;
    static uint8_t txBuffer[];
    static uint8_t txBufferIndex;
    static uint8_t txBufferLength;
    static uint8_t transmitting;
    public:
        uint8_t endTransmission(uint8_t sendStop);
        void beginTransmission(uint8_t address);
        void setAddress(uint8_t);

        void iniciar();
        uint8_t I2C_Repeated_Start(unsigned char);
        uint8_t I2C_Start(unsigned char);
        void  espera();
        void I2C_Stop();
        void iniciarComunicacion();
        uint8_t enviarDatos(unsigned char );
        unsigned char recibirDatos_ACK();
        unsigned char recibirDatos_nACK();
        uint8_t estado();
};
