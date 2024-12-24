#!/usr/bin/python3

import rclpy
from rclpy.node import Node
from nav_msgs.msg import Odometry
import math

class ModelPosition(Node):
    def __init__(self):
        super().__init__('model_position_node')

        # Subscription
        self.subscription = self.create_subscription(Odometry, '/odom', self.odom_callback, 10)

        self.get_logger().info('Node Model Position Start!!!')

    def odom_callback(self, msg:Odometry):
        x = round(msg.pose.pose.position.x * 100, 2)
        y = round(msg.pose.pose.position.y * 100, 2)
        z = round(msg.pose.pose.position.z * 100, 2)

        self.get_logger().info(f'\nDistance x: {x} cm.\nDistance y: {y} cm.\nDistance z: {z} cm.')

def main(args=None):
    rclpy.init(args=args)
    distance_calculator = ModelPosition()
    rclpy.spin(distance_calculator)
    distance_calculator.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()