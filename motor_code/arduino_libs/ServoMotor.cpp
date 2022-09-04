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
    _task_freq = 10;
    ServoMotor::setAngSpdDeg(180);
}

void ServoMotor::rotateThroughAngle(float angle)
{
    angle = ServoMotor::saturateAngle(ServoMotor::read() + angle);
    _req_angle = angle;
}

void ServoMotor::rotateToAngle(float angle)
{
    angle = ServoMotor::saturateAngle(angle + _default_angle);
    _req_angle = angle;
}

void ServoMotor::setParams(int pin, float task_freq, float ang_spd = 180.0, float default_angle = 90.0, int min_pulse_width = 544, int max_pulse_width = 2400)
{
    _default_angle = default_angle;
    ServoMotor::attach(pin, min_pulse_width, max_pulse_width);
    _task_freq = task_freq;
    ServoMotor::setAngSpdDeg(ang_spd);
}

void ServoMotor::setAngSpdDeg(float ang_spd)
{
    // increment is determined by task frequency and desired angular speed
    //  task_freq in kHz, ang_spd in deg/s
    //  number of possible rotation calls per second 'n' = task_freq * 1000
    // to get increment per rotation, 
    //  ang_spd / n
    _angle_increment = ang_spd / (1000.0 * _task_freq);
    Serial.println(_angle_increment);
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

void ServoMotor::checkMove()
{
    _moving = abs(_req_angle - _curr_angle) > _angle_increment ? 1 : 0; 
    if (_moving)
    {
        ServoMotor::rotate();
    }
    
}

void ServoMotor::rotate()
{
    float _new_angle;
    if (_req_angle > _curr_angle)
    {
        _new_angle = _curr_angle + _angle_increment;
    }
    else if (_req_angle < _curr_angle)
    {
        _new_angle = _curr_angle - _angle_increment;
    }
    
    ServoMotor::write(_new_angle);
    _curr_angle = _new_angle;
}