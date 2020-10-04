#include <DAC.h>

DAC_HandleTypeDef DacHandle;

//======================================================================================
void MX_DAC_Init(void)
{
  DAC_ChannelConfTypeDef sConfig = {0};

  /** DAC Initialization
  */
  DacHandle.Instance = DAC;
  if (HAL_DAC_Init(&DacHandle) != HAL_OK)
  {
    Error_Handler(3);
  }
  /** DAC channel OUT1 config
  */
  sConfig.DAC_Trigger = DAC_TRIGGER_NONE;
  sConfig.DAC_OutputBuffer = DAC_OUTPUTBUFFER_ENABLE;
  if (HAL_DAC_ConfigChannel(&DacHandle, &sConfig, DACx_CHANNEL) != HAL_OK)
  {
    Error_Handler(3);
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
void DAC_SetValue(uint8_t AValue)														// Установка значения в ЦАП
{
	if (HAL_DAC_SetValue(&DacHandle, DACx_CHANNEL, DAC_ALIGN_8B_R, (uint32_t)AValue) != HAL_OK)
	{
	  Error_Handler(21);//Setting value Error
	}

	if (HAL_DAC_Start(&DacHandle, DACx_CHANNEL) != HAL_OK)
	{
	  Error_Handler(21);//Start Error
	}

}
//======================================================================================
