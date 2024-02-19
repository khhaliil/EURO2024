/*
 * Navigation.c
 *
 *  Created on: Nov 17, 2023
 *      Author: Dhia Mnasri
 */

/* Includes BEGIN-------------------------------------------------------------*/
#include "main.h"
#include "NavConfig.h"
#include "NavTypes.h"
#include "NavConstants.h"
#include "Navigation.h"
#include "math.h"

/* Includes END---------------------------------------------------------------*/

/* Private define BEGIN-------------------------------------------------------*/

/* Private define END---------------------------------------------------------*/

/* External variables BEGIN---------------------------------------------------*/

extern float Nav_CurrentRobotLocation [3] ;

/* External variables END-----------------------------------------------------*/

/* Private variables BEGIN----------------------------------------------------*/

Nav_TestPathStates_ten Nav_TestPathState_en = Nav_Test_Idle_en ;
Nav_WallAlignStates_ten Nav_WallAlignState_en = Nav_WallAlign_Idle_en ;
Nav_ExecutePath_States_ten Nav_ExecutePath_State_en = Nav_ExecutePath_Idle_en;

Nav_Navigator_Indicators Nav_Navigator_Indicator = MASTER_Navigator_WaitForOrders ;
Nav_Navigator_States_en Nav_Navigator_CurrentState_en = Nav_Navigator_WaitForOrders_en ;
Nav_TrajectoryStates_ten Nav_TrajectoryState_en = Nav_Trajectory_Idle_en ;
Nav_TrajectoryModes_ten  Nav_TrajectoryMode_en = Nav_ForwardLinearTrajectory_en;
Nav_TrapezePhases_ten Nav_TrapezePhase_en = Nav_Trapeze_Accelerating_en ;
Nav_GoToXY_States_ten Nav_GoToXY_State_en = Nav_GoToXY_Idle_en ;



double Nav_XYTargets_ad[21][4] = {{0.0}};

uint8_t Nav_CurrentTargetNumber_u8 = 0 ;
uint8_t Nav_NumberOfTargets_u8 = 0 ;

extern Recieved_Orders_FromROS MASTER_Orders ;
ROBOT_CurrentState_typedef ROBOT_CurrentState_struct ;
uint8_t Nav_NavigatorMustAlert = 0 ;


double Nav_KpDistance_d    = 0 ;
double Nav_KiDistance_d    = 0 ;
double Nav_KdDistance_d    = 0 ;

double Nav_KpAngle_d       = 0 ;
double Nav_KiAngle_d       = 0 ;
double Nav_KdAngle_d       = 0 ;


int32_t Nav_RightTicks_i32           = 0 ;


int32_t Nav_LeftTicks_i32            = 0 ;


int32_t Nav_OverflowLeftEncoder_i32  = 0 ;
int32_t Nav_PrevLeftEncoderCNT_i32   = 0 ;
uint32_t Nav_Test_enter = 0 ;


double Nav_ConvertLeft_Ticks2mm_d     = 0.0 ;
double Nav_ConvertRight_Ticks2mm_d    = 0.0 ;

double Nav_MeasuredDistanceLeft_mm_d  = 0.0 ;
double Nav_MeasuredDistanceRight_mm_d = 0.0 ;

double Nav_MeasuredDistance_mm_d      = 0.0 ;
double Nav_PrevMeasuredDistance_mm_d  = 0.0 ;

double Nav_LimitDistance_mm_d         = 0.0 ;

double Nav_ReferenceAngle_deg_d = 0.0 ;
double Nav_ReferenceDistance_d = 0.0 ;


double Nav_MeasuredAngle_rad_d        = 0.0 ;
double Nav_PrevMeasuredAngle_rad_d    = 0.0 ;
double Nav_RemainingAngle_deg_d		  = 0.0 ;



double Nav_CurveCoefficient_d		  = 0.0 ;

double Nav_CurrentAngle_rad_d        = 0.0 ;
double Nav_PrevAngle_rad_d			 = 0.0 ;
double Nav_AverageAngle_rad_d		 = 0.0 ;
double Nav_CurrentAngle_deg_d        = 0.0 ;

double Nav_DeltaX_mm_d                = 0.0 ;
double Nav_DeltaY_mm_d                = 0.0 ;

double Nav_StartX_mm_d                = 500.0;
double Nav_StartY_mm_d                = 500.0;

double Nav_CurrentX_mm_d              = 0.0 ;
double Nav_CurrentY_mm_d              = 0.0 ;

double Nav_CurrentTargetX_mm_d		  = 0.0 ;
double Nav_CurrentTargetY_mm_d		  = 0.0 ;

double Nav_TargetX_mm_d              = 0.0 ;
double Nav_TargetY_mm_d              = 0.0 ;



double Nav_TargetArrivingAngle_deg_d = 0.0 ;
uint32_t Nav_Test_enter_2 = 0 ;

double Nav_TargetDistance_mm_d = 0.0 ;
double Nav_RemainingDistance_mm_d = 0.0 ;
double Nav_CurrentTargetDistance_mm_d = 0.0 ;
double Nav_PrevTargetDistance_mm_d = 0.0 ;

double Nav_TargetAngle_deg_d = 0.0 ;
double Nav_CurrentTargetAngle_deg_d   = 0.0 ;
double Nav_PrevTargetAngle_deg_d      = 0.0 ;

double Nav_TargetLinearVelocity_d   = 0.0 ;
double Nav_TargetAngularVelocity_d   = 0.0 ;
double Nav_ReferenceAngularVelocity_d = 0.0;

