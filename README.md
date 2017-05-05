To build:

1) Create and enter a build directory:
	mkdir build && cd build

2) Point CMake to the AVR toolchain:
	cmake -DCMAKE_TOOLCHAIN_FILE=../cmake_avr_functions.cmake ..

3) Make and deploy the executable:
	make upload_heartbeat


