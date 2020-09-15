/*
  MovementController.h - Library for controlling a 2WD Engine.
  Created by Ricardo Fiorani, September 15, 2020.
*/

#ifndef MovementController_h
#define MovementController_h

#include "Arduino.h"

class MovementController
{
  public:
    MovementController();
    void forward(int speed);
    void back(int speed);
    void stopMoving();
    void turnRight(int amount);
    void turnLeft(int amount);
    int defaultSpeed;
  private:
    int EnableMotorA;
    int EnableMotorB;
    int MotorA1;
    int MotorA2;
    int MotorB1;
    int MotorB2;
    void forwardWheelA(int speed);
    void forwardWheelB(int speed);
    void backwardWheelA(int speed);
    void backwardWheelB(int speed);
};

#endif