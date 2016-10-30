#include <Ultrasonic.h>
#include <Servo.h>

// Servo to steer the car
Servo car_servo;

// Control Ints
int pos;
int servo_pin;
// End steering servo

// Sonar pins declaration
// Front Sensor
const int front_trig = 22;
const int front_echo = 23;

// Blind left
 const int bl_trig = 24;
 const int bl_echo = 25;

// Blind right
const int br_trig = 26;
const int br_echo = 27;

// Rear sensor
const int back_trig = 28;
const int back_echo = 29;

// Init Sensor Objects
Ultrasonic front(front_trig,front_echo);
Ultrasonic blind_left(bl_trig,bl_echo);
Ultrasonic blind_right(br_trig,br_echo);
Ultrasonic back(back_trig,back_echo);

// Sonar Values (needed for distance calcs)
float cmdistance,indistance;
long microsec;
int SAFE_DISTANCE = 12;
// End sonar sensor setup

// Alerts buzzers set up
const int alert_buzzer;

// Setup section
void setup() {
  // Set alert buzzer
  pinMode (alert_buzzer, OUTPUT);
  Serial.begin(9600);
}

// Main program loop
void loop() {
  // put your main code here, to run repeatedly:
  
}

float sensor_read(Ultrasonic sensor) {
  microsec = sensor.timing();
  cmdistance = sensor.CalcDistance(microsec,Ultrasonic::CM);//this result unit is centimeter
  indistance = sensor.CalcDistance(microsec,Ultrasonic::IN);//this result unit is inches

  // Testing for inches
  if(indistance < SAFE_DISTANCE) {
    buzzer_alert();
  }
  return(indistance);
}

// Signal buzzer
void buzzer_alert(void) {
  digitalWrite(alert_buzzer, HIGH);
  delay(200);
  digitalWrite(alert_buzzer, LOW);
}


