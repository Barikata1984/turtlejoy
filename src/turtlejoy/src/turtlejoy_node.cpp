//-------------------------------------
//	- - - - - - TurtleJoy - - - - - -
//-------------------------------------
//	This code is written based on the sample code from
//	"http://forestofazumino.web.fc2.com/" and 
//	modified by Barikata1984

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <math.h>
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <wiringPi.h>
#include <vector>
//#include "difinitions.h"
//#include "motor_status.h"

using namespace std;

#define FREQUENCY	  20
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
#define INDEX	 0
#define VALUE	 1

//bool set;
int left_rev;;
int right_rev;

class motor_status{
private:
	char		current_flag;
	char		past_flag;
	vector<int>	pin_num(3);
public:
	// constructor
	motor_status::motor_status{
		current_flag = 0;
		past_flag = 0;
		pin_num = {0, 0, 0};
	}

	// constructors with arguments
	motor_status::motor_status(int P_1, int P_2, int P_PWM){
};

// callback function
void messageCallBack(const geometry_msgs::Twist& twist);

// initialize gpio pins
int init_gpio();

// obtain revolution direction flag from pwm command
int get_flag(int read_rev);

// main loop.
int main(int argv, char **argc){
	vector<motor_status>	motors(2);
	vector<vector<vector<int> > >	motor_status{
		{		// the right motor
			{R_1, 0}, {R_2, 0}, {R_PWM, 0},
		}, {	//	the left motor
			{L_1, 0}, {L_2, 0}, {L_PWM, 0},
		}					
	};
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
	ros::Subscriber sub = nh.subscribe("/joy0", 1000, &messageCallBack);
	ros::Rate rate(FREQUENCY);		// set frequency.
 
 	// repeat till <C-c> is inputted.
	while(ros::ok()){
		R_current_flag = get_flag(right_rev);
		if(R_current_flag != R_past_flag){
			switch(R_current_flag){
			case -1:
				digitalWrite(R_1, 0);
				digitalWrite(R_2, 1);
//				pwmWrite(R_PWM, abs(right_rev));
			case 0:
				digitalWrite(R_1, 0);
				digitalWrite(R_2, 0);
//				pwmWrite(R_PWM, abs(right_rev));
			case 1:
				digitalWrite(R_1, 1);
				digitalWrite(R_2, 0);
//				pwmWrite(R_PWM, 0);
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

		R_past_flag = R_current_flag;

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

	ROS_INFO_STREAM("");
	ROS_INFO_STREAM("");
	ROS_INFO_STREAM("_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/");
	ROS_INFO_STREAM("L-Rev-COMMAND: " << left_rev);
	ROS_INFO_STREAM("R-Rev-COMMAND: " << right_rev);
	ROS_INFO_STREAM("_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/");
	ROS_INFO_STREAM("");
	ROS_INFO_STREAM("");
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

int get_flag(int read_rev){
	if(read_rev==0){
		return 0;
	}else{
		return read_rev / abs(read_rev);
	}
}





