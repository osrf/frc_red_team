#!/usr/bin/env python
import roslib; roslib.load_manifest('frcred_gazebo')
import rospy
import tf.transformations

from geometry_msgs.msg import Pose
from geometry_msgs.msg import Quaternion

import sys, select, termios, tty

msg = """
Reading from the keyboard  and Publishing to Pose!
---------------------------
i: increase Z translate
k: decrease Z translate
j: pan left
l: pan right
u: tilt down
p: tilt up

q/z : increase/decrease max speeds by 10%
w/x : increase/decrease only linear speed by 10%
e/c : increase/decrease only angular speed by 10%

CTRL-C to quit
"""

# for pan/tilt/z case, 

moveBindings = {
    'i':(0,0,1,0,0,0),
    'k':(0,0,-1,0,0,0),
    'j':(0,0,0,0,0,-1),
    'l':(0,0,0,0,0,1),
    'u':(0,0,0,-1,0,0),
    'p':(0,0,0,1,0,0),
         }

speedBindings={
    'q':(1.1,1.1),
    'z':(.9,.9),
    'w':(1.1,1),
    'x':(.9,1),
    'e':(1,1.1),
    'c':(1,.9),
        }

def getKey():
  tty.setraw(sys.stdin.fileno())
  select.select([sys.stdin], [], [], 0)
  key = sys.stdin.read(1)
  termios.tcsetattr(sys.stdin, termios.TCSADRAIN, settings)
  return key

speed = .01
turn = 1

def vels(speed,turn):
    return "currently:\tspeed %s\tturn %s " % (speed,turn)

if __name__=="__main__":
    settings = termios.tcgetattr(sys.stdin)
    pose = Pose()
    rospy.init_node('teleop_pose_keyboard')
    pub = rospy.Publisher('/camera_pan_tilt/cmd_vel', Pose, queue_size = 1)

    x = 0
    y = 0
    z = 0
    pan = 0
    tilt = 0
    status = 0

    try:
      print msg
      print vels(speed,turn)
      while(1):
        key = getKey()
        if key in moveBindings.keys():
          x = moveBindings[key][0]
          y = moveBindings[key][1]
          z = moveBindings[key][2]
          tilt = moveBindings[key][3]
          pan = moveBindings[key][5]
        elif key in speedBindings.keys():
          speed = speed * speedBindings[key][0]
          turn = turn * speedBindings[key][1]

          print vels(speed,turn)
          if (status == 14):
            print msg
          status = (status + 1) % 15
        else:
          x = 0
          y = 0
          z = 0
          pan = 0
          tilt = 0
          if (key == '\x03'):
            break

        pose.position.x += x*speed
        pose.position.y += y*speed
        pose.position.z += z*speed;

        # Convert the euler angles
        # TODO tf.transformations ordering vs geometry ordering
        q = (pose.orientation.x, pose.orientation.y, pose.orientation.z, pose.orientation.w)
        cur_euler = tf.transformations.euler_from_quaternion(q)
        cur_euler = (cur_euler[0]+pan*turn, cur_euler[1], cur_euler[2]+tilt*turn)
        q = tf.transformations.quaternion_from_euler(*cur_euler)
        pose.orientation = Quaternion(*q)
        pub.publish(pose)



    finally:
        termios.tcsetattr(sys.stdin, termios.TCSADRAIN, settings)

