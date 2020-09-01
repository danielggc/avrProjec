#include "nRF24L01.hpp"
#include "mirf.hpp"

uint8_t payload_len;

void nrf24_init(){
	spi_init();
	mirf_CE_lo;
    _delay_us(10);    
    mirf_CSN_hi;    
}

void nrf24_config(uint8_t channel, uint8_t pay_length)
{
    payload_len = pay_length;

    nrf24_configRegister(RF_CH,channel);
    nrf24_configRegister(RX_PW_P1, payload_len); 
    nrf24_configRegister(RF_SETUP, (0<<RF_DR)|((0x03)<<RF_PWR));
    nrf24_configRegister(CONFIG,nrf24_CONFIG);
    nrf24_configRegister(EN_AA,(1<<ENAA_P0)|(1<<ENAA_P1)|(0<<ENAA_P2)|(0<<ENAA_P3)|(0<<ENAA_P4)|(0<<ENAA_P5));
    nrf24_configRegister(EN_RXADDR,(1<<ERX_P0)|(1<<ERX_P1)|(0<<ERX_P2)|(0<<ERX_P3)|(0<<ERX_P4)|(0<<ERX_P5));
    nrf24_configRegister(SETUP_RETR,(0x04<<ARD)|(0x0F<<ARC));
    nrf24_configRegister(DYNPD,(0<<DPL_P0)|(0<<DPL_P1)|(0<<DPL_P2)|(0<<DPL_P3)|(0<<DPL_P4)|(0<<DPL_P5));

    nrf24_powerUpRx();
    nrf24_powerUpTx();
}

void nrf24_rx_address(uint8_t * adr) 
{
	mirf_CE_lo
    nrf24_writeRegister(RX_ADDR_P1,adr,nrf24_ADDR_LEN);
  	mirf_CE_hi
}

uint8_t nrf24_payload_length()
{
    return payload_len;
}

void nrf24_tx_address(uint8_t* adr)
{
    nrf24_writeRegister(RX_ADDR_P0,adr,nrf24_ADDR_LEN);
    nrf24_writeRegister(TX_ADDR,adr,nrf24_ADDR_LEN);
}

uint8_t nrf24_dataReady() 
{
    uint8_t status = nrf24_getStatus();

    if ( status & (1 << RX_DR) ) 
    {
        return 1;
    }

    return !nrf24_rxFifoEmpty();;
}

uint8_t nrf24_rxFifoEmpty()
{
    uint8_t fifoStatus;

    nrf24_readRegister(FIFO_STATUS,&fifoStatus,1);
    
    return (fifoStatus & (1 << RX_EMPTY));
}

uint8_t nrf24_payloadLength()
{
    uint8_t status;
   	mirf_CSN_lo 
    _delay_us(10);
    spi_fast_shift(R_RX_PL_WID);
    status = spi_fast_shift(0x00);
    _delay_us(10);    
    mirf_CSN_hi;
    return status;
}

void nrf24_getData(uint8_t* data) 
{
   	mirf_CSN_lo 
    _delay_us(10);                               

    spi_fast_shift( R_RX_PAYLOAD );
    
    nrf24_transferSync(data,data,payload_len);
    
    _delay_us(10);    
    mirf_CSN_hi;

    nrf24_configRegister(STATUS,(1<<RX_DR));   
}

uint8_t nrf24_retransmissionCount()
{
    uint8_t rv;
    nrf24_readRegister(OBSERVE_TX,&rv,1);
    rv = rv & 0x0F;
    return rv;
}


void nrf24_send(uint8_t* value) 
{    
		mirf_CE_lo
     
    nrf24_powerUpTx();

    #if 1
       	mirf_CSN_lo 
        _delay_us(10);           

        spi_fast_shift(FLUSH_TX);     

    _delay_us(10);        
        mirf_CSN_hi;                    
    #endif 

   	mirf_CSN_lo 
    _delay_us(10);

    spi_fast_shift(W_TX_PAYLOAD);

    nrf24_transmitSync(value,payload_len);   

    _delay_us(10);    
    mirf_CSN_hi;

  	mirf_CE_hi    
}

uint8_t nrf24_isSending()
{
    uint8_t status;

    status = nrf24_getStatus();
                
    if((status & ((1 << TX_DS)  | (1 << MAX_RT))))
    {        
        return 0;
    }

    return 1; 

}

uint8_t nrf24_getStatus()
{
    uint8_t rv;
   	mirf_CSN_lo 
    _delay_us(10);
    rv = spi_fast_shift(NOP);
    _delay_us(10);    
    mirf_CSN_hi;
    return rv;
}

uint8_t nrf24_lastMessageStatus()
{
    uint8_t rv;

    rv = nrf24_getStatus();

    if((rv & ((1 << TX_DS))))
    {
        return NRF24_TRANSMISSON_OK;
    }
    else if((rv & ((1 << MAX_RT))))
    {
        return NRF24_MESSAGE_LOST;
    }  
    else
    {
        return 0xFF;
    }
}

void nrf24_powerUpRx()
{     
   	mirf_CSN_lo 
    _delay_us(10);
    spi_fast_shift(FLUSH_RX);
    _delay_us(10);    
    mirf_CSN_hi;

    nrf24_configRegister(STATUS,(1<<RX_DR)|(1<<TX_DS)|(1<<MAX_RT)); 

    mirf_CE_lo    
    nrf24_configRegister(CONFIG,nrf24_CONFIG|((1<<PWR_UP)|(1<<PRIM_RX)));    
  	mirf_CE_hi
}

void nrf24_powerUpTx()
{
    nrf24_configRegister(STATUS,(1<<RX_DR)|(1<<TX_DS)|(1<<MAX_RT)); 

    nrf24_configRegister(CONFIG,nrf24_CONFIG|((1<<PWR_UP)|(0<<PRIM_RX)));
}

void nrf24_powerDown()
{
		mirf_CE_lo
    nrf24_configRegister(CONFIG,nrf24_CONFIG);
}



void nrf24_transferSync(uint8_t* dataout,uint8_t* datain,uint8_t len)
{
    uint8_t i;

    for(i=0;i<len;i++)
    {
        datain[i] = spi_fast_shift(dataout[i]);
    }

}

void nrf24_transmitSync(uint8_t* dataout,uint8_t len)
{
    uint8_t i;
    
    for(i=0;i<len;i++)
    {
        spi_fast_shift(dataout[i]);
    }

}

void nrf24_configRegister(uint8_t reg, uint8_t value)
{
   	mirf_CSN_lo 
    _delay_us(10);
    spi_fast_shift(W_REGISTER | (REGISTER_MASK & reg));
    spi_fast_shift(value);
    _delay_us(10);    
    mirf_CSN_hi;
}

void nrf24_readRegister(uint8_t reg, uint8_t* value, uint8_t len)
{
   	mirf_CSN_lo 
    _delay_us(10);
    spi_fast_shift(R_REGISTER | (REGISTER_MASK & reg));
    nrf24_transferSync(value,value,len);
    _delay_us(10);    
    mirf_CSN_hi;
}

void nrf24_writeRegister(uint8_t reg, uint8_t* value, uint8_t len) 
{
   	mirf_CSN_lo 
    _delay_us(10);
    spi_fast_shift(W_REGISTER | (REGISTER_MASK & reg));
    nrf24_transmitSync(value,len);
    _delay_us(10);    
    mirf_CSN_hi;
}
