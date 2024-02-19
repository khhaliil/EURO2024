/*
 * NavRoutineFunctions.c
 *
 *  Created on: Nov 17, 2023
 *      Author: Dhia Mnasri
 */

#include "main.h"
#include "NavConfig.h"
#include "NavTypes.h"
#include "NavConstants.h"
#include "Navigation.h"
#include "math.h"



extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim5;
extern TIM_HandleTypeDef htim6;
extern TIM_HandleTypeDef htim15;


extern int32_t Nav_RightTicks_i32;
extern int32_t Nav_LeftTicks_i32 ;



extern int32_t Nav_OverflowLeftEncoder_i32  ;
extern int32_t Nav_PrevLeftEncoderCNT_i32   ;
extern uint32_t Nav_Test_enter  ;


extern double Nav_ConvertLeft_Ticks2mm_d     ;
extern double Nav_ConvertRight_Ticks2mm_d    ;

extern double Nav_MeasuredDistanceLeft_mm_d  ;
extern double Nav_MeasuredDistanceRight_mm_d ;

extern double Nav_MeasuredDistance_mm_d      ;
extern double Nav_PrevMeasuredDistance_mm_d  ;

double Nav_PrevDistanceError_d=0,Nav_DerivativeAction_d=0;/////////////////////////////////////////////

extern double Nav_LimitDistance_mm_d         ;

extern double Nav_ReferenceAngle_deg_d ;
extern double Nav_ReferenceDistance_d ;


extern double Nav_MeasuredAngle_rad_d        ;
extern double Nav_PrevMeasuredAngle_rad_d    ;
extern double Nav_RemainingAngle_deg_d		  ;



extern double Nav_CurveCoefficient_d0 ;

extern double Nav_CurrentAngle_rad_d    ;
extern double Nav_PrevAngle_rad_d	 ;
extern double Nav_AverageAngle_rad_d ;
extern double Nav_CurrentAngle_deg_d    ;

extern double Nav_DeltaX_mm_d            ;
extern double Nav_DeltaY_mm_d            ;

extern double Nav_StartX_mm_d           ;
extern double Nav_StartY_mm_d           ;

extern double Nav_CurrentX_mm_d          ;
extern double Nav_CurrentY_mm_d          ;

extern double Nav_CurrentTargetX_mm_d ;
extern double Nav_CurrentTargetY_mm_d ;

extern double Nav_TargetX_mm_d              ;
extern double Nav_TargetY_mm_d              ;



extern double Nav_TargetArrivingAngle_deg_d  ;
extern uint32_t Nav_Test_enter_2  ;

extern double Nav_TargetDistance_mm_d;
extern double Nav_RemainingDistance_mm_d  ;
extern double Nav_CurrentTargetDistance_mm_d ;
extern double Nav_PrevTargetDistance_mm_d ;

extern double Nav_TargetAngle_deg_d ;
extern double Nav_CurrentTargetAngle_deg_d    ;
extern double Nav_PrevTargetAngle_deg_d       ;

extern double Nav_TargetLinearVelocity_d    ;
extern double Nav_TargetAngularVelocity_d    ;
extern double Nav_ReferenceAngularVelocity_d ;

extern double Nav_MeasuredVelocity_mm_d     ;
extern double Nav_MeasuredAngularVelocity_rad_d ;
extern double Nav_MeasuredAngularVelocity_deg_d     ;
extern double Nav_ReferenceLinearVelocity_d  ;
extern double Nav_DistanceError_d            ;
extern double Nav_SumDistanceError_d         ;
extern double Nav_PID_DistanceOutput_d       ;

extern double Nav_AngleError_d               ;
extern double Nav_SumAngleError_d            ;
extern double Nav_PID_AngleOutput_d          ;



extern double Nav_Going_BackwardTargetX_mm_d ;
extern double Nav_Going_BackwardTargetY_mm_d ;
extern double Nav_GoingBackwardCurrentTargetX_mm_d   ;
extern double Nav_GoingBackwardCurrentTargetY_mm_d   ;

extern int32_t Nav_RightMotorCommand_i32  ;
extern int32_t Nav_LeftMotorCommand_i32   ;

