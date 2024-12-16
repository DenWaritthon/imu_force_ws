#!/usr/bin/env python3

import rclpy
from rclpy.node import Node
import numpy as np
import yaml
import os
from rclpy.qos import QoSProfile, ReliabilityPolicy
from sensor_msgs.msg import Imu
from std_msgs.msg import Float64MultiArray

class KalmanNode(Node):
    def __init__(self):
        super().__init__('kalman_filter_node')
        
        qos_profile = QoSProfile(
            reliability=ReliabilityPolicy.BEST_EFFORT,
            depth=10
        )
        
        self.create_subscription(Imu, "mpu6050_publisher", self.imu_callback, qos_profile)
        self.kalman_publisher = self.create_publisher(Imu, "kalman_publisher", qos_profile)
        self.raw_accel_publisher = self.create_publisher(Float64MultiArray, "raw_acceleration", qos_profile)
        
        self.package_path = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
        self.config_file = os.path.join(self.package_path, 'config', 'imu_calibration.yaml')
        self.acc_covariance, self.acc_offset, self.gyro_covariance, self.gyro_offset = self.read_yaml_config(self.config_file)
        
        # Initialize Kalman filter variables for acceleration
        
        self.a = np.zeros((3, 1))  # State estimates for acceleration [a_x, a_y, a_z]
        self.P = np.ones((3, 1)) * 1.0  # Initial estimate error covariance
        self.Q = np.ones((3, 1)) * 0.01  # Process noise variance (tunable)
        self.R = np.ones((3, 1)) * 1.0   # Measurement noise variance (tunable)
        
    def read_yaml_config(self, file_path):
        with open(file_path, 'r') as file:
            config = yaml.safe_load(file)
        
        acc_covariance = np.array(config['acc_covariance'])
        acc_offset = np.array(config['acc_offset']).reshape(-1, 1)
        gyro_covariance = np.array(config['gyro_covariance'])
        gyro_offset = np.array(config['gyro_offset']).reshape(-1, 1)
    
        return acc_covariance, acc_offset, gyro_covariance, gyro_offset
    
    def imu_callback(self, msg: Imu):
        # Correct the accelerometer data with calibration offsets
        Ax = msg.linear_acceleration.x - float(self.acc_offset[0])
        Ay = msg.linear_acceleration.y - float(self.acc_offset[1])
        Az = msg.linear_acceleration.z - float(self.acc_offset[2])
        
        # Measured acceleration vector
        z = np.array([
            [Ax],
            [Ay],
            [Az]
        ])
        
        # Apply the Kalman filter to each axis
        for i in range(3):
            # Prediction step (state remains the same as we assume constant acceleration)
            P_priori = self.P[i] + self.Q[i]
            
            # Update step
            K = P_priori / (P_priori + self.R[i])
            self.a[i] = self.a[i] + K * (z[i] - self.a[i])
            self.P[i] = (1 - K) * P_priori
        
        # Create a new Imu message with filtered acceleration data
        filtered_msg = Imu()
        filtered_msg.header = msg.header
        filtered_msg.linear_acceleration.x = float(self.a[0])
        filtered_msg.linear_acceleration.y = float(self.a[1])
        filtered_msg.linear_acceleration.z = float(self.a[2])
        filtered_msg.angular_velocity = msg.angular_velocity
        filtered_msg.orientation = msg.orientation
        
        # Publish the filtered IMU message
        self.kalman_publisher.publish(filtered_msg)
        
        # Optionally, publish the raw and filtered acceleration data for comparison
        raw = Float64MultiArray()
        raw.data = [
            float(z[0]), float(self.a[0]),  # X-axis: raw and filtered
            float(z[1]), float(self.a[1]),  # Y-axis: raw and filtered
            float(z[2]), float(self.a[2])   # Z-axis: raw and filtered
        ]
        self.raw_accel_publisher.publish(raw)

def main(args=None):
    rclpy.init(args=args)
    node = KalmanNode()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        print("Shutting down...")
    finally:
        if rclpy.ok():
            rclpy.shutdown()

if __name__ == '__main__':
    main()
