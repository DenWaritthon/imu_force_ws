// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from imu_custom_msg:srv/Calibrate.idl
// generated code does not contain a copyright notice
#include "imu_custom_msg/srv/detail/calibrate__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"

// Include directives for member types
// Member `data`
#include "std_msgs/msg/detail/float64_multi_array__functions.h"

bool
imu_custom_msg__srv__Calibrate_Request__init(imu_custom_msg__srv__Calibrate_Request * msg)
{
  if (!msg) {
    return false;
  }
  // data
  if (!std_msgs__msg__Float64MultiArray__Sequence__init(&msg->data, 0)) {
    imu_custom_msg__srv__Calibrate_Request__fini(msg);
    return false;
  }
  return true;
}

void
imu_custom_msg__srv__Calibrate_Request__fini(imu_custom_msg__srv__Calibrate_Request * msg)
{
  if (!msg) {
    return;
  }
  // data
  std_msgs__msg__Float64MultiArray__Sequence__fini(&msg->data);
}

bool
imu_custom_msg__srv__Calibrate_Request__are_equal(const imu_custom_msg__srv__Calibrate_Request * lhs, const imu_custom_msg__srv__Calibrate_Request * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // data
  if (!std_msgs__msg__Float64MultiArray__Sequence__are_equal(
      &(lhs->data), &(rhs->data)))
  {
    return false;
  }
  return true;
}

bool
imu_custom_msg__srv__Calibrate_Request__copy(
  const imu_custom_msg__srv__Calibrate_Request * input,
  imu_custom_msg__srv__Calibrate_Request * output)
{
  if (!input || !output) {
    return false;
  }
  // data
  if (!std_msgs__msg__Float64MultiArray__Sequence__copy(
      &(input->data), &(output->data)))
  {
    return false;
  }
  return true;
}

