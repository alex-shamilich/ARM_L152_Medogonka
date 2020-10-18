// Работа с механическим инкрементальным энкодером
// на аппаратном таймере TIM3 в режиме энкодера
#include <Encoder.h>
#include "tim.h"
//=======================================================================================
void  Encoder_Init(void)																// Настройка GPIO портов для энкодера
{
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();
	__HAL_RCC_GPIOE_CLK_ENABLE();
	__HAL_RCC_GPIOH_CLK_ENABLE();

	GPIO_InitTypeDef GPIO_InitStruct;

	// ENC_A
    GPIO_InitStruct.Pin 		= ENC_A_Pin;
    GPIO_InitStruct.Mode 		= GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull 		= GPIO_NOPULL;
    GPIO_InitStruct.Speed 		= GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate 	= GPIO_AF2_TIM3;
    HAL_GPIO_Init(ENC_A_GPIO_Port, &GPIO_InitStruct);

	// ENC_B
    GPIO_InitStruct.Pin 		= ENC_B_Pin;
    GPIO_InitStruct.Mode 		= GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull 		= GPIO_NOPULL;
    GPIO_InitStruct.Speed 		= GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF2_TIM3;
    HAL_GPIO_Init(ENC_B_GPIO_Port, &GPIO_InitStruct);

	// ENC_BTN
	GPIO_InitStruct.Pin 		= ENC_BTN_Pin;
	GPIO_InitStruct.Mode 		= GPIO_MODE_IT_FALLING;
	GPIO_InitStruct.Pull 		= GPIO_NOPULL;
	GPIO_InitStruct.Speed		= GPIO_SPEED_FREQ_MEDIUM;
	HAL_GPIO_Init(ENC_BTN_GPIO_Port, &GPIO_InitStruct);


	// включаем прерывания
	//  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 14, 0);
	//  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

    MX_TIM3_Init();																		// Настройка таймера TIM3 для работы с энкодером
    Encoder_Start();																	// Начальная установка для энкодера
}
//=======================================================================================

//=======================================================================================
void Encoder_Start(void)																// Начальная установка для энкодера
{
	Encoder_State.MP_Encoder_Value 				= ENCODER_VAL_DEFAULT;
	Encoder_State.MP_Encoder_Value_old 			= ENCODER_VAL_DEFAULT;
//	Encoder_State.MP_Encoder_Value_prev 		= ENCODER_VAL_DEFAULT;
	__HAL_TIM_SET_COUNTER(&htim3, Encoder_State.MP_Encoder_Value);
	HAL_TIM_Encoder_Start_IT(&htim3, TIM_CHANNEL_ALL);
}
//=======================================================================================
void Encoder_Stop(void)																	// Остановка энкодера
{
	Encoder_State.MP_Encoder_Value 				= ENCODER_VAL_DEFAULT;
	Encoder_State.MP_Encoder_Value_old 			= ENCODER_VAL_DEFAULT;
//	Encoder_State.MP_Encoder_Value_prev 		= ENCODER_VAL_DEFAULT;
	__HAL_TIM_SET_COUNTER(&htim3, Encoder_State.MP_Encoder_Value);
	HAL_TIM_Encoder_Stop_IT(&htim3, TIM_CHANNEL_ALL);
}
//=======================================================================================
uint8_t Encoder_Scan(void)																// Сканировать состояние энкодера
{
	Encoder_State.MP_Encoder_Value 				= __HAL_TIM_GET_COUNTER(&htim3);
	Encoder_State.MP_Encoder_Dir 				= __HAL_TIM_IS_TIM_COUNTING_DOWN(&htim3);
	Encoder_State.MP_Encoder_Delta				= Encoder_State.MP_Encoder_Value - Encoder_State.MP_Encoder_Value_old;
	Encoder_State.fEncoder3Changes				= ( Encoder_State.MP_Encoder_Delta != 0 );
	Encoder_State.Btn_pressed					= ENC_BTN_PRESSED;

	if (Encoder_State.fEncoder3Changes)
	{
		Encoder_State.MP_Encoder_Value_old = Encoder_State.MP_Encoder_Value;			// обновить предыдущее состояние энкодера для следующего цикла сканирования
	}

	return Encoder_State.fEncoder3Changes;
}
//=======================================================================================


