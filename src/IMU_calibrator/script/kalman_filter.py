#!/usr/bin/env python3

import rclpy
from rclpy.node import Node
import numpy as np
import yaml
import os
from rclpy.qos import QoSProfile, ReliabilityPolicy
from sensor_msgs.msg import Imu
from math import atan2, sqrt, hypot, atan
from std_msgs.msg import Float64MultiArray
import matplotlib.pyplot as plt
from math import pi
import pandas as pd


K_data = [0.5]
t = [0]
# Get the directory of the current script
script_dir = os.path.dirname(__file__)
# Construct the relative path to the dataset
csv_path = os.path.join(script_dir, '../data/imu_dataset.csv')

# Load the dataset using the dynamically constructed path
df = pd.read_csv(csv_path)

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
        
        process_roll_error = 2
        process_pitch_error = 2
        # initialize state 
        self.x = np.zeros((3, 1))
        self.u = np.zeros((3, 1))   # control input
        
        #estimate variance
        self.p = np.array([process_roll_error**2, process_pitch_error**2])
        
        #measure noise uncertainty in accel sensor
        self.r_roll = df['acc_x'].std()**2
        self.r_pitch = df['acc_y'].std()**2
        
        
        #process noise uncertainty in gyro sensor
        self.p_roll = 0.098033**2
        self.p_pitch = 0.113961**2 
            
        
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
        future_P_pitch = self.p[1] + (self.dt**2) * (self.p_pitch)
        
        #kalman gain update
        K_roll = future_P_roll / ( future_P_roll+self.r_roll )
        K_pitch = future_P_pitch / ( future_P_pitch+self.r_pitch )
        
        K_data.append(K_roll)
        t.append(t[len(t)-1]+self.dt)
        
        #fusion state update
        if abs(angleRoll) > 1.3:
            K_roll = 0
        self.x[0] = future_roll + K_roll * (angleRoll - future_roll)
        self.x[1] = future_pitch + K_pitch * (anglePitch - future_pitch)
        
        #p update
        self.p[0] = (1 - K_roll) * self.p[0]
        self.p[1] = (1 - K_pitch) * self.p[1]
        
        
        pub_msg.orientation.x = float(self.x[0]) 
        pub_msg.orientation.y = float(self.x[1])
        
        self.kalman_publisher.publish(pub_msg)
        
        raw = Float64MultiArray()
        raw.data = [angleRoll  , float(self.x[0]), anglePitch, float(self.x[1])]
        
        raw.data = [angleRoll*180/pi  , float(self.x[0])*180/pi , anglePitch*180/pi , float(self.x[1])*180/pi ]
        
        self.raw_angle_publisher.publish(raw)
        print(f'K_roll : {K_roll}')
        
        print(f'gyro_roll : {self.u[0]}')
        print(f'raw_rate_roll : {msg.angular_velocity.x}')
        print(f'gyro_pitch : {self.u[1]}')
        print(f'raw_rate_pitch : {msg.angular_velocity.y}')
        
        

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