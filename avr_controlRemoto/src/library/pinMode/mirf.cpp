#include "mirf.h"
#include "nRF24L01.hpp"

volatile uint8_t PTX;
uint8_t payload_len;

nRF24::nRF24(){
    SPI comunicacion ;
    comunicacion.SPI_Init(Master);
}
void nRF24::mirf_init(){
    DDRB |=  (1<<CE)|(1<<CSN);
    mirf_CE_lo;
    mirf_CSN_hi;
}

void nRF24::mirf_config(uint8_t channel, uint8_t pay_length){
/* 
    mirf_CE_lo;
    payload_len = pay_length;
    mirf_config_register(RF_CH,channel);
    mirf_config_register(RX_PW_P0, 0x00); // Auto-ACK pipe ...
    mirf_config_register(RX_PW_P1, payload_len); // Data payload pipe
    mirf_config_register(RX_PW_P2, 0x00); // Pipe not used 
    mirf_config_register(RX_PW_P3, 0x00); // Pipe not used 
    mirf_config_register(RX_PW_P4, 0x00); // Pipe not used 
    mirf_config_register(RX_PW_P5, 0x00); // Pipe not used 
    mirf_config_register(RF_SETUP, (0<<RF_DR)|((0x03)<<RF_PWR));
    mirf_config_register(CONFIG,nrf24_CONFIG);
    mirf_config_register(EN_AA,(1<<ENAA_P0)|(1<<ENAA_P1)|(0<<ENAA_P2)|(0<<ENAA_P3)|(0<<ENAA_P4)|(0<<ENAA_P5));
    mirf_config_register(EN_RXADDR,(1<<ERX_P0)|(1<<ERX_P1)|(0<<ERX_P2)|(0<<ERX_P3)|(0<<ERX_P4)|(0<<ERX_P5));
    mirf_config_register(SETUP_RETR,(0x04<<ARD)|(0x0F<<ARC));
    mirf_config_register(DYNPD,(0<<DPL_P0)|(0<<DPL_P1)|(0<<DPL_P2)|(0<<DPL_P3)|(0<<DPL_P4)|(0<<DPL_P5));
    nrf24_powerUpRx();
    mirf_CE_hi;


    
*/  
    payload_len = pay_length;
    mirf_config_register(RF_CH,channel);
    mirf_config_register(RX_PW_P0, 0x00); 
    mirf_config_register(RX_PW_P1, pay_length);
    mirf_config_register(RX_PW_P2, 0x00); 
    mirf_config_register(RX_PW_P3, 0X00); 
    mirf_config_register(RX_PW_P4, 0x00);  
    mirf_config_register(RX_PW_P5, 0x00);  
    mirf_config_register(RF_SETUP, (0<<RF_DR)|((0x03)<<RF_PWR));
    mirf_config_register(CONFIG,nrf24_CONFIG);
    mirf_config_register(EN_AA,(1<<ENAA_P0)|(1<<ENAA_P1)|(0<<ENAA_P2)|(0<<ENAA_P3)|(0<<ENAA_P4)|(0<<ENAA_P5));
    mirf_config_register(EN_RXADDR,(1<<ERX_P0)|(1<<ERX_P1)|(0<<ERX_P2)|(0<<ERX_P3)|(0<<ERX_P4)|(0<<ERX_P5));
    mirf_config_register(SETUP_RETR,(0x04<<ARD)|(0x0F<<ARC));
    mirf_config_register(DYNPD,(0<<DPL_P0)|(0<<DPL_P1)|(0<<DPL_P2)|(0<<DPL_P3)|(0<<DPL_P4)|(0<<DPL_P5));
    nrf24_powerUpRx(); 
    mirf_CE_hi;   
  }

void nRF24::nrf24_flushRX(){
    mirf_CSN_lo;
    comunicacion.SPI_uint8_tTransmit(FLUSH_RX);
    mirf_CSN_hi;
}
void nRF24::nrf24_powerUpRx(){     
    nrf24_flushRX();
    mirf_config_register(STATUS,(1<<MASK_RX_DR)|(1<<MASK_TX_DS)|(1<<MASK_MAX_RT));
    mirf_CE_lo;
    mirf_config_register(CONFIG,nrf24_CONFIG|((1<<PWR_UP)|(1<<PRIM_RX)));    
    mirf_CE_hi;
}

void nRF24:: mirf_config_register(uint8_t reg, uint8_t value){
    mirf_CSN_lo;
    comunicacion.SPI_uint8_tTransmit(W_REGISTER|(REGISTER_MASK & reg));
    comunicacion.SPI_uint8_tTransmit(value);
    mirf_CSN_hi;

}

void nRF24::nrf24_rx_address(uint8_t* adr){
    mirf_CE_lo;
    nrf24_writeRegister(RX_ADDR_P1,adr,nrf24_ADDR_LEN);
    mirf_CE_hi;
}

