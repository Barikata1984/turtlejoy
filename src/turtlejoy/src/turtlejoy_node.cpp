//-------------------------------------
//	- - - - - - TurtleJoy - - - - - -
//-------------------------------------
//	This code is written based on the sample code from
//	"http://forestofazumino.web.fc2.com/" and 
//	modified by Barikata1984

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <wiringPi.h>
#include <vector>

using namespace std;

#define FREQUENCY	  30
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

int	right_rev;
int	left_rev;

class motor_status{
private:
	int			current_flag;
	int			past_flag;
	vector<char>	pin_num;
	int				rev;
public:
	// constructor
	motor_status();
	motor_status(char pin_1, char pin_2, char pin_pwm);
	
	void set_current_flag(int read_rev);	// this function is defined below
	int	get_current_flag(){return current_flag;};

	void set_past_flag(){past_flag = current_flag;};
	int get_past_flag(){return past_flag;};

	int check_flags();	// this function is defined bellow

	void set_rev(int read_command){rev = read_command;};
};

motor_status::motor_status(){
//motor_status::motor_status() : pin_num(3, {0, 0, 0}){
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

//		R_current_flag = get_flag(right_rev);
//		if(R_current_flag != R_past_flag){
//			switch(R_current_flag){
//			case -1:
//				digitalWrite(R_1, 0);
//				digitalWrite(R_2, 1);
//			case 0:
//				digitalWrite(R_1, 0);
//				digitalWrite(R_2, 0);
//			case 1:
//				digitalWrite(R_1, 1);
//				digitalWrite(R_2, 0);
//			}	
//		}
//		pwmWrite(R_PWM, abs(right_rev));
//		
//		R_past_flag = R_current_flag;


// callback function
//void messageCallBack(const geometry_msgs::Twist &twist, vector<motor_status> &read_motors);
void messageCallBack(const geometry_msgs::Twist &twis);

// initialize gpio pins
int init_gpio();

// main loop.
int main(int argv, char **argc){
	vector<motor_status>	motors{motor_status(R_1, R_2, R_PWM), motor_status(L_1, L_2, L_PWM)};
	left_rev = 0;
	right_rev = 0;

	ros::init(argv, argc, "turtlereal3_node");
	ros::NodeHandle nh;
	
	//------------------------------------------
	ROS_INFO_STREAM("Hi! me's the Turtlejoy!!");
	//------------------------------------------

	init_gpio();
	
	//------------------------------------------
	ROS_INFO_STREAM("GPIO initialized");
	//------------------------------------------

	// genetate subscriber
//	ros::Subscriber sub = nh.subscribe<geometry_msgs::Twist>("/joy0", 1000, boost::bind(messageCallBack, _1, &motors));
	ros::Subscriber sub = nh.subscribe("/joy0", 1000, messageCallBack);
	ros::Rate rate(FREQUENCY);		// set frequency.
 
 	// repeat till <C-c> is inputted.
	while(ros::ok()){
		motors[RIGHT].set_current_flag(right_rev);
//		right_flag = motors[RIGHT].get_current_flag();
		cout << "right_flag is" << motors[RIGHT].get_current_flag() << endl;
		if(motors[RIGHT].check_flags()){
			switch(motors[RIGHT].get_current_flag()){
			case 0:
				digitalWrite(R_1, 0);
				digitalWrite(R_2, 1);
				break;
				ROS_INFO_STREAM("Hi!");
			case 1:
				digitalWrite(R_1, 0);
				digitalWrite(R_2, 0);
				break;
				ROS_INFO_STREAM("It's!!");
			case 2:
				digitalWrite(R_1, 1);
				digitalWrite(R_2, 0);
				break;
				ROS_INFO_STREAM("Me!!!");
			}	
		}
		pwmWrite(R_PWM, abs(right_rev));
		
//		if(left_rev > 128){
//			digitalWrite(L_1, 1);
//			digitalWrite(L_2, 0);
//			pwmWrite(L_PWM, abs(left_rev));
//		}else if(left_rev < -128){
//			digitalWrite(L_1, 0);
//			digitalWrite(L_2, 1);
//			pwmWrite(L_PWM, abs(left_rev));
//		}else{
//			digitalWrite(L_1, 0);
//			digitalWrite(L_2, 0);
//			pwmWrite(L_PWM, 0);
//		}

		motors[RIGHT].set_past_flag();
		
		ros::spinOnce();
		rate.sleep();
	}

	pinMode(R_1, INPUT);
	pinMode(R_2, INPUT);
	pinMode(R_PWM, INPUT);

	pinMode(L_1, OUTPUT);
	pinMode(L_2, OUTPUT);
	pinMode(L_PWM, PWM_OUTPUT);

	ROS_INFO_STREAM("See you later, master.");	
	return 0;
}

// callback function
void messageCallBack(const geometry_msgs::Twist& twist) {
	left_rev	= (int)TICK * twist.linear.x;
	right_rev	= (int)TICK * twist.angular.y;

//	ROS_INFO_STREAM("_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/");
//	ROS_INFO_STREAM("L-Rev-COMMAND: " << left_rev);
//	ROS_INFO_STREAM("R-Rev-COMMAND: " << right_rev);
//	ROS_INFO_STREAM("");
}

int init_gpio() {
	wiringPiSetupGpio();

	// set pi-node for the right motor
	pinMode(R_1, OUTPUT);
	pinMode(R_2, OUTPUT);
	pinMode(R_PWM, PWM_OUTPUT);
	
	// set pi-node for the left motor
	pinMode(L_1, OUTPUT);
	pinMode(L_2, OUTPUT);
	pinMode(L_PWM, PWM_OUTPUT);

	// set pwm 
	pwmSetMode(PWM_MODE_MS);
	pwmSetClock(400);
	pwmSetRange(1023);
}

