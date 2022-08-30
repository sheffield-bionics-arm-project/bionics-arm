/*
  BLDC.C - Library for controlling a BLDC motor using a 
   L293D driver board (or similar). To be used for Arduino
  Created by David Wilkinson (Sheffield Bionics) 23-08-2022.
  Released into the public domain.
*/

#include "Arduino.h"
#include "BLDC.h"

BLDC::BLDC(int pin_Ah, int pin_Al, int pin_Bh, int pin_Bl, int pin_Ch, int pin_Cl)
{
    // setting gate driver pins to be outputs, initially low
    pinMode(pin_Ah, OUTPUT);
    pinMode(pin_Al, OUTPUT);
    pinMode(pin_Bh, OUTPUT);
    pinMode(pin_Bl, OUTPUT);
    pinMode(pin_Ch, OUTPUT);
    pinMode(pin_Cl, OUTPUT);

    digitalWrite(pin_Ah, LOW);
    digitalWrite(pin_Al, LOW);
    digitalWrite(pin_Bh, LOW);
    digitalWrite(pin_Bl, LOW);
    digitalWrite(pin_Ch, LOW);
    digitalWrite(pin_Cl, LOW);

    _pin_Ah = pin_Ah;
    _pin_Al = pin_Al;
    _pin_Bh = pin_Bh;
    _pin_Bl = pin_Bl;
    _pin_Ch = pin_Ch;
    _pin_Cl = pin_Cl;

    //_delay_amount = (unsigned long) (60.0 * 1000.0 / _steps_per_rev / speed_rpm); // delay is in ms thus * 1000, dependent on required speed
    _last_switch_time = 0;
}

BLDC::rampUp(int init_period, int final_period, int ramp_delay)
{

}