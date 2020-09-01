#include "nRF24L01.hpp"
#include "mirf.hpp"


Nrf24::Nrf24(){
    SPI comunicacion;
    comunicacion.SPI_Init(Master);
}
void Nrf24::nrf24_init(){
    DDRB |= ((1<<CSN)|(1<<CE));
    mirf_CE_lo;
    mirf_CSN_hi;
}

void Nrf24::nrf24_config(){
    
    nrf24_configRegister(RF_CH,mirf_CH);
    nrf24_configRegister(RX_PW_P0, mirf_PAYLOAD);
    nrf24_powerUpRx();
    mirf_CE_hi;
}

void Nrf24::nrf24_rx_address(uint8_t * adr) {
	mirf_CE_lo
    nrf24_writeRegister(RX_ADDR_P1,adr,nrf24_ADDR_LEN);
  	mirf_CE_hi
}

uint8_t  Nrf24::nrf24_payload_length(){
    return  mirf_PAYLOAD;
}

void Nrf24::nrf24_tx_address(uint8_t* adr){
    nrf24_writeRegister(RX_ADDR_P0,adr,nrf24_ADDR_LEN);
    nrf24_writeRegister(TX_ADDR,adr,nrf24_ADDR_LEN);
}

uint8_t  Nrf24::nrf24_dataReady() {
    uint8_t status = nrf24_getStatus();

    if ( status & (1 << RX_DR) ){
        return 1;
    }

    return !nrf24_rxFifoEmpty();;
}

uint8_t  Nrf24::nrf24_rxFifoEmpty(){
    uint8_t fifoStatus;

    nrf24_readRegister(FIFO_STATUS,&fifoStatus,1);
    
    return (fifoStatus & (1 << RX_EMPTY));
}

uint8_t  Nrf24::nrf24_payloadLength(){
    uint8_t status;
   	mirf_CSN_lo 
    _delay_us(10);
    comunicacion.SPI_uint8_tTransmit(R_RX_PL_WID);
    status = comunicacion.SPI_uint8_tTransmit(0x00);
    _delay_us(10);    
    mirf_CSN_hi;
    return status;
}

void Nrf24::nrf24_getData(uint8_t* data){
   	mirf_CSN_lo 
    _delay_us(10);                               

    comunicacion.SPI_uint8_tTransmit( R_RX_PAYLOAD );
    
    nrf24_transferSync(data,data,mirf_PAYLOAD);
    
    _delay_us(10);    
    mirf_CSN_hi;

    nrf24_configRegister(STATUS,(1<<RX_DR));   
}

uint8_t  Nrf24::nrf24_retransmissionCount(){
    uint8_t rv;
    nrf24_readRegister(OBSERVE_TX,&rv,1);
    rv = rv & 0x0F;
    return rv;
}


void Nrf24::nrf24_send(uint8_t* value) {    
		mirf_CE_lo
     
    nrf24_powerUpTx();

    #if 1
       	mirf_CSN_lo 
        _delay_us(10);           

        comunicacion.SPI_uint8_tTransmit(FLUSH_TX);     

    _delay_us(10);        
        mirf_CSN_hi;                    
    #endif 

   	mirf_CSN_lo 
    _delay_us(10);

    comunicacion.SPI_uint8_tTransmit(W_TX_PAYLOAD);

    nrf24_transmitSync(value,mirf_PAYLOAD);   

    _delay_us(10);    
    mirf_CSN_hi;

  	mirf_CE_hi    
}

uint8_t  Nrf24::nrf24_isSending(){
    uint8_t status;

    status = nrf24_getStatus();
                
    if((status & ((1 << TX_DS)  | (1 << MAX_RT)))){        
        return 0;
    }

    return 1; 

}

uint8_t  Nrf24::nrf24_getStatus(){
    uint8_t rv;
   	mirf_CSN_lo 
    _delay_us(10);
    rv = comunicacion.SPI_uint8_tTransmit(NOP);
    _delay_us(10);    
    mirf_CSN_hi;
    return rv;
}

uint8_t   Nrf24::nrf24_lastMessageStatus(){
    uint8_t rv;

    rv = nrf24_getStatus();

    if((rv & ((1 << TX_DS)))){
        return NRF24_TRANSMISSON_OK;
    }
    else if((rv & ((1 << MAX_RT)))){
        return NRF24_MESSAGE_LOST;
    }  
    else{
        return 0xFF;
    }
}

void Nrf24::nrf24_powerUpRx(){     
   	mirf_CSN_lo 
    _delay_us(10);
    comunicacion.SPI_uint8_tTransmit(FLUSH_RX);
    _delay_us(10);    
    mirf_CSN_hi;

    nrf24_configRegister(STATUS,(1<<RX_DR)|(1<<TX_DS)|(1<<MAX_RT)); 

    mirf_CE_lo    
    nrf24_configRegister(CONFIG,nrf24_CONFIG|((1<<PWR_UP)|(1<<PRIM_RX)));    
  	mirf_CE_hi
}

void Nrf24::nrf24_powerUpTx(){
    nrf24_configRegister(STATUS,(1<<RX_DR)|(1<<TX_DS)|(1<<MAX_RT)); 

    nrf24_configRegister(CONFIG,nrf24_CONFIG|((1<<PWR_UP)|(0<<PRIM_RX)));
}

void Nrf24::nrf24_powerDown(){
		mirf_CE_lo
    nrf24_configRegister(CONFIG,nrf24_CONFIG);
}



void Nrf24::nrf24_transferSync(uint8_t* dataout,uint8_t* datain,uint8_t len){
    uint8_t i;

    for(i=0;i<len;i++){
        datain[i] = comunicacion.SPI_uint8_tTransmit(dataout[i]);
    }

}

void Nrf24::nrf24_transmitSync(uint8_t* dataout,uint8_t len){
    uint8_t i;
    
    for(i=0;i<len;i++){
        comunicacion.SPI_uint8_tTransmit(dataout[i]);
    }

}

void Nrf24::nrf24_configRegister(uint8_t reg, uint8_t value){
   	mirf_CSN_lo 
    _delay_us(10);
    comunicacion.SPI_uint8_tTransmit(W_REGISTER | (REGISTER_MASK & reg));
    comunicacion.SPI_uint8_tTransmit(value);
    _delay_us(10);    
    mirf_CSN_hi;
}

void Nrf24::nrf24_readRegister(uint8_t reg, uint8_t* value, uint8_t len){
   	mirf_CSN_lo 
    _delay_us(10);
    comunicacion.SPI_uint8_tTransmit(R_REGISTER | (REGISTER_MASK & reg));
    nrf24_transferSync(value,value,len);
    _delay_us(10);    
    mirf_CSN_hi;
}

void Nrf24::nrf24_writeRegister(uint8_t reg, uint8_t* value, uint8_t len) {
   	mirf_CSN_lo 
    _delay_us(10);
    comunicacion.SPI_uint8_tTransmit(W_REGISTER | (REGISTER_MASK & reg));
    nrf24_transmitSync(value,len);
    _delay_us(10);    
    mirf_CSN_hi;
}
