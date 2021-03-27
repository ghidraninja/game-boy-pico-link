/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "pio_spi.h"
const uint OE_PIN = 1;
const uint SI_PIN = 3;
const uint SO_PIN = 4;
const uint CLK_PIN = 2;

int main() {
    stdio_init_all();
    
    stdio_set_translate_crlf(&stdio_usb, false);

    pio_spi_inst_t spi = {
            .pio = pio0,
            .sm = 0
    };
    uint cpha1_prog_offs = pio_add_program(spi.pio, &spi_cpha1_program);
    pio_spi_init(spi.pio, spi.sm, cpha1_prog_offs, 8, 4058.838, 1, 1, CLK_PIN, SO_PIN, SI_PIN);

    gpio_init(OE_PIN);
    // gpio_init(SI_PIN);
    // gpio_init(SO_PIN);
    // gpio_init(CLK_PIN);

    gpio_set_dir(OE_PIN, GPIO_OUT);
    gpio_put(OE_PIN, 1);
    // gpio_set_dir(OE_PIN, GPIO_IN);
    // gpio_set_dir(SO_PIN, GPIO_OUT);



    while(1) {
        unsigned char tx = getchar();
        unsigned char rx;
        pio_spi_write8_read8_blocking(&spi, &tx, &rx, 1);
        // printf("Rec: %x\n", rx);
        putchar(rx);
    }

    printf("Good morning!\n");
    while(1) {
        sleep_ms(30);
        printf("Still alive\n");
        char tx = 0x11;
        char rx;
        pio_spi_write8_read8_blocking(&spi, &tx, &rx, 1);
        printf("Rec: %x\n", rx);
        putchar(rx);
    }
    // getchar();
    // PIO pio = pio0;
    // uint offset = pio_add_program(pio, &hello_program);

    // // Get an unused state machine
    // uint sm = pio_claim_unused_sm(pio, true);
    // hello_program_init(pio, sm, offset, PICO_DEFAULT_LED_PIN);
    // while (true) {
    //     printf("Hello, world!\n");
    //     printf("Pio offset is: %d\n", offset);
    //     pio_sm_put_blocking(pio, sm, 1);
    //     sleep_ms(1000);

    //     pio_sm_put_blocking(pio, sm, 0);
    //     sleep_ms(500);
    // }
    return 0;
}
// int main() {

//     const uint LED_PIN = 25;

//     gpio_init(LED_PIN);
//     gpio_set_dir(LED_PIN, GPIO_OUT);
//     while (true) {
//         gpio_put(LED_PIN, 1);
//         sleep_ms(250);
//         gpio_put(LED_PIN, 0);
//         sleep_ms(250);
//     }
