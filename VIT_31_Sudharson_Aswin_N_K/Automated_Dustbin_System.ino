#include <Servo.h>

// Variable for servo position
int servoPos = 0;

// Initializing the servo motor and pins
Servo servo_9;
#define pirPin 13
#define trigPin 9
#define echoPin 8
#define overridePin 11

// RGB LED pins
#define greenPin 2
#define yellowPin 3
#define redPin 4

// Variables for ultrasonic sensor and PIR sensor
long duration;
int distance;
int pirState = LOW;
int val = 0;

// Setup function to initialize pin modes and servo
void setup() {
  servo_9.attach(6, 500, 2500); // Attaching servo to pin 6
  pinMode(pirPin, INPUT); // Setting PIR pin as input
  pinMode(trigPin, OUTPUT); // Setting trigger pin as output
  pinMode(echoPin, INPUT); // Setting echo pin as input
  pinMode(overridePin, INPUT); // Setting override pin as input
  
  pinMode(greenPin, OUTPUT); // Setting green pin as output
  pinMode(yellowPin, OUTPUT); // Setting yellow pin as output
  pinMode(redPin, OUTPUT); // Setting red pin as output
}

// Loop function for continuous execution
void loop() {
  // Calling functions to check various parameters
  checkDistance();
  checkPIR();
  checkOverride();
  checkBinStatus();
}

// Function to measure the distance using the ultrasonic sensor
void checkDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
}

// Function to check the PIR sensor and open or close the lid accordingly
void checkPIR() {
  if (digitalRead(pirPin) == HIGH) {
    openLid();
    pirState = HIGH;
  }
  if (pirState == HIGH) {
    closeLid();
    pirState = LOW;
  }
}

// Function to check the manual override button and operate the lid
void checkOverride() {
  if (digitalRead(overridePin) == HIGH) {
    openLid();
    closeLid();
  }
}

// Function to check the bin status and set the LED color accordingly
void checkBinStatus() {
  int binLevel = map(distance, 0, 200, 0, 100);
  
  if (binLevel < 40) {
    setColor(1, 0, 0); // Red
  } else if (binLevel >= 40 && binLevel < 70) {
    setColor(1, 1, 0); // Yellow
  } else {
    setColor(0, 1, 0); // Green
  }
}

// Function to open the lid gradually
void openLid() {
  for (servoPos = 0; servoPos <= 90; servoPos += 1) {
    servo_9.write(servoPos);
    delay(15);
  }
  delay(5000);
}

// Function to close the lid gradually
void closeLid() {
  for (servoPos = 90; servoPos >= 0; servoPos -= 1) {
    servo_9.write(servoPos);
    delay(15); 
  }
}

// Function to set the RGB LED color
void setColor(int red, int green, int blue) {
  digitalWrite(redPin, red);
  digitalWrite(greenPin, green);
  digitalWrite(yellowPin, blue);
}
