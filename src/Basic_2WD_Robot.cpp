/*
    * Basic_2WD_Robot.cpp
    *
    * A simple demonstration of controlling a 2WD robot using the Raspberry Pi Pico.
    * This code initializes the motors and performs a series of movements to showcase basic functionality.
    *
    * Pasan_RK95
*/

#include <stdio.h>
#include "pico/stdlib.h"
#include "robot_2wd.h"

int main() {
    stdio_init_all();
    
    init_robot();
    
    printf("Starting Basic 2WD Robot Demo...\n");
    
    // Sample speed for demo
    int speed = MAX_SPEED * (2/3) ;

    sleep_ms(2000); // Wait for 2 seconds before starting the demo
    demo_movements(speed);

    // run again
    demo_movements(speed);
    
    // blink an LED to indicate demo completion (optional)
    const uint LED_PIN = PICO_DEFAULT_LED_PIN;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    while (true)
    {
        gpio_put(LED_PIN, 1); // LED on
        sleep_ms(500);
        gpio_put(LED_PIN, 0); // LED off
        sleep_ms(500);
    }

    printf("Demo Completed. Stopping Motors.\n");
    stop_motors();

    return 0;
}