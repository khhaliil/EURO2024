/*
 * NavStateMachines.c
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

extern Nav_TestPathStates_ten Nav_TestPathState_en	 			;
extern Nav_WallAlignStates_ten Nav_WallAlignState_en 			;
extern Nav_ExecutePath_States_ten Nav_ExecutePath_State_en 	    ;

extern Nav_Navigator_Indicators Nav_Navigator_Indicator 		;
extern Nav_Navigator_States_en Nav_Navigator_CurrentState_en 	;
extern Nav_TrajectoryStates_ten Nav_TrajectoryState_en 		;
extern Nav_TrajectoryModes_ten  Nav_TrajectoryMode_en 			;
extern Nav_TrapezePhases_ten Nav_TrapezePhase_en 				;
extern Nav_GoToXY_States_ten Nav_GoToXY_State_en 				;

extern double Nav_XYTargets_ad[5][4];

extern uint8_t Nav_CurrentTargetNumber_u8 ;
extern uint8_t Nav_NumberOfTargets_u8  ;

extern double Nav_TargetX_mm_d              ;
extern double Nav_TargetY_mm_d              ;
extern double Nav_TargetArrivingAngle_deg_d ;
extern int8_t ROBOT_Direction ;

extern int32_t Nav_RightTicks_i32;
extern int32_t Nav_LeftTicks_i32;

int32_t  Nav_PrevRightTicks=0;
int32_t  Nav_PrevLeftTicks=0;


extern double Nav_ConvertLeft_Ticks2mm_d     ;
extern double Nav_ConvertRight_Ticks2mm_d    ;

extern double Nav_MeasuredDistanceLeft_mm_d  ;
extern double Nav_MeasuredDistanceRight_mm_d ;

extern double Nav_MeasuredDistance_mm_d      ;
extern double Nav_PrevMeasuredDistance_mm_d  ;

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


extern uint32_t Nav_Counter_u32 ;

extern double Nav_KpDistance_d    ;
extern double Nav_KiDistance_d    ;
extern double Nav_KdDistance_d    ;

extern double Nav_KpAngle_d       ;
extern double Nav_KiAngle_d       ;
extern double Nav_KdAngle_d       ;


/**
  * @brief  This state machine is used when we need the robot to execute a path composed of a number of consecutive coordinates
  * @param  none
  * @retval void
  */

void Nav_vExecutePath()
{
	switch ( Nav_ExecutePath_State_en )
	{

	case Nav_ExecutePath_Idle_en :
	{
		Nav_ExecutePath_State_en = Nav_ExecutePath_SetNextTarget_en;
	}break;


	case Nav_ExecutePath_SetNextTarget_en :
	{
		if ( Nav_CurrentTargetNumber_u8 < ( Nav_NumberOfTargets_u8 ) )
		{
			Nav_ExecutePath_State_en = Nav_ExecutePath_GoToXY_en;
		}
		else
		{
			Nav_ExecutePath_State_en = Nav_ExecutePath_Finished_en ;
		}
	}break;

	case Nav_ExecutePath_GoToXY_en :
	{
		if( Nav_GoToXY_State_en == Nav_GoToXY_Idle_en )
		{
			Nav_TargetX_mm_d = Nav_XYTargets_ad[Nav_CurrentTargetNumber_u8][0];
			Nav_TargetY_mm_d = Nav_XYTargets_ad[Nav_CurrentTargetNumber_u8][1];
			Nav_TargetArrivingAngle_deg_d = Nav_XYTargets_ad[Nav_CurrentTargetNumber_u8][2];
			ROBOT_Direction = Nav_XYTargets_ad[Nav_CurrentTargetNumber_u8][3] ;

			Nav_GoToXY_State_en = Nav_GoToXY_Rotate_en;
		}
		else if ( Nav_GoToXY_State_en == Nav_GoToXY_Finished_en )
		{
			Nav_CurrentTargetNumber_u8++;
			Nav_ExecutePath_State_en = Nav_ExecutePath_SetNextTarget_en ;
			Nav_GoToXY_State_en = Nav_GoToXY_Idle_en ;
		}
		else
		{
			Nav_vGoToXYStateMachine_BOB();
		}
	}break;

	case Nav_ExecutePath_Finished_en :
	{

	}break;

	}

	Nav_vNavigationRoutine();

}


/**
  * @brief  Called either by the ExecutePathStateMachine or the NavigationStateMachine this state machine
  * guides the robot from its current position to a new point on the map with a rotation a straight line
  * and another rotation if we need a specific angle after arriving
  * @param  none
  * @retval void
  */