double Nav_MeasuredVelocity_mm_d      = 0.0 ;
double Nav_MeasuredAngularVelocity_rad_d = 0.0;
double Nav_MeasuredAngularVelocity_deg_d      = 0.0 ;
double Nav_ReferenceLinearVelocity_d  = 0.0 ;
double Nav_DistanceError_d           = 0.0 ;
double Nav_SumDistanceError_d        = 0.0 ;
double Nav_PID_DistanceOutput_d      = 0.0 ;

double Nav_AngleError_d              = 0.0 ;
double Nav_SumAngleError_d           = 0.0 ;
double Nav_PID_AngleOutput_d         = 0.0 ;



double Nav_Going_BackwardTargetX_mm_d = 0.0 ;
double Nav_Going_BackwardTargetY_mm_d = 0.0 ;
double Nav_GoingBackwardCurrentTargetX_mm_d  = 0.0 ;
double Nav_GoingBackwardCurrentTargetY_mm_d  = 0.0 ;

int32_t Nav_RightMotorCommand_i32 = 0.0 ;
int32_t Nav_LeftMotorCommand_i32  = 0.0 ;

int8_t Nav_RightMotorDirection_i8 = 1 ;
int8_t Nav_LeftMotorDirection_i8  = 1 ;

int32_t MONITOR_RightMotorCommand_i32 =0.0;
int32_t MONITOR_LeftMotorCommand_i32  =0.0;

double Nav_Acc_d           = 0.0 ;
double Nav_MaxVelocity_d   = 0.0 ;

double Nav_AngularAcc_d    = 0.0 ;
double Nav_MaxAngularVelocity_d = 0.0 ;

uint32_t Nav_CurrentSample_u32   = 0 ;

uint32_t Nav_AccelerationSamples_u32   = 0 ;


uint32_t Nav_Counter_u32 = 0;



float MASTER_Robot_State [2] = {50.0 , 0.0} ;

int8_t ROBOT_Direction = ROBOT_Going_Forward ;

/* Private variables END------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Private user code ---------------------------------------------------------*/


void Nav_vNavigatorInit()
{
	Nav_ConvertRight_Ticks2mm_d =( M_PI * WHEEL_DIAMETER_MM ) / ENCODER_RESOLUTION  ;
	Nav_ConvertLeft_Ticks2mm_d  = (  M_PI * WHEEL_DIAMETER_MM * LEFT_WHEEL_GAIN ) / ENCODER_RESOLUTION  ;
		Nav_CurrentX_mm_d = 0.0 ;
		Nav_CurrentY_mm_d =0;
	Nav_CurrentAngle_rad_d	= 0 ;
	Nav_CurrentAngle_deg_d = 0 ;
	Nav_CurrentTargetAngle_deg_d =0 ;
	Nav_PrevTargetAngle_deg_d =0 ;



	Nav_NumberOfTargets_u8 =4 ; // DYNAMICCCCC
//	Nav_XYTargets_ad[0][0] =700; 	Nav_XYTargets_ad[0][1] = 0	; 	Nav_XYTargets_ad[0][2] = 1000.0 ;   Nav_XYTargets_ad[0][3] = ROBOT_Going_Forward ;
//	Nav_XYTargets_ad[1][0] = 700 	; 	Nav_XYTargets_ad[1][1] = 700	; 	Nav_XYTargets_ad[1][2] = 1000 ;   Nav_XYTargets_ad[1][3] = ROBOT_Going_Forward ;
//	Nav_XYTargets_ad[2][0] = 0 ; 	Nav_XYTargets_ad[2][1] = 700 ;	Nav_XYTargets_ad[2][2] = 1000.0 ;   Nav_XYTargets_ad[2][3] = ROBOT_Going_Forward ;
//Nav_XYTargets_ad[3][0] = 0.0 	;   Nav_XYTargets_ad[3][1] = 0 	;	Nav_XYTargets_ad[3][2] = 0 ;   Nav_XYTargets_ad[3][3]  = ROBOT_Going_Forward;



	Nav_XYTargets_ad[0][0] = 1300 	; 	Nav_XYTargets_ad[0][1] = 0 	; 	Nav_XYTargets_ad[0][2] = 1000.0 ;   Nav_XYTargets_ad[0][3] = ROBOT_Going_Forward ;

	Nav_XYTargets_ad[1][0] = 1300	; 	Nav_XYTargets_ad[1][1] = 1600; 	;	Nav_XYTargets_ad[1][2] = 1000.0 ;   Nav_XYTargets_ad[1][3] = ROBOT_Going_Forward ;

		Nav_XYTargets_ad[2][0] = 0 ; 	Nav_XYTargets_ad[2][1] = 1600.0 ;	Nav_XYTargets_ad[2][2] = 1000.0 ;   Nav_XYTargets_ad[2][3] = ROBOT_Going_Forward ;

		Nav_XYTargets_ad[3][0] = 0.0 	;   Nav_XYTargets_ad[3][1] = 0.0 	;	Nav_XYTargets_ad[3][2] = 1000 ;   Nav_XYTargets_ad[3][3]  = ROBOT_Going_Backward ;
////
////		//pieton
//		Nav_XYTargets_ad[4][0] = 1740.0 	;   Nav_XYTargets_ad[4][1] = 1100 	;	Nav_XYTargets_ad[4][2] = 1000.0 ;   Nav_XYTargets_ad[4][3]  = ROBOT_Going_Forward ;
////baterie
//		Nav_XYTargets_ad[5][0] = 1740.0 	;   Nav_XYTargets_ad[5][1] = 2260 	;	Nav_XYTargets_ad[5][2] = 180 ;   Nav_XYTargets_ad[5][3]  = ROBOT_Going_Forward ;
//		// middle (982 ; 1543)
//		Nav_XYTargets_ad[6][0] = 982.0 	;   Nav_XYTargets_ad[6][1] = 1543.0	;	Nav_XYTargets_ad[6][2] = 1000 ;   Nav_XYTargets_ad[6][3]  = ROBOT_Going_Forward ;
//
//		// dodge (339;2263)
//		Nav_XYTargets_ad[7][0] =339.0 	;   Nav_XYTargets_ad[7][1] = 2263.0	;	Nav_XYTargets_ad[7][2] = 1000 ;   Nav_XYTargets_ad[7][3]  = ROBOT_Going_Forward ;
//		//(339,2964)
//
//		// cube  (339;2263) // fonctionnel jawou behi
//		Nav_XYTargets_ad[8][0] =339.0 	;   Nav_XYTargets_ad[8][1] = 2954.0	;	Nav_XYTargets_ad[8][2] = 1000 ;   Nav_XYTargets_ad[8][3]  = ROBOT_Going_Forward ;
//
//		// ^^^^^^^^^^^^^^^^^^^^fonctionnel jawou behi ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//		//not tested yet |||||||||||||||||||||||||||
//
//		//(339,2964) push cube
//		Nav_XYTargets_ad[9][0] =339.0 	;   Nav_XYTargets_ad[9][1] = 2954.0	;	Nav_XYTargets_ad[9][2] = 1000 ;   Nav_XYTargets_ad[9][3]  = ROBOT_Going_Forward ;
//		//backing after pushing cube
//		Nav_XYTargets_ad[10][0] =339.0 	;   Nav_XYTargets_ad[10][1] = 2604.0	;	Nav_XYTargets_ad[10][2] = 1000 ;   Nav_XYTargets_ad[10][3]  = ROBOT_Going_Forward ;
//
//		// going to scan bars
//		Nav_XYTargets_ad[11][0] =1333.0 	;   Nav_XYTargets_ad[11][1] = 2604.0	;	Nav_XYTargets_ad[11][2] = 1000 ;   Nav_XYTargets_ad[11][3]  = ROBOT_Going_Forward ;
//
//		// going to position to push (1864;2463.9)
//		Nav_XYTargets_ad[12][0] =1864.0 	;   Nav_XYTargets_ad[12][1] = 2464.0	;	Nav_XYTargets_ad[12][2] = 1000 ;   Nav_XYTargets_ad[12][3]  = ROBOT_Going_Forward ;
//
//		// pushing  (1964;2463.9)
//		Nav_XYTargets_ad[13][0] =1954.0 	;   Nav_XYTargets_ad[13][1] = 2464.0	;	Nav_XYTargets_ad[13][2] = 1000 ;   Nav_XYTargets_ad[13][3]  = ROBOT_Going_Forward ;
//		// the end (-200;2604)
//		Nav_XYTargets_ad[14][0] =20.0 	;   Nav_XYTargets_ad[14][1] = 2604.0	;	Nav_XYTargets_ad[14][2] = 1000 ;   Nav_XYTargets_ad[14][3]  = ROBOT_Going_Forward ;
}




