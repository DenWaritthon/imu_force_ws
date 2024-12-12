# imu_force_ws

**Project Description:**  
This repository focuses on developing firmware and implementing signal-processing filters for the STM32 G474RE microcontroller. The goal is to accurately measure and analyze three-axis inertial data (X, Y, and Z) to support advanced motion analysis and control applications.

The project is divided into two main parts: a hardware interface and a software-based filtering system.

## 1. Hardware Interface
- **Sensor:** MPU6050  
  The MPU6050 is a popular inertial measurement unit (IMU) that integrates a 3-axis accelerometer and a 3-axis gyroscope into a single chip.  
- **STM32 G474RE Integration:**  
  The firmware ensures stable communication with the MPU6050 through I2C, configures the device registers, and retrieves raw data in real-time.

## 2. Software Filter
- **Moving Average Algorithm:**  
  A custom node applies a moving average filter to the raw IMU data. This technique helps reduce noise and improve the quality of the measured signals.  
- **Modularity & Extensibility:**  
  The filtering implementation is modular, allowing for the easy integration of additional filters or algorithms in the future.

**Future Enhancements:**
- Explore advanced filtering algorithms (e.g., Kalman filters) for improved accuracy and robustness.
- Expand documentation and provide example code to facilitate integration into larger robotics or control systems.
