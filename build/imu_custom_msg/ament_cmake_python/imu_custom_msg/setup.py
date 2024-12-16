from setuptools import find_packages
from setuptools import setup

setup(
    name='imu_custom_msg',
    version='0.0.0',
    packages=find_packages(
        include=('imu_custom_msg', 'imu_custom_msg.*')),
)
