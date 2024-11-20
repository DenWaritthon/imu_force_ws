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
        
        # Load calibration data
        self.package_path = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
        self.config_file = os.path.join(self.package_path, 'config', 'imu_calibration.yaml')
        self.acc_covariance, self.acc_offset, self.gyro_covariance, self.gyro_offset = self.read_yaml_config(self.config_file)
        
        # Time step (assuming constant sampling rate)
        self.dt = 0.01  # Adjust according to your actual sampling rate
        
        # Initialize state vector [a_x, a_y, a_z, j_x, j_y, j_z]
        self.x = np.zeros((6, 1))
        
        # Initialize covariance matrix
        self.P = np.eye(6) * 1.0  # Initial uncertainty
        
        # Process noise covariance
        q_accel = 0.0001  # Process noise variance for acceleration (tunable)
        q_jerk = 0.0001  # Process noise variance for jerk (tunable)
        self.Q = np.diag([q_accel]*3 + [q_jerk]*3)
        
        # Measurement noise covariance
        r_meas = 0.0031879987532569447  # Measurement noise variance for acceleration (tunable)
        self.R = np.eye(3) * r_meas
        
        # State transition matrix
        self.F = np.array([
            [1, 0, 0, self.dt, 0, 0],
            [0, 1, 0, 0, self.dt, 0],
            [0, 0, 1, 0, 0, self.dt],
            [0, 0, 0, 1, 0, 0],
            [0, 0, 0, 0, 1, 0],
            [0, 0, 0, 0, 0, 1],
        ])
        
        # Measurement matrix
        self.H = np.array([
            [1, 0, 0, 0, 0, 0],  # Measuring a_x
            [0, 1, 0, 0, 0, 0],  # Measuring a_y
            [0, 0, 1, 0, 0, 0],  # Measuring a_z
        ])
        
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
        
        # Kalman Filter Prediction Step
        # x_k|k-1 = F * x_k-1|k-1
        x_pred = self.F @ self.x
        
        # P_k|k-1 = F * P_k-1|k-1 * F^T + Q
        P_pred = self.F @ self.P @ self.F.T + self.Q
        
        # Kalman Filter Update Step
        # Innovation or measurement residual
        y = z - (self.H @ x_pred)
        
        # Innovation covariance
        S = self.H @ P_pred @ self.H.T + self.R
        
        # Optimal Kalman gain
        K = P_pred @ self.H.T @ np.linalg.inv(S)
        
        # Updated state estimate
        self.x = x_pred + K @ y
        
        # Updated estimate covariance
        self.P = (np.eye(6) - K @ self.H) @ P_pred
        
        # Extract filtered acceleration and jerk estimates
        a_est = self.x[0:3]  # Acceleration estimates
        j_est = self.x[3:6]  # Jerk estimates
        
        # Create a new Imu message with filtered acceleration data
        filtered_msg = Imu()
        filtered_msg.header = msg.header
        filtered_msg.linear_acceleration.x = float(a_est[0])
        filtered_msg.linear_acceleration.y = float(a_est[1])
        filtered_msg.linear_acceleration.z = float(a_est[2])
        filtered_msg.angular_velocity = msg.angular_velocity
        filtered_msg.orientation = msg.orientation  # Keep orientation as is
        
        # Publish the filtered IMU message
        self.kalman_publisher.publish(filtered_msg)
        
        # Optionally, publish the raw and filtered acceleration data for comparison
        raw = Float64MultiArray()
        raw.data = [
            float(z[0]), float(a_est[0]),  # X-axis: raw and filtered acceleration
            float(z[1]), float(a_est[1]),  # Y-axis: raw and filtered acceleration
            float(z[2]), float(a_est[2]),  # Z-axis: raw and filtered acceleration
            float(j_est[0]),               # X-axis jerk estimate
            float(j_est[1]),               # Y-axis jerk estimate
            float(j_est[2])                # Z-axis jerk estimate
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
