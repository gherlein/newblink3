

/**
 * Copyright (c) 2024 Gregory C Herlein
 * Derived from sample code at https://www.iopress.info/index.php/books/master-the-raspberry-pi-pico-in-c-wifi-with-lwip-mbedtls/9-programs/73-picocprogramswifi?showall=1
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "credentials.h"

int setup(uint32_t country, const char *ssid, const char *pass, uint32_t auth)
{
    if (cyw43_arch_init_with_country(country))
    {
        return 1;
    }
    cyw43_arch_enable_sta_mode();
    if (cyw43_arch_wifi_connect_blocking(ssid, pass, auth))
    {
        return 2;
    }
}

uint32_t auth = CYW43_AUTH_WPA2_MIXED_PSK;
int main()
{
    stdio_init_all();
    setup(country, ssid, pass, auth);
    while (true)
    {
        printf("on\n");
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
        sleep_ms(500);
        printf("off\n");
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
        sleep_ms(500);
    }
}