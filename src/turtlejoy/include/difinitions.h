#define WIRINGPI_SETUP
#define WIRINGPI_SETUP_GPIO

#ifdef __INITIALIZED_WITH_WIRINGPI_SETUP__
#define	R_1		14
#define	R_2		13
#define R_PWM	26	// the pin set the revolution speed of the right motor
#define L_1		 3
#define L_2		 2
#define L_PWM	 1	// the pin set the revolution speed of the left moto
#endif

#ifdef __INITIALIZED_WITH_WIRINGPI_SETUP_GPIO__
#define	R_1		11
#define	R_2		 9
#define R_PWM	12	// the pin set the revolution speed of the right motor
#define L_1		22
#define L_2		27
#define L_PWM	18	// the pin set the revolution speed of the left moto
#endif
