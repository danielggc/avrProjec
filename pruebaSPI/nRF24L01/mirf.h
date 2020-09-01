#include <avr/io.h> 
#include <avr/interrupt.h>
#include "../library/SPI/spi.hpp"
#define TX_POWERUP mirf_config_register(CONFIG, mirf_CONFIG | ( (1<<PWR_UP) | (0<<PRIM_RX) ) )
#define RX_POWERUP mirf_config_register(CONFIG, mirf_CONFIG | ( (1<<PWR_UP) | (1<<PRIM_RX) ) )

#define mirf_CH 2
#define mirf_PAYLOAD 16
#define mirf_CONFIG ((1 << MASK_RX_DR) | (1 << EN_CRC) | (0 << CRCO )) 
#define  CE PORTD0
#define  CSN PORTD1

#define NRF24_TRANSMISSON_OK 0
#define NRF24_MESSAGE_LOST   1

#define mirf_CSN_hi     PORTB |=  (1<<CSN);
#define mirf_CSN_lo     PORTB &= ~(1<<CSN);
#define mirf_CE_hi      PORTB |=  (1<<CE);
#define mirf_CE_lo      PORTB &= ~(1<<CE);


class nRF24{
    private:
        SPI comunicacion ;
    public:
        nRF24();

        //funciones de ajustes 
        void mirf_init();
        void nrf24_rx_address(uint8_t* adr);
        void nrf24_tx_address(uint8_t* adr);
        void mirf_config(uint8_t,uint8_t);
       
        //funciones de verificacion de estado

        // funciones txt RX
        void mirf_send(uint8_t * value, uint8_t len);
        void nrf24_getData(uint8_t* data);

        //convercion de envion de informacion SPI
        void nrf24_transferSync(uint8_t* dataout,uint8_t* datain,uint8_t len); 
        void nrf24_transmitSync(uint8_t* dataout,uint8_t len);
        void nrf24_writeRegister(uint8_t reg, uint8_t* value, uint8_t len);
        void mirf_set_RADDR(uint8_t * adr);
        void mirf_config_register(uint8_t reg, uint8_t value);
        
        // ce administracion de energuia
        void nrf24_powerUpRx();
        void nrf24_powerUpTx();
        void nrf24_powerUpDon();
        //validar informacion
        uint8_t nrf24_dataReady();
        uint8_t nrf24_rxFifoEmpty();
        uint8_t nrf24_getStatus();
        void nrf24_readRegister(uint8_t reg, uint8_t* value, uint8_t len);
        uint8_t nrf24_isSending();
        uint8_t nrf24_lastMessageStatus();


};

