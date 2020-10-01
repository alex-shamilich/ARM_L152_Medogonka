/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
typedef StaticQueue_t osStaticMessageQDef_t;
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 128 * 4
};
/* Definitions for myTask_IMU */
osThreadId_t myTask_IMUHandle;
const osThreadAttr_t myTask_IMU_attributes = {
  .name = "myTask_IMU",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 128 * 4
};
/* Definitions for myTask_LCD */
osThreadId_t myTask_LCDHandle;
const osThreadAttr_t myTask_LCD_attributes = {
  .name = "myTask_LCD",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 512 * 4
};
/* Definitions for myTask_ADC */
osThreadId_t myTask_ADCHandle;
const osThreadAttr_t myTask_ADC_attributes = {
  .name = "myTask_ADC",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 256 * 4
};
/* Definitions for myTask_ScanCTRL */
osThreadId_t myTask_ScanCTRLHandle;
const osThreadAttr_t myTask_ScanCTRL_attributes = {
  .name = "myTask_ScanCTRL",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 128 * 4
};
/* Definitions for myQueue_UART_Rx */
osMessageQueueId_t myQueue_UART_RxHandle;
uint8_t myQueue_UART_RxBuffer[ 32 * sizeof( uint8_t ) ];
osStaticMessageQDef_t myQueue_UART_RxControlBlock;
const osMessageQueueAttr_t myQueue_UART_Rx_attributes = {
  .name = "myQueue_UART_Rx",
  .cb_mem = &myQueue_UART_RxControlBlock,
  .cb_size = sizeof(myQueue_UART_RxControlBlock),
  .mq_mem = &myQueue_UART_RxBuffer,
  .mq_size = sizeof(myQueue_UART_RxBuffer)
};
/* Definitions for myMutex_I2C1 */
osMutexId_t myMutex_I2C1Handle;
const osMutexAttr_t myMutex_I2C1_attributes = {
  .name = "myMutex_I2C1"
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
void StartTask_IMU(void *argument);
void StartTask_LCD(void *argument);
void StartTask_ADC(void *argument);
void StartTask_ScanControls(void *argument);

extern void MX_USB_DEVICE_Init(void);
void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */
  /* Create the mutex(es) */
  /* creation of myMutex_I2C1 */
  myMutex_I2C1Handle = osMutexNew(&myMutex_I2C1_attributes);

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the queue(s) */
  /* creation of myQueue_UART_Rx */
  myQueue_UART_RxHandle = osMessageQueueNew (32, sizeof(uint8_t), &myQueue_UART_Rx_attributes);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* creation of myTask_IMU */
  myTask_IMUHandle = osThreadNew(StartTask_IMU, NULL, &myTask_IMU_attributes);

  /* creation of myTask_LCD */
  myTask_LCDHandle = osThreadNew(StartTask_LCD, NULL, &myTask_LCD_attributes);

  /* creation of myTask_ADC */
  myTask_ADCHandle = osThreadNew(StartTask_ADC, NULL, &myTask_ADC_attributes);

  /* creation of myTask_ScanCTRL */
  myTask_ScanCTRLHandle = osThreadNew(StartTask_ScanControls, NULL, &myTask_ScanCTRL_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* init code for USB_DEVICE */
  MX_USB_DEVICE_Init();
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_StartTask_IMU */
/**
* @brief Function implementing the myTask_IMU thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask_IMU */
void StartTask_IMU(void *argument)
{
  /* USER CODE BEGIN StartTask_IMU */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartTask_IMU */
}

/* USER CODE BEGIN Header_StartTask_LCD */
/**
* @brief Function implementing the myTask_LCD thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask_LCD */
void StartTask_LCD(void *argument)
{
  /* USER CODE BEGIN StartTask_LCD */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartTask_LCD */
}

/* USER CODE BEGIN Header_StartTask_ADC */
/**
* @brief Function implementing the myTask_ADC thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask_ADC */
void StartTask_ADC(void *argument)
{
  /* USER CODE BEGIN StartTask_ADC */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartTask_ADC */
}

/* USER CODE BEGIN Header_StartTask_ScanControls */
/**
* @brief Function implementing the myTask_ScanCTRL thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask_ScanControls */
void StartTask_ScanControls(void *argument)
{
  /* USER CODE BEGIN StartTask_ScanControls */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartTask_ScanControls */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
