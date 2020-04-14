## Controlling LEDs

By using a potentiometer, and reading its analog values to toggle which LEDs light up according to its variable resistance.

More info on Potentiometer [here](https://www.arduino.cc/en/tutorial/potentiometer).

## Notes

By convention attach the cathode (short leg) of each of the LEDs to ground through a 220-ohm resistor. Note that the resistor can be on either side of the LED, but it **must** be present. When two or more components are in series, the current will be the same through all of them, and so it doesn't matter which order they are in.

Because LEDs are current dependent, it's usually necessary to protect them from excessive current with a series resistor. Some LEDs include a built-in series resistor. **Most do not**.

## Circuit Diagram

Made in [Tinkercad](https://www.tinkercad.com)

<img src="https://github.com/nayfusaurus/arduino-learning-project/blob/master/1.%20Controlling_LEDs/Controlling_LEDs_Circuit_Diagram.png" width="175">

## Demo

![](Controlling_LEDs_Demo.gif)
