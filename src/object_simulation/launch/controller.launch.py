from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='object_simulation',
            executable='force_controller.py',
            name='force_controller',
            output='screen'
        ),
        Node(
            package='object_simulation',
            executable='aruco_controller.py',
            name='aruco_controller',
            output='screen'
        )
    ])