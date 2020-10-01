#include "dac.h"

DAC_HandleTypeDef hdac;

//======================================================================================
void MX_DAC_Init(void)
{
  DAC_ChannelConfTypeDef sConfig = {0};

  /** DAC Initialization
  */
  hdac.Instance = DAC;
  if (HAL_DAC_Init(&hdac) != HAL_OK)
  {
    Error_Handler();
  }
  /** DAC channel OUT1 config
  */
  sConfig.DAC_Trigger = DAC_TRIGGER_NONE;
  sConfig.DAC_OutputBuffer = DAC_OUTPUTBUFFER_ENABLE;
  if (HAL_DAC_ConfigChannel(&hdac, &sConfig, DAC_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }

}
//======================================================================================
void HAL_DAC_MspInit(DAC_HandleTypeDef* dacHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(dacHandle->Instance==DAC)
  {
    /* DAC clock enable */
    __HAL_RCC_DAC_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**DAC GPIO Configuration
    PA4     ------> DAC_OUT1
    */
    GPIO_InitStruct.Pin = DAC1__MOTOR_SPEED_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(DAC1__MOTOR_SPEED_GPIO_Port, &GPIO_InitStruct);

  }
}
//======================================================================================
void HAL_DAC_MspDeInit(DAC_HandleTypeDef* dacHandle)
{

  if(dacHandle->Instance==DAC)
  {
    /* Peripheral clock disable */
    __HAL_RCC_DAC_CLK_DISABLE();

    /**DAC GPIO Configuration
    PA4     ------> DAC_OUT1
    */
    HAL_GPIO_DeInit(DAC1__MOTOR_SPEED_GPIO_Port, DAC1__MOTOR_SPEED_Pin);
  }
}
//======================================================================================
