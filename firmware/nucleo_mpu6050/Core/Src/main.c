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
#include <rclc/executor.h>
#include <uxr/client/transport.h>
#include <rmw_microxrcedds_c/config.h>
#include <rmw_microros/rmw_microros.h>
#include <rcl/init_options.h>
#include <micro_ros_utilities/string_utilities.h>
#include <sensor_msgs/msg/imu.h>
#include <math.h>
#include <imu_custom_msg/srv/get_status.h>
#include <geometry_msgs/msg/twist.h>

#include <mpu6050.h>
#include <imu_custom_msg/srv/calibrate.h>

#include <std_msgs/msg/int32.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define G2M_S2 9.81
#define DEG2RAD M_PI / 180.0
#define RAD2DEG 180.0 / M_PI

#define MPU6050_ADDR     (0x68 << 1)  // Shifted left by 1 for STM32 HAL
#define WHO_AM_I_REG     0x75         // WHO_AM_I register address
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
rclc_support_t support;
rcl_allocator_t allocator;
rcl_node_t node;
rcl_timer_t mpu6050_timer;
rcl_publisher_t mpu6050_publisher;
sensor_msgs__msg__Imu mpu6050_msg;
rclc_executor_t executor;
MPU6050_t MPU6050;



rcl_service_t status_service;
rcl_service_t calibrate_service;

imu_custom_msg__srv__GetStatus_Request request_msg;
imu_custom_msg__srv__GetStatus_Response response_msg;

imu_custom_msg__srv__Calibrate_Request calibrate_request_msg;
imu_custom_msg__srv__Calibrate_Response calibrate_response_msg;

std_msgs__msg__Float64MultiArray request_arr;


rcl_publisher_t gazebo_vel_publisher;
rcl_publisher_t vel_publisher;
geometry_msgs__msg__Twist twist_msg;
geometry_msgs__msg__Twist gazebo_twist_msg;

uint8_t register_value;
HAL_StatusTypeDef ret;

float process_roll_error = 0.098033;
float process_pitch_error = 0.113961;
float measure_roll_error = 0.042646;
float measure_pitch_error = 0.08; //0.033375;

float dt = 0.01;
double x[3] = { 0.0, 0.0, 0.0 };
double u[3] = { 0.0, 0.0, 0.0 };
double p[2] = { pow(2, 2), pow(2, 2) };
double r_roll;
double r_pitch;
double p_roll;
double p_pitch;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void MX_FREERTOS_Init(void);
/* USER CODE BEGIN PFP */
bool cubemx_transport_open(struct uxrCustomTransport *transport);
bool cubemx_transport_close(struct uxrCustomTransport *transport);
size_t cubemx_transport_write(struct uxrCustomTransport *transport,
		const uint8_t *buf, size_t len, uint8_t *err);
size_t cubemx_transport_read(struct uxrCustomTransport *transport, uint8_t *buf,
		size_t len, int timeout, uint8_t *err);

void* microros_allocate(size_t size, void *state);
void microros_deallocate(void *pointer, void *state);
void* microros_reallocate(void *pointer, size_t size, void *state);
void* microros_zero_allocate(size_t number_of_elements, size_t size_of_element,
		void *state);

void service_callback(const void *request_msg, void *response_msg);
void update_vel();
void read_register();
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

