// Buzzer routines
// Author: Alex Shamilich
//
// необходимо установить правильный порт в заголовочном файле

#include "Buzzer_TIM.h"
#include "Freertos.h"
#include "cmsis_os.h"

uint8_t			BUZZER_BuzzerState;														// состояние баззера (включен/выключен)

//======================================================================================
void BUZZER_Init(uint8_t state)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();
	__HAL_RCC_GPIOE_CLK_ENABLE();
	__HAL_RCC_GPIOH_CLK_ENABLE();

	HAL_GPIO_WritePin(BUZZER_GPIO_Port, BUZZER_Pin, GPIO_PIN_RESET);

	__HAL_RCC_GPIOA_CLK_ENABLE();
	GPIO_InitStruct.Pin 		= BUZZER_Pin;
	GPIO_InitStruct.Mode 		= GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull 		= GPIO_PULLDOWN;
	GPIO_InitStruct.Speed 		= GPIO_SPEED_FREQ_LOW;


	HAL_GPIO_Init(BUZZER_GPIO_Port, &GPIO_InitStruct);
	BUZZER_BuzzerState = state;


	TIM_MasterConfigTypeDef sMasterConfig;

	htim6.Instance 				= TIM6;
	htim6.Init.Prescaler 		= 32;
	htim6.Init.Period 			= BUZZER_HALF_PERIOD_TIM;
	htim6.Init.CounterMode 		= TIM_COUNTERMODE_UP;
	htim6.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	if (HAL_TIM_Base_Init(&htim6) != HAL_OK)
	{
		Error_Handler(4);
	}

	sMasterConfig.MasterOutputTrigger 	= TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode 		= TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&htim6, &sMasterConfig) != HAL_OK)
	{
		Error_Handler(4);
	}

	HAL_TIM_Base_MspInit(&htim6);														// Настройка прерываний для таймера

	HAL_TIM_MspPostInit(&htim6);

}
//======================================================================================
void BUZZER_Beep(void) 																	// Generates one short beep in RealMode with stupid waiting
{
//	htim6.Init.Period = 100;
//	HAL_TIM_Base_Init(&htim6);
	if (BUZZER_BuzzerState == BUZZER_STSTE_ON)
	{
		uint16_t len = BUZZER_NUM_HALF_PERIOD_NORM;
		while (len--)
		{
			BUZZER_INV;
			HAL_Delay(BUZZER_HALF_PERIOD);
		}
		BUZZER_OFF;
	}
}
//======================================================================================
void BUZZER_BeepTIM(void) 																// Generates one short beep under RTOS
{
	if (BUZZER_BuzzerState == BUZZER_STSTE_ON)
	{
		HAL_TIM_Base_Start_IT(&htim6);													// Запуск тааймера, на обработчике состояния таймера - смена состояния пина баззера
		osDelay(BUZZER_NUM_HALF_PERIOD_NORM);											// если задержка через планировщик RTOS (минимум 1мс)
	//	HAL_Delay(BUZZER_NUM_HALF_PERIOD_NORM);											// если задержка через HAL (минимум 1мс)
		HAL_TIM_Base_Stop_IT(&htim6);
		BUZZER_OFF;
	}
}
//======================================================================================
void BUZZER_Beep_Tick(void) 															// Generates one very-very short beep
{
	if (BUZZER_BuzzerState == BUZZER_STSTE_ON)
	{
		uint16_t len = BUZZER_NUM_HALF_PERIOD_SHORT/4;
		while (len--)
		{
			BUZZER_INV;
			HAL_Delay(BUZZER_HALF_PERIOD);
		}
		BUZZER_OFF;
	}
}
//======================================================================================
void BUZZER_Beep_TickTIM(void)															// Generates one very-very short beep
{
	if (BUZZER_BuzzerState == BUZZER_STSTE_ON)
	{
		HAL_TIM_Base_Start_IT(&htim6);													// Запуск тааймера, на обработчике состояния таймера - смена состояния пина баззера
		osDelay(BUZZER_NUM_HALF_PERIOD_SHORT/4);										// если задержка через планировщик RTOS (минимум 1мс)
	//	HAL_Delay(BUZZER_NUM_HALF_PERIOD_SHORT/4);										// если задержка через HAL (минимум 1мс)
		HAL_TIM_Base_Stop_IT(&htim6);
		BUZZER_OFF;
	}
}
//======================================================================================
void BUZZER_Beep_Short(void) 															// Generates one very short beep
{
	if (BUZZER_BuzzerState == BUZZER_STSTE_ON)
	{
		uint16_t len = BUZZER_NUM_HALF_PERIOD_SHORT;
		while (len--)
		{
			BUZZER_INV;
			HAL_Delay(BUZZER_HALF_PERIOD);
		}
		BUZZER_OFF;
	}
}
//======================================================================================
void BUZZER_Beep_ShortTIM(void) 														// Generates one very short beep
{
	if (BUZZER_BuzzerState == BUZZER_STSTE_ON)
	{
		HAL_TIM_Base_Start_IT(&htim6);													// Запуск тааймера, на обработчике состояния таймера - смена состояния пина баззера
		osDelay(BUZZER_NUM_HALF_PERIOD_SHORT);											// если задержка через планировщик RTOS (минимум 1мс)
	//	HAL_Delay(BUZZER_NUM_HALF_PERIOD_SHORT);										// если задержка через HAL (минимум 1мс)
		HAL_TIM_Base_Stop_IT(&htim6);
		BUZZER_OFF;
	}
}
//======================================================================================
void BUZZER_Beep_Dbl(void) 																// Generates 2 short beeps
{
	if (BUZZER_BuzzerState == BUZZER_STSTE_ON)
	{
		BUZZER_Beep_Short();
		HAL_Delay(BUZZER_DELAY);
		BUZZER_Beep_Short();
	}
}
//======================================================================================
void BUZZER_Beep_DblTIM(void) 															// Generates 2 short beeps
{
	if (BUZZER_BuzzerState == BUZZER_STSTE_ON)
	{
		BUZZER_Beep_ShortTIM();
		osDelay(BUZZER_DELAY);
		BUZZER_Beep_ShortTIM();
	}
}
//======================================================================================
void BUZZER_Beep_Tri(void) 																// Generates 3 short beeps
{
	if (BUZZER_BuzzerState == BUZZER_STSTE_ON)
	{
		BUZZER_Beep_Short();
		HAL_Delay(BUZZER_DELAY);
		BUZZER_Beep_Short();
		HAL_Delay(BUZZER_DELAY);
		BUZZER_Beep_Short();
	}
}
//======================================================================================
void BUZZER_Beep_TriTIM(void) 															// Generates 3 short beeps
{
	if (BUZZER_BuzzerState == BUZZER_STSTE_ON)
	{
		BUZZER_Beep_ShortTIM();
		osDelay(BUZZER_DELAY);
		BUZZER_Beep_ShortTIM();
		osDelay(BUZZER_DELAY);
		BUZZER_Beep_ShortTIM();
	}
}
//======================================================================================
// http://mcustep.ru/init/stm32f4/44-stm32f4-delay-realizatsiya-zaderzhek.html
// http://www.carminenoviello.com/2015/09/04/precisely-measure-microseconds-stm32/
