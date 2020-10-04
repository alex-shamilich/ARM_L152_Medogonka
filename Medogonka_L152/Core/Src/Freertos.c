//======================================================================================
// File Name          : freertos.c
// Description        : Code for freertos applications
//======================================================================================

#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"
#include "stdio.h"
#include "LCD_ili9488_fonts.h"

//#include "LCD_ili9488.h"
//#include "LCD_ili9488_fonts.h"
//======================================================================================
typedef StaticQueue_t osStaticMessageQDef_t;
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name 		= "defaultTask",
  .priority 	= (osPriority_t) osPriorityNormal,
  .stack_size 	= 128 * 4
};
//======================================================================================
osThreadId_t myTask_IMUHandle;
const osThreadAttr_t myTask_IMU_attributes = {
  .name 		= "myTask_IMU",
  .priority 	= (osPriority_t) osPriorityNormal,
  .stack_size 	= 128 * 4
};
//======================================================================================
osThreadId_t myTask_LCDHandle;
const osThreadAttr_t myTask_LCD_attributes = {
  .name 		= "myTask_LCD",
  .priority 	= (osPriority_t) osPriorityNormal,
  .stack_size 	= 512 * 4
};
//======================================================================================
osThreadId_t myTask_ADCHandle;
const osThreadAttr_t myTask_ADC_attributes = {
  .name 		= "myTask_ADC",
  .priority 	= (osPriority_t) osPriorityNormal,
  .stack_size 	= 256 * 4
};
//======================================================================================
osThreadId_t myTask_ScanCTRLHandle;
const osThreadAttr_t myTask_ScanCTRL_attributes = {
  .name = "myTask_ScanCTRL",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 128 * 4
};
//======================================================================================
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
//======================================================================================
osMutexId_t myMutex_I2C1Handle;
const osMutexAttr_t myMutex_I2C1_attributes = {
  .name = "myMutex_I2C1"
};
//======================================================================================

void StartDefaultTask(void *argument);
void StartTask_IMU(void *argument);
void StartTask_LCD(void *argument);
void StartTask_ADC(void *argument);
void StartTask_ScanControls(void *argument);

extern void MX_USB_DEVICE_Init(void);
void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

//======================================================================================
void MX_FREERTOS_Init(void)																// FreeRTOS initialization
{
  // Create the mutex(es)
  myMutex_I2C1Handle 		= osMutexNew(&myMutex_I2C1_attributes);						// creation of myMutex_I2C1

  // Create the queue(s)
  myQueue_UART_RxHandle 	= osMessageQueueNew (32, sizeof(uint8_t), &myQueue_UART_Rx_attributes);	// creation of myQueue_UART_Rx

  // Create the thread(s)
  defaultTaskHandle 		= osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);
  myTask_IMUHandle 			= osThreadNew(StartTask_IMU, NULL, &myTask_IMU_attributes);
  myTask_LCDHandle 			= osThreadNew(StartTask_LCD, NULL, &myTask_LCD_attributes);
  myTask_ADCHandle 			= osThreadNew(StartTask_ADC, NULL, &myTask_ADC_attributes);
  myTask_ScanCTRLHandle 	= osThreadNew(StartTask_ScanControls, NULL, &myTask_ScanCTRL_attributes);
}
//======================================================================================
void StartDefaultTask(void *argument)													// implementing the defaultTask thread.
{

  MX_USB_DEVICE_Init();																	// init code for USB_DEVICE

  BUZZER_BeepTIM();

  for(;;)
  {
	//LED_LIGHT_INV;
	// LED_GREEN_INV;
    osDelay(100);


  }
}
//======================================================================================
void StartTask_IMU(void *argument)														// implementing the myTask_IMU thread.
{
  for(;;)
  {
    osDelay(1);
  }
}
//======================================================================================
void StartTask_LCD(void *argument)														// implementing the myTask_LCD thread.
{
  char str[18];

  for(;;)
  {
	sprintf(str, "%04.3f", ADC_State.Speed_value_volts);
	LCD9488_GUI_Draw_StringColor(10, 230, str, (unsigned char*)LCD55Mono37x48, RED, CYAN, DRAW_NO_OVERLYING);

	sprintf(str, "%03d", ADC_State.Speed_value_percent);
	LCD9488_GUI_Draw_StringColor(200, 230, str, (unsigned char*)Digital7Mono32x48, RED, CYAN, DRAW_NO_OVERLYING);

	sprintf(str, "%+2.1fC", ADC_State.CPU_Temperature);
	LCD9488_GUI_Draw_StringColor(10, 10, str, (unsigned char*)Arial28x28, RED, CYAN, DRAW_NO_OVERLYING);

	sprintf(str, "%3.3fv", ADC_State.ADC_Ref_Voltage);
	LCD9488_GUI_Draw_StringColor(200, 10, str, (unsigned char*)Arial28x28, RED, CYAN, DRAW_NO_OVERLYING);

	LED_GREEN_INV;

    osDelay(100);
  }
}
//======================================================================================
void StartTask_ADC(void *argument)														// Поток для сканирования АЦП (Напряжения питания и мотора, Тока питания и мотора, положения регулятора скорости)
{
  for(;;)
  {
	ADC_ScanState();																	// Замер из АЦП по всем каналам сразу
    osDelay(50);
  }
}
//======================================================================================
void StartTask_ScanControls(void *argument)												// implementing the myTask_ScanCTRL thread.
{
  for(;;)
  {
	// Выбор направления движения мотора
	if (HAL_GPIO_ReadPin(BTN_FWD_GPIO_Port,  BTN_FWD_Pin) == GPIO_PIN_RESET)
		MOTOR_FWD_SET;
	else
		MOTOR_FWD_RESET;

	if (HAL_GPIO_ReadPin(BTN_BWD_GPIO_Port,  BTN_BWD_Pin) == GPIO_PIN_RESET)
		MOTOR_BWD_SET;
	else
		MOTOR_BWD_RESET;


	if (HAL_GPIO_ReadPin(SNS_HALL_IN_GPIO_Port,  SNS_HALL_IN_Pin) == GPIO_PIN_RESET)
		LED_LIGHT_RESET;
	else
		LED_LIGHT_SET;


//	if (HAL_GPIO_ReadPin(ENC_BTN_GPIO_Port,  ENC_BTN_Pin) == GPIO_PIN_SET)
//		LED_GREEN_RESET;
//	else
//		LED_GREEN_SET;
//	if (HAL_GPIO_ReadPin(ENC_A_GPIO_Port,  ENC_A_Pin) == GPIO_PIN_RESET)
//		LED_GREEN_RESET;
//	else
//		LED_GREEN_SET;
//
//	if (HAL_GPIO_ReadPin(ENC_B_GPIO_Port,  ENC_B_Pin) == GPIO_PIN_RESET)
//		LED_GREEN_RESET;
//	else
//		LED_GREEN_SET;


    osDelay(1);
  }
}
//======================================================================================
