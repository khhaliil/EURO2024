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

    MASTER_SMachine_Idle_en = 1
    MASTER_SMachine_Preparation_en = 2
    MASTER_SMachine_WaitForSignal_en = 3
    MASTER_SMachine_MoveOn_en = 4
    MASTER_SMachine_WaitToReach_en = 5
    MASTER_SMachine_DestinationReached_en = 6
    MASTER_SMachine_ExecuteTask_en = 7
    MASTER_SMachine_WaitToFinishTask_en = 8

    MASTER_SMachine_SuddenStop_en = 9 
    MASTER_SMachine_ConfirmedStop_en = 10

    MASTER_SMachine_ParallelMoveOn_en = 11
    MASTER_SMachine_ParallelWaitToReach_en = 12
    MASTER_SMachine_ParallelDestReached_en = 13


class MASTER_MasterStates_ten (Enum):

    MASTER_Stop_en = 1
    MASTER_Start_en = 2
    MASTER_MasterReady_en = 3
    MASTER_MasterBusy_en = 4
    MASTER_ParallelMasterReady_en = 5
    MASTER_ParallelMasterReadyToMove_en = 6
    MASTER_ParallelMasterReadyToExecute_e = 7
    MASTER_ParallelMasterBusy_en = 8
    MASTER_Preparing_en = 9

class MASTER_NavigatorStates_ten (Enum):

    MASTER_NavigatorIdle_en = 0
    MASTER_NavigatorReady_en = 1
    MASTER_NavigatorBusy_en = 2
    MASTER_NavigatorGoingToRespond_en = 3
    MASTER_NavigatorReachedDest_en = 4
    MASTER_NavigatorConfirmedStop_en = 5


    #MASTER_ParallelNavigatorReady_en = 6
    #MASTER_ParallelNavigatorBusy_en = 7
    #MASTER_ParallelNavigatorGoingToRespond_en = 8
    #MASTER_ParallelNavigatorReachedDest_en = 9

    
    #MASTER_NavigatorParallelConfirmedStop_en = 11

class MASTER_NavigatorOrders_ten (Enum):

    Navigator_SuddenStop_en = 1
    Navigator_MoveOn_en = 2

##################################### DECLARE VARIABLES HERE ####################################

# MASTER Orders and NAVIGATOR Status

MASTER_Navigator_MessageRecieved            = 0
MASTER_Navigator_Stop_Flag                  = 1
MASTER_Navigator_Indicator_WaitForOrders    = 2
MASTER_Navigator_Can_GO                     = 3
MASTER_Navigator_Still_IDLE                 = 4
MASTER_Navigator_No_Rotate_After            = 1000 
MASTER_PermissionTo_Navigator = MASTER_Navigator_Can_GO

#global MASTER_CurrentMachineState_en
#global MASTER_CurrentMasterState_en
#global MASTER_CurrentNavigatorState_en

global CurrentTask_Blue_en
global CurrentTask_Green_en

global nav_currentX
global nav_currentY
global nav_currentAngle
global nav_currentState

MASTER_CurrentMachineState_en = MASTER_SMachineStates_ten.MASTER_SMachine_Idle_en
MASTER_CurrentMasterState_en = MASTER_MasterStates_ten.MASTER_Start_en #put back to stop
MASTER_CurrentNavigatorState_en = MASTER_NavigatorStates_ten.MASTER_NavigatorGoingToRespond_en

############################# STATE CLASSES START HERE ##################################