void Nav_TrapezeLinearVelocity2()
{
	switch( Nav_TrapezePhase_en )
	{
	case Nav_Trapeze_Idle_en:
	{

	}break;
	case Nav_Trapeze_Accelerating_en:
	{
		Nav_ReferenceDistance_d = (Nav_TargetLinearVelocity_d * Nav_TargetLinearVelocity_d) / ( 2 * Nav_Acc_d ) ;

		if( Nav_RemainingDistance_mm_d < 2.0 ) // calibring seuil
		{
			if( Nav_RemainingDistance_mm_d > Nav_ReferenceDistance_d )
			{
				if ( Nav_TargetLinearVelocity_d < Nav_MaxVelocity_d )
				{
					Nav_TargetLinearVelocity_d = Nav_Acc_d * Nav_CurrentSample_u32 ;
				}
				else
				{
					Nav_TrapezePhase_en = Nav_Trapeze_ConstantVelocity_en;
				}
			}
			else
			{
				Nav_AccelerationSamples_u32 = Nav_CurrentSample_u32 - 1;
				Nav_ReferenceLinearVelocity_d = Nav_TargetLinearVelocity_d;
				Nav_TrapezePhase_en = Nav_Trapeze_Decelerating_en;
			}
		}
		else
		{
			if( Nav_RemainingDistance_mm_d > ( Nav_ReferenceDistance_d + 2.0 ) )
			{
				if ( Nav_TargetLinearVelocity_d < Nav_MaxVelocity_d )
				{
					Nav_TargetLinearVelocity_d = Nav_Acc_d * Nav_CurrentSample_u32 ;
				}
				else
				{
					Nav_TrapezePhase_en = Nav_Trapeze_ConstantVelocity_en;
				}
			}
			else
			{
				Nav_AccelerationSamples_u32 = Nav_CurrentSample_u32 - 1;
				Nav_ReferenceLinearVelocity_d = Nav_TargetLinearVelocity_d;
				Nav_TrapezePhase_en = Nav_Trapeze_Decelerating_en;
			}
		}




	}break;

	case Nav_Trapeze_ConstantVelocity_en:
	{
		Nav_ReferenceDistance_d = (Nav_TargetLinearVelocity_d * Nav_TargetLinearVelocity_d) / ( 2 * Nav_Acc_d ) ;
		if( Nav_RemainingDistance_mm_d > ( Nav_ReferenceDistance_d + 2.0 ) )
		{
			Nav_TargetLinearVelocity_d = Nav_MaxVelocity_d ;
		}
		else
		{
			Nav_AccelerationSamples_u32 = Nav_CurrentSample_u32 - 1;
			Nav_ReferenceLinearVelocity_d = Nav_TargetLinearVelocity_d;
			Nav_TrapezePhase_en = Nav_Trapeze_Decelerating_en;
		}
	}break;

	case Nav_Trapeze_Decelerating_en:
	{
		Nav_ReferenceDistance_d = (Nav_TargetLinearVelocity_d * Nav_TargetLinearVelocity_d) / ( 2 * Nav_Acc_d ) ;

		if( Nav_RemainingDistance_mm_d >= Nav_ReferenceDistance_d )
		{
			Nav_ReferenceLinearVelocity_d = Nav_TargetLinearVelocity_d;
			Nav_AccelerationSamples_u32 = Nav_CurrentSample_u32 - 1;
		}
		else
		{
			Nav_TargetLinearVelocity_d = Nav_ReferenceLinearVelocity_d - ( Nav_Acc_d * ( Nav_CurrentSample_u32 -Nav_AccelerationSamples_u32 ) )  ;
		}

		if( ( Nav_RemainingDistance_mm_d <= 0.0 ) || ( Nav_TargetLinearVelocity_d <= 0.0) )
		{
			Nav_TargetLinearVelocity_d = 0 ;
			Nav_TrapezePhase_en = Nav_Trapeze_Finished_en ;
		}

	}break;
	case Nav_Trapeze_OrderUrgentDecelerating_en:
	{
		Nav_AccelerationSamples_u32 = Nav_CurrentSample_u32 - 1;
		Nav_ReferenceLinearVelocity_d = Nav_TargetLinearVelocity_d;
		Nav_TrapezePhase_en = Nav_Trapeze_UrgentDecelerating_en;
	}break;
	case Nav_Trapeze_UrgentDecelerating_en:
	{
		Nav_TargetLinearVelocity_d = Nav_ReferenceLinearVelocity_d - ( Nav_Acc_d * ( Nav_CurrentSample_u32 -Nav_AccelerationSamples_u32 ) )  ;
		if(  Nav_TargetLinearVelocity_d < 0.0)
		{
			Nav_TargetLinearVelocity_d = 0 ;
			Nav_TrapezePhase_en = Nav_Trapeze_Finished_en ;
		}
	}break;


	case Nav_Trapeze_Finished_en:
	{
		Nav_TargetLinearVelocity_d = 0.0 ;
		Nav_TrapezePhase_en = Nav_Trapeze_Idle_en ;
	}break;

	}
}

