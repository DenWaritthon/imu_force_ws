#!/usr/bin/env python3

import rclpy
from rclpy.node import Node
import numpy as np
import yaml
import os
from rclpy.qos import QoSProfile, ReliabilityPolicy
from sensor_msgs.msg import Imu
from math import atan2, sqrt, hypot
from std_msgs.msg import Float64MultiArray
import matplotlib.pyplot as plt


K_data = [0.5]
t = [0]

class KalmanNode(Node):
    def __init__(self):
        super().__init__('kalman_filter_node')
        
        qos_profile = QoSProfile(
            reliability=ReliabilityPolicy.BEST_EFFORT,
            depth=10
        )
        
        self.create_subscription(Imu, "mpu6050_publisher", self.imu_callback, qos_profile)
        self.kalman_publisher = self.create_publisher(Imu, "kalman_publisher",qos_profile)
        self.raw_angle_publisher = self.create_publisher(Float64MultiArray, "raw_angle",qos_profile)
        
        self.package_path = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
        self.config_file = os.path.join(self.package_path, 'config', 'imu_calibration.yaml')
        self.acc_covariance, self.acc_offset, self.gyro_covariance, self.gyro_offset = self.read_yaml_config(self.config_file)
        
    
        self.dt = 0.01
        
        process_roll_error = 0.5
        process_pitch_error = 0.5
        # initialize state 
        self.x = np.zeros((3, 1))
        self.u = np.zeros((3, 1))   # control input
        
        #estimate variance
        self.p = np.array([process_roll_error**2, process_pitch_error**2])
        self.r_roll = 0.45**2
        self.r_pitch = 1.5**2
        
    def read_yaml_config(self,file_path):
        with open(file_path, 'r') as file:
            config = yaml.safe_load(file)
        
        acc_covariance = np.array(config['acc_covariance'])
        acc_offset = np.array(config['acc_offset']).reshape(-1, 1)
        gyro_covariance = np.array(config['gyro_covariance'])
        gyro_offset = np.array(config['gyro_offset']).reshape(-1, 1)
    
        return acc_covariance, acc_offset, gyro_covariance, gyro_offset
    
    def imu_callback(self, msg: Imu):
        
        pub_msg = msg
        pub_msg.linear_acceleration.x -= float(self.acc_offset[0])
        pub_msg.linear_acceleration.y -= float(self.acc_offset[1])
        pub_msg.linear_acceleration.z -= float(self.acc_offset[2])
        
        #measure angular rate
        self.u[0] = msg.angular_velocity.x - float(self.gyro_offset[0])
        self.u[1] = msg.angular_velocity.y - float(self.gyro_offset[1])
        self.u[2] = msg.angular_velocity.z - float(self.gyro_offset[2])

        Ax = pub_msg.linear_acceleration.x
        Ay = pub_msg.linear_acceleration.y
        Az = pub_msg.linear_acceleration.z
        
        # angle from accelerometor
        angleRoll = atan2(Ay, hypot(Ax, Az))
        anglePitch = atan2(-Ax, hypot(Ay, Az))
        
        #predict step
        future_roll = self.x[0] + self.dt * self.u[0]
        future_pitch = self.x[1] + self.dt * self.u[1]
        
        future_P_roll = self.p[0] + (self.dt**2) * (0.04)
        future_P_pitch = self.p[1] + (self.dt**2) * (0.03)
        
        #kalman gain update
        K_roll = future_P_roll / ( future_P_roll+self.r_roll )
        K_pitch = future_P_pitch / ( future_P_pitch+self.r_pitch )
        
        K_data.append(K_roll)
        t.append(t[len(t)-1]+self.dt)
        
        #fusion state update
        self.x[0] = future_roll + K_roll * (angleRoll - future_roll)
        self.x[1] = future_pitch + K_pitch * (anglePitch - future_pitch)
        
        #p update
        self.p[0] = (1 - K_roll) * self.p[0]
        self.p[1] = (1 - K_pitch) * self.p[1]
        
        
        pub_msg.orientation.x = float(self.x[0])
        pub_msg.orientation.y = float(self.x[1])
        
        self.kalman_publisher.publish(pub_msg)
        
        raw = Float64MultiArray()
        raw.data = [angleRoll, anglePitch, float(K_pitch)]
        
        self.raw_angle_publisher.publish(raw)
        print(f'K_roll : {K_roll}')
        

def main(args=None):
    rclpy.init(args=args)
    node = KalmanNode()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        print("Shutting down and plotting data...")
    finally:
        if rclpy.ok():  # Check if ROS is still active
            rclpy.shutdown()
        
        # Plot only if there is data collected
        if len(t) > 1 and len(K_data) > 0:
            plt.plot(t, K_data, label='K_roll')
            plt.xlabel("Time (s)")
            plt.ylabel("Kalman Gain (K_roll)")
            plt.title("Kalman Gain over Time")
            plt.legend()
            plt.show()
        else:
            print("No data to plot.")

if __name__ == '__main__':
    main()