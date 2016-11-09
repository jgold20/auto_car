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

LiquidCrystal_I2C lcd(0x3f,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

// Create Servo object
Servo car_servo;

// Distance sensors
// Front Sensor
const int front_trig = 28;
const int front_echo = 29;

// Rear Sensor
const int rear_trig = 25;
const int rear_echo = 24;


// Needs wiring
// Right blind spot 
//const int right_trig = 37;
//const int right_echo = 36;

// Left blind spot
//const int left_trig = 28;
//const int left_echo = 29;


// Create Ultrasonic sensor objects
Ultrasonic front(front_trig,front_echo);
Ultrasonic rear(rear_trig,rear_echo);
//Ultrasonic left(left_trig,left_echo);
//Ultrasonic right(right_trig,right_echo);


// For sonar measurements
float cmdistance,indistance;
long microsec;

// Sensor values 
// s1 = front, s2 = rear, s3 = left, s4= right
float s1,s2,s3,s4;
// Car LEDS 
/*
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
*/

// Car control vars
const int dir = 3; // direction of motor
const int pwm = 2; // power and speed of rear DC motor


// alerts
//const int left_buzzer = 27;
//const int right_buzzer = 26;

// Setup code
void setup() {
 
  Serial.begin(9600);//set Serial Baud rate
 // pinMode(left_buzzer, OUTPUT);
//  pinMode(right_buzzer, OUTPUT);
  pinMode(dir, OUTPUT);
  s1 = 0;
  s2 = 0;
  s3 = 0;
  s4 = 0;
  car_servo.attach(9);
  delay(2000);
}


// Main driver loop
void loop() {
  // Get distance in front
  s1 = sensor_read(front);
  forward();
  analogWrite(pwm, 10);
  
  // if sensor front is too close to object
  if(sensor_read(front) < 15) 
  {
    // Stop
    analogWrite(pwm, 0);
    delay(1000000000);
  }
 

  s1 = sensor_read(front);
  s2 = sensor_read(rear);

  

 
 Serial.println(s1);
 Serial.println(s2);
  
 
  delay(200);
  
}


// Driving Functions

// Drive car forward
void forward(void) {
  digitalWrite(dir, LOW);
}

// Drive car backward
void backward() {
  digitalWrite(dir, HIGH);
}

// Turn left
void turn_left() {
  car_servo.write(15);
}

// Turn right
void turn_right() {
  car_servo.write(165);
}

void straighten() {
  car_servo.write(90);
}

void hand_brake() {
  analogWrite(pwm, 0);
}

void brake() {
  analogWrite(pwm, 0);
}

// End Driving functions
//-------------------------------------------------------------------

// Car Lights
/*
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
*/

// Saftey Systems

// Sonar sensor read
// Read from distance sensor
float sensor_read(Ultrasonic sensor) {
  microsec = sensor.timing();
  cmdistance = sensor.CalcDistance(microsec,Ultrasonic::CM);//this result unit is centimeter
  indistance = sensor.CalcDistance(microsec,Ultrasonic::IN);//this result unit is inches
 
  return(indistance);
}



String closet_object(float front, float rear, float left, float right) {
  Serial.println("Closet obj func called");
  if(front < rear && front < left && front < right) {
    Serial.println("front");
    return "front";
  }
  
  if(rear < front && rear < left && rear < left) {
    Serial.println("2");
    return "rear";
  }

  if(left < rear && left < front && left < right) {
    Serial.println("3");
    return "left";
  }

  if(right < left && right < front && right < rear) {
    Serial.println("4");
    return "right";
  }
}
