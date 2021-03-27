cmake_minimum_required(VERSION 3.13)

# initialize the SDK based on PICO_SDK_PATH
# note: this must happen before project()
include(pico_sdk_import.cmake)

project(hello_world)

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

add_executable(hello_world

pio_spi.c
pio_spi.h
    hello_world.c
)


# Compile PIO program
#pico_generate_pio_header(hello_world ${CMAKE_CURRENT_LIST_DIR}/hello.pio)
pico_generate_pio_header(hello_world ${CMAKE_CURRENT_LIST_DIR}/spi.pio)

# Add pico_stdlib library which aggregates commonly used features
target_link_libraries(hello_world pico_stdlib hardware_pio)

# enable usb output, disable uart output
pico_enable_stdio_usb(hello_world 1)
pico_enable_stdio_uart(hello_world 0)

# create map/bin/hex/uf2 file in addition to ELF.
pico_add_extra_outputs(hello_world)


# add url via pico_set_program_url
# example_auto_set_url(hello_world)