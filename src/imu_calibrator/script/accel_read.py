#!/usr/bin/env python3

import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Imu
import yaml
import os
import numpy as np
from rclpy.qos import QoSProfile, ReliabilityPolicy
from collections import deque
from ament_index_python.packages import get_package_share_directory

class LowPassAccelCollector(Node):
    def __init__(self):
        super().__init__('lowpass_accel_collector_node')

        # Declare and get parameter for calibration file
        current_dir = os.path.dirname(os.path.realpath(__file__))
        calibration_file = os.path.join(current_dir, '..', 'config', 'imu_calibration.yaml')
        self.declare_parameter('calibration_file', calibration_file)
        calibration_file = self.get_parameter('calibration_file').get_parameter_value().string_value

        # Load calibration offsets
        self.acc_offset = [0.0, 0.0, 0.0]
        if os.path.exists(calibration_file):
            self.get_logger().info(f"Loading calibration from {calibration_file}")
            with open(calibration_file, 'r') as f:
                calibration_data = yaml.safe_load(f) or {}
            # Adjust this key if your YAML uses a different key for offsets
            if 'acc_offset' in calibration_data:
                self.acc_offset = calibration_data['acc_offset']
                self.get_logger().info(f"Loaded offsets: {self.acc_offset}")
            else:
                self.get_logger().warn("No 'acc_offset' found in calibration file. Using default [0,0,0]")
        else:
            self.get_logger().warn(f"Calibration file {calibration_file} not found. Using default offsets.")

        qos_profile = QoSProfile(
            reliability=ReliabilityPolicy.BEST_EFFORT,
            depth=10
        )
        
        # Subscriber for raw IMU data
        self.create_subscription(Imu, "/mpu6050_publisher", self.imu_callback, qos_profile)
        
        # Publisher for filtered IMU data
        self.filtered_imu_publisher = self.create_publisher(Imu, "/acceleration", qos_profile)

        # Deques for storing recent samples for moving average
        # We will filter all three acceleration axes
        self.window_size = 16  # Number of samples for moving average
        self.acc_x_data = deque(maxlen=self.window_size)
        self.acc_y_data = deque(maxlen=self.window_size)
        self.acc_z_data = deque(maxlen=self.window_size)

    def moving_average_filter(self, data_deque):
        """Compute the moving average for the given deque of data."""
        if len(data_deque) == 0:
            return 0.0
        return float(np.mean(data_deque))
    

    def imu_callback(self, msg: Imu):
        # Apply offset to raw acceleration
        raw_accel_x = msg.linear_acceleration.x - self.acc_offset[0]
        raw_accel_y = msg.linear_acceleration.y - self.acc_offset[1]
        raw_accel_z = msg.linear_acceleration.z - self.acc_offset[2]

        # Append offset-corrected data to deques
        self.acc_x_data.append(raw_accel_x)
        self.acc_y_data.append(raw_accel_y)
        self.acc_z_data.append(raw_accel_z)

        # Compute the moving average filtered values
        filtered_x = self.moving_average_filter(self.acc_x_data)
        filtered_y = self.moving_average_filter(self.acc_y_data)
        filtered_z = self.moving_average_filter(self.acc_z_data)
        
        # filtered_x = raw_accel_x
        # filtered_y = raw_accel_y
        # filtered_z = raw_accel_z

        # Create a new IMU message with filtered data
        filtered_msg = Imu()
        filtered_msg.header = msg.header
        filtered_msg.linear_acceleration.x = round(filtered_x,1)
        filtered_msg.linear_acceleration.y = round(filtered_y,1)
        filtered_msg.linear_acceleration.z = round(filtered_z,1)
        filtered_msg.angular_velocity = msg.angular_velocity  # Keep angular velocity unchanged
        filtered_msg.orientation = msg.orientation  # Keep orientation unchanged

        # Publish the filtered IMU message
        self.filtered_imu_publisher.publish(filtered_msg)

        # Log the filtered values (optional)
        self.get_logger().info(
            f"Filtered IMU: ax={filtered_x:.3f}, ay={filtered_y:.3f}, az={filtered_z:.3f}"
        )


def main(args=None):
    rclpy.init(args=args)
    node = LowPassAccelCollector()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        print("Shutting down...")
    finally:
        if rclpy.ok():
            rclpy.shutdown()


if __name__ == '__main__':
    main()