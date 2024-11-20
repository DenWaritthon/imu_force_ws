// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from imu_custom_msg:srv/Calibrate.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "imu_custom_msg/srv/detail/calibrate__rosidl_typesupport_introspection_c.h"
#include "imu_custom_msg/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "imu_custom_msg/srv/detail/calibrate__functions.h"
#include "imu_custom_msg/srv/detail/calibrate__struct.h"


// Include directives for member types
// Member `data`
#include "std_msgs/msg/float64_multi_array.h"
// Member `data`
#include "std_msgs/msg/detail/float64_multi_array__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void imu_custom_msg__srv__Calibrate_Request__rosidl_typesupport_introspection_c__Calibrate_Request_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  imu_custom_msg__srv__Calibrate_Request__init(message_memory);
}

void imu_custom_msg__srv__Calibrate_Request__rosidl_typesupport_introspection_c__Calibrate_Request_fini_function(void * message_memory)
{
  imu_custom_msg__srv__Calibrate_Request__fini(message_memory);
}

size_t imu_custom_msg__srv__Calibrate_Request__rosidl_typesupport_introspection_c__size_function__Calibrate_Request__data(
  const void * untyped_member)
{
  const std_msgs__msg__Float64MultiArray__Sequence * member =
    (const std_msgs__msg__Float64MultiArray__Sequence *)(untyped_member);
  return member->size;
}

const void * imu_custom_msg__srv__Calibrate_Request__rosidl_typesupport_introspection_c__get_const_function__Calibrate_Request__data(
  const void * untyped_member, size_t index)
{
  const std_msgs__msg__Float64MultiArray__Sequence * member =
    (const std_msgs__msg__Float64MultiArray__Sequence *)(untyped_member);
  return &member->data[index];
}

void * imu_custom_msg__srv__Calibrate_Request__rosidl_typesupport_introspection_c__get_function__Calibrate_Request__data(
  void * untyped_member, size_t index)
{
  std_msgs__msg__Float64MultiArray__Sequence * member =
    (std_msgs__msg__Float64MultiArray__Sequence *)(untyped_member);
  return &member->data[index];
}

void imu_custom_msg__srv__Calibrate_Request__rosidl_typesupport_introspection_c__fetch_function__Calibrate_Request__data(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const std_msgs__msg__Float64MultiArray * item =
    ((const std_msgs__msg__Float64MultiArray *)
    imu_custom_msg__srv__Calibrate_Request__rosidl_typesupport_introspection_c__get_const_function__Calibrate_Request__data(untyped_member, index));
  std_msgs__msg__Float64MultiArray * value =
    (std_msgs__msg__Float64MultiArray *)(untyped_value);
  *value = *item;
}

void imu_custom_msg__srv__Calibrate_Request__rosidl_typesupport_introspection_c__assign_function__Calibrate_Request__data(
  void * untyped_member, size_t index, const void * untyped_value)
{
  std_msgs__msg__Float64MultiArray * item =
    ((std_msgs__msg__Float64MultiArray *)
    imu_custom_msg__srv__Calibrate_Request__rosidl_typesupport_introspection_c__get_function__Calibrate_Request__data(untyped_member, index));
  const std_msgs__msg__Float64MultiArray * value =
    (const std_msgs__msg__Float64MultiArray *)(untyped_value);
  *item = *value;
}

