#ifndef _PID_
#define _PID_

#include "Arduino.h"

class PID
{
public:
  struct pid_config_t
  {
    float p, i, d, f;
    float deadband;
    uint16_t on_target_time;
  };

  /**
   * Create the PID object
   */
  PID(pid_config_t &config);

  /**
   * Update the PID loop by taking the time difference from last update,
   * and running the PID formula with the new sensor data
   */
  void update(float sensorVal);

  /**
   * Reset the PID loop by resetting time since 0 and accumulated error.
   */
  void reset();

  /**
   * Gets the current PID out value, from when update() was last run
   */
  float get();

  /**
   * Get the delta between the current sensor data and the target
   */
  float get_error();

  /**
   * Set the target for the PID loop, where the robot is trying to end up
   */
  void set_target(float target);

  /**
   * Set the limits on the PID out. The PID out will "clip" itself to be 
   * between the limits.
   */
  void set_limits(float lower, float upper);

  /**
   * Returns true if the loop is within [deadband] for [on_target_time]
   * seconds
   */
  bool is_on_target();

private:
  pid_config_t &config;

  float last_error = 0, accum_error = 0;
  float last_time = 0, on_target_last_time = 0;
  float lower_limit = 0, upper_limit = 0;

  float target = 0, sensor_val = 0, out = 0;
  bool is_checking_on_target = false;
};

#endif
