# windowed-couscous

## Objective
The main objective of the project is to control state of the window with AC motor, dependent on the temperature inside a room. 

## Communication with the user
Device is supplied with the LCD screen in which user can check the current room temperature, operating mode and settings. Operating mode is being changed with 3-step switch.
Device has also two push-buttons, with which user can set up the temperature above which window will be open and below which it will be closed. He can also change the interval of the temperature check. 

## Circuit
![diagram](https://github.com/kajedot/windowed-couscous/assets/22113075/d5ba23b2-9bff-47c0-96fa-43f63a085970)

## Max power consumption calculation
- Arduino Nano: 280 mA [src](https://arduino.stackexchange.com/questions/926/what-is-the-maximum-power-consumption-of-the-arduino-nano-3-0)
- LCD WD-C1602M: 3 mA (datasheet)
- Relay x2: 122 mA (measured)
SUM: 405 mA
