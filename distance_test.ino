/*
 *UltrasonicDemo.pde - Ultrasonic sensor Ranging measure Demo
 *@Author:dragon
 *@DATA:2013-8-7
 *Company website:www.elecfreaks.com
 */
#include <Ultrasonic.h>
#include <Servo.h>


//-------------------------
// Sonar Sensor Setup
// Front sensor
#define front_trig 22
#define front_echo 23

// Blind left
#define bl_trig 24
#define bl_echo 25

// Blind right
#define br_trig 26
#define br_echo 27

// Rear sensor
#define back_trig 28
#define back_echo 29

// Init ultrasonic sensors
Ultrasonic front(front_trig,front_echo);
Ultrasonic blind_left(bl_trig,bl_echo);
Ultrasonic blind_right(br_trig,br_echo);
Ultrasonic back(back_trig,back_echo);

// Dist values for finding ultra sonic range
float cmdistance,indistance;
long microsec;
//-------------------------

// Buzzer setup
#define speakerPin 8

// distance min for check
// Distance in inches
const int SAFE_DISTANCE = 4;



// LEDS
//const int green_led = 13;
//onst int red_led = 12;

// Values for distance readings on each sonar
float s1, s2, s3, s4;

// Init servo
Servo myservo;


// Setup loop
void setup()
{
  s1, s2, s3, s4 = 0;
  pinMode (speakerPin, OUTPUT);
  //set Serial Baud rate
	Serial.begin(9600);

}

void loop()
{
  s1 = sensor_read(front);
  delay(50);
  s2 = sensor_read(blind_left);
  delay(50);
  s3 = sensor_read(blind_right);
  delay(50);
  s4 = sensor_read(back);
  delay(50);
  Serial.print("Front: ");
  Serial.println(s1);
  delay(500);
  Serial.print("Back: ");
  Serial.println(s4);
  delay(500);
  Serial.print("Left Blind: ");
  Serial.println(s1);
  delay(500);
  Serial.print("Right Blind: ");
  Serial.println(s3);
  delay(500);
  Serial.println("----------------");
}


float sensor_read(Ultrasonic sensor) {
  // Sensor one
  microsec = sensor.timing();
  indistance = sensor.CalcDistance(microsec,Ultrasonic::IN);//this result unit is inches
  if(indistance < SAFE_DISTANCE) {
    buzzer_alert();
  }
  return(indistance);
}


// Signal buzzer
void buzzer_alert(void) {
  digitalWrite(speakerPin, HIGH);
  delay(420);
  digitalWrite(speakerPin, LOW);
}


