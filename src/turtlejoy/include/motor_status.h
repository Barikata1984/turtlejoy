//-------------------------------------
//	- - - - - - TurtleJoy - - - - - -
//-------------------------------------
//	This code is written based on the sample code from
//	"http://forestofazumino.web.fc2.com/" and 
//	modified by Barikata1984

#include <wiringPi.h>
#include <vector>
#include "definitions.h"

//#ifndef	__MOTOR_STATUS_H_INCLUDED__
//#define	__MOTOR_STATUS_H_INCLUDED__

using namespace std;

class motor_status{
private:
	int				current_flag;
	int				past_flag;
	vector<int>	pin_num;
	int				rev;
public:
	// constructors
	motor_status();
	motor_status(char pin_1, char pin_2, char pin_pwm);
	
	// the functions defined in source file.
	void	set_current_flag(int read_rev);
	int		check_flags();
	void	driver(int command);
	
	// inline menber function
	int			get_current_flag(){return current_flag;};
	void		set_past_flag(){past_flag = current_flag;};
	int			get_past_flag(){return past_flag;};
	vector<int>	get_pin_num(){return pin_num;};
	void		set_rev(int read_command){rev = read_command;};
	int			get_rev(){return rev;};
};

//#endif
