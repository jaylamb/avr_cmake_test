#################################
###         LICENSE!!         ###
#################################

add_avr_executable(
	avr_playland
	avr_playland.c

	adc.c
	uart.c
    led.c
    tach.c
)
