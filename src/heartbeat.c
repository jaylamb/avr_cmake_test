#include <avr/io.h> 
#include <util/delay.h>

int main( void ){

    DDRB |= (1 << PB5);

    while (1) {
        PORTB= 0x20;
        _delay_ms( 500 );
        PORTB= 0x00;
        _delay_ms( 100 );
        PORTB= 0x20;
	_delay_ms( 500 );
	PORTB= 0x00;
	_delay_ms( 1000 );
    }

    return( 0 ); 
}
