#include <AccelStepper.h>
#include <math.h>
#define XY_Cordinates 2

#define TaskPriority_is_HIGH 0
#define X 0
#define Y 1
#define Core1 0
#define NULL_INPUT_PARAMETER NULL
#define STACK_SIZE_BYTES 10000

#define RIGHT_SENSOR_PIN 18
#define MID_SENSOR_PIN 5
#define LEFT_SENSOR_PIN 19

#define RIGHTSENSOR 0
#define MIDSENSOR 1
#define LEFTSENSOR 2


#define MOTOR_INTERFACE_TYPE 1
#define Right_DIR_PIN 14
#define Right_STEP_PIN 12
#define Wheel_Diametre 79
#define Wheel_Perimeter M_PI * Wheel_Diametre   //=245 mm
#define Left_DIR_PIN 26
#define Left_STEP_PIN 32
#define Pami_Track  133 //135
#define STEPS_PER_REVOLUTION 200 // 200->one rotate
bool Obstacle_FLAG_BOOL=true;
 bool Controlled_FLAG=true,Prev_Obstacle_FLAG_BOOL=true ;
TaskHandle_t ObjectDetect;
AccelStepper RightStepper(MOTOR_INTERFACE_TYPE, Right_STEP_PIN, Right_DIR_PIN);
AccelStepper LeftStepper(MOTOR_INTERFACE_TYPE, Left_STEP_PIN, Left_DIR_PIN);
uint8_t Coordinates_Rank=2;//to be changed 
 // do not touch this by any means 

 uint8_t  Obstacle_FLAG[3]= {1,1,1};
void setup() {
    Coordinates_Rank=3;
 
 
  xTaskCreatePinnedToCore(ObjectDetection ,"ObjectDetect", STACK_SIZE_BYTES, NULL_INPUT_PARAMETER, TaskPriority_is_HIGH, &ObjectDetect, Core1);  //&ObjectDetect,        Task handle
  float **PamiTargetXY_PathPlanner = new float*[Coordinates_Rank];
  float **PamiTargetXY = new float*[Coordinates_Rank];
  float *Radius= new float[Coordinates_Rank];
  float *Theta= new float[Coordinates_Rank];
  
  for (int i = 0; i < Coordinates_Rank; i++)
  {
  PamiTargetXY_PathPlanner[i] = new float[XY_Cordinates];
  PamiTargetXY[i] = new float[XY_Cordinates];
  }
  Serial.begin(9600);
Motors_Setup();


  PamiTargetXY_PathPlanner[0][X]=1275.0;
  PamiTargetXY_PathPlanner[0][Y]=75.0;

   PamiTargetXY_PathPlanner[1][X]=1275.0;
  PamiTargetXY_PathPlanner[1][Y]=1200;

     PamiTargetXY_PathPlanner[2][X]=516.0;
  PamiTargetXY_PathPlanner[2][Y]=1416;

  //   PamiTargetXY_PathPlanner[3][X]=224.0;
  //PamiTargetXY_PathPlanner[3][Y]=1772;
  
  Theta[0]=M_PI/2;
 delay(3500);
  
  
 ExecuteXY(PamiTargetXY,PamiTargetXY_PathPlanner,Radius,Theta);

}



void loop() {

}


int Convert_distance_mm_2_steps(float distance) {
  return ((int)(distance * STEPS_PER_REVOLUTION) / (Wheel_Perimeter));
}

float Convert_angle_rad_2_Arc(float angle) {
  return (angle * Pami_Track * 0.5);
}



void CoordinatesTreatment(float **PamiTargetXY,float **PamiTargetXY_PathPlanner)
{ PamiTargetXY[0][0]=PamiTargetXY_PathPlanner[0][0];
PamiTargetXY[0][1]=PamiTargetXY_PathPlanner[0][1];
  for(int i=1;i<Coordinates_Rank;i++)
  { PamiTargetXY[i][0]=PamiTargetXY_PathPlanner[i][0]-PamiTargetXY_PathPlanner[i-1][0];
  PamiTargetXY[i][1]=PamiTargetXY_PathPlanner[i][1]-PamiTargetXY_PathPlanner[i-1][1];
  } 
}


void ExecuteXY(float **PamiTargetXY,float **PamiTargetXY_PathPlanner, float *Radius, float* Theta) {
CoordinatesTreatment(PamiTargetXY,PamiTargetXY_PathPlanner);
 Cartesian_To_Polar_Coordinates(PamiTargetXY,Radius,Theta);
  int i=0;
  for (i = 1; i < Coordinates_Rank; i++)
    {
      PamiRotating_rad(Theta[i]);
      PamiMoving_MM(Radius[i]);
      delay(1000);
      /* Serial.print("Point Reached: ");
       Serial.println(Radius[i]);
       Serial.print("angle=  ");
       Serial.println(Theta[i]*180*(1/M_PI));
       Serial.print("x=  ");
       Serial.println(PamiTargetXY[i][0]);
       Serial.print("y=   ");
       Serial.println(PamiTargetXY[i][1]);
       Serial.print("*******************************************************: ");*/
    }
   
}

void PamiMoving_Steps(int StepsDesired) {
  RightStepper.move(-StepsDesired);
  LeftStepper.move(StepsDesired);

  while ((LeftStepper.isRunning() || RightStepper.isRunning())&& Controlled_FLAG )  {
    LeftStepper.run();
    RightStepper.run();
  }
}

void PamiRotating(float StepsDesired) {
  RightStepper.move(-StepsDesired);
  LeftStepper.move(-StepsDesired);
  while ((LeftStepper.isRunning() || RightStepper.isRunning())&& Controlled_FLAG )  {
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

void Cartesian_To_Polar_Coordinates(float** PamiTargetXY, float *Radius, float* Theta) {
  for (int i = 1; i <Coordinates_Rank; i++) {
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

void ObjectDetection(void *pvParameters) {
   pinMode(RIGHT_SENSOR_PIN,INPUT);
   pinMode(LEFT_SENSOR_PIN,INPUT);
   pinMode(MID_SENSOR_PIN,INPUT);
  
  while (1) {
  Obstacle_FLAG[RIGHTSENSOR] = digitalRead(RIGHT_SENSOR_PIN);
  Obstacle_FLAG[LEFTSENSOR] = digitalRead(LEFT_SENSOR_PIN);
  Obstacle_FLAG[MIDSENSOR] = digitalRead(MID_SENSOR_PIN);
  Obstacle_FLAG_BOOL= Obstacle_FLAG[RIGHTSENSOR]& Obstacle_FLAG[LEFTSENSOR]  &Obstacle_FLAG[MIDSENSOR];
   Serial.print("Obstacle_FLAG_BOOL= ");
 Serial.println(Obstacle_FLAG_BOOL);
 Controlled_FLAG=Obstacle_FLAG_BOOL|Prev_Obstacle_FLAG_BOOL;
Prev_Obstacle_FLAG_BOOL=Obstacle_FLAG_BOOL;
      
    vTaskDelay(2000 / portTICK_PERIOD_MS); // Delay for 2 seconds
  }
}