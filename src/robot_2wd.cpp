/*
    *   robot_2wd.cpp
    *   Created on: Jun 6, 2024
    *   Declarations of the functions for 2 wheel drive (2WD) robot motor controls
    *   Pasan_RK95
*/

#include <stdio.h>
#include "robot_2wd.h"  // Include your new header!
#include "hardware/uart.h"
#include "hardware/pwm.h"

int64_t alarm_callback(alarm_id_t id, void *user_data) {
    // Stop the motors
    pwm_set_gpio_level(LEFT_L_PWM, 0);
    pwm_set_gpio_level(LEFT_R_PWM, 0);
    pwm_set_gpio_level(RIGHT_L_PWM, 0);
    pwm_set_gpio_level(RIGHT_R_PWM, 0);
    return 0; // Return 0 to indicate that the alarm should not repeat
}

// set up motor pins for PWM
void setup_motor_pins(uint gpio_pin) {
    gpio_set_function(gpio_pin, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(gpio_pin);

    // set to 10kHz PWM frequency
    pwm_set_clkdiv(slice_num, 12.5f);
    pwm_set_wrap(slice_num, MAX_SPEED);

    // start with 0 speed
    pwm_set_chan_level(slice_num, pwm_gpio_to_channel(gpio_pin), 0);

    // turn on the PWM output
    pwm_set_enabled(slice_num, true);
}

// Initialize all robot pins
void init_robot() {
    setup_motor_pins(LEFT_L_PWM);
    setup_motor_pins(LEFT_R_PWM);
    setup_motor_pins(RIGHT_L_PWM);
    setup_motor_pins(RIGHT_R_PWM);
}

// Left Motor control function
void left_motor(int speed) {
    if (speed > 0) {
        pwm_set_gpio_level(LEFT_L_PWM, speed);
        pwm_set_gpio_level(LEFT_R_PWM, 0);  
    } else if (speed < 0) {
        pwm_set_gpio_level(LEFT_L_PWM, 0);
        pwm_set_gpio_level(LEFT_R_PWM, -speed);
    } else {
        pwm_set_gpio_level(LEFT_L_PWM, 0);
        pwm_set_gpio_level(LEFT_R_PWM, 0);
    }
}

// Right Motor control function
void right_motor(int speed) {
    if (speed > 0) {
        pwm_set_gpio_level(RIGHT_L_PWM, speed);
        pwm_set_gpio_level(RIGHT_R_PWM, 0);
    } else if (speed < 0) {
        pwm_set_gpio_level(RIGHT_L_PWM, 0);
        pwm_set_gpio_level(RIGHT_R_PWM, -speed);
    } else {
        pwm_set_gpio_level(RIGHT_L_PWM, 0);
        pwm_set_gpio_level(RIGHT_R_PWM, 0);
    }
}   

// Main Robot movement function
void move_proportionally(int left_speed, int right_speed) {
    left_motor(left_speed);
    right_motor(right_speed);
}

// Simple robot movement functions
void move_forward(int speed) {
    printf("Moving Forward at speed: %d\n", speed);
    move_proportionally(speed, speed);
}

void move_backward(int speed) {
    printf("Moving Backward at speed: %d\n", speed);
    move_proportionally(-speed, -speed);
}

void turn_left(int speed) {
    printf("Turning Left at speed: %d\n", speed);
    move_proportionally(-speed, speed);
}

void turn_right(int speed) {
    printf("Turning Right at speed: %d\n", speed);
    move_proportionally(speed, -speed);
}

void stop_motors() {
    printf("Stopping Motors\n");
    move_proportionally(0, 0);
}

// Demo function to test robot movements
void demo_movements(int speed) {
    move_forward(speed);
    sleep_ms(2000);
    stop_motors();
    sleep_ms(1000);
    turn_left(speed);
    sleep_ms(2000);
    stop_motors();
    sleep_ms(1000);
    move_backward(speed);
    sleep_ms(2000);
    stop_motors();
    sleep_ms(1000);
    turn_right(speed);
    sleep_ms(2000);
    stop_motors();
}