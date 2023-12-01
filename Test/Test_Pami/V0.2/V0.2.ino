#include <AccelStepper.h>
#include <BluetoothSerial.h>

const int dirPin1 = 2;
const int stepPin1 = 3;
const int dirPin2 = 4;
const int stepPin2 = 5;

#define motorInterfaceType 1

AccelStepper stepper1(motorInterfaceType, stepPin1, dirPin1);
AccelStepper stepper2(motorInterfaceType, stepPin2, dirPin2);

BluetoothSerial SerialBT;

TaskHandle_t MotorControlTask;

enum RobotState {
  IDLE,
  MOVE_FORWARD,
  TURN_90_DEG,
  MOVE_FORWARD2, 
};

// Variable to track the current state
RobotState currentState = IDLE;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("PAMI"); // Bluetooth device name
  
  
  stepper1.setMaxSpeed(1000);
  stepper1.setAcceleration(50);
  stepper1.setSpeed(500);

  stepper2.setMaxSpeed(1000);
  stepper2.setAcceleration(50);
  stepper2.setSpeed(500);

}

xTaskCreatePinnedToCore(
      MotorControlTaskFunction, /* Function to implement the task */
      "MotorControlTask",       /* Name of the task */
      10000,                    /* Stack size in words */
      NULL,                     /* Task input parameter */
      1,                        /* Priority of the task */
      &MotorControlTask,        /* Task handle. */
      0);                       /* Core where the task should run */

void loop() {
  // Your loop can handle other tasks if needed, but it can remain empty
}

void MotorControlTaskFunction(void *parameter) {
  while (1) {
    switch (currentState) {
      case IDLE:
        break;
      case MOVE_FORWARD:
        moveOneMeter();
        currentState = TURN_90_DEG;
        break;
      case TURN_90_DEG:
        turn90();
        currentState = MOVE_FORWARD2;
        break;
      case MOVE_FORWARD2:
        moveOneMeter();
        currentState = IDLE;  // After moving another meter, go back to IDLE
        break;
    }
    stepper1.run();
    stepper2.run();

    vTaskDelay(1); // Adjust the delay as needed
  }
}

void moveOneMeter() {
  const long stepsPerMeter = 2000; // Adjust this value based on your motor and leadscrew characteristics
  const long targetPosition = stepsPerMeter;

  stepper1.moveTo(targetPosition);
  stepper2.moveTo(targetPosition);

  // Wait until both motors reach their target positions
  while (stepper1.distanceToGo() != 0 || stepper2.distanceToGo() != 0) {
    stepper1.run();
    stepper2.run();
    vTaskDelay(1); // Adjust the delay as needed
  }
}

void turn90() {
  const float degreesToSteps = 200; // Adjust this value based on your motor and leadscrew characteristics
  const long targetPosition = degreesToSteps * 90;

  stepper1.moveTo(targetPosition);
  stepper2.moveTo(-targetPosition);

  // Wait until both motors reach their target positions
  while (stepper1.distanceToGo() != 0 || stepper2.distanceToGo() != 0) {
    stepper1.run();
    stepper2.run();
    vTaskDelay(1); // Adjust the delay as needed
  }
}
