## Issue

At 100 or 400 kHz, the sensor always disconnect when motors are running.
It is problably because of parasites.

My theory is that the 10k pull-up resistors on SDA and SCL on the PCB board are too high and should be replaced with 2k as recommended in the VL53L0X official documentation.

See R3 and R4 on `VL53L0X - Schematic - 47k are in fact 10k.jpg`.

I tried to solder new resistors in place bug pads are too small and it didn't worked :(


## Resources

https://cookierobotics.com/037/
https://electronics.stackexchange.com/questions/369801/removing-pull-up-resistors-from-breakout-board

