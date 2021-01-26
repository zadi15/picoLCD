cmake_minimum_required(VERSION 3.12)

include(pico_sdk_import.cmake)

project(picoLCD)

pico_sdk_init()

add_executable(picoLCD
    main.c
    LCDops.c
    generalOps.c
)

pico_enable_stdio_usb(picoLCD 1)
pico_enable_stdio_uart(picoLCD 1)

pico_add_extra_outputs(picoLCD)

target_link_libraries(picoLCD pico_stdlib)
