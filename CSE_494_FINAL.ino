

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

int last_x = 0;
int last_y = 0;

unsigned int width = 0;         //object's width
unsigned int height = 0;        //object's height
unsigned int area = 0;
unsigned int newarea = 0;
unsigned int last_h = 0;
unsigned int last_w = 0;  
int Xmin = 70;                  //min x position
int Xmax = 200;                 //max x position
int maxArea = 4200;
int minArea = 840;


// Car control
int pwm = 5;
int dir = 7;

// Setup Robot
void setup()
{
  //Serial.begin(9600);
  pinMode(dir, OUTPUT);
  car_servo.attach(10); // Steering servo
  Stop();
  pixy.init(); // init the camera
  
} // end setup


// Loop code
void loop()
{

  static int i;
  
  uint16_t blocks;
  blocks = pixy.getBlocks();  //receive data from pixy
  signature = pixy.blocks[i].signature;    //get object's signature
  x = pixy.blocks[i].x;                    //get x position
  y = pixy.blocks[i].y;                    //get y position
  width = pixy.blocks[i].width;            //get width
  height = pixy.blocks[i].height;          //get height
  
  // Check for correct sig
  if (signature == 2) // Rover is looking for object with signaure 2
  {
    area = width * height; //calculate the object area 
    
    if (x < Xmin)//turn left if x position < max x position
    {
      left();
    }
    else if (x > Xmax) //turn right if x position > max x position
    {
      right();
    }
    else if (area < minArea) //go forward if object too small
    {
      forward();
    }
    else if (area > maxArea) //go backward if object too big
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
}

// move car forwards
void forward()//forward
{
  digitalWrite(dir, LOW);
  car_servo.write(90);
  analogWrite(pwm, 12);
}

void right()//turn right
{
  car_servo.write(155);
}

void left(void)//turn left
{
  car_servo.write(25);
}

void Stop()//stop
{
  car_servo.write(90);
  analogWrite(pwm, 0);
}

/*
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
//  pixy.blocks[i].print();
}*/
