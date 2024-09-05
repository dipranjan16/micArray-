
// Pin definitions for microphones (e.g., connect microphones to analog pins)
const int mic1Pin = A0;  // Microphone 1
const int mic2Pin = A1;  // Microphone 2
const int mic3Pin = A2;  // Microphone 3
const int mic4Pin = A3;  // Microphone 4
const int mic5Pin = A4;  // Microphone 5
const int mic6Pin = A5;  // Microphone 6

// Variables to store time when sound was detected
unsigned long mic1Time = 0;
unsigned long mic2Time = 0;
unsigned long mic3Time = 0;
unsigned long mic4Time = 0;
unsigned long mic5Time = 0;
unsigned long mic6Time = 0;

bool mic1Detected = false;
bool mic2Detected = false;
bool mic3Detected = false;
bool mic4Detected = false;
bool mic5Detected = false;
bool mic6Detected = false;

// Speed of sound in air (in meters per second)
const float speedOfSound = 343.0;

void setup() {
  Serial.begin(9600);  // Initialize serial communication

  // Set microphone pins as input (optional, as analog pins are input by default)
  pinMode(mic1Pin, INPUT);
  pinMode(mic2Pin, INPUT);
  pinMode(mic3Pin, INPUT);
  pinMode(mic4Pin, INPUT);
  pinMode(mic5Pin, INPUT);
  pinMode(mic6Pin, INPUT);
}

void loop() {
  // Read microphones (analog values between 0 and 1023)
  int mic1Val = analogRead(mic1Pin);
  int mic2Val = analogRead(mic2Pin);
  int mic3Val = analogRead(mic3Pin);
  int mic4Val = analogRead(mic4Pin);
  int mic5Val = analogRead(mic5Pin);
  int mic6Val = analogRead(mic6Pin);

  // Detect the first sound (assuming a threshold for sound level detection)
  int soundThreshold = 500;  // Adjust threshold based on your sensor's sensitivity

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

  if (mic4Val > soundThreshold && !mic4Detected) {
    mic4Time = micros();
    mic4Detected = true;
    Serial.println("Mic 4 detected sound");
  }

  if (mic5Val > soundThreshold && !mic5Detected) {
    mic5Time = micros();
    mic5Detected = true;
    Serial.println("Mic 5 detected sound");
  }

  if (mic6Val > soundThreshold && !mic6Detected) {
    mic6Time = micros();
    mic6Detected = true;
    Serial.println("Mic 6 detected sound");
  }

  // Once all microphones detected sound, calculate the direction
  if (mic1Detected && mic2Detected && mic3Detected && mic4Detected && mic5Detected && mic6Detected) {
    // Calculate the time differences
    unsigned long t12 = mic2Time - mic1Time;  // Time difference between mic 1 and mic 2
    unsigned long t23 = mic3Time - mic2Time;  // Time difference between mic 2 and mic 3
    unsigned long t34 = mic4Time - mic3Time;  // Time difference between mic 3 and mic 4
    unsigned long t45 = mic5Time - mic4Time;  // Time difference between mic 4 and mic 5
    unsigned long t56 = mic6Time - mic5Time;  // Time difference between mic 5 and mic 6

    // Convert time differences to distance using the speed of sound
    float d12 = (t12 / 1e6) * speedOfSound;  // Distance between mic 1 and mic 2
    float d23 = (t23 / 1e6) * speedOfSound;  // Distance between mic 2 and mic 3
    float d34 = (t34 / 1e6) * speedOfSound;  // Distance between mic 3 and mic 4
    float d45 = (t45 / 1e6) * speedOfSound;  // Distance between mic 4 and mic 5
    float d56 = (t56 / 1e6) * speedOfSound;  // Distance between mic 5 and mic 6

    // Here, you would add logic to determine the angle or direction based on the distance differences
    // For now, we just print the time differences and distances
    Serial.print("Time difference between mic 1 and mic 2: ");
    Serial.println(t12);
    Serial.print("Time difference between mic 2 and mic 3: ");
    Serial.println(t23);
    Serial.print("Time difference between mic 3 and mic 4: ");
    Serial.println(t34);
    Serial.print("Time difference between mic 4 and mic 5: ");
    Serial.println(t45);
    Serial.print("Time difference between mic 5 and mic 6: ");
    Serial.println(t56);

    Serial.print("Distance difference between mic 1 and mic 2: ");
    Serial.println(d12);
    Serial.print("Distance difference between mic 2 and mic 3: ");
    Serial.println(d23);
    Serial.print("Distance difference between mic 3 and mic 4: ");
    Serial.println(d34);
    Serial.print("Distance difference between mic 4 and mic 5: ");
    Serial.println(d45);
    Serial.print("Distance difference between mic 5 and mic 6: ");
    Serial.println(d56);

    // Reset for next detection
    mic1Detected = false;
    mic2Detected = false;
    mic3Detected = false;
    mic4Detected = false;
    mic5Detected = false;
    mic6Detected = false;
  }
}
