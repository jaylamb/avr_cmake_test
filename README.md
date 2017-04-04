Quick temporary "readme". Just notes on the state of things:

To build (at the moment)

1) Create and enter a build directory:
	mkdir build && cd build

2) Point CMake to the AVR toolchain:
	cmake -DCMAKE_TOOLCHAIN_FILE=../cmake_avr_functions.cmake ..

3) Make the deployable object:
	make

4) Enter the build/src directory (WTF?):
	cd src/

5) Deploy the .hex file to the MCU (Why sudo?):
	sudo avrdude -p m328p -P /dev/ttyUSB0 -c arduino -b 115200 -U flash:w:toggle-led.hex

This thing needs work, but it should be capable of getting a heartbeat led going.	 
