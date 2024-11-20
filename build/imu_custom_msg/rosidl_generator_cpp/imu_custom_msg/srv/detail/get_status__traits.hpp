// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from imu_custom_msg:srv/GetStatus.idl
// generated code does not contain a copyright notice

#ifndef IMU_CUSTOM_MSG__SRV__DETAIL__GET_STATUS__TRAITS_HPP_
#define IMU_CUSTOM_MSG__SRV__DETAIL__GET_STATUS__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "imu_custom_msg/srv/detail/get_status__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace imu_custom_msg
{

namespace srv
{

inline void to_flow_style_yaml(
  const GetStatus_Request & msg,
  std::ostream & out)
{
  (void)msg;
  out << "null";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const GetStatus_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  (void)msg;
  (void)indentation;
  out << "null\n";
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const GetStatus_Request & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace imu_custom_msg

namespace rosidl_generator_traits
{

[[deprecated("use imu_custom_msg::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const imu_custom_msg::srv::GetStatus_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  imu_custom_msg::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use imu_custom_msg::srv::to_yaml() instead")]]
inline std::string to_yaml(const imu_custom_msg::srv::GetStatus_Request & msg)
{
  return imu_custom_msg::srv::to_yaml(msg);
}

template<>
inline const char * data_type<imu_custom_msg::srv::GetStatus_Request>()
{
  return "imu_custom_msg::srv::GetStatus_Request";
}

template<>
inline const char * name<imu_custom_msg::srv::GetStatus_Request>()
{
  return "imu_custom_msg/srv/GetStatus_Request";
}

template<>
struct has_fixed_size<imu_custom_msg::srv::GetStatus_Request>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<imu_custom_msg::srv::GetStatus_Request>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<imu_custom_msg::srv::GetStatus_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'status'
#include "std_msgs/msg/detail/bool__traits.hpp"

namespace imu_custom_msg
{

namespace srv
{

inline void to_flow_style_yaml(
  const GetStatus_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: status
  {
    out << "status: ";
    to_flow_style_yaml(msg.status, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const GetStatus_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: status
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "status:\n";
    to_block_style_yaml(msg.status, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const GetStatus_Response & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace imu_custom_msg

namespace rosidl_generator_traits
{

[[deprecated("use imu_custom_msg::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const imu_custom_msg::srv::GetStatus_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  imu_custom_msg::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use imu_custom_msg::srv::to_yaml() instead")]]
inline std::string to_yaml(const imu_custom_msg::srv::GetStatus_Response & msg)
{
  return imu_custom_msg::srv::to_yaml(msg);
}

template<>
inline const char * data_type<imu_custom_msg::srv::GetStatus_Response>()
{
  return "imu_custom_msg::srv::GetStatus_Response";
}

template<>
inline const char * name<imu_custom_msg::srv::GetStatus_Response>()
{
  return "imu_custom_msg/srv/GetStatus_Response";
}

template<>
struct has_fixed_size<imu_custom_msg::srv::GetStatus_Response>
  : std::integral_constant<bool, has_fixed_size<std_msgs::msg::Bool>::value> {};

template<>
struct has_bounded_size<imu_custom_msg::srv::GetStatus_Response>
  : std::integral_constant<bool, has_bounded_size<std_msgs::msg::Bool>::value> {};

template<>
struct is_message<imu_custom_msg::srv::GetStatus_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<imu_custom_msg::srv::GetStatus>()
{
  return "imu_custom_msg::srv::GetStatus";
}

template<>
inline const char * name<imu_custom_msg::srv::GetStatus>()
{
  return "imu_custom_msg/srv/GetStatus";
}

template<>
struct has_fixed_size<imu_custom_msg::srv::GetStatus>
  : std::integral_constant<
    bool,
    has_fixed_size<imu_custom_msg::srv::GetStatus_Request>::value &&
    has_fixed_size<imu_custom_msg::srv::GetStatus_Response>::value
  >
{
};

template<>
struct has_bounded_size<imu_custom_msg::srv::GetStatus>
  : std::integral_constant<
    bool,
    has_bounded_size<imu_custom_msg::srv::GetStatus_Request>::value &&
    has_bounded_size<imu_custom_msg::srv::GetStatus_Response>::value
  >
{
};

template<>
struct is_service<imu_custom_msg::srv::GetStatus>
  : std::true_type
{
};

template<>
struct is_service_request<imu_custom_msg::srv::GetStatus_Request>
  : std::true_type
{
};

template<>
struct is_service_response<imu_custom_msg::srv::GetStatus_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // IMU_CUSTOM_MSG__SRV__DETAIL__GET_STATUS__TRAITS_HPP_
