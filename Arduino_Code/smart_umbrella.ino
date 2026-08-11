#include <Servo.h>

Servo umbrellaServo;

// Sensor pins
const int rainSensorPin = A0;
const int lightSensorPin = A1;

// Servo pin
const int servoPin = 9;

// Threshold values
// You may need to change these after testing
const int rainThreshold = 500;
const int lightThreshold = 600;

// Servo positions
const int OPEN_POSITION = 90;
const int CLOSE_POSITION = 0;

bool umbrellaOpen = false;

void setup() {
  Serial.begin(9600);

  umbrellaServo.attach(servoPin);

  // Start with umbrella closed
  umbrellaServo.write(CLOSE_POSITION);
  umbrellaOpen = false;

  Serial.println("Smart Umbrella System Started");
}

void loop() {

  // Read sensors
  int rainValue = analogRead(rainSensorPin);
  int lightValue = analogRead(lightSensorPin);

  // Display sensor values
  Serial.print("Rain Sensor: ");
  Serial.print(rainValue);

  Serial.print(" | Light Sensor: ");
  Serial.println(lightValue);

  /*
     Rain sensor:
     Depending on your sensor module, the value may
     DECREASE when water is detected.

     LDR:
     Depending on the wiring, the value may increase
     or decrease with light.
  */

  bool rainDetected = rainValue < rainThreshold;
  bool strongLight = lightValue > lightThreshold;

  // Open umbrella if rain OR strong sunlight is detected
  if (rainDetected || strongLight) {

    if (!umbrellaOpen) {
      openUmbrella();
    }
  }

  // Close umbrella if there is no rain and light is low
  else {

    if (umbrellaOpen) {
      closeUmbrella();
    }
  }

  delay(1000);
}


// ----------------------------
// Open Umbrella
// ----------------------------

void openUmbrella() {

  Serial.println("Opening Umbrella...");

  umbrellaServo.write(OPEN_POSITION);

  delay(1000);

  umbrellaOpen = true;

  Serial.println("Umbrella OPEN");
}


// ----------------------------
// Close Umbrella
// ----------------------------

void closeUmbrella() {

  Serial.println("Closing Umbrella...");

  umbrellaServo.write(CLOSE_POSITION);

  delay(1000);

  umbrellaOpen = false;

  Serial.println("Umbrella CLOSED");
}
