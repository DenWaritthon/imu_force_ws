// generated from rosidl_typesupport_c/resource/idl__type_support.cpp.em
// with input from imu_custom_msg:srv/GetStatus.idl
// generated code does not contain a copyright notice

#include "cstddef"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "imu_custom_msg/srv/detail/get_status__struct.h"
#include "imu_custom_msg/srv/detail/get_status__type_support.h"
#include "rosidl_typesupport_c/identifier.h"
#include "rosidl_typesupport_c/message_type_support_dispatch.h"
#include "rosidl_typesupport_c/type_support_map.h"
#include "rosidl_typesupport_c/visibility_control.h"
#include "rosidl_typesupport_interface/macros.h"

namespace imu_custom_msg
{

namespace srv
{

namespace rosidl_typesupport_c
{

typedef struct _GetStatus_Request_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _GetStatus_Request_type_support_ids_t;

static const _GetStatus_Request_type_support_ids_t _GetStatus_Request_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _GetStatus_Request_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _GetStatus_Request_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _GetStatus_Request_type_support_symbol_names_t _GetStatus_Request_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, imu_custom_msg, srv, GetStatus_Request)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, imu_custom_msg, srv, GetStatus_Request)),
  }
};

typedef struct _GetStatus_Request_type_support_data_t
{
  void * data[2];
} _GetStatus_Request_type_support_data_t;

static _GetStatus_Request_type_support_data_t _GetStatus_Request_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _GetStatus_Request_message_typesupport_map = {
  2,
  "imu_custom_msg",
  &_GetStatus_Request_message_typesupport_ids.typesupport_identifier[0],
  &_GetStatus_Request_message_typesupport_symbol_names.symbol_name[0],
  &_GetStatus_Request_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t GetStatus_Request_message_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_GetStatus_Request_message_typesupport_map),
  rosidl_typesupport_c__get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_c

}  // namespace srv

}  // namespace imu_custom_msg

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_c, imu_custom_msg, srv, GetStatus_Request)() {
  return &::imu_custom_msg::srv::rosidl_typesupport_c::GetStatus_Request_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "imu_custom_msg/srv/detail/get_status__struct.h"
// already included above
// #include "imu_custom_msg/srv/detail/get_status__type_support.h"
// already included above
// #include "rosidl_typesupport_c/identifier.h"
// already included above
// #include "rosidl_typesupport_c/message_type_support_dispatch.h"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_c/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace imu_custom_msg
{

namespace srv
{

namespace rosidl_typesupport_c
{

typedef struct _GetStatus_Response_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _GetStatus_Response_type_support_ids_t;

static const _GetStatus_Response_type_support_ids_t _GetStatus_Response_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _GetStatus_Response_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _GetStatus_Response_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _GetStatus_Response_type_support_symbol_names_t _GetStatus_Response_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, imu_custom_msg, srv, GetStatus_Response)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, imu_custom_msg, srv, GetStatus_Response)),
  }
};

typedef struct _GetStatus_Response_type_support_data_t
{
  void * data[2];
} _GetStatus_Response_type_support_data_t;

static _GetStatus_Response_type_support_data_t _GetStatus_Response_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _GetStatus_Response_message_typesupport_map = {
  2,
  "imu_custom_msg",
  &_GetStatus_Response_message_typesupport_ids.typesupport_identifier[0],
  &_GetStatus_Response_message_typesupport_symbol_names.symbol_name[0],
  &_GetStatus_Response_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t GetStatus_Response_message_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_GetStatus_Response_message_typesupport_map),
  rosidl_typesupport_c__get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_c

}  // namespace srv

}  // namespace imu_custom_msg

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_c, imu_custom_msg, srv, GetStatus_Response)() {
  return &::imu_custom_msg::srv::rosidl_typesupport_c::GetStatus_Response_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "imu_custom_msg/srv/detail/get_status__type_support.h"
// already included above
// #include "rosidl_typesupport_c/identifier.h"
#include "rosidl_typesupport_c/service_type_support_dispatch.h"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace imu_custom_msg
{

namespace srv
{

namespace rosidl_typesupport_c
{

typedef struct _GetStatus_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _GetStatus_type_support_ids_t;

static const _GetStatus_type_support_ids_t _GetStatus_service_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _GetStatus_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _GetStatus_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _GetStatus_type_support_symbol_names_t _GetStatus_service_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, imu_custom_msg, srv, GetStatus)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, imu_custom_msg, srv, GetStatus)),
  }
};

typedef struct _GetStatus_type_support_data_t
{
  void * data[2];
} _GetStatus_type_support_data_t;

static _GetStatus_type_support_data_t _GetStatus_service_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _GetStatus_service_typesupport_map = {
  2,
  "imu_custom_msg",
  &_GetStatus_service_typesupport_ids.typesupport_identifier[0],
  &_GetStatus_service_typesupport_symbol_names.symbol_name[0],
  &_GetStatus_service_typesupport_data.data[0],
};

static const rosidl_service_type_support_t GetStatus_service_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_GetStatus_service_typesupport_map),
  rosidl_typesupport_c__get_service_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_c

}  // namespace srv

}  // namespace imu_custom_msg

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_c, imu_custom_msg, srv, GetStatus)() {
  return &::imu_custom_msg::srv::rosidl_typesupport_c::GetStatus_service_type_support_handle;
}

#ifdef __cplusplus
}
#endif
