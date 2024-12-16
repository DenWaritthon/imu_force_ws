#!/usr/bin/env python3

import rclpy
from rclpy.node import Node
from imu_custom_msg.srv import Calibrate
from std_msgs.msg import Bool


class CalibrateServiceServer(Node):
    def __init__(self):
        super().__init__('calibrate_service_server')
        self.srv = self.create_service(Calibrate, 'imu/calibrate', self.calibrate_callback)
        self.get_logger().info('Calibrate service server started.')

    def calibrate_callback(self, request, response):
        # Log received data for debugging
        self.get_logger().info(f'Received calibration request with data: {request.data}')

        # Dummy response logic (e.g., returning success if data is non-empty)
        if request.data:
            response.success = Bool(data=True)
            self.get_logger().info('Calibration successful.')
        else:
            response.success = Bool(data=False)
            self.get_logger().info('Calibration failed - no data provided.')

        return response

def main(args=None):
    rclpy.init(args=args)
    node = CalibrateServiceServer()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