void Nav_vGoToXYStateMachine_BOB()
{
	switch( Nav_GoToXY_State_en )
	{
	case Nav_GoToXY_Idle_en :
	{

	}break;

	case Nav_GoToXY_Rotate_en :
	{
		if ( Nav_TrajectoryState_en == Nav_Trajectory_Idle_en )
		{

			if ( ROBOT_Direction == ROBOT_Going_Forward )
			{
				Nav_TargetAngle_deg_d = ( atan2( (Nav_TargetY_mm_d - Nav_CurrentY_mm_d) ,(Nav_TargetX_mm_d - Nav_CurrentX_mm_d ) ) * 180.0 ) / M_PI;
				Nav_RemainingAngle_deg_d =  Nav_TargetAngle_deg_d - Nav_CurrentTargetAngle_deg_d ;
				Nav_vSaturateRemainingAngle();
			}
			else if ( ROBOT_Direction == ROBOT_Going_Backward )
			{
				Nav_TargetAngle_deg_d = ( atan2( (Nav_CurrentY_mm_d - Nav_TargetY_mm_d) ,(Nav_CurrentX_mm_d - Nav_TargetX_mm_d ) ) * 180.0 ) / M_PI;
				Nav_RemainingAngle_deg_d =  Nav_TargetAngle_deg_d - Nav_CurrentTargetAngle_deg_d ;
				Nav_vSaturateRemainingAngle();

			}

			if( Nav_RemainingAngle_deg_d > 0.0 )
			{
				Nav_MaxAngularVelocity_d = 300 ;
				Nav_AngularAcc_d = 320 ;
				Nav_TrajectoryMode_en = Nav_ForwardAngularTrajectory_en;
			}
			else
			{
				Nav_MaxAngularVelocity_d = -300.0 ;
				Nav_AngularAcc_d = -320.0 ;
				Nav_TrajectoryMode_en = Nav_ReverseAngularTrajectory_en;
			}

			Nav_TrajectoryState_en = Nav_Trajectory_ResetVariables_en;
		}
		else if ( Nav_TrajectoryState_en == Nav_Trajectory_Finish_en)
		{
			Nav_GoToXY_State_en = Nav_GoToXY_Forward_en;
			Nav_TrajectoryState_en = Nav_Trajectory_Idle_en;
		}
		else
		{
			Nav_vIndependantTrajectoryStateMachine();
		}
	}break;

	case Nav_GoToXY_Forward_en :
	{
		if ( Nav_TrajectoryState_en == Nav_Trajectory_Idle_en )
		{
			if (ROBOT_Direction == ROBOT_Going_Forward )
			{
				Nav_TrajectoryMode_en = Nav_ForwardLinearTrajectory_en;
				Nav_MaxVelocity_d = 500 ; //400 ; //300 ;//700
				Nav_Acc_d = 400 ;//1500
				//Nav_TargetDistance_mm_d = sqrt ( pow( Nav_TargetX_mm_d - Nav_CurrentX_mm_d ,2 ) + pow( Nav_TargetY_mm_d - Nav_CurrentY_mm_d , 2 ) ) ;
				Nav_TrajectoryState_en = Nav_Trajectory_ResetVariables_en;
			}
			else if ( ROBOT_Direction == ROBOT_Going_Backward)
			{
				Nav_TrajectoryMode_en = Nav_ReverseLinearTrajectory_en;
				Nav_MaxVelocity_d = - 500 ; //400 ; //300 ;//700
				Nav_Acc_d = - 400 ;//1500
				//Nav_TargetDistance_mm_d = sqrt ( pow( Nav_TargetX_mm_d - Nav_CurrentX_mm_d ,2 ) + pow( Nav_TargetY_mm_d - Nav_CurrentY_mm_d , 2 ) ) ;
				Nav_TrajectoryState_en = Nav_Trajectory_ResetVariables_en;

			}
		}
		else if ((Nav_TrajectoryState_en == Nav_Trajectory_Finish_en  ) && ( Nav_TargetArrivingAngle_deg_d != Nav_No_Rotate_After))
		{
			Nav_GoToXY_State_en = Nav_GoToXY_RotateAfter_en;
			Nav_TrajectoryState_en = Nav_Trajectory_Idle_en;
		}
		else if ((Nav_TrajectoryState_en == Nav_Trajectory_Finish_en ) && ( Nav_TargetArrivingAngle_deg_d == Nav_No_Rotate_After))
		{
			Nav_GoToXY_State_en = Nav_GoToXY_Finished_en ;
			Nav_TrajectoryState_en = Nav_Trajectory_Idle_en;
		}
		else
		{
			Nav_vIndependantTrajectoryStateMachine();
		}
	}break;

	case Nav_GoToXY_RotateAfter_en :
	{

		if ( Nav_TrajectoryState_en == Nav_Trajectory_Idle_en )
		{
			Nav_TargetAngle_deg_d = Nav_TargetArrivingAngle_deg_d;
			Nav_RemainingAngle_deg_d =  Nav_TargetAngle_deg_d - Nav_CurrentTargetAngle_deg_d ;
			Nav_vSaturateRemainingAngle();
			if( Nav_RemainingAngle_deg_d > 0.0 )
			{
				Nav_MaxAngularVelocity_d = 300;//200 ;
				Nav_AngularAcc_d = 320 ;//230 ;
				Nav_TrajectoryMode_en = Nav_ForwardAngularTrajectory_en;
			}
			else
			{
				Nav_MaxAngularVelocity_d = -300.0 ;
				Nav_AngularAcc_d = -320.0 ;
				Nav_TrajectoryMode_en = Nav_ReverseAngularTrajectory_en;
			}

			Nav_TrajectoryState_en = Nav_Trajectory_ResetVariables_en;
		}
		else if ( Nav_TrajectoryState_en == Nav_Trajectory_Finish_en)
		{
			Nav_GoToXY_State_en = Nav_GoToXY_Finished_en;
			Nav_TrajectoryState_en = Nav_Trajectory_Idle_en;
		}
		else
		{
			Nav_vIndependantTrajectoryStateMachine();
		}
	}break;
	case Nav_GoToXY_OrderSuddenStop_en :
	{
		Nav_GoToXY_State_en = Nav_GoToXY_ExecuteSuddenStop_en;
		Nav_TrajectoryState_en = Nav_Trajectory_OrderSuddenStop_en ; // A redefinir Nav_Trajectory_ExecuteSuddenStop_en
		Nav_vIndependantTrajectoryStateMachine();

	}break;
	case Nav_GoToXY_ExecuteSuddenStop_en :
	{
		if ( Nav_TrajectoryState_en == Nav_Trajectory_Finish_en) // Is it necessary to 	do this checking ?
		{
			Nav_GoToXY_State_en = Nav_GoToXY_Finished_en;
			Nav_TrajectoryState_en = Nav_Trajectory_Idle_en;
		}
		else
		{
			Nav_vIndependantTrajectoryStateMachine();
		}

	}break;

	case Nav_GoToXY_Finished_en :
	{
		//	Nav_Navigator_CurrentState_en = Nav_Navigator_WaitForOrders_en ;

	}break;
	}
}

