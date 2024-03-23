#include <AccelStepper.h>
#include <math.h>


#define MOTOR_INTERFACE_TYPE 1
#define Right_DIR_PIN 14
#define Right_STEP_PIN 13
#define Wheel_Diametre 79
#define Wheel_Perimeter M_PI * Wheel_Diametre   //=245 mm
#define Left_DIR_PIN 4
#define Left_STEP_PIN 2
#define Pami_Track  133 //135
#define STEPS_PER_REVOLUTION 200 // 200->one rotate

AccelStepper RightStepper(MOTOR_INTERFACE_TYPE, Right_STEP_PIN, Right_DIR_PIN);
AccelStepper LeftStepper(MOTOR_INTERFACE_TYPE, Left_STEP_PIN, Left_DIR_PIN);
float PamiTargetXY_PathPlanner[5][2]={
  {0,1000},
  {0,500},
  {0,1000},
  {0,0},
  {0,0},
};

float Radius[5], Theta[5];

float PamiTargetXY [5][2];

void setup() {
  Theta[0]=M_PI/2;
  Serial.begin(9600);
  Motors_Setup();
  delay(3500);
  ExecuteXY();

}

void loop() {

}


int Convert_distance_mm_2_steps(float distance) {
  return ((int)(distance * STEPS_PER_REVOLUTION) / (Wheel_Perimeter));
}

float Convert_angle_rad_2_Arc(float angle) {
  return (angle * Pami_Track * 0.5);
}



void CoordinatesTreatment(float PamiTargetXY[5][2],float PamiTargetXY_PathPlanner[5][2])
{ PamiTargetXY[0][0]=PamiTargetXY_PathPlanner[0][0];
PamiTargetXY[0][1]=PamiTargetXY_PathPlanner[0][1];
  for(int i=1;i<5;i++)
  { PamiTargetXY[i][0]=PamiTargetXY_PathPlanner[i][0]-PamiTargetXY_PathPlanner[i-1][0];
  PamiTargetXY[i][1]=PamiTargetXY_PathPlanner[i][1]-PamiTargetXY_PathPlanner[i-1][1];
  } 
}


void ExecuteXY() {
CoordinatesTreatment(PamiTargetXY,PamiTargetXY_PathPlanner);
 Cartesian_To_Polar_Coordinates(PamiTargetXY,Radius,Theta);
  int i=0;
  for (i = 1; i < 5; i++)
    {
      PamiRotating_rad(Theta[i]);
      PamiMoving_MM(Radius[i]);
      delay(1000);
       Serial.print("Point Reached: ");
       Serial.println(Radius[i]);
       Serial.print("angle=  ");
       Serial.println(Theta[i]*180*(1/M_PI));
       Serial.print("x=  ");
       Serial.println(PamiTargetXY[i][0]);
       Serial.print("y=   ");
       Serial.println(PamiTargetXY[i][1]);
       Serial.print("*******************************************************: ");
    }
   
}

void PamiMoving_Steps(int StepsDesired) {
  RightStepper.move(-StepsDesired);
  LeftStepper.move(StepsDesired);
  while (LeftStepper.isRunning() || RightStepper.isRunning()) {
    LeftStepper.run();
    RightStepper.run();
  }
}

void PamiRotating(float StepsDesired) {
  RightStepper.move(-StepsDesired);
  LeftStepper.move(-StepsDesired);
  while (LeftStepper.isRunning() || RightStepper.isRunning()) {
    LeftStepper.run();
    RightStepper.run();
  }
}

void PamiMoving_MM(float distance) {
  PamiMoving_Steps(Convert_distance_mm_2_steps(distance));
}

void PamiRotating_rad(float angle) {
  PamiRotating(Convert_distance_mm_2_steps(Convert_angle_rad_2_Arc(angle)));
}

void Cartesian_To_Polar_Coordinates(float PamiTargetXY[5][2], float Radius[5], float Theta[5]) {
  for (int i = 0; i < 5; i++) {
    float x = PamiTargetXY[i][0];
    float y = PamiTargetXY[i][1];
    Radius[i] = sqrt(x * x + y * y);
    Theta[i] = atan2(y, x);
}
   for (int i = 1; i < 5; i++) {
        int j;
         for (j = 0; j < i; j++) {
            Theta[i] -= Theta[j];     
        }
    }
    for (int i = 1; i < 5; i++) {
        while (Theta[i]*180*(1/M_PI) < -180) {
            Theta[i] += 2*M_PI;
        }
        
        while (Theta[i]*180*(1/M_PI) > 180) {
            Theta[i] -= 2*M_PI;
        }


        }

}

void Motors_Setup() {
  pinMode(Right_DIR_PIN, OUTPUT);
  pinMode(Right_STEP_PIN, OUTPUT);
  pinMode(Left_DIR_PIN, OUTPUT);
  pinMode(Left_STEP_PIN, OUTPUT);

  LeftStepper.setMaxSpeed(1000);
  LeftStepper.setAcceleration(450);
  LeftStepper.setSpeed(600);

  RightStepper.setMaxSpeed(1000);
  RightStepper.setAcceleration(450);
  RightStepper.setSpeed(600);
}