void timer_callback(rcl_timer_t *timer, int64_t last_call_time) {

	if (timer != NULL) {
		MPU6050_Read_All(&hi2c1, &MPU6050);

		mpu6050_msg.header.stamp.sec = rmw_uros_epoch_millis() / 1000;
		mpu6050_msg.header.stamp.nanosec = rmw_uros_epoch_nanos() / 1000;

//		mpu6050_msg.linear_acceleration.x = G2M_S2 * MPU6050.Ax;
//		mpu6050_msg.linear_acceleration.y = G2M_S2 * MPU6050.Ay;
//		mpu6050_msg.linear_acceleration.z = G2M_S2 * MPU6050.Az;
//		mpu6050_msg.angular_velocity.x = DEG2RAD * MPU6050.Gx;
//		mpu6050_msg.angular_velocity.y = DEG2RAD * MPU6050.Gy;
//		mpu6050_msg.angular_velocity.z = DEG2RAD * MPU6050.Gz;

		mpu6050_msg.linear_acceleration.x = G2M_S2 * MPU6050.Ax
				- 1.066469;
		mpu6050_msg.linear_acceleration.y = G2M_S2 * MPU6050.Ay
				- -0.050949;
		mpu6050_msg.linear_acceleration.z = G2M_S2 * MPU6050.Az
				- 1.663030;

		mpu6050_msg.angular_velocity.x = DEG2RAD * MPU6050.Gx
				- (-0.007206);
		mpu6050_msg.angular_velocity.y = DEG2RAD * MPU6050.Gy
				- (-0.003486);
		mpu6050_msg.angular_velocity.z = DEG2RAD * MPU6050.Gz
				- (0.031661);

		float Ax = mpu6050_msg.linear_acceleration.x;
		float Ay = mpu6050_msg.linear_acceleration.y;
		float Az = mpu6050_msg.linear_acceleration.z;

		u[0] = mpu6050_msg.angular_velocity.x;
		u[1] = mpu6050_msg.angular_velocity.y;

		float angleRoll = atan2(Ay, hypot(Ax, Az));
		float anglePitch = atan2(-Ax, hypot(Ay, Az));

		//predict
		float future_roll = x[0] + dt * u[0];
		float future_pitch = x[1] + dt * u[1];

		float future_P_roll = p[0] + (pow(dt, 2) * p_roll);
		float future_P_pitch = p[1] + (pow(dt, 2) * p_pitch);

		//kalman gain update
		float K_roll = future_P_roll / (future_P_roll + r_roll);
		float K_pitch = future_P_pitch / (future_P_pitch + r_pitch);

		//fusion state update
		if (abs(angleRoll) > 1.3) {
			K_roll = 0;
		}

		x[0] = future_roll + K_roll * (angleRoll - future_roll);
		x[1] = future_pitch + K_pitch * (anglePitch - future_pitch);

		//p update
		p[0] = (1 - K_roll) * p[0];
		p[1] = (1 - K_pitch) * p[1];

		mpu6050_msg.orientation.x = x[0];
		mpu6050_msg.orientation.y = x[1];
		mpu6050_msg.orientation.z = angleRoll;

		update_vel();





		rcl_publish(&mpu6050_publisher, &mpu6050_msg, NULL);

	}
}

void service_callback(const void *request_msg, void *response_msg) {

	imu_custom_msg__srv__GetStatus_Response *response =
			(imu_custom_msg__srv__GetStatus_Response*) response_msg;

	read_register();
	if(ret == 0){
		response->status.data = true;
	}
	else{
		response->status.data = false;
	}



}

void calibrate_service_callback(const void *req_msg, void *res_msg) {
    const imu_custom_msg__srv__Calibrate_Request *req = (const imu_custom_msg__srv__Calibrate_Request *) req_msg;
    imu_custom_msg__srv__Calibrate_Response *res = (imu_custom_msg__srv__Calibrate_Response *) res_msg;

    // Set the response
    res->success.data = true;
}