imu_custom_msg__srv__Calibrate_Request *
imu_custom_msg__srv__Calibrate_Request__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  imu_custom_msg__srv__Calibrate_Request * msg = (imu_custom_msg__srv__Calibrate_Request *)allocator.allocate(sizeof(imu_custom_msg__srv__Calibrate_Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(imu_custom_msg__srv__Calibrate_Request));
  bool success = imu_custom_msg__srv__Calibrate_Request__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
imu_custom_msg__srv__Calibrate_Request__destroy(imu_custom_msg__srv__Calibrate_Request * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    imu_custom_msg__srv__Calibrate_Request__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
imu_custom_msg__srv__Calibrate_Request__Sequence__init(imu_custom_msg__srv__Calibrate_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  imu_custom_msg__srv__Calibrate_Request * data = NULL;

  if (size) {
    data = (imu_custom_msg__srv__Calibrate_Request *)allocator.zero_allocate(size, sizeof(imu_custom_msg__srv__Calibrate_Request), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = imu_custom_msg__srv__Calibrate_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        imu_custom_msg__srv__Calibrate_Request__fini(&data[i - 1]);
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
imu_custom_msg__srv__Calibrate_Request__Sequence__fini(imu_custom_msg__srv__Calibrate_Request__Sequence * array)
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
      imu_custom_msg__srv__Calibrate_Request__fini(&array->data[i]);
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

imu_custom_msg__srv__Calibrate_Request__Sequence *
imu_custom_msg__srv__Calibrate_Request__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  imu_custom_msg__srv__Calibrate_Request__Sequence * array = (imu_custom_msg__srv__Calibrate_Request__Sequence *)allocator.allocate(sizeof(imu_custom_msg__srv__Calibrate_Request__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = imu_custom_msg__srv__Calibrate_Request__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
imu_custom_msg__srv__Calibrate_Request__Sequence__destroy(imu_custom_msg__srv__Calibrate_Request__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    imu_custom_msg__srv__Calibrate_Request__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
imu_custom_msg__srv__Calibrate_Request__Sequence__are_equal(const imu_custom_msg__srv__Calibrate_Request__Sequence * lhs, const imu_custom_msg__srv__Calibrate_Request__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!imu_custom_msg__srv__Calibrate_Request__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
imu_custom_msg__srv__Calibrate_Request__Sequence__copy(
  const imu_custom_msg__srv__Calibrate_Request__Sequence * input,
  imu_custom_msg__srv__Calibrate_Request__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(imu_custom_msg__srv__Calibrate_Request);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    imu_custom_msg__srv__Calibrate_Request * data =
      (imu_custom_msg__srv__Calibrate_Request *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!imu_custom_msg__srv__Calibrate_Request__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          imu_custom_msg__srv__Calibrate_Request__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!imu_custom_msg__srv__Calibrate_Request__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `success`
#include "std_msgs/msg/detail/bool__functions.h"

bool
imu_custom_msg__srv__Calibrate_Response__init(imu_custom_msg__srv__Calibrate_Response * msg)
{
  if (!msg) {
    return false;
  }
  // success
  if (!std_msgs__msg__Bool__init(&msg->success)) {
    imu_custom_msg__srv__Calibrate_Response__fini(msg);
    return false;
  }
  return true;
}

void
imu_custom_msg__srv__Calibrate_Response__fini(imu_custom_msg__srv__Calibrate_Response * msg)
{
  if (!msg) {
    return;
  }
  // success
  std_msgs__msg__Bool__fini(&msg->success);
}

bool
imu_custom_msg__srv__Calibrate_Response__are_equal(const imu_custom_msg__srv__Calibrate_Response * lhs, const imu_custom_msg__srv__Calibrate_Response * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // success
  if (!std_msgs__msg__Bool__are_equal(
      &(lhs->success), &(rhs->success)))
  {
    return false;
  }
  return true;
}

bool
imu_custom_msg__srv__Calibrate_Response__copy(
  const imu_custom_msg__srv__Calibrate_Response * input,
  imu_custom_msg__srv__Calibrate_Response * output)
{
  if (!input || !output) {
    return false;
  }
  // success
  if (!std_msgs__msg__Bool__copy(
      &(input->success), &(output->success)))
  {
    return false;
  }
  return true;
}

imu_custom_msg__srv__Calibrate_Response *
imu_custom_msg__srv__Calibrate_Response__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  imu_custom_msg__srv__Calibrate_Response * msg = (imu_custom_msg__srv__Calibrate_Response *)allocator.allocate(sizeof(imu_custom_msg__srv__Calibrate_Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(imu_custom_msg__srv__Calibrate_Response));
  bool success = imu_custom_msg__srv__Calibrate_Response__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
imu_custom_msg__srv__Calibrate_Response__destroy(imu_custom_msg__srv__Calibrate_Response * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    imu_custom_msg__srv__Calibrate_Response__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
imu_custom_msg__srv__Calibrate_Response__Sequence__init(imu_custom_msg__srv__Calibrate_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  imu_custom_msg__srv__Calibrate_Response * data = NULL;

  if (size) {
    data = (imu_custom_msg__srv__Calibrate_Response *)allocator.zero_allocate(size, sizeof(imu_custom_msg__srv__Calibrate_Response), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = imu_custom_msg__srv__Calibrate_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        imu_custom_msg__srv__Calibrate_Response__fini(&data[i - 1]);
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
imu_custom_msg__srv__Calibrate_Response__Sequence__fini(imu_custom_msg__srv__Calibrate_Response__Sequence * array)
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
      imu_custom_msg__srv__Calibrate_Response__fini(&array->data[i]);
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

imu_custom_msg__srv__Calibrate_Response__Sequence *
imu_custom_msg__srv__Calibrate_Response__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  imu_custom_msg__srv__Calibrate_Response__Sequence * array = (imu_custom_msg__srv__Calibrate_Response__Sequence *)allocator.allocate(sizeof(imu_custom_msg__srv__Calibrate_Response__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = imu_custom_msg__srv__Calibrate_Response__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
imu_custom_msg__srv__Calibrate_Response__Sequence__destroy(imu_custom_msg__srv__Calibrate_Response__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    imu_custom_msg__srv__Calibrate_Response__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
imu_custom_msg__srv__Calibrate_Response__Sequence__are_equal(const imu_custom_msg__srv__Calibrate_Response__Sequence * lhs, const imu_custom_msg__srv__Calibrate_Response__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!imu_custom_msg__srv__Calibrate_Response__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
imu_custom_msg__srv__Calibrate_Response__Sequence__copy(
  const imu_custom_msg__srv__Calibrate_Response__Sequence * input,
  imu_custom_msg__srv__Calibrate_Response__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(imu_custom_msg__srv__Calibrate_Response);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    imu_custom_msg__srv__Calibrate_Response * data =
      (imu_custom_msg__srv__Calibrate_Response *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!imu_custom_msg__srv__Calibrate_Response__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          imu_custom_msg__srv__Calibrate_Response__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!imu_custom_msg__srv__Calibrate_Response__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
