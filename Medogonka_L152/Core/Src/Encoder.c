/*
 * encoder.c
 *
 *  Created on: Oct 1, 2020
 *      Author: EN-E-01
 */

#include <Encoder.h>

//=======================================================================================
void  Encoder_Init(void)																	// Настройка GPIO портов для энкодера
{
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();
	__HAL_RCC_GPIOE_CLK_ENABLE();
	__HAL_RCC_GPIOH_CLK_ENABLE();


	GPIO_InitTypeDef GPIO_InitStruct;

	// ENC_BTN
	GPIO_InitStruct.Pin 		= ENC_BTN_Pin;
	GPIO_InitStruct.Mode 		= GPIO_MODE_IT_FALLING;
	GPIO_InitStruct.Pull 		= GPIO_NOPULL;
	GPIO_InitStruct.Speed		= GPIO_SPEED_FREQ_MEDIUM;
	HAL_GPIO_Init(ENC_BTN_GPIO_Port, &GPIO_InitStruct);

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


	 // включаем прерывания
	//  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 14, 0);
	//  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);


}
//=======================================================================================
