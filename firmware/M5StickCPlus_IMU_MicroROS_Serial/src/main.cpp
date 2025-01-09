#include <Arduino.h>
#include <micro_ros_platformio.h>
#include <M5Unified.h>
#include <rcl/rcl.h>
#include <rclc/rclc.h>
#include <rclc/executor.h>
#include <sensor_msgs/msg/imu.h>

#if !defined(MICRO_ROS_TRANSPORT_ARDUINO_SERIAL)
#error This example is only available for Arduino framework with serial transport.
#endif

rcl_publisher_t publisher;
sensor_msgs__msg__Imu mpu6050_msg;

rclc_executor_t executor;
rclc_support_t support;
rcl_allocator_t allocator;
rcl_node_t node;
rcl_timer_t timer;

#define DEG2RAD M_PI / 180.0
#define G2M_S2 9.81

#define RCCHECK(fn)              \
  {                              \
    rcl_ret_t temp_rc = fn;      \
    if ((temp_rc != RCL_RET_OK)) \
    {                            \
      error_loop();              \
    }                            \
  }
#define RCSOFTCHECK(fn)          \
  {                              \
    rcl_ret_t temp_rc = fn;      \
    if ((temp_rc != RCL_RET_OK)) \
    {                            \
    }                            \
  }

static constexpr const uint8_t calib_value = 64;
static constexpr const float coefficient_tbl[3] = {0.5f, (1.0f / 256.0f), (1.0f / 1024.0f)};
static uint8_t calib_countdown = 0;

void updateCalibration(uint32_t c, bool clear = false)
{
  calib_countdown = c;

  if (c == 0)
  {
    clear = true;
  }

  if (clear)
  {
    if (c)
    {
      M5.Imu.setCalibration(calib_value, calib_value, calib_value);
    }
    else
    {
      M5.Imu.setCalibration(0, 0, calib_value);
      M5.Imu.saveOffsetToNVS();
    }
  }
}

void startCalibration(void)
{
  updateCalibration(10, true);
}

void error_loop()
{
  while (1)
  {
    delay(100);
  }
}

void timer_callback(rcl_timer_t *timer, int64_t last_call_time)
{
  RCLC_UNUSED(last_call_time);
  if (timer != NULL)
  {
    static uint32_t frame_count = 0;
    static uint32_t prev_sec = 0;

    auto imu_update = M5.Imu.update();
    if (imu_update)
    {
      auto data = M5.Imu.getImuData();

      mpu6050_msg.linear_acceleration.x = data.accel.x * G2M_S2;
      mpu6050_msg.linear_acceleration.y = data.accel.y * G2M_S2;
      mpu6050_msg.linear_acceleration.z = data.accel.z * G2M_S2;

      mpu6050_msg.angular_velocity.x = data.gyro.x * DEG2RAD;
      mpu6050_msg.angular_velocity.y = data.gyro.y * DEG2RAD;
      mpu6050_msg.angular_velocity.z = data.gyro.z * DEG2RAD;

      ++frame_count;
    }
    else
    {
      M5.update();

      if (M5.BtnA.wasClicked() || M5.BtnPWR.wasClicked() || M5.Touch.getDetail().wasClicked())
      {
        startCalibration();
      }
    }

    int32_t sec = millis() / 1000;
    if (prev_sec != sec)
    {
      prev_sec = sec;
      M5_LOGI("sec:%d  frame:%d", sec, frame_count);
      frame_count = 0;

      if (calib_countdown)
      {
        updateCalibration(calib_countdown - 1);
      }

      if ((sec & 7) == 0)
      {
        vTaskDelay(1);
      }
    }

    RCSOFTCHECK(rcl_publish(&publisher, &mpu6050_msg, NULL));
  }
}

void setup()
{
  Serial.begin(115200);
  set_microros_serial_transports(Serial);

  auto cfg = M5.config();
  M5.begin(cfg);

  const char *name;
  auto imu_type = M5.Imu.getType();
  switch (imu_type)
  {
  case m5::imu_none:
    name = "not found";
    break;
  case m5::imu_sh200q:
    name = "sh200q";
    break;
  case m5::imu_mpu6050:
    name = "mpu6050";
    break;
  case m5::imu_mpu6886:
    name = "mpu6886";
    break;
  case m5::imu_mpu9250:
    name = "mpu9250";
    break;
  case m5::imu_bmi270:
    name = "bmi270";
    break;
  default:
    name = "unknown";
    break;
  };
  M5_LOGI("imu:%s", name);
  M5.Display.printf("imu:%s", name);

  if (imu_type == m5::imu_none)
  {
    for (;;)
    {
      delay(1);
    }
  }

  if (!M5.Imu.loadOffsetFromNVS())
  {
    startCalibration();
  }
  pinMode(10, OUTPUT);
  digitalWrite(10, LOW);
  delay(2000);

  allocator = rcl_get_default_allocator();

  // Set domain ID to 50
  rcl_init_options_t init_options = rcl_get_zero_initialized_init_options();
  RCCHECK(rcl_init_options_init(&init_options, allocator));
  RCCHECK(rcl_init_options_set_domain_id(&init_options, 50));
  RCCHECK(rclc_support_init_with_options(&support, 0, NULL, &init_options, &allocator));
  RCCHECK(rcl_init_options_fini(&init_options));

  RCCHECK(rclc_node_init_default(&node, "M5StickC_IMU_node", "", &support));
  RCCHECK(rclc_publisher_init_default(
      &publisher,
      &node,
      ROSIDL_GET_MSG_TYPE_SUPPORT(sensor_msgs, msg, Imu),
      "IMU_publisher"));

  const unsigned int timer_timeout = 10;
  RCCHECK(rclc_timer_init_default(
      &timer,
      &support,
      RCL_MS_TO_NS(timer_timeout),
      timer_callback));

  RCCHECK(rclc_executor_init(&executor, &support.context, 1, &allocator));
  RCCHECK(rclc_executor_add_timer(&executor, &timer));
}

void loop()
{
  delay(100);
  RCSOFTCHECK(rclc_executor_spin_some(&executor, RCL_MS_TO_NS(100)));
}
