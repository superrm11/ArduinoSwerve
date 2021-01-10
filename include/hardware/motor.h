#ifndef _MOTOR_
#define _MOTOR_

#include "Arduino.h"

class Motor
{
  public:
  Motor(int pin1, int pin2);

  /**
   * Set the speed of the motor
   * @param speed -255 -> 255
   */
  void set_speed(int16_t speed);

  /**
   * Set whether the motor is revesered. False by default.
   */
  void set_inverted(bool inverted);

  private:

  const uint8_t pin1, pin2;
  bool inverted = false;

};

#endif
