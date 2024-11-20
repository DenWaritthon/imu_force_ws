// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from imu_custom_msg:srv/GetStatus.idl
// generated code does not contain a copyright notice
#include "imu_custom_msg/srv/detail/get_status__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"

bool
imu_custom_msg__srv__GetStatus_Request__init(imu_custom_msg__srv__GetStatus_Request * msg)
{
  if (!msg) {
    return false;
  }
  // structure_needs_at_least_one_member
  return true;
}

void
imu_custom_msg__srv__GetStatus_Request__fini(imu_custom_msg__srv__GetStatus_Request * msg)
{
  if (!msg) {
    return;
  }
  // structure_needs_at_least_one_member
}

bool
imu_custom_msg__srv__GetStatus_Request__are_equal(const imu_custom_msg__srv__GetStatus_Request * lhs, const imu_custom_msg__srv__GetStatus_Request * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // structure_needs_at_least_one_member
  if (lhs->structure_needs_at_least_one_member != rhs->structure_needs_at_least_one_member) {
    return false;
  }
  return true;
}

bool
imu_custom_msg__srv__GetStatus_Request__copy(
  const imu_custom_msg__srv__GetStatus_Request * input,
  imu_custom_msg__srv__GetStatus_Request * output)
{
  if (!input || !output) {
    return false;
  }
  // structure_needs_at_least_one_member
  output->structure_needs_at_least_one_member = input->structure_needs_at_least_one_member;
  return true;
}

