//-------------------------------------
// - - - - - motor_status.h - - - - - -
//-------------------------------------

#include <wiringPi.h>
#include <vector>
#include "definitions.h"

#ifndef	__MOTOR_STATUS_H_INCLUDED__
#define	__MOTOR_STATUS_H_INCLUDED__

using namespace std;

class motor_status{
private:
	int			current_flag;
	int			past_flag;
	vector<int>	pin_num;
	int			rev;

public:
	// constructors
	motor_status();
	motor_status(char pin_1, char pin_2, char pin_pwm);
	
	// the functions defined in source file.
	void		set_current_flag(int read_rev);
	int			check_flags();
	void		driver(int write_command);
	
	// inline menber function
	int			get_current_flag(){return current_flag;};
	void		set_past_flag(){past_flag = current_flag;};
	int			get_past_flag(){return past_flag;};
	int			get_pin_num(int pin_role){return pin_num[pin_role];};
	void		set_rev(int read_command){rev = read_command;};
	int			get_rev(){return rev;};
};

#endif
