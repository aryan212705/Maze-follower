//Maze runner code for bot made using motor driver IC L293D
int lefttrig = 13;  // left sensor trigger pin
int leftecho = 11;  // left sensor echo pin
int frontecho = 2; // front sensor echo pin
int fronttrig = 3; // front sensor trigger pin
int righttrig = 4; // right sensor trigger pin
int rightecho = 5; // right sensor echo pin*/
int motor1_a = 6;  // motor 1 a(left motor)
int motor1_b = 7;  // motor 1 b
int vcc_sensors = 8; // power supply pin for all sensors
int motor2_a = 9;  // motor 2 a(right motor)
int motor2_b = 10; // motor 2 b
int driverpower2 = 12;  // motor driver board 5V power supply

void setup() {
  
  // setting up pins for OUTPUT
  pinMode(motor1_a, OUTPUT);
  pinMode(motor1_b, OUTPUT);
  pinMode(motor2_a, OUTPUT);
  pinMode(motor2_b, OUTPUT);
  pinMode(vcc_sensors, OUTPUT);
  digitalWrite(vcc_sensors, HIGH);
  pinMode(driverpower2, OUTPUT);
  digitalWrite(driverpower2, HIGH);
}


void loop() {
  int reading = analyse();
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
  digitalWrite(driverpower2, HIGH);
  digitalWrite(motor1_a, HIGH);
  digitalWrite(motor2_a, HIGH);
  delay(500);
  digitalWrite(motor1_a, LOW);
  digitalWrite(motor2_a, LOW);
}

void leftturn(){
  digitalWrite(motor2_a, HIGH);
  delay(200);
  digitalWrite(motor2_a, LOW);
}

void rightturn(){
  digitalWrite(motor1_a, HIGH);
  delay(200);
  digitalWrite(motor1_a, LOW); 
}

void uturn(){
  digitalWrite(motor1_b, HIGH);
  digitalWrite(motor2_a, HIGH);
  delay(200);
  digitalWrite(motor1_b, LOW);
  digitalWrite(motor2_a, LOW); 
}

void littleleft(){
  digitalWrite(motor2_a, HIGH);
  delay(50);
  digitalWrite(motor2_a, LOW);
}

void littleright(){
  digitalWrite(motor1_a, HIGH);
  delay(50);
  digitalWrite(motor1_a, LOW); 
}

// function to get reading of sensor based on supplied trigger and echo pin
long sensor(int pingPin, int echoPin){
  long duration, cm;
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(pingPin, LOW);
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
  cm = microsecondsToCentimeters(duration);
  return cm;
}

// function to convert time into distance
long microsecondsToCentimeters(long microseconds) {
   return microseconds / 29 / 2;
}

int analyse() {
   long left = sensor(lefttrig, leftecho);  // left sensor reading in cm
   long front = sensor(fronttrig, frontecho); // front sensor reading in cm
   long right = sensor(righttrig, rightecho);  // right sensor reading in cm
   if (right > 7 && right < 13){
      return 4;    // turn a little right
   }
   if (left > 7 && left < 13){
      return 5;    // turn a little left
   }
   if (right >= 13){
      return 2;    // turn right by 90 degrees
   }
   if (front > 8){
      return 0;    // go straight
   }
   if (left >= 13){
      return 1;    // turn left by 90 degrees
   }
   return 3;       // take a uturn
}