void StartDefaultTask(void *argument) {
	/* USER CODE BEGIN 5 */

	// micro-ROS configuration
	rmw_uros_set_custom_transport(
	true, (void*) &hlpuart1, cubemx_transport_open, cubemx_transport_close,
			cubemx_transport_write, cubemx_transport_read);

	rcl_allocator_t freeRTOS_allocator =
			rcutils_get_zero_initialized_allocator();
	freeRTOS_allocator.allocate = microros_allocate;
	freeRTOS_allocator.deallocate = microros_deallocate;
	freeRTOS_allocator.reallocate = microros_reallocate;
	freeRTOS_allocator.zero_allocate = microros_zero_allocate;

	if (!rcutils_set_default_allocator(&freeRTOS_allocator)) {
		printf("Error on default allocators (line %d)\n", __LINE__);
	}

	// micro-ROS app
	allocator = rcl_get_default_allocator();

	//create init_options
	rcl_init_options_t init_options = rcl_get_zero_initialized_init_options();
	rcl_init_options_init(&init_options, allocator);
	rcl_init_options_set_domain_id(&init_options, 69);

	rclc_support_init_with_options(&support, 0, NULL, &init_options,
			&allocator);

	// create node
	rclc_node_init_default(&node, "cubemx_node", "", &support);
	rmw_uros_sync_session(1000);

	// create timer
	rclc_timer_init_default(&mpu6050_timer, &support, RCL_MS_TO_NS(10),
			timer_callback);

	//create publisher
	rclc_publisher_init_best_effort(&mpu6050_publisher, &node,
			ROSIDL_GET_MSG_TYPE_SUPPORT(sensor_msgs, msg, Imu),
			"mpu6050_publisher");

	//create header
	mpu6050_msg.header.frame_id = micro_ros_string_utilities_init("imu_frame");

	//imu_status
	rclc_service_init_default(&status_service, &node,
			ROSIDL_GET_SRV_TYPE_SUPPORT(imu_custom_msg, srv, GetStatus),
			"imu/status");

	rclc_service_init_default(&calibrate_service, &node,
				ROSIDL_GET_SRV_TYPE_SUPPORT(imu_custom_msg, srv, Calibrate),
				"imu/calibrate");

	//cmd_vel publisher
	rclc_publisher_init_default(&vel_publisher,
			&node,
			ROSIDL_GET_MSG_TYPE_SUPPORT(geometry_msgs, msg, Twist),
			"cmd_vel");

	rclc_publisher_init_default(&gazebo_vel_publisher,
				&node,
				ROSIDL_GET_MSG_TYPE_SUPPORT(geometry_msgs, msg, Twist),
				"gazebo/cmd_vel");



	//create executor
	executor = rclc_executor_get_zero_initialized_executor();
	rclc_executor_init(&executor, &support.context, 2, &allocator);
	rclc_executor_add_timer(&executor, &mpu6050_timer);
	rclc_executor_add_service(&executor, &status_service, &request_msg, &response_msg, service_callback);
	rclc_executor_add_service(&executor, &calibrate_service, &calibrate_request_msg, &calibrate_response_msg, calibrate_service_callback);
	rclc_executor_spin(&executor);

	for (;;) {
		osDelay(10);
	}
	/* USER CODE END 5 */
}
/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void) {

	/* USER CODE BEGIN 1 */
	r_roll = pow(measure_roll_error, 2);
	r_pitch = pow(measure_pitch_error, 2);
	p_roll = pow(2, 2);
	p_pitch = pow(2, 2);

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
	while (MPU6050_Init(&hi2c1) == 1)
		;
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
	while (1) {
		/* USER CODE END WHILE */

		/* USER CODE BEGIN 3 */
	}
	/* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void) {
	RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
	RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };

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
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		Error_Handler();
	}

	/** Initializes the CPU, AHB and APB buses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
			| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK) {
		Error_Handler();
	}
}

/* USER CODE BEGIN 4 */
void update_vel(){
	float scale_factor = 5.0/90.0;

	twist_msg.linear.x = x[1] * RAD2DEG * scale_factor;
	twist_msg.angular.z = -1 * x[0] * RAD2DEG *scale_factor;

	rcl_publish(&vel_publisher, &twist_msg, NULL);

	gazebo_twist_msg.linear.x = x[1] * RAD2DEG * scale_factor *0.05;
	gazebo_twist_msg.linear.y = -1 * x[0] * RAD2DEG *scale_factor *0.05;

	rcl_publish(&gazebo_vel_publisher, &gazebo_twist_msg, NULL);


}

void read_register() {

    // Read 1 byte from the register
    ret = HAL_I2C_Mem_Read(&hi2c1, MPU6050_ADDR, WHO_AM_I_REG, I2C_MEMADD_SIZE_8BIT, &register_value, 1, HAL_MAX_DELAY);

    if (ret == HAL_OK) {
        // Successfully read, print or process `register_value`
        printf("Register Value: 0x%02X\n", register_value);
    } else {
        // Error handling
        printf("I2C Read Error\n");
    }
}
/* USER CODE END 4 */

/**
 * @brief  Period elapsed callback in non blocking mode
 * @note   This function is called  when TIM1 interrupt took place, inside
 * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
 * a global variable "uwTick" used as application time base.
 * @param  htim : TIM handle
 * @retval None
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
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
void Error_Handler(void) {
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1) {
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
