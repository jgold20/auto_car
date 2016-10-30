#include <SPI.h>
#include <SD.h>
#include <Ultrasonic.h>
#include <Servo.h>

// SD CARD FOR DATA LOG
const int chipSelect = 4;

// Servo to steer the car
Servo car_servo;

// Control Ints
int servo_pin;
// End steering servo


// Sonar pins declaration
// Front Sensor
const int front_trig = 23;
const int front_echo = 25;

/*
// Blind left
 const int bl_trig = 24;
 const int bl_echo = 25;

// Blind right
const int br_trig = 26;
const int br_echo = 27;

// Rear sensor
const int back_trig = 28;
const int back_echo = 29;
*/
// Init Sensor Objects
Ultrasonic front(front_trig,front_echo);
//Ultrasonic blind_left(bl_trig,bl_echo);
//Ultrasonic blind_right(br_trig,br_echo);
//Ultrasonic back(back_trig,back_echo);

// Sonar Values (needed for distance calcs)
float cmdistance,indistance;
long microsec;
int SAFE_DISTANCE = 18;
// End sonar sensor setup


// Alerts buzzers set up
const int alert_buzzer = 8;

// Setup section
void setup() {
  // Set alert buzzer
  pinMode (alert_buzzer, OUTPUT);
  Serial.begin(9600);

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  Serial.println("card initialized.");
}

// Main program loop
void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Ready to test");
  sensor_read(front);
  delay(250);
}

// Read from distance sensor
float sensor_read(Ultrasonic sensor) {
  microsec = sensor.timing();
  cmdistance = sensor.CalcDistance(microsec,Ultrasonic::CM);//this result unit is centimeter
  indistance = sensor.CalcDistance(microsec,Ultrasonic::IN);//this result unit is inches

  Serial.print("cm: ");
  Serial.println(cmdistance);
  Serial.print("inches: ");
  Serial.println(indistance);
  
  
  // Testing for inches
  if(indistance < SAFE_DISTANCE) {
    Serial.println("Too close!"); // DEBUG
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