'''
* Brief * : This class will be responsible of establishing communication for the first time with Navigation Node
* OUTPUT * : The state will be looping on itself until navigator sends back the trash value and then goes to state preparation

Navigator state is a T = 0 Idle, establishing communication, it will go to GOING TO RESPOND ==> READY and finally got back to Idle so we can use Idle state in robot status callback AGAIN !  
'''
class Idle(smach.State):     
    def __init__(self):
        smach.State.__init__(self, outcomes=['Go to: Idle', 'Go to: Preparation']
                             )

    def execute(self, userdata):
        global MASTER_CurrentNavigatorState_en
        talker_acknowledge()
        rospy.sleep(0.5)
        nav_currentState = rospy.get_param('nav_currentState')
        if (nav_currentState == 1):  
            MASTER_CurrentNavigatorState_en = MASTER_NavigatorStates_ten.MASTER_NavigatorReady_en 
            MASTER_CurrentMachineState_en = MASTER_SMachineStates_ten.MASTER_SMachine_WaitForSignal_en
            time.sleep(2)
            
            return 'Go to: Preparation'
        
        else:
            return 'Go to: Idle'
        #elif (MASTER_CurrentNavigatorState_en == MASTER_NavigatorStates_ten.MASTER_NavigatorGoingToRespond_en):
        #   return 'Go to: Idle'

'''
* BRIEF * This state will be responsible of ROBOTS PREPARATION SUCH AS POSITIONNING and Getting configurations
'''
class Preparation(smach.State):  # TODO: needs lcd code + MECHANISMS INITIALIZATION FUNCTION    
    def __init__(self):
        smach.State.__init__(self, outcomes=['Go to: Preparation',
                                             'Go to: WaitForSignal'])

    def execute(self, userdata):
        global MASTER_CurrentNavigatorState_en
        #MASTER_CurrentNavigatorState_en=MASTER_NavigatorStates_ten.MASTER_NavigatorReady_en
        if (MASTER_CurrentNavigatorState_en == MASTER_NavigatorStates_ten.MASTER_NavigatorReady_en) :
            MASTER_CurrentMachineState_en = MASTER_SMachineStates_ten.MASTER_SMachine_WaitForSignal_en
            time.sleep(2)
            return  'Go to: WaitForSignal'

        # get color, plate where the robot is placed, strategy, and localization data (disposition du robot pour l'auto-calibration)
        # confirm communication with stm, lora and camera
        # launch localisation process
        else:
            return 'Go to: Preparation'

'''
* BRIEF * IN THIS STATE ROBOT IS WAITING FOR THE STAT SIGNAL (JACK)
'''
class WaitForSignal(smach.State):
  
    def __init__(self):
        smach.State.__init__(self, outcomes=['Go to: MoveOn', 'Go to: WaitForSignal'],
                             )

    def execute(self, userdata):
        global MASTER_CurrentMachineState_en
        global MASTER_CurrentMasterState_en
        global MASTER_CurrentNavigatorState_en
        global jack
        jack = rospy.get_param('jack')
        rospy.sleep(0.5)
        if (MASTER_CurrentMasterState_en == MASTER_MasterStates_ten.MASTER_Start_en)and(jack==True):
            MASTER_CurrentMachineState_en = MASTER_SMachineStates_ten.MASTER_SMachine_MoveOn_en
            MASTER_CurrentMasterState_en = MASTER_MasterStates_ten.MASTER_MasterReady_en
            MASTER_CurrentNavigatorState_en = MASTER_NavigatorStates_ten.MASTER_NavigatorReady_en
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
        global MASTER_CurrentMachineState_en
        global MASTER_CurrentMasterState_en
        global MASTER_CurrentNavigatorState_en
        nav_currentState = rospy.get_param("nav_currentState")
        send_target()
        rospy.sleep(0.5)
        
        # Update navigation state
        if(nav_currentState == 2):
            MASTER_CurrentNavigatorState_en = MASTER_NavigatorStates_ten.MASTER_NavigatorBusy_en
            MASTER_CurrentMachineState_en = MASTER_SMachineStates_ten.MASTER_SMachine_WaitToReach_en
            rospy.sleep(2)
            return 'Go to: WaitToReach'
        
        if (MASTER_CurrentNavigatorState_en == MASTER_NavigatorStates_ten.MASTER_NavigatorReady_en):
            return 'Go to: MoveOn'



        
