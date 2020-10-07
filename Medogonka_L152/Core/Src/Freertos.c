//======================================================================================
// File Name          : freertos.c
// Description        : Code for freertos applications
//======================================================================================

#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

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
osThreadId_t myTask_SetStateHandle;
const osThreadAttr_t myTask_SetState_attributes = {
  .name = "myTask_SetState",
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
void StartTask_SetState(void *argument);

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
  myTask_SetStateHandle 	= osThreadNew(StartTask_SetState, NULL, &myTask_SetState_attributes);
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

  for(;;)
  {
	Display_Test(0,0);
	Display_MotorDirection(250, 50, MotorDirection);									// Показать направление вращения мотора

	Display_SystemVoltage(100, 5);

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
	Motor_Scan_DirectionState(); 														// Сканирование переключателя направления движения мотора


	// Мигаем подсветкой согласно датчику вращения todo: временно
	if (HAL_GPIO_ReadPin(SNS_HALL_IN_GPIO_Port,  SNS_HALL_IN_Pin) == GPIO_PIN_RESET)
		LED_LIGHT_RESET;
	else
		LED_LIGHT_SET;



    osDelay(10);
  }
}
//======================================================================================
void StartTask_SetState(void *argument)													// implementing the myTask_SetState thread.
{
  for(;;)
  {

	Motor_Set_DirectionState(MotorDirection);											// Установить направление мотора

	//DAC_SetValue((uint8_t)((double)Speed_value_percent*(double)2.55));				// Установить скорость мотора и пересчитать шкалу из  [0..100] в [0..255], получим на выход е DAC напряжение [0..3.3V]
	DAC_SetValue((uint8_t)((double)Speed_value_percent*(double)1.58));					// Установить скорость мотора и пересчитать шкалу из  [0..100] в [0..255], получим на выход е DAC напряжение [0..3.3V] (1.58 - коэф чтобы получить на выходе 0..5V после ЦАП+ОУ)


	FAN_Set_Speed(Speed_value_percent);													// Установить скорость мотора вентилятора охлаждения (ШИМ)



    osDelay(20);
  }
}
//======================================================================================
