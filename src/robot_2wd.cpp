/*
 *   robot_2wd.cpp
 *   Created on: Jun 6, 2024
 *   Declarations of the functions for 2 wheel drive (2WD) robot motor controls
 *   Pasan_RK95
 */

#include <stdio.h>
#include "robot_2wd.h" // Include your new header!
#include "hardware/uart.h"
#include "hardware/pwm.h"

int64_t alarm_callback(alarm_id_t id, void *user_data)
{
    // Stop the motors
    left_motor(0);
    right_motor(0);
    return 0; // Return 0 to indicate that the alarm should not repeat
}

// Set up PWM pin for motor enable (speed control)
void setup_pwm_pin(uint gpio_pin)
{
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

// Set up direction control pins (digital GPIO)
void setup_direction_pin(uint gpio_pin)
{
    gpio_init(gpio_pin);
    gpio_set_dir(gpio_pin, GPIO_OUT);
    gpio_put(gpio_pin, 0); // Start with LOW
}

// Initialize all robot pins for L298N motor driver
void init_robot()
{
    // Setup PWM pins (speed control)
    setup_pwm_pin(LEFT_ENA);
    setup_pwm_pin(RIGHT_ENB);

    // Setup direction pins (digital control)
    setup_direction_pin(LEFT_IN1);
    setup_direction_pin(LEFT_IN2);
    setup_direction_pin(RIGHT_IN3);
    setup_direction_pin(RIGHT_IN4);
}

// Left Motor control function (L298N)
// speed: positive = forward, negative = backward, 0 = stop
void left_motor(int speed)
{
    // Ensure speed is within valid range [-255, 255]
    if (speed > MAX_SPEED)
        speed = MAX_SPEED;
    if (speed < -MAX_SPEED)
        speed = -MAX_SPEED;

    if (speed > 0)
    {
        // Forward: IN1=HIGH, IN2=LOW
        gpio_put(LEFT_IN1, 1);
        gpio_put(LEFT_IN2, 0);
        pwm_set_gpio_level(LEFT_ENA, speed);
    }
    else if (speed < 0)
    {
        // Backward: IN1=LOW, IN2=HIGH
        gpio_put(LEFT_IN1, 0);
        gpio_put(LEFT_IN2, 1);
        pwm_set_gpio_level(LEFT_ENA, -speed);
    }
    else
    {
        // Stop: both LOW
        gpio_put(LEFT_IN1, 0);
        gpio_put(LEFT_IN2, 0);
        pwm_set_gpio_level(LEFT_ENA, 0);
    }
}

// Right Motor control function (L298N)
// speed: positive = forward, negative = backward, 0 = stop
void right_motor(int speed)
{
    // Ensure speed is within valid range [-255, 255]
    if (speed > MAX_SPEED)
        speed = MAX_SPEED;
    if (speed < -MAX_SPEED)
        speed = -MAX_SPEED;

    if (speed > 0)
    {
        // Forward: IN3=HIGH, IN4=LOW
        gpio_put(RIGHT_IN3, 1);
        gpio_put(RIGHT_IN4, 0);
        pwm_set_gpio_level(RIGHT_ENB, speed);
    }
    else if (speed < 0)
    {
        // Backward: IN3=LOW, IN4=HIGH
        gpio_put(RIGHT_IN3, 0);
        gpio_put(RIGHT_IN4, 1);
        pwm_set_gpio_level(RIGHT_ENB, -speed);
    }
    else
    {
        // Stop: both LOW
        gpio_put(RIGHT_IN3, 0);
        gpio_put(RIGHT_IN4, 0);
        pwm_set_gpio_level(RIGHT_ENB, 0);
    }
}

// Main Robot movement function
void move_proportionally(int left_speed, int right_speed)
{
    left_motor(left_speed);
    right_motor(right_speed);
}

// Simple robot movement functions
void move_forward(int speed)
{
    printf("Moving Forward at speed: %d\n", speed);
    move_proportionally(speed, speed);
}

void move_backward(int speed)
{
    printf("Moving Backward at speed: %d\n", speed);
    move_proportionally(-speed, -speed);
}

void turn_left(int speed)
{
    printf("Turning Left at speed: %d\n", speed);
    move_proportionally(-speed, speed);
}

void turn_right(int speed)
{
    printf("Turning Right at speed: %d\n", speed);
    move_proportionally(speed, -speed);
}

void stop_motors()
{
    printf("Stopping Motors\n");
    move_proportionally(0, 0);
}

// Demo function to test robot movements
void demo_movements(int speed)
{
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