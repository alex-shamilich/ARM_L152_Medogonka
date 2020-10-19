//======================================================================================
// File Name          : freertos.c
// Description        : Code for freertos applications
//======================================================================================
#include "main.h"

#include "ExchangeStruct.h"
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"
#include "FreeRTOSUser.h"


//======================================================================================
// THREADs
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
osThreadId_t myTask_ScanTempHandle;
const osThreadAttr_t myTask_ScanTemp_attributes = {
  .name = "myTask_ScanTemp",
  .priority = (osPriority_t) osPriorityNormal,
//  .priority = (osPriority_t) osPriorityHigh,
  .stack_size = 512 * 4
};
//======================================================================================
osThreadId_t myTask_SetStateHandle;
const osThreadAttr_t myTask_SetState_attributes = {
  .name = "myTask_SetState",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 128 * 4
};
//======================================================================================
osThreadId_t myTask_MicroRLHandle;
const osThreadAttr_t myTask_MicroRL_attributes = {
  .name = "myTask_MicroRL",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 300 * 4
};
//======================================================================================
// QUEUEs
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
// MUTEX
//======================================================================================
osMutexId_t myMutex_I2C1Handle;
const osMutexAttr_t myMutex_I2C1_attributes = {
  .name = "myMutex_I2C1"
};
//======================================================================================
osMutexId_t MircoRL_Tx_MutexHandle;
const osMutexAttr_t MutexMircoRL_Tx_attributes = {
  .name = "MutexMircoRL_Tx"
};
//======================================================================================
osMutexId_t MircoRL_TxCMD_MutexHandle;
const osMutexAttr_t MutexMircoRL_TxCMD_attributes = {
  .name = "MutexMircoRL_TxCMD"
};
//======================================================================================


void StartDefaultTask(void *argument);
void StartTask_IMU(void *argument);
void StartTask_LCD(void *argument);
void StartTask_ADC(void *argument);
void StartTask_ScanTemperature(void *argument);
void StartTask_ScanControls(void *argument);
void StartTask_SetState(void *argument);
void StartTask_MircoRL(void *argument);


extern void MX_USB_DEVICE_Init(void);
void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */


extern TIM_HandleTypeDef htim9;


/* Hook prototypes */
void configureTimerForRunTimeStats(void);
unsigned long getRunTimeCounterValue(void);

/* Functions needed when configGENERATE_RUN_TIME_STATS is on */
//__weak void configureTimerForRunTimeStats(void)
void configureTimerForRunTimeStats(void)
{
	HAL_TIM_Base_Start(&htim9);
}

//__weak unsigned long getRunTimeCounterValue(void)
unsigned long getRunTimeCounterValue(void)
{
    static unsigned long counter = 0;

     counter += __HAL_TIM_GET_COUNTER(&htim9);
     __HAL_TIM_SET_COUNTER(&htim9, 0);

     return counter;
}

