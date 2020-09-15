/*
  MovementController.cpp - Library for controlling a 2WD Engine.
  Created by Ricardo Fiorani, September 15, 2020.
*/

#include "Arduino.h"
#include "MovementController.h"

MovementController::MovementController()
{
  EnableMotorA = 10;
  EnableMotorB = 11;
  MotorA1 = 5;
  MotorA2 = 6;
  MotorB1 = 7;
  MotorB2 = 8;
  defaultSpeed = 57;
  // All motor control pins are outputs
  pinMode(EnableMotorA, OUTPUT);
  pinMode(EnableMotorB, OUTPUT);
  pinMode(MotorA1, OUTPUT);
  pinMode(MotorA2, OUTPUT);
  pinMode(MotorB1, OUTPUT);
  pinMode(MotorB2, OUTPUT);
}

void MovementController::forward(int speed)   //run both motors in the same direction
{
  if (speed < 1) {
    MovementController::stopMoving();
    return;
  }

  MovementController::forwardWheelA(speed);
  MovementController::forwardWheelB(speed);
}

void MovementController::back(int speed) {
  if (speed < 1) {
    MovementController::stopMoving();
    return;
  }

  MovementController::backwardWheelA(speed);
  MovementController::backwardWheelB(speed);
}

void MovementController::stopMoving() {
  MovementController::stopWheelA();
  MovementController::stopWheelB();
}

void MovementController::stopWheelA() {
  digitalWrite(MotorA1, LOW);
  digitalWrite(MotorA2, LOW);
}

void MovementController::stopWheelB() {
  digitalWrite(MotorB1, LOW);
  digitalWrite(MotorB2, LOW);
}

void MovementController::forwardWheelA(int speed) {
  digitalWrite(MotorA1, HIGH);
  digitalWrite(MotorA2, LOW);
  analogWrite(EnableMotorA, speed);
}

void MovementController::forwardWheelB(int speed) {
  digitalWrite(MotorB1, HIGH);
  digitalWrite(MotorB2, LOW);
  analogWrite(EnableMotorB, speed);
}

void MovementController::backwardWheelA(int speed) {
  digitalWrite(MotorA1, LOW);
  digitalWrite(MotorA2, HIGH);
  analogWrite(EnableMotorA, speed);
}

void MovementController::backwardWheelB(int speed) {
  digitalWrite(MotorB1, LOW);
  digitalWrite(MotorB2, HIGH);
  analogWrite(EnableMotorB, speed);
}

void MovementController::turnRight(int amount) {
  MovementController::backwardWheelB(defaultSpeed);
  MovementController::forwardWheelA(defaultSpeed);
  delay(amount);
}

void MovementController::turnLeft(int amount) {
  MovementController::backwardWheelA(defaultSpeed);
  MovementController::forwardWheelB(defaultSpeed);
  delay(amount);
}