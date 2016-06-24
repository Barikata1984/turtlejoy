//-------------------------------------
//	- - - - - difinitions.h - - - - - -
//-------------------------------------

#ifndef	__DEFINITIONS_H__
#define	__DEFINITIONS_H__

#define FREQUENCY  40
#define PERIOD	   20
#define TICK	 1024 

// define gpio pins to control motors
#define	R_1		   11
#define	R_2			9
#define R_PWM	   12	// set the revolution speed of the right motor
#define L_1		   22
#define L_2		   27
#define L_PWM	   18	// set the revolution speed of the left motor

#define	RIGHT	 	0
#define	LEFT	 	1
#define PIN_1	 	0	// the 1st pin for the motor
#define PIN_2	 	1	// the 2nd pin for the motor
#define PIN_PWM	 	2	// the pwm pin for the motor

#define PWM_CLOCK	 400	
#define PWM_RANGE	1024

#endif
