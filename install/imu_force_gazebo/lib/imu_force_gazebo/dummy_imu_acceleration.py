#!/usr/bin/python3

import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Imu


class DummyIMUAcceleration(Node):
    def __init__(self):
        super().__init__('dummy_imu_acceleration')

        # publisher 
        self.accleration_pub = self.create_publisher(Imu, '/acceleration', 10)
        
        # timer
        self.dt = 3.0 # 3 sec
        self.create_timer(self.dt, self.timer_loop)
        
        # variable
        self.acc_x = [0.0, 10.0, 0.0, 0.0, 0.0, -10.0, 0.0]
        self.acc_y = [0.0, 5.0, 0.0, 0.0, 0.0, -5.0, 0.0]

        self.get_logger().info(f'Node Dummy IMU Acceleration Start!!!')

    def pub_accleration(self, a_x, a_y):
        msg = Imu()
        msg.linear_acceleration.x = a_x
        msg.linear_acceleration.y = a_y

        self.accleration_pub.publish(msg)

    def timer_loop(self):
        if len(self.acc_x) != 0 and len(self.acc_y) != 0 :
            a_x = self.acc_x.pop(0)
            a_y = self.acc_y.pop(0)
            self.pub_accleration(a_x,a_y)
            self.get_logger().info(f'acceleration x : {a_x}, acceleration y : {a_y}')
        else:
            self.get_logger().info(f'acceleration list Empty!!')



def main(args=None):
    rclpy.init(args=args)
    node = DummyIMUAcceleration()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__=='__main__':
    main()
