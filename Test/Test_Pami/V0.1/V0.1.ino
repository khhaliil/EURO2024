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

void setup() {
  Serial.begin(115200);
  SerialBT.begin("PAMI"); 
  delay(1000);

  setupStepper(stepper1);
  setupStepper(stepper2);
}

void loop() {
  if (SerialBT.available()) {
    char command = SerialBT.read();
    
    if (command == 'G') {
      moveOneMeter(stepper1, stepper2);
      turn90(stepper1, stepper2);
      moveOneMeter(stepper1, stepper2);
    }
  }

  stepper1.run();
  stepper2.run();
  vTaskDelay(1); 
}

void setupStepper(AccelStepper &stepper) {
  stepper.setMaxSpeed(1000);
  stepper.setAcceleration(50);
  stepper.setSpeed(500);
}

void moveOneMeter(AccelStepper &stepper1, AccelStepper &stepper2) {
  const long stepsPerMeter = 2000;
  const long targetPosition = stepsPerMeter;

  stepper1.moveTo(targetPosition);
  stepper2.moveTo(targetPosition);

  while (stepper1.distanceToGo() || stepper2.distanceToGo()) {
    stepper1.run();
    stepper2.run();
    vTaskDelay(1); 
  }
}

void turn90(AccelStepper &stepper1, AccelStepper &stepper2) {
  const float degreesToSteps = 200;
  const long targetPosition = degreesToSteps * 90;

  stepper1.moveTo(targetPosition);
  stepper2.moveTo(-targetPosition);

  while (stepper1.distanceToGo() || stepper2.distanceToGo()) {
    stepper1.run();
    stepper2.run();
    vTaskDelay(1); 
}