void nRF24::nrf24_tx_address(uint8_t* adr){
    nrf24_writeRegister(TX_ADDR,adr,nrf24_ADDR_LEN);
    nrf24_writeRegister(RX_ADDR_P0,adr,nrf24_ADDR_LEN);
}

void nRF24::nrf24_writeRegister(uint8_t reg, uint8_t* value, uint8_t len){
    mirf_CE_lo;
    comunicacion.SPI_uint8_tTransmit(W_REGISTER|(REGISTER_MASK & reg));
    nrf24_transmitSync(value,len);
    mirf_CE_hi;
}

// VERIFICACION
void nRF24::nrf24_readRegister(uint8_t reg, uint8_t* value, uint8_t len){
    mirf_CSN_lo;
    comunicacion.SPI_uint8_tTransmit(R_REGISTER|(REGISTER_MASK & reg));
    nrf24_transferSync(value,value,len);
    mirf_CSN_hi;
}

uint8_t nRF24::nrf24_getStatus(){
    uint8_t status;    
    mirf_CSN_lo;
    status = comunicacion.SPI_uint8_tTransmit(NOP);
    mirf_CSN_hi;
    return status;
}


uint8_t nRF24::nrf24_rxFifoEmpty(){
    uint8_t fifoStatus;
    nrf24_readRegister(FIFO_STATUS,&fifoStatus,1);
    return (fifoStatus & (1<<RX_EMPTY));
}

uint8_t nRF24::nrf24_isSending(){
    uint8_t status;
    status=nrf24_getStatus();
    if(status & ((1<<MASK_TX_DS)|(1<<MASK_MAX_RT))){
        return 0 ;//falso!!!!
    }
    return 1;
}

uint8_t nRF24::nrf24_lastMessageStatus(){
    uint8_t rv;
    rv = nrf24_getStatus();
    if((rv & ((1 << MASK_TX_DS)))){
        return NRF24_TRANSMISSON_OK;
    }

    else if((rv & ((1 << MASK_MAX_RT)))){
        return NRF24_MESSAGE_LOST;
    }  

    else{
        return 0xFF;
    }
}
uint8_t nRF24::nrf24_dataReady(){
    uint8_t status = nrf24_getStatus();
    
    if ( status & (1 << MASK_RX_DR)){
        return 1;
    }
    else if(status & (1<<PRIM_RX)){
        return 4;    

    }
    return !nrf24_rxFifoEmpty();;
}


//comunicacion
void nRF24::mirf_send(uint8_t *value){
        uint8_t status;
        do{
            status=comunicacion.SPI_uint8_tTransmit(NOP);
        } while ( !( status & ( (1 << MASK_TX_DS) | (1 << MASK_RX_DR) ) ) );

        mirf_CE_lo;
        nrf24_powerUpTx();
        mirf_CSN_lo;
        comunicacion.SPI_uint8_tTransmit(FLUSH_TX);
        mirf_CSN_hi;
        _delay_ms(10);
        mirf_CSN_lo;
        comunicacion.SPI_uint8_tTransmit(W_TX_PAYLOAD);
        for(int i=0; i<mirf_PAYLOAD;i++){
            comunicacion.SPI_uint8_tTransmit(value[i]);
        }
        _delay_ms(10);
        mirf_CSN_hi;
        mirf_CE_hi;
        
}

uint8_t nRF24::nrf24_getData(uint8_t* data){
    mirf_CSN_lo;
    comunicacion.SPI_uint8_tTransmit(R_RX_PAYLOAD);
    for(int i=0;i<mirf_PAYLOAD;i++){
        data[i] =comunicacion.SPI_uint8_tTransmit(R_RX_PAYLOAD);
    }
    //nrf24_transferSync(data,data,payload_len);
    mirf_CSN_hi;
    mirf_config_register(STATUS,(1<<MASK_RX_DR));
}
///cuidado esto no tiene algo de sentido
void nRF24::nrf24_transferSync(uint8_t* dataout,uint8_t* datain,uint8_t len){
    for(int i;i<len;i++){
        dataout[i] =comunicacion.SPI_uint8_tTransmit(NOP);
    }
}

void nRF24::nrf24_transmitSync(uint8_t* dataout, uint8_t len){
    uint8_t i;
    for(i=0;i<len;i++){
        comunicacion.SPI_uint8_tTransmit(dataout[i]);

    }
}

void nRF24::nrf24_powerUpTx(){
    mirf_config_register(STATUS,(1<<MASK_RX_DR)|(1<<MASK_TX_DS)|(1<<MASK_MAX_RT));
    mirf_config_register(CONFIG,mirf_CONFIG|((1<<PWR_UP)|(0<<PRIM_RX)));
}