void Nav_TrapezeReverseLinearVelocity2()
{
	switch( Nav_TrapezePhase_en )
	{
	case Nav_Trapeze_Idle_en:
	{

	}break;
	case Nav_Trapeze_Accelerating_en:
	{

		Nav_ReferenceDistance_d = (Nav_TargetLinearVelocity_d * Nav_TargetLinearVelocity_d) / ( 2 * Nav_Acc_d ) ;
		if( Nav_RemainingDistance_mm_d > (-2.0) )
		{
			if( Nav_RemainingDistance_mm_d <  Nav_ReferenceDistance_d  )
			{
				if ( Nav_TargetLinearVelocity_d > Nav_MaxVelocity_d )
				{
					Nav_TargetLinearVelocity_d = Nav_Acc_d * Nav_CurrentSample_u32 ;
				}
				else
				{
					Nav_TrapezePhase_en = Nav_Trapeze_ConstantVelocity_en;
				}
			}
			else
			{
				Nav_AccelerationSamples_u32 = Nav_CurrentSample_u32 - 1;
				Nav_ReferenceLinearVelocity_d = Nav_TargetLinearVelocity_d;
				Nav_TrapezePhase_en = Nav_Trapeze_Decelerating_en;
			}
		}
		else
		{
			if( Nav_RemainingDistance_mm_d <  ( Nav_ReferenceDistance_d - 2.0 ) )
			{
				if ( Nav_TargetLinearVelocity_d > Nav_MaxVelocity_d )
				{
					Nav_TargetLinearVelocity_d = Nav_Acc_d * Nav_CurrentSample_u32 ;
				}
				else
				{
					Nav_TrapezePhase_en = Nav_Trapeze_ConstantVelocity_en;
				}
			}
			else
			{
				Nav_AccelerationSamples_u32 = Nav_CurrentSample_u32 - 1;
				Nav_ReferenceLinearVelocity_d = Nav_TargetLinearVelocity_d;
				Nav_TrapezePhase_en = Nav_Trapeze_Decelerating_en;
			}
		}

	}break;

	case Nav_Trapeze_ConstantVelocity_en:
	{
		Nav_ReferenceDistance_d = (Nav_TargetLinearVelocity_d * Nav_TargetLinearVelocity_d) / ( 2 * Nav_Acc_d ) ;
		if( Nav_RemainingDistance_mm_d < ( Nav_ReferenceDistance_d - 2.0 ) )
		{
			Nav_TargetLinearVelocity_d = Nav_MaxVelocity_d ;
		}
		else
		{
			Nav_AccelerationSamples_u32 = Nav_CurrentSample_u32 - 1;
			Nav_ReferenceLinearVelocity_d = Nav_TargetLinearVelocity_d;
			Nav_TrapezePhase_en = Nav_Trapeze_Decelerating_en;
		}
	}break;

	case Nav_Trapeze_Decelerating_en:
	{
		Nav_ReferenceDistance_d = (Nav_TargetLinearVelocity_d * Nav_TargetLinearVelocity_d) / ( 2 * Nav_Acc_d ) ;

		if( Nav_RemainingDistance_mm_d <= Nav_ReferenceDistance_d )
		{
			Nav_ReferenceLinearVelocity_d = Nav_TargetLinearVelocity_d;
			Nav_AccelerationSamples_u32 = Nav_CurrentSample_u32 - 1;
		}
		else
		{
			Nav_TargetLinearVelocity_d = Nav_ReferenceLinearVelocity_d - ( Nav_Acc_d * ( Nav_CurrentSample_u32 -Nav_AccelerationSamples_u32 ) )  ;
		}

		if( ( Nav_RemainingDistance_mm_d >= 0.0 ) || ( Nav_TargetLinearVelocity_d >= 0.0) )
		{
			Nav_TargetLinearVelocity_d = 0 ;
			Nav_TrapezePhase_en = Nav_Trapeze_Finished_en ;
		}

	}break;
	case Nav_Trapeze_OrderUrgentDecelerating_en:
	{
		Nav_AccelerationSamples_u32 = Nav_CurrentSample_u32 - 1;
		Nav_ReferenceLinearVelocity_d = Nav_TargetLinearVelocity_d;
		Nav_TrapezePhase_en = Nav_Trapeze_UrgentDecelerating_en;
	}break;
	case Nav_Trapeze_UrgentDecelerating_en:
	{
		Nav_TargetLinearVelocity_d = Nav_ReferenceLinearVelocity_d - ( Nav_Acc_d * ( Nav_CurrentSample_u32 -Nav_AccelerationSamples_u32 ) )  ;
		if(  Nav_TargetLinearVelocity_d >= 0.0)
		{
			Nav_TargetLinearVelocity_d = 0 ;
			Nav_TrapezePhase_en = Nav_Trapeze_Finished_en ;
		}
	}break;


	case Nav_Trapeze_Finished_en:
	{
		Nav_TargetLinearVelocity_d = 0.0 ;
		Nav_TrapezePhase_en = Nav_Trapeze_Idle_en ;
	}break;

	}
}


