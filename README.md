# ArduinoSwerve
A scale model swerve drive powered by Arduino

This will be a module in the 3rd iteration of my 3D printed robots; this time with a *true* swerve drive. The final bot will be controlled via a Raspberry Pi,
however due to a lack of hardware PWM and an ADC, an arduino was chosen to govern the drivetrain. Eventually it will communicate with the Pi via I2C/SPI/Serial, TBD.

Hardware development documentation will be coming soon.

# Building
This project uses the [Arduino-Makefile](https://github.com/sudar/Arduino-Makefile) build system rather than the default Arduino IDE. This allows for a more traditional C/C++ project structure due to scale of the project. Follow the installation instructions there and make sure the ARDMK_DIR environment variable is properly set. Then it's just:

```
cd src/
make
make upload
```
