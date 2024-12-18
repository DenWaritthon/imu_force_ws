#!/usr/bin/python3

import rclpy
from rclpy.node import Node
from gazebo_msgs.srv import ApplyLinkWrench
from sensor_msgs.msg import Imu
from rosgraph_msgs.msg import Clock
from rclpy.qos import QoSProfile, QoSReliabilityPolicy
import math  # Import math for sqrt calculation


class ForceController(Node):
    def __init__(self):
        super().__init__('force_controller')

        # Service client
        self.force_client = self.create_client(ApplyLinkWrench, '/apply_link_wrench')
        # Set QoS profile to Best Effort to match Gazebo's /clock publisher
        qos_profile = QoSProfile(depth=10, reliability=QoSReliabilityPolicy.BEST_EFFORT)
        self.create_subscription(Clock, '/clock', self.clock_callback, qos_profile)

        # IMU Subscription
        self.create_subscription(Imu, '/acceleration', self.acceleration_callback, qos_profile)

        # Variables
        self.name = 'cylinder'
        self.force_x = 0.0
        self.force_y = 0.0
        self.force_stack_x = 0.0
        self.force_stack_y = 0.0

        self.mass = 2.0 # Mass of the cylinder in kg

        self.acc_x = 0.0
        self.acc_y = 0.0

        self.time_sec = 0.0
        self.time_nanosec = 0.0

        self.get_logger().info(f'Node Force Controller Start!!!')

    def set_force(self):
        """Prepare and send the ApplyLinkWrench request."""
        msg = ApplyLinkWrench.Request()

        msg.link_name = self.name
        msg.reference_frame = 'world'  # Apply force in world frame for consistency

        msg.wrench.force.x = self.force_x
        # msg.wrench.force.y = self.force_y

        self.set_time()
        msg.start_time.sec = int(self.time_sec)
        msg.start_time.nanosec = int(self.time_nanosec)

        msg.duration.sec = 0
        msg.duration.nanosec = 1_000_000  # Apply force for 1 ms

        self.force_client.call_async(msg)

        # self.get_logger().info(f'Force applied x: {self.force_x}, y: {self.force_y}')
        # self.get_logger().info(f'Force applied y: {self.force_y}')
        self.get_logger().info(f'Start at: {self.time_sec} sec, {self.time_nanosec} nanosec')

    def set_time(self):
        """Synchronize start time with simulation clock."""
        self.time_nanosec += 1 * (10**9)
        self.time_sec += self.time_nanosec // (10**9)
        self.time_nanosec %= (10**9)

    # def force_calculation(self):
    #     """Calculate the force based on acceleration and mass."""
    #     self.force_x = self.mass * self.acc_x
    #     self.force_y = self.mass * self.acc_y
    #     self.force_stack_x += self.force_x
    #     self.force_stack_y += self.force_y
    #     self.get_logger().info(f'Force calculation x: {self.force_x}, y: {self.force_y}')

    def force_calculation_x(self):
        """Calculate the force based on acceleration and mass."""
        self.force_x = self.mass * self.acc_x
        self.force_stack_x += self.force_x
        self.get_logger().info(f'Force calculation x: {self.force_stack_x}')

    def force_calculation_y(self):
        """Calculate the force based on acceleration and mass."""
        self.force_y = self.mass * self.acc_y
        self.force_stack_y += self.force_y
        self.get_logger().info(f'Force calculation y: {self.force_stack_y}')

    def acceleration_callback(self, msg: Imu):
        """Callback for IMU acceleration data."""
        self.acc_x = msg.linear_acceleration.x
        self.acc_y = msg.linear_acceleration.y

        # Calculate acceleration magnitude
        # magnitude = math.sqrt(self.acc_x**2 + self.acc_y**2)

        # self.get_logger().info(f'Acceleration x: {self.acc_x}, y: {self.acc_y}')

        # Apply force only if acceleration magnitude > 0.5
        # self.get_logger().info(f'Stack Force x: {self.force_stack_x}, y: {self.force_stack_y}')
        # if abs(self.acc_x) > 0.15 or abs(self.acc_y) > 0.15:            
        #     if abs(self.acc_x) > 0.15:
        #         self.get_logger().info(f'Acceleration x {abs(self.acc_x)} > 0.15')
        #         self.force_calculation_x()

        #     if abs(self.acc_y) > 0.15:
        #         self.get_logger().info(f'Acceleration y {abs(self.acc_y)} > 0.15')
        #         self.force_calculation_y()
            
        #     self.set_force()
        if abs(self.acc_x) > 0.15:
                self.get_logger().info(f'Acceleration x {abs(self.acc_x)} > 0.15')
                self.force_calculation_x()
                self.set_force()
        else:
            # self.get_logger().info(f'Acceleration magnitude {abs(self.acc_y):.3f} <= 0.5, no force applied.')
            # self.get_logger().info(f'Stack Force x: {self.force_stack_x}, y: {self.force_stack_y}')
            # self.force_x = self.force_stack_x * -1
            # self.force_y = self.force_stack_y * -1
            
            if (self.force_stack_x > abs(0.0)):
                self.get_logger().info(f'Stop Force x: {self.force_x*-1} !!!!!!!!!')
                # self.force_x = self.force_stack_x * -1
                # self.set_force()
            self.force_stack_x = 0.0
            self.force_stack_y = 0.0
            
        # self.force_calculation()
        # self.set_force()

    def clock_callback(self, msg: Clock):
        """Callback for simulation clock updates."""
        self.time_sec = msg.clock.sec
        self.time_nanosec = msg.clock.nanosec


def main(args=None):
    rclpy.init(args=args)
    node = ForceController()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
