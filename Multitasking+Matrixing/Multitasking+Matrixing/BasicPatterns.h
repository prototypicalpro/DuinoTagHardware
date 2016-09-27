/*
 * BasicPatterns.h
 *
 * Created: 9/25/2016 4:23:26 PM
 *  Author: Noah
 *
 * This file will detail the syntax for creating simple lighting patterns
 * And hopefully have a way to display them all at once
 */

#include <avr/pgmspace.h>

#ifndef BASICPATTERNS_H_
#define BASICPATTERNS_H_

#define animationNum (sizeof(animationStore) / sizeof(animationStore[0]))

typedef const uint8_t PROGMEM animation_t;

//below are commands understood by the interpreter
enum lightCommands{
	L_SET_POWER, //set light power, from 0 - 10
	L_DELAY,  //add a delay in the animation, in tens of milliseconds
	L_RAND = 255, //replace with a random number between 1 and 10
	L_RAND_FLICKER = 254, //replace with a random number, but only 1 or 10
};

animation_t animationStore[][10] = { //array which stores the animations
	{
		L_SET_POWER, 10,  //turn the LED on
		L_DELAY, 10,  //delay for 100 millis
		L_SET_POWER, L_RAND, //set the power to a random number between 0 and 1
		L_DELAY, 10, //delay for another 100 millis
	}, //and repeat
	{
		L_SET_POWER, 10,
		L_DELAY, L_RAND,
		L_SET_POWER, 0,
		L_DELAY, 5,
	},
	{
		L_SET_POWER, 5,
		L_DELAY, 100,
		L_SET_POWER, 0,
		L_DELAY, 5,
	},
	//insert as many as you like here
};

#endif /* BASICPATTERNS_H_ */