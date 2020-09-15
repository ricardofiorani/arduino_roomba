#include <Servo.h>
#include <MovementController.h>
const bool DEBUG_MODE_ENABLED = false;

/**
   SERVO

   ORANGE = DATA = 9
   RED = POSITIVE
   BROWN = NEGATIVE
*/
const int servoPort = 9;
Servo sensorServo;

const int movementOffset = 25;
const int LEFT = 180 - movementOffset;
const int CENTER = 90;
const int RIGHT = 0 + movementOffset;


/**
   MOTORS
*/
// const int EnableMotorA = 10;
// const int EnableMotorB = 11;
// const int MotorA1 = 5;
// const int MotorA2 = 6;
// const int MotorB1 = 7;
// const int MotorB2 = 8;

// const int defaultSpeed = 57;

/**
   ULTRASONIC SENSOR
*/
const int sonicSensorTrigger = 4; //attach pin D4 Arduino to pin Trig of HC-SR04
const int sonicSensorEcho = 3; //attach pin D3 Arduino to pin Echo of HC-SR04

void setup() {
  // All motor control pins are outputs
  // pinMode(EnableMotorA, OUTPUT);
  // pinMode(EnableMotorB, OUTPUT);
  // pinMode(MotorA1, OUTPUT);
  // pinMode(MotorA2, OUTPUT);
  // pinMode(MotorB1, OUTPUT);
  // pinMode(MotorB2, OUTPUT);

  //Ultrasonic sensor
  pinMode(sonicSensorTrigger, OUTPUT); // Sets the sonicSensorTrigger as an OUTPUT
  pinMode(sonicSensorEcho, INPUT); // Sets the sonicSensorEcho as an INPUT

  //Servo
  sensorServo.attach(servoPort);  // attaches the servo on pin 9 to the servo object

  //Logger
  Serial.begin(9600);
}

/**
   Ultrasonic sensor
*/
int getDistance() {
  // Clears the sonicSensorTrigger condition
  digitalWrite(sonicSensorTrigger, LOW);
  delayMicroseconds(2);
  // Sets the sonicSensorTrigger HIGH (ACTIVE) for 10 microseconds
  digitalWrite(sonicSensorTrigger, HIGH);
  delayMicroseconds(30);
  digitalWrite(sonicSensorTrigger, LOW);
  // Reads the sonicSensorEcho, returns the sound wave travel time in microseconds
  const long duration = pulseIn(sonicSensorEcho, HIGH);
  // Calculating the distance
  const int distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  delay(50);

  return distance;
}

/**
   Servo
*/
void moveServo(int degrees) {
  sensorServo.write(degrees);
  delay(100);
}

/**
   Assisting methods
*/

void logDistance(String distanceName, int distance) {
  debug(distanceName);
  debug(" : ");
  debug(distance);
  debugLn(" cm");
}

int smallest(int x, int y, int z) {
  int smallest = min(x, y);
  return min(smallest, z);
}

int biggest(int x, int y, int z) {
  int biggest = max(x, y);
  return max(biggest, z);
}

int currentPosition = CENTER;
int distanceLeft;
int distanceRight;
int distanceCenter;

void updateRadar() {
  moveServo(currentPosition);

  switch (currentPosition) {
    case CENTER:
      distanceCenter = getDistance();
      logDistance("Distance CENTER", distanceCenter);
      currentPosition = LEFT;
      break;
    case LEFT:
      distanceLeft = getDistance();
      logDistance("Distance LEFT", distanceCenter);
      currentPosition = RIGHT;
      break;
    case RIGHT:
      distanceRight = getDistance();
      logDistance("Distance RIGHT", distanceCenter);
      currentPosition = CENTER;
      break;
  }
}

void debug(String message) {
  if (false == DEBUG_MODE_ENABLED) {
    return;
  }
  
  Serial.print(message);
}

void debug(int message){
  if (false == DEBUG_MODE_ENABLED) {
    return;
  }
  
  Serial.print(message);
}

void debugLn(String message){
  if (false == DEBUG_MODE_ENABLED) {
    return;
  }

  Serial.println(message);
}

void debugLn(int message) {
  if (false == DEBUG_MODE_ENABLED) {
    return;
  }

  Serial.println(message);
}

// -- MAIN LOOP

void loop() {
  //Speedtest
  // for(int i = 0; i < 256; i++){
  //   debug("SPEED: ");
  //   debugLn(i);
  //   moveForward(i);
  //   delay(100);
  // }
  // return;

  updateRadar();

  const int minDistance = smallest(distanceCenter, distanceLeft, distanceRight);
  const int maxDistance = biggest(distanceCenter, distanceLeft, distanceRight);

  if (minDistance != 0 && minDistance <= 15 ) {
    if (minDistance == distanceCenter) {
      debugLn("CENTER SENSOR: Near colision detected!");

      moveBackwards(defaultSpeed);
      delay(200);
      updateRadar();
      updateRadar();
      updateRadar();

      if (distanceRight >= distanceLeft) {
        debugLn("CENTER SENSOR: Turning RIGHT");
        turnRight(250);
      } else {
        debugLn("CENTER SENSOR: Turning LEFT");
        turnLeft(250);
      }
    } else if (minDistance == distanceLeft) {
      debugLn("LEFT SENSOR: Near colision detected!");
      turnRight(250);
    } else {
      debugLn("RIGHT SENSOR: Near colision detected!");
      turnLeft(250);
    }
  } else {
    debugLn("No possible colision detected");
  }

  moveForward(defaultSpeed);

  return; //-------------------------------------------


  //Below is the old logic

  //If can move forward, just go forward and end of loop
  // if (distanceCenter == 0 || distanceCenter > 10) {
  //   debugLn("Continuing forward");
  //   moveForward(defaultSpeed);
  //   moveServo(CENTER);
  //   delay(200);
  //   stopWheels();
  //   return;
  // }

  // debugLn("Too close to something, going backwards");
  // //otherwise, search for a new location
  // stopWheels();
  // moveBackwards(defaultSpeed);
  // delay(1000);
  // stopWheels();

  // //Distance right
  // debugLn("Checking distance to right direction");
  // moveServo(RIGHT);
  // distanceRight = getDistance();
  // logDistance("Distance on the right", distanceRight);
  // delay(1000);

  // //Distance left
  // moveServo(LEFT);
  // distanceLeft = getDistance();
  // logDistance("Distance on the left", distanceLeft);
  // delay(1000);

  // //Move to the default position
  // moveServo(CENTER);

  // if (distanceRight >= distanceLeft) {
  //   debugLn("Turning right 3");
  //   turnRight(250);
  //   moveForward(defaultSpeed);
  // } else {
  //   debugLn("Turning left 3");
  //   turnLeft(250);
  //   moveForward(defaultSpeed);
  // }
}

