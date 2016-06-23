//-------------------------------------
//	- - - - - - TurtleJoy - - - - - -
//-------------------------------------
//	This code is written based on the sample code from
//	"http://forestofazumino.web.fc2.com/" and 
//	modified by Barikata1984

#ifndef	__DEFINITIONS_H__
#define	__DEFINITIONS_H__

#define FREQUENCY	  40
#define PERIOD		  20
#define TICK		1024 

// define gpio pins to control motors
#define	R_1		11
#define	R_2		 9
#define R_PWM	12	// the pin set the revolution speed of the right motor
#define L_1		22
#define L_2		27
#define L_PWM	18	// the pin set the revolution speed of the left motor

#define	RIGHT	 0
#define	LEFT	 1
#define PIN_1	 0	// the pin set the revolution speed of the right motor
#define PIN_2	 1	// the pin set the revolution speed of the right motor
#define PIN_PWM	 2	// the pin set the revolution speed of the right motor

#define PWM_CLOCK	 400	
#define PWM_RANGE	1024

#endif
