#include <avr/interrupt.h> 
#include <avr/io.h> 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <util/delay.h>

#include "adc.h"
#include "led.h"
#include "tach.h"
#include "uart.h"

int main( void ){

//uint16_t adc_result;
//char adc_string [5];

uint32_t const TIMER_FREQUENCY = 2000000;
int32_t frequency_ticks = 0;
int32_t frequency_whole = 0;
int32_t frequency_tenths = 0;

char frequency_string[20];

uart_init();
uart_send_string( "UART Initialized.\n\r" );

adc_init();
uart_send_string( "ADC Initialized on channel 0.\n\r" );

tach_init();
uart_send_string( "Tach Initialized.\n\r" );

led_init();
uart_send_string( "LED Initialized.\n\r" );

sei();

    while (1) {
        led_blink();

        if ( wait_for_tach_trigger())
        {
            frequency_ticks = read_tachometer();
            frequency_whole = TIMER_FREQUENCY / frequency_ticks;
            frequency_tenths = ( TIMER_FREQUENCY * 10 / frequency_ticks ) - ( frequency_whole * 10 );

            sprintf( frequency_string, "%lu.%lu\n\r", frequency_whole, frequency_tenths); 
            uart_send_string( frequency_string );
        }

        //adc_result = adc_read( 0 );
        //uart_send_string( strcat( itoa( adc_result, adc_string, 10 ), "\n\r" ));

        _delay_ms( 2000 );
    }

return( 0 ); 

}
