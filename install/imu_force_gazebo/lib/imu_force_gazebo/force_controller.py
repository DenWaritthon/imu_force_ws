#!/usr/bin/python3

import rclpy
from rclpy.node import Node
from gazebo_msgs.srv import ApplyLinkWrench
from sensor_msgs.msg import Imu
from rosgraph_msgs.msg import Clock
from rclpy.qos import QoSProfile, QoSReliabilityPolicy


class ForceController(Node):
    def __init__(self):
        super().__init__('force_controller')

        # service client
        self.force_client = self.create_client(ApplyLinkWrench, '/apply_link_wrench')

        # subscription
        self.create_subscription(Imu, '/acceleration', self.acceleration_callback, 10)

        # Set QoS profile to Best Effort to match Gazebo's /clock publisher
        qos_profile = QoSProfile(depth=10, reliability=QoSReliabilityPolicy.BEST_EFFORT)
        self.create_subscription(Clock, '/clock', self.clock_callback, qos_profile)

        # variable
        self.name = 'cylinder'
        self.force_x = 0.0
        self.force_y = 0.0

        self.mass = 1

        self.acc_x = 0.0
        self.acc_y = 0.0

        self.time_sec = 0.0
        self.time_nanosec = 0.0

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
        self.get_logger().info(f'start at: {self.time_sec} sec, {self.time_nanosec} nanosec')

    def  set_time(self):
        self.time_nanosec +=  1* (10**9)
        self.time_sec += self.time_nanosec // (10**9)
        self.time_nanosec %= (10**9)

    def force_calcalation(self):
        self.force_x = self.mass * self.acc_x
        self.force_y = self.mass * self.acc_y
        self.get_logger().info(f'force calcalation x : {self.force_x}, force calcalation y : {self.force_y}')

    def acceleration_callback(self, msg:Imu):
        self.acc_x = msg.linear_acceleration.x
        self.acc_y = msg.linear_acceleration.y
        self.get_logger().info(f'acceleration x : {self.acc_x}, acceleration y : {self.acc_y}')
        self.force_calcalation()

        self.set_force()

    def clock_callback(self, msg:Clock):
        self.time_sec = msg.clock.sec
        self.time_nanosec = msg.clock.nanosec
        # self.get_logger().info(f'clock : {self.time_sec} sec, {self.time_nanosec} nanosec')


def main(args=None):
    rclpy.init(args=args)
    node = ForceController()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__=='__main__':
    main()