'''
* BRIEF * THIS STATE EXECUTES WHILE THE ROBOT IS NAVIGATING TO ITS TARGET
'''      
class WaitToReach(smach.State):  # starts moving here

    
    def __init__(self):
        smach.State.__init__(self, outcomes=['Go to: SuddenStop', 'Go to: DestinationReached', 'Go to: WaitToReach'],
                             )

    def execute(self, userdata):
        global MASTER_CurrentMachineState_en
        global MASTER_CurrentMasterState_en
        global MASTER_CurrentNavigatorState_en
        global lidar_obstacle_detected
 
        lidar_obstacle_detected = rospy.get_param('obstacle')
        nav_currentState = rospy.get_param("nav_currentState")

        if lidar_obstacle_detected:
            MASTER_CurrentMachineState_en = MASTER_SMachineStates_ten.MASTER_SMachine_SuddenStop_en
            return 'Go to: SuddenStop'             
        elif ( nav_currentState == 3 ):
            MASTER_CurrentNavigatorState_en == MASTER_NavigatorStates_ten.MASTER_NavigatorReachedDest_en
            talker_acknowledge()
            # if there are no obstacles, once the master receives smothing from the nav it switches to dest reached
            MASTER_CurrentMachineState_en = MASTER_SMachineStates_ten.MASTER_SMachine_DestinationReached_en
            return 'Go to: DestinationReached'
        else:
            return 'Go to: WaitToReach'
'''
* BRIEF * TIS STATE MARKS REACHING THE TARGET
'''  
class DestinationReached(smach.State):


    def __init__(self):
        smach.State.__init__(self, outcomes=['Go to: ExecuteTask', 'Go to: MoveOn', 'Go to: Parallel_MoveOn' ],
                             )

    def execute(self, userdata):
        global MASTER_CurrentMachineState_en
        global MASTER_CurrentMasterState_en
        global MASTER_CurrentNavigatorState_en
        
        rospy.loginfo("DestinationReached")
        rospy.sleep(100)
        
        if (MASTER_CurrentMachineState_en == MASTER_SMachineStates_ten.MASTER_SMachine_DestinationReached_en):  # TRUE
            # DEPENDING ON WHETHER YOU HAVE A TASK TO EXECUTE OR NOT AFTER REACHING THE CURRENT TARGET
            # CHANGE MASTER_CurrentTargets WITH THE VARIABLE NAME THAT HAS THAT INFORMATION
            if (MASTER_CurrentTargets[3] == MASTER_WILL_Execute_Task):
                MASTER_CurrentMachineState_en = MASTER_SMachineStates_ten.MASTER_SMachine_ExecuteTask_en
                MASTER_CurrentMasterState_en = MASTER_MasterStates_ten.MASTER_MasterReady_en
                MASTER_CurrentNavigatorState_en = MASTER_NavigatorStates_ten.MASTER_NavigatorReady_en
                return 'Go to: ExecuteTask'

            else:
                MASTER_CurrentMachineState_en = MASTER_SMachineStates_ten.MASTER_SMachine_MoveOn_en
                MASTER_CurrentNavigatorState_en = MASTER_NavigatorStates_ten.MASTER_NavigatorReady_en
                return 'Go to: MoveOn'

# THIS STATE DOES NOT EXECUTE ANY FUNCTIONS: ITS TRANSITIONAL
class ExecuteTask(smach.State):

    global MASTER_CurrentMachineState_en
    global MASTER_CurrentMasterState_en
    global MASTER_CurrentNavigatorState_en

    def __init__(self):
        smach.State.__init__(self, outcomes=['Go to: waitToFinishTask'])

    def execute(self, userdata):

        if (MASTER_CurrentMasterState_en == MASTER_MasterStates_ten.MASTER_MasterReady_en):  #ALWAYS TRUE
            MASTER_CurrentMachineState_en = MASTER_SMachineStates_ten.MASTER_SMachine_WaitToFinishTask_en
            MASTER_CurrentMasterState_en = MASTER_MasterStates_ten.MASTER_MasterBusy_en
        return 'Go to: waitToFinishTask'

