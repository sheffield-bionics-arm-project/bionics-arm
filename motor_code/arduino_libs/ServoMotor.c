/*
  ServoMotor.c - Library for controlling a servo motor using the
   Arduino Servo library.
  Created by David Wilkinson (Sheffield Bionics) 31-08-2022.
  Released into the public domain.
*/

#include "Arduino.h"
#include "ServoMotor.h"


ServoMotor::ServoMotor(int pin, float default_angle = 90, int min_pulse_width = 544, int max_pulse_width = 2400): Servo()
{
    _default_angle = default_angle;
    ServoMotor::attach(pin, min_pulse_width, max_pulse_width);
}
void ServoMotor::rotateThroughAngle(float angle)
{
    float final_angle = ServoMotor::saturateAngle(float angle);
    ServoMotor::write(final_angle);    
}
void ServoMotor::rotateToAngle(float angle)
{

}
void ServoMotor::setParams(float default_angle = 90, int min_pulse_width = 544, int max_pulse_width = 2400)
{

}

float ServoMotor::saturateAngle(float angle)
{
    if (_default_angle + angle > 180.0)
    {
        return 180.0
    }
    else if (_default_angle - angle < 0.0)
    {
        return 0.0
    }
    else
        return _default_angle + angle;
}