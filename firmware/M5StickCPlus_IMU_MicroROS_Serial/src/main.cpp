#include <Arduino.h>
#include <micro_ros_platformio.h>
#include <M5Unified.h>
#include <rcl/rcl.h>
#include <rclc/rclc.h>
#include <rclc/executor.h>

#include <sensor_msgs/msg/imu.h>

#if !defined(MICRO_ROS_TRANSPORT_ARDUINO_SERIAL)
#error This example is only avaliable for Arduino framework with serial transport.
#endif

rcl_publisher_t publisher;
sensor_msgs__msg__Imu mpu6050_msg;

rclc_executor_t executor;
rclc_support_t support;
rcl_allocator_t allocator;
rcl_node_t node;
rcl_timer_t timer;

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

// Strength of the calibration operation;
// 0: disables calibration.
// 1 is weakest and 255 is strongest.
static constexpr const uint8_t calib_value = 255;

// This sample code performs calibration by clicking on a button or screen.
// After 10 seconds of calibration, the results are stored in NVS.
// The saved calibration values are loaded at the next startup.
//
// === How to calibration ===
// ※ Calibration method for Accelerometer
//    Change the direction of the main unit by 90 degrees
//     and hold it still for 2 seconds. Repeat multiple times.
//     It is recommended that as many surfaces as possible be on the bottom.
//
// ※ Calibration method for Gyro
//    Simply place the unit on a quiet desk and hold it still.
//    It is recommended that this be done after the accelerometer calibration.
//
// ※ Calibration method for geomagnetic sensors
//    Rotate the main unit slowly in multiple directions.
//    It is recommended that as many surfaces as possible be oriented to the north.
//
// Values for extremely large attitude changes are ignored.
// During calibration, it is desirable to move the device as gently as possible.

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
    { // Start calibration.
      M5.Imu.setCalibration(calib_value, calib_value, calib_value);
    }
    else
    { // Stop calibration. (Continue calibration only for the geomagnetic sensor)
      M5.Imu.setCalibration(0, 0, calib_value);

      // save calibration values.
      M5.Imu.saveOffsetToNVS();
    }
  }
}

void startCalibration(void)
{
  updateCalibration(10, true);
}

// Error handle loop
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

    // To update the IMU value, use M5.Imu.update.
    // If a new value is obtained, the return value is non-zero.
    auto imu_update = M5.Imu.update();
    if (imu_update)
    {
      // Obtain data on the current value of the IMU.
      auto data = M5.Imu.getImuData();

      mpu6050_msg.linear_acceleration.x = data.accel.x;
      mpu6050_msg.linear_acceleration.y = data.accel.y;
      mpu6050_msg.linear_acceleration.z = data.accel.z;

      mpu6050_msg.orientation.x = data.gyro.x;
      mpu6050_msg.orientation.y = data.gyro.y;
      mpu6050_msg.orientation.z = data.gyro.z;
    
      // Serial.print("GyroX: ");
      // Serial.print(data.gyro.x);
      // Serial.print("  GyroY: ");
      // Serial.print(data.gyro.y);
      // Serial.print("  GyroZ: ");
      // Serial.println(data.gyro.z);

      // Serial.print("AccelX: ");
      // Serial.print(data.accel.x);
      // Serial.print(" AccelY: ");
      // Serial.print(data.accel.y);
      // Serial.print(" AccelZ: ");
      // Serial.println(data.accel.z);
      /*
          // The data obtained by getImuData can be used as follows.
          data.accel.x;      // accel x-axis value.
          data.accel.y;      // accel y-axis value.
          data.accel.z;      // accel z-axis value.
          data.accel.value;  // accel 3values array [0]=x / [1]=y / [2]=z.

          data.gyro.x;      // gyro x-axis value.
          data.gyro.y;      // gyro y-axis value.
          data.gyro.z;      // gyro z-axis value.
          data.gyro.value;  // gyro 3values array [0]=x / [1]=y / [2]=z.

          data.mag.x;       // mag x-axis value.
          data.mag.y;       // mag y-axis value.
          data.mag.z;       // mag z-axis value.
          data.mag.value;   // mag 3values array [0]=x / [1]=y / [2]=z.

          data.value;       // all sensor 9values array [0~2]=accel / [3~5]=gyro / [6~8]=mag

          M5_LOGV("ax:%f  ay:%f  az:%f", data.accel.x, data.accel.y, data.accel.z);
          M5_LOGV("gx:%f  gy:%f  gz:%f", data.gyro.x , data.gyro.y , data.gyro.z );
          M5_LOGV("mx:%f  my:%f  mz:%f", data.mag.x  , data.mag.y  , data.mag.z  );
      */
      ++frame_count;
    }
    else
    {
      M5.update();

      // Calibration is initiated when a button or screen is clicked.
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
      { // prevent WDT.
        vTaskDelay(1);
      }
    }

    // Publish the IMU data.
    RCSOFTCHECK(rcl_publish(&publisher, &mpu6050_msg, NULL));
  }
}

void setup()
{
  // Configure serial transport
  Serial.begin(115200);
  set_microros_serial_transports(Serial);

  auto cfg = M5.config();

  M5.begin(cfg);
  Serial.begin(115200);

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

  // Read calibration values from NVS.
  if (!M5.Imu.loadOffsetFromNVS())
  {
    startCalibration();
  }
  pinMode(10, OUTPUT);
  digitalWrite(10, LOW);
  delay(2000);

  allocator = rcl_get_default_allocator();

  // create init_options
  RCCHECK(rclc_support_init(&support, 0, NULL, &allocator));

  // create node
  RCCHECK(rclc_node_init_default(&node, "micro_ros_platformio_node", "", &support));

  // create publisher
  RCCHECK(rclc_publisher_init_default(
      &publisher,
      &node,
      ROSIDL_GET_MSG_TYPE_SUPPORT(sensor_msgs, msg, Imu),
      "imu_publisher"));

  // create timer,
  const unsigned int timer_timeout = 10;
  RCCHECK(rclc_timer_init_default(
      &timer,
      &support,
      RCL_MS_TO_NS(timer_timeout),
      timer_callback));

  // create executor
  RCCHECK(rclc_executor_init(&executor, &support.context, 1, &allocator));
  RCCHECK(rclc_executor_add_timer(&executor, &timer));
}

void loop()
{
  delay(100);
  RCSOFTCHECK(rclc_executor_spin_some(&executor, RCL_MS_TO_NS(100)));
}