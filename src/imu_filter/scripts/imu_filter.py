#!/usr/bin/python3

import rclpy
from rclpy.node import Node
from rclpy.qos import QoSProfile ,ReliabilityPolicy
from ament_index_python import get_package_share_directory
from sensor_msgs.msg import Imu

import os
import yaml


class ImuFilterNode(Node):
    def __init__(self):
        super().__init__('imu_filter_node')

        # Load calibration parameter
        self.declare_parameter('file','imu_calibration.yaml')
        pkg_name = 'imu_filter'

        imu_calib_pkg_share_path = get_package_share_directory(pkg_name)
        ws_path, _ = imu_calib_pkg_share_path.split('install')

        file = self.get_parameter('file').value
        imu_calib_path = os.path.join(ws_path ,'src', pkg_name , 'config', file)

        with open(imu_calib_path, 'r') as file:
            self.calibration_value = yaml.safe_load(file)

        # publisher
        self.imu_offset_pub = self.create_publisher(Imu, 'imu_offset', 10) 
        self.imu_filter_pub = self.create_publisher(Imu, 'imu_filter', 10)

        # Subscription
        qos_profile = QoSProfile(reliability = ReliabilityPolicy.BEST_EFFORT,depth = 10)
        self.create_subscription(Imu,'IMU_publisher', self.imu_callback, qos_profile)

        # timer
        # self.dt = 0.1 # 10 Hz
        # self.timer = self.create_timer(self.dt, self.timer_callback)

        # Variables
        self.imu_acc = [0.0, 0.0, 0.0]
        self.imu_gyro = [0.0, 0.0, 0.0]

        self.acc = [0.0, 0.0, 0.0]
        self.gyro = [0.0, 0.0, 0.0]

        self.filter_acc = [0.0, 0.0, 0.0]
        self.filter_gyro = [0.0, 0.0, 0.0]

        self.a = 0.1

        self.get_logger().info(f'Node Imu Filter Node Start!!!')

    # def timer_callback(self):
    #     pass

    def iir_filter(self):
        self.filter_gyro[0] = (self.a * self.acc[0]) + ((1 - self.a) * self.filter_gyro[0])
        self.filter_gyro[1] = (self.a * self.acc[1]) + ((1 - self.a) * self.filter_gyro[1])
        self.filter_gyro[2] = (self.a * self.acc[2]) + ((1 - self.a) * self.filter_gyro[2])

        self.filter_acc[0] = (self.a * self.acc[0]) + ((1 - self.a) * self.filter_acc[0])
        self.filter_acc[1] = (self.a * self.acc[1]) + ((1 - self.a) * self.filter_acc[1])
        self.filter_acc[2] = (self.a * self.acc[2]) + ((1 - self.a) * self.filter_acc[2])

    def imu_filter_publisher(self):
        msg = Imu()

        msg.angular_velocity.x = self.filter_gyro[0]
        msg.angular_velocity.y = self.filter_gyro[1]
        msg.angular_velocity.z = self.filter_gyro[2]

        msg.linear_acceleration.x = self.filter_acc[0]
        msg.linear_acceleration.y = self.filter_acc[1]
        msg.linear_acceleration.z = self.filter_acc[2]

        self.imu_filter_pub.publish(msg)

    def imu_offset_publisher(self):
        msg = Imu()

        msg.angular_velocity.x = self.gyro[0]
        msg.angular_velocity.y = self.gyro[1]
        msg.angular_velocity.z = self.gyro[2]

        msg.linear_acceleration.x = self.acc[0]
        msg.linear_acceleration.y = self.acc[1]
        msg.linear_acceleration.z = self.acc[2]

        self.imu_offset_pub.publish(msg)

    def imu_offset(self):
        self.gyro[0] = self.imu_gyro[0] - self.calibration_value['gyro offset'][0]
        self.gyro[1] = self.imu_gyro[1] - self.calibration_value['gyro offset'][1]
        self.gyro[2] = self.imu_gyro[2] - self.calibration_value['gyro offset'][2]

        self.acc[0] = self.imu_acc[0] - self.calibration_value['acc offset'][0]
        self.acc[1] = self.imu_acc[1] - self.calibration_value['acc offset'][1]
        self.acc[2] = self.imu_acc[2] - self.calibration_value['acc offset'][2]

    def imu_callback(self, msg :Imu):
        self.imu_acc[0] = msg.linear_acceleration.x
        self.imu_acc[1] = msg.linear_acceleration.y  
        self.imu_acc[2] = msg.linear_acceleration.z  

        self.imu_gyro[0] = msg.angular_velocity.x
        self.imu_gyro[1] = msg.angular_velocity.y
        self.imu_gyro[2] = msg.angular_velocity.z

        self.imu_offset()
        self.imu_offset_publisher()

        self.iir_filter()
        self.imu_filter_publisher()

def main(args=None):
    rclpy.init(args=args)
    node = ImuFilterNode()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__=='__main__':
    main()
