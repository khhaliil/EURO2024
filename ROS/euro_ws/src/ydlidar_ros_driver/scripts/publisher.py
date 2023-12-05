#!/usr/bin/env python3
import rospy
from std_msgs.msg import Float64
import datetime as dt
import matplotlib.pyplot as plt
import matplotlib.animation as animation


fig = plt.figure()
ax = fig.add_subplot(1, 1, 1)
xs = []
ys = []

def callback(data):
    rospy.loginfo(data)
    
    global xs 
    global ys


def animate (data, xs, ys):

    rospy.loginfo(data)
    
    xs.plot(dt.datetime.now().strftime('%H:%M:%S.%f'))
    ys.plot(data)

    xs = xs[-20:] 
    ys = ys[-20:]

    ax.clear()
    ax.plot(xs, ys)

    plt.xticks(rotation=45, ha='right')
    plt.subplots_adjust(bottom=0.30)
    plt.title('Lidar Angle')
    plt.ylabel('Angle in deg')

     
def listener():
        # In ROS, nodes are uniquely named. If two nodes with the same
       # name are launched, the previous one is kicked off. The
      # anonymous=True flag means that rospy will choose a unique
      # name for our 'listener' node so that multiple listeners can
      # run simultaneously.
    rospy.init_node('listener', anonymous=True)
  
    rospy.Subscriber("ObstaclePos", Float64, callback)
  
       # spin() simply keeps python from exiting until this node is stopped
    rospy.spin()

ani = animation.FuncAnimation(fig, animate, fargs=(xs, ys), interval=1000)
plt.show()
   
if __name__ == '__main__':
    listener()