void Nav_vTestPathIndependantTrajectoryStateMachine()
{
	switch(Nav_TrajectoryState_en)
	{

	case Nav_Trajectory_Idle_en :
	{

	}break;

	case Nav_Trajectory_ResetVariables_en :
	{
		//reset the current sample
		Nav_CurrentSample_u32 = 0;
		Nav_TrapezePhase_en = Nav_Trapeze_Accelerating_en;
		//reset measuring variables
		ENCODER_RIGHT->CNT = ENCODER_RIGHT->ARR / 2 ;
		ENCODER_LEFT->CNT = ENCODER_LEFT->ARR / 2 ;
		Nav_PrevMeasuredDistance_mm_d = 0.0 ;
		Nav_PrevMeasuredAngle_rad_d   = 0.0 ;
		//Nav_PrevMeasuredAngle_deg_d   = 0.0 ;
		Nav_vFeedbackRoutine();

		//reset the Target Distance variables
		Nav_CurrentTargetDistance_mm_d = 0.0 ;
		Nav_PrevTargetDistance_mm_d = 0.0 ;

		Nav_PrevTargetAngle_deg_d = Nav_CurrentTargetAngle_deg_d;

		//reset the pid variables
		Nav_SumDistanceError_d = 0.0 ;
		Nav_SumAngleError_d = 0.0 ;
		Nav_TrajectoryState_en = Nav_Trajectory_SetPath_en;
	}break;

	case Nav_Trajectory_SetPath_en :
	{

		//		Nav_RemainingDistance_mm_d = Nav_TargetDistance_mm_d - ( Nav_CurrentTargetDistance_mm_d -  Nav_MeasuredDistance_mm_d );
		if ( Nav_TrajectoryMode_en == Nav_ForwardLinearTrajectory_en )
		{
			Nav_MaxVelocity_d = Nav_MaxVelocity_d * SAMPLING_PERIOD ;
			Nav_Acc_d = Nav_Acc_d * SAMPLING_PERIOD * SAMPLING_PERIOD ;
			FORWARD_LINEAR_TRAJECTORY_PID
		}
		else if ( Nav_TrajectoryMode_en == Nav_ReverseLinearTrajectory_en )
		{
			Nav_MaxVelocity_d = Nav_MaxVelocity_d * SAMPLING_PERIOD ;
			Nav_Acc_d = Nav_Acc_d * SAMPLING_PERIOD * SAMPLING_PERIOD ;
			REVERSE_LINEAR_TRAJECTORY_PID
		}
		else if ( Nav_TrajectoryMode_en == Nav_ForwardAngularTrajectory_en )
		{
			Nav_MaxAngularVelocity_d = Nav_MaxAngularVelocity_d * SAMPLING_PERIOD ;
			Nav_AngularAcc_d = Nav_AngularAcc_d * SAMPLING_PERIOD * SAMPLING_PERIOD;
			FORWARD_ANGULAR_TRAJECTORY_PID
		}
		else if ( Nav_TrajectoryMode_en == Nav_ReverseAngularTrajectory_en )
		{
			Nav_MaxAngularVelocity_d = Nav_MaxAngularVelocity_d * SAMPLING_PERIOD ;
			Nav_AngularAcc_d = Nav_AngularAcc_d * SAMPLING_PERIOD * SAMPLING_PERIOD;
			FORWARD_ANGULAR_TRAJECTORY_PID
		}
		Nav_Counter_u32 = 0 ;
		Nav_TrajectoryState_en = Nav_Trajectory_WaitToExecute_en;
	}break;

	case Nav_Trajectory_WaitToExecute_en :
	{
		Nav_Counter_u32++;
		if (Nav_Counter_u32 > 2)
		{
			Nav_TrajectoryState_en = Nav_Trajectory_Execute_en;
			Nav_Counter_u32 = 0 ;
		}
	}break;

	case Nav_Trajectory_Execute_en :
	{
		Nav_CurrentSample_u32++;
		if  ( Nav_TrajectoryMode_en == Nav_ForwardLinearTrajectory_en )
		{
//			Nav_TargetDistance_mm_d = sqrt ( pow( Nav_TargetX_mm_d - Nav_CurrentX_mm_d ,2 ) + pow( Nav_TargetY_mm_d - Nav_CurrentY_mm_d , 2 ) ) ;
			Nav_RemainingDistance_mm_d = Nav_TargetDistance_mm_d - Nav_CurrentTargetDistance_mm_d ;
//			Nav_LimitDistance_mm_d = sqrt ( pow( Nav_TargetX_mm_d - Nav_CurrentTargetX_mm_d ,2 ) + pow( Nav_TargetY_mm_d - Nav_CurrentTargetY_mm_d , 2 ) ) ;
//			if( Nav_LimitDistance_mm_d > 10.0)
//			{
//				Nav_CurrentTargetX_mm_d = Nav_CurrentX_mm_d + ( Nav_CurrentTargetDistance_mm_d -  Nav_MeasuredDistance_mm_d )*cos( Nav_CurrentAngle_rad_d ) ;
//				Nav_CurrentTargetY_mm_d = Nav_CurrentY_mm_d + ( Nav_CurrentTargetDistance_mm_d -  Nav_MeasuredDistance_mm_d )*sin( Nav_CurrentAngle_rad_d ) ;
//				Nav_CurrentTargetAngle_deg_d = ( atan2( (Nav_TargetY_mm_d - Nav_CurrentTargetY_mm_d) ,(Nav_TargetX_mm_d - Nav_CurrentTargetX_mm_d ) ) * 180.0 ) / M_PI;
//
//				Nav_vCurrentTargetAngleFollower();
//			}
			Nav_TrapezeLinearVelocity2();
			Nav_vTargetDistanceCalculationRoutine();
		}
		else if ( Nav_TrajectoryMode_en == Nav_ReverseLinearTrajectory_en )
		{
//			Nav_TargetDistance_mm_d = - sqrt ( pow( Nav_TargetX_mm_d - Nav_CurrentX_mm_d ,2 ) + pow( Nav_TargetY_mm_d - Nav_CurrentY_mm_d , 2 ) ) ;
			Nav_RemainingDistance_mm_d = Nav_TargetDistance_mm_d - Nav_CurrentTargetDistance_mm_d ;
//			Nav_LimitDistance_mm_d = sqrt ( pow( Nav_TargetX_mm_d - Nav_CurrentTargetX_mm_d ,2 ) + pow( Nav_TargetY_mm_d - Nav_CurrentTargetY_mm_d , 2 ) ) ;
//			if( Nav_LimitDistance_mm_d > 10.0)
//			{
//				Nav_CurrentTargetX_mm_d = Nav_CurrentX_mm_d + ( Nav_CurrentTargetDistance_mm_d -  Nav_MeasuredDistance_mm_d )*cos( Nav_CurrentAngle_rad_d ) ;
//				Nav_CurrentTargetY_mm_d = Nav_CurrentY_mm_d + ( Nav_CurrentTargetDistance_mm_d -  Nav_MeasuredDistance_mm_d )*sin( Nav_CurrentAngle_rad_d ) ;
//				Nav_CurrentTargetAngle_deg_d = ( atan2( (Nav_CurrentTargetY_mm_d - Nav_TargetY_mm_d ) ,(Nav_CurrentTargetX_mm_d - Nav_TargetX_mm_d ) ) * 180.0 ) / M_PI;
//				Nav_Test_enter_2 ++ ;
//				Nav_vCurrentTargetAngleFollower();
//				//Nav_CurrentTargetAngle_deg_d=0;
//			}
			Nav_TrapezeReverseLinearVelocity2();
			Nav_vTargetDistanceCalculationRoutine();

			//			Nav_Going_BackwardTargetX_mm_d = 2 * Nav_CurrentX_mm_d - Nav_TargetX_mm_d ;
			//			Nav_Going_BackwardTargetY_mm_d = 2 * Nav_CurrentY_mm_d - Nav_TargetY_mm_d ;
			//			Nav_TargetAngle_deg_d = ( atan2( (Nav_Going_BackwardTargetY_mm_d - Nav_CurrentY_mm_d) ,(Nav_Going_BackwardTargetX_mm_d - Nav_CurrentX_mm_d ) ) * 180.0 ) / M_PI;


		}
		else if ( Nav_TrajectoryMode_en == Nav_ForwardAngularTrajectory_en )
		{
//			if ( Nav_GoToXY_State_en == Nav_GoToXY_Rotate_en ) // because in the rotate after state we need to go to a constant target angle
//			{
//				if (ROBOT_Direction == ROBOT_Going_Forward)
//				{
//					Nav_TargetAngle_deg_d = ( atan2( (Nav_TargetY_mm_d - Nav_CurrentY_mm_d) ,(Nav_TargetX_mm_d - Nav_CurrentX_mm_d ) ) * 180.0 ) / M_PI;
//				}
//				else
//				{
//					Nav_TargetAngle_deg_d = ( atan2( (Nav_CurrentY_mm_d - Nav_TargetY_mm_d) ,(Nav_CurrentX_mm_d - Nav_TargetX_mm_d ) ) * 180.0 ) / M_PI;
//				}
//			}
			Nav_RemainingAngle_deg_d =  Nav_TargetAngle_deg_d - Nav_CurrentTargetAngle_deg_d  ;
//			Nav_vSaturateRemainingAngle();
			Nav_TrapezeAngularVelocity2();
			Nav_vTargetAngleCalculationRoutine();
		}
		else if ( Nav_TrajectoryMode_en == Nav_ReverseAngularTrajectory_en )
		{
//			if ( Nav_GoToXY_State_en == Nav_GoToXY_Rotate_en )
//			{
//				if ( ROBOT_Direction == ROBOT_Going_Forward)
//				{
//					Nav_TargetAngle_deg_d = ( atan2( (Nav_TargetY_mm_d - Nav_CurrentY_mm_d) ,(Nav_TargetX_mm_d - Nav_CurrentX_mm_d ) ) * 180.0 ) / M_PI;
//				}
//				else
//				{
//					Nav_TargetAngle_deg_d = ( atan2( (Nav_CurrentY_mm_d - Nav_TargetY_mm_d) ,(Nav_CurrentX_mm_d - Nav_TargetX_mm_d ) ) * 180.0 ) / M_PI;
//				}
//			}
			Nav_RemainingAngle_deg_d =  Nav_TargetAngle_deg_d - Nav_CurrentTargetAngle_deg_d  ;
//			Nav_vSaturateRemainingAngle();
			Nav_TrapezeReverseAngularVelocity2();
			Nav_vTargetAngleCalculationRoutine();
		}
		if  ( ( Nav_TrajectoryMode_en == Nav_ForwardLinearTrajectory_en ) || ( Nav_TrajectoryMode_en == Nav_ReverseLinearTrajectory_en ) )
		{
			if( ( Nav_CurrentSample_u32 > Nav_AccelerationSamples_u32 )
					&& ( Nav_TargetLinearVelocity_d == 0 )
					&& ( fabs (Nav_TargetAngularVelocity_d) < 0.0001 )
					&& ( Nav_MeasuredVelocity_mm_d == 0 )
					&& ( Nav_MeasuredAngularVelocity_deg_d == 0 )
					&& ( fabs( Nav_DistanceError_d ) < 1.5 ) )
			{
				Nav_Counter_u32 ++ ;
				//Nav_TrajectoryState_en = Nav_Trajectory_WaitAfterArriving_en;
			}
		}
		else if ( ( Nav_TrajectoryMode_en == Nav_ForwardAngularTrajectory_en ) ||  ( Nav_TrajectoryMode_en == Nav_ReverseAngularTrajectory_en  ) )
		{
			if( ( Nav_CurrentSample_u32 > Nav_AccelerationSamples_u32 )
					&& ( Nav_TargetLinearVelocity_d == 0 )
					&& ( fabs (Nav_TargetAngularVelocity_d) < 0.0001 )
					&& ( Nav_MeasuredVelocity_mm_d == 0 )
					&& ( Nav_MeasuredAngularVelocity_deg_d == 0 )
					&& ( fabs( Nav_AngleError_d ) < 1.5 ) )
			{
				Nav_Counter_u32 ++ ;
				//Nav_TrajectoryState_en = Nav_Trajectory_WaitAfterArriving_en;
			}
		}
		else
		{
			Nav_Counter_u32 = 0 ;
		}
		if ( Nav_Counter_u32 > 5 )
		{
			Nav_TrajectoryState_en = Nav_Trajectory_WaitAfterArriving_en;
			Nav_Counter_u32 = 0 ;
		}

	}break;
	case Nav_Trajectory_OrderSuddenStop_en :
	{
		Nav_TrapezePhase_en = Nav_Trapeze_OrderUrgentDecelerating_en ;

		Nav_TrajectoryState_en = Nav_Trajectory_ExecuteSuddenStop_en ;
		if ( Nav_TrajectoryMode_en == Nav_ForwardLinearTrajectory_en )
		{
			Nav_Acc_d = 16000 * SAMPLING_PERIOD * SAMPLING_PERIOD ;//4000
		}
		else if ( Nav_TrajectoryMode_en == Nav_ReverseLinearTrajectory_en )
		{
			Nav_Acc_d = Nav_Acc_d * SAMPLING_PERIOD * SAMPLING_PERIOD ;
		}
		else if ( Nav_TrajectoryMode_en == Nav_ForwardAngularTrajectory_en )
		{
			Nav_AngularAcc_d = Nav_AngularAcc_d * SAMPLING_PERIOD * SAMPLING_PERIOD;
		}
		else if ( Nav_TrajectoryMode_en == Nav_ReverseAngularTrajectory_en )
		{
			Nav_AngularAcc_d = Nav_AngularAcc_d * SAMPLING_PERIOD * SAMPLING_PERIOD;
		}
		Nav_CurrentSample_u32++;
		if (  Nav_TrajectoryMode_en == Nav_ForwardLinearTrajectory_en )
		{
			Nav_TrapezeLinearVelocity2();
			Nav_vTargetDistanceCalculationRoutine();
		}
		else if ( Nav_TrajectoryMode_en == Nav_ReverseLinearTrajectory_en )
		{

		}
		else if ( Nav_TrajectoryMode_en == Nav_ForwardAngularTrajectory_en )
		{
			Nav_TrapezeAngularVelocity2();
			Nav_vTargetAngleCalculationRoutine();
		}
		else if ( Nav_TrajectoryMode_en == Nav_ReverseAngularTrajectory_en )
		{
			Nav_TrapezeReverseAngularVelocity2();
			Nav_vTargetAngleCalculationRoutine();
		}
	}break;
	case Nav_Trajectory_ExecuteSuddenStop_en :
	{

		Nav_CurrentSample_u32++;
		if ( ( Nav_TrajectoryMode_en == Nav_ForwardLinearTrajectory_en ) || ( Nav_TrajectoryMode_en == Nav_ReverseLinearTrajectory_en ) )
		{
			Nav_TrapezeLinearVelocity2();
			Nav_vTargetDistanceCalculationRoutine();
		}
		else if ( Nav_TrajectoryMode_en == Nav_ForwardAngularTrajectory_en )
		{
			Nav_TrapezeAngularVelocity2();
			Nav_vTargetAngleCalculationRoutine();
		}
		else if ( Nav_TrajectoryMode_en == Nav_ReverseAngularTrajectory_en )
		{
			Nav_TrapezeReverseAngularVelocity2();
			Nav_vTargetAngleCalculationRoutine();
		}
		if( ( Nav_CurrentSample_u32 > Nav_AccelerationSamples_u32 )
				&& ( Nav_TargetLinearVelocity_d == 0 )
				&& ( Nav_TargetAngularVelocity_d == 0 )
				&& ( Nav_MeasuredVelocity_mm_d == 0 )
				&& ( Nav_MeasuredAngularVelocity_deg_d == 0 ))
		{
			Nav_Counter_u32 = 0 ;
			Nav_TrajectoryState_en = Nav_Trajectory_WaitAfterArriving_en;
		}

	}break;

	case Nav_Trajectory_WaitAfterArriving_en :
	{
		Nav_Counter_u32++;
		if (Nav_Counter_u32 > 2)
		{
			Nav_TrajectoryState_en = Nav_Trajectory_Finish_en;

		}
	}break;

	case Nav_Trajectory_Finish_en :
	{

	}break;
	}

}


