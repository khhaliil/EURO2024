#include <stdio.h>
#include <math.h>

#define MOTOR_INTERFACE_TYPE 1
#define Right_DIR_PIN 12
#define Right_STEP_PIN 10
#define Wheel_Radius 7.7
#define Wheel_Perimeter (M_PI * Wheel_Radius) // Corrected definition
#define Left_DIR_PIN 4
#define Left_STEP_PIN 3
#define Pami_Track 14.1
#define STEPS_PER_REVOLUTION 200 // 200->one rotate


int Convert_distance_mm_2_steps(float distance);
float Convert_angle_deg_2_Arc(float angle);
void ExecutePathXYPami(float PamiTargetXY[5][2],int CurrentTargetXYrank,int TargetsXYNumber );


int main() {
    float PamiTargetXY[5][2] = {
        {1, 1},
        {-1, -1.0},
        {0, 0},
        {0, 0},
        {0.0, 0.0}
    };

    float Radius[5];
    float Theta[5];
     int i=0;
    Cartesian_To_Polar_Coordinates(PamiTargetXY, Radius, Theta);

    printf("Radius:\n");
    for ( i= 0; i < 5; i++) {
        printf("%f\n", Radius[i]);
    }
    
    printf("Theta:\n");
    i=0;
    for (i = 0; i < 5; i++) {
        printf("%f\n", (Theta[i]*180)/3.14);
    }

    return 0;
}

int Convert_distance_mm_2_steps(float distance) {
    return ((int)(distance * STEPS_PER_REVOLUTION) / Wheel_Perimeter);
}

float Convert_angle_deg_2_Arc(float angle) {
    return (angle * Pami_Track * 0.5);
}

void Cartesian_To_Polar_Coordinates(float PamiTargetXY[5][2], float Radius[5], float Theta[5]) {
	int i=0;
    for (i = 0; i < 5; i++) {
        float x = PamiTargetXY[i][0];
        float y = PamiTargetXY[i][1];
        Radius[i] = sqrt(x * x + y * y);
        Theta[i] = atan2(y, x);
    }
}


void ExecutePathXYPami(float PamiTargetXY[5][2], int CurrentTargetXYrank, int TargetsXYNumber) {
 
    while (CurrentTargetXYrank > 0) {
        printf("moving to (%f,%f)\n", PamiTargetXY[TargetsXYNumber - CurrentTargetXYrank][0],PamiTargetXY[TargetsXYNumber - CurrentTargetXYrank][1]);
        CurrentTargetXYrank--;
    }
}



