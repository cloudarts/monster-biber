/**

COMMAND SYNTAX:
===============
"[COMMAND];[VALUE]"

COMMANDS AND VALUES:
====================
-1 NONE
0 TURN HEAD (600 - 2400)
1 SONAR PING (no value)
2 SET LEFT MOTOR SPEED (-255 - 255) 
3 SET RIGHT MOTOR SPEED (-255 - 255)
4 SET SPEED FOR BOTH MOTORS (-255 - 255)

*/



#include <Servo.h> 
#include <NewPing.h>
#include <AFMotor.h>

#define BAUD_RATE 115200
#define SERVO_HEAD 10
#define TRIGGER_PIN  A1  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     A0  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 300 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
#define ANSWER_SERVO_DELAY 600
#define SERVO_WAIT_TIME_MILLIS 30
#define SONAR_WAIT_TIME_MILLIS 30

#define COMMAND_BUFFER_LENGTH 12

#define SERVO_MIN_MS 600
#define SERVO_MAX_MS 2400
const int SERVO_CENTER = (SERVO_MAX_MS - SERVO_MIN_MS)/2 + SERVO_MIN_MS;


Servo servo;

AF_DCMotor motorLeft(1, MOTOR12_1KHZ);
AF_DCMotor motorRight(4, MOTOR12_1KHZ);

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

char inData[COMMAND_BUFFER_LENGTH]; // Allocate some space for the string
char inChar=-1; // Where to store the character read
byte index = 0; // Index into array; where to store the character


unsigned long lastServoTime;
unsigned long lastSonarTime;

  
void setup() {
  
  // turn on servo
  servo.attach(SERVO_HEAD);   
  Serial.begin(BAUD_RATE); 
  lastServoTime = millis();
  lastSonarTime = millis();
  
  motorLeft.setSpeed(0);
  motorRight.setSpeed(0);
  motorLeft.run(RELEASE);
  motorRight.run(RELEASE);
  /*
  servo.writeMicroseconds(SERVO_MIN_MS);
  delay(ANSWER_SERVO_DELAY);
  servo.writeMicroseconds(SERVO_MAX_MS);
  delay(ANSWER_SERVO_DELAY);
  servo.writeMicroseconds(SERVO_CENTER);
  delay(ANSWER_SERVO_DELAY);
  */
}

void loop() {
  readSerial();
}

bool readSerial() {
  int value = -1;
  while (Serial.available() > 0) {
    
    int command = Serial.parseInt();
    
    if( command == 0 ) {        // movement: "0;255;255"
      
      // left motor speed
      value = Serial.parseInt();
      int leftSpeed = value;
      
      // right motor speed
      value = Serial.parseInt();
      value *= -1;  // right motor is wired differently
      int rightSpeed = value;
      
      setMotorSpeed(1, leftSpeed);
      setMotorSpeed(2, rightSpeed);
      break;
    }
    else if( command == 1 ) {    // head movement: "1;1500"
      
      value = Serial.parseInt();
      servo.writeMicroseconds(value); 
      break;
    }
    else if( command == 2 ) {   // sonar ping; "2"
       sonarPing(); 
       break;
    }
  }
}

void setMotorSpeed(int motor, int value) {
  motor = constrain(motor, 0, 2);
  value = constrain(value, -255, 255);
  int absValue = abs(value);
  
  uint8_t direction = RELEASE;
  if( value > 0 ) {
    direction = FORWARD;
  }
  else if( value < 0 ) {
    direction = BACKWARD;  
  }
  
  if( motor == 0 ) {
    motorLeft.setSpeed(absValue);
    motorRight.setSpeed(absValue);  
    motorLeft.run(direction);
    motorRight.run(direction);    
  }
  else if( motor == 1 ) {
    motorLeft.setSpeed(absValue);
    motorLeft.run(direction);    
  }
  else {
    motorRight.setSpeed(absValue);
    motorRight.run(direction);  
  }
} 

void sonarPing() {
  unsigned int dist = getDistance();
  Serial.print(dist);
  Serial.print("\n");
}


unsigned int getDistance() {
  unsigned int uS = sonar.ping(); // Send ping, get ping time in microseconds (uS).
  unsigned int distance = uS / US_ROUNDTRIP_CM; // Convert ping time to distance in cm and print result (0 = outside set distance range)
  return distance;
}
