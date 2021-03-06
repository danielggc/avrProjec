#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
 DDRB |= (1 << PORTB7); // PORTB7 direction = out
 
 while (1)
 {
  
  // 1 pulse
  PORTB |= (1 << PORTB7); // PORTB7 hi = LED L on
  _delay_ms(500); // 0.5 sec
  PORTB &= ~(1 << PORTB7); // PORTB7 hi = LED L off
  
  // delay
  _delay_ms(2000); // 2 sec

  // 2 pulses
  PORTB |= (1 << PORTB7);
  _delay_ms(500);
  PORTB &= ~(1 << PORTB7);
  _delay_ms(500);
  PORTB |= (1 << PORTB7);
  _delay_ms(500);
  PORTB &= ~(1 << PORTB7);

  // delay
  _delay_ms(2000);
 }
}
