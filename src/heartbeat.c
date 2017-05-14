#include <avr/io.h> 
#include <stdio.h>
#include <stdlib.h>
#include <util/delay.h>
#include <string.h>

// define some macros
#define BAUD 9600                                   // define baud
#define BAUDRATE ((F_CPU)/(BAUD*16UL)-1)            // set baud rate value for UBRR

void uart_init (void)
{
    UBRR0H  = (BAUDRATE>>8);                      // shift the register right by 8 bits
    UBRR0L  = BAUDRATE;                           // set baud rate
    UCSR0B |= (1<<TXEN0)|(1<<RXEN0);                // enable receiver and transmitter
    UCSR0C |= (1<<USBS0)|(3<<UCSZ00);
    //UCSR0C|= (1<<URSEL0)|(1<<UCSZ0)|(1<<UCSZ1);   // 8bit data format
}

void USART_Transmit( unsigned char data )
{
    /* Wait for empty transmit buffer */
    while ( !( UCSR0A & (1<<UDRE0)) );
    /* Put data into buffer, sends the data */
    UDR0 = data;
}

void usart_send_string( char const * const string )
{
    for( size_t i = 0; i < strlen(string); i++ )
        USART_Transmit( string[ i ] ); 
}

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

	//USART_Transmit( 'W' );
	usart_send_string( "BLINK\n\r" );
    }

    return( 0 ); 
}
