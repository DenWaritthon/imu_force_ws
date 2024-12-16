# Prototype of the system simulating the force acting on the object, referring to the force from the IMU Sensor value.

This repository focuses on developing firmware and implementing signal-processing filters for the STM32 G474RE microcontroller. The goal is to accurately measure and analyze three-axis inertial data (X, Y, and Z) to support simulation in gazebo.

# Table of Contents



# User installation guide 

## Prerequisites

Ensure you have the following dependencies installed

**Hardware Require**
- `STM32 G474RE`
- `MPU6050`

**Middle ware**
- `ROS2 Humble`
- `MicroRos`

**Applications**
- `Gazabo` 
- `STM32CubeIDE`

## Install project workspace
Clone this workspace

```bash
git clone https://github.com/DenWaritthon/imu_force_ws.git -b main
```

# Methodology

## IMU filter
- **Moving Average Algorithm:**  
  A custom node applies a moving average filter to the raw IMU data. This technique helps reduce noise and improve the quality of the measured signals.  
- **Modularity & Extensibility:**  
  The filtering implementation is modular, allowing for the easy integration of additional filters or algorithms in the future.

## Newton's equations

# System architecture 

![System architecture](<picture/System architecture.png>)

System seperate the work into sub-node that work differently 6 node considt of

- IMU_Node (Micro ROS) เป็น node ที่รับค่าของ IMU มาและ Pub ค่าขึ้นไปโดยใช้ Topic : /IMU_data ไปที่ node IMU_calibrate_node และ lowpass_accel_collector_node

- IMU_calabrate_node เป็น Node ที่รับค่าจาก IMU_node (Micro ROS) มาใช้ Calibrate ค่า IMU ให้มีความแม่นยำมากขึ้น

- lowpass_accel_collector_node เป็น Node ที่รับค่าจาก IMU_node (Micro Ros) หลังจากที่ Calibate ค่าไปแล้วโดยจะค่าค่า ความเร่งโดยจะ Pub Topic : /acceleration ไปที่ Node Force_control_node 

- Force_control_node เป็น Node ที่จะรับค่าความเร่งจาก Node : lowpass_accel_collector_node มาคำนวณโดยใช้ Newton's equations เพื่อควบคุม Object ผ่าน Servive :/apply_link_wrench ของ Gazebo

- dummy_imu_acceleration เป็น Node ที่เอาไว้ใช้ทดสอบการทำงานของ Force_control_node ที่จะควบคุม Object ของ Gazebo

- Gazebo_node จะเป็น Node ของโปรแกรม Gazebo ที่เอาไว้แสดงผลของระบบ โดยจะมี Topic : /Odom สำหรับการแสดงตำแหน่งของ Object บน Ground_truth 
  
# User guide

After Clone workspace then Build and source

```bash
cd imu_force_ws/
colcon build
source install/setup.bash
```

## How to use simulation

Run the simulation in ROS2

**Run controller system**

``` bash
ros2 launch imu_force_gazebo sim.launch.py
```

**Run imu calibration**

```bash
ros2 run imu_calibration calibrate.py
```

**Run imu publisher**
```bash
ros2 run imu_calibration controller_node.py
```

### Config IMU 
สามารถแก้แกนของ IMU ได้(ในกรณีที่อย่างเปลี่ยนรูปแบบการวาง)

![imu_config_1](picture/imu_config_1.png)

และสามารถเลือกได้ว่าจะใช้ data แบบไหน 
- raw - bias
- moving average
โดยสามารถเลือก Comment ได้


![imu_config_2](picture/imu_config_2.png)

ถ้า Calibrate แล้วค่าไม่เท่ากับ 0 ให้มาปรับค่าแรงโน้มถ่วงให้ตรงตามท่าที่วางด้วย

![imu_config_3](picture/imu_config_3.png)

# Demos and Result

https://github.com/user-attachments/assets/915b964d-cd14-45ad-b883-2db0a28bd911

# Conclusion
Simulation the movement of the human arm using ROS2 Humble and use various python libraries for instance roboticstoolbox, spatialmath, numpy, scipy and pygame for the user interface. This simulation simulate the human arm from the shoulder to the wrist. And 3D visualized by RVIZ in ROS2 that can control manually by input or using the user interface for the easier use.
\
But the thing that we have not been done is Test and Validate compare to the real human arm so it will be in our future plans.  

# Future plan
- Explore advanced filtering algorithms (e.g., Kalman filters) for improved accuracy and robustness.
- Expand documentation and provide example code to facilitate integration into larger robotics or control systems.

   
# Developer Member

- Waritthon Kongnoo
- Kraiwich Vichakhot
- Chayanin Napia