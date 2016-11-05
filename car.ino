/*
 * Author: Joshua Gold
 * Date: November 2nd 2016  
 * Description
 * This test sketch is used to control the car to do basic functions
 * including driving and obstacle detection
 */

#include <Servo.h>
#include <Ultrasonic.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// Global Vars
#define speakerPin 8
#define SAFE_DISTANCE 16
// Create Servo object
Servo car_servo;

// Distance sensors
// Front Sensor
const int front_trig = 31;
const int front_echo = 30;

// Rear Sensor
const int rear_trig = 53;
const int rear_echo = 52;

// Right blind spot 
const int right_trig = 41;
const int right_echo = 44;

// Left blind spot
const int left_trig = 49;
const int left_echo = 48;

// Create Ultrasonic sensor objects
Ultrasonic front(front_trig,front_echo);
Ultrasonic left(left_trig,left_echo);
Ultrasonic right(right_trig,right_echo);
Ultrasonic rear(rear_trig,rear_echo);

// For sonar measurements
float cmdistance,indistance;
long microsec;

// Sensor values 
// s1 = front, s2 = rear, s3 = left, s4= right
float s1,s2,s3,s4;
// Car LEDS
const int head_light_left;
const int head_light_right;
const int rear_light_left;
const int rear_light_right;
const int front_turn_signal_left;
const int front_turn_signal_right;
const int rear_turn_signal_left;
const int rear_turn_signal_right;
const int reverse_left;
const int reverse_right;
const int brake_left;
const int brake_right;


// Car control vars
int dir; // direction of motor
int pwm; // power and speed of rear DC motor

LiquidCrystal_I2C lcd(0x3f,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display


void setup() {
  // put your setup code here, to run once:
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Ready...");
  Serial.begin(9600);//set Serial Baud rate
  pinMode(speakerPin, OUTPUT);
  s1 = 0;
  s2 = 0;
  s3 = 0;
  s4 = 0;
}

void loop() {
  // put your main code here, to run repeatedly:
  // Front
  Serial.println("Front:");
  s1 = sensor_read(front);
  delay(100);
  Serial.println("Rear:");
  s2 = sensor_read(rear);
  delay(100);
  Serial.println("Left:");
  s3 = sensor_read(left);
  delay(100);
  Serial.println("Right:");
  s4 = sensor_read(right);
 delay(100);
 lcd.clear();
 lcd.setCursor(0,0); 
 lcd.print("F: ");
 lcd.setCursor(2,0);
 lcd.print(s1);
 lcd.setCursor(0,1);
lcd.print("R: ");
lcd.setCursor(2,1);
  lcd.print(s2);
  /*
 // Blind spot obstruction
 if(s4 < 20 || s3 < 20) {
  // Alert buzzer
  buzzer_alert();
 }
  if(s1 < SAFE_DISTANCE) {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Front sensor");
  } else if(s2 < SAFE_DISTANCE) {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Rear sensor");
  } else if(s3 < SAFE_DISTANCE) {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Left sensor");
  } else if(s4 < SAFE_DISTANCE) {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Right sensor");
  } else {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("All clear");
  }*/
  Serial.println("--------------");
  delay(710);
  
}




// Driving Functions

// Drive car forward
void forward() {
  
}

// Drive car backward
void backward() {
  
}

// Turn left
void turn_left() {
  
}

// Turn right
void turn_right() {
  
}

void hand_brake() {
  
}

void brake() {
  
}

// End Driving functions
//-------------------------------------------------------------------

// Car Lights

void headlights(bool on) {
  if(on){
    // Turn on signal lights 
  } else {
    // Turn off signal lights
  }
}

void high_beams(bool on) {
  if(on){
    // Turn on signal lights 
  } else {
    // Turn off signal lights
  }
}

// 
void left_turn_signal(bool on) {
  if(on){
    // Turn on signal lights 
  } else {
    // Turn off signal lights
  }
}

void right_turn_signal(bool on) {
  if(on){
    // Turn on signal lights 
  } else {
    // Turn off signal lights
  }
}

void brake_lights(bool on) {
  if(on){
    // Turn on signal lights 
  } else {
    // Turn off signal lights
  }
}

void reverse_lights(bool on) {
  if(on){
    // Turn on signal lights 
  } else {
    // Turn off signal lights
  }
}

void hazzard_lights(bool on) {
  if(on){
    // Turn on signal lights 
  } else {
    // Turn off signal lights
  }
}

// end lights

// Saftey Systems

// Sonar sensor read
// Read from distance sensor
float sensor_read(Ultrasonic sensor) {
  microsec = sensor.timing();
  cmdistance = sensor.CalcDistance(microsec,Ultrasonic::CM);//this result unit is centimeter
  indistance = sensor.CalcDistance(microsec,Ultrasonic::IN);//this result unit is inches
  
  Serial.print("cm: ");
  Serial.println(cmdistance);
  Serial.print("inches: ");
  Serial.println(indistance);
  
  
  return(indistance);
}

// Signal buzzer
void buzzer_alert(void) {
  digitalWrite(speakerPin, HIGH);
  delay(100 );
  digitalWrite(speakerPin, LOW);
}

