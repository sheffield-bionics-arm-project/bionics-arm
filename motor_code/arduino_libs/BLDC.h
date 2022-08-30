/*
  BLDC.C - Library for controlling a BLDC motor. 
  To be used for Arduino.
  Created by David Wilkinson (Sheffield Bionics) 23-08-2022.
  Released into the public domain.
*/

#ifndef BLDC_H
#define BLDC_H

#include "Arduino.h"

class BLDC
{
  public:
    BLDC(int pin_Ah, int pin_Al, int pin_Bh, int pin_Bl, int pin_Ch, int pin_Cl);
    void rampUpSpeedDutyCycle(int init_period, int final_period, int ramp_delay);
    void trapezoidalControl(float angle);
    void stepOnce();
    void synchronize();                                         //used for initialization to synchronize position
    int duty_cycle, ramp_done;

  private:
    int _pin_Ah, _pin_Al, _pin_Bh, _pin_Bl, _pin_Ch, _pin_Cl;   // gate driver pins
    int _counter, _commutation_period;              // vars for open-loop control
    unsigned long _last_switch_time,                            // time that previous switch event occurred
};

#endif