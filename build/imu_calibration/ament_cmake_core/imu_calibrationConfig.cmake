# generated from ament/cmake/core/templates/nameConfig.cmake.in

# prevent multiple inclusion
if(_imu_calibration_CONFIG_INCLUDED)
  # ensure to keep the found flag the same
  if(NOT DEFINED imu_calibration_FOUND)
    # explicitly set it to FALSE, otherwise CMake will set it to TRUE
    set(imu_calibration_FOUND FALSE)
  elseif(NOT imu_calibration_FOUND)
    # use separate condition to avoid uninitialized variable warning
    set(imu_calibration_FOUND FALSE)
  endif()
  return()
endif()
set(_imu_calibration_CONFIG_INCLUDED TRUE)

# output package information
if(NOT imu_calibration_FIND_QUIETLY)
  message(STATUS "Found imu_calibration: 0.0.0 (${imu_calibration_DIR})")
endif()

# warn when using a deprecated package
if(NOT "" STREQUAL "")
  set(_msg "Package 'imu_calibration' is deprecated")
  # append custom deprecation text if available
  if(NOT "" STREQUAL "TRUE")
    set(_msg "${_msg} ()")
  endif()
  # optionally quiet the deprecation message
  if(NOT ${imu_calibration_DEPRECATED_QUIET})
    message(DEPRECATION "${_msg}")
  endif()
endif()

# flag package as ament-based to distinguish it after being find_package()-ed
set(imu_calibration_FOUND_AMENT_PACKAGE TRUE)

# include all config extra files
set(_extras "")
foreach(_extra ${_extras})
  include("${imu_calibration_DIR}/${_extra}")
endforeach()
