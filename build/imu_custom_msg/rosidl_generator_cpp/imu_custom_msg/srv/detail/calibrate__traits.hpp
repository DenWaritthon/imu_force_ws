// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from imu_custom_msg:srv/Calibrate.idl
// generated code does not contain a copyright notice

#ifndef IMU_CUSTOM_MSG__SRV__DETAIL__CALIBRATE__TRAITS_HPP_
#define IMU_CUSTOM_MSG__SRV__DETAIL__CALIBRATE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "imu_custom_msg/srv/detail/calibrate__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'data'
#include "std_msgs/msg/detail/float64_multi_array__traits.hpp"

namespace imu_custom_msg
{

namespace srv
{

inline void to_flow_style_yaml(
  const Calibrate_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: data
  {
    if (msg.data.size() == 0) {
      out << "data: []";
    } else {
      out << "data: [";
      size_t pending_items = msg.data.size();
      for (auto item : msg.data) {
        to_flow_style_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Calibrate_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: data
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.data.size() == 0) {
      out << "data: []\n";
    } else {
      out << "data:\n";
      for (auto item : msg.data) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Calibrate_Request & msg, bool use_flow_style = false)
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
  const imu_custom_msg::srv::Calibrate_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  imu_custom_msg::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use imu_custom_msg::srv::to_yaml() instead")]]
inline std::string to_yaml(const imu_custom_msg::srv::Calibrate_Request & msg)
{
  return imu_custom_msg::srv::to_yaml(msg);
}

template<>
inline const char * data_type<imu_custom_msg::srv::Calibrate_Request>()
{
  return "imu_custom_msg::srv::Calibrate_Request";
}

template<>
inline const char * name<imu_custom_msg::srv::Calibrate_Request>()
{
  return "imu_custom_msg/srv/Calibrate_Request";
}

template<>
struct has_fixed_size<imu_custom_msg::srv::Calibrate_Request>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<imu_custom_msg::srv::Calibrate_Request>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<imu_custom_msg::srv::Calibrate_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'success'
#include "std_msgs/msg/detail/bool__traits.hpp"

namespace imu_custom_msg
{

namespace srv
{

inline void to_flow_style_yaml(
  const Calibrate_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: success
  {
    out << "success: ";
    to_flow_style_yaml(msg.success, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Calibrate_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: success
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "success:\n";
    to_block_style_yaml(msg.success, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Calibrate_Response & msg, bool use_flow_style = false)
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
  const imu_custom_msg::srv::Calibrate_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  imu_custom_msg::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use imu_custom_msg::srv::to_yaml() instead")]]
inline std::string to_yaml(const imu_custom_msg::srv::Calibrate_Response & msg)
{
  return imu_custom_msg::srv::to_yaml(msg);
}

template<>
inline const char * data_type<imu_custom_msg::srv::Calibrate_Response>()
{
  return "imu_custom_msg::srv::Calibrate_Response";
}

template<>
inline const char * name<imu_custom_msg::srv::Calibrate_Response>()
{
  return "imu_custom_msg/srv/Calibrate_Response";
}

template<>
struct has_fixed_size<imu_custom_msg::srv::Calibrate_Response>
  : std::integral_constant<bool, has_fixed_size<std_msgs::msg::Bool>::value> {};

template<>
struct has_bounded_size<imu_custom_msg::srv::Calibrate_Response>
  : std::integral_constant<bool, has_bounded_size<std_msgs::msg::Bool>::value> {};

template<>
struct is_message<imu_custom_msg::srv::Calibrate_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<imu_custom_msg::srv::Calibrate>()
{
  return "imu_custom_msg::srv::Calibrate";
}

template<>
inline const char * name<imu_custom_msg::srv::Calibrate>()
{
  return "imu_custom_msg/srv/Calibrate";
}

template<>
struct has_fixed_size<imu_custom_msg::srv::Calibrate>
  : std::integral_constant<
    bool,
    has_fixed_size<imu_custom_msg::srv::Calibrate_Request>::value &&
    has_fixed_size<imu_custom_msg::srv::Calibrate_Response>::value
  >
{
};

template<>
struct has_bounded_size<imu_custom_msg::srv::Calibrate>
  : std::integral_constant<
    bool,
    has_bounded_size<imu_custom_msg::srv::Calibrate_Request>::value &&
    has_bounded_size<imu_custom_msg::srv::Calibrate_Response>::value
  >
{
};

template<>
struct is_service<imu_custom_msg::srv::Calibrate>
  : std::true_type
{
};

template<>
struct is_service_request<imu_custom_msg::srv::Calibrate_Request>
  : std::true_type
{
};

template<>
struct is_service_response<imu_custom_msg::srv::Calibrate_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // IMU_CUSTOM_MSG__SRV__DETAIL__CALIBRATE__TRAITS_HPP_
