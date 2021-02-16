#include <stdbool.h>

/**
 * \brief Initialize tachometer.
 */
void tach_init( void );

/**
 * \brief Read the frequency measured by the tachometer.
 */
uint32_t read_tachometer( void );

/**
 * \brief Wait for a tach pulse.
 *
 * \return true once a pulse is received
 * \return false if a pulse is not received within five seconds
 */
 bool wait_for_tach_trigger( void );

/**
 * \brief Configure external interrupt INT0.
 */
void configure_external_interrupt( void );

/**
 * \brief Initialize Timer/Counter0.
 */
void configure_timer0( void );

/**
 * \brief Calculate the current time on Timer0
 *
 * \return The current time on Timer0
 */
 uint32_t get_current_time( void );

/**
 * \brief Reset timer.
 */
 void reset_timer( void );