void Nav_TrapezeAngularVelocity2()
{
	switch( Nav_TrapezePhase_en )
	{

	case Nav_Trapeze_Idle_en:
	{

	}break;
	case Nav_Trapeze_Accelerating_en:
	{
		Nav_ReferenceAngle_deg_d = ( Nav_TargetAngularVelocity_d * Nav_TargetAngularVelocity_d) / ( 2 * Nav_AngularAcc_d ) ;

		if( Nav_RemainingAngle_deg_d < 2.0 )
		{
			if( Nav_RemainingAngle_deg_d > Nav_ReferenceAngle_deg_d )
			{
				if ( Nav_TargetAngularVelocity_d < Nav_MaxAngularVelocity_d  )
				{
					Nav_TargetAngularVelocity_d = Nav_AngularAcc_d * Nav_CurrentSample_u32 ;
				}
				else
				{
					Nav_TrapezePhase_en = Nav_Trapeze_ConstantVelocity_en;
				}
			}
			else
			{
				Nav_AccelerationSamples_u32 = Nav_CurrentSample_u32 - 1;
				Nav_ReferenceAngularVelocity_d = Nav_TargetAngularVelocity_d;
				Nav_TrapezePhase_en = Nav_Trapeze_Decelerating_en;
			}
		}

		else
		{
			if( Nav_RemainingAngle_deg_d > ( Nav_ReferenceAngle_deg_d + 2.0 ) )
			{
				if ( Nav_TargetAngularVelocity_d < Nav_MaxAngularVelocity_d  )
				{
					Nav_TargetAngularVelocity_d = Nav_AngularAcc_d * Nav_CurrentSample_u32 ;
				}
				else
				{
					Nav_TrapezePhase_en = Nav_Trapeze_ConstantVelocity_en;
				}
			}
			else
			{
				Nav_AccelerationSamples_u32 = Nav_CurrentSample_u32 - 1;
				Nav_ReferenceAngularVelocity_d = Nav_TargetAngularVelocity_d;
				Nav_TrapezePhase_en = Nav_Trapeze_Decelerating_en;
			}
		}


	}break;

	case Nav_Trapeze_ConstantVelocity_en:
	{
		Nav_ReferenceAngle_deg_d = ( Nav_TargetAngularVelocity_d * Nav_TargetAngularVelocity_d) / ( 2 * Nav_AngularAcc_d ) ;
		if( Nav_RemainingAngle_deg_d > ( Nav_ReferenceAngle_deg_d + 2.0 ) )
		{
			Nav_TargetAngularVelocity_d = Nav_MaxAngularVelocity_d ;
		}
		else
		{
			Nav_AccelerationSamples_u32 = Nav_CurrentSample_u32 - 1;
			Nav_ReferenceAngularVelocity_d = Nav_TargetAngularVelocity_d;
			Nav_TrapezePhase_en = Nav_Trapeze_Decelerating_en;
		}
	}break;

	case Nav_Trapeze_Decelerating_en:
	{
		Nav_ReferenceAngle_deg_d = ( Nav_TargetAngularVelocity_d * Nav_TargetAngularVelocity_d) / ( 2 * Nav_AngularAcc_d ) ;
		if( Nav_RemainingAngle_deg_d > Nav_ReferenceAngle_deg_d )
		{
			Nav_ReferenceAngularVelocity_d = Nav_TargetAngularVelocity_d;
			Nav_AccelerationSamples_u32 = Nav_CurrentSample_u32 - 1;
		}
		else
		{
			Nav_TargetAngularVelocity_d = Nav_ReferenceAngularVelocity_d - ( Nav_AngularAcc_d * ( Nav_CurrentSample_u32 -Nav_AccelerationSamples_u32 ) )  ;
		}

		if( ( Nav_RemainingAngle_deg_d <= 0.0 ) || (Nav_TargetAngularVelocity_d <= 0.0) )
		{
			Nav_TargetAngularVelocity_d = 0 ;
			Nav_TrapezePhase_en = Nav_Trapeze_Finished_en ;
		}
	}break;
	case Nav_Trapeze_OrderUrgentDecelerating_en:
	{
		Nav_AccelerationSamples_u32 = Nav_CurrentSample_u32 - 1;
		Nav_ReferenceLinearVelocity_d = Nav_TargetLinearVelocity_d;
		Nav_TrapezePhase_en = Nav_Trapeze_UrgentDecelerating_en;
	}break;
	case Nav_Trapeze_UrgentDecelerating_en :
	{
		Nav_TargetAngularVelocity_d = Nav_ReferenceAngularVelocity_d - ( Nav_AngularAcc_d * ( Nav_CurrentSample_u32 -Nav_AccelerationSamples_u32 ) )  ;

		if( ( Nav_RemainingAngle_deg_d <= 0.0 ) || (Nav_TargetAngularVelocity_d <= 0.0) )
		{
			Nav_TargetAngularVelocity_d = 0 ;
			Nav_TrapezePhase_en = Nav_Trapeze_Finished_en ;
		}
	}break ;
	case Nav_Trapeze_Finished_en:
	{
		Nav_TargetAngularVelocity_d = 0.0 ;
		Nav_TrapezePhase_en = Nav_Trapeze_Idle_en ;
	}break;

	}
}

