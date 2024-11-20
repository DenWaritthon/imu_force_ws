import yaml
import numpy as np
import os

def read_yaml_config(file_path):
    with open(file_path, 'r') as file:
        config = yaml.safe_load(file)
    
    acc_covariance = np.array(config['acc_covariance'])
    acc_offset = np.array(config['acc_offset']).reshape(-1, 1)
    gyro_covariance = np.array(config['gyro_covariance'])
    gyro_offset = np.array(config['gyro_offset']).reshape(-1, 1)
    
    return acc_covariance, acc_offset, gyro_covariance, gyro_offset

# Example usage
package_path = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
config_file = os.path.join(package_path, 'config', 'imu_calibration.yaml')
acc_covariance, acc_offset, gyro_covariance, gyro_offset = read_yaml_config(config_file)

print("Accelerometer Covariance:\n", acc_covariance)
print("Accelerometer Offset:\n", acc_offset)
print("Gyroscope Covariance:\n", gyro_covariance)
print("Gyroscope Offset:\n", gyro_offset)
