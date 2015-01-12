#include <Servo.h> 
#include <NewPing.h>

#define TRIGGER_PIN  A1  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     A0  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 300 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
#define ANSWER_SERVO_DELAY 1000
#define SERVO_WAIT_TIME_MILLIS 30
#define SONAR_WAIT_TIME_MILLIS 30

#define SERVO_MIN_MS 600
#define SERVO_MAX_MS 2400

#define COMMAND_BUFFER_LENGTH 12

Servo servo;

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

COMMAND currentCommand;

char inData[COMMAND_BUFFER_LENGTH]; // Allocate some space for the string
char inChar=-1; // Where to store the character read
byte index = 0; // Index into array; where to store the character

enum COMMANDS {
  NONE = -1,
  SONAR,        // value = servo microseconds
  COMMANDS_MAX
}

unsigned long lastServoTime;
unsigned long lastSonarTime;
  
void setup() {
  
  // turn on servo
  servo.attach(10);   
  Serial.begin(115200); 
  lastServoTime = millis();
  lastSonarTime = millis();
  sayYes();
}

void loop() {
  readSerial();
}

bool readSerial() {
  bool readSomething = false;
  int command = -1;
  int value = -1;
  while (Serial.available() > 0) {
    readSomething = true;
    command = Serial.parseInt();
    if( command < 0 || command > COMMANDS.COMMANDS_MAX) {
      command = COMMANDS.NONE;
    }
    value = Serial.parseInt();
  }
  
  switch(command) {
    case SONAR: {
       sonarPing(value);
    } 
  } 
  
  return readSomething;
}

void sonarPing(microseconds) {
  microseconds = constrain(microseconds, SERVO_MIN_MS, SERVO_MAX_MS);
  servo.writeMicroseconds(microseconds);
  waitForServo();
  lastServoTime = millis();
  printDistance(); 
  lastServoTime = millis();
}

void waitForServo {
  unsigned long now = millis();
  unsigned long diff = now - lastServoTime;
  if( diff < SERVO_WAIT_TIME_MILLIS ) {
    unsigned long delayTime = SERVO_WAIT_TIME_MILLIS - diff;
    Serial.write("delaying servo movement for ms: ");
    Serial.print(delayTime, DEC);
    delay(delayTime);
  }
}

void printDistance() {
  unsigned int uS = sonar.ping(); // Send ping, get ping time in microseconds (uS).
  Serial.print(uS / US_ROUNDTRIP_CM); // Convert ping time to distance in cm and print result (0 = outside set distance range)
}


void sayNo() {
   servo.writeMicroseconds((SERVO_MAX_MS - SERVO_MIN_MS)/2 + SERVO_MIN_MS);
   delay(ANSWER_SERVO_DELAY);
   servo.writeMicroseconds(SERVO_MAX_MS);
   delay(ANSWER_SERVO_DELAY);
   servo.writeMicroseconds((SERVO_MAX_MS - SERVO_MIN_MS)/2 + SERVO_MIN_MS);
   delay(ANSWER_SERVO_DELAY);
   servo.writeMicroseconds(SERVO_MAX_MS);
   delay(ANSWER_SERVO_DELAY);
   servo.writeMicroseconds((SERVO_MAX_MS - SERVO_MIN_MS)/2 + SERVO_MIN_MS);
   delay(ANSWER_SERVO_DELAY);
}

void sayYes() {
   servo.writeMicroseconds((SERVO_MAX_MS - SERVO_MIN_MS)/2 + SERVO_MIN_MS);
   delay(ANSWER_SERVO_DELAY);
   servo.writeMicroseconds(SERVO_MIN_MS);
   delay(ANSWER_SERVO_DELAY);
   servo.writeMicroseconds((SERVO_MAX_MS - SERVO_MIN_MS)/2 + SERVO_MIN_MS);
   delay(ANSWER_SERVO_DELAY);
   servo.writeMicroseconds(SERVO_MIN_MS);
   delay(ANSWER_SERVO_DELAY);
   servo.writeMicroseconds((SERVO_MAX_MS - SERVO_MIN_MS)/2 + SERVO_MIN_MS);
   delay(ANSWER_SERVO_DELAY);
}
