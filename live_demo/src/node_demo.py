#!/usr/bin/env python
import rospy
import tf
from dynamic_reconfigure.server import Server
from live_demo.cfg import LiveDemoConfig
from std_msgs.msg import Int32
from std_msgs.msg import ColorRGBA
import math

def reconfigureCb(config, level):
    rospy.loginfo("""Reconfiugre Request: {R}, {G}, {B}""".format(**config))
    return config

def posicioCb(msg):
    br = tf.TransformBroadcaster()
    br.sendTransform((0.007, 0.0, 0.0125), tf.transformations.quaternion_from_euler
              (0, 0, math.radians(msg.data)), rospy.Time.now(), "helice_eix", "cos")    
    c = ColorRGBA()
    #wolframalpha: graph sin (2*t),sin (2*t+pi/3*2),sin (2*t+pi*2/3*2) from t=0 to t=pi
    c.r=max(255*(math.sin(math.radians(msg.data)*2.0)),0)
    c.g=max(255*(math.sin(math.radians(msg.data)*2.0+2.0/3.0*math.pi)),0)
    c.b=max(255*(math.sin(math.radians(msg.data)*2.0+4.0/3.0*math.pi)),0)
    pub.publish(c)

if __name__ == '__main__':
    rospy.init_node('node_demo')
    print "node_demo INICIAT "
    rospy.Subscriber('/posicio', Int32, posicioCb)
    pub = rospy.Publisher('/color', ColorRGBA)
    srv = Server(LiveDemoConfig, reconfigureCb)
    rospy.spin()