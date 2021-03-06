# Arduino Office Sign


My humble setup for driving a character LCD.

## Hardware used
* Arduino Ethernet
* [i2c LCD backpack](http://www.adafruit.com/products/292) (for fewer wiring)
* [20x4 character LCD](http://www.adafruit.com/products/498)
* [Ribbon cable](https://www.sparkfun.com/products/10647)
* [0.1" crimp pins](http://www.pololu.com/product/1931)
* [0.1" crimp housing](http://www.pololu.com/product/1900)

## Arduino libraries used
Put the following libraries in `~/Documents/Arduino/libraries` on Mac OS X (or follow instructions [here](http://arduino.cc/en/Guide/Libraries).)

* [Time](http://playground.arduino.cc/Code/Time)
* [Timezone](https://github.com/JChristensen/Timezone)
* [LiquidTWI2](https://github.com/lincomatic/LiquidTWI2)