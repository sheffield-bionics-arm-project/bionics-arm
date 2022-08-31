/*
  ServoMotor.h - Library for controlling a servo motor using the
   Arduino Servo library.
  Created by David Wilkinson (Sheffield Bionics) 31-08-2022.
  Released into the public domain.
*/

#ifndef SERVOMOTOR_H
#define SERVOMOTOR_H

#include "Arduino.h"
#include <Servo.h>

class ServoMotor : public Servo
{
    public:
        ServoMotor(int pin, float default_angle = 90, int min_pulse_width = 544, int max_pulse_width = 2400);
        void rotateThroughAngle(float angle);
        void rotateToAngle(float angle);
        void setParams(float default_angle = 90, int min_pulse_width = 544, int max_pulse_width = 2400);

    private:
        int _default_angle;
        float saturateAngle(float angle);
};

#endif