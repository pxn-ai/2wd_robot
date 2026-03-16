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
    int speed = 100;
    
    sleep_ms(2000); // Wait for 2 seconds before starting the demo
    demo_movements(speed);

    printf("Demo Completed. Stopping Motors.\n");
    stop_motors();
    
    return 0;
}