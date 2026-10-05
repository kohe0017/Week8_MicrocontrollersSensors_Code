/*
  DM3014 Interactive Devices, Ashley Hi 2026
  Week 8 - Microcontrollers & Sensors
  ESP32-C3 Sensor Servo Example
  When distance is less than 10cm, ultrasonic sensor triggers servo to turn 180º.
  Additional Components: Servo Motor, HC-SR04 Sensor
*/

// ====== Reference Libraries ======
#include <ESP32Servo.h>

// ====== Set Servo ======
#define SERVO_PIN 7

// ====== Set HC-SR04 Sensor ======
#define TRIG_PIN  3
#define ECHO_PIN  4
#define DISTANCE_THRESHOLD  10 // *** edit the sensor trigger distance here (in cm)

// ====== Create Servo Objects ======
Servo servo;

// ====== Sensor Variables ======
float duration_us, distance_cm;

void setup() {
  // ====== Setup Serial Monitor ======
  Serial.begin(115200);

  // ====== Setup Sensor / Servo ======
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  

  ESP32PWM::allocateTimer(0);
	ESP32PWM::allocateTimer(1);
	ESP32PWM::allocateTimer(2);
	ESP32PWM::allocateTimer(3);
	servo.setPeriodHertz(50);
	servo.attach(SERVO_PIN, 500, 2000);
  servo.write(0);

  pinMode(8, OUTPUT);
}

void loop() {
  // ====== Sensor / Servo Output ======
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  duration_us = pulseIn(ECHO_PIN, HIGH);
  distance_cm = 0.017 * duration_us;
  if (distance_cm < DISTANCE_THRESHOLD) {
    servo.write(90); 
    digitalWrite(8, HIGH); // *** edit the rotation of the servo here (within range: 0 – 180)
  //     // change state of the LED by setting the pin to the HIGH voltage level
  // delay(1000);  
  } else if (distance_cm < DISTANCE_THRESHOLD/2) {
    servo.write(180); // *** edit the rotation of the servo here (within range: 0 – 180)
    digitalWrite(8, HIGH);   // change state of the LED by setting the pin to the LOW voltage level
  
  } 
  else {
    servo.write(0);
    digitalWrite(8, LOW);
  }
  // ====== Serial Output ======
  Serial.print("Distance: ");
  Serial.print(distance_cm);
  Serial.println(" cm");

  delay(500);
}