void Nav_TrapezeReverseAngularVelocity2()
{
	switch( Nav_TrapezePhase_en )
	{

	case Nav_Trapeze_Idle_en:
	{

	}break;
	case Nav_Trapeze_Accelerating_en:
	{
		Nav_ReferenceAngle_deg_d = ( Nav_TargetAngularVelocity_d * Nav_TargetAngularVelocity_d) / ( 2 * Nav_AngularAcc_d ) ;

		if( Nav_RemainingAngle_deg_d > (-2.0) )
		{
			if( Nav_RemainingAngle_deg_d < Nav_ReferenceAngle_deg_d )
			{
				if ( Nav_TargetAngularVelocity_d > Nav_MaxAngularVelocity_d  )
				{
					Nav_TargetAngularVelocity_d = Nav_AngularAcc_d * Nav_CurrentSample_u32 ;
				}
				else
				{
					Nav_TrapezePhase_en = Nav_Trapeze_ConstantVelocity_en;
				}
			}
			else
			{
				Nav_AccelerationSamples_u32 = Nav_CurrentSample_u32 - 1;
				Nav_ReferenceAngularVelocity_d = Nav_TargetAngularVelocity_d;
				Nav_TrapezePhase_en = Nav_Trapeze_Decelerating_en;
			}
		}
		else
		{
			if( Nav_RemainingAngle_deg_d < ( Nav_ReferenceAngle_deg_d - 2.0 ) )
			{
				if ( Nav_TargetAngularVelocity_d > Nav_MaxAngularVelocity_d  )
				{
					Nav_TargetAngularVelocity_d = Nav_AngularAcc_d * Nav_CurrentSample_u32 ;
				}
				else
				{
					Nav_TrapezePhase_en = Nav_Trapeze_ConstantVelocity_en;
				}
			}
			else
			{
				Nav_AccelerationSamples_u32 = Nav_CurrentSample_u32 - 1;
				Nav_ReferenceAngularVelocity_d = Nav_TargetAngularVelocity_d;
				Nav_TrapezePhase_en = Nav_Trapeze_Decelerating_en;
			}
		}


	}break;

	case Nav_Trapeze_ConstantVelocity_en:
	{
		Nav_ReferenceAngle_deg_d = ( Nav_TargetAngularVelocity_d * Nav_TargetAngularVelocity_d) / ( 2 * Nav_AngularAcc_d ) ;
		if( Nav_RemainingAngle_deg_d < ( Nav_ReferenceAngle_deg_d /*- 2.0*/ ))
		{
			Nav_TargetAngularVelocity_d = Nav_MaxAngularVelocity_d ;
		}
		else
		{
			Nav_AccelerationSamples_u32 = Nav_CurrentSample_u32 - 1;
			Nav_ReferenceAngularVelocity_d = Nav_TargetAngularVelocity_d;
			Nav_TrapezePhase_en = Nav_Trapeze_Decelerating_en;
		}
	}break;

	case Nav_Trapeze_Decelerating_en:
	{
		Nav_ReferenceAngle_deg_d = ( Nav_TargetAngularVelocity_d * Nav_TargetAngularVelocity_d) / ( 2 * Nav_AngularAcc_d ) ;
		if( Nav_RemainingAngle_deg_d < Nav_ReferenceAngle_deg_d )
		{
			Nav_ReferenceAngularVelocity_d = Nav_TargetAngularVelocity_d;
			Nav_AccelerationSamples_u32 = Nav_CurrentSample_u32 - 1;
		}
		else
		{
			Nav_TargetAngularVelocity_d = Nav_ReferenceAngularVelocity_d - ( Nav_AngularAcc_d * ( Nav_CurrentSample_u32 -Nav_AccelerationSamples_u32 ) )  ;
		}

		if( ( Nav_RemainingAngle_deg_d >= 0.0 ) || (Nav_TargetAngularVelocity_d >= 0.0) )
		{
			Nav_TargetAngularVelocity_d = 0 ;
			Nav_TrapezePhase_en = Nav_Trapeze_Finished_en ;
		}
	}break;
	case Nav_Trapeze_OrderUrgentDecelerating_en:
	{
		Nav_AccelerationSamples_u32 = Nav_CurrentSample_u32 - 1;
		Nav_ReferenceLinearVelocity_d = Nav_TargetLinearVelocity_d;
		Nav_TrapezePhase_en = Nav_Trapeze_UrgentDecelerating_en;
	}break;
	case Nav_Trapeze_UrgentDecelerating_en :
	{
		Nav_TargetAngularVelocity_d = Nav_ReferenceAngularVelocity_d - ( Nav_AngularAcc_d * ( Nav_CurrentSample_u32 -Nav_AccelerationSamples_u32 ) )  ;
		if( ( Nav_RemainingAngle_deg_d >= 0.0 ) || (Nav_TargetAngularVelocity_d >= 0.0) )
		{
			Nav_TargetAngularVelocity_d = 0 ;
			Nav_TrapezePhase_en = Nav_Trapeze_Finished_en ;
		}

	}break;

	case Nav_Trapeze_Finished_en:
	{
		Nav_TargetAngularVelocity_d = 0.0 ;
		Nav_TrapezePhase_en = Nav_Trapeze_Idle_en ;
	}break;

	}

}



