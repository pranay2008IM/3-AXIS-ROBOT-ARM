#include <Servo.h>

// Define pins for the servos and joysticks
const int servoZPin = 9;        // Pin for Z-axis servo
const int servoYPin = 10;       // Pin for Y-axis servo
const int servoExtensionPin = 11; // Pin for extension servo

const int joystickZPin = A0;    // Joystick for Z-axis (X-axis)
const int joystickYPin = A1;    // Joystick for Y-axis (Y-axis)
const int joystickExtensionPin = A2; // Joystick for extension (X-axis)

// Create Servo objects
Servo servoZ;
Servo servoY;
Servo servoExtension;

// Variables to store the servo positions
int servoZPos = 90;         // Start at the middle position
int servoYPos = 90;
int servoExtensionPos = 90;

// Define a threshold for joystick's neutral position
const int centerThreshold = 20;

// Define the step size for precise movement
const int stepSize = 1;  // Move 1 degree at a time

void setup() {
  // Attach servos to their respective pins
  servoZ.attach(servoZPin);
  servoY.attach(servoYPin);
  servoExtension.attach(servoExtensionPin);

  // Initialize servo positions
  servoZ.write(servoZPos);
  servoY.write(servoYPos);
  servoExtension.write(servoExtensionPos);
}

void loop() {
  // Read joystick values
  int joystickZVal = analogRead(joystickZPin);
  int joystickYVal = analogRead(joystickYPin);
  int joystickExtensionVal = analogRead(joystickExtensionPin);

  // Calculate deviations from center
  int deviationZ = joystickZVal - 512;
  int deviationY = joystickYVal - 512;
  int deviationExtension = joystickExtensionVal - 512;

  // Control Z-axis servo
  if (abs(deviationZ) > centerThreshold) {
    if (deviationZ > 0 && servoZPos < 180) {
      servoZPos += stepSize;  // Move clockwise
    } else if (deviationZ < 0 && servoZPos > 0) {
      servoZPos -= stepSize;  // Move counterclockwise
    }
  }

  // Control Y-axis servo
  if (abs(deviationY) > centerThreshold) {
    if (deviationY > 0 && servoYPos < 180) {
      servoYPos += stepSize;  // Move clockwise
    } else if (deviationY < 0 && servoYPos > 0) {
      servoYPos -= stepSize;  // Move counterclockwise
    }
  }

  // Control extension servo
  if (abs(deviationExtension) > centerThreshold) {
    if (deviationExtension > 0 && servoExtensionPos < 180) {
      servoExtensionPos += stepSize;  // Move clockwise
    } else if (deviationExtension < 0 && servoExtensionPos > 0) {
      servoExtensionPos -= stepSize;  // Move counterclockwise
    }
  }

  // Write positions to servos
  servoZ.write(servoZPos);
  servoY.write(servoYPos);
  servoExtension.write(servoExtensionPos);

  // Small delay for smooth movement
  delay(15);
}
