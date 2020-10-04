/*
 * keys.c
 *
 *  Created on: Oct 1, 2020
 *      Author: EN-E-01
 */
#include "keys.h"

//=======================================================================================
void  Keys_Init(void)																	// Настройка GPIO портов для кнопок
{
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();
	__HAL_RCC_GPIOE_CLK_ENABLE();
	__HAL_RCC_GPIOH_CLK_ENABLE();


	GPIO_InitTypeDef GPIO_InitStruct;


	// BTN_START
	GPIO_InitStruct.Pin 		= BTN_START_Pin;
	GPIO_InitStruct.Mode 		= GPIO_MODE_IT_FALLING;
	GPIO_InitStruct.Pull 		= GPIO_NOPULL;
	GPIO_InitStruct.Speed		= GPIO_SPEED_FREQ_MEDIUM;
	HAL_GPIO_Init(BTN_START_GPIO_Port, &GPIO_InitStruct);


	// BTN_STOP
	GPIO_InitStruct.Pin 		= BTN_STOP_Pin;
	GPIO_InitStruct.Mode 		= GPIO_MODE_IT_FALLING;
	GPIO_InitStruct.Pull 		= GPIO_NOPULL;
	GPIO_InitStruct.Speed		= GPIO_SPEED_FREQ_MEDIUM;
	HAL_GPIO_Init(BTN_STOP_GPIO_Port, &GPIO_InitStruct);

	// BTN_MOTOR
	GPIO_InitStruct.Pin 		= BTN_MOTOR_Pin;
	GPIO_InitStruct.Mode 		= GPIO_MODE_IT_FALLING;
	GPIO_InitStruct.Pull 		= GPIO_NOPULL;
	GPIO_InitStruct.Speed		= GPIO_SPEED_FREQ_MEDIUM;
	HAL_GPIO_Init(BTN_MOTOR_GPIO_Port, &GPIO_InitStruct);

	// Вход переключателя МОТОР ВПЕРЕД
	GPIO_InitStruct.Pin 		= BTN_FWD_Pin;
	GPIO_InitStruct.Mode 		= GPIO_MODE_IT_FALLING;
	GPIO_InitStruct.Pull 		= GPIO_NOPULL;
	GPIO_InitStruct.Speed		= GPIO_SPEED_FREQ_MEDIUM;
	HAL_GPIO_Init(BTN_FWD_GPIO_Port, &GPIO_InitStruct);

	// Вход переключателя МОТОР НАЗАД
	GPIO_InitStruct.Pin 		= BTN_BWD_Pin;
	GPIO_InitStruct.Mode 		= GPIO_MODE_IT_FALLING;
	GPIO_InitStruct.Pull 		= GPIO_NOPULL;
	GPIO_InitStruct.Speed		= GPIO_SPEED_FREQ_MEDIUM;
	HAL_GPIO_Init(BTN_BWD_GPIO_Port, &GPIO_InitStruct);




	 // включаем прерывания
	//  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 14, 0);
	//  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);


}
//=======================================================================================

