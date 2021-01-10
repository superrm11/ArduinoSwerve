#ifndef _ROTSENSOR_
#define _ROTSENSOR_

#include "Arduino.h"

#define BAM_270 49152
#define BAM_180 32767
#define BAM_90 16384

class RotSensor
{
  public:
  RotSensor(const uint8_t analog_pin);

  void remap(int min, int max, int new_min, int new_max);

  int get_deg();

  uint16_t get_bams();

  void set_inverted(bool is_inverted);

  private:
  
  int pin;
  
  int min = 0, max = 1023;
  int new_min = 0, new_max = 1023;
  uint16_t bam_min = 0, bam_max = UINT16_MAX;

  bool is_inverted = false;

};

#endif
