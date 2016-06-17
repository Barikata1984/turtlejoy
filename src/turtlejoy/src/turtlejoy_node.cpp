//-------------------------------------
//	- - - - - - TurtleJoy - - - - - -
//-------------------------------------
//	This code is written based on the sample code from
//	"http://forestofazumino.web.fc2.com/" and 
//	modified by Barikata1984

#include <stdio.h>
#include <fcntl.h>
#include <math.h>
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <wiringPi.h>
#include <vector>
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
public:
	char	current_flag;
	char	past_flag;
	vector< vector<int> >	pins_status;
};

// callback function
void messageCallBack(const geometry_msgs::Twist& twist) {
	left_rev	= (int)TICK * twist.linear.x;
	right_rev	= (int)TICK * twist.angular.y;

	ROS_INFO_STREAM("left revolution command: " << left_rev << ", right revolution command: " << right_rev);
}

// initialize gpio pins
int init_gpio() {
	if(wiringPiSetupGpio() == -1){
		ROS_INFO_STREAM("Sorry, master. I couldn't initialize GPIOs.");
	}

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
	pwmSetRange(1024);
}

// drive motors
void drive_motors(vector<vector<vector<int> > >	&read_driver_pins){
	for(int i=0; i<2; i++){
		for(int j=0; j<2; j++){
			digitalWrite(read_driver_pins[i][j][INDEX], read_driver_pins[i][j][VALUE]);
		}
		pwmWrite(read_driver_pins[i][PIN_PWM][INDEX], read_driver_pins[i][PIN_PWM][VALUE]);
	}			
}
//void drive_motors(vector<vector<vector<int> > >	&read_driver_pins){
//void set_motor_config(vector<int> &read_motor_status){

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
//	set = false;

	ros::init(argv, argc, "turtlereal3_node");
	ros::NodeHandle nh;
	
	//------------------------------------------
	ROS_INFO_STREAM("Hi! me's the Turtlejoy!!");
	//------------------------------------------
	
	init_gpio();
	
	//------------------------------------------
	ROS_INFO_STREAM("GPIO initialized");
	//------------------------------------------

	ros::Subscriber sub = nh.subscribe("/joy0", 1000, &messageCallBack);  // generate the subscribre.
	ros::Rate rate(FREQUENCY);		// set frequency.
 
//	ROS_INFO_STREAM(x_pos);
 
 	// repeat till <C-c> is inputted.
	while(ros::ok()){
		if(right_rev > 128){
			digitalWrite(R_1, 1);
			digitalWrite(R_2, 0);
			pwmWrite(R_PWM, abs(right_rev));
		}else if(right_rev < -128){
			digitalWrite(R_1, 0);
			digitalWrite(R_2, 1);
			pwmWrite(R_PWM, abs(right_rev));
		}else{
			digitalWrite(R_1, 0);
			digitalWrite(R_2, 0);
			pwmWrite(R_PWM, 0);
		}	
			
		if(left_rev > 128){
			digitalWrite(L_1, 1);
			digitalWrite(L_2, 0);
			pwmWrite(L_PWM, abs(left_rev));
		}else if(left_rev < -128){
			digitalWrite(L_1, 0);
			digitalWrite(L_2, 1);
			pwmWrite(L_PWM, abs(left_rev));
		}else{
			digitalWrite(L_1, 0);
			digitalWrite(L_2, 0);
			pwmWrite(L_PWM, 0);
		}
//
//	
//		if(right_rev > 128){
//			digitalWrite(R_1, 1);
//			digitalWrite(R_2, 0);
//			pwmWrite(R_PWM, abs(right_rev));
//		}else if(right_rev < -128){
//			digitalWrite(R_1, 0);
//			digitalWrite(R_2, 1);
//			pwmWrite(R_PWM, abs(right_rev));
//		}else{
//			digitalWrite(R_1, 0);
//			digitalWrite(R_2, 0);
//			pwmWrite(R_PWM, 0);
//		}	
//			
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
//
//		drive_motors(motos[0]);
		ros::spinOnce();
		rate.sleep();
	}
}



