// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from imu_custom_msg:srv/GetStatus.idl
// generated code does not contain a copyright notice

#ifndef IMU_CUSTOM_MSG__SRV__DETAIL__GET_STATUS__BUILDER_HPP_
#define IMU_CUSTOM_MSG__SRV__DETAIL__GET_STATUS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "imu_custom_msg/srv/detail/get_status__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace imu_custom_msg
{

namespace srv
{


}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::imu_custom_msg::srv::GetStatus_Request>()
{
  return ::imu_custom_msg::srv::GetStatus_Request(rosidl_runtime_cpp::MessageInitialization::ZERO);
}

}  // namespace imu_custom_msg


namespace imu_custom_msg
{

namespace srv
{

namespace builder
{

class Init_GetStatus_Response_status
{
public:
  Init_GetStatus_Response_status()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::imu_custom_msg::srv::GetStatus_Response status(::imu_custom_msg::srv::GetStatus_Response::_status_type arg)
  {
    msg_.status = std::move(arg);
    return std::move(msg_);
  }

private:
  ::imu_custom_msg::srv::GetStatus_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::imu_custom_msg::srv::GetStatus_Response>()
{
  return imu_custom_msg::srv::builder::Init_GetStatus_Response_status();
}

}  // namespace imu_custom_msg

#endif  // IMU_CUSTOM_MSG__SRV__DETAIL__GET_STATUS__BUILDER_HPP_
