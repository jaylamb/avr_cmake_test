//Define macros
#include <avr/io.h> 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <util/delay.h>
#include "uart.h"

#define BAUD 9600                                 // define baud

#define BAUDRATE ((F_CPU)/(BAUD*16UL)-1)          // set baud rate value for UBRR

void uart_init (void)
{   
    UBRR0H  = (BAUDRATE>>8);                      // shift the register right by 8 bits
    UBRR0L  = BAUDRATE;                           // set baud rate
    UCSR0B |= (1<<TXEN0)|(1<<RXEN0);              // enable receiver and transmitter
    UCSR0C |= (1<<USBS0)|(3<<UCSZ00);             // 8 bit data format
}

void uart_transmit( unsigned char data )
{
    while ( !( UCSR0A & (1<<UDRE0)) );            // wait for transmit buffer to be empty
    UDR0 = data;                                  // place input character into tx buffer
}

void uart_send_string( char * const string )
{
    for( size_t i = 0; i < strlen(string); i++ )
        uart_transmit( string[ i ] );
}
