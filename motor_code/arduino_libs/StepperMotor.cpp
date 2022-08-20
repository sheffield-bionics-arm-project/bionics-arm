/*
  StepperMotor.h - Library for controlling a stepper motor using a 
   ULN2003 driver board (or similar). To be used for Arduino
  Created by David Wilkinson (Sheffield Bionics) 20-08-2022.
  Released into the public domain.
*/

#include "Arduino.h"
#include "StepperMotor.h"

StepperMotor::StepperMotor(int steps_per_rev, int speed_rpm, int pin_coil_1, int pin_coil_2, int pin_coil_3, int pin_coil_4)
{
  pinMode(pin_coil_1, OUTPUT);
  pinMode(pin_coil_2, OUTPUT);
  pinMode(pin_coil_3, OUTPUT);
  pinMode(pin_coil_4, OUTPUT);

  _pin_coil_1 = pin_coil_1;
  _pin_coil_2 = pin_coil_2;
  _pin_coil_3 = pin_coil_3;
  _pin_coil_4 = pin_coil_4;
  _steps_per_rev = steps_per_rev;

  _commutation_state = 0;
  _direction = 1;

  _delay_amount = 60 * 1000 / _steps_per_rev / speed_rpm; // delay is in ms thus * 1000, dependent on required speed
  _last_step_time = 0;
}

void StepperMotor::stepOnce()
{
  // loop until waited required delay time to match speed
  while (millis() - _last_step_time < _delay_amount);

  switch (_commutation_state)
  {
    case 0
      digitalWrite(_pin_coil_1, LOW);
      digitalWrite(_pin_coil_2, HIGH);
      digitalWrite(_pin_coil_3, HIGH);
      digitalWrite(_pin_coil_4, HIGH);
      break;

    case 1
      digitalWrite(_pin_coil_1, LOW);
      digitalWrite(_pin_coil_2, HIGH);
      digitalWrite(_pin_coil_3, LOW);
      digitalWrite(_pin_coil_4, HIGH);
      break;

    case 2
      digitalWrite(_pin_coil_1, HIGH);
      digitalWrite(_pin_coil_2, HIGH);
      digitalWrite(_pin_coil_3, LOW);
      digitalWrite(_pin_coil_4, HIGH);
      break;

    case 3
      digitalWrite(_pin_coil_1, HIGH);
      digitalWrite(_pin_coil_2, LOW);
      digitalWrite(_pin_coil_3, LOW);
      digitalWrite(_pin_coil_4, HIGH);
      break;

    case 4
      digitalWrite(_pin_coil_1, HIGH);
      digitalWrite(_pin_coil_2, LOW);
      digitalWrite(_pin_coil_3, HIGH);
      digitalWrite(_pin_coil_4, HIGH);
      break;

    case 5
      digitalWrite(_pin_coil_1, HIGH);
      digitalWrite(_pin_coil_2, LOW);
      digitalWrite(_pin_coil_3, HIGH);
      digitalWrite(_pin_coil_4, LOW);
      break;

    case 6
      digitalWrite(_pin_coil_1, HIGH);
      digitalWrite(_pin_coil_2, HIGH);
      digitalWrite(_pin_coil_3, HIGH);
      digitalWrite(_pin_coil_4, LOW);
      break;

    case 7
      digitalWrite(_pin_coil_1, LOW);
      digitalWrite(_pin_coil_2, HIGH);
      digitalWrite(_pin_coil_3, HIGH);
      digitalWrite(_pin_coil_4, LOW);
      break;
  }
  _last_step_time = millis();
  
  _commutation_state = (_commutation_state + _direction) % 8; //setting next commutation state
}

void StepperMotor::setSpeed(float speed_rpm)
{
  _delay_amount = 60 * 1000 / _steps_per_rev / abs(speed_rpm);
  _direction = speed_rpm / abs(speed_rpm);
}

void StepperMotor::rotateThroughAngle(float angle_deg, float max_speed_rpm=NULL)
{
  int num_steps = (angle_deg / 360.0) * _steps_per_rev;
}

void StepperMotor::cycleSteps()