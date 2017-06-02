#include <stdint.h>
#include <avr/io.h>

void adc_init( uint8_t channel )
{
    ADCSRA |= (( 1 << ADPS2 ) | ( 1<<ADPS1 ) | ( 1 << ADPS0 ));
    ADMUX  |=  ( 1 << REFS0 );
    ADCSRA |=  ( 1 << ADEN  );
    ADCSRA |=  ( 1 << ADSC  ); 
}

uint16_t adc_read( uint8_t channel )
{
    ADMUX  &= 0xF0;
    ADMUX  |= channel;
    ADCSRA |= (1<<ADSC);
    while( ADCSRA & ( 1 << ADSC ));
    
    return ADCW; 
}