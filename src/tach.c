#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <util/delay.h>

#include "tach.h"
#include "uart.h"

bool     volatile tach_trigger;
uint8_t  volatile timer_value;
uint32_t volatile overflow_count;
uint32_t volatile measured_time;

uint32_t const TIMER_FREQUENCY = 2000000;
uint32_t const FIVE_SECONDS = 39063;

void tach_init( void )
{
    timer_value = 0;
    overflow_count = 0;

    configure_external_interrupt();

    configure_timer0();
}

uint32_t read_tachometer( void )
{
    _delay_ms( 100 );
    return measured_time;
}

bool wait_for_tach_trigger( void )
{
    tach_trigger = false;
    reset_timer();
    uart_send_string( "Waiting for tach pulse..." );
    
    while( !tach_trigger )
    {
       if ( overflow_count > FIVE_SECONDS )
       {
        uart_send_string("timed out.\n\r");
        return false;
       }
    }

    uart_send_string("pulse received.\n\r");
    return true;
}

void configure_external_interrupt( void )
{
    DDRD &= ( 0 << PD2 );

    EICRA |= ( 1 << ISC01 | 1 << ISC00 );
    EIMSK |= ( 1 << INT0 );
}

void configure_timer0( void )
{
    TCCR0B |= ( 1 << CS01  );
    TIMSK0 |= ( 1 << TOIE0 );
}

uint32_t get_current_time( void )
{
    timer_value = TCNT0;
    return ( overflow_count * 256 ) + timer_value;
}

void reset_timer( void )
{
    timer_value = 0;
    overflow_count = 0;
}

/**
 * \brief Interrupt service routine for external interrupt INT0.
 */
 ISR(INT0_vect)
 {
    measured_time = get_current_time();

    if( !tach_trigger ){ tach_trigger = true; }

    reset_timer();
 }

/**
 * \brief Interrupt service routine for Timer/Counter0 overflow.
 */
 ISR(TIMER0_OVF_vect)
 {
     overflow_count++;
 }