void Nav_vIndependantTrajectoryStateMachine()
{
	switch(Nav_TrajectoryState_en)
	{

	case Nav_Trajectory_Idle_en :
	{

	}break;

	case Nav_Trajectory_ResetVariables_en :
	{
		//reset the current sample
		Nav_CurrentSample_u32 = 0;
		Nav_TrapezePhase_en = Nav_Trapeze_Accelerating_en;
		//reset measuring variables
		ENCODER_RIGHT->CNT = ENCODER_RIGHT->ARR / 2 ;
		ENCODER_LEFT->CNT = ENCODER_LEFT->ARR / 2 ;
		Nav_PrevMeasuredDistance_mm_d = 0.0 ;
		Nav_PrevMeasuredAngle_rad_d   = 0.0 ;
		//Nav_PrevMeasuredAngle_deg_d   = 0.0 ;
		Nav_vFeedbackRoutine();

		//reset the Target Distance variables
		Nav_CurrentTargetDistance_mm_d = 0.0 ;
		Nav_PrevTargetDistance_mm_d = 0.0 ;

		Nav_PrevTargetAngle_deg_d = Nav_CurrentTargetAngle_deg_d;

		//reset the pid variables
		Nav_SumDistanceError_d = 0.0 ;
		Nav_SumAngleError_d = 0.0 ;
		Nav_TrajectoryState_en = Nav_Trajectory_SetPath_en;
	}break;

	case Nav_Trajectory_SetPath_en :
	{

		//		Nav_RemainingDistance_mm_d = Nav_TargetDistance_mm_d - ( Nav_CurrentTargetDistance_mm_d -  Nav_MeasuredDistance_mm_d );
		if ( Nav_TrajectoryMode_en == Nav_ForwardLinearTrajectory_en )
		{
			Nav_MaxVelocity_d = Nav_MaxVelocity_d * SAMPLING_PERIOD ;
			Nav_Acc_d = Nav_Acc_d * SAMPLING_PERIOD * SAMPLING_PERIOD ;
			FORWARD_LINEAR_TRAJECTORY_PID
		}
		else if ( Nav_TrajectoryMode_en == Nav_ReverseLinearTrajectory_en )
		{
			Nav_MaxVelocity_d = Nav_MaxVelocity_d * SAMPLING_PERIOD ;
			Nav_Acc_d = Nav_Acc_d * SAMPLING_PERIOD * SAMPLING_PERIOD ;
			REVERSE_LINEAR_TRAJECTORY_PID
		}
		else if ( Nav_TrajectoryMode_en == Nav_ForwardAngularTrajectory_en )
		{
			Nav_MaxAngularVelocity_d = Nav_MaxAngularVelocity_d * SAMPLING_PERIOD ;
			Nav_AngularAcc_d = Nav_AngularAcc_d * SAMPLING_PERIOD * SAMPLING_PERIOD;
			FORWARD_ANGULAR_TRAJECTORY_PID
		}
		else if ( Nav_TrajectoryMode_en == Nav_ReverseAngularTrajectory_en )
		{
			Nav_MaxAngularVelocity_d = Nav_MaxAngularVelocity_d * SAMPLING_PERIOD ;
			Nav_AngularAcc_d = Nav_AngularAcc_d * SAMPLING_PERIOD * SAMPLING_PERIOD;
			FORWARD_ANGULAR_TRAJECTORY_PID
		}
		Nav_Counter_u32 = 0 ;
		Nav_TrajectoryState_en = Nav_Trajectory_WaitToExecute_en;
	}break;

	case Nav_Trajectory_WaitToExecute_en :
	{
		Nav_Counter_u32++;
		if (Nav_Counter_u32 > 2)
		{
			Nav_TrajectoryState_en = Nav_Trajectory_Execute_en;
			Nav_Counter_u32 = 0 ;
		}
	}break;

	case Nav_Trajectory_Execute_en :
	{
		Nav_CurrentSample_u32++;
		if  ( Nav_TrajectoryMode_en == Nav_ForwardLinearTrajectory_en )
		{
			Nav_TargetDistance_mm_d = sqrt ( pow( Nav_TargetX_mm_d - Nav_CurrentX_mm_d ,2 ) + pow( Nav_TargetY_mm_d - Nav_CurrentY_mm_d , 2 ) ) ;
			Nav_RemainingDistance_mm_d = Nav_TargetDistance_mm_d - ( Nav_CurrentTargetDistance_mm_d -  Nav_MeasuredDistance_mm_d );
			Nav_LimitDistance_mm_d = sqrt ( pow( Nav_TargetX_mm_d - Nav_CurrentTargetX_mm_d ,2 ) + pow( Nav_TargetY_mm_d - Nav_CurrentTargetY_mm_d , 2 ) ) ;
			if( Nav_LimitDistance_mm_d > 10.0)
			{
				Nav_CurrentTargetX_mm_d = Nav_CurrentX_mm_d + ( Nav_CurrentTargetDistance_mm_d -  Nav_MeasuredDistance_mm_d )*cos( Nav_CurrentAngle_rad_d ) ;
				Nav_CurrentTargetY_mm_d = Nav_CurrentY_mm_d + ( Nav_CurrentTargetDistance_mm_d -  Nav_MeasuredDistance_mm_d )*sin( Nav_CurrentAngle_rad_d ) ;
				Nav_CurrentTargetAngle_deg_d = ( atan2( (Nav_TargetY_mm_d - Nav_CurrentTargetY_mm_d) ,(Nav_TargetX_mm_d - Nav_CurrentTargetX_mm_d ) ) * 180.0 ) / M_PI;

				Nav_vCurrentTargetAngleFollower();
			}
			Nav_TrapezeLinearVelocity2();
			Nav_vTargetDistanceCalculationRoutine();
		}
		else if ( Nav_TrajectoryMode_en == Nav_ReverseLinearTrajectory_en )
		{
			Nav_TargetDistance_mm_d = - sqrt ( pow( Nav_TargetX_mm_d - Nav_CurrentX_mm_d ,2 ) + pow( Nav_TargetY_mm_d - Nav_CurrentY_mm_d , 2 ) ) ;
			Nav_RemainingDistance_mm_d = Nav_TargetDistance_mm_d - ( Nav_CurrentTargetDistance_mm_d -  Nav_MeasuredDistance_mm_d );
			Nav_LimitDistance_mm_d = sqrt ( pow( Nav_TargetX_mm_d - Nav_CurrentTargetX_mm_d ,2 ) + pow( Nav_TargetY_mm_d - Nav_CurrentTargetY_mm_d , 2 ) ) ;
			if( Nav_LimitDistance_mm_d > 10.0)
			{
				Nav_CurrentTargetX_mm_d = Nav_CurrentX_mm_d + ( Nav_CurrentTargetDistance_mm_d -  Nav_MeasuredDistance_mm_d )*cos( Nav_CurrentAngle_rad_d ) ;
				Nav_CurrentTargetY_mm_d = Nav_CurrentY_mm_d + ( Nav_CurrentTargetDistance_mm_d -  Nav_MeasuredDistance_mm_d )*sin( Nav_CurrentAngle_rad_d ) ;
				Nav_CurrentTargetAngle_deg_d = ( atan2( (Nav_CurrentTargetY_mm_d - Nav_TargetY_mm_d ) ,(Nav_CurrentTargetX_mm_d - Nav_TargetX_mm_d ) ) * 180.0 ) / M_PI;
				Nav_Test_enter_2 ++ ;
				Nav_vCurrentTargetAngleFollower();
				//Nav_CurrentTargetAngle_deg_d=0;
			}
			Nav_TrapezeReverseLinearVelocity2();
			Nav_vTargetDistanceCalculationRoutine();

			//			Nav_Going_BackwardTargetX_mm_d = 2 * Nav_CurrentX_mm_d - Nav_TargetX_mm_d ;
			//			Nav_Going_BackwardTargetY_mm_d = 2 * Nav_CurrentY_mm_d - Nav_TargetY_mm_d ;
			//			Nav_TargetAngle_deg_d = ( atan2( (Nav_Going_BackwardTargetY_mm_d - Nav_CurrentY_mm_d) ,(Nav_Going_BackwardTargetX_mm_d - Nav_CurrentX_mm_d ) ) * 180.0 ) / M_PI;


		}
		else if ( Nav_TrajectoryMode_en == Nav_ForwardAngularTrajectory_en )
		{
			if ( Nav_GoToXY_State_en == Nav_GoToXY_Rotate_en ) // because in the rotate after state we need to go to a constant target angle
			{
				if (ROBOT_Direction == ROBOT_Going_Forward)
				{
					Nav_TargetAngle_deg_d = ( atan2( (Nav_TargetY_mm_d - Nav_CurrentY_mm_d) ,(Nav_TargetX_mm_d - Nav_CurrentX_mm_d ) ) * 180.0 ) / M_PI;
				}
				else
				{
					Nav_TargetAngle_deg_d = ( atan2( (Nav_CurrentY_mm_d - Nav_TargetY_mm_d) ,(Nav_CurrentX_mm_d - Nav_TargetX_mm_d ) ) * 180.0 ) / M_PI;
				}
			}
			Nav_RemainingAngle_deg_d =  Nav_TargetAngle_deg_d - Nav_CurrentTargetAngle_deg_d  ;
			Nav_vSaturateRemainingAngle();
			Nav_TrapezeAngularVelocity2();
			Nav_vTargetAngleCalculationRoutine();
		}
		else if ( Nav_TrajectoryMode_en == Nav_ReverseAngularTrajectory_en )
		{
			if ( Nav_GoToXY_State_en == Nav_GoToXY_Rotate_en )
			{
				if ( ROBOT_Direction == ROBOT_Going_Forward)
				{
					Nav_TargetAngle_deg_d = ( atan2( (Nav_TargetY_mm_d - Nav_CurrentY_mm_d) ,(Nav_TargetX_mm_d - Nav_CurrentX_mm_d ) ) * 180.0 ) / M_PI;
				}
				else
				{
					Nav_TargetAngle_deg_d = ( atan2( (Nav_CurrentY_mm_d - Nav_TargetY_mm_d) ,(Nav_CurrentX_mm_d - Nav_TargetX_mm_d ) ) * 180.0 ) / M_PI;
				}
			}
			Nav_RemainingAngle_deg_d =  Nav_TargetAngle_deg_d - Nav_CurrentTargetAngle_deg_d  ;
			Nav_vSaturateRemainingAngle();
			Nav_TrapezeReverseAngularVelocity2();
			Nav_vTargetAngleCalculationRoutine();
		}
		if  ( ( Nav_TrajectoryMode_en == Nav_ForwardLinearTrajectory_en ) || ( Nav_TrajectoryMode_en == Nav_ReverseLinearTrajectory_en ) )
		{
			if( ( Nav_CurrentSample_u32 > Nav_AccelerationSamples_u32 )
					&& ( Nav_TargetLinearVelocity_d == 0 )
					&& ( fabs (Nav_TargetAngularVelocity_d) < 0.0001 )
					&& ( Nav_MeasuredVelocity_mm_d == 0 )
					&& ( Nav_MeasuredAngularVelocity_deg_d == 0 )
					&& ( fabs( Nav_DistanceError_d ) < 1.5 ) )
			{
				Nav_Counter_u32 ++ ;
				//Nav_TrajectoryState_en = Nav_Trajectory_WaitAfterArriving_en;
			}
		}
		else if ( ( Nav_TrajectoryMode_en == Nav_ForwardAngularTrajectory_en ) ||  ( Nav_TrajectoryMode_en == Nav_ReverseAngularTrajectory_en  ) )
		{
			if( ( Nav_CurrentSample_u32 > Nav_AccelerationSamples_u32 )
					&& ( Nav_TargetLinearVelocity_d == 0 )
					&& ( fabs (Nav_TargetAngularVelocity_d) < 0.0001 )
					&& ( Nav_MeasuredVelocity_mm_d == 0 )
					&& ( Nav_MeasuredAngularVelocity_deg_d == 0 )
					&& ( fabs( Nav_AngleError_d ) < 1.5 ) )
			{
				Nav_Counter_u32 ++ ;
				//Nav_TrajectoryState_en = Nav_Trajectory_WaitAfterArriving_en;
			}
		}
		else
		{
			Nav_Counter_u32 = 0 ;
		}
		if ( Nav_Counter_u32 > 5 )
		{
			Nav_TrajectoryState_en = Nav_Trajectory_WaitAfterArriving_en;
			Nav_Counter_u32 = 0 ;
		}

	}break;
	case Nav_Trajectory_OrderSuddenStop_en :
	{
		Nav_TrapezePhase_en = Nav_Trapeze_OrderUrgentDecelerating_en ;

		Nav_TrajectoryState_en = Nav_Trajectory_ExecuteSuddenStop_en ;
		if ( Nav_TrajectoryMode_en == Nav_ForwardLinearTrajectory_en )
		{
			Nav_Acc_d = 16000 * SAMPLING_PERIOD * SAMPLING_PERIOD ;//4000
		}
		else if ( Nav_TrajectoryMode_en == Nav_ReverseLinearTrajectory_en )
		{
			Nav_Acc_d = Nav_Acc_d * SAMPLING_PERIOD * SAMPLING_PERIOD ;
		}
		else if ( Nav_TrajectoryMode_en == Nav_ForwardAngularTrajectory_en )
		{
			Nav_AngularAcc_d = Nav_AngularAcc_d * SAMPLING_PERIOD * SAMPLING_PERIOD;
		}
		else if ( Nav_TrajectoryMode_en == Nav_ReverseAngularTrajectory_en )
		{
			Nav_AngularAcc_d = Nav_AngularAcc_d * SAMPLING_PERIOD * SAMPLING_PERIOD;
		}
		Nav_CurrentSample_u32++;
		if (  Nav_TrajectoryMode_en == Nav_ForwardLinearTrajectory_en )
		{
			Nav_TrapezeLinearVelocity2();
			Nav_vTargetDistanceCalculationRoutine();
		}
		else if ( Nav_TrajectoryMode_en == Nav_ReverseLinearTrajectory_en )
		{

		}
		else if ( Nav_TrajectoryMode_en == Nav_ForwardAngularTrajectory_en )
		{
			Nav_TrapezeAngularVelocity2();
			Nav_vTargetAngleCalculationRoutine();
		}
		else if ( Nav_TrajectoryMode_en == Nav_ReverseAngularTrajectory_en )
		{
			Nav_TrapezeReverseAngularVelocity2();
			Nav_vTargetAngleCalculationRoutine();
		}
	}break;
	case Nav_Trajectory_ExecuteSuddenStop_en :
	{

		Nav_CurrentSample_u32++;
		if ( ( Nav_TrajectoryMode_en == Nav_ForwardLinearTrajectory_en ) || ( Nav_TrajectoryMode_en == Nav_ReverseLinearTrajectory_en ) )
		{
			Nav_TrapezeLinearVelocity2();
			Nav_vTargetDistanceCalculationRoutine();
		}
		else if ( Nav_TrajectoryMode_en == Nav_ForwardAngularTrajectory_en )
		{
			Nav_TrapezeAngularVelocity2();
			Nav_vTargetAngleCalculationRoutine();
		}
		else if ( Nav_TrajectoryMode_en == Nav_ReverseAngularTrajectory_en )
		{
			Nav_TrapezeReverseAngularVelocity2();
			Nav_vTargetAngleCalculationRoutine();
		}
		if( ( Nav_CurrentSample_u32 > Nav_AccelerationSamples_u32 )
				&& ( Nav_TargetLinearVelocity_d == 0 )
				&& ( Nav_TargetAngularVelocity_d == 0 )
				&& ( Nav_MeasuredVelocity_mm_d == 0 )
				&& ( Nav_MeasuredAngularVelocity_deg_d == 0 ))
		{
			Nav_Counter_u32 = 0 ;
			Nav_TrajectoryState_en = Nav_Trajectory_WaitAfterArriving_en;
		}

	}break;

	case Nav_Trajectory_WaitAfterArriving_en :
	{
		Nav_Counter_u32++;
		if (Nav_Counter_u32 > 2)
		{
			Nav_TrajectoryState_en = Nav_Trajectory_Finish_en;

		}
	}break;

	case Nav_Trajectory_Finish_en :
	{

	}break;
	}

}




