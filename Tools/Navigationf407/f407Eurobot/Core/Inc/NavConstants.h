/*
 * NavConstants.h
 *
 *  Created on: Nov 17, 2023
 *      Author: Dhia Mnasri
 */

#ifndef INC_NAVCONSTANTS_H_
#define INC_NAVCONSTANTS_H_
#define M_2PI			6.28318530717958647692
#define SAMPLING_PERIOD   		0.005
#define MAXIMUM_MOTOR_COMMAND  					5000
#define MINIMUM_SATURATION_COMMAND				50

#define Nav_No_Rotate_After 	1000
#define ROBOT_Going_Backward 	4
#define ROBOT_Going_Forward		3

#define MINIMUM_RIGHT_MOTOR_FORWARD_COMMAND	 	231
#define MINIMUM_RIGHT_MOTOR_REVERSE_COMMAND		222

#define MINIMUM_LEFT_MOTOR_FORWARD_COMMAND      383
#define MINIMUM_LEFT_MOTOR_REVERSE_COMMAND		411




#define TRACK_MM     					304.5 //285.1
#define WHEEL_LEFT_DIAMETER_MM  		64.0
#define WHEEL_RIGHT_DIAMETER_MM   	    64.0
#define WHEEL_DIAMETER_MM  				61.18//62.3  //61.1
#define LEFT_WHEEL_GAIN					1.0001//1.0007
#define ENCODER_RESOLUTION		2048.0



//PID
#define FORWARD_LINEAR_TRAJECTORY_PID	      \
		Nav_KpDistance_d    = 100;   \
		Nav_KiDistance_d    = 0.0;	 	\
		Nav_KdDistance_d    = 1000;   \
		Nav_KpAngle_d       = 90		  ;  \
		Nav_KiAngle_d       = 0.0000 ;     \
		Nav_KdAngle_d       = 900 ;



#define REVERSE_LINEAR_TRAJECTORY_PID  \
		Nav_KpDistance_d    = 97.0;   \
		Nav_KiDistance_d    = 0.0;	 	\
		Nav_KdDistance_d    = 800;   \
		Nav_KpAngle_d       = 90		  ;  \
		Nav_KiAngle_d       = 0.0 ;     \
		Nav_KdAngle_d       = 999 ;


#define FORWARD_ANGULAR_TRAJECTORY_PID \
     	Nav_KpDistance_d    = 90;   \
		Nav_KiDistance_d    = 0;   \
		Nav_KdDistance_d    = 900;    \
		Nav_KpAngle_d       = 110.9 ;  \
		Nav_KiAngle_d       = 0.0 ;    \
		Nav_KdAngle_d       =800 ;



#endif /* INC_NAVCONSTANTS_H_ */