bool imu_custom_msg__srv__Calibrate_Request__rosidl_typesupport_introspection_c__resize_function__Calibrate_Request__data(
  void * untyped_member, size_t size)
{
  std_msgs__msg__Float64MultiArray__Sequence * member =
    (std_msgs__msg__Float64MultiArray__Sequence *)(untyped_member);
  std_msgs__msg__Float64MultiArray__Sequence__fini(member);
  return std_msgs__msg__Float64MultiArray__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember imu_custom_msg__srv__Calibrate_Request__rosidl_typesupport_introspection_c__Calibrate_Request_message_member_array[1] = {
  {
    "data",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(imu_custom_msg__srv__Calibrate_Request, data),  // bytes offset in struct
    NULL,  // default value
    imu_custom_msg__srv__Calibrate_Request__rosidl_typesupport_introspection_c__size_function__Calibrate_Request__data,  // size() function pointer
    imu_custom_msg__srv__Calibrate_Request__rosidl_typesupport_introspection_c__get_const_function__Calibrate_Request__data,  // get_const(index) function pointer
    imu_custom_msg__srv__Calibrate_Request__rosidl_typesupport_introspection_c__get_function__Calibrate_Request__data,  // get(index) function pointer
    imu_custom_msg__srv__Calibrate_Request__rosidl_typesupport_introspection_c__fetch_function__Calibrate_Request__data,  // fetch(index, &value) function pointer
    imu_custom_msg__srv__Calibrate_Request__rosidl_typesupport_introspection_c__assign_function__Calibrate_Request__data,  // assign(index, value) function pointer
    imu_custom_msg__srv__Calibrate_Request__rosidl_typesupport_introspection_c__resize_function__Calibrate_Request__data  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers imu_custom_msg__srv__Calibrate_Request__rosidl_typesupport_introspection_c__Calibrate_Request_message_members = {
  "imu_custom_msg__srv",  // message namespace
  "Calibrate_Request",  // message name
  1,  // number of fields
  sizeof(imu_custom_msg__srv__Calibrate_Request),
  imu_custom_msg__srv__Calibrate_Request__rosidl_typesupport_introspection_c__Calibrate_Request_message_member_array,  // message members
  imu_custom_msg__srv__Calibrate_Request__rosidl_typesupport_introspection_c__Calibrate_Request_init_function,  // function to initialize message memory (memory has to be allocated)
  imu_custom_msg__srv__Calibrate_Request__rosidl_typesupport_introspection_c__Calibrate_Request_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t imu_custom_msg__srv__Calibrate_Request__rosidl_typesupport_introspection_c__Calibrate_Request_message_type_support_handle = {
  0,
  &imu_custom_msg__srv__Calibrate_Request__rosidl_typesupport_introspection_c__Calibrate_Request_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_imu_custom_msg
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, imu_custom_msg, srv, Calibrate_Request)() {
  imu_custom_msg__srv__Calibrate_Request__rosidl_typesupport_introspection_c__Calibrate_Request_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, std_msgs, msg, Float64MultiArray)();
  if (!imu_custom_msg__srv__Calibrate_Request__rosidl_typesupport_introspection_c__Calibrate_Request_message_type_support_handle.typesupport_identifier) {
    imu_custom_msg__srv__Calibrate_Request__rosidl_typesupport_introspection_c__Calibrate_Request_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &imu_custom_msg__srv__Calibrate_Request__rosidl_typesupport_introspection_c__Calibrate_Request_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "imu_custom_msg/srv/detail/calibrate__rosidl_typesupport_introspection_c.h"
// already included above
// #include "imu_custom_msg/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "imu_custom_msg/srv/detail/calibrate__functions.h"
// already included above
// #include "imu_custom_msg/srv/detail/calibrate__struct.h"


// Include directives for member types
// Member `success`
#include "std_msgs/msg/bool.h"
// Member `success`
#include "std_msgs/msg/detail/bool__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void imu_custom_msg__srv__Calibrate_Response__rosidl_typesupport_introspection_c__Calibrate_Response_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  imu_custom_msg__srv__Calibrate_Response__init(message_memory);
}

void imu_custom_msg__srv__Calibrate_Response__rosidl_typesupport_introspection_c__Calibrate_Response_fini_function(void * message_memory)
{
  imu_custom_msg__srv__Calibrate_Response__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember imu_custom_msg__srv__Calibrate_Response__rosidl_typesupport_introspection_c__Calibrate_Response_message_member_array[1] = {
  {
    "success",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(imu_custom_msg__srv__Calibrate_Response, success),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers imu_custom_msg__srv__Calibrate_Response__rosidl_typesupport_introspection_c__Calibrate_Response_message_members = {
  "imu_custom_msg__srv",  // message namespace
  "Calibrate_Response",  // message name
  1,  // number of fields
  sizeof(imu_custom_msg__srv__Calibrate_Response),
  imu_custom_msg__srv__Calibrate_Response__rosidl_typesupport_introspection_c__Calibrate_Response_message_member_array,  // message members
  imu_custom_msg__srv__Calibrate_Response__rosidl_typesupport_introspection_c__Calibrate_Response_init_function,  // function to initialize message memory (memory has to be allocated)
  imu_custom_msg__srv__Calibrate_Response__rosidl_typesupport_introspection_c__Calibrate_Response_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t imu_custom_msg__srv__Calibrate_Response__rosidl_typesupport_introspection_c__Calibrate_Response_message_type_support_handle = {
  0,
  &imu_custom_msg__srv__Calibrate_Response__rosidl_typesupport_introspection_c__Calibrate_Response_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_imu_custom_msg
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, imu_custom_msg, srv, Calibrate_Response)() {
  imu_custom_msg__srv__Calibrate_Response__rosidl_typesupport_introspection_c__Calibrate_Response_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, std_msgs, msg, Bool)();
  if (!imu_custom_msg__srv__Calibrate_Response__rosidl_typesupport_introspection_c__Calibrate_Response_message_type_support_handle.typesupport_identifier) {
    imu_custom_msg__srv__Calibrate_Response__rosidl_typesupport_introspection_c__Calibrate_Response_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &imu_custom_msg__srv__Calibrate_Response__rosidl_typesupport_introspection_c__Calibrate_Response_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "imu_custom_msg/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "imu_custom_msg/srv/detail/calibrate__rosidl_typesupport_introspection_c.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/service_introspection.h"

// this is intentionally not const to allow initialization later to prevent an initialization race
static rosidl_typesupport_introspection_c__ServiceMembers imu_custom_msg__srv__detail__calibrate__rosidl_typesupport_introspection_c__Calibrate_service_members = {
  "imu_custom_msg__srv",  // service namespace
  "Calibrate",  // service name
  // these two fields are initialized below on the first access
  NULL,  // request message
  // imu_custom_msg__srv__detail__calibrate__rosidl_typesupport_introspection_c__Calibrate_Request_message_type_support_handle,
  NULL  // response message
  // imu_custom_msg__srv__detail__calibrate__rosidl_typesupport_introspection_c__Calibrate_Response_message_type_support_handle
};

static rosidl_service_type_support_t imu_custom_msg__srv__detail__calibrate__rosidl_typesupport_introspection_c__Calibrate_service_type_support_handle = {
  0,
  &imu_custom_msg__srv__detail__calibrate__rosidl_typesupport_introspection_c__Calibrate_service_members,
  get_service_typesupport_handle_function,
};

// Forward declaration of request/response type support functions
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, imu_custom_msg, srv, Calibrate_Request)();

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, imu_custom_msg, srv, Calibrate_Response)();

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_imu_custom_msg
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, imu_custom_msg, srv, Calibrate)() {
  if (!imu_custom_msg__srv__detail__calibrate__rosidl_typesupport_introspection_c__Calibrate_service_type_support_handle.typesupport_identifier) {
    imu_custom_msg__srv__detail__calibrate__rosidl_typesupport_introspection_c__Calibrate_service_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  rosidl_typesupport_introspection_c__ServiceMembers * service_members =
    (rosidl_typesupport_introspection_c__ServiceMembers *)imu_custom_msg__srv__detail__calibrate__rosidl_typesupport_introspection_c__Calibrate_service_type_support_handle.data;

  if (!service_members->request_members_) {
    service_members->request_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, imu_custom_msg, srv, Calibrate_Request)()->data;
  }
  if (!service_members->response_members_) {
    service_members->response_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, imu_custom_msg, srv, Calibrate_Response)()->data;
  }

  return &imu_custom_msg__srv__detail__calibrate__rosidl_typesupport_introspection_c__Calibrate_service_type_support_handle;
}
