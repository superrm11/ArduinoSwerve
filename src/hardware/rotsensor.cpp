#include "hardware/rotsensor.h"

RotSensor::RotSensor(const uint8_t analog_pin)
: pin(analog_pin)
{

}

void RotSensor::remap(int min, int max, int new_min, int new_max)
{
    this->min = min;
    this->max = max;
    this->new_min = new_min;
    this->new_max = new_max;
}

int RotSensor::get_deg()
{
    if( is_inverted )
        return map(analogRead(pin), min, max, new_max, new_min);

    return map(analogRead(pin), min, max, new_min, new_max);
}

uint16_t RotSensor::get_bams()
{
    if( is_inverted )
        return get_deg() * (UINT16_MAX / 360);
}

void RotSensor::set_inverted(bool is_inverted)
{
    this->is_inverted = is_inverted;
}