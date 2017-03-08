#
# Licence
#

#


# options
option(WITH_MCU "Add the MCU type to the target file name." ON)

# executables in use
find_program(AVR_CC avr-gcc)
find_program(AVR_CXX avr-g++)
find_program(AVR_OBJCOPY avr-objcopy)
find_program(AVR_SIZE_TOOL avr-size)
find_program(AVR_OBJDUMP avr-objdump)

# toolchain starts with defining madatory variables
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR, avr)
set(CMAKE_C_COMPILER ${AVR_CC})
set(CMAKE_CXX_COMPILER ${AVR_CXX})

# add exe
# Creates targets and dependencies for AVR toolchain, building an
# executable. Calls add_exe with ELF file as target name so any link
# dependencies ned to be using that target, e.g. for
# target_link_libraries(<EXECUTABLE_NAME>-${AVR_MCU).elf ...)

function(add_avr_executable EXECUTABLE_NAME)
    if (NOT ARGN)
        message(FATAL_ERROR "No source files given for ${EXECUTABLE_NAME}.")		
    endif(NOT ARGN)

    # set file names
    set(elf_file     ${EXECUTABLE_NAME}${MCU_TYPE_FOR_FILENAME}.elf)
    set(hex_file     ${EXECUTABLE_NAME}${MCU_TYPE_FOR_FILENAME}.hex)
    set(map_file     ${EXECUTABLE_NAME}${MCU_TYPE_FOR_FILENAME}.map)
    set(eeprom_image ${EXECUTABLE_NAME}${MCU_TYPE_FOR_FILENAME}.eeprom)
    
    # elf file
    add_executable(${elf_file} EXCLUDE_FROM_ALL ${ARGN})

    set_target_properties(
        ${elf_file}
        PROPERTIES
            COMPILE_FLAGS "-mcu=${AVR_MCU}, -m32"
            LINK_FLAGS "-mmcu=${AVR_MCU} -Wl, -m32, --gc-sections -mrelax -Wl, -Map, ${map_file}"
    )