extern int8_t Nav_RightMotorDirection_i8 ;
extern int8_t Nav_LeftMotorDirection_i8  ;

extern int32_t MONITOR_RightMotorCommand_i32 ;
extern int32_t MONITOR_LeftMotorCommand_i32  ;

extern double Nav_Acc_d           ;
extern double Nav_MaxVelocity_d   ;

extern double Nav_AngularAcc_d    ;
extern double Nav_MaxAngularVelocity_d  ;

extern uint32_t Nav_CurrentSample_u32   ;

extern uint32_t Nav_AccelerationSamples_u32   ;

extern double Nav_CurveCoefficient_d ;

extern double Nav_KpDistance_d    ;
extern double Nav_KiDistance_d    ;
extern double Nav_KdDistance_d    ;

extern double Nav_KpAngle_d       ;
extern double Nav_KiAngle_d       ;
extern double Nav_KdAngle_d       ;


void Nav_vNavigationRoutine()
{
	Nav_vFeedbackRoutine();
	Nav_vPidDistance();
	Nav_vPidAngle();
	Nav_vCalculateMotorsCommand();
	Nav_vMotorsRoutine();
}


void Nav_vFeedbackRoutine()
{
	//Read ticks from encoder mode timers
	if  ( ENCODER_RIGHT->CNT > 0 )
	{
		Nav_RightTicks_i32 = ( (int32_t) ( ENCODER_RIGHT->CNT - ( ENCODER_RIGHT->ARR / 2 ) ) )   ;
	}

	if( ENCODER_LEFT->CNT > 0 )
	{

		Nav_LeftTicks_i32 =( (int32_t) ( ENCODER_LEFT->CNT - ( ENCODER_LEFT->ARR / 2 ) ) )   ;
	}

	//convert measured distance from ticks to mm for every encoder
	Nav_MeasuredDistanceRight_mm_d = (double) ( Nav_RightTicks_i32 * Nav_ConvertRight_Ticks2mm_d ) ;
	Nav_MeasuredDistanceLeft_mm_d  = (double) ( Nav_LeftTicks_i32  * Nav_ConvertLeft_Ticks2mm_d  ) ;

	//Measure distance of robot center ( (right + left)/2 )
	Nav_MeasuredDistance_mm_d = (double) ( ( Nav_MeasuredDistanceRight_mm_d   +  Nav_MeasuredDistanceLeft_mm_d ) / 2.0  ) ;

	//Measure linear velocity
	Nav_MeasuredVelocity_mm_d = Nav_MeasuredDistance_mm_d - Nav_PrevMeasuredDistance_mm_d ;
	Nav_PrevMeasuredDistance_mm_d = Nav_MeasuredDistance_mm_d;

	//Measure local angle of robot center
	Nav_MeasuredAngle_rad_d =  ( double ) ( ( Nav_MeasuredDistanceRight_mm_d   -  Nav_MeasuredDistanceLeft_mm_d ) / TRACK_MM )   ;

	//Measure angular velocity
	Nav_MeasuredAngularVelocity_rad_d = Nav_MeasuredAngle_rad_d - Nav_PrevMeasuredAngle_rad_d ;
	Nav_PrevMeasuredAngle_rad_d = Nav_MeasuredAngle_rad_d ;

	Nav_MeasuredAngularVelocity_deg_d = (double) ( ( Nav_MeasuredAngularVelocity_rad_d / M_PI ) * 180.0 ) ;

	//Measure global angle of robot center
	Nav_CurrentAngle_rad_d += Nav_MeasuredAngularVelocity_rad_d ;
	Nav_CurrentAngle_deg_d =  (double) ( ( Nav_CurrentAngle_rad_d / M_PI ) * 180.0 ) ;

	Nav_AverageAngle_rad_d = ( ( Nav_CurrentAngle_rad_d + Nav_PrevAngle_rad_d ) / 2 ) ;
	Nav_PrevAngle_rad_d = Nav_CurrentAngle_rad_d;

	if ( Nav_MeasuredAngularVelocity_rad_d ==0 )
	{
		Nav_CurveCoefficient_d = 1;
	}
	else
	{
		Nav_CurveCoefficient_d = ( sin( Nav_MeasuredAngularVelocity_rad_d / 2 ) ) / (Nav_MeasuredAngularVelocity_rad_d / 2 ) ;
	}

	//Measure X and Y of robot center
	Nav_DeltaX_mm_d = ( Nav_CurveCoefficient_d * Nav_MeasuredVelocity_mm_d )*cos( Nav_AverageAngle_rad_d ) ;
	Nav_DeltaY_mm_d = ( Nav_CurveCoefficient_d * Nav_MeasuredVelocity_mm_d )*sin( Nav_AverageAngle_rad_d ) ;

	Nav_CurrentX_mm_d +=  Nav_DeltaX_mm_d  ;
	Nav_CurrentY_mm_d +=  Nav_DeltaY_mm_d  ;
}



