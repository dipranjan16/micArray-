#include <Wire.h>

// Pin definitions for microphones (e.g., connect microphones to GPIO pins)
const int mic1Pin = 34;  // Microphone 1
const int mic2Pin = 35;  // Microphone 2
const int mic3Pin = 32;  // Microphone 3

// Variables to store time when sound was detected
unsigned long mic1Time = 0;
unsigned long mic2Time = 0;
unsigned long mic3Time = 0;

bool mic1Detected = false;
bool mic2Detected = false;
bool mic3Detected = false;

// Speed of sound in air (in meters per second)
const float speedOfSound = 343.0;

void setup() {
  Serial.begin(115200);

  pinMode(mic1Pin, INPUT);
  pinMode(mic2Pin, INPUT);
  pinMode(mic3Pin, INPUT);
}

void loop() {
  // Read microphones
  int mic1Val = analogRead(mic1Pin);
  int mic2Val = analogRead(mic2Pin);
  int mic3Val = analogRead(mic3Pin);

  // Detect the first sound (assuming a threshold for sound level detection)
  int soundThreshold = 1000;  // Adjust threshold based on your sensor's sensitivity

  if (mic1Val > soundThreshold && !mic1Detected) {
    mic1Time = micros();  // Capture time in microseconds
    mic1Detected = true;
    Serial.println("Mic 1 detected sound");
  }

  if (mic2Val > soundThreshold && !mic2Detected) {
    mic2Time = micros();
    mic2Detected = true;
    Serial.println("Mic 2 detected sound");
  }

  if (mic3Val > soundThreshold && !mic3Detected) {
    mic3Time = micros();
    mic3Detected = true;
    Serial.println("Mic 3 detected sound");
  }

  // Once all microphones detected sound, calculate the direction
  if (mic1Detected && mic2Detected && mic3Detected) {
    // Calculate the time differences
    unsigned long t12 = mic2Time - mic1Time;  // Time difference between mic 1 and mic 2
    unsigned long t23 = mic3Time - mic2Time;  // Time difference between mic 2 and mic 3
    unsigned long t31 = mic1Time - mic3Time;  // Time difference between mic 3 and mic 1

    // Convert time differences to distance using the speed of sound
    float d12 = (t12 / 1e6) * speedOfSound;  // Distance between mic 1 and mic 2
    float d23 = (t23 / 1e6) * speedOfSound;  // Distance between mic 2 and mic 3
    float d31 = (t31 / 1e6) * speedOfSound;  // Distance between mic 3 and mic 1

    // Here, you would add logic to determine the angle or direction based on the distance differences
    // For now, we just print the time differences and distances
    Serial.print("Time difference between mic 1 and mic 2: ");
    Serial.println(t12);
    Serial.print("Time difference between mic 2 and mic 3: ");
    Serial.println(t23);
    Serial.print("Time difference between mic 3 and mic 1: ");
    Serial.println(t31);

    Serial.print("Distance difference between mic 1 and mic 2: ");
    Serial.println(d12);
    Serial.print("Distance difference between mic 2 and mic 3: ");
    Serial.println(d23);
    Serial.print("Distance difference between mic 3 and mic 1: ");
    Serial.println(d31);

    // Reset for next detection
    mic1Detected = false;
    mic2Detected = false;
    mic3Detected = false;
  }
}
