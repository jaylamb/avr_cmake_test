#include <avr/io.h> 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <util/delay.h>
#include "uart.h"

int main( void ){

uart_init();

    DDRB |= (1 << PB5);

    while (1) {
        PORTB= 0x20;
        _delay_ms( 100 );
        PORTB= 0x00;
        _delay_ms( 100 );
        PORTB= 0x20;
	_delay_ms( 300 );
	PORTB= 0x00;
	_delay_ms( 4500 );

	uart_send_string( "BLINK\n\r" );
    }

    return( 0 ); 
}