void Nav_vPidDistance()
{
	//Calculate Distance Error
	Nav_DistanceError_d = Nav_CurrentTargetDistance_mm_d -  Nav_MeasuredDistance_mm_d ;

	//Calculate the sum of distance Error using the Integral Term of the PID
	Nav_SumDistanceError_d = Nav_KiDistance_d * Nav_DistanceError_d + Nav_SumDistanceError_d ;

//    //Derivative Action
//	Nav_DerivativeAction_d = Nav_KdDistance_d*(Nav_DistanceError_d-Nav_PrevDistanceError_d);

	//calculate the Output of the distance PID block
	Nav_PID_DistanceOutput_d = ( double ) ( ( Nav_KpDistance_d *  Nav_DistanceError_d ) - ( Nav_KdDistance_d * Nav_MeasuredVelocity_mm_d ) + Nav_SumDistanceError_d  );
//	Nav_PID_DistanceOutput_d = ( double ) ( ( Nav_KpDistance_d *  Nav_DistanceError_d ) + Nav_DerivativeAction_d + Nav_SumDistanceError_d  );
}

void Nav_vPidAngle()
{
	//Calculate Angle Error
	Nav_AngleError_d =  Nav_CurrentTargetAngle_deg_d - Nav_CurrentAngle_deg_d ;

	//Calculate the sum of Angle Error using the Integral Term of the PID
	Nav_SumAngleError_d = Nav_KiAngle_d * Nav_AngleError_d + Nav_SumAngleError_d ;

	//Calculate the Output of the Angle PID block
	Nav_PID_AngleOutput_d = ( double ) ( ( Nav_KpAngle_d *  Nav_AngleError_d ) - ( Nav_KdAngle_d * Nav_MeasuredAngularVelocity_deg_d ) + Nav_SumAngleError_d  ) ;
}


