#!/usr/bin/env python3
import rospy
from enum import Enum
import time
import smach
import smach_ros
from std_msgs.msg import (Bool, Float32MultiArray, Int8, Int8MultiArray,
                          Int32MultiArray, String)

from ros_can_interface.msg import master_acknowledgSignal
from ros_can_interface.msg import master_navigationMessage
from ros_can_interface.msg import lidar_stopSignal


##################################### TYPEDEF ENUMS HERE ###############################
class MASTER_SMachineStates_ten (Enum):

    MASTER_SMachine_Idle_en = 0
    MASTER_SMachine_WaitForSignal_en = 1
    MASTER_SMachine_MoveOn_en = 2
    MASTER_SMachine_WaitToReach_en = 3
    MASTER_SMachine_DestinationReached_en = 4

    MASTER_SMachine_SuddenStop_en = 5
    MASTER_SMachine_ConfirmedStop_en = 6
    
    MASTER_SMachine_Finish_en = 7

class MASTER_NavigatorStates_ten (Enum):

    MASTER_NavigatorIdle_en = 0
    MASTER_NavigatorReady_en = 1
    MASTER_NavigatorBusy_en = 2
    MASTER_NvigatorWaitToReceiveAcknowledge_en = 3
    MASTER_NavigatorReachedDest_en = 4
    MASTER_NavigatorConfirmedStop_en = 5
    
##################################### DECLARE VARIABLES HERE #####################################

MASTER_CurrentNavigatorState_en = MASTER_NavigatorStates_ten.MASTER_NavigatorIdle_en
MASTER_SMachineCurrentState_en = MASTER_SMachineStates_ten.MASTER_SMachine_Idle_en

navigation_targets = [
    master_navigationMessage(1000, 0, 655, True),
]

current_target = 0

#################################### CREATE A CLASS OF PUBLISHERS #################################

class Publishers:
    globalNavigator_Acknowledge_Publisher = rospy.Publisher('/ros_can_interface/master_acknowledge', master_acknowledgSignal, queue_size=10)
    Navigator_Target_Publisher = rospy.Publisher('/ros_can_interface/navigation_data', master_navigationMessage, queue_size=10)
    Navigator_Stop_Publisher = rospy.Publisher('/ros_can_interface/stopSignal', lidar_stopSignal, queue_size=10)

################################### NAVIGATION FUNCTIONS CLASS #######################

class Navigation:
    # Constants
    communication_wait_time = 0.5
    
    @staticmethod
    def acknowledge_order():
        acknowlegeSignal = master_acknowledgSignal()
        acknowlegeSignal.master_acknowledgeSignal = True
        Publishers.globalNavigator_Acknowledge_Publisher.publish(acknowlegeSignal)

    @staticmethod
    def target_order(navigation_target):
        Publishers.Navigator_Target_Publisher.publish(navigation_target)

    @staticmethod
    def stop_order():
        stopSignal = lidar_stopSignal()
        stopSignal.stopSignalState = True
        Publishers.Navigator_Stop_Publisher.publish(stopSignal)
        
    @staticmethod
    def check_current_state():
        return rospy.get_param('nav_currentState')
        
################################### LIDAR FUNCTIONS CLASS #######################
        
class Lidar:
    @staticmethod
    def obstacle_detected():
        return rospy.get_param('obstacle')
        
    
        
############################# STATE CLASSES START HERE ##################################

class Idle(smach.State):    
     
    def __init__(self):
        smach.State.__init__(self, outcomes=['Go to: Idle',
                                             'Go to: WaitForSignal'])

    def execute(self, userdata):
        global MASTER_CurrentNavigatorState_en
        global MASTER_SMachineCurrentState_en
        
        Navigation.acknowledge_order()        
        rospy.sleep(Navigation.communication_wait_time)
        
        if ( Navigation.check_current_state() == 1 ):  
            MASTER_CurrentNavigatorState_en = MASTER_NavigatorStates_ten.MASTER_NavigatorReady_en 
            MASTER_SMachineCurrentState_en = MASTER_SMachineStates_ten.MASTER_SMachine_WaitForSignal_en
                        
            return 'Go to: WaitForSignal'
        
        else:
            return 'Go to: Idle'
        
