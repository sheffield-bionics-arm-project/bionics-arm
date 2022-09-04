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
        ServoMotor(float default_angle = 90);
        void rotateThroughAngle(float angle);
        void rotateToAngle(float angle);
        void setParams(int pin, float task_freq, float ang_spd = 180.0, float default_angle = 90.0, int min_pulse_width = 544, int max_pulse_width = 2400);
        void setAngSpdDeg(float ang_spd_deg);
        void checkMove();                   // function used to check whether movement operation is complete, else enter move fcn


    private:
        int _default_angle, _pin;           // deg, default angle used for rotation relative to this | arduino pin used for control signal
        float _curr_angle;                  // deg, current angle of Servo. used for rated move operations
        float _req_angle;                   // deg, requested angle for Servo. used for movement operation checking
        float _angle_increment;             // deg, determined by desired angular speed
        float _task_freq;                     // kHz, frequency at which servomotor functions are called in background tasks
        int _moving;                        // boolean, signifies whether a move operation is in progress
        unsigned long _move_start_time;     // ms, start time of movement. used to conform to angular speed
        float saturateAngle(float angle);   // function used to saturate angle request to between 0/180deg
        void rotate();                      // function used to rotate servo by increment if rotate move needed;
};

#endif