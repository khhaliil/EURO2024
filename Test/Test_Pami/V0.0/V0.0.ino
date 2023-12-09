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

void setup() {
  Serial.begin(115200);
  SerialBT.begin("PAMI"); 
  delay(1000);

  stepper1.setMaxSpeed(1000);
  stepper1.setAcceleration(50);
  stepper1.setSpeed(500);

  stepper2.setMaxSpeed(1000);
  stepper2.setAcceleration(50);
  stepper2.setSpeed(500);

  xTaskCreatePinnedToCore(
      MotorControlTaskFunction, /* Function to implement the task */
      "MotorControlTask",       /* Name of the task */
      10000,                    /* Stack size in words */
      NULL,                     /* Task input parameter */
      1,                        /* Priority of the task */
      &MotorControlTask,        /* Task handle. */
      0);                       /* Core where the task should run */
}

void loop() { 
}
void MotorControlTaskFunction(void *parameter) {
  while (1) {
    if (SerialBT.available()) {
      char command = SerialBT.read();

      
      if (command == 'G') {

        moveOneMeter();
      }
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
}
