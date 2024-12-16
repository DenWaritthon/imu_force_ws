// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from imu_custom_msg:srv/Calibrate.idl
// generated code does not contain a copyright notice

#ifndef IMU_CUSTOM_MSG__SRV__DETAIL__CALIBRATE__BUILDER_HPP_
#define IMU_CUSTOM_MSG__SRV__DETAIL__CALIBRATE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "imu_custom_msg/srv/detail/calibrate__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace imu_custom_msg
{

namespace srv
{

namespace builder
{

class Init_Calibrate_Request_data
{
public:
  Init_Calibrate_Request_data()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::imu_custom_msg::srv::Calibrate_Request data(::imu_custom_msg::srv::Calibrate_Request::_data_type arg)
  {
    msg_.data = std::move(arg);
    return std::move(msg_);
  }

private:
  ::imu_custom_msg::srv::Calibrate_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::imu_custom_msg::srv::Calibrate_Request>()
{
  return imu_custom_msg::srv::builder::Init_Calibrate_Request_data();
}

}  // namespace imu_custom_msg


namespace imu_custom_msg
{

namespace srv
{

namespace builder
{

class Init_Calibrate_Response_success
{
public:
  Init_Calibrate_Response_success()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::imu_custom_msg::srv::Calibrate_Response success(::imu_custom_msg::srv::Calibrate_Response::_success_type arg)
  {
    msg_.success = std::move(arg);
    return std::move(msg_);
  }

private:
  ::imu_custom_msg::srv::Calibrate_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::imu_custom_msg::srv::Calibrate_Response>()
{
  return imu_custom_msg::srv::builder::Init_Calibrate_Response_success();
}

}  // namespace imu_custom_msg

#endif  // IMU_CUSTOM_MSG__SRV__DETAIL__CALIBRATE__BUILDER_HPP_