'''
* BRIEF * THIS STATE RUNS WHILE THE ROBOT S MECHANISMS ARE EXCUTING THIER CURRENT TASK
'''  
class waitToFinishTask(smach.State):

    def __init__(self):
        smach.State.__init__(self, outcomes=['Go to: waitToFinishTask', 'Go to: MoveOn',
                                             'Go to: Parallel_MoveOn'])

    def execute(self, userdata):
        # FUNCTIONS EXECUTION HERE
        if (MASTER_CurrentMasterState_en == MASTER_MasterStates_ten.MASTER_MasterReady_en ):
            MASTER_CurrentMachineState_en = MASTER_SMachineStates_ten.MASTER_SMachine_MoveOn_en
            MASTER_CurrentNavigatorState_en = MASTER_NavigatorStates_ten.MASTER_NavigatorReady_en
            return 'Go to: MoveOn'
        elif (MASTER_CurrentMasterState_en == MASTER_MasterStates_ten.MASTER_ParallelMasterReady_en):
            MASTER_CurrentMachineState_en = MASTER_SMachineStates_ten.MASTER_SMachine_ParallelMoveOn_en            
            MASTER_CurrentNavigatorState_en = MASTER_NavigatorStates_ten.MASTER_ParallelNavigatorBusy_en
            return 'Go to: Parallel_MoveOn'
        else:
            return 'Go to: waitToFinishTask'

class Parallel_MoveOn (smach.State):
    def __init__(self):
        smach.State.__init__(self, outcomes=['Go to: Parallel_MoveOn', 'Go to: Parallel_WaitToReach'],
                             )

    def execute(self, userdata):
        
        if (MASTER_CurrentNavigatorState_en == MASTER_NavigatorStates_ten.MASTER_ParallelNavigatorBusy_en):
            MASTER_CurrentMachineState_en = MASTER_SMachineStates_ten.MASTER_SMachine__ParallelWaitToReach_en
            MASTER_First_Time_Publishing_Targets = 1
            return 'Go to: Parallel_WaitToReach'
        else:
            return 'Go to: Parallel_MoveOn'


class Parallel_WaitToReach (smach.State):  #involves task execution
    def __init__(self):
        smach.State.__init__(self, outcomes=['Go to: Parallel_WaitToReach',
                                              'Go to: Parallel_DestinationReached',
                                              'Go to: Parallel_SuddenStop']
                             )

    def execute(self, userdata):
        global MASTER_CurrentMachineState_en
        global MASTER_CurrentMasterState_en
        global MASTER_CurrentNavigatorState_en
        global MASTER_SUDDEN_STOP_REDUCE_RANGE_TIMER_sec
        global MASTER_SUDDEN_STOP_REDUCED_ACTIVATED_bool


        if Lidar_ObstacleDetected_b:
            MASTER_CurrentMachineState_en = MASTER_SMachineStates_ten.MASTER_SMachine_ParallelSuddenStop_en
            return 'Go to: Parallel_SuddenStop'
        
        elif MASTER_CurrentMachineState_en == MASTER_SMachineStates_ten.MASTER_SMachine_SuddenStop_en :
            return 'Go to: Parallel_SuddenStop' 

        if (MASTER_CurrentMasterState_en == MASTER_MasterStates_ten.MASTER_ParallelMasterBusy_en):
            # EXECUTE FUNCTIONS HERE
            pass
        elif MASTER_CurrentNavigatorState_en == MASTER_NavigatorStates_ten.MASTER_ParallelNavigatorReachedDest_en:
            # if there are no obstacles, once the master receives sthing from the nav it switches to dest reached
            MASTER_CurrentMachineState_en = MASTER_SMachineStates_ten.MASTER_SMachine_ParallelDestReached_en
            sleep(0.5)
            return 'Go to: Parallel_DestinationReached'
        else:
            #print(MASTER_CurrentNavigatorState_en.value)
            sleep(1)
            return 'Go to: Parallel_WaitToReach'

