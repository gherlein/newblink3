

/**
 * Copyright (c) 2024 Gregory C Herlein
 * Derived from sample code at https://www.iopress.info/index.php/books/master-the-raspberry-pi-pico-in-c-wifi-with-lwip-mbedtls/9-programs/73-picocprogramswifi?showall=1
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico/stdlib.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"
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
    printf("IP: %s\n",
           ip4addr_ntoa(netif_ip_addr4(netif_default)));
    printf("Mask: %s\n",
           ip4addr_ntoa(netif_ip_netmask4(netif_default)));
    printf("Gateway: %s\n",
           ip4addr_ntoa(netif_ip_gw4(netif_default)));
    printf("Host Name: %s\n",
           netif_get_hostname(netif_default));
}

int main()
{
    uint32_t auth = CYW43_AUTH_WPA2_MIXED_PSK;
    // workaround for a hardware debug problem
    // https://forums.raspberrypi.com/viewtopic.php?t=363914
    // also in openocd you need to us -c "set USE_CORE 0"  before rp2040.cfg is loaded per https://github.com/raspberrypi/debugprobe/issues/45
    timer_hw->dbgpause = 0;
    sleep_ms(150);

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