imu_custom_msg__srv__GetStatus_Request *
imu_custom_msg__srv__GetStatus_Request__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  imu_custom_msg__srv__GetStatus_Request * msg = (imu_custom_msg__srv__GetStatus_Request *)allocator.allocate(sizeof(imu_custom_msg__srv__GetStatus_Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(imu_custom_msg__srv__GetStatus_Request));
  bool success = imu_custom_msg__srv__GetStatus_Request__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
imu_custom_msg__srv__GetStatus_Request__destroy(imu_custom_msg__srv__GetStatus_Request * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    imu_custom_msg__srv__GetStatus_Request__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
imu_custom_msg__srv__GetStatus_Request__Sequence__init(imu_custom_msg__srv__GetStatus_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  imu_custom_msg__srv__GetStatus_Request * data = NULL;

  if (size) {
    data = (imu_custom_msg__srv__GetStatus_Request *)allocator.zero_allocate(size, sizeof(imu_custom_msg__srv__GetStatus_Request), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = imu_custom_msg__srv__GetStatus_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        imu_custom_msg__srv__GetStatus_Request__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
imu_custom_msg__srv__GetStatus_Request__Sequence__fini(imu_custom_msg__srv__GetStatus_Request__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      imu_custom_msg__srv__GetStatus_Request__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

imu_custom_msg__srv__GetStatus_Request__Sequence *
imu_custom_msg__srv__GetStatus_Request__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  imu_custom_msg__srv__GetStatus_Request__Sequence * array = (imu_custom_msg__srv__GetStatus_Request__Sequence *)allocator.allocate(sizeof(imu_custom_msg__srv__GetStatus_Request__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = imu_custom_msg__srv__GetStatus_Request__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
imu_custom_msg__srv__GetStatus_Request__Sequence__destroy(imu_custom_msg__srv__GetStatus_Request__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    imu_custom_msg__srv__GetStatus_Request__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
imu_custom_msg__srv__GetStatus_Request__Sequence__are_equal(const imu_custom_msg__srv__GetStatus_Request__Sequence * lhs, const imu_custom_msg__srv__GetStatus_Request__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!imu_custom_msg__srv__GetStatus_Request__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
imu_custom_msg__srv__GetStatus_Request__Sequence__copy(
  const imu_custom_msg__srv__GetStatus_Request__Sequence * input,
  imu_custom_msg__srv__GetStatus_Request__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(imu_custom_msg__srv__GetStatus_Request);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    imu_custom_msg__srv__GetStatus_Request * data =
      (imu_custom_msg__srv__GetStatus_Request *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!imu_custom_msg__srv__GetStatus_Request__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          imu_custom_msg__srv__GetStatus_Request__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!imu_custom_msg__srv__GetStatus_Request__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `status`
#include "std_msgs/msg/detail/bool__functions.h"

bool
imu_custom_msg__srv__GetStatus_Response__init(imu_custom_msg__srv__GetStatus_Response * msg)
{
  if (!msg) {
    return false;
  }
  // status
  if (!std_msgs__msg__Bool__init(&msg->status)) {
    imu_custom_msg__srv__GetStatus_Response__fini(msg);
    return false;
  }
  return true;
}

void
imu_custom_msg__srv__GetStatus_Response__fini(imu_custom_msg__srv__GetStatus_Response * msg)
{
  if (!msg) {
    return;
  }
  // status
  std_msgs__msg__Bool__fini(&msg->status);
}

bool
imu_custom_msg__srv__GetStatus_Response__are_equal(const imu_custom_msg__srv__GetStatus_Response * lhs, const imu_custom_msg__srv__GetStatus_Response * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // status
  if (!std_msgs__msg__Bool__are_equal(
      &(lhs->status), &(rhs->status)))
  {
    return false;
  }
  return true;
}

bool
imu_custom_msg__srv__GetStatus_Response__copy(
  const imu_custom_msg__srv__GetStatus_Response * input,
  imu_custom_msg__srv__GetStatus_Response * output)
{
  if (!input || !output) {
    return false;
  }
  // status
  if (!std_msgs__msg__Bool__copy(
      &(input->status), &(output->status)))
  {
    return false;
  }
  return true;
}

imu_custom_msg__srv__GetStatus_Response *
imu_custom_msg__srv__GetStatus_Response__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  imu_custom_msg__srv__GetStatus_Response * msg = (imu_custom_msg__srv__GetStatus_Response *)allocator.allocate(sizeof(imu_custom_msg__srv__GetStatus_Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(imu_custom_msg__srv__GetStatus_Response));
  bool success = imu_custom_msg__srv__GetStatus_Response__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
imu_custom_msg__srv__GetStatus_Response__destroy(imu_custom_msg__srv__GetStatus_Response * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    imu_custom_msg__srv__GetStatus_Response__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
imu_custom_msg__srv__GetStatus_Response__Sequence__init(imu_custom_msg__srv__GetStatus_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  imu_custom_msg__srv__GetStatus_Response * data = NULL;

  if (size) {
    data = (imu_custom_msg__srv__GetStatus_Response *)allocator.zero_allocate(size, sizeof(imu_custom_msg__srv__GetStatus_Response), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = imu_custom_msg__srv__GetStatus_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        imu_custom_msg__srv__GetStatus_Response__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
imu_custom_msg__srv__GetStatus_Response__Sequence__fini(imu_custom_msg__srv__GetStatus_Response__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      imu_custom_msg__srv__GetStatus_Response__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

imu_custom_msg__srv__GetStatus_Response__Sequence *
imu_custom_msg__srv__GetStatus_Response__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  imu_custom_msg__srv__GetStatus_Response__Sequence * array = (imu_custom_msg__srv__GetStatus_Response__Sequence *)allocator.allocate(sizeof(imu_custom_msg__srv__GetStatus_Response__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = imu_custom_msg__srv__GetStatus_Response__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
imu_custom_msg__srv__GetStatus_Response__Sequence__destroy(imu_custom_msg__srv__GetStatus_Response__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    imu_custom_msg__srv__GetStatus_Response__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
imu_custom_msg__srv__GetStatus_Response__Sequence__are_equal(const imu_custom_msg__srv__GetStatus_Response__Sequence * lhs, const imu_custom_msg__srv__GetStatus_Response__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!imu_custom_msg__srv__GetStatus_Response__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
imu_custom_msg__srv__GetStatus_Response__Sequence__copy(
  const imu_custom_msg__srv__GetStatus_Response__Sequence * input,
  imu_custom_msg__srv__GetStatus_Response__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(imu_custom_msg__srv__GetStatus_Response);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    imu_custom_msg__srv__GetStatus_Response * data =
      (imu_custom_msg__srv__GetStatus_Response *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!imu_custom_msg__srv__GetStatus_Response__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          imu_custom_msg__srv__GetStatus_Response__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!imu_custom_msg__srv__GetStatus_Response__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
