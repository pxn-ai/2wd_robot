/*
 *   robot_2wd.h
 *   Pasan_RK95
 *   Created on: Jun 6, 2024
 *   Header file for 2 wheel drive (2WD) robot motor controls
 *   This file contains function prototypes and definitions for controlling a 2WD robot using the Raspberry Pi Pico.
 *   Pasan_RK95
 */

#ifndef ROBOT_2WD_H
#define ROBOT_2WD_H

#include "pico/stdlib.h"
#include "hardware/timer.h"

// --- UART Defines ---
#define UART_ID uart0
#define BAUD_RATE 115200
#define DATA_BITS 8
#define STOP_BITS 1
#define PARITY UART_PARITY_NONE

// --- Motor Pin Definitions (L298N Motor Driver) ---
// Left Motor
#define LEFT_ENA 20 // Enable A - PWM for left motor speed
#define LEFT_IN1 14 // Direction A - Left motor forward
#define LEFT_IN2 22 // Direction A - Left motor reverse

// Right Motor
#define RIGHT_ENB 21 // Enable B - PWM for right motor speed
#define RIGHT_IN3 15 // Direction B - Right motor forward
#define RIGHT_IN4 28 // Direction B - Right motor reverse

// --- Settings ---
#define MAX_SPEED 255

// --- Function Prototypes ---
// These tell the compiler that these functions exist,
// even though the actual code is in the .cpp file.
int64_t alarm_callback(alarm_id_t id, void *user_data);
void setup_motor_pins(uint gpio_pin);
void left_motor(int speed);
void right_motor(int speed);
void move_proportionally(int left_speed, int right_speed);
void move_forward(int speed);
void move_backward(int speed);
void turn_left(int speed);
void turn_right(int speed);
void stop_motors();
void demo_movements(int speed);

// Optional helper function to make main() cleaner
void init_robot();

#endif // ROBOT_2WD_H