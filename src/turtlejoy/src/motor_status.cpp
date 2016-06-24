//-------------------------------------
// - - - - - motor_status.h - - - - - -
//-------------------------------------

#include <wiringPi.h>
#include <stdlib.h>
#include <vector>
#include "motor_status.h"
#include <ros/ros.h>

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
	if(abs(read_rev)<64){
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

void motor_status::driver(int write_command){
	set_rev(write_command);
	set_current_flag(rev);
//	ROS_INFO_STREAM("I'm moving!!!!");
	if(check_flags()){
	//	ROS_INFO_STREAM("I'm moving!!!!");
		switch(get_current_flag()){
		case 0:
			digitalWrite(pin_num[PIN_1], 0);
			digitalWrite(pin_num[PIN_2], 1);
//			ROS_INFO_STREAM("Hi!");
			break;
		case 1:
			digitalWrite(pin_num[PIN_1], 0);
			digitalWrite(pin_num[PIN_2], 0);
//			ROS_INFO_STREAM("It's!!");
			break;
		case 2:
			digitalWrite(pin_num[PIN_1], 1);
			digitalWrite(pin_num[PIN_2], 0);
//			ROS_INFO_STREAM("Me!!!");
			break;
		}	
	}
	pwmWrite(pin_num[PIN_PWM], abs(rev));
	set_past_flag();
}
