#include <ADC.h>
#include "ADC_Ext.h"


ADC_HandleTypeDef hadc;

//======================================================================================
void MX_ADC_Init(void)
{
  ADC_ChannelConfTypeDef sConfig = {0};

  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
  */
  hadc.Instance = ADC1;
  hadc.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV1;
  hadc.Init.Resolution = ADC_RESOLUTION_12B;
  hadc.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc.Init.ScanConvMode = ADC_SCAN_DISABLE;
  hadc.Init.EOCSelection = ADC_EOC_SEQ_CONV;
  hadc.Init.LowPowerAutoWait = ADC_AUTOWAIT_DISABLE;
  hadc.Init.LowPowerAutoPowerOff = ADC_AUTOPOWEROFF_DISABLE;
  hadc.Init.ChannelsBank = ADC_CHANNELS_BANK_A;
  hadc.Init.ContinuousConvMode = DISABLE;
  hadc.Init.NbrOfConversion = 1;
  hadc.Init.DiscontinuousConvMode = DISABLE;
  hadc.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc.Init.DMAContinuousRequests = DISABLE;
  if (HAL_ADC_Init(&hadc) != HAL_OK)
  {
    Error_Handler(2);
  }
  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_TEMPSENSOR;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_4CYCLES;
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
  {
    Error_Handler(2);
  }

}
//======================================================================================
void HAL_ADC_MspInit(ADC_HandleTypeDef* adcHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(adcHandle->Instance==ADC1)
  {
    /* ADC1 clock enable */
    __HAL_RCC_ADC1_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOE_CLK_ENABLE();

    /**ADC GPIO Configuration
    PA0-WKUP1     ------> ADC_IN0
    PA1     ------> ADC_IN1
    PC5     ------> ADC_IN15
    PE8     ------> ADC_IN23
    PE9     ------> ADC_IN24
    */
    GPIO_InitStruct.Pin = ADC_V_MOTOR_Pin|ADC_V_IN_12V_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = ADC_SPEED_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(ADC_SPEED_GPIO_Port, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = ADC_I_IN_12V_Pin|ADC_I_MOTOR_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

    /* ADC1 interrupt Init */
    HAL_NVIC_SetPriority(ADC1_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(ADC1_IRQn);

  }
}
//======================================================================================

void HAL_ADC_MspDeInit(ADC_HandleTypeDef* adcHandle)
{

  if(adcHandle->Instance==ADC1)
  {
    /* Peripheral clock disable */
    __HAL_RCC_ADC1_CLK_DISABLE();

    /**ADC GPIO Configuration
    PA0-WKUP1     ------> ADC_IN0
    PA1     ------> ADC_IN1
    PC5     ------> ADC_IN15
    PE8     ------> ADC_IN23
    PE9     ------> ADC_IN24
    */
    HAL_GPIO_DeInit(GPIOA, ADC_V_MOTOR_Pin|ADC_V_IN_12V_Pin);

    HAL_GPIO_DeInit(ADC_SPEED_GPIO_Port, ADC_SPEED_Pin);

    HAL_GPIO_DeInit(GPIOE, ADC_I_IN_12V_Pin|ADC_I_MOTOR_Pin);

    /* ADC1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(ADC1_IRQn);
  }
}
//======================================================================================
uint32_t ADC_GetRAWData(uint32_t Channel)												// Получить сырые данные для обрботки по указанному каналу
{
	ADC_ChannelConfTypeDef sConfig = {0};

	sConfig.Rank         = ADC_REGULAR_RANK_1;
	sConfig.SamplingTime = ADC_SAMPLETIME_16CYCLES;

	sConfig.Channel      = Channel;
 	if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
	{
		Error_Handler(2);
	}

	// Замер из АЦП
	HAL_ADC_Start(&hadc);
	HAL_ADC_PollForConversion(&hadc, 10);
	ADC_State.ADC_RAW = HAL_ADC_GetValue(&hadc);
	HAL_ADC_Stop(&hadc);

	return ADC_State.ADC_RAW;
}
//======================================================================================
void ADC_ScanState(void)																// Замер из АЦП по всем каналам сразу
{
	// Распределение каналов АЦП:
	// ADC Channel: IN0							- ADC_V_MOTOR
	// ADC Channel: IN1							- ADC_V_IN_12V
	// ADC Channel: IN15						- ADC_SPEED
	// ADC Channel: IN23						- ADC_I_IN_12V
	// ADC Channel: IN24						- ADC_I_MOTOR
	// ADC Channel: Temperature Sensor Channel 	- температура кристалла процессора
	// ADC Channel: Vrefint Channel				- Напряжение питания, для рассчетов опоры

	ADC_State.DataReady = 0;


	ADC_GetRAWData(ADC_CHANNEL_VREFINT);												// Канал АЦП - опорное напряжение для рассчета напряжения питания процессора
	if (ADC_State.ADC_RAW < 4096)
	{
		// Реальное напряжение питания процессора, точнее питание аналоговой части
		ADC_State.ADC_Ref_Voltage = __LL_ADC_CALC_VREFANALOG_VOLTAGE(ADC_State.ADC_RAW, hadc.Init.Resolution) / 1000.0; // калибровка батареи - опорное напряжение АЦП
		ADC_State.DataReady++;
	}

	ADC_GetRAWData(ADC_CHANNEL_TEMPSENSOR);												// Канал АЦП - температура внутри процессора
	if (ADC_State.ADC_RAW < 4096)
	{
		// Пересчет  сырых данных АЦП в температуру в градусах Цельсия, без учета реального напряжения питания
		ADC_State.CPU_Temperature 	= COMPUTATION_TEMPERATURE_TEMP30_TEMP110(ADC_State.ADC_RAW) - 2;

//		// Пересчет  сырых данных АЦП в температуру в градусах Цельсия, с учетом реального опопрного напряжения питания
//		ADC_State.CPU_Temperature_raw 	= __LL_ADC_CALC_DATA_TO_VOLTAGE(ADC_State.ADC_Ref_Voltage, ADC_State.ADC_RAW, hadc.Init.Resolution);  // пересчет из сырых данных АЦП в напряжение в вольтах с учетом разрядности
//		ADC_State.CPU_TemperatureRef    = __LL_ADC_CALC_TEMPERATURE((uint32_t)(1000*ADC_State.ADC_Ref_Voltage), ADC_State.ADC_RAW , hadc.Init.Resolution) - 2;

		ADC_State.DataReady++;
	}

	ADC_GetRAWData(CHANNEL_ADC_SPEED);													// Канал АЦП - регулятор скорости мотора (пременный резистор 0..3.3V)
	if (ADC_State.ADC_RAW < 4096)
	{
		ADC_State.Speed_value_volts 	= ADC_State.ADC_RAW * (ADC_REF_VOLTAGE_DEFAULT / 4096) * DIVIDER_ADC_SPEED;
		ADC_State.Speed_value_percent	= (uint8_t)( (ADC_State.Speed_value_volts/ADC_REF_VOLTAGE_DEFAULT)*(double)100 );
		Speed_value_percent = ADC_State.Speed_value_percent;

		ADC_State.DataReady++;
	}

	ADC_GetRAWData(CHANNEL_ADC_V_IN_12V);												// Канал АЦП - напряжение питания на входе
	if (ADC_State.ADC_RAW < 4096)
	{
		ADC_State.V_IN_12V_value_volts 	= ADC_State.ADC_RAW * (ADC_REF_VOLTAGE_DEFAULT / 4096) * DIVIDER_ADC_V_IN_12V;

		ADC_State.DataReady++;
	}

	ADC_GetRAWData(CHANNEL_ADC_V_MOTOR);												// Канал АЦП - напряжение питания мотора (среднее)
	if (ADC_State.ADC_RAW < 4096)
	{
		ADC_State.V_IN_MOTOR_value_volts 	= ADC_State.ADC_RAW * (ADC_REF_VOLTAGE_DEFAULT / 4096) * DIVIDER_ADC_V_MOTOR;

		ADC_State.DataReady++;
	}

	ADC_GetRAWData(CHANNEL_ADC_I_IN_12V);												// Канал АЦП - общий входной ток
	if (ADC_State.ADC_RAW < 4096)
	{
		ADC_State.I_IN_12V_value_amperes 	= ADC_State.ADC_RAW * (ADC_REF_VOLTAGE_DEFAULT / 4096) * DIVIDER_ADC_I_IN_12V;

		ADC_State.DataReady++;
	}

	ADC_GetRAWData(CHANNEL_ADC_I_MOTOR);												// Канал АЦП - ток мотора
	if (ADC_State.ADC_RAW < 4096)
	{
		ADC_State.I_IN_MOTOR_value_amperes 	= ADC_State.ADC_RAW * (ADC_REF_VOLTAGE_DEFAULT / 4096) * DIVIDER_ADC_I_MOTOR;

		ADC_State.DataReady++;
	}

}
//=======================================================================================
