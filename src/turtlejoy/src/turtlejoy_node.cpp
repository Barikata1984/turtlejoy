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

// main loop.
int main(int argv, char **argc){
	vector<motor_status>	motors{
								motor_status(R_1, R_2, R_PWM),
								motor_status(L_1, L_2, L_PWM),
							};
//	vector<int>	joy_commands(2, 0);
	
	ros::init(argv, argc, "turtlejoy_node");
	ros::NodeHandle nh;
	
	//------------------------------------------
	ROS_INFO_STREAM("Hi! me's the Turtlejoy!!");
	//------------------------------------------

	initialize_gpio(motors);
	
	//------------------------------------------
	ROS_INFO_STREAM("GPIO initialized");
	//------------------------------------------

	// genetate subscriber
//	ros::Subscriber sub = nh.subscribe<geometry_msgs::Twist>("/joy0", 100, boost::bind(messageCallBack, _1, &joy_commands));
	ros::Subscriber sub = nh.subscribe("/joy0", 100, messageCallBack);
	ros::Rate rate(FREQUENCY);		// set frequency.
 
 	// repeat till <C-c> is inputted.
	while(ros::ok()){
		ROS_INFO_STREAM("_/_/_/_/_/_/_/_/_/_/_/_/");
		for(int i; i<joy_commands.size(); i++){
			motors[i].driver(joy_commands[i]);

			switch(i){
			case 0:
				ROS_INFO_STREAM("Right: " << motors[i].get_rev());
				break;
			case 1:
				ROS_INFO_STREAM("Left : " << motors[i].get_rev());
				ROS_INFO_STREAM("");
				break;
			}
		}

//		motors[RIGHT].set_current_flag(right_rev);
//		cout << "right_flag is" << motors[RIGHT].get_current_flag() << endl;
//		if(motors[RIGHT].check_flags()){
//			switch(motors[RIGHT].get_current_flag()){
//			case 0: //				digitalWrite(R_1, 0);
//				digitalWrite(R_2, 1);
//				break;
//				ROS_INFO_STREAM("Hi!");
//			case 1:
//				digitalWrite(R_1, 0);
//				digitalWrite(R_2, 0);
//				break;
//				ROS_INFO_STREAM("It's!!");
//			case 2:
//				digitalWrite(R_1, 1);
//				digitalWrite(R_2, 0);
//				break;
//				ROS_INFO_STREAM("Me!!!");
//			}	
//		}
//		pwmWrite(R_PWM, abs(right_rev));
//		
////		if(left_rev > 128){
////			digitalWrite(L_1, 1);
////			digitalWrite(L_2, 0);
////			pwmWrite(L_PWM, abs(left_rev));
////		}else if(left_rev < -128){
////			digitalWrite(L_1, 0);
////			digitalWrite(L_2, 1);
////			pwmWrite(L_PWM, abs(left_rev));
////		}else{
////			digitalWrite(L_1, 0);
////			digitalWrite(L_2, 0);
////			pwmWrite(L_PWM, 0);
////		}
//
//		motors[RIGHT].set_past_flag();
		
		ros::spinOnce();
		rate.sleep();
	}

	terminate_gpio(motors);

	ROS_INFO_STREAM("See you later, master.");	
	return 0;
}

// callback function
void messageCallBack(const geometry_msgs::Twist &twist) {
//void messageCallBack(const geometry_msgs::Twist &twist, vector<int>::iterator write_command){
	joy_commands[RIGHT]	= (int)TICK * twist.angular.y;
	joy_commands[LEFT]	= (int)TICK * twist.linear.x;

//	ROS_INFO_STREAM("_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/");
//	ROS_INFO_STREAM("R-Rev-COMMAND: " << motors[RIGHT].get_rev());
//	ROS_INFO_STREAM("L-Rev-COMMAND: " << motors[LEFT].get_rev());
//	ROS_INFO_STREAM("");
}

int initialize_gpio(vector<motor_status> &read_motors) {
	wiringPiSetupGpio();

	for(int i; i<read_motors.size(); i++){
		// set pi-node for the right motor
		pinMode(read_motors[i].get_pin_num(PIN_1), OUTPUT);
		pinMode(read_motors[i].get_pin_num(PIN_2), OUTPUT);
		pinMode(read_motors[i].get_pin_num(PIN_PWM), PWM_OUTPUT);
	}

	// set pi-node for the left motor
//	pinMode(L_1, OUTPUT);
//	pinMode(L_2, OUTPUT);
//	pinMode(L_PWM, PWM_OUTPUT);

	// set pwm 
	pwmSetMode(PWM_MODE_MS);
	pwmSetClock(400);
	pwmSetRange(PWM_CLOCK);
}

int terminate_gpio(vector<motor_status> &read_motors) {
	for(int i; i<read_motors.size(); i++){
		// set pi-node for the right motor
		pinMode(read_motors[i].get_pin_num(PIN_1), INPUT);
		pinMode(read_motors[i].get_pin_num(PIN_2), INPUT);
		pinMode(read_motors[i].get_pin_num(PIN_PWM), INPUT);
	}
//	pinMode(R_1, INPUT);
//	pinMode(R_2, INPUT);
//	pinMode(R_PWM, INPUT);

//	pinMode(L_1, INPUT);
//	pinMode(L_2, INPUT);
//	pinMode(L_PWM, INPUT);
}
