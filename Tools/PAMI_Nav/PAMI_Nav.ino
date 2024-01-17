#include <AccelStepper.h>
#include <math.h>

#define MOTOR_INTERFACE_TYPE 1
#define Right_DIR_PIN 12
#define Right_STEP_PIN 10
#define Wheel_Radius 3
#define Wheel_Perimeter M_PI * 2 * Wheel_Radius //= 18.84 cm=188.4 mm
#define Left_DIR_PIN 4
#define Left_STEP_PIN 3
#define Pami_Track  10


#define STEPS_PER_REVOLUTION 200 // 200->one rotate

AccelStepper RightStepper(MOTOR_INTERFACE_TYPE, Right_STEP_PIN, Right_DIR_PIN);
AccelStepper LeftStepper(MOTOR_INTERFACE_TYPE, Left_STEP_PIN, Left_DIR_PIN);
float PamiTargetXY[5][2];

float Radius,Theta;

void setup() {
Motors_Setup();

RightStepper.setCurrentPosition(0);      //test -> runToPosition();           Moves the motor to the target position and blocks until it is at position. Dont use this in event loops, since it blocks.
LeftStepper.setCurrentPosition(0);

Cartesian_To_Polar_Coordinates(PamiTargetXY, &Radius, &Theta);
PamiMoving( Convert_distance_mm_2_steps(Radius) );
}

void loop() {
  
}



int Convert_distance_mm_2_steps(float distance) {return((int)(distance*STEPS_PER_REVOLUTION)/Wheel_Perimeter) ;}

float Convert_angle_deg_2_Arc(float angle) {return(angle*Pami_Track*0.5);}


void PamiMoving(int StepsDesired) 
{
  if(*StepsDesired>0)
  {
    RightStepper.move(-StepsDesired);
    LeftStepper.move(StepsDesired);
    while (LeftStepper.isRunning() || RightStepper.isRunning())
  
     {
       LeftStepper.run();
       RightStepper.run();
    }
  }
  else
  {
    RightStepper.move(StepsDesired);
    LeftStepper.move(-StepsDesired);
    while (LeftStepper.isRunning() || RightStepper.isRunning())
  
     {
       LeftStepper.run();
       RightStepper.run();
    }
  }
}



void PamiRotating(float StepsDesired){
  RightStepper.move(-StepsDesired);
    LeftStepper.move(-StepsDesired);
    while (LeftStepper.isRunning() || RightStepper.isRunning())
  
     {
       LeftStepper.run();
       RightStepper.run();
    }
}


void Cartesian_To_Polar_Coordinates(float PamiTargetXY[5][2], float *Radius, float *Theta) 
{
    // Extracting x and y coordinates from the array
    float x = PamiTargetXY[0][0];
    float y = PamiTargetXY[1][1];
    *Radius = sqrt(x * x + y * y);
    *Theta = atan2(y, x);
}




void Motors_Setup()
{
  pinMode(Right_DIR_PIN, OUTPUT);
  pinMode(Right_STEP_PIN, OUTPUT);
  pinMode(Left_DIR_PIN, OUTPUT);
  pinMode(Left_STEP_PIN, OUTPUT);

  // Set motor parameters
  LeftStepper.setMaxSpeed(1000);    // Set maximum speed in steps per second
  LeftStepper.setAcceleration(100); // Set acceleration in steps per second^2
  LeftStepper.setSpeed(500);

  RightStepper.setMaxSpeed(1000);    // Set maximum speed in steps per second
  RightStepper.setAcceleration(100); // Set acceleration in steps per second^2
  RightStepper.setSpeed(500);
 }


