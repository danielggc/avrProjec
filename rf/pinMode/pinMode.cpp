#include"pinMode.hpp"

    PinConfiguration::PinConfiguration(char _portType){
        portType=_portType;
    }
    int PinConfiguration::Pind(unsigned int _pinRead){
        unsigned int pinRead =_pinRead;    
        if(portType == 'B'){
            if(pinRead & pin7){
                if (~PINB & (1 << PB7)){
                    return 1;
                }
                
            }
            else if(pinRead & pin6){
                if (~PINB & (1 << PB6)){
                    return 1;
                }
                
            }
            else if(pinRead & pin5){
                if (~PINB & (1 << PB5)){
                    return 1;
                }
                
            }            
            else if(pinRead & pin4){
                if (~PINB & (1 << PB4)){
                    return 1;
                }
                
            }
            else if(pinRead & pin3){
                if (~PINB & (1 << PB3)){
                    return 1;
                }
                
            }        
            else if(pinRead & pin2){
                if (~PINB & (1 << PB2)){
                    return 1;
                }
                
            }        
            else if(pinRead & pin1){
                if (~PINB & (1 << PB1)){
                    return 1;
                }
                
            }
            else if(pinRead & pin0){
                if (~PINB & (1 << PB0)){
                    return 1;
                }
                
            }  
            return 0;                  
        }
        if(portType == 'H'){
            if(pinRead & pin7){
                if (~PINH & (1 << PH7)){
                    return 1;
                }
                
            }
            else if(pinRead & pin6){
                if (~PINH & (1 << PH6)){
                    return 1;
                }
                
            }
            else if(pinRead & pin5){
                if (~PINH & (1 << PH5)){
                    return 1;
                }
                
            }            
            else if(pinRead & pin4){
                if (~PINH & (1 << PH4)){
                    return 1;
                }
                
            }
            else if(pinRead & pin3){
                if (~PINH & (1 << PH3)){
                    return 1;
                }
                
            }        
            else if(pinRead & pin2){
                if (~PINH & (1 << PH2)){
                    return 1;
                }
                
            }        
            else if(pinRead & pin1){
                if (~PINH & (1 << PH1)){
                    return 1;
                }
                
            }
            else if(pinRead & pin0){
                if (~PINH & (1 << PH0)){
                    return 1;
                }
                
            }
            return 0;                    
        }
    }
    void PinConfiguration::pinMode(unsigned int _operaciones){
        unsigned int operaciones = _operaciones;
        if(operaciones & LOW){
            if(portType == 'H'){
                if(operaciones & pin7){
                    DDRH |= (1 << PORTH7); 
                }
                else if(operaciones & pin6){
                    DDRH |= (1 << PORTH6); 
                }
                else if (operaciones & pin5){
                DDRH |= (1 << PORTH5); 
                }
                else if (operaciones & pin4){
                DDRH |= (1 << PORTH4); 
                }
                else if (operaciones & pin3){
                DDRH |= (1 << PORTH3); 
                }
                else if (operaciones & pin2){
                DDRH |= (1 << PORTH2); 
                }
                else if (operaciones & pin1){
                DDRH |= (1 << PORTH1); 
                }
                else if (operaciones & pin0){
                DDRH |= (1 << PORTH0); 
                }
            }
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
            if(portType == 'H'){
                if(operaciones & pin7){
                    DDRH &= ~(1 << PORTH7); 
                }
                else if(operaciones & pin6){
                    DDRH &= ~(1 << PORTH6); 
                }
                else if (operaciones & pin5){
                DDRH &= ~(1 << PORTH5); 
                }
                else if (operaciones & pin4){
                DDRH &= ~(1 << PORTH4); 
                }
                else if (operaciones & pin3){
                DDRH &= ~(1 << PORTH3); 
                }
                else if (operaciones & pin2){
                DDRH &= ~(1 << PORTH2); 
                }
                else if (operaciones & pin1){
                DDRH &= ~(1 << PORTH1); 
                }
                else if (operaciones & pin0){
                DDRH &= ~(1 << PORTH0); 
                }
            }
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
    }
    void PinConfiguration::diguitalWrite(unsigned int _operaciones){
        unsigned int operaciones = _operaciones;
        if(portType == 'H'){
            if(operaciones & pin7){
                if(operaciones & HIGHT){ 
                    PORTH |= (1 << PORTH7);
                }
                else{
                    PORTH &= ~(1 << PORTH7);
                }
            }
            else if(operaciones & pin6){
                if(operaciones & HIGHT ){
                    PORTH |= (1 << PORTH6);
                }
                else{
                    PORTH &= ~(1 << PORTH6);
                }
            }
            else if(operaciones & pin5 ){
                if(operaciones & HIGHT ){
                    PORTH |= (1 << PORTH5);
                }
                else{
                    PORTH &= ~(1 << PORTH5);
                }
            }
            else if(operaciones & pin4){
                if(operaciones & HIGHT ){
                    PORTH |= (1 << PORTH4);
                }
                else{
                    PORTH &= ~(1 << PORTH4);
                }
            }
            else if(operaciones & pin3){
                if(operaciones & HIGHT ){
                    PORTH |= (1 << PORTH3);
                }
                else{
                    PORTH &= ~(1 << PORTH3);
                }
            }
            else if(operaciones & pin2){
                if(operaciones & HIGHT ){
                    PORTH |= (1 << PORTH2);
                }
                else{
                    PORTH &= ~(1 << PORTH2);
                }
            }
            else if(operaciones & pin1){
                if(operaciones & HIGHT ){
                    PORTH |= (1 << PORTH1);
                }
                else{
                    PORTH &= ~(1 << PORTH1);
                }
            }
            else if(operaciones & pin0){
                if(operaciones & HIGHT ){
                    PORTH |= (1 << PORTH0);
                }
                else{
                    PORTH &= ~(1 << PORTH0);
                }
            }
        }

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