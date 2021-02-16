#include <avr/io.h> 
#include <util/delay.h>

#include "led.h"

void led_init( void )
{
    DDRB |= (1 << PB5);
}

void led_blink( void ){

    PORTB= 0x20;
    _delay_ms( 100 );
    PORTB= 0x00;
    _delay_ms( 100 );
    PORTB= 0x20;
    _delay_ms( 300 );
    PORTB= 0x00;
}
