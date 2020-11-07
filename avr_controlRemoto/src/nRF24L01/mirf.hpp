

#ifndef NRF24L01_H
#define NRF24L01_H
#include <avr/io.h> 
#include <avr/interrupt.h>
#include "../library/SPI/spi.hpp"
#include "../library/UART/UART.hpp"

#include <stdint.h>

#define low 0
#define high 1

#define nrf24_ADDR_LEN 5
#define nrf24_CONFIG ((1<<EN_CRC)|(0<<CRCO))

#define NRF24_TRANSMISSON_OK 0
#define NRF24_MESSAGE_LOST   1
#define CE  PB1
#define CSN PB0

#define mirf_CSN_hi     PORTB |=  (1<<CSN);
#define mirf_CSN_lo     PORTB &= ~(1<<CSN);
#define mirf_CE_hi      PORTB |=  (1<<CE);
#define mirf_CE_lo      PORTB &= ~(1<<CE);



#define mirf_CH 2
#define mirf_PAYLOAD 16
class Nrf24{
    private:
        SPI comunicacion ;
        UART pantalla1;
    public:
        Nrf24();
        void mirf_config_register(uint8_t reg, uint8_t value);
        void    nrf24_init();
        void    nrf24_rx_address(uint8_t* adr);
        void    nrf24_tx_address(uint8_t* adr);
        void    nrf24_config();

        uint8_t nrf24_dataReady();
        uint8_t nrf24_isSending();
        uint8_t nrf24_getStatus();
        uint8_t nrf24_rxFifoEmpty();

        void    nrf24_send(char* value);
        void    nrf24_send(uint8_t* value);
        void    nrf24_getData(uint8_t* data);

        uint8_t nrf24_payloadLength();

        uint8_t nrf24_lastMessageStatus();
        uint8_t nrf24_retransmissionCount();

        uint8_t nrf24_payload_length();

        void    nrf24_powerUpRx();
        void    nrf24_powerUpTx();
        void    nrf24_powerDown();

        uint8_t spi_transfer(uint8_t tx);
        void    nrf24_transmitSync(uint8_t* dataout,uint8_t len);
        void    nrf24_transmitSync(char* dataout,uint8_t len);
        void    nrf24_transferSync(uint8_t* dataout,uint8_t* datain,uint8_t len);
        void    nrf24_configRegister(uint8_t reg, uint8_t value);
        void    nrf24_readRegister(uint8_t reg, uint8_t* value, uint8_t len);
        void    nrf24_writeRegister(uint8_t reg, uint8_t* value, uint8_t len);
};
#endif