class WaitForSignal(smach.State):
  
    def __init__(self):
        smach.State.__init__(self, outcomes=['Go to: MoveOn', 'Go to: WaitForSignal'],
                             )

    def execute(self, userdata):
        global MASTER_SMachineCurrentState_en
        global MASTER_CurrentNavigatorState_en
        
        jack_state = rospy.get_param('jack')
        
        if ( ( jack_state == True ) and ( MASTER_CurrentNavigatorState_en == MASTER_NavigatorStates_ten.MASTER_NavigatorReady_en  ) ):
            MASTER_SMachineCurrentState_en = MASTER_SMachineStates_ten.MASTER_SMachine_MoveOn_en
            
            return 'Go to: MoveOn'
          
        else:
            return 'Go to: WaitForSignal'

'''
* BRIEF * This state IS RESPONSIBLE FOR SENDING THE TARGET INFORMATION TO THE NAVIGATION ALGORITHM
'''
class MoveOn(smach.State):
    
    def __init__(self):
        smach.State.__init__(self,
                             outcomes=['Go to: WaitToReach', 'Go to: MoveOn'])

    def execute(self, userdata):
        global MASTER_SMachineCurrentState_en
        global MASTER_CurrentNavigatorState_en
        
        Navigation.target_order( navigation_targets[current_target] ) 
        rospy.sleep(Navigation.communication_wait_time)
        
        # Update navigation state
        if( Navigation.check_current_state() == 2 ):
            MASTER_CurrentNavigatorState_en = MASTER_NavigatorStates_ten.MASTER_NavigatorBusy_en
            MASTER_SMachineCurrentState_en = MASTER_SMachineStates_ten.MASTER_SMachine_WaitToReach_en
            
            return 'Go to: WaitToReach'
        
        else:
            return 'Go to: MoveOn'
        
class WaitToReach(smach.State):  # starts moving here

    def __init__(self):
        smach.State.__init__(self, outcomes=['Go to: SuddenStop', 'Go to: DestinationReached', 'Go to: WaitToReach'],
                             )

    def execute(self, userdata):
        global MASTER_SMachineCurrentState_en
        global MASTER_CurrentNavigatorState_en
        
        lidar_obstacle_detected = rospy.get_param('obstacle')
        
        if lidar_obstacle_detected:
            MASTER_SMachineCurrentState_en = MASTER_SMachineStates_ten.MASTER_SMachine_SuddenStop_en
            return 'Go to: SuddenStop'
                     
        elif ( Navigation.check_current_state == 3 ):
            MASTER_CurrentNavigatorState_en = MASTER_NavigatorStates_ten.MASTER_NvigatorWaitToReceiveAcknowledge_en
            MASTER_SMachineCurrentState_en = MASTER_SMachineStates_ten.MASTER_SMachine_DestinationReached_en
            
            return 'Go to: DestinationReached'
        
        else:
            return 'Go to: WaitToReach'

class DestinationReached(smach.State):

    def __init__(self):
        smach.State.__init__(self, outcomes=['Go to: Finished', 'Go to: DestinationReached'],
                             )

    def execute(self, userdata):
        global MASTER_SMachineCurrentState_en
        global MASTER_CurrentNavigatorState_en
        global current_target
        
        Navigation.acknowledge_order()
        rospy.sleep(Navigation.communication_wait_time)
        
        if ( Navigation.check_current_state() == 1 ):
            return 'Go to: Finished'

        else:
            return 'Go to: DestinationReached'
        
class SuddenStop (smach.State):

    def __init__(self):
        smach.State.__init__(self, outcomes=['Go to: ConfirmedStop', 'Go to: SuddenStop'],
                             )

    def execute(self, userdata):
        global MASTER_SMachineCurrentState_en
        global MASTER_CurrentNavigatorState_en
        
        Navigation.stop_order()
        rospy.sleep(Navigation.communication_wait_time)
        
        # communicated with navigator under if obstacle detected in wait to reach and waits for callback (conf stop)
        if ( Navigation.check_current_state() == 7):
            MASTER_CurrentNavigatorState_en == MASTER_NavigatorStates_ten.MASTER_NavigatorConfirmedStop_en
            MASTER_SMachineCurrentState_en = MASTER_SMachineStates_ten.MASTER_SMachine_ConfirmedStop_en
            
            return 'Go to: ConfirmedStop'

        else:
            return 'Go to: SuddenStop'

