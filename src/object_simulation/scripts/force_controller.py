#!/usr/bin/python3

import rclpy
from rclpy.node import Node
from gazebo_msgs.srv import ApplyLinkWrench
from sensor_msgs.msg import Imu
from geometry_msgs.msg import Point
from rosgraph_msgs.msg import Clock
from rclpy.qos import QoSProfile, ReliabilityPolicy
import math  # Import math for sqrt calculation


class ForceController(Node):
    def __init__(self):
        super().__init__('force_controller')

        # Service client
        self.force_client = self.create_client(ApplyLinkWrench, '/apply_link_wrench')
        
        # Subscription
        self.create_subscription(Imu, 'acceleration', self.acceleration_callback, 10)
        qos_profile = QoSProfile(reliability=ReliabilityPolicy.BEST_EFFORT, depth=10)
        self.create_subscription(Clock, '/clock', self.clock_callback, qos_profile)
        self.create_subscription(Point, '/diff_pose', self.diff_pose_callback, 10)

        # Variables
        self.name = 'model'
        self.mass = 0.2  # Mass in kg
               
        self.acc_x = 0.0
        self.acc_y = 0.0

        self.force_x = 0.0
        self.force_y = 0.0
        
        self.time_sec = 0.0
        self.time_nanosec = 0.0

        self.diff_x = 0.0
        self.diff_y = 0.0
        self.diff_z = 0.0

        # self.k_gain = 0.01

        self.get_logger().info(f'Node Force Controller Start!!!')

    def set_force(self):
        msg = ApplyLinkWrench.Request()

        msg.link_name = self.name
        msg.reference_frame = self.name

        msg.wrench.force.x = self.force_x
        msg.wrench.force.y = self.force_y

        self.set_time()
        msg.start_time.sec = int(self.time_sec)
        msg.start_time.nanosec = int(self.time_nanosec)

        self.force_client.call_async(msg)

        self.get_logger().info(f'force apply x : {self.force_x}, force apply y : {self.force_y}')
        # self.get_logger().info(f'start at: {self.time_sec} sec, {self.time_nanosec} nanosec')

    def set_time(self):
        self.time_nanosec += 1 * (10**9)
        self.time_sec += self.time_nanosec // (10**9)
        self.time_nanosec %= (10**9)

    def force_calcalation(self):
        self.force_x = abs(self.mass * self.acc_x)
        self.force_y = abs(self.mass * self.acc_y)
        # self.get_logger().info(f'force calcalation x : {self.force_x}, force calcalation y : {self.force_y}')

    def acceleration_callback(self, msg: Imu):
        self.acc_x = msg.linear_acceleration.x
        self.acc_y = msg.linear_acceleration.y
        # self.get_logger().info(f'acceleration x : {self.acc_x}, acceleration y : {self.acc_y}')

        if abs(self.diff_x) > 0.5 or abs(self.diff_y) > 0.5:
            self.get_logger().info(f'diff pose x : {self.diff_x}, diff pose y : {self.diff_y}')
            self.force_calcalation()
            
            if round(self.force_x, 2) > 0.02 or round(self.force_y, 2) > 0.02: # If the force is greater than 0.02, apply the force
                self.force_x = self.force_x * (self.diff_x) * 0.01 #self.k_gain
                self.force_y = self.force_y * (self.diff_y) * 0.01#self.k_gainrce
                self.get_logger().info(f'IMU Force')
                self.set_force()
            else:
                self.force_x = 0.02 * self.diff_x * 0.01 #self.k_gain
                self.force_y = 0.02 * self.diff_y * 0.01 #self.k_gain
                self.get_logger().info(f'Add Force')
                self.set_force()
            
    def clock_callback(self, msg: Clock):
        self.time_sec = msg.clock.sec
        self.time_nanosec = msg.clock.nanosec
        # self.get_logger().info(f'clock : {self.time_sec} sec, {self.time_nanosec} nanosec')
    
    def diff_pose_callback(self, msg: Point):
        self.diff_x = msg.x * -1
        self.diff_y = msg.y * -1
        # self.diff_z = msg.z * -1
        # self.get_logger().info(f'diff pose x : {self.diff_x}, diff pose y : {self.diff_y}, diff pose z : {self.diff_z}')

def main(args=None):
    rclpy.init(args=args)
    node = ForceController()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
