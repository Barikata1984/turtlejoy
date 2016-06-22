//-------------------------------------
//	- - - - - - TurtleJoy - - - - - -
//-------------------------------------
//	This code is written based on the sample code from
//	"http://forestofazumino.web.fc2.com/" and 
//	modified by Barikata1984

#include <wiringPi.h>
#include <stdlib.h>
#include <vector>
#include "motor_status.h"

using namespace std;

motor_status::motor_status(){
	current_flag = 0;
	past_flag = 0;
	pin_num = {0, 0, 0};
	rev = 0;
}

motor_status::motor_status(char pin_1, char pin_2, char pin_pwm){
	current_flag = 0;
	past_flag = 0;
	pin_num = {pin_1, pin_2, pin_pwm};
	rev = 0;
}

void motor_status::set_current_flag(int read_rev){
	if(read_rev==0){
		current_flag = 1;
	}else{
		current_flag = ((read_rev / abs(read_rev)) + 1);
	}
}

int motor_status::check_flags(){
	if(current_flag==past_flag){
		return 1;
	}else{
		return 0;
	}
}

void motor_status::driver(int command){
	set_rev(command);
	set_current_flag(rev);
	if(check_flags()){
		switch(get_current_flag()){
		case 0:
			digitalWrite(pin_num[PIN_1], 0);
			digitalWrite(pin_num[PIN_2], 1);
			break;
//			ROS_INFO_STREAM("Hi!");
		case 1:
			digitalWrite(pin_num[PIN_1], 0);
			digitalWrite(pin_num[PIN_2], 0);
			break;
//			ROS_INFO_STREAM("It's!!");
		case 2:
			digitalWrite(pin_num[PIN_1], 1);
			digitalWrite(pin_num[PIN_2], 0);
			break;
//			ROS_INFO_STREAM("Me!!!");
		}	
	}
	pwmWrite(PIN_PWM, abs(rev));
	set_past_flag();
}
