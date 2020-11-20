//======================================================================================
// File Name          : main.c
// Description        : Main program body
//======================================================================================

//======================================================================================
// Контроллер двигателя медогонки
//
// Author: Alex Shamilich  (2020-10-01)
//
//
// Процессор:
//		STM32L152VET6 LQFP-100
//
// Система:
//		FreeRTOS 10.0.1
//
// Переферия подключенная:
//		LCD Color 480х320 ILI9488  (SPI2)
//		Баззер - динамик
//		LED_GREEN - отладочный светодиод
// 		LED_LIGHT - управление подсветкой бака
//		Кнопки: СТАРТ, СТОП, МОТОР, Переключатель направления мотора
//		Вход датчика оборотов бака
//		UART2:	Virtual COM-Port для printf (115200/8/N/1)
// 		настроен АЦП для получения токов, напряжений, температуры процессора
// 		настроен ЦАП для управления скоростью мотора, сканирование переключателя направления мотора и отправвка его состояния в контроллер мотора
// 		настроен TIM11 - для ШИМ управления оборотами мотора вентилятора охлаждения контроллера двигателя
//		настроена возможность отладки FreeRTOS (подключен микросекундный таймер на TIM9)
// 		настроен TIM4 - для рассчета оборотов бака (скорости мотора) по датчику Холла (см InputCaptureCallback + PeriodElaspedCallback)
// 		настроен TIM10 - для микросекундных задержек Delay_us()
//      настроены термодатчики DS18B20 на 1-Wire, опрос раз в 15 сек в отдельной задаче RtOS
// 		встроена командная консоль MicroRL на порт UART5 (115200/8/N/1)
// 		настроен инкрементальный энкодер на аппаратном таймере (TIM3) см: Encoder_Scan()

// I2C1 - подключение датчиков (MPU-6050,
// SPI1 - SD Card
// SPI2 - LCD экран ILI9488
// UART порты:
// 		UART1:
// 		UART2:	Virtual COM-Port возможность вывода сообщений с помощью простого printf (переопределен putc и заглушки к stdlib)
// 		UART3:
// 		UART4:
// 		UART5:  Консоль MicroRL (через BLUETOOTH адаптер)
// Таймеры:
//		TIM2	отключен
//		TIM3	обслуживание энкодера для меню
//		TIM4	магнитный датчик оборотов бака
//		TIM5	отключен
//		TIM6	динамик
//		TIM7	источник тиков для FreeRTOS
//		TIM9	источник микросекундных тиков (для отладки FreeRTOS)
//		TIM10	источник микросекундных тиков (для DelayUS() со сбросом ) нужен для 1-Wire DS18B20
//		TIM11	ШИМ управление оборотами мотора вентилятора охлаждения контроллера двигателя


//======================================================================================
#include "main.h"

#include "cmsis_os.h"
#include <ADC.h>
#include <DAC.h>
#include <DMA.h>
#include "fatfs.h"
#include "i2c.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "usb_device.h"
#include "gpio.h"
#include "ExchangeStruct.h"

#include "LCD_ili9488_test.h"


void SystemClock_Config(void);
void MX_FREERTOS_Init(void);

//======================================================================================
int fatfs_test(void)
{

}

