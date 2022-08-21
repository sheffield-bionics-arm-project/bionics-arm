/*
  StepperMotor.h - Library for controlling a stepper motor using a 
   ULN2003 driver board (or similar). Supports half and full step modes.
   To be used on Arduino (Uno) board.
  Created by David Wilkinson (Sheffield Bionics) 20-08-2022.
  Released into the public domain.
*/

#include "Arduino.h"
#include "StepperMotor.h"

StepperMotor::StepperMotor(int steps_per_rev, int speed_rpm, int step_mode, int pin_coil_1, int pin_coil_2, int pin_coil_3, int pin_coil_4)
{
  pinMode(pin_coil_1, OUTPUT);
  pinMode(pin_coil_2, OUTPUT);
  pinMode(pin_coil_3, OUTPUT);
  pinMode(pin_coil_4, OUTPUT);

  _pin_c1 = pin_coil_1;
  _pin_c2 = pin_coil_2;
  _pin_c3 = pin_coil_3;
  _pin_c4 = pin_coil_4;
  _steps_per_rev = steps_per_rev;
  _step_mode = step_mode;

  _commutation_state = 0; //by default
  _direction = 1;

  _delay_amount = (unsigned long) (60.0 * 1000.0 / _steps_per_rev / speed_rpm); // delay is in ms thus * 1000, dependent on required speed
  _last_step_time = 0;
}

void StepperMotor::stepOnce()
{
  // loop until waited required delay time to match speed
  while (millis() - _last_step_time < _delay_amount);

  if (_step_mode == 0)
  {
    switch (_commutation_state)
    {
      case 0:
        digitalWrite(_pin_c1, LOW);
        digitalWrite(_pin_c2, HIGH);
        digitalWrite(_pin_c3, HIGH);
        digitalWrite(_pin_c4, HIGH);
        break;

      case 1:
        digitalWrite(_pin_c1, LOW);
        digitalWrite(_pin_c2, HIGH);
        digitalWrite(_pin_c3, LOW);
        digitalWrite(_pin_c4, HIGH);
        break;

      case 2:
        digitalWrite(_pin_c1, HIGH);
        digitalWrite(_pin_c2, HIGH);
        digitalWrite(_pin_c3, LOW);
        digitalWrite(_pin_c4, HIGH);
        break;

      case 3:
        digitalWrite(_pin_c1, HIGH);
        digitalWrite(_pin_c2, LOW);
        digitalWrite(_pin_c3, LOW);
        digitalWrite(_pin_c4, HIGH);
        break;

      case 4:
        digitalWrite(_pin_c1, HIGH);
        digitalWrite(_pin_c2, LOW);
        digitalWrite(_pin_c3, HIGH);
        digitalWrite(_pin_c4, HIGH);
        break;

      case 5:
        digitalWrite(_pin_c1, HIGH);
        digitalWrite(_pin_c2, LOW);
        digitalWrite(_pin_c3, HIGH);
        digitalWrite(_pin_c4, LOW);
        break;

      case 6:
        digitalWrite(_pin_c1, HIGH);
        digitalWrite(_pin_c2, HIGH);
        digitalWrite(_pin_c3, HIGH);
        digitalWrite(_pin_c4, LOW);
        break;

      case 7:
        digitalWrite(_pin_c1, LOW);
        digitalWrite(_pin_c2, HIGH);
        digitalWrite(_pin_c3, HIGH);
        digitalWrite(_pin_c4, LOW);
        break;
    }
    _commutation_state = (_commutation_state + _direction) % 8; //setting next commutation state
  }

  else
  {
    switch (_commutation_state)
    {
      case 0:
        digitalWrite(_pin_c1, LOW);
        digitalWrite(_pin_c2, HIGH);
        digitalWrite(_pin_c3, HIGH);
        digitalWrite(_pin_c4, HIGH);
        break;

      case 1:
        digitalWrite(_pin_c1, HIGH);
        digitalWrite(_pin_c2, HIGH);
        digitalWrite(_pin_c3, LOW);
        digitalWrite(_pin_c4, HIGH);
        break;

      case 2:
        digitalWrite(_pin_c1, HIGH);
        digitalWrite(_pin_c2, LOW);
        digitalWrite(_pin_c3, HIGH);
        digitalWrite(_pin_c4, HIGH);
        break;

      case 3:
        digitalWrite(_pin_c1, HIGH);
        digitalWrite(_pin_c2, HIGH);
        digitalWrite(_pin_c3, HIGH);
        digitalWrite(_pin_c4, LOW);
        break;
    }
    _commutation_state = ( ( (_commutation_state + _direction) % 4) + 4 ) % 4; //setting next commutation state
  }
  _last_step_time = millis();
}

void StepperMotor::setSpeed(float speed_rpm)
{
  _delay_amount = 60 * 1000 / _steps_per_rev / abs(speed_rpm);
  int prev_direction = _direction;
  _direction = speed_rpm / abs(speed_rpm);

  if (prev_direction = _direction * -1) // if change in direction, update next commutation state accordingly
  {
    //this is required in case motor speed changes sign between commutations
    _commutation_state = ( ( (_commutation_state + _direction) % 8) + 8 ) % 8;
  }
  
}

void StepperMotor::setStepMode(int step_mode)
{
  _step_mode = step_mode; // 0 = half step, 1 = full step 
}

void StepperMotor::rotateThroughAngle(float angle_deg)
{
  if (angle_deg < 0) // if negative
  {
    _direction = -1;
    angle_deg = angle_deg * -1;
  }
  
  int num_steps = (angle_deg / 360.0) * _steps_per_rev;
  for (int i = 0; i < num_steps; i++)
  {
    stepOnce();
    Serial.println(_commutation_state);
  }
  
}

void StepperMotor::synchronize()
{
  int num_steps = _step_mode ? 4 : 8; // if step mode is half, then 8 steps required
  for (int i = 0; i < num_steps; i++)
  {
    stepOnce();
  }  
}