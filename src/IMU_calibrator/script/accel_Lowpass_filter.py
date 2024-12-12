import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Imu
from collections import deque
from rclpy.qos import QoSProfile, ReliabilityPolicy

class ImuFilterNode(Node):
    def __init__(self):
        super().__init__('imu_filter_node')
        
        # Define the window size for the moving average
        self.window_size = 8
        
        # Deques to store recent acceleration values for moving average
        self.acc_x = deque(maxlen=self.window_size)
        self.acc_y = deque(maxlen=self.window_size)
        self.acc_z = deque(maxlen=self.window_size)

        # Define QoS profile
        qos_profile = QoSProfile(
            reliability=ReliabilityPolicy.BEST_EFFORT,
            depth=10
        )
        
        # Subscriber for raw IMU data
        self.subscription = self.create_subscription(
            Imu,
            '/mpu6050_publisher',
            self.imu_callback,
            qos_profile
        )

        # Publisher for moving average filtered IMU data
        self.moving_pub = self.create_publisher(
            Imu,
            '/filtered_imu_moving',
            qos_profile
        )

    def imu_callback(self, msg: Imu):
        # Extract linear acceleration from the incoming message
        ax = msg.linear_acceleration.x
        ay = msg.linear_acceleration.y
        az = msg.linear_acceleration.z
        
        # Append new values for moving average calculation
        self.acc_x.append(ax)
        self.acc_y.append(ay)
        self.acc_z.append(az)
        
        # Compute moving average
        moving_ax = sum(self.acc_x) / len(self.acc_x)
        moving_ay = sum(self.acc_y) / len(self.acc_y)
        moving_az = sum(self.acc_z) / len(self.acc_z)
        
        # Create and publish IMU message with moving average filtering
        moving_msg = Imu()
        moving_msg.header = msg.header
        moving_msg.orientation = msg.orientation
        moving_msg.angular_velocity = msg.angular_velocity
        moving_msg.linear_acceleration.x = moving_ax
        moving_msg.linear_acceleration.y = moving_ay
        moving_msg.linear_acceleration.z = moving_az
        
        self.moving_pub.publish(moving_msg)

def main(args=None):
    rclpy.init(args=args)
    node = ImuFilterNode()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()

if __name__ == '__main__':
    main()
