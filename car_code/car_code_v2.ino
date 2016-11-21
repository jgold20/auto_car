/*
   Author: Joshua Gold
   Date: November 2nd 2016
   Description
   This test sketch is used to control the car to do basic functions
   including driving and obstacle detection
*/

// Includes for sketch
#include <Servo.h>
#include "Ultrasonic.h"
#include <Wire.h>


// Init Servos
Servo car_servo;

// Car Vars
const int pwm = 2; // car speed
const int dir = 3; // direction



// distance for sonar
int rear_sensor, front_sensor, left_sensor, right_sensor;

// Checking Left and right distances
int checkRight; // Right Side
int checkLeft; // Left Side


// Init sonar
//Ultrasonic front(12,13);
//Ultrasonic rear(12,13);
//Ultrasonic left(12,13);
//Ultrasonic right(12,13);


// Code for car setup
void setup() {
  // Start serial output
  Serial.begin(9600);
  // Attach Servo
  car_servo.attach(9);
  // Var for car directio (Backwards and forwards)
  pinMode(dir, OUTPUT);
}

// Main loop
void loop() {
   // Start car auto program
   
}


// Driving functions of the car

// Drives car forward (int speed)
void drive_forward(int speed) {
  // set dir to forward
  digitalWrite(dir, LOW);
  // Set DC motor to specified speed
  analogWrite(pwm, speed);
}


// Drive car backward
void drive_backwards(int speed) {
  // Set dir to backward
  digitalWrite(dir, HIGH);
  // Set pwm to specified speed
  analogWrite(pwm, speed);
}


// Stops hand_break()
void hand_break(void) {
  // stops car quick
  analogWrite(pwm, 0);
}


// Turns car to given pos
void turn_car(int pos) {
  // write to servo
  car_servo.write(pos);
}

// Car light control

// Turn on an led 
void turn_led_on(int led) {
  // Set LED to on
  digitalWrite(led, HIGH); // turn LED on
}


// Turn off an led 
void turn_led_off(int led) {
  // Set LED to on
  digitalWrite(led, LOW); // Turn LED off
}

// 







