#include"PIN.hpp"


void configAnalogPWM(){
    
   DDRB |= (1<<PB3);
    TCCR2A |= (1<<WGM21)|(1<<WGM20);
    TCCR2A |= (1<<COM2A1)|(1<<COM2A0)|(0<<COM2B1)|(0<<COM2B0);
    TCCR2B |= (0<<CS02)|(1<<CS00);
    
}



void adc_init()
{
    ADMUX = (1<<REFS0);
    ADCSRA = (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
}
uint16_t adc_read(uint8_t ch){
  ch &= 0b00000111; 
  ADMUX = (ADMUX & 0xF8)|ch; 
  ADCSRA |= (1<<ADSC);
  while(ADCSRA & (1<<ADSC));
  return (ADC);
}


PinConfiguration::PinConfiguration(char _portType){
    portType=_portType;
}
int PinConfiguration::Pind(unsigned int _pinRead){
    unsigned int pinRead =_pinRead;    
    if(portType == 'B'){
        if(pinRead & pin7){
            if (~PINB & (1 << PORT7)){
                return 1;
            }                
        }
        else if(pinRead & pin6){
            if (~PINB & (1 << PORT6)){
                return 1;
            }                
        }
        else if(pinRead & pin5){
            if (~PINB & (1 << PORT5)){
                return 1;
            }        
        }            
        else if(pinRead & pin4){
            if (~PINB & (1 << PORT4)){
                return 1;
            }        
        }
        else if(pinRead & pin3){
            if (~PINB & (1 << PORT3)){
                return 1;
            }                
        }        
        else if(pinRead & pin2){
            if (~PINB & (1 << PORT2)){
                return 1;
            }        
        }        
        else if(pinRead & pin1){
            if (~PINB & (1 << PORT1)){
                return 1;
            }                
        }
        else if(pinRead & pin0){
            if (~PINB & (1 << PORT0)){
                return 1;
            }                
        }  
        return 0;                  
    }
}

void PinConfiguration::pinMode(unsigned int _operaciones){
    unsigned int operaciones = _operaciones;
    if(operaciones & LOW){
         if(portType == 'B'){
            if(operaciones & pin7){
                DDRB |= (1 << PORTB7); 
            }
            else if(operaciones & pin6){
                DDRB |= (1 << PORTB6); 
            }
            else if (operaciones & pin5){
                DDRB |= (1 << PORTB5); 
            }
            else if (operaciones & pin4){
                DDRB |= (1 << PORTB4); 
            }
            else if (operaciones & pin3){
                DDRB |= (1 << PORTB3); 
            }
            else if (operaciones & pin2){
                DDRB |= (1 << PORTB2); 
            }
            else if (operaciones & pin1){
                DDRB |= (1 << PORTB1); 
            }
            else if (operaciones & pin0){
                DDRB |= (1 << PORTB0); 
            }
        }
    }
    if(operaciones & HIGHT){
        if(portType == 'B'){
            if(operaciones & pin7){
                DDRB &= ~(1 << PORTB7); 
            }
            else if(operaciones & pin6){
                DDRB &= ~(1 << PORTB6); 
            }
            else if (operaciones & pin5){
                DDRB &= ~(1 << PORTB5); 
            }
            else if (operaciones & pin4){
                DDRB &= ~(1 << PORTB4); 
            }
            else if (operaciones & pin3){
                DDRB &= ~(1 << PORTB3); 
            }
            else if (operaciones & pin2){
                DDRB &= ~(1 << PORTB2); 
            }
            else if (operaciones & pin1){
                DDRB &= ~(1 << PORTB1); 
            }
            else if (operaciones & pin0){
                DDRB &= ~(1 << PORTB0); 
            }
        }
    }
    if(operaciones & LOW){
         if(portType == 'D'){
            if(operaciones & pin7){
                DDRD |= (1 << PORTD7); 
            }
            else if(operaciones & pin6){
                DDRD |= (1 << PORTD6); 
            }
            else if (operaciones & pin5){
                DDRD |= (1 << PORTD5); 
            }
            else if (operaciones & pin4){
                DDRD |= (1 << PORTD4); 
            }
            else if (operaciones & pin3){
                DDRD |= (1 << PORTD3); 
            }
            else if (operaciones & pin2){
                DDRD |= (1 << PORTD2); 
            }
            else if (operaciones & pin1){
                DDRD |= (1 << PORTD1); 
            }
            else if (operaciones & pin0){
                DDRD |= (1 << PORTD0); 
            }
        }
    }
    if(operaciones & HIGHT){
        if(portType == 'D'){
            if(operaciones & pin7){
                DDRD &= ~(1 << PORTD7); 
            }
            else if(operaciones & pin6){
                DDRD &= ~(1 << PORTD6); 
            }
            else if (operaciones & pin5){
                DDRD &= ~(1 << PORTD5); 
            }
            else if (operaciones & pin4){
                DDRD &= ~(1 << PORTD4); 
            }
            else if (operaciones & pin3){
                DDRD &= ~(1 << PORTD3); 
            }
            else if (operaciones & pin2){
                DDRD &= ~(1 << PORTD2); 
            }
            else if (operaciones & pin1){
                DDRD &= ~(1 << PORTD1); 
            }
            else if (operaciones & pin0){
                DDRD &= ~(1 << PORTD0); 
            }
        }
    }
}

void PinConfiguration::diguitalWrite(unsigned int _operaciones){
    unsigned int operaciones = _operaciones;
if(portType  ==  'B'){
        if(operaciones & pin7){
            if(operaciones & HIGHT ){
                PORTB |= (1 << PORTB7);
            }
            else{
                PORTB &= ~(1 << PORTB7);
            }
        }    
        else if(operaciones & pin6){
            if(operaciones & HIGHT ){
                PORTB |= (1 << PORTB6);
            }
            else{
                PORTB &= ~(1 << PORTB6);
            }
        }
        else if(operaciones & pin5){
            if(operaciones & HIGHT ){
                PORTB |= (1 << PORTB5);
            }
            else{
                PORTB &= ~(1 << PORTB5);
            }
        }
        else if(operaciones & pin4){
            if(operaciones & HIGHT ){
                PORTB |= (1 << PORTB4);
            }
            else{
                PORTB &= ~(1 << PORTB4);
            }
        }            
        else if(operaciones & pin3){
            if(operaciones & HIGHT ){
                PORTB |= (1 << PORTB3);
            }
            else{
                PORTB &= ~(1 << PORTB3);
            }
        }
        else if(operaciones & pin2){
            if(operaciones & HIGHT ){
                PORTB |= (1 << PORTB2);
            }
            else{
                PORTB &= ~(1 << PORTB2);
            }
        }
        else if(operaciones & pin1){
            if(operaciones & HIGHT ){
                PORTB |= (1 << PORTB1);
            }
            else{
                PORTB &= ~(1 << PORTB1);
            }
        }
        else if(operaciones & pin0){
            if(operaciones & HIGHT ){
                PORTB |= (1 << PORTB0);
            }
            else{
                PORTB &= ~(1 << PORTB0);
            }
        }
    }
}