void Nav_vCalculateMotorsCommand()
{
	//Calculate each motor command using the output of the distance PID and Angle PID blocks
	Nav_RightMotorCommand_i32 = ( int32_t ) ( Nav_PID_DistanceOutput_d + Nav_PID_AngleOutput_d )   ;
	Nav_LeftMotorCommand_i32  = ( int32_t ) ( Nav_PID_DistanceOutput_d - Nav_PID_AngleOutput_d )   ;

	// Right Motor Direction Settings
	if( Nav_RightMotorCommand_i32 >= 0.0 )
	{
		Nav_RightMotorDirection_i8 = MOTOR_DIRECTION_FORWARD ;
	}
	else
	{
		Nav_RightMotorDirection_i8 = MOTOR_DIRECTION_REVERSE ;
		Nav_RightMotorCommand_i32 = fabs( Nav_RightMotorCommand_i32 );
	}
	//Left Motor Direction Settings
	if( Nav_LeftMotorCommand_i32 >= 0.0 )
	{
		Nav_LeftMotorDirection_i8 = MOTOR_DIRECTION_FORWARD ;
	}
	else
	{
		Nav_LeftMotorDirection_i8 = MOTOR_DIRECTION_REVERSE ;
		Nav_LeftMotorCommand_i32 = fabs( Nav_LeftMotorCommand_i32 );
	}

	//Right Motor Maximum Command Settings
	if(Nav_RightMotorCommand_i32 > MAXIMUM_MOTOR_COMMAND )
	{
		Nav_RightMotorCommand_i32 = MAXIMUM_MOTOR_COMMAND ;
	}
	//Left Motor Maximum Command Settings
	if(Nav_LeftMotorCommand_i32 > MAXIMUM_MOTOR_COMMAND )
	{
		Nav_LeftMotorCommand_i32 = MAXIMUM_MOTOR_COMMAND ;
	}

	Nav_RightMotorCommand_i32 = ( int32_t ) ( ( (double) ( (MOTOR_PWM->ARR )  *  Nav_RightMotorCommand_i32 )  / MAXIMUM_MOTOR_COMMAND )  ) ;
	Nav_LeftMotorCommand_i32  = ( int32_t ) ( ( (double) ( (MOTOR_PWM->ARR )  *  Nav_LeftMotorCommand_i32 )   / MAXIMUM_MOTOR_COMMAND )  ) ;

	if ( Nav_RightMotorDirection_i8 == MOTOR_DIRECTION_FORWARD )
	{
		if ( ( Nav_RightMotorCommand_i32 > MINIMUM_SATURATION_COMMAND)
				&& ( Nav_RightMotorCommand_i32 < MINIMUM_RIGHT_MOTOR_FORWARD_COMMAND ) )
		{
			Nav_RightMotorCommand_i32 = MINIMUM_RIGHT_MOTOR_FORWARD_COMMAND;
		}
	}
	else
	{
		if ((Nav_RightMotorCommand_i32 > MINIMUM_SATURATION_COMMAND)
				&& (Nav_RightMotorCommand_i32 < MINIMUM_RIGHT_MOTOR_REVERSE_COMMAND))
		{
			Nav_RightMotorCommand_i32 = MINIMUM_RIGHT_MOTOR_REVERSE_COMMAND;
		}
	}


	if (  Nav_LeftMotorDirection_i8 == MOTOR_DIRECTION_FORWARD )
	{
		if (( Nav_LeftMotorCommand_i32 > MINIMUM_SATURATION_COMMAND )
				&& (Nav_LeftMotorCommand_i32 < MINIMUM_LEFT_MOTOR_FORWARD_COMMAND))

		{
			Nav_LeftMotorCommand_i32 = MINIMUM_LEFT_MOTOR_FORWARD_COMMAND;
		}
	}
	else
	{
		if( ( Nav_LeftMotorCommand_i32 > MINIMUM_SATURATION_COMMAND )
				&& (Nav_LeftMotorCommand_i32 < MINIMUM_LEFT_MOTOR_REVERSE_COMMAND)  )
		{
			Nav_LeftMotorCommand_i32 = MINIMUM_LEFT_MOTOR_REVERSE_COMMAND;
		}
	}

	//MONITORING
	MONITOR_RightMotorCommand_i32 = Nav_RightMotorDirection_i8 * Nav_RightMotorCommand_i32 ;
	MONITOR_LeftMotorCommand_i32  = Nav_LeftMotorDirection_i8 * Nav_LeftMotorCommand_i32  ;
}


void Nav_vMotorsRoutine()
{

	if (Nav_LeftMotorDirection_i8 == MOTOR_DIRECTION_FORWARD)
	{
		MOTOR_PWM->LEFT_FORWARD = Nav_LeftMotorCommand_i32 ;
		MOTOR_PWM->LEFT_REVERSE = 0 ;
	}
	else if ( Nav_LeftMotorDirection_i8 == MOTOR_DIRECTION_REVERSE )
	{
		MOTOR_PWM->LEFT_REVERSE= Nav_LeftMotorCommand_i32  ;
		MOTOR_PWM->LEFT_FORWARD = 0 ;
	}

	if (Nav_RightMotorDirection_i8 == MOTOR_DIRECTION_FORWARD )
	{
		MOTOR_PWM->RIGHT_FORWARD = Nav_RightMotorCommand_i32 ;
		MOTOR_PWM->RIGHT_REVERSE = 0;
	}
	else if (Nav_RightMotorDirection_i8 == MOTOR_DIRECTION_REVERSE )
	{
		MOTOR_PWM->RIGHT_REVERSE =  Nav_RightMotorCommand_i32  ;
		MOTOR_PWM->RIGHT_FORWARD = 0 ;
	}

}

