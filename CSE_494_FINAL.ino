

#include <SPI.h>
#include <Pixy.h>
#include <Servo.h>
//#include <NewPing.h>

//#define MAX_DISTANCE 200 // Maximum distance (in cm) to ping

// Create instance of servo and pixy cam
Servo car_servo;
Pixy pixy;


// Pixy Vars
int signature = 0;
int x = 0;                      //positon x axis
int y = 0;                      //position y axis

unsigned int width = 0;         //object's width
unsigned int height = 0;        //object's height
unsigned int area = 0;
unsigned int newarea = 0;

int Xmin = 70;                  //min x position
int Xmax = 200;                 //max x position
int maxArea = 0;
int minArea = 0;

static int i = 0;


// Car control
int pwm = 5;
int dir = 7;

/*
// Sonar on front of car
const int front_echo = 8;
const int front_trig = 9;
int front_d = 0;

// New ping arduino lib
NewPing front_sonar(front_trig, front_echo , MAX_DISTANCE);
*/

// Setup Robot
void setup()
{
  Serial.begin(9600);
  pinMode(dir, OUTPUT);
  car_servo.attach(10); // Steering servo
  Stop();
  pixy.init(); // init the camera
  digitalWrite(dir, LOW);
} // end setup


// Loop code
void loop()
{
  while (millis() < 5000) 
  {
    scan();
    area = width * height; //calculate the object area
    maxArea = area + 1000;
    minArea = area - 1000;
  }

  // Scan for desired objects
  scan();

  if (signature == 2) // Rover is looking for object with signaure 2
  {
    newarea = width * height; //calculate the object area 

    if (x < Xmin)//turn left if x position < max x position
    {
      left();
    }
    else if (x > Xmax) //turn right if x position > max x position
    {
      right();
    }
    else if (newarea < minArea) //go forward if object too small
    {
      forward();
    }
    else if (newarea > maxArea) //go backward if object too big
    {
      backward();
    }

    //else stop
    else
    {
      Stop();
    }
  }
  else
  {
    // No wanted objects stop the car
    Stop();
  }
}


// Move car backwards
void backward()//backward
{
  digitalWrite(dir, HIGH);
  car_servo.write(90);
  analogWrite(pwm, 12);
  Serial.println("GOING BACK");
}

// move car forwards
void forward()//forward
{
  digitalWrite(dir, LOW);
  car_servo.write(90);
  analogWrite(pwm, 12);
  Serial.println("GOING Forward");
}

void right()//turn right
{
  car_servo.write(145);
  Serial.println("GOING right");
}

void left()//turn left
{
  car_servo.write(30);
  Serial.println("GOING left");
}

void Stop()//stop
{
  car_servo.write(90);
  analogWrite(pwm, 0);
  Serial.println("STOP");
}


// scan for object -- non turning
void scan()
{
  uint16_t blocks;
  blocks = pixy.getBlocks();  //receive data from pixy
  signature = pixy.blocks[i].signature;    //get object's signature
  x = pixy.blocks[i].x;                    //get x position
  y = pixy.blocks[i].y;                    //get y position
  width = pixy.blocks[i].width;            //get width
  height = pixy.blocks[i].height;          //get height
}
