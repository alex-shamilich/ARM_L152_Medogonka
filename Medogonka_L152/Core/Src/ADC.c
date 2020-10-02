#include <ADC.h>

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
//const double MP_Battery_Levels[6] = {3.72, 3.79, 3.88, 3.91, 4.01, 4.15};				// Уровни АЦП для прорисовки батарей
const double MP_Battery_Levels[6] = {2.6, 2.9, 3.2, 3.5, 4.00, 4.15};				// Уровни АЦП для прорисовки батарей //todo: тестово, чтобы всю шкалу резистором перекрутить!
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

	ADC_ChannelConfTypeDef sConfig = {0};

// из ЛДН	(STM32L152)
	Battery_State.DataReady = 0;

	sConfig.Rank         = ADC_REGULAR_RANK_1;          /* Rank of sampled channel number ADCx_CHANNEL */
	sConfig.SamplingTime = ADC_SAMPLETIME_4CYCLES;

	// Замер из АЦП Vref для определения напряжения питания
	sConfig.Channel      = CHANNEL_ADC_SPEED;      	// Канал АЦП - регулятор скорости мотора (пременный резистор 0..3.3V)
 	if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
	{
		Error_Handler(10);
	}


	// Замер из АЦП
	HAL_ADC_Start(&hadc);
	HAL_ADC_PollForConversion(&hadc, 100);

	Battery_State.ADC_RAW = HAL_ADC_GetValue(&hadc);

	HAL_ADC_Stop(&hadc);

	// Обработка значений
	if (Battery_State.ADC_RAW < 4096)
	{

		Battery_State.battery_raw_volts 	= Battery_State.ADC_RAW * (Battery_State.ADC_Ref_Voltage / 4096);
		Battery_State.battery_cell_volts 	= (Battery_State.ADC_12V_Voltage * Battery_State.battery_raw_volts ) / 4;			// напряжение в пересчете на 1 банку
		Battery_State.battery_level 		= 0;

		for (uint8_t i=0; i<6; i++)
		{
			if (Battery_State.battery_cell_volts > MP_Battery_Levels[i])
			{
				Battery_State.battery_level++;
			}
		}
//		Voltage = (double)((double)Volt * 0.00325 + 0.34);	// аппроксимация для 2х литиевых батарей

		Battery_State.DataReady = 1;
	}








//	// из LRF (STM32L432)
//
////	ADC_ChannelConfTypeDef sConfig = {0};
//	ADC_State.DataReady = 0;
//	uint16_t ADC_RAW;
//
////	DBG_PIN_LED_GREEN_SET;
//
//	sConfig.Rank         = ADC_REGULAR_RANK_1;          /* Rank of sampled channel number ADCx_CHANNEL */
//	sConfig.SamplingTime = ADC_SAMPLETIME_4CYCLES;
//
//	// Замер из АЦП Vref для определения напряжения питания
//	sConfig.Channel      = ADC_CHANNEL_VREFINT;      	// Канал АЦП - источник опорного напряжения
// 	if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
//	{
//		Error_Handler(10);
//	}
//	HAL_ADC_Start(&hadc);
//	HAL_ADC_PollForConversion(&hadc, 10);
//	ADC_RAW = HAL_ADC_GetValue(&hadc);
//	HAL_ADC_Stop(&hadc);
//
//	// Реальное напряжение питания процессора, точнее питание аналоговой части
//	ADC_State.ADC_Ref_Voltage = __LL_ADC_CALC_VREFANALOG_VOLTAGE(ADC_RAW, hadc.Init.Resolution) / 1000.0; // калибровка батареи - опорное напряжение АЦП
//
//
//
//	// Анализ напряжения на батарее
//	ADC_State.LOW_BATT		  = 0;									// Статус зизкого заряда АКБ перед выключением (1=напряжение ниже порога работы, 0=норма)
//
//	// Замер из АЦП для батареи
//	sConfig.Channel      = ADC_CHANNEL_6;               	// Канал АЦП - аналоговый вход АЦП (ADIN1)
//	if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
//	{
//		Error_Handler(10);
//	}
//	HAL_ADC_Start(&hadc);
//	HAL_ADC_PollForConversion(&hadc, 10);
//	ADC_State.ADC_RAW = HAL_ADC_GetValue(&hadc);
//	HAL_ADC_Stop(&hadc);
//
//	// Обработка значений
//	if (ADC_State.ADC_RAW < 4096)
//	{
//		ADC_State.battery_raw_volts 	= __LL_ADC_CALC_DATA_TO_VOLTAGE(ADC_State.ADC_Ref_Voltage, ADC_State.ADC_RAW, hadc.Init.Resolution) - 0.030;  // пересчет из сырых данных АЦП в напряжение в вольтах с учетом разрядности
//		ADC_State.battery_cell_volts 	= ADC_State.battery_raw_volts * ADC_DIVIDER_RATIO;  // делитель на 2 на входе АЦП от батарейки (USB)
//		ADC_State.battery_level 		= 0;
//
//		for (uint8_t i=0; i<6; i++)
//		{
//			if (ADC_State.battery_cell_volts > MP_Battery_Levels[i])
//			{
//				ADC_State.battery_level++;
//			}
//		}
//		ADC_State.DataReady = 1;
//	}
//
//	// Статус пониженного напряжения питания для автоотключения системы
//	if (ADC_State.battery_cell_volts > BATTERY_LOW_THRESHOLD)
//	{
//		ADC_State.LOW_BATT = 0;																// нормальный уровень батареи
//	}
//	else
//	{
//		ADC_State.LOW_BATT = 1;																// пониженный, отключаемся
//	}
//
//
//	// Температура
//	sConfig.Channel      = ADC_CHANNEL_TEMPSENSOR;      	// Канал АЦП - термодатчик
// 	if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
//	{
//		Error_Handler(10);
//	}
//	HAL_ADC_Start(&hadc);
//	HAL_ADC_PollForConversion(&hadc, 10);
//	ADC_Temperature_State.ADC_RAW = HAL_ADC_GetValue(&hadc);
//	HAL_ADC_Stop(&hadc);
//
//	// Пересчет  сырых данных АЦП в температуру в градусах Цельсия, с учетом реального опопрного напряжения питания
//	ADC_Temperature_State.Temperature_DegreeCelsius = __LL_ADC_CALC_TEMPERATURE((uint32_t)(1000*ADC_State.ADC_Ref_Voltage), (ADC_Temperature_State.ADC_RAW + 24), hadc.Init.Resolution);
//
//	ADC_Temperature_State.InternalTemperature_raw 	= __LL_ADC_CALC_DATA_TO_VOLTAGE(ADC_State.ADC_Ref_Voltage, ADC_Temperature_State.ADC_RAW, hadc.Init.Resolution);  // пересчет из сырых данных АЦП в напряжение в вольтах с учетом разрядности
//
////	DBG_PIN_LED_GREEN_RESET;


}
//=======================================================================================
