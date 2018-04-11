#include <NewPing.h>
#include<AFMotor.h>
//Maze runner code for bot made using motor driver shield

AF_DCMotor motor2(2);
AF_DCMotor motor1(1);

#define lefttrig A0  // left sensor trigger pin
#define leftecho A1  // left sensor echo pin
#define frontecho A4 // front sensor echo pin
#define fronttrig A5 // front sensor trigger pin
#define righttrig A3 // right sensor trigger pin
#define rightecho A2 // right sensor echo pin
#define MAX_DISTANCE 100

NewPing sonarleft(lefttrig, leftecho, MAX_DISTANCE);
NewPing sonarright(righttrig, rightecho, MAX_DISTANCE);
NewPing sonarfront(fronttrig, frontecho, MAX_DISTANCE);


void setup() {
  motor2.setSpeed(160);
  motor1.setSpeed(160);
}


void loop() {
  int reading = analyse();
  delay(500);
  // Taking decision based on the values of reading. Values ranging from 0 to 5
  if (reading == 0){
     straight();           // go straight
  }
  else if (reading == 1){
     leftturn();           // turn left by 90 degrees
  }
  else if (reading == 2){
     rightturn();          // turn right by 90 degrees
  }
  else if (reading == 3){
     uturn();              // take uturn i.e., all the routes are blocked
  }
  else if (reading == 4){
     littleright();        // turn to right by a few degrees
  }
  else if (reading == 5){
     littleleft();         // turn to left by a few degrees
  } 
}

void straight(){
  motor2.run(FORWARD);
  motor1.run(FORWARD);
  delay(500);
  motor2.run(RELEASE);
  motor1.run(RELEASE);
}

void leftturn(){
  motor1.run(FORWARD);
  motor2.run(RELEASE);
  delay(500);
  motor1.run(RELEASE);
  motor2.run(RELEASE);
}

void rightturn(){
  motor2.run(FORWARD);
  motor1.run(RELEASE);
  delay(500);
  motor2.run(RELEASE);
  motor1.run(RELEASE);
}

void uturn(){
  motor1.run(BACKWARD);
  motor2.run(FORWARD);
  delay(500);
  motor1.run(RELEASE);
  motor2.run(RELEASE); 
}

void littleleft(){
  motor1.run(FORWARD);
  delay(50);
  motor1.run(RELEASE);
}

void littleright(){
  motor2.run(FORWARD);
  delay(50);
  motor2.run(RELEASE);
}


int readPing(int sensor) { // read the ultrasonic sensor distance
  delay(70);   
  unsigned int uS;
  if(sensor == 1) 
    uS = sonarleft.ping();
  else if(sensor == 2)
    uS = sonarright.ping();
  else if(sensor == 3)
    uS = sonarfront.ping();
  int cm = uS/US_ROUNDTRIP_CM;
  return cm;
}

//Maze width is 30cm and distance between sensors is 8cm 
int analyse() {
   long left = readPing(1);  // left sensor reading in cm
   if (left == 0){
       left = readPing(1);
   }
   long front = readPing(3); // front sensor reading in cm
   if (front == 0){
      front = readPing(3);
   }
   long right = readPing(2);  // right sensor reading in cm
   if (right == 0){
      right = readPing(2); 
   }
   if (right > 13 && right < 18){
      return 4;    // turn a little right
   }
   if (left > 13 && left < 18){
      return 5;    // turn a little left
   }
   if (right >= 18){
      return 2;    // turn right by 90 degrees
   }
   if (front > 8){
      return 0;    // go straight
   }
   if (left >= 18){
      return 1;    // turn left by 90 degrees
   }
   return 3;       // take a uturn
}
