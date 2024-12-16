// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from imu_custom_msg:srv/Calibrate.idl
// generated code does not contain a copyright notice

#ifndef IMU_CUSTOM_MSG__SRV__DETAIL__CALIBRATE__STRUCT_HPP_
#define IMU_CUSTOM_MSG__SRV__DETAIL__CALIBRATE__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'data'
#include "std_msgs/msg/detail/float64_multi_array__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__imu_custom_msg__srv__Calibrate_Request __attribute__((deprecated))
#else
# define DEPRECATED__imu_custom_msg__srv__Calibrate_Request __declspec(deprecated)
#endif

namespace imu_custom_msg
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct Calibrate_Request_
{
  using Type = Calibrate_Request_<ContainerAllocator>;

  explicit Calibrate_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_init;
  }

  explicit Calibrate_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_init;
    (void)_alloc;
  }

  // field types and members
  using _data_type =
    std::vector<std_msgs::msg::Float64MultiArray_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<std_msgs::msg::Float64MultiArray_<ContainerAllocator>>>;
  _data_type data;

  // setters for named parameter idiom
  Type & set__data(
    const std::vector<std_msgs::msg::Float64MultiArray_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<std_msgs::msg::Float64MultiArray_<ContainerAllocator>>> & _arg)
  {
    this->data = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    imu_custom_msg::srv::Calibrate_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const imu_custom_msg::srv::Calibrate_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<imu_custom_msg::srv::Calibrate_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<imu_custom_msg::srv::Calibrate_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      imu_custom_msg::srv::Calibrate_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<imu_custom_msg::srv::Calibrate_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      imu_custom_msg::srv::Calibrate_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<imu_custom_msg::srv::Calibrate_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<imu_custom_msg::srv::Calibrate_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<imu_custom_msg::srv::Calibrate_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__imu_custom_msg__srv__Calibrate_Request
    std::shared_ptr<imu_custom_msg::srv::Calibrate_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__imu_custom_msg__srv__Calibrate_Request
    std::shared_ptr<imu_custom_msg::srv::Calibrate_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Calibrate_Request_ & other) const
  {
    if (this->data != other.data) {
      return false;
    }
    return true;
  }
  bool operator!=(const Calibrate_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Calibrate_Request_

// alias to use template instance with default allocator
using Calibrate_Request =
  imu_custom_msg::srv::Calibrate_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace imu_custom_msg


// Include directives for member types
// Member 'success'
#include "std_msgs/msg/detail/bool__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__imu_custom_msg__srv__Calibrate_Response __attribute__((deprecated))
#else
# define DEPRECATED__imu_custom_msg__srv__Calibrate_Response __declspec(deprecated)
#endif

namespace imu_custom_msg
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct Calibrate_Response_
{
  using Type = Calibrate_Response_<ContainerAllocator>;

  explicit Calibrate_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : success(_init)
  {
    (void)_init;
  }

  explicit Calibrate_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : success(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _success_type =
    std_msgs::msg::Bool_<ContainerAllocator>;
  _success_type success;

  // setters for named parameter idiom
  Type & set__success(
    const std_msgs::msg::Bool_<ContainerAllocator> & _arg)
  {
    this->success = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    imu_custom_msg::srv::Calibrate_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const imu_custom_msg::srv::Calibrate_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<imu_custom_msg::srv::Calibrate_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<imu_custom_msg::srv::Calibrate_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      imu_custom_msg::srv::Calibrate_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<imu_custom_msg::srv::Calibrate_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      imu_custom_msg::srv::Calibrate_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<imu_custom_msg::srv::Calibrate_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<imu_custom_msg::srv::Calibrate_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<imu_custom_msg::srv::Calibrate_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__imu_custom_msg__srv__Calibrate_Response
    std::shared_ptr<imu_custom_msg::srv::Calibrate_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__imu_custom_msg__srv__Calibrate_Response
    std::shared_ptr<imu_custom_msg::srv::Calibrate_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Calibrate_Response_ & other) const
  {
    if (this->success != other.success) {
      return false;
    }
    return true;
  }
  bool operator!=(const Calibrate_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Calibrate_Response_

// alias to use template instance with default allocator
using Calibrate_Response =
  imu_custom_msg::srv::Calibrate_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace imu_custom_msg

namespace imu_custom_msg
{

namespace srv
{

struct Calibrate
{
  using Request = imu_custom_msg::srv::Calibrate_Request;
  using Response = imu_custom_msg::srv::Calibrate_Response;
};

}  // namespace srv

}  // namespace imu_custom_msg

#endif  // IMU_CUSTOM_MSG__SRV__DETAIL__CALIBRATE__STRUCT_HPP_
