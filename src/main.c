/**
 * Copyright (c) 2022 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"

int main() {
   // workaround for a hardware debug problem
    // https://forums.raspberrypi.com/viewtopic.php?t=363914
    // also in openocd you need to us -c "set USE_CORE 0"  before rp2040.cfg is loaded per https://github.com/raspberrypi/debugprobe/issues/45
    timer_hw->dbgpause = 0;
    sleep_ms(150);


  stdio_init_all();
    if (cyw43_arch_init()) {
        printf("Wi-Fi init failed");
        return -1;
    }
    while (true) {
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
        sleep_ms(250);
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
        sleep_ms(250);
    }
}
