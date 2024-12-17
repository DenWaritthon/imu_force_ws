# Prototype of the system simulating the force acting on the object, referring to the force from the IMU Sensor value.

This repository focuses on developing firmware and implementing signal-processing filters for the STM32 G474RE microcontroller. The goal is to accurately measure and analyze three-axis inertial data (X, Y, and Z) to support simulation in gazebo.

# Table of Contents


# Objective
- To create a simulation system for the movement of objects when a force is applied to the Gazebo by using the actual force obtained by converting the value from the IMU Sensor into the force that will be applied to the object on the Gazebo.

# Scope
- **Actual Object**
  - The actual object is a cylinder with a diameter of 32 mm and a height of 60 mm. An IMU sensor is attached at the center of the object, which is made from PETG plastic.
- **Simulation System**
  -  The system is constructed on Gazebo with the object model being a cylinder of the same size as the actual object.
  -  The force applied to the object in the simulation system is only applied at the center of the object.
  -  The force applied will only be in the x and y axes.
- **Testing System**
  - Testing is conducted by attaching the actual object to a core XY movement system that can move 0.18 m in the x-axis and 0.18 m in the y-axis.
  - The system will move with an acceleration not exceeding 0.5 m/s².

# User installation guide 

## Prerequisites

Ensure you have the following dependencies installed

**Hardware Require**
- `STM32 G474RE`
- `MPU6050`
  
**Hardware Setup**
**Pin Connections**

| STM32G474RE Pin | MPU6050 Pin |
|-----------------|-------------|
| 5V              | VCC         |
| GND             | GND         |
| PB_8/D15        | SCL         |
| PB_9/D14        | SDA         |

![pic_connections](picture/imu_force_pin.png)

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

Convert the velocity obtained from the IMU into a force to apply to the object in Guzabo using Newton's equations.
```math
\sum F = ma
```

Given
- $F$ is the force to be obtained
- $m$ is the weight of the actual object, which weighs **xx kg. แก้ใน code ด้วย**
- $a$ is the acceleration measured by the IMU


# System architecture 

![System architecture](<picture/System architecture.png>)

System separate the work into sub-node that work differently 6 node consist of

- IMU_Node (Micro ROS) is a node that have input value from IMU and Pub the value to Topic : /IMU_data to the node IMU_calibrate_node and lowpass_accel_collector_node.

- IMU_calabrate_node is a Node that have input value from IMU_node (Micro ROS) to Calibrate value of the IMU to make it more accurate.

- lowpass_accel_collector_node is a Node that have a input value from IMU_node (Micro Ros) after Calibate the value then the accelerate value by Pub Topic : /acceleration to Node Force_control_node.

- Force_control_node is a Node that get input of accelerate value from Node : lowpass_accel_collector_node to calculate in Newton's equations to control Object by Servive :/apply_link_wrench of Gazebo.

- dummy_imu_acceleration is a Node that is for testing of  Force_control_node that control Object of Gazebo.

- Gazebo_node is a Node of  Gazebo program that will be display result of the system that have Topic : /Odom for display the position of the Object on Ground_truth.

- distance_gazebo_node is a Node that have input value from Node : Gazebo_node to calculate distance and displacement origin to Object.
  
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
Able to edit the axis of the IMU (In case of that you want to rotate the axis)

![imu_config_1](picture/imu_config_1.png)

And able to choose from this two option below
- raw – bias
- moving average
By comment the code
And after that you need to colcon build to build the project so the project can be work properly

![imu_config_2](picture/imu_config_2.png)   

If calibrate and the value  is not  0 you need to configuration the gravity according to the axis set as well

![imu_config_3](picture/imu_config_3.png)

If you make any changes, don't forget to run `colcon build` again.

# Demos and Result

This section showcases the system's capabilities and results.

Setup for testing in real world with 3D printer for test x any y axis 

**Video Kriwich1**

**Video Here plane1**

# Conclusion

Our system demonstrated successful real-time synchronization between virtual and physical objects. However, during automated testing utilizing a 3D-printed motion platform, the embedded IMU was susceptible to noise induced by the stepper motor system, hindering accurate object tracking. Manual intervention revealed that the system was capable of precise movement, suggesting that the noise interference was the primary cause of the observed inaccuracies.

# Future plan
- Explore advanced filtering algorithms (e.g., Kalman filters) for improved accuracy and robustness.
- Expand documentation and provide example code to facilitate integration into larger robotics or control systems.

   
# Developer Member

- Waritthon Kongnoo
- Kraiwich Vichakhot
- Chayanin Napia
