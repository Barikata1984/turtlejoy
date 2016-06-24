//-------------------------------------
//	- - - - - - TurtleJoy - - - - - -
//-------------------------------------
//	This code is written based on the sample code from
//	"http://forestofazumino.web.fc2.com/" and 
//	modified by Barikata1984

#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <wiringPi.h>
#include <vector>
#include "definitions.h"
#include "motor_status.h"

using namespace std;

vector<int>	joy_commands(2, 0);

// callback function
//void messageCallBack(const geometry_msgs::Twist &twist, vector<int>::iterator write_commands);
void messageCallBack(const geometry_msgs::Twist &twis);

// handle gpio pins
int initialize_gpio(vector<motor_status> &read_motors);
int terminate_gpio(vector<motor_status> &read_motors);


// - - - - - - - - - - - - - - - -
// main loop.
// - - - - - - - - - - - - - - - -
int main(int argv, char **argc){
	vector<motor_status>	motors{
								motor_status(R_1, R_2, R_PWM),
								motor_status(L_1, L_2, L_PWM),
							};
//	vector<int>	joy_commands(2, 0);
	
	ros::init(argv, argc, "turtlejoy_node");
	ros::NodeHandle nh;
	
	//------------------------------------------
	ROS_INFO_STREAM("Hi! me's Turtlejoy!!");
	//------------------------------------------

	initialize_gpio(motors);
	
	//------------------------------------------
	ROS_INFO_STREAM("GPIO is initialized!!");
	//------------------------------------------

	// genetate subscriber
//	ros::Subscriber sub = nh.subscribe<geometry_msgs::Twist>("/joy0", 100, boost::bind(messageCallBack, _1, &joy_commands));
	ros::Subscriber sub = nh.subscribe("/joy0", 1000, messageCallBack);
	ros::Rate rate(FREQUENCY);		// set frequency.
 
 	// repeat till <C-c> is inputted.
	while(ros::ok()){
		ROS_INFO_STREAM("_/_/_/_/_/_/_/_/_/_/_/_/");
		for(int i=0; i<joy_commands.size(); i++){
			motors[i].driver(joy_commands[i]);

			switch(i){
			case RIGHT:
//				ROS_INFO_STREAM("Right: " << motors[i].get_rev());
				break;
			case LEFT:
//				ROS_INFO_STREAM("Left : " << motors[i].get_rev());
				ROS_INFO_STREAM("");
				break;
			}
		}

		ros::spinOnce();
		rate.sleep();
	}

	terminate_gpio(motors);

	ROS_INFO_STREAM("See you later, master!!");	
	return 0;
}

// callback function
void messageCallBack(const geometry_msgs::Twist &twist) {
//void messageCallBack(const geometry_msgs::Twist &twist, vector<int>::iterator write_command){
	joy_commands[RIGHT]	= (int)(TICK * twist.angular.y);
	joy_commands[LEFT]	= (int)(TICK * twist.linear.x);

//	ROS_INFO_STREAM("_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/");
//	ROS_INFO_STREAM("R-Rev-COMMAND: " << joy_commands[RIGHT]);
//	ROS_INFO_STREAM("L-Rev-COMMAND: " << joy_commands[LEFT]);
//	ROS_INFO_STREAM("");
}

int initialize_gpio(vector<motor_status> &read_motors) {
	wiringPiSetupGpio();	// the function from "wiringPi.h" used to setup gpio pins. This function must be used with root authorization. 

	for(int i=0; i<read_motors.size(); i++){
		// set pi-node for the right motor
		pinMode(read_motors[i].get_pin_num(PIN_1), OUTPUT);
		pinMode(read_motors[i].get_pin_num(PIN_2), OUTPUT);
		pinMode(read_motors[i].get_pin_num(PIN_PWM), PWM_OUTPUT);
	}
	
	// set pwm 
	pwmSetMode(PWM_MODE_MS);
	pwmSetClock(PWM_CLOCK);
	pwmSetRange(PWM_RANGE);
}

int terminate_gpio(vector<motor_status> &read_motors) {
	for(int i; i<read_motors.size(); i++){
		// set pi-node for the right motor
		pinMode(read_motors[i].get_pin_num(PIN_1), INPUT);
		pinMode(read_motors[i].get_pin_num(PIN_2), INPUT);
		pinMode(read_motors[i].get_pin_num(PIN_PWM), INPUT);
	}
}
