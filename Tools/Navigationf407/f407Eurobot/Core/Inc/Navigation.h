/*
 * Navigation.h
 *
 *  Created on: Nov 17, 2023
 *      Author: Dhia Mnasri
 */

#ifndef INC_NAVIGATION_H_
#define INC_NAVIGATION_H_

void Nav_vTestPathStateMachine();
void Nav_vNavigatorInit();
void Nav_vNavigationRoutine();
void Nav_vFeedbackRoutine();
void Nav_vLocalisation();
void Nav_vPidDistance();
void Nav_vPidAngle();
void Nav_vCalculateMotorsCommand();
void Nav_vMotorsRoutine();
void Nav_vTargetDistanceCalculationRoutine();
void Nav_vTargetAngleCalculationRoutine();
void Nav_vCalculateLinearTrajectory();
void Nav_vCalculateAngularTrajectory();
void Nav_TrapezeLinearVelocity();
void Nav_TrapezeAngularVelocity();
void Nav_TrapezeLinearVelocity2();
void Nav_TrapezeAngularVelocity2();
void Nav_TrapezeReverseAngularVelocity2();
void Nav_vSaturateRemainingAngle();
void Nav_vIndependantTrajectoryStateMachine();
void Nav_vTestPathIndependantTrajectoryStateMachine();
void Nav_Navigator_StateMachine ();
void Nav_vCurrentTargetAngleFollower();
void Nav_vGoToXYStateMachine();
void Nav_vExecutePath();
void Nav_TrapezeReverseLinearVelocity2 ();
void Nav_vGoToXYStateMachine_BOB ();
void Nav_vWallAlign();


#endif /* INC_NAVIGATION_H_ */
