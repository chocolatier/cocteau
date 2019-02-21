# Build Instructions 

## Rover Wiring

First, build the DFRobot Pirate according to the instructions [here](https://www.dfrobot.com/wiki/index.php/Pirate_4WD_Mobile_Platform_SKU:ROB0003). Disregard the instruction manual that came with the kit. The above wiki is a lot more detailed, and also has guide on wiring.  

Before you attach the 2nd plate, wire the additional sensors and servos to the Romeo Microcontroller. 

### Mini Pan-and-Tilt Hat 

Attach the Pan Wire to Digital Input 8

Attach the Tilt Wire to Digital Input 7


### Sharp GP2Y0A21YK0F 

Plug the 3 Pin Cable in first. Then wire the live (red wire) to 5V, the ground (black wire) to GND and the analog (white wire) to A0. 

### DFRobot 10cm infrared sensor

Attach it to one of the three pin Digital Input Sets - I have used 2. 

![Wiring](images/wiring.jpg)

## Mounts 

### Sharp GP2Y0A21YK0F 

Construct a triangle out of cardboard, and tape the sensor onto one side. !

![Cardboard](images/cardboard.jpg)

Tape the other side to the bottom of the sensor plate. (See image below)

### Pan and Tilt Hat 

Tape it onto the top of the sensor plate. 

Make sure that it is oriented correctly, so that when the panning servo is centered, it points towards the front of the rover. 

![Sensor Plate](images/sensor_plate.jpg)

