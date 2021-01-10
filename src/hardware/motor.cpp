#include "hardware/motor.h"

Motor::Motor(int pin1, int pin2): pin1(pin1), pin2(pin2)
{

}

/**
 * Set the speed of the motor
 * @param speed -255 -> 255
 */
void Motor::set_speed(int16_t speed)
{
    // Limit the speed between -255 and 255
    speed = (speed > 255) ? 255 : (speed < -255) ? -255 : speed;

    // Decide if pin1 is PWM and pin2 is OFF, or vice versa
    bool set_pin_1 = (inverted && speed > 0) || (!inverted && speed < 0);
    bool set_pin_2 = (!inverted && speed > 0) || (inverted && speed < 0);

    if(set_pin_1)
    {
        analogWrite(pin1, abs(speed));
        digitalWrite(pin2, 0);
    } else if(set_pin_2)
    {
        digitalWrite(pin1, 0);
        analogWrite(pin2, abs(speed));
    } else
    {
        digitalWrite(pin1, 0);
        digitalWrite(pin2, 0);
    }

}

void Motor::set_inverted(bool inverted)
{
    this->inverted = inverted;
}