/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"
#include "dma.h"
#include "i2c.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <rcl/rcl.h>
#include <rcl/error_handling.h>
#include <rclc/rclc.h>
#include <rcl/init_options.h>
#include <rclc/executor.h>
#include <uxr/client/transport.h>
#include <rmw_microxrcedds_c/config.h>
#include <rmw_microros/rmw_microros.h>
#include <micro_ros_utilities/string_utilities.h>

#include <imu_interfaces/srv/imu_calibration.h>
#include <imu_interfaces/srv/imu_status.h>
#include <sensor_msgs/msg/imu.h>
#include <geometry_msgs/msg/twist.h>
#include <mpu6050.h>
#include <math.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
typedef struct {
	double x;
	double y;
	double z;
}offset3D_t;

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define G2M_S2 9.81
#define DEG2RAD M_PI/180.0
#define RAD2DEG 180/M_PI
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
#define RCSOFTCHECK(fn) if (fn != RCL_RET_OK){};
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

// Micro ROS Define starter
rclc_support_t support;
rcl_allocator_t allocator;
rcl_node_t node;
rcl_init_options_t init_options;

// Timer
rcl_timer_t node_timer;

// Executor
rclc_executor_t executor;

// Publisher
rcl_publisher_t mpu6050_publisher;

// Service server
rcl_service_t mpu6050_service;
imu_interfaces__srv__ImuCalibration_Response mpu6050_response;
imu_interfaces__srv__ImuCalibration_Request mpu6050_request;

rcl_service_t mpu6050_status_service;
imu_interfaces__srv__ImuStatus_Request mpu6050_status_request;
imu_interfaces__srv__ImuStatus_Response mpu6050_status_response;

// Message
sensor_msgs__msg__Imu mpu6050_msg;
geometry_msgs__msg__Twist cmd_vel_msg;

// Variable
MPU6050_t MPU6050;
offset3D_t accel_offset;
offset3D_t gyro_offset;

double dt = 0.01;

bool is_calibrate = false;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void MX_FREERTOS_Init(void);
/* USER CODE BEGIN PFP */
bool cubemx_transport_open(struct uxrCustomTransport * transport);
bool cubemx_transport_close(struct uxrCustomTransport * transport);
size_t cubemx_transport_write(struct uxrCustomTransport* transport, const uint8_t * buf, size_t len, uint8_t * err);
size_t cubemx_transport_read(struct uxrCustomTransport* transport, uint8_t* buf, size_t len, int timeout, uint8_t* err);

void * microros_allocate(size_t size, void * state);
void microros_deallocate(void * pointer, void * state);
void * microros_reallocate(void * pointer, size_t size, void * state);
void * microros_zero_allocate(size_t number_of_elements, size_t size_of_element, void * state);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

void pub_mpu6050(){
	// Set value in mpu6050_msg
	mpu6050_msg.header.frame_id = micro_ros_string_utilities_init("mpu6050_frame");
	mpu6050_msg.header.stamp.sec = rmw_uros_epoch_millis()/1000;
	mpu6050_msg.header.stamp.nanosec = rmw_uros_epoch_nanos();

	mpu6050_msg.linear_acceleration.x = G2M_S2 * MPU6050.Ax - accel_offset.x;
	mpu6050_msg.linear_acceleration.y = G2M_S2 * MPU6050.Ay - accel_offset.y;
	mpu6050_msg.linear_acceleration.z = G2M_S2 * MPU6050.Az - accel_offset.z;

	mpu6050_msg.angular_velocity.x = DEG2RAD * MPU6050.Gx - gyro_offset.x;
	mpu6050_msg.angular_velocity.y = DEG2RAD * MPU6050.Gy - gyro_offset.y;
	mpu6050_msg.angular_velocity.z = DEG2RAD * MPU6050.Gz - gyro_offset.z;

	// Publish mpu6050 data
	RCSOFTCHECK(rcl_publish(&mpu6050_publisher, &mpu6050_msg, NULL));
}

void service_callback(const void * request_msg, void * response_msg){
  imu_interfaces__srv__ImuCalibration_Request * req_in = (imu_interfaces__srv__ImuCalibration_Request *) request_msg;
  imu_interfaces__srv__ImuCalibration_Response* res_in = (imu_interfaces__srv__ImuCalibration_Response *) response_msg;

  for(int i=0 ; i<9 ; i++){
	  mpu6050_msg.linear_acceleration_covariance[i] = req_in->imu_calib.linear_acceleration_covariance[i];
	  mpu6050_msg.angular_velocity_covariance[i] = req_in->imu_calib.angular_velocity_covariance[i];
  }

  accel_offset.x = req_in->imu_calib.linear_acceleration.x;
  accel_offset.y = req_in->imu_calib.linear_acceleration.y;
  accel_offset.z = req_in->imu_calib.linear_acceleration.z;

  gyro_offset.x = req_in->imu_calib.angular_velocity.x;
  gyro_offset.y = req_in->imu_calib.angular_velocity.y;
  gyro_offset.z = req_in->imu_calib.angular_velocity.z;

  res_in->success = true;
  is_calibrate = true;

  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_SET);
}

