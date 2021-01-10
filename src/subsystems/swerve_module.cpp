#include "subsystems/swerve_module.h"

/**
 * Create a single swerve module, which consists of a direction motor, a drive motor, and a potentiometer
 * @param dir Motor controlling the direction of the wheel
 * @param drive Motor controlling the speed of the wheel
 * @param sensor A custom potentiometer wrapper with re-mapped inputs
 * @param dir_pid_config PID configuration controlling the movements of the Direction motor
 */
SwerveModule::SwerveModule(Motor &dir, Motor &drive, RotSensor &sensor, PID::pid_config_t &dir_pid_config)
: dir(dir), drive(drive), sensor(sensor), dir_pid(dir_pid_config)
{
    dir_pid.reset();
    dir_pid.set_limits(-1.0, 1.0);
}

/**
 * Set the direction of motor using a PID loop
 * 
 * Actual precision is limited to 10 bits from the ADC
 * 
 * @param bams Angle to be set to, in 16 bit BAMS
 */
bool SwerveModule::set_dir(uint16_t bams)
{
    // Deal with the deadzone on the 360 pot.
    // Set the setpoint to the closest pot bound rather than a value that can't be reached.
    // Helps avoid deadzone "jitter"
    if (bams >= MAX_POT || bams <= MIN_POT)
    {
        uint16_t pot_dist_min = bams - MIN_POT;
        uint16_t pot_dist_max = bams - MAX_POT;

        pot_dist_min = (pot_dist_min > BAM_180) ? UINT16_MAX - pot_dist_min : pot_dist_min;
        pot_dist_max = (pot_dist_max > BAM_180) ? UINT16_MAX - pot_dist_max : pot_dist_max;

        if(pot_dist_max < pot_dist_min)
            bams = MAX_POT;
        else 
            bams = MIN_POT;

    }

    uint16_t current_dir = sensor.get_bams();

    // Get the distance to the new setpoint
    uint16_t bams_dist = bams - current_dir;

    // Determine +/- absolute value distance
    uint16_t abs_dist = (bams_dist > BAM_180) ? UINT16_MAX - bams_dist : bams_dist;

    // Since BAMS are unsigned, make the distance signed
    int8_t inverse = (bams_dist > BAM_180) ? -1 : 1;

    // Caste to degrees for the PID loop
    float to_pid = (((float) abs_dist) / UINT16_MAX) * 360.0 * inverse;
    dir_pid.update(to_pid);

    // Make sure the motor doesn't stall below it's min value
    int16_t out = dir_pid.get() * 255;
    out = (abs(out) < MIN_MOTOR_SPEED) ? 0 : out;

    dir.set_speed(out);
    return false;
}

/**
 * Rotate the drive motor
 * @param val -255 -> 255
 */
bool SwerveModule::set_speed(int16_t val)
{
    drive.set_speed((abs(val) > MIN_MOTOR_SPEED) ? val : 0);
    return false;
}