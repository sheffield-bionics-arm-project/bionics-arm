/*
  ServoMotor.c - Library for controlling a servo motor using the
   Arduino Servo library.
  Created by David Wilkinson (Sheffield Bionics) 31-08-2022.
  Released into the public domain.
*/

#include "Arduino.h"
#include "ServoMotor.h"


ServoMotor::ServoMotor(float default_angle = 90)
{
    _default_angle = default_angle;
    _curr_angle = _default_angle;
    _moving = 0;
}

void ServoMotor::rotateThroughAngle(float angle)
{
    _moving = 1;
    angle = ServoMotor::saturateAngle(ServoMotor::read() + angle);
    ServoMotor::write(angle);

    _moving = 0;
}

void ServoMotor::rotateToAngle(float angle)
{
    angle = ServoMotor::saturateAngle(angle + _default_angle);
    _req_angle = angle;
}

void ServoMotor::setParams(int pin, unsigned long moving_time = 3000, float default_angle = 90, int min_pulse_width = 544, int max_pulse_width = 2400)
{
    _default_angle = default_angle;
    ServoMotor::attach(pin, min_pulse_width, max_pulse_width);
}

void ServoMotor::setAngSpd(float ang_spd)
{
    _ang_spd = ang_spd;
}

float ServoMotor::saturateAngle(float angle)
{
    if (angle > 180.0)
    {
        return 180.0;
    }
    else if (angle < 0.0)
    {
        return 0.0;
    }
    else
        return angle;
}

float ServoMotor::checkMove()
{
    _moving = _curr_angle != _req_angle ? 1 : 0; 
    if (_moving)
    {
        ServoMotor::rotate();
    }
    
}

void ServoMotor::rotate()
{
    float new_angle;

    if ((_req_angle - _curr_angle) > _angle_increment)
    {
       new_angle
    }
    
    ServoMotor::write(angle);
}