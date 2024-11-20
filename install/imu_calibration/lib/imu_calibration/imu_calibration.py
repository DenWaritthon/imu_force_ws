#!/usr/bin/env python3

import rclpy
from rclpy.node import Node
from rclpy.qos import QoSProfile, ReliabilityPolicy
from ament_index_python.packages import get_package_share_directory
from sensor_msgs.msg import Imu
import os
import numpy as np
import yaml
import csv
from imu_custom_msg.srv import Calibrate
from std_msgs.msg import Float64MultiArray 

class IMUcalibratorNode(Node):
    def __init__(self):
        super().__init__('MU_calibrator_node')  # Name of the node
        self.get_logger().info('IMU_calibrator_Node has been started.')
        self.declare_parameter('file', 'imu_calibration.yaml')
        pkg_name = 'imu_calibration'

        qos_profile = QoSProfile(
            reliability=ReliabilityPolicy.BEST_EFFORT,
            depth=10
        )

        self.create_subscription(Imu, "mpu6050_publisher", self.imu_callback, qos_profile)
        
        self.caibrate_client = self.create_client(Calibrate, "imu/calibrate")
        while not self.caibrate_client.wait_for_service(timeout_sec=1.0):
            self.get_logger().info('Service not available, waiting again...')
        
        imu_calib_pkg_share_path = get_package_share_directory(pkg_name)
        ws_path = imu_calib_pkg_share_path.split('install')
        
        
        file = self.get_parameter('file').value
        self.imu_calib_path = os.path.join(ws_path[0], 'src', 'IMU_calibrator', 'config', file)
        print(self.imu_calib_path)
        print(f"calibration file is save at: {self.imu_calib_path}")

        self.n = 0
        self.n_max = 100
        self.acc_list = []
        self.gyro_list = []
        
        self.dataset_path = os.path.join(ws_path[0], 'src', 'IMU_calibrator', 'data', 'imu_dataset.csv')

    def save_calibration(self, mean, cov, name: str):
        
        with open(self.imu_calib_path, 'r') as file:
            value = yaml.safe_load(file) or {}
        
        mean_List = mean.tolist()
        cov_List = cov.tolist()

        value[f'{name}_offset'] = mean_List
        value[f'{name}_covariance'] = cov_List

        with open(self.imu_calib_path, 'w') as file:
            yaml.dump(value, file)

    def imu_callback(self, msg: Imu):
        if self.n < self.n_max:
            self.n += 1
            self.acc_list.append(
                [msg.linear_acceleration.x,
                 msg.linear_acceleration.y,
                 msg.linear_acceleration.z - 9.81]
            )
            self.gyro_list.append(
                [msg.angular_velocity.x,
                 msg.angular_velocity.y,
                 msg.angular_velocity.z]
            )
            print("collect data: " + str(self.n))
        else:
            acc_array = np.array(self.acc_list)
            acc_offset = np.mean(acc_array, 0)
            acc_cov = np.absolute(np.cov(acc_array.T))

            gyro_array = np.array(self.gyro_list)
            gyro_offset = np.mean(gyro_array, 0)
            gyro_cov = np.absolute(np.cov(gyro_array.T))

            self.save_calibration(acc_offset, acc_cov, 'acc')
            self.save_calibration(gyro_offset, gyro_cov, 'gyro')
            self.save_dataset()
            
            # while not self.caibrate_client.wait_for_service(timeout_sec=1.0):
            #     self.get_logger().info('Service not available, waiting again...')
            #     self.request = Calibrate.Request()

            # print(acc_offset)
            # print(acc_cov)
            # print(gyro_offset)
            
            # print("", end='\n'*2)
            # print("debug: ")
            # print(acc_array)
            # print("", end='\n'*2)
            # print(acc_array.T.shape)
            
            c = []
            for i in acc_offset:
                c.append(i)
            for i in gyro_offset:
                c.append(i)
            c.append(acc_cov[0][0])
            c.append(acc_cov[1][1])
            c.append(acc_cov[2][2])
            c.append(gyro_cov[0][0])
            c.append(gyro_cov[1][1])
            c.append(gyro_cov[2][2])
            
            self.send_request(c)
            
            exit()
            
    def save_dataset(self):
        with open(self.dataset_path, 'w', newline='') as csvfile:
            csv_writer = csv.writer(csvfile)
            csv_writer.writerow(['acc_x', 'acc_y', 'acc_z', 'gyro_x', 'gyro_y', 'gyro_z'])
            for acc, gyro in zip(self.acc_list, self.gyro_list):
                csv_writer.writerow(acc + gyro)

        print(f"Dataset saved to {self.dataset_path}")
        
            
    def send_request(self, a):
        self.request = Calibrate.Request()
        float_array = Float64MultiArray()
        float_array.data = [float(x) for x in a]
        self.request.data = [float_array]  # Wrap in a list
        future = self.caibrate_client.call_async(self.request)
        future.add_done_callback(self.handle_service_response)

            
    def handle_service_response(self, future):
        try:
            response = future.result()
            if response.success:
                self.get_logger().info('Calibration service successful.')
            else:
                self.get_logger().info('Calibration service failed.')
        except Exception as e:
            self.get_logger().error(f'Service call failed with exception: {e}')
            


def main(args=None):
    rclpy.init(args=args)
    node = IMUcalibratorNode()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