class ConfirmedStop (smach.State):
    def __init__(self):
        smach.State.__init__(self, outcomes=['Go to: MoveOn', 'Go to: ConfirmedStop'],
                             )

    def execute(self, userdata):
        global MASTER_CurrentMachineState_en
        global MASTER_CurrentNavigatorState_en

        lidar_obstacle_detected = rospy.get_param('obstacle')
        
        if not (lidar_obstacle_detected):
            
            Navigation.acknowledge_order()
            rospy.sleep(Navigation.communication_wait_time)
            
            if( Navigation.check_current_state() == 1 ):
                MASTER_CurrentNavigatorState_en = MASTER_NavigatorStates_ten.MASTER_NavigatorReady_en
                MASTER_CurrentMachineState_en = MASTER_SMachineStates_ten.MASTER_SMachine_MoveOn_en
                return 'Go to: MoveOn'

        else:  
            return 'Go to: ConfirmedStop'
        
class Finished(smach.State):

    def __init__(self):
        smach.State.__init__(self, outcomes=['Go to: Finished'],
                             )

    def execute(self, userdata):
        return 'Go to: Finished'
        

###################################### GENERAL FUNCTIONS START HERE #################
################################     CALLBACK FUNCTIONS      ########################


################################## NAVIGATION FUNCTIONS ###########################

######################################## LIDAR FUNCTIONS ############################


######################################### MECHANISMS FUNCTIONS START HERE ###########

    
######################################### screen configurations #####################
    

############################################### MAIN STARTS HERE ####################

def main():

    # initialize global variables
    global RisingEdge_variable
    RisingEdge_variable = 0

    # CURRENT STATES

    # NODE INITIALIZATION : 
    rospy.init_node('hafnaoui', anonymous=True)

    ############  STRATEGY PUBLISHERS  ##################
    
    ############  NAVIGATION PUBLISHERS  ################

    ############      SUBSCRIBERS HERE   ################ 
    

    # Create a SMACH state machine
    sm = smach.StateMachine(outcomes=['NavigatorReached'])
    

    # Open the container
    with sm:
        # Add states to the container
        smach.StateMachine.add('Idle', Idle(),
                               transitions={'Go to: Idle': 'Idle',
                                            'Go to: WaitForSignal': 'WaitForSignal'
                                            })
        
        smach.StateMachine.add('WaitForSignal', WaitForSignal(),
                               transitions={'Go to: WaitForSignal': 'WaitForSignal',
                                            'Go to: MoveOn': 'MoveOn'
                                            })

        smach.StateMachine.add('MoveOn', MoveOn(),
                               transitions={'Go to: WaitToReach': 'WaitToReach',
                                            'Go to: MoveOn': 'MoveOn'
                                            })

        smach.StateMachine.add('WaitToReach', WaitToReach(),
                               transitions={'Go to: SuddenStop': 'SuddenStop',
                                            'Go to: DestinationReached': 'DestinationReached',
                                            'Go to: WaitToReach': 'WaitToReach'
                                            })

        smach.StateMachine.add('SuddenStop', SuddenStop(),
                               transitions={'Go to: ConfirmedStop': 'ConfirmedStop',
                                            'Go to: SuddenStop': 'SuddenStop'
                                            })

        smach.StateMachine.add('ConfirmedStop', ConfirmedStop(),
                               transitions={'Go to: ConfirmedStop': 'ConfirmedStop',
                                            'Go to: MoveOn': 'MoveOn'
                                            })
        
        smach.StateMachine.add('DestinationReached', DestinationReached(),
                               transitions={'Go to: Finished': 'Finished',
                                            'Go to: DestinationReached': 'DestinationReached',
                                            })
        smach.StateMachine.add('Finished', Finished(),
                               transitions={'Go to: Finished': 'Finished'
                                            })
        
    sis = smach_ros.IntrospectionServer('server_name', sm, '/Hafnaoui_Jr')
    sis.start()

    # Execute SMACH plan
    outcome = sm.execute()

    rospy.spin()
    sis.stop()


if __name__ == '__main__':
    main()
