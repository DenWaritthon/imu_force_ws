from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch_ros.actions import Node
from launch.substitutions import LaunchConfiguration
from launch.actions import DeclareLaunchArgument, IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
import os

def generate_launch_description():
    
    pkg = get_package_share_directory('imu_force_description')

    rviz_path = os.path.join(pkg,'config','display.rviz')
    rviz = Node(
        package='rviz2',
        executable='rviz2',
        name='rviz',
        arguments=['-d', rviz_path],
        output='screen')
    
    cylinder = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            [
                os.path.join(
                    get_package_share_directory('imu_force_description'),
                    "launch",
                    "cylinder_description.launch.py"
                )
            ]
        ),
    )

    launch_description = LaunchDescription() 
    launch_description.add_action(rviz)
    launch_description.add_action(cylinder)

    return launch_description