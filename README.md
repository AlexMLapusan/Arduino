
# Arduino Project

This is my attempt to simulate a theremin on an Arduino. In addition, there are tunes incorporated ('Mario theme' and the chorus of 'Never gonna give you up')


# Necessary components
You will need the following: <br/>
2 x Photoresistor 5528; <br/>
5 x Resistors: 2 x 10K; <br/>
1 x 1K, 2 x 330 ohm; <br/>
1 x Button; <br/>
2 x Led; <br/>
1 x Speaker; <br/>
Connecting wires. <br/>

# Schematic
The scheme can be found in the Scheme.jpg file:
https://github.com/AlexMLapusan/Arduino/blob/master/Schematic.jpg


## Implementation
In this project I am using an additional library that allows the use of the function tone with 2 parameters (frequency and volume), more information can be found here https://github.com/connornishijima/arduino-volume1#installation. 
Also there are two header files, pitches.h and songs.h, in which are defined the notes and their frequencies, respectively the code for playing the songs.

## How to use
The project's goal is to allow you to control the volume and the frequency of a speaker with the help of 2 photoresistors.
Using this project is pretty straight forward. The first 5 seconds after turning the board on are used to calibrate the photoresistors, in this phase you should put as much and as little light as possible on both photoresistors so that the minimum and maximum frequency/volume can be assessed properly.
After the calibration period you will be able to control the volume with the left photoresistor and the frequency with the one on the right (I chose the frequencies to be the 89 pitches from the pitch.h file but that can be easily changed).
There are 3 states, the first is the theremin, the second one plays the 'Mario theme' and the third 'Never gonna give you up'. These states are changed by pressing the button. 
