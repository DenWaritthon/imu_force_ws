# Prototype of the system simulating the force acting on the object, referring to the force from the IMU Sensor value.

This repository focuses on developing firmware and implementing signal-processing filters for the STM32 G474RE microcontroller. The goal is to accurately measure and analyze three-axis inertial data (X, Y, and Z) to support simulation in gazebo.

# Table of Contents


# Objective
- To create a simulation system for the movement of objects when a force is applied to the Gazebo by using the actual force obtained by converting the value from the IMU Sensor into the force that will be applied to the object on the Gazebo.

# Scope
- **Actual Object**
  - The actual object is the M5StickC Plus microcontroller.
- **Simulation System**
  -  The system is constructed on Gazebo with the object model being a  Square shape of the same size as the actual object.
  -  The force applied to the object in the simulation system is only applied at the center of the object.
  -  The force applied will only be in the x and y axes.
- **Working environment**
  - The operation will be performed under the A4 size test area with the Web camera set up 0.3 m above the paper.
  
  `ใส่รูปสภาพแวดล้อม`

# User installation guide 

## Prerequisites

Ensure you have the following dependencies installed

**Hardware Require**
- `M5 StickC Plus`
- `Web camera`

**Middle ware**
- `ROS2 Humble`
- `MicroRos`

**Applications**
- `Gazabo` 
- `Platfrom IO`

## Install project workspace
Clone this workspace

```bash
git clone https://github.com/DenWaritthon/imu_force_ws.git -b main
```

# Methodology

## IMU filter : IIR filter 
It is a filter used to adjust the acceleration value obtained from the IMU Sensor to be more stable by taking the previous value into consideration and adjusting the properties according to the specified gain value which will work according to the equation.
```math
a_{out} = a_k a_{in} + (1-a_k)a_{out}[n-1]
```

Given
- $a_{out}$ is the acceleration out put from IIR filter
- $a_{in}$ is the acceleration input put from IMU sensor
- $a_k$ is gain value

## Newton's equations

Convert the velocity obtained from the IMU into a force to apply to the object in Guzabo using Newton's equations.
```math
\sum F = ma
```

Given
- $F$ is the force to be obtained
- $m$ is the weight of the actual object, which weighs 0.02 kg.
- $a$ is the acceleration measured by the IMU

## Aruco


# System architecture 

`ใส่รูป System architecture`

System separate the work into sub-node that work differently 8 node consist of

- **M5StickC_IMU_node (Micro Ros)**
  
- **imu_calibration_node** is a Node that have input value from IMU_node (Micro ROS) to Calibrate value of the IMU to make it more accurate.
  
- **imu_filter_node** is a Node that have a input value from M5StickC_IMU_node (Micro Ros) after Calibate the value then the accelerate value by Pub Topic : /acceleration to Node Force_control_node.
  
- **aruco_detect_node**
  
- **aruco_controller**
  
- **Force_control_node** is a Node that get input of accelerate value from Node : imu_filter_node to calculate in Newton's equations and get input of difference between actual position and position in Gazebo from Node : aruco_controller to control Object by Servive :/apply_link_wrench of Gazebo.
  
- **Gazebo_node**
  
- **model_position_node** is a Node that have input value from Node : Gazebo_node to calculate model position.
  
# User guide

After Clone workspace then Build and source

```bash
cd imu_force_ws/
colcon build
source install/setup.bash
```

## How to use simulation

Before starting the operation after setting up the environment.

- **Run caliblate IMU**
``` bash
ros2 run
```

Run the simulation in ROS2.

- **Run Gazebo simulation**
``` bash
ros2 launch imu_force_gazebo 
```

- **Run IMU filter**
``` bash
ros2 run
```

- **Run Aruco**
``` bash
ros2 run
```

- **Run Force controller**
``` bash
ros2 run
```

Check the position of objects in the Gazebo and the real world.

- **In Gazebo**
``` bash
ros2 run
```

- **In real world**
``` bash
ros2 run
```

# Demos and Result


# Conclusion


# Future plan
- Explore advanced filtering algorithms (e.g., Kalman filters) for improved accuracy and robustness.
- Expand documentation and provide example code to facilitate integration into larger robotics or control systems.

# Developer Member

- Waritthon Kongnoo
- Kraiwich Vichakhot
- Chayanin Napia