void Nav_vTargetDistanceCalculationRoutine()
{
	Nav_CurrentTargetDistance_mm_d = Nav_PrevTargetDistance_mm_d + Nav_TargetLinearVelocity_d ;
	Nav_PrevTargetDistance_mm_d = Nav_CurrentTargetDistance_mm_d ;
}

void Nav_vTargetAngleCalculationRoutine()
{
	Nav_CurrentTargetAngle_deg_d = Nav_PrevTargetAngle_deg_d + Nav_TargetAngularVelocity_d ;
	Nav_PrevTargetAngle_deg_d = Nav_CurrentTargetAngle_deg_d;
}



void Nav_vSaturateRemainingAngle()
{
	if( Nav_RemainingAngle_deg_d > 180 )
	{
		Nav_RemainingAngle_deg_d -= 360;
	}
	else if ( Nav_RemainingAngle_deg_d < -180 )
	{
		Nav_RemainingAngle_deg_d += 360;
	}
	if( (  Nav_RemainingAngle_deg_d > 177 )|| ( Nav_RemainingAngle_deg_d < -177 ) )
	{
		Nav_RemainingAngle_deg_d = 177;
	}
}

void Nav_vCurrentTargetAngleFollower()
{

	if( (Nav_CurrentTargetAngle_deg_d - Nav_CurrentAngle_deg_d) > 340.0  )
	{
		Nav_CurrentAngle_deg_d += 360.0;
		Nav_CurrentAngle_rad_d += M_2PI ;
		Nav_PrevAngle_rad_d += M_2PI ;
	}
	else if( ( Nav_CurrentAngle_deg_d - Nav_CurrentTargetAngle_deg_d) > 340.0 )
	{

		Nav_CurrentAngle_deg_d -=  (double) 360.0;
		Nav_CurrentAngle_rad_d -=((double) M_2PI) ;
		Nav_PrevAngle_rad_d -=  ((double) M_2PI );
	}
}

void Nav_vWallAlign()
{
	switch(Nav_WallAlignState_en)
	{

	case Nav_WallAlign_Idle_en :
	{
		//HAL_Delay(10000);

	}break;
	case Nav_WallAlign_ResetVariables_en :
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
		Nav_Counter_u32 = 0;

		Nav_WallAlignState_en = Nav_WallAlign_SetTarget_en;
	}break;

	case Nav_WallAlign_SetTarget_en :
	{
		Nav_MaxVelocity_d = Nav_MaxVelocity_d * SAMPLING_PERIOD ;
		Nav_Acc_d = Nav_Acc_d * SAMPLING_PERIOD * SAMPLING_PERIOD ;
		REVERSE_LINEAR_TRAJECTORY_PID
		Nav_WallAlignState_en = Nav_WallAlign_ConstantVelocityMove_en;


	}break;
	case Nav_WallAlign_ConstantVelocityMove_en :
	{
		Nav_CurrentSample_u32++;
		Nav_RemainingDistance_mm_d = -1000.0;
		Nav_TrapezeReverseLinearVelocity2();
		Nav_vTargetDistanceCalculationRoutine();
		if(  ( Nav_CurrentSample_u32 >  100  )
				&& ( Nav_MeasuredVelocity_mm_d == 0 )
				&& ( Nav_MeasuredAngularVelocity_deg_d == 0 ))
		{
			Nav_Counter_u32++;
		}
		else
		{
			Nav_Counter_u32 = 0;
		}
		if  ( Nav_Counter_u32 > 3 )
		{
			Nav_TargetLinearVelocity_d = 0.0 ;
			Nav_TrapezePhase_en = Nav_Trapeze_Idle_en ;
			Nav_WallAlignState_en = Nav_WallAlign_ArrivedAtWall_en;
		}

	}break;

	case Nav_WallAlign_ArrivedAtWall_en :
	{
		//reset the current sample
		Nav_CurrentSample_u32 = 0;

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

		Nav_CurrentX_mm_d = 0.0 ;
		Nav_CurrentY_mm_d = 0.0 ;
		Nav_CurrentAngle_rad_d	= 0 ;
		Nav_CurrentAngle_deg_d = 0 ;
		Nav_CurrentTargetAngle_deg_d = 0 ;
		Nav_PrevTargetAngle_deg_d = 0 ;


		Nav_WallAlignState_en = Nav_WallAlign_Finish_en;
	}break;


	case Nav_WallAlign_Finish_en :
	{
		//Nav_Test_enter = 1;
		Nav_WallAlignState_en = Nav_WallAlign_Idle_en;
	}break;
}

}



void Nav_Navigator_StateMachine ()
{
	switch (Nav_Navigator_CurrentState_en)
	{
	case Nav_Navigator_WaitForOrders_en :

	{


		//		Nav_Navigator_Indicator =MASTER_Navigator_WaitForOrders ;

		// Transition to next State will be a consequence of an INdicator , The Indicator value is changed in MASTER_NavigatorResponsetoMaster .
		if  ( ( Nav_Navigator_Indicator == MASTER_Navigator_Can_GO_Forward ) || ( Nav_Navigator_Indicator == MASTER_Navigator_Can_Go_Backward ) )
		{
			Nav_Navigator_CurrentState_en = Nav_Navigator_StartExecutingPath_en ;
			ROBOT_Direction = Nav_Navigator_Indicator ; // Its either forward "3" or backward "4"
		}




	}break ;

	case Nav_Navigator_StartExecutingPath_en :
	{
		if ( Nav_Navigator_Indicator == MASTER_Navigator_Stop_Flag )
		{
			Nav_Navigator_CurrentState_en = Nav_Navigator_SuddenStop_en ;
			Nav_GoToXY_State_en = Nav_GoToXY_OrderSuddenStop_en   ; 		 // A redefinir Nav_GoToXY_SuddenStop_en
		}
		else
		{
			Nav_Navigator_Indicator = MASTER_Navigator_MessageRecieved ;
		}

		if ( Nav_GoToXY_State_en == Nav_GoToXY_Idle_en )
		{
			Nav_TargetX_mm_d 	 = (double)( MASTER_Orders.X_target_i32 );
			Nav_TargetY_mm_d 	 = (double) MASTER_Orders.Y_Target_i32 ;
			Nav_TargetArrivingAngle_deg_d = (double) MASTER_Orders.TETA_Target_i32 ;
			Nav_GoToXY_State_en = Nav_GoToXY_Rotate_en ;
		}

		else if ( Nav_GoToXY_State_en == Nav_GoToXY_Finished_en )
		{
			// Send to CM4 eli enty wselt lel blasa li hachtek biha
			Nav_Navigator_Indicator = MASTER_Navigator_WaitForOrders ;
			Nav_NavigatorMustAlert = 1 ;
			Nav_GoToXY_State_en = Nav_GoToXY_Idle_en ;
			Nav_Navigator_CurrentState_en = Nav_Navigator_Finished_en ;
		}
		else
		{
			Nav_vGoToXYStateMachine_BOB();
		}

	}break;

	case Nav_Navigator_SuddenStop_en :
	{
		// Let the master know you stopped

		if ( Nav_GoToXY_State_en == Nav_GoToXY_Finished_en )
		{
			// Send to CM4 eli enty wselt lel blasa li hachtek biha
			Nav_Navigator_Indicator = MASTER_Navigator_Stop_Flag ;
			Nav_NavigatorMustAlert = 1 ;
			Nav_GoToXY_State_en = Nav_GoToXY_Idle_en ;
			Nav_Navigator_CurrentState_en = Nav_Navigator_WaitForOrders_en ;
		}

		else
		{
			Nav_vGoToXYStateMachine_BOB();
		}

	}break;
	case Nav_Navigator_ConfirmedStop_en :
	{
		// Let the master know you stopped

	}break;
	case Nav_Navigator_Finished_en :
	{
		Nav_Navigator_Indicator = MASTER_Navigator_WaitForOrders ;
		Nav_Navigator_CurrentState_en = Nav_Navigator_WaitForOrders_en ;

	}break;
	}

	Nav_vNavigationRoutine();

	// State updating
	ROBOT_CurrentState_struct.Indicator 			= Nav_Navigator_Indicator  ;
	ROBOT_CurrentState_struct.Current_X_i32			= Nav_CurrentX_mm_d ;
	ROBOT_CurrentState_struct.Current_Y_i32    		= Nav_CurrentY_mm_d ;
	ROBOT_CurrentState_struct.Current_TETA_i32 		= Nav_CurrentAngle_deg_d ;
	ROBOT_CurrentState_struct.Current_Velocity_i32 	= Nav_MeasuredVelocity_mm_d * 1000 ;
}



//	case Nav_ExecutePath_WallAlign_en :
//	{
//		if ( Nav_WallAlignState_en == Nav_WallAlign_Idle_en )
//		{
//			ROBOT_Direction = ROBOT_Going_Backward ;
//			Nav_MaxVelocity_d = -120 ; //400 ; //300 ;
//			Nav_Acc_d = -200 ;
//			Nav_TargetDistance_mm_d = -1000 ;
//			Nav_WallAlignState_en = Nav_WallAlign_ResetVariables_en;
//		}
//		else if ( Nav_WallAlignState_en == Nav_WallAlign_Finish_en )
//		{
//			Nav_ExecutePath_State_en = Nav_ExecutePath_SetNextTarget_en;
//			Nav_WallAlignState_en = Nav_WallAlign_Idle_en ;
//		}
//		else
//		{
//			Nav_vWallAlign();
//		}
//	}break;
