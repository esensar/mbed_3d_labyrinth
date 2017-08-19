# 3D Labyrinth game for embedded system

## Introduction

3D labyrinth game written for university project.  
Originally built on [mbed](https://www.mbed.com/en/) compiler with my colleague [Dino Dizdarević](https://github.com/dizda13). [(Link to original mbed repository)](https://developer.mbed.org/users/pai2015dinodizdarevi/code/NoviLabirnt3D/)  
Game used Nokia 5110 LCD display and generic joystick for controls.  
Check out the demo video: https://www.youtube.com/watch?v=8I6GM97ciso

## Requirements

Originally compiled for [LPC1114FN28](https://developer.mbed.org/users/ytsuboi/notebook/getting-started-with-mbed-lpc1114/) platform, but it should be runnable on anything that can support the LCD display and generic joystick (with minor code modifications due to pins being hardcoded).
Besides the platform, only Nokia 5110 LCD display and generic joystick is required.

### Pin setup

The following image shows the pins of used platform.
![LPC1114FN28 pins](https://developer.mbed.org/media/uploads/okano/pinout_dip28-20131006-.png)

Used pins:
 * dp1 used as digital input - used as a switch to start playing the game
 * dp10 and dp11 used as analog inputs for joystick, dp10 for y axis and dp11 for x axis
 * dp4, dp24, dp23, dp25, dp2, dp6, dp18 used for Nokiad 5110 LCD (in this order)
 
### Controls

For all controls, only joystick is used and the switch included on platform (if it is not, it should be used connected to a digital input pin).
Before switching the game on, simple looping animation is displayed, switching between different images that are used to draw all possible combinations of visible walls in the game.
Once the switch is pressed the game starts. To move forward, simply move the joystick up. Holding it up will cause that action to repeat. Walking into walls will just return the player to the same position.
Moving joystick left and right will make the player turn in place. Moving joystick down opens up the map, which will display player as an arrow.

## Code blocks explanation

Before explaining the code, I know there are many things that should have been done differently and there are many bad coding practices,
but I wanted to leave the code in its original state. At that point we were satisfied with it just working.

## TODO - Cleaning up the repository  
- [x] Upload to GitHub from mbed  
- [ ] Add windows console adaptation  
- [ ] Add unix console adaptation  
- [ ] Translate parts of code not written in english  
- [x] Add a more detailed documentation with images  
- [ ] Explain codes of block
