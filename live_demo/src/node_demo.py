#!/usr/bin/env python
# coding=utf-8

# Llibreries

# ROS core
import rospy
# Llibreries de transformades
import tf
# Dynamic Reconfigure
from dynamic_reconfigure.server import Server
from live_demo.cfg import LiveDemoConfig
# Tipus de missatges
from std_msgs.msg import Int32
from std_msgs.msg import ColorRGBA
# llibreria matemàtica
import math

# -----------------------------------------------------------------------------

# Callbacks

# Publicar la transformada del servo motor
def posicio_callback(msg):
    # la posició x,y,x és calculada del model del servomotor
    # Els frame_id també es troben al model
    # model/arduino_setup.urdf
    pub_tf.sendTransform((0.007, 0.0, 0.0125), tf.transformations.quaternion_from_euler
              (0, 0, math.radians(msg.data)), rospy.Time.now(), "helice_eix", "cos")    

# Actualitzar configuració i publicar el nou color
def reconfigure_callback(config, level):
    # La configuració és un arxiu que cal compilar
    # cfg/LiveDemo.cfg
    rospy.logwarn("""Reconfiugre Request: {R}, {G}, {B}""".format(**config))
    pub_color.publish(ColorRGBA(config.R, config.G, config.B,0))
    return config

# Apagar el LED al sortir
def shutdown_callback():
    pub_color.publish(ColorRGBA())
    rospy.logwarn("node_demo TANCAT")

# -----------------------------------------------------------------------------
    
# Node

if __name__ == '__main__':

    # Inici del node
    rospy.init_node('node_demo')
    rospy.logwarn("node_demo INICIAT")

    # Definició de publishers i subscribers
    pub_tf = tf.TransformBroadcaster()
    pub_color = rospy.Publisher('/color', ColorRGBA)
    rospy.Subscriber('/posicio', Int32, posicio_callback)

    # Definició del servidor dynamic reconfigure
    srv = Server(LiveDemoConfig, reconfigure_callback)

    # Definició de la funció que cal fer quan es tanqui el node
    rospy.on_shutdown(shutdown_callback)

    # Iterador del node (while(!shutdown))
    rospy.spin()