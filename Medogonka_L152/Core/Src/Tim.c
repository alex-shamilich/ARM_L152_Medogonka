#include "tim.h"

TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim4;
TIM_HandleTypeDef htim6;
TIM_HandleTypeDef htim11;

//======================================================================================
void MX_TIM3_Init(void)
{
  TIM_Encoder_InitTypeDef sConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 0;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 100;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  sConfig.EncoderMode = TIM_ENCODERMODE_TI1;
  sConfig.IC1Polarity = TIM_ICPOLARITY_RISING;
  sConfig.IC1Selection = TIM_ICSELECTION_DIRECTTI;
  sConfig.IC1Prescaler = TIM_ICPSC_DIV1;
  sConfig.IC1Filter = 0;
  sConfig.IC2Polarity = TIM_ICPOLARITY_RISING;
  sConfig.IC2Selection = TIM_ICSELECTION_DIRECTTI;
  sConfig.IC2Prescaler = TIM_ICPSC_DIV1;
  sConfig.IC2Filter = 0;
  if (HAL_TIM_Encoder_Init(&htim3, &sConfig) != HAL_OK)
  {
    Error_Handler(4);
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler(4);
  }

}
//======================================================================================
void MX_TIM4_Init(void)
{
  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  htim4.Instance = TIM4;
  htim4.Init.Prescaler = 0;
  htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim4.Init.Period = 65535;
  htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV4;
  htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim4) != HAL_OK)
  {
    Error_Handler(4);
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim4, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler(4);
  }
  if (HAL_TIM_OC_Init(&htim4) != HAL_OK)
  {
    Error_Handler(4);
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig) != HAL_OK)
  {
    Error_Handler(4);
  }
  sConfigOC.OCMode = TIM_OCMODE_ACTIVE;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_OC_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler(4);
  }
  HAL_TIM_MspPostInit(&htim4);

}
//======================================================================================
void MX_TIM6_Init(void)
{
	// Инициализация в модуле Buzzer_TIM

//  TIM_MasterConfigTypeDef sMasterConfig = {0};
//
//  htim6.Instance = TIM6;
//  htim6.Init.Prescaler = 0;
//  htim6.Init.CounterMode = TIM_COUNTERMODE_UP;
//  htim6.Init.Period = 65535;
//  htim6.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
//  if (HAL_TIM_Base_Init(&htim6) != HAL_OK)
//  {
//    Error_Handler(4);
//  }
//  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
//  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
//  if (HAL_TIMEx_MasterConfigSynchronization(&htim6, &sMasterConfig) != HAL_OK)
//  {
//    Error_Handler(4);
//  }
//
}
//======================================================================================
void MX_TIM11_Init(void)
{
  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  htim11.Instance = TIM11;
  htim11.Init.Prescaler = 0;
  htim11.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim11.Init.Period = 100;
  htim11.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim11.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim11) != HAL_OK)
  {
    Error_Handler(4);
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim11, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler(4);
  }
  if (HAL_TIM_PWM_Init(&htim11) != HAL_OK)
  {
    Error_Handler(4);
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim11, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler(4);
  }
  HAL_TIM_MspPostInit(&htim11);

}
//======================================================================================
void HAL_TIM_Encoder_MspInit(TIM_HandleTypeDef* tim_encoderHandle)
{

//  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(tim_encoderHandle->Instance==TIM3)
  {
    /* TIM3 clock enable */
    __HAL_RCC_TIM3_CLK_ENABLE();

//    __HAL_RCC_GPIOE_CLK_ENABLE();
//    /**TIM3 GPIO Configuration
//    PE3     ------> TIM3_CH1
//    PE4     ------> TIM3_CH2
//    */
//    GPIO_InitStruct.Pin = ENC_A_Pin|ENC_B_Pin;
//    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
//    GPIO_InitStruct.Pull = GPIO_NOPULL;
//    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
//    GPIO_InitStruct.Alternate = GPIO_AF2_TIM3;
//    HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

    /* TIM3 interrupt Init */
    HAL_NVIC_SetPriority(TIM3_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(TIM3_IRQn);
  }
}
//======================================================================================
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* tim_baseHandle)
{

  if(tim_baseHandle->Instance==TIM4)
  {
    /* TIM4 clock enable */
    __HAL_RCC_TIM4_CLK_ENABLE();
  }
  if(tim_baseHandle->Instance==TIM6)
  {
    /* TIM6 clock enable */
    __HAL_RCC_TIM6_CLK_ENABLE();

    /* TIM6 interrupt Init */
    HAL_NVIC_SetPriority(TIM6_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(TIM6_IRQn);

  }
  else if(tim_baseHandle->Instance==TIM11)
  {
    /* TIM11 clock enable */
    __HAL_RCC_TIM11_CLK_ENABLE();
  }
}
//======================================================================================
void HAL_TIM_MspPostInit(TIM_HandleTypeDef* timHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(timHandle->Instance==TIM4)
  {
    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**TIM4 GPIO Configuration
    PB6     ------> TIM4_CH1
    */
    GPIO_InitStruct.Pin = SNS_HALL_IN_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF2_TIM4;
    HAL_GPIO_Init(SNS_HALL_IN_GPIO_Port, &GPIO_InitStruct);
  }
  else if(timHandle->Instance==TIM11)
  {
    __HAL_RCC_GPIOE_CLK_ENABLE();
    /**TIM11 GPIO Configuration
    PE1     ------> TIM11_CH1
    */
    GPIO_InitStruct.Pin = PWM_COOLING_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF3_TIM11;
    HAL_GPIO_Init(PWM_COOLING_GPIO_Port, &GPIO_InitStruct);
  }

}
//======================================================================================
void HAL_TIM_Encoder_MspDeInit(TIM_HandleTypeDef* tim_encoderHandle)
{
  if(tim_encoderHandle->Instance==TIM3)
  {
    /* Peripheral clock disable */
    __HAL_RCC_TIM3_CLK_DISABLE();

//    /**TIM3 GPIO Configuration
//    PE3     ------> TIM3_CH1
//    PE4     ------> TIM3_CH2
//    */
//    HAL_GPIO_DeInit(GPIOE, ENC_A_Pin|ENC_B_Pin);

    /* TIM3 interrupt Deinit */
    HAL_NVIC_DisableIRQ(TIM3_IRQn);
  }
}
//======================================================================================
void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef* tim_baseHandle)
{
  if(tim_baseHandle->Instance==TIM4)
  {
    /* Peripheral clock disable */
    __HAL_RCC_TIM4_CLK_DISABLE();
  }
  else if(tim_baseHandle->Instance==TIM6)
  {
    /* Peripheral clock disable */
    __HAL_RCC_TIM6_CLK_DISABLE();
  }
  else if(tim_baseHandle->Instance==TIM11)
  {
    /* Peripheral clock disable */
    __HAL_RCC_TIM11_CLK_DISABLE();
  }
}
//======================================================================================
