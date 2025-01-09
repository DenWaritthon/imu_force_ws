#!/usr/bin/python3

import rclpy
from rclpy.node import Node

from geometry_msgs.msg import Point
from nav_msgs.msg import Odometry


class ArucoController(Node):
    def __init__(self):
        super().__init__('aruco_controller')

        # Publisher
        self.diff_pose_client = self.create_publisher(Point, '/diff_pose', 10)

        # Subscription
        self.create_subscription(Point, '/object_pose', self.object_pose_callback, 10)
        self.subscription = self.create_subscription(Odometry, '/odom', self.odom_callback, 10)

        # timer 
        self.create_timer(0.1, self.timer_callback)

        # variables
        self.object_pose_x = 0.0
        self.object_pose_y = 0.0
        self.object_pose_z = 0.0
        self.odom_x = 0.0
        self.odom_y = 0.0
        self.odom_z = 0.0

        #logger
        self.get_logger().info(f'Node Aruco Controller Start!!!')

    def object_pose_callback(self, msg:Point):
        self.object_pose_x = msg.x
        self.object_pose_y = msg.y
        self.object_pose_z = msg.z
        pass

    def odom_callback(self, msg:Odometry):
        self.odom_x = round(msg.pose.pose.position.x * 100, 2)
        self.odom_y = round(msg.pose.pose.position.y * 100, 2)
        self.odom_z = round(msg.pose.pose.position.z * 100, 2)

        # self.get_logger().info(f'\nDistance x: {x} cm.\nDistance y: {y} cm.\nDistance z: {z} cm.')

    def timer_callback(self):
        diff_x = self.odom_x - self.object_pose_x
        diff_y = self.odom_y - self.object_pose_y
        diff_z = self.odom_z - self.object_pose_z

        msg = Point()
        msg.x = diff_x
        msg.y = diff_y
        msg.z = diff_z
        self.diff_pose_client.publish(msg)
        
def main(args=None):
    rclpy.init(args=args)
    node = ArucoController()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__=='__main__':
    main()
