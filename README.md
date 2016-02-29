# King-Kong 

##What it is?
It is a 3 meter tall robotic kingkong costume which one person can get inside, and control it. This project is done by menbers at Fablab Taipei, and supported by NTSEC. I think it is the very first time we try to make something huge, together. I personally divided this project into to part electrical and none electrical. and here I will skip the non electric part, and only contains the electric part, which mostly, is arduino involved.

##Arduino part
For the arduino part, there are three major effect needs to be produced:
* Facial expression
  * Moving eyes
  * Moving jaw and shouting effects
* Robotic stepping sound effect
* Punch lighting

### Facial expression
The moving eyes part is made by two led array, and for this part we get support and help from OpenLab community a lot. YiHung Cheng is the one who started tinkering with the code. 

### Robotic stepping sound effect
The [PCM library](http://highlowtech.org/?p=1963) presented by High-Low-Tech is an awesome trick to play audio file with arduino, without any other mp3 shields. With the libaries, you can play a 4 sec long mp3 file with Arduino uno. My stepping effect needs a little bit more than that. the effect i need consist of two part. when one feet raise up, it should generate a mechanical motion sound, and when the feet touch the ground, it need to generate a crash sound. so there are two part of audio file needs to be implemented into arduino code, that's a little be more than arduino uno can handle, so I use arduino mega. in order to use arduino mega, download the PCM libraries, and open PCM.c with text editor, find following lines:
```c
int speakerPin = 11; // for mega, you need to use pin 10.

```
change the speakerPin from 11 to 10, save it, and now with Arduino mega, we can put more audio file into Arduino.

#### Materials: 
* archade game button x 2
* Arduino mega x2
* Mini usb speaker x1


