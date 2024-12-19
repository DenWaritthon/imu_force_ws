#!/usr/bin/python3

import rclpy
from rclpy.node import Node
from rclpy.qos import QoSProfile ,ReliabilityPolicy
from sensor_msgs.msg import Imu

import os
import numpy as np



class AccelerationFiltererNode(Node):
    def __init__(self):
        super().__init__('acceleration_filterer_node')

        # publisher 
        self.accleration_pub = self.create_publisher(Imu, '/acceleration', 10)
        
        # Subscription
        qos_profile = QoSProfile(reliability = ReliabilityPolicy.BEST_EFFORT,depth = 10)
        self.create_subscription(Imu,'mpu6050_publisher', self.imu_callback, qos_profile)

        # Variables
        self.a = 0.1

        self.acc_x = 0.0 
        self.acc_y = 0.0 
        self.acc_z = 0.0 
        
        self.iir_acc_x = 0.0 
        self.iir_acc_y = 0.0 
        self.iir_acc_z = 0.0

        self.get_logger().info(f'Node Acceleration Filterer Start!!!') 

    def pub_accleration(self, a_x, a_y):
        msg = Imu()
        msg.linear_acceleration.x = a_x
        msg.linear_acceleration.y = a_y

        self.accleration_pub.publish(msg)

    def imu_callback(self, msg :Imu):
        self.acc_x = msg.linear_acceleration.x
        self.acc_y = msg.linear_acceleration.y
        self.acc_z = msg.linear_acceleration.z

        self.iir_acc_x = (self.a * self.acc_x) + ((1 - self.a)*self.iir_acc_x) 
        self.iir_acc_y = (self.a * self.acc_y) + ((1 - self.a)*self.iir_acc_y) 
        self.iir_acc_z = (self.a * self.acc_z) + ((1 - self.a)*self.iir_acc_z)

        self.pub_accleration(self.iir_acc_x,self.iir_acc_y) 
        

def main(args=None):
    rclpy.init(args=args)
    node = AccelerationFiltererNode()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__=='__main__':
    main()
