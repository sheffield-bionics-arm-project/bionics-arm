/*
  StepperMotor.h - Library for controlling a unipolar stepper motor using a 
   ULN2003 driver board (or similar). To be used for Arduino
  Created by David Wilkinson (Sheffield Bionics) 20-08-2022.
  Released into the public domain.
*/

#ifndef StepperMotor_h
#define StepperMotor_h

#include "Arduino.h"

class StepperMotor
{
  public:
    StepperMotor(int steps_per_rev, int speed_rpm, int pin_coil_1, int pin_coil_2, int pin_coil_3, int pin_coil_4);
    void setSpeed(float speed_rpm);
    void rotateThroughAngle(float angle);
    void stepOnce(int commutation_state);
    void cycleSteps(); //used for initialization to synchronize position

  private:
    int _steps_per_rev, _pin_coil_1, _pin_coil_2, _pin_coil_3, _pin_coil_4, _step_number;
    int _commutation_state, _direction;
    unsigned long _delay_amount;
    unsigned long _last_step_time;
    
};

#endif