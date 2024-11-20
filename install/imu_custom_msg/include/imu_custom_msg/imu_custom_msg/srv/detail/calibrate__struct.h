// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from imu_custom_msg:srv/Calibrate.idl
// generated code does not contain a copyright notice

#ifndef IMU_CUSTOM_MSG__SRV__DETAIL__CALIBRATE__STRUCT_H_
#define IMU_CUSTOM_MSG__SRV__DETAIL__CALIBRATE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'data'
#include "std_msgs/msg/detail/float64_multi_array__struct.h"

/// Struct defined in srv/Calibrate in the package imu_custom_msg.
typedef struct imu_custom_msg__srv__Calibrate_Request
{
  std_msgs__msg__Float64MultiArray__Sequence data;
} imu_custom_msg__srv__Calibrate_Request;

// Struct for a sequence of imu_custom_msg__srv__Calibrate_Request.
typedef struct imu_custom_msg__srv__Calibrate_Request__Sequence
{
  imu_custom_msg__srv__Calibrate_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} imu_custom_msg__srv__Calibrate_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'success'
#include "std_msgs/msg/detail/bool__struct.h"

/// Struct defined in srv/Calibrate in the package imu_custom_msg.
typedef struct imu_custom_msg__srv__Calibrate_Response
{
  /// Response
  std_msgs__msg__Bool success;
} imu_custom_msg__srv__Calibrate_Response;

// Struct for a sequence of imu_custom_msg__srv__Calibrate_Response.
typedef struct imu_custom_msg__srv__Calibrate_Response__Sequence
{
  imu_custom_msg__srv__Calibrate_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} imu_custom_msg__srv__Calibrate_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // IMU_CUSTOM_MSG__SRV__DETAIL__CALIBRATE__STRUCT_H_