//======================================================================================
int main(void)
{
	HAL_Init();																			// Настройка HAL
	SystemClock_Config();																// Настройка системы тактирования

	MX_GPIO_Init();																		// Настройка пинов GPIO, не привязанных к блокам SPI, UART, I2C, keys, encoder, ADC, DAC
	MX_DMA_Init();																		// Настройка DMA
	MX_SPI1_Init();																		// Настройка SPI1 для работы с SD картой
	MX_SPI2_Init();																		// Настройка SPI2 для работы с LCD экраном ILI9488
	MX_I2C1_Init();																		// Настройка I2C для работы с IMU

	MX_USART1_UART_Init();																// Настройка USART1
	MX_USART2_UART_Init();																// Настройка USART2 для Virtual COM-Port
	MX_USART3_UART_Init();																// Настройка USART3
	MX_UART4_Init();																	// Настройка UART4
	MX_UART5_Init();																	// Настройка UART5 терминальной связи с ПК

	MX_DAC_Init();																		// Настройка ЦАП для управления скоростью мотора
	MX_ADC_Init();																		// Настройка АЦП для измерения токов, напряжений, регулятора скорости
	MX_TIM3_Init();																		// Настройка для работы энкодера
	MX_TIM6_Init();																		// Настройка для работы динамика
	MX_TIM4_Init();																		// Настройка для работы тахометра оборотов бака
	MX_TIM9_Init();																		// Настройка для отладки FreeRTOS
	MX_TIM10_Init();																	// Настройка источника микросекундных тиков (для DelayUS() со сбросом ) нужен для 1-Wire DS18B20
	MX_TIM11_Init();																	// Настройка для ШИМ управления оборотами мотора вентилятора охлаждения контроллера двигателя

	DS18B20_Init();																		// Инициализация термодатчиков

	Encoder_Init();																		// Настройка энкодера (GPIO, Таймер, переменные)

	MX_FATFS_Init();																	// Настройка для работы с файлами на SD Card

	Keys_Init();																		// Настройка GPIO портов для кнопок
	Encoder_Init();																		// Настройка GPIO портов для энкодера

	FAN_Init();																			// Настройка ШИМ-управления для двигателя вентилятора ихлажения


	BUZZER_Init(BUZZER_STSTE_ON);														// Инициализация и включение пъезодинамика (пищалки/баззера)

  //  // фейковый трансмит для настройки SPI
  //  uint8_t data = 0;
  //  HAL_SPI_Transmit(&LCD_SPI, &data, 1, 10);

	HAL_Delay(100);
	LCD9488_Init();	   																	// Инициализаци экрана LCD ILI9488
	HAL_Delay(100);

	LCD9488_GUI_SetOrientation(1);														// Установка ориентации экрана
	HAL_Delay(100);



	//подключаем в единую структуру все данные от переферии
	ExchangeStruct.Encoder_State =			&Encoder_State;							// структура с информацией от энкодера


	EEPROM_OptionsLoad();																// чтение настроек по умолчанию и чтение сознаненных настроек из EEPROM

	BUZZER_Beep();



	// Рисуем начальную заставку на UART2
	printf("\033[2J"); 																	// Очистка окна терминала.   //https://www.linux.org.ru/forum/development/628620
	printf("\033[0;0H"); 																// задает абсолютные координаты курсора (строка, столбец)  // https://www.opennet.ru/base/dev/console_ctl.txt.html
	printf("Medogonka. Alex Shamilich\n");												// Строка приветствия
	printf("Version: %s\n", FIRMWARE_VER);
	printf("  Date: %s\n", __DATE__);
	printf("  Time: %s\n", __TIME__);
	printf("FreeRTOS, MircoRL, ADC, DAC, 1-Wire\n");
	printf("UART2->Virtual_COM\n");
	printf("UART5->MicroRL\n");
	printf("TIM4, TIM9, TIM10, TIM11 \n");
	printf("18B20, Encoder\n");


	fatfs_test();

//	main_test();																		// Тесты LCD

	osKernelInitialize();  																// Настройка планировщика FreeRTOS
	MX_FREERTOS_Init();																	// Настройка объектов FreeRTOS
	osKernelStart();																	// Запуск планировщика FreeRTOS



	// После старта планировщика сюда мы никогда не должны зайти, поэтому бесконечный цикл.
	while (1)
	{
	}
}
//======================================================================================
void SystemClock_Config(void)															// System Clock Configuration
{
	RCC_OscInitTypeDef RCC_OscInitStruct = {0};
	RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

	/** Configure the main internal regulator output voltage
	*/
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
	/** Initializes the RCC Oscillators according to the specified parameters
	* in the RCC_OscInitTypeDef structure.
	*/
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL12;
	RCC_OscInitStruct.PLL.PLLDIV = RCC_PLL_DIV3;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
	{
	Error_Handler(0);
	}
	/** Initializes the CPU, AHB and APB buses clocks
	*/
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
							  |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
	{
	Error_Handler(0);
	}
	HAL_RCC_MCOConfig(RCC_MCO1, RCC_MCO1SOURCE_SYSCLK, RCC_MCODIV_16);
}
//======================================================================================
/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM7 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if (htim->Instance == TIM4)
  {
	MotorSpeed_Period 	= 0;															// Если натикало больше чем период таймера (htim4.Init.Period), то считаем скорость мотора нулевой
  }

  if (htim->Instance == TIM7)
  {
    HAL_IncTick();
  }
  if (htim->Instance == TIM6)
  {
	BUZZER_INV;																			// меняем состояние пина баззера
  }

}
//======================================================================================
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	if (htim->Instance == TIM4)															// Считаем скорость по интервалу импульсов от датчика скорости
	{
		MotorSpeed_Period = __HAL_TIM_GET_COUNTER(&htim4);
		__HAL_TIM_SET_COUNTER(&htim4, 0);
	}

}
//======================================================================================
void Delay_for_errror(uint32_t ms) 														// должна работать вне зависимости от прерываний. Когда все рухнуло и нужно диодом показать код ошибки
{
    volatile uint32_t 	nCount;
    nCount = SystemCoreClock / 10000 * ms;
    for (; nCount!=0; nCount--);
}
//=======================================================================================
void Error_Handler(uint8_t err_num)														// Обработчик ошибок
{
  //gl_err_num = err_num;
  while(1)
  {
	LED_GREEN_SET;
	Delay_for_errror(500);
	LED_GREEN_RESET;
    Delay_for_errror(500);
    for(uint8_t i=0; i < err_num; ++i)
    {
    	LED_GREEN_SET;
    	Delay_for_errror(130);
    	LED_GREEN_RESET;
        Delay_for_errror(130);
    }
    Delay_for_errror(1000);
  }
}
//======================================================================================
#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
//======================================================================================
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
//======================================================================================


// строка программирования без GIT:
// -c SWD FREQ=4000 UR -P ${workspace_loc}\${project_path}\${config_name:${project_name}}\${project_name}.hex 0x08000000 -V after_programming -Q -Rst

// строка программирования после перехода на GIT:
// полный путь проекта не внутри воркспейса эклипса
// + привязка с синему программаторы
// -c SWD FREQ=4000 UR SN=53FF6E065088515355451387 -P ${project_loc}\${config_name:${project_name}}\${project_name}.hex 0x08000000 -V after_programming -Q -Rst


// http://m.blog.naver.com/jrkim/220625783320
