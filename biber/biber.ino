// set serial to 115200
// send ascii: 
// 0,100 = left, 100ms
// 1,200 = right, 200ms
// 2,1000 = forward, 1000ms
// 3,2000 = backward, 1000ms
// 4,128 = set speed of both motors to 128 


#include <AFMotor.h>

#define BAUD_RATE 115200

AF_DCMotor motorLeft(2, MOTOR12_1KHZ);
AF_DCMotor motorRight(3, MOTOR34_1KHZ);

enum Command {
  Left = 0,
  Right,
  Forward,
  Backward,
  Speed,

  COMMAND_MAX
};

void setup() {
  motorLeft.setSpeed(255);
  motorRight.setSpeed(255);

  motorLeft.run(RELEASE);
  motorRight.run(RELEASE);
     
  Serial.begin(BAUD_RATE); 
}

// the loop function runs over and over again forever
void loop() {
    while (Serial.available() > 0) {
        Command command = (Command)Serial.parseInt();
        int value = Serial.parseInt();
        if(command < 0 || command >= COMMAND_MAX || value <= 0 || value > 10000)
          continue;
          
        switch(command) {
          case Left: 
            turnLeft(value);
            break;
          case Right: 
            turnRight(value);
            break;
          case Forward: 
            driveForward(value);
            break;
          case Backward: 
            driveBackward(value);
            break;
          case Speed: 
            if(value > 255)
              continue;
            setSpeed(value);
            break;          
        }
    }
}

void turnLeft(int delayMs) {
  motorLeft.run(FORWARD);
  motorRight.run(BACKWARD);
  delay(delayMs);
  motorLeft.run(RELEASE);
  motorRight.run(RELEASE);
}

void turnRight(int delayMs) {
  motorLeft.run(BACKWARD);
  motorRight.run(FORWARD);
  delay(delayMs);
  motorLeft.run(RELEASE);
  motorRight.run(RELEASE);
}

void driveForward(int delayMs) {
  motorLeft.run(BACKWARD);
  motorRight.run(BACKWARD);
  delay(delayMs);
  motorLeft.run(RELEASE);
  motorRight.run(RELEASE);
}

void driveBackward(int delayMs) {
  motorLeft.run(FORWARD);
  motorRight.run(FORWARD);
  delay(delayMs);
  motorLeft.run(RELEASE);
  motorRight.run(RELEASE);
}

void setSpeed(int speed) {
  
  motorLeft.setSpeed(speed);
  motorRight.setSpeed(speed);
}