//======================================================================================
void MX_FREERTOS_Init(void)																// FreeRTOS initialization
{
  // Create the mutex(es)
  myMutex_I2C1Handle 		= osMutexNew(&myMutex_I2C1_attributes);						// creation of myMutex_I2C1
  MircoRL_Tx_MutexHandle 	= osMutexNew(&MutexMircoRL_Tx_attributes);					// creation of MutexMircoRL_Tx
  MircoRL_TxCMD_MutexHandle	= osMutexNew(&MutexMircoRL_TxCMD_attributes);				// creation of MutexMircoRL_TxCMD

  MicroRL_xRxSemaphore = xSemaphoreCreateCounting(10,0);
  MicroRL_xTxSemaphore = xSemaphoreCreateBinary();
  xSemaphoreGive(MicroRL_xTxSemaphore);

  // Create the queue(s)
  myQueue_UART_RxHandle 	= osMessageQueueNew (32, sizeof(uint8_t), &myQueue_UART_Rx_attributes);	// creation of myQueue_UART_Rx

  // Create the thread(s)
  defaultTaskHandle 		= osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);
  myTask_IMUHandle 			= osThreadNew(StartTask_IMU, NULL, &myTask_IMU_attributes);
  myTask_LCDHandle 			= osThreadNew(StartTask_LCD, NULL, &myTask_LCD_attributes);
  myTask_ADCHandle 			= osThreadNew(StartTask_ADC, NULL, &myTask_ADC_attributes);
  myTask_ScanCTRLHandle 	= osThreadNew(StartTask_ScanControls, NULL, &myTask_ScanCTRL_attributes);
  myTask_ScanTempHandle 	= osThreadNew(StartTask_ScanTemperature, NULL, &myTask_ScanTemp_attributes);
  myTask_SetStateHandle 	= osThreadNew(StartTask_SetState, NULL, &myTask_SetState_attributes);
  myTask_MicroRLHandle 		= osThreadNew(StartTask_MircoRL, NULL, &myTask_MicroRL_attributes);
}
//======================================================================================
void StartDefaultTask(void *argument)													// Поток по-умолчанию
{

  MX_USB_DEVICE_Init();																	// init code for USB_DEVICE

  BUZZER_BeepTIM();																		// Квакнуть баззером при старте

  for(;;)
  {
	//LED_LIGHT_INV;
	// LED_GREEN_INV;
    osDelay(100);


  }
}
//======================================================================================
void StartTask_IMU(void *argument)														// Поток сканирования данных от МЕМС по вибрации
{
  for(;;)
  {
    osDelay(10);
  }
}
//======================================================================================
void StartTask_LCD(void *argument)														// Поток вывода на LCD экран
{

  for(;;)
  {
	Display_Test(200,230);
	Display_MotorDirection(50, 50, MotorDirection);										// Показать направление вращения мотора
	Display_MotorSpeed(250, 50, MotorSpeed);											// Показать скорость вращения мотора

	Display_SystemVoltage(100, 5);

	Display_Temperature(10, 100, Temperature_Motor);									// Темература от датчика мотора
	Display_Temperature(10, 140, Temperature_Driver);									// Темература от датчика драйвера
	Display_Temperature(10, 180, Temperature_Air);										// Темература от датчика воздуха

	Display_Encoder(50, 230);															// Значение энкодера

	LED_GREEN_INV;

    osDelay(200);
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
void StartTask_ScanControls(void *argument)												// Поток сканироваяни элементов управления
{
  HAL_TIM_Base_Start_IT(&htim4);

  HAL_TIM_IC_Start_IT(&htim4, TIM_CHANNEL_1);											// Запустить TIM4 для анализа оборотов бака

  for(;;)
  {
	Motor_Scan_DirectionState(); 														// Сканирование переключателя направления движения мотора

	if (Encoder_Scan())																	// Просканировать энкодер и если состояние энкодера поменялось, выполниить действие
	{
		BUZZER_Beep_TickTIM();															// Сделать короткий тик баззером на каждую смену энкодера
//		TerminalPrintINT_ENCODER();														// послать строку в терминал с состоянием кнопок
	}




//	// Мигаем подсветкой согласно датчику вращения todo: временно
//	if (HAL_GPIO_ReadPin(SNS_HALL_IN_GPIO_Port,  SNS_HALL_IN_Pin) == GPIO_PIN_RESET)
//		LED_LIGHT_RESET;
//	else
//		LED_LIGHT_SET;

    osDelay(10);
  }
}
//======================================================================================
void StartTask_ScanTemperature(void *argument)											// Поток сканирования температуры по 1-Wire от термодатчиков DS18B20
{
  osDelay(200);

  for(;;)
  {
	DS18B20_Measure_Async_Start(TEMP_MOTOR_1W_GPIO_Port, 	TEMP_MOTOR_1W_Pin);			// Запрос на старт замера температуры мотора
	DS18B20_Measure_Async_Start(TEMP_DRIVER_1W_GPIO_Port,	TEMP_DRIVER_1W_Pin);		// Запрос на старт замера температуры драйвера мотора
	DS18B20_Measure_Async_Start(TEMP_AIR_1W_GPIO_Port, 		TEMP_AIR_1W_Pin);			// Запрос на старт замера температуры воздуха
	osDelay(1000);																		// задержка для 12-битного преобразования
	Temperature_Motor_RAW	= DS18B20_Measure_Async_FinishN(TEMP_MOTOR_1W_GPIO_Port, 	TEMP_MOTOR_1W_Pin);			// Возврат ответа от финальной фазы замера для температуры мотора
	Temperature_Driver_RAW	= DS18B20_Measure_Async_FinishN(TEMP_DRIVER_1W_GPIO_Port, 	TEMP_DRIVER_1W_Pin);		// Возврат ответа от финальной фазы замера для температуры драйвера мотора
	Temperature_Air_RAW		= DS18B20_Measure_Async_FinishN(TEMP_AIR_1W_GPIO_Port, 		TEMP_AIR_1W_Pin);			// Возврат ответа от финальной фазы замера для температуры воздуха

	Temperature_Motor		= DS18B20_Temperature_Double(Temperature_Motor_RAW);		// Пересчет в double
	Temperature_Driver		= DS18B20_Temperature_Double(Temperature_Driver_RAW);		// Пересчет в double
	Temperature_Air			= DS18B20_Temperature_Double(Temperature_Air_RAW);			// Пересчет в double

    osDelay(15000);																		// Интервал сканирования температур - 10 сек
  }
}
//======================================================================================
void StartTask_SetState(void *argument)													// Поток установки сотояний системы
{
  for(;;)
  {

	Motor_Set_DirectionState(MotorDirection);											// Установить направление мотора

	//DAC_SetValue((uint8_t)((double)Speed_value_percent*(double)2.55));				// Установить скорость мотора и пересчитать шкалу из  [0..100] в [0..255], получим на выход е DAC напряжение [0..3.3V]
	DAC_SetValue((uint8_t)((double)Speed_value_percent*(double)1.58));					// Установить скорость мотора и пересчитать шкалу из  [0..100] в [0..255], получим на выход е DAC напряжение [0..3.3V] (1.58 - коэф чтобы получить на выходе 0..5V после ЦАП+ОУ)

	MotorSpeed = ((MotorSpeed_Period > 0) ? ((uint16_t)((double)60000/(double)MotorSpeed_Period)) : (0) );			// Пересчет периода оборотов мотора от датчика Холла в скорость (стелано на таймере-4)


	//FAN_Set_Speed(Speed_value_percent);													// Установить скорость мотора вентилятора охлаждения (ШИМ)
	FAN_Set_Speed(0);																	// Установить скорость мотора вентилятора охлаждения (ШИМ)



    osDelay(20);
  }
}
//======================================================================================
void StartTask_MircoRL(void *argument)													// командный интерпретатор
{
	UNUSED(argument);
	microrl_terminalInit();																// нициализация командного интерпретатора

	HAL_UART_Receive_IT(&huart5, (uint8_t *)MainCPU_Rx_Buffer, 1);						// делаем начальный запрос на асинхронный прием обного байта - стартуем прием данных от UART на прерываниях

	while(1)
	{
		microrl_terminalProcess();														// Процесс просыпается от семафора MicroRL_xRxSemaphore
	}
}
//=======================================================================================
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
//	//	if ( huart->Instance == USART1 ) 												// Если это колбэк по прерыванию от USART-1  - компас
//	//	{
//	////		USART2->DR = USART1->DR;												// делаем эхо вывод из компаса в виртуальный COM-порта на PC (самый быстрый вариант)
//	//		MP_HCM505_RxCpltCallback(); 												// вызываем обработчик Callback окончания приема для компаса
//	//	}
//
//		if ( huart->Instance == USART2 ) 												// Если это колбэк по прерыванию от USART-2  - запрос в терминал командной строки от PC
//		{
//	//		USART2->DR = USART3->DR;													// делаем эхо вывод в виртуальный COM-порта на PC (самый быстрый вариант)
//		}
//
//
//		if ( huart->Instance == USART3 ) 												// Если это колбэк по прерыванию от USART-3  - GPS
//		{
////			USART2->DR = USART3->DR;												// делаем эхо вывод из GPS приемника в виртуальный COM-порта на PC (самый быстрый вариант)
////			MP_GPS_RxCpltCallback(); 												// вызываем обработчик Callback окончания приема для GPS
////
//			/* Создадим переменную куда будет положен результат API-функции xQueueReceiveFromISR(),
//			он станет pdTRUE, если операция с очередью разблокирует более высокоприоритетную задачу.*/
//			static portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
//			if( GPS_Rx_QueueHandle != 0 )
//				xQueueSendFromISR( GPS_Rx_QueueHandle,  ( void * )&MP_GPS_USART_RxBuffer[0], &xHigherPriorityTaskWoken  ); // записываем в очередь принятый байт от GPS
//			HAL_UART_Receive_IT(&huart3, (uint8_t *)MP_GPS_USART_RxBuffer, 1);			// делаем запрос на асинхронный прием обного байта
//		}
//
	if ( huart->Instance == UART5 ) 												// Если это колбэк по прерыванию от USART-5  - запрос в терминал MicroRL командной строки
	{
		//USART2->DR = MainCPU_Rx_Buffer[0];										// делаем эхо вывод в виртуальный COM-порта на PC (самый быстрый вариант)

		MircoRL_sRxRingBuf.data[MircoRL_sRxRingBuf.wrIdx++] = MainCPU_Rx_Buffer[0];	// складываем полученный байт в кольцевой буфер приема
		if (MircoRL_sRxRingBuf.wrIdx >= MICRORL_uartSIZE_OF_RING_BUFFER)			// переход через 0
		{
			MircoRL_sRxRingBuf.wrIdx = 0;
		}
		portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
		xSemaphoreGiveFromISR(MicroRL_xRxSemaphore, &xHigherPriorityTaskWoken);		// Семафорим в StartTask_MircoRL что прилетел байт из UART и что-то с ним нужно сделать
		if( xHigherPriorityTaskWoken != pdFALSE )
		{
			portYIELD();
		}
		HAL_UART_Receive_IT(&huart5, (uint8_t *)MainCPU_Rx_Buffer, 1);				// делаем опять запрос на асинхронный прием обного байта
	}
}
//=======================================================================================