void imu_status_service_callback(const void * request_msg, void * response_msg){
  imu_interfaces__srv__ImuStatus_Request * req_in = (imu_interfaces__srv__ImuStatus_Request *) request_msg;
  imu_interfaces__srv__ImuStatus_Response * res_in = (imu_interfaces__srv__ImuStatus_Response *) response_msg;

  if (req_in->imu_status_check.data){
	  if(is_calibrate){
		  double g = G2M_S2 * MPU6050.Az - accel_offset.z;
		  if( g >= 9.0 && g <= 10.8) {
			  res_in->imu_status.data = true;
		  }else {
			  res_in->imu_status.data = false;
		}
	  }else {
		  res_in->imu_status.data   = false;
	}
  }
}

void timer_callback(rcl_timer_t * timer, int64_t last_call_time){
	if (timer != NULL) {
		// Read mpu6050
		MPU6050_Read_All(&hi2c1, &MPU6050);
		// call mpu6050 publish function
		pub_mpu6050();
	}
}

void StartDefaultTask(void *argument){
  // micro-ROS configuration

  rmw_uros_set_custom_transport(
    true,
    (void *) &hlpuart1,
    cubemx_transport_open,
    cubemx_transport_close,
    cubemx_transport_write,
    cubemx_transport_read);

  rcl_allocator_t freeRTOS_allocator = rcutils_get_zero_initialized_allocator();
  freeRTOS_allocator.allocate = microros_allocate;
  freeRTOS_allocator.deallocate = microros_deallocate;
  freeRTOS_allocator.reallocate = microros_reallocate;
  freeRTOS_allocator.zero_allocate =  microros_zero_allocate;

  if (!rcutils_set_default_allocator(&freeRTOS_allocator)) {
      printf("Error on default allocators (line %d)\n", __LINE__);
  }

  // micro-ROS app
  allocator = rcl_get_default_allocator();

  //create init_options
  init_options = rcl_get_zero_initialized_init_options();
  RCSOFTCHECK(rcl_init_options_init(&init_options, allocator));
  RCSOFTCHECK(rcl_init_options_set_domain_id(&init_options, 50));

  rclc_support_init_with_options(&support, 0, NULL, &init_options, &allocator);

  // create node
  rclc_node_init_default(&node, "mpu6050_node", "", &support);

  // sync time
  rmw_uros_sync_session(1000);

  // create timer
  rclc_timer_init_default(
	  &node_timer,
	  &support,
	  RCL_MS_TO_NS(dt*1000),
	  timer_callback
  );

  // create publisher
  rclc_publisher_init_best_effort(
  	  &mpu6050_publisher,
  	  &node,
  	  ROSIDL_GET_MSG_TYPE_SUPPORT(sensor_msgs, msg, Imu),
  	  "mpu6050_publisher"
  );

  // create service
  rclc_service_init_default(
	  &mpu6050_service,
	  &node,
	  ROSIDL_GET_SRV_TYPE_SUPPORT(imu_interfaces, srv, ImuCalibration),
	  "mpu6050_calibration"
  );

  rclc_service_init_default(
	  &mpu6050_status_service,
	  &node,
	  ROSIDL_GET_SRV_TYPE_SUPPORT(imu_interfaces, srv, ImuStatus),
	  "status"
  );

  // create executor
  executor = rclc_executor_get_zero_initialized_executor();
  rclc_executor_init(&executor, &support.context, 3, &allocator);
  rclc_executor_add_timer(&executor, &node_timer);
  rclc_executor_add_service(&executor, &mpu6050_status_service, &mpu6050_status_request, &mpu6050_status_response, imu_status_service_callback);
  rclc_executor_add_service(&executor, &mpu6050_service, &mpu6050_request, &mpu6050_response, service_callback);
  rclc_executor_spin(&executor);

  for(;;){
    osDelay(10);
  }
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_LPUART1_UART_Init();
  MX_I2C1_Init();
  /* USER CODE BEGIN 2 */
  while (MPU6050_Init(&hi2c1) == 1);
  /* USER CODE END 2 */

  /* Init scheduler */
  osKernelInitialize();

  /* Call init function for freertos objects (in cmsis_os2.c) */
  MX_FREERTOS_Init();

  /* Start scheduler */
  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1_BOOST);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV4;
  RCC_OscInitStruct.PLL.PLLN = 85;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM1 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM1) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
