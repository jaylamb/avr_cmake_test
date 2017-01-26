#include <avr/io.h> 
#include <util/delay.h>

int main( void ){

    DDRB |= (1 << PB5);

    while (1) {
        PORTB= 0b00100000;
        _delay_ms( 500 );
        PORTB= 0b00000000;
        _delay_ms( 500 );
    }

    return( 0 ); 
}
