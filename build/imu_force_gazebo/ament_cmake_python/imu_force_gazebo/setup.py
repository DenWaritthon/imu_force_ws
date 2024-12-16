from setuptools import find_packages
from setuptools import setup

setup(
    name='imu_force_gazebo',
    version='0.0.0',
    packages=find_packages(
        include=('imu_force_gazebo', 'imu_force_gazebo.*')),
)
