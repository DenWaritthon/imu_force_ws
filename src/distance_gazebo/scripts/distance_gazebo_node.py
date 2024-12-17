#!/usr/bin/python3

import rclpy
from rclpy.node import Node
from nav_msgs.msg import Odometry
from std_msgs.msg import Float64
from geometry_msgs.msg import Pose
import math

class DistanceCalculator(Node):
    def __init__(self):
        super().__init__('distance_gazebo_node')
        self.displacement_pub = self.create_publisher(Float64, 'displacement', 10)
        self.distance_pub = self.create_publisher(Pose, 'distance', 10)
        self.subscription = self.create_subscription(Odometry, '/odom', self.odom_callback, 10)
        self.timer = self.create_timer(0.1, self.timer_callback)  # 10 Hz

    def odom_callback(self, msg):
        x = msg.pose.pose.position.x
        y = msg.pose.pose.position.y
        z = msg.pose.pose.position.z

        displacement = math.sqrt(x**2 + y**2 + z**2)
        self.displacement_pub.publish(Float64(data=displacement))

        distance = Pose()
        distance.position.x = x
        distance.position.y = y
        distance.position.z = z
        self.distance_pub.publish(distance)

    def timer_callback(self):
        pass  # Timer callback is required to keep the node alive

def main(args=None):
    rclpy.init(args=args)
    distance_calculator = DistanceCalculator()
    rclpy.spin(distance_calculator)
    distance_calculator.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()