class Parallel_DestinationReached(smach.State):
    global nav_currentX
    global nav_currentY
    global nav_currentAngle
    global nav_currentState
    global MASTER_CurrentMachineState_en
    global MASTER_CurrentMasterState_en
    global MASTER_CurrentNavigatorState_en

    def __init__(self):
        smach.State.__init__(self, outcomes=['Go to: ExecuteTask', 'Go to: Parallel_DestinationReached','Go to: MoveOn'],
                             )

    def execute(self, userdata):
        
        if ( MASTER_CurrentMasterState_en == MASTER_MasterStates_ten.MASTER_ParallelMasterBusy_en ) :
            # DEPENDING ON WHETHER YOU HAVE A TASK TO EXECUTE OR NOT AFTER REACHING THE CURRENT TARGET
            # CHANGE MASTER_CurrentTargets WITH THE VARIABLE NAME THAT HAS THAT INFORMATION
            if  (MASTER_CurrentTargets [3] == MASTER_WONT_Execute_Task) :
                MASTER_CurrentMachineState_en = MASTER_SMachineStates_ten.MASTER_SMachine_ParallelMoveOn_en
                MASTER_CurrentNavigatorState_en = MASTER_NavigatorStates_ten.MASTER_ParallelNavigatorReady_en
                return 'Go to: Parallel_MoveOn'
            else : 
                # CONTINUE TO EXECUTE FUNCTIONS HERE IF NOT DONE
                return 'Go to: Parallel_DestinationReached'

        elif (MASTER_CurrentNavigatorState_en == MASTER_NavigatorStates_ten.MASTER_ParallelNavigatorReachedDest_en ):
            MASTER_CurrentNavigatorState_en = MASTER_NavigatorStates_ten.MASTER_ParallelNavigatorReady_en
            return 'Go to: Parallel_DestinationReached'
        
        elif (MASTER_CurrentNavigatorState_en == MASTER_NavigatorStates_ten.MASTER_ParallelNavigatorReady_en) :   
            if  (MASTER_CurrentTargets [3] == MASTER_WONT_Execute_Task) :
                MASTER_CurrentMachineState_en = MASTER_SMachineStates_ten.MASTER_SMachine_MoveOn_en
                return 'Go to: MoveOn'
        
            if   (MASTER_CurrentTargets [3] == MASTER_WILL_Execute_Task ) :
                MASTER_CurrentMachineState_en = MASTER_SMachineStates_ten.MASTER_SMachine_ExecuteTask_en
                return 'Go to: ExecuteTask'


class SuddenStop (smach.State):
    global nav_currentX
    global nav_currentY
    global nav_currentAngle
    global nav_currentState
    global MASTER_CurrentMachineState_en
    global MASTER_CurrentMasterState_en
    global MASTER_CurrentNavigatorState_en

    def __init__(self):
        smach.State.__init__(self, outcomes=['Go to: confirmed stop', 'Go to: sudden stop'],
                             )

    def execute(self, userdata):
        talker_stop()
        rospy.sleep(0.5)
        nav_currentState = rospy.get_param("nav_currentState")
        # communicated with navigator under if obstacle detected in wait to reach and waits for callback (conf stop)
        if (nav_currentState == 5):
            MASTER_CurrentNavigatorState_en == MASTER_NavigatorStates_ten.MASTER_NavigatorConfirmedStop_en
            MASTER_CurrentMachineState_en = MASTER_SMachineStates_ten.MASTER_SMachine_ConfirmedStop_en
            return 'Go to: confirmed stop'

        else:
            return 'Go to: sudden stop'

class ConfirmedStop (smach.State):
    def __init__(self):
        smach.State.__init__(self, outcomes=['Go to: MoveOn', 'Go to: ConfirmedStop'],
                             )

    def execute(self, userdata):
        global MASTER_CurrentMachineState_en
        global MASTER_CurrentMasterState_en
        global MASTER_CurrentNavigatorState_en

        if not (lidar_obstacle_detected):
            talker_acknowledge()
            rospy.sleep(0.5)
            nav_currentState = rospy.get_param("nav_currentState")
            if(nav_currentState == 1):
                MASTER_CurrentNavigatorState_en = MASTER_NavigatorStates_ten.MASTER_NavigatorReady_en
                MASTER_CurrentMachineState_en = MASTER_SMachineStates_ten.MASTER_SMachine_MoveOn_en
                return 'Go to: MoveOn'

        else:  
            return 'Go to: ConfirmedStop'

class Parallel_SuddenStop (smach.State):
    global MASTER_CurrentMachineState_en
    global MASTER_CurrentMasterState_en
    global MASTER_CurrentNavigatorState_en

    def __init__(self):
        smach.State.__init__(self, outcomes=['Go to: Parallel_ConfirmedStop', 'Go to: Parallel_SuddenStop'],
                             )

    def execute(self, userdata):


        # communicated with navigator under if obstacle detected in wait to reach and waits for callback (conf stop)
        if (MASTER_CurrentNavigatorState_en == MASTER_NavigatorStates_ten.MASTER_NavigatorParallelConfirmedStop_en):
            MASTER_CurrentMachineState_en = MASTER_SMachineStates_ten.MASTER_SMachine_ConfirmedStop_en
            return 'Go to: Parallel_ConfirmedStop'

        else:
            return 'Go to: Parallel_SuddenStop'

class Parallel_ConfirmedStop (smach.State):

    def __init__(self):
        smach.State.__init__(self, outcomes=['Go to: Parallel_MoveOn', 'Go to: Parallel_ConfirmedStop'],
                             )

    def execute(self, userdata):
        global MASTER_CurrentMachineState_en
        global MASTER_CurrentMasterState_en
        global MASTER_CurrentNavigatorState_en

        if not (Lidar_ObstacleDetected_b):
            MASTER_CurrentNavigatorState_en = MASTER_NavigatorStates_ten.MASTER_ParallelNavigatorReady_en
            MASTER_CurrentMachineState_en = MASTER_SMachineStates_ten.MASTER_SMachine_ParallelMoveOn_en
            return 'Go to: Parallel_MoveOn'

        if (MASTER_CurrentMasterState_en == MASTER_MasterStates_ten.MASTER_ParallelMasterBusy_en):
            # CONTINUE TO EXECUTE TASKS HERE WHILE THE OBSTACLE IS STILL THERE
            return 'Go to: Parallel_ConfirmedStop'
        else:
            return 'Go to: Parallel_ConfirmedStop'

###################################### GENERAL FUNCTIONS START HERE #################
################################     CALLBACK FUNCTIONS      ########################


  ################################## NAVIGATION FUNCTIONS ###########################
    

######################################## LIDAR FUNCTIONS ############################


######################################### MECHANISMS FUNCTIONS START HERE ###########

    
######################################### screen configurations #####################
    

############################################### MAIN STARTS HERE ####################
def talker_acknowledge():
    pub = rospy.Publisher('/ros_can_interface/master_acknowledge',master_acknowledgSignal, queue_size=10)

    rate = rospy.Rate(10) # 10hz
    
    msg=master_acknowledgSignal()
    msg.master_acknowledgeSignal=True
    pub.publish(msg)
    
def send_target():
    pub = rospy.Publisher('/ros_can_interface/navigation_data', master_navigationMessage, queue_size=10)
    msg=master_navigationMessage()
    msg.nav_targetX=200.00
    msg.nav_targetY=200.00
    msg.nav_targetAngle=90.00
    msg.nav_isForward=True
    pub.publish(msg)
    
def talker_stop():
    pub = rospy.Publisher('/ros_can_interface/stopSignal', lidar_stopSignal, queue_size=10)
    rate = rospy.Rate(10) # 10hz
    msg=lidar_stopSignal()
    msg.stopSignalState=True
    pub.publish(msg)

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
                                            'Go to: Preparation': 'Preparation'})

        smach.StateMachine.add('Preparation', Preparation(),
                               transitions={'Go to: Preparation': 'Preparation',
                                            'Go to: WaitForSignal': 'WaitForSignal'})

        smach.StateMachine.add('WaitForSignal', WaitForSignal(),
                               transitions={'Go to: MoveOn': 'MoveOn',
                                            'Go to: WaitForSignal': 'WaitForSignal'})

        smach.StateMachine.add('MoveOn', MoveOn(),
                               transitions={'Go to: WaitToReach': 'WaitToReach',
                                            'Go to: MoveOn': 'MoveOn'})

        smach.StateMachine.add('WaitToReach', WaitToReach(),
                               transitions={'Go to: SuddenStop': 'SuddenStop',
                                            'Go to: DestinationReached': 'DestinationReached',
                                            'Go to: WaitToReach': 'WaitToReach'})

        smach.StateMachine.add('SuddenStop', SuddenStop(),
                               transitions={'Go to: confirmed stop': 'ConfirmedStop',
                                            'Go to: sudden stop': 'SuddenStop'})

        smach.StateMachine.add('ConfirmedStop', ConfirmedStop(),
                               transitions={'Go to: ConfirmedStop': 'ConfirmedStop',
                                            'Go to: MoveOn': 'MoveOn'})
        smach.StateMachine.add('DestinationReached', DestinationReached(),
                               transitions={'Go to: MoveOn': 'MoveOn',
                                            'Go to: ExecuteTask': 'ExecuteTask',
                                            'Go to: Parallel_MoveOn':'Parallel_MoveOn'})
        smach.StateMachine.add('ExecuteTask', ExecuteTask(),
                               transitions={'Go to: waitToFinishTask': 'waitToFinishTask',
                                            })
        smach.StateMachine.add('waitToFinishTask', waitToFinishTask(),
                               transitions={'Go to: waitToFinishTask': 'waitToFinishTask' ,
                                'Go to: MoveOn' : 'MoveOn',
                                'Go to: Parallel_MoveOn':'Parallel_MoveOn'})
        smach.StateMachine.add('Parallel_MoveOn', Parallel_MoveOn(),
                               transitions={'Go to: Parallel_MoveOn': 'Parallel_MoveOn',
                                            'Go to: Parallel_WaitToReach':'Parallel_WaitToReach'
                                            })
        smach.StateMachine.add('Parallel_WaitToReach', Parallel_WaitToReach(),
                               transitions={'Go to: Parallel_WaitToReach': 'Parallel_WaitToReach',
                                              'Go to: Parallel_DestinationReached' : 'Parallel_DestinationReached',
                                              'Go to: Parallel_SuddenStop': 'Parallel_SuddenStop'
                                            })

        smach.StateMachine.add('Parallel_DestinationReached', Parallel_DestinationReached(),
                               transitions={'Go to: ExecuteTask' : 'ExecuteTask',
                                'Go to: Parallel_DestinationReached' : 'Parallel_DestinationReached',
                                'Go to: MoveOn' : 'MoveOn'
                                            })

        smach.StateMachine.add('Parallel_SuddenStop', Parallel_SuddenStop(),
                               transitions={'Go to: Parallel_ConfirmedStop': 'Parallel_ConfirmedStop',
                                'Go to: Parallel_SuddenStop': 'Parallel_SuddenStop'})

        smach.StateMachine.add('Parallel_ConfirmedStop', Parallel_ConfirmedStop(),
                               transitions={'Go to: Parallel_MoveOn': 'Parallel_MoveOn',
                                'Go to: Parallel_ConfirmedStop': 'Parallel_ConfirmedStop'})

    sis = smach_ros.IntrospectionServer('server_name', sm, '/Hafnaoui_Jr')
    sis.start()

    # Execute SMACH plan
    outcome = sm.execute()

    rospy.spin()
    sis.stop()


if __name__ == '__main__':
    
    main()
