#ifndef _SWERVEMODULE_
#define _SWERVEMODULE_

#include "hardware/motor.h"
#include "hardware/rotsensor.h"
#include "utils/pid.h"

#define MIN_MOTOR_SPEED 50 // 0 -> 255
#define MIN_POT 910
#define MAX_POT 63518

/**
 * 1/4th of a classic swerve drive, or 1/2 of a differential swerve drive.
 * 
 * Swerve drive is a type of robotic drivetrain that acts as "controllable caster wheels".
 * This allows for unparalleled grip and control compared to other omnidirectional drivetrains.
 * 
 * Each module consists of a wheel, and a rotating platform connected to motors and geared together in a 
 * way that allows control over a wheel's speed and pointing direction.
 */
class SwerveModule
{
  public:

  /**
   * Create a single swerve module, which consists of a direction motor, a drive motor, and a potentiometer
   * @param dir Motor controlling the direction of the wheel
   * @param drive Motor controlling the speed of the wheel
   * @param sensor A custom potentiometer wrapper with re-mapped inputs
   * @param dir_pid_config PID configuration controlling the movements of the Direction motor
   */
  SwerveModule(Motor &dir, Motor &drive, RotSensor &sensor, PID::pid_config_t &dir_pid_config);

  /**
   * Set the direction of motor using a PID loop
   * 
   * Actual precision is limited to 10 bits from the ADC
   * 
   * @param bams Angle to be set to, in 16 bit BAMS
   */
  bool set_dir(uint16_t degrees);

  /**
   * Rotate the drive motor
   * @param val -255 -> 255
   */
  bool set_speed(int16_t percent);

  private:
  
  Motor &dir, &drive;
  RotSensor &sensor;
  
  PID dir_pid;
};

#endif
