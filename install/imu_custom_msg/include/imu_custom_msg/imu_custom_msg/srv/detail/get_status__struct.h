// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from imu_custom_msg:srv/GetStatus.idl
// generated code does not contain a copyright notice

#ifndef IMU_CUSTOM_MSG__SRV__DETAIL__GET_STATUS__STRUCT_H_
#define IMU_CUSTOM_MSG__SRV__DETAIL__GET_STATUS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in srv/GetStatus in the package imu_custom_msg.
typedef struct imu_custom_msg__srv__GetStatus_Request
{
  uint8_t structure_needs_at_least_one_member;
} imu_custom_msg__srv__GetStatus_Request;

// Struct for a sequence of imu_custom_msg__srv__GetStatus_Request.
typedef struct imu_custom_msg__srv__GetStatus_Request__Sequence
{
  imu_custom_msg__srv__GetStatus_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} imu_custom_msg__srv__GetStatus_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'status'
#include "std_msgs/msg/detail/bool__struct.h"

/// Struct defined in srv/GetStatus in the package imu_custom_msg.
typedef struct imu_custom_msg__srv__GetStatus_Response
{
  std_msgs__msg__Bool status;
} imu_custom_msg__srv__GetStatus_Response;

// Struct for a sequence of imu_custom_msg__srv__GetStatus_Response.
typedef struct imu_custom_msg__srv__GetStatus_Response__Sequence
{
  imu_custom_msg__srv__GetStatus_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} imu_custom_msg__srv__GetStatus_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // IMU_CUSTOM_MSG__SRV__DETAIL__GET_STATUS__STRUCT_H_
