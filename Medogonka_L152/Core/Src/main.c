//======================================================================================
// File Name          : main.c
// Description        : Main program body
//======================================================================================
#define FIRMWARE_VER "0.0.1"
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
//

// I2C1 - подключение датчиков (MPU-6050,
// SPI1 - SD Карта
// SPI2 - LCD экран ILI9488
// UART порты:
// 		UART1:
// 		UART2:	Virtual COM-Port возможность вывода сообщений с помощью простого printf (переопределен putc и заглушки к stdlib)
// 		UART3:
// 		UART4:  терминальная связь с ПК
// 		UART5:
// Таймеры:
//		TIM2	отключен
//		TIM3	обслуживание энкодера для меню
//		TIM4	магнитный датчик оборотов бака
//		TIM5	отключен
//		TIM6	отключен
//		TIM7	источник тиков для FreeRTOS
//		TIM9	отключен
//		TIM10	отключен
//		TIM11	ШИМ управление оборотами мотора вентилятора охлаждения контроллера двигателя


//======================================================================================
#include "main.h"

#include "cmsis_os.h"
#include "adc.h"
#include "dac.h"
#include "dma.h"
#include "fatfs.h"
#include "i2c.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "usb_device.h"
#include "gpio.h"


#include "LCD_ili9488_test.h"

void SystemClock_Config(void);
void MX_FREERTOS_Init(void);
//======================================================================================
int main(void)
{
	HAL_Init();
	SystemClock_Config();

	MX_GPIO_Init();
	MX_DMA_Init();
	MX_SPI1_Init();
	MX_SPI2_Init();
	MX_I2C1_Init();
	MX_USART1_UART_Init();
	MX_DAC_Init();
	MX_FATFS_Init();
	MX_ADC_Init();
	MX_TIM3_Init();
	MX_TIM4_Init();
	MX_TIM11_Init();
	MX_UART4_Init();
	MX_UART5_Init();
	MX_USART2_UART_Init();
	MX_USART3_UART_Init();

  //  // фейковый трансмит для настройки SPI
  //  uint8_t data = 0;
  //  HAL_SPI_Transmit(&LCD_SPI, &data, 1, 10);

	HAL_Delay(100);
	LCD9488_Init();	   // Инициализаци экрана
	HAL_Delay(100);

	LCD9488_GUI_SetOrientation(1);
	HAL_Delay(100);

	main_test();																		// Тесты LCD

	osKernelInitialize();  																// Init scheduler  Call init function for freertos objects (in freertos.c)
	MX_FREERTOS_Init();
	osKernelStart();																	// Start scheduler

	/* We should never get here as control is now taken by the scheduler */
	/* Infinite loop */
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

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
	{
	Error_Handler();
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
  if (htim->Instance == TIM7)
  {
    HAL_IncTick();
  }
}
//======================================================================================
void Error_Handler(void)																// This function is executed in case of error occurrence.
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
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
