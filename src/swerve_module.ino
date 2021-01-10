#include "hardware/rotsensor.h"
#include "hardware/motor.h"
#include "subsystems/swerve_module.h"

struct PID::pid_config_t dir_config
{
  .p=.04, .d=.002
};

RotSensor pot(A0);
Motor dir(4, 5), drive(2, 3);
SwerveModule mod(dir, drive, pot, dir_config);

void setup() {

  Serial.begin(115200);

  pinMode(A0, INPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);

  pot.remap(235, 770, 90, 270);
  pot.set_inverted(true);

}

uint16_t setpt = 180 * (UINT16_MAX / 360);

void loop() {
  // Serial.println(map(((analogRead(A0) / 1023.0) * 360), 80, 272, 90, 270));

  if (Serial.available() > 0)
  {
    char buffer[20];
    Serial.readBytes(buffer, 20);
    setpt = atoi(buffer) * (UINT16_MAX / 360);
  }

  // Serial.println(pot.get_bams());

  mod.set_dir(setpt);

  // drive.set_speed(245);

  // dir.set_speed(50);

  delay(10);
}