void Nav_vTestPathStateMachine()
{
	switch( Nav_TestPathState_en )
	{

	case Nav_Test_Idle_en :
	{
		Nav_TestPathState_en = Nav_Test_Rotate_360deg_en;
	}break;


	case Nav_Test_WallAlign_en :
	{
		if ( Nav_WallAlignState_en == Nav_WallAlign_Idle_en )
		{
			Nav_MaxVelocity_d = -120 ; //400 ; //300 ;
			Nav_Acc_d = -350 ;
			Nav_TargetDistance_mm_d = -1000 ;
			Nav_WallAlignState_en = Nav_WallAlign_ResetVariables_en;
		}
		else if ( Nav_WallAlignState_en == Nav_WallAlign_Finish_en )
		{
//			Nav_TestPathState_en = Nav_Test_Forward_1000mm_en;
			Nav_WallAlignState_en = Nav_WallAlign_Idle_en ;
		}
		else
		{
			Nav_vWallAlign();
//			if(Nav_PrevRightTicks==Nav_RightTicks_i32)
//			{
//			MOTOR_PWM->RIGHT_FORWARD=0;
//			MOTOR_PWM->RIGHT_REVERSE=0;
//
//			}
//			Nav_PrevRightTicks=Nav_RightTicks_i32;
//
//
//
//			if(Nav_PrevLeftTicks==Nav_LeftTicks_i32)
//			{
//			MOTOR_PWM->LEFT_FORWARD=0;
//			MOTOR_PWM->LEFT_REVERSE=0;
//			}
//			Nav_PrevLeftTicks=Nav_LeftTicks_i32;
		}

	}break;

	case Nav_Test_Forward_1000mm_en :
	{
		if ( Nav_TrajectoryState_en == Nav_Trajectory_Idle_en )
		{
			Nav_TrajectoryMode_en = Nav_ForwardLinearTrajectory_en;
			Nav_MaxVelocity_d = 500 ; //400 ; //300 ;
			Nav_Acc_d = 400 ;
			Nav_TargetDistance_mm_d = 2100 ;
			Nav_TrajectoryState_en = Nav_Trajectory_ResetVariables_en;
		}
		else if ( Nav_TrajectoryState_en == Nav_Trajectory_Finish_en)
		{
			Nav_TestPathState_en = Nav_Test_Finished_en;
			Nav_TrajectoryState_en = Nav_Trajectory_Idle_en;
		}
		else
		{
			Nav_vTestPathIndependantTrajectoryStateMachine();
		}
	}break;

	case Nav_Test_Rotate_360deg_en :
	{
		if ( Nav_TrajectoryState_en == Nav_Trajectory_Idle_en )
		{
			Nav_TrajectoryMode_en = Nav_ForwardAngularTrajectory_en; //Nav_ReverseAngularTrajectory_en
			Nav_MaxAngularVelocity_d = 150 ; // 150 70 ;
			Nav_AngularAcc_d = 180 ; //230
			Nav_TargetAngle_deg_d = 360 ;
			Nav_TrajectoryState_en = Nav_Trajectory_ResetVariables_en;
		}
		else if ( Nav_TrajectoryState_en == Nav_Trajectory_Finish_en)
		{
			Nav_TestPathState_en = Nav_Test_Finished_en;
			Nav_TrajectoryState_en = Nav_Trajectory_Idle_en;
		}
		else
		{
			Nav_vTestPathIndependantTrajectoryStateMachine();
		}
	}break;

	case Nav_Test_Reverse_1000mm_en :
	{
		if ( Nav_TrajectoryState_en == Nav_Trajectory_Idle_en )
		{
			Nav_TrajectoryMode_en = Nav_ReverseLinearTrajectory_en;
			Nav_MaxVelocity_d = -500 ; //-400 ; //-300 ;
			Nav_Acc_d = -400 ;
			Nav_TargetDistance_mm_d = -2100 ;
			Nav_TrajectoryState_en = Nav_Trajectory_ResetVariables_en;
		}
		else if ( Nav_TrajectoryState_en == Nav_Trajectory_Finish_en)
		{
			Nav_TestPathState_en = Nav_Test_Finished_en;
			Nav_TrajectoryState_en = Nav_Trajectory_Idle_en;
		}
		else
		{
			Nav_vTestPathIndependantTrajectoryStateMachine();
		}
	}break;

	case Nav_Test_Finished_en :
	{
		//Nav_TestPathState_en = Nav_Test_Idle_en;
	}break;
	}

	Nav_vNavigationRoutine();
}


