#include <avr/interrupt.h>
#include <avr/io.h> 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <util/delay.h>

#include "uart.h"
#include "adc.h"

int main( void ){

uint16_t adc_result;
char adc_string [5];

uart_init();
uart_send_string( "UART Initialized.\n\r" );

adc_init( );
uart_send_string( "ADC Initialized on channel 0.\n\r" );

sei();
uart_send_string( "Interrupts Initialized\n\r" );

    DDRB |= (1 << PB5);
    DDRD &= (0 << PD2);

    EICRA |= (1<<ISC01)|(1<<ISC00); // enable receiver and transmitter
    EIMSK |= (1<<INT0);             // 8 bit data format

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

	adc_result = adc_read( 0 );

	uart_send_string( strcat( itoa( adc_result, adc_string, 10 ), "\n\r" ));

    }

    return( 0 ); 
}

ISR(INT0_vect){
	uart_send_string( "WOWEE\n\r" );
}
