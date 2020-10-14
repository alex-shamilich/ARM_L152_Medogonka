// Драйвер термодатчиков DS18B20.c
//
//
// По мотивам проекта USB-термометра:
//   http://cxem.net/mc/mc39.php
//   Автор: Бражников Михаил (devices2000 {сцобака} ya.ru)

#include "main.h"
#include "cmsis_os.h" 																	// для osDelay(();
//=======================================================================================
void  DS18B20_Init(void)																// Инициализация термодатчиков
{
	// Настройка GPIO
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();
	__HAL_RCC_GPIOE_CLK_ENABLE();
	__HAL_RCC_GPIOH_CLK_ENABLE();

	HAL_GPIO_WritePin(TEMP_AIR_1W_GPIO_Port, 		TEMP_AIR_1W_Pin, 		GPIO_PIN_SET);
	HAL_GPIO_WritePin(TEMP_MOTOR_1W_GPIO_Port, 		TEMP_MOTOR_1W_Pin, 		GPIO_PIN_SET);
	HAL_GPIO_WritePin(TEMP_DRIVER_1W_GPIO_Port, 	TEMP_DRIVER_1W_Pin, 	GPIO_PIN_SET);

	GPIO_InitStruct.Pin = TEMP_AIR_1W_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
	HAL_GPIO_Init(TEMP_AIR_1W_GPIO_Port, &GPIO_InitStruct);


	GPIO_InitStruct.Pin = TEMP_MOTOR_1W_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
	HAL_GPIO_Init(TEMP_MOTOR_1W_GPIO_Port, &GPIO_InitStruct);


	GPIO_InitStruct.Pin = TEMP_DRIVER_1W_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
	HAL_GPIO_Init(TEMP_DRIVER_1W_GPIO_Port, &GPIO_InitStruct);


}
//=======================================================================================
void  DS18B20_ConfigPinToRead(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)					// Сконфигурировать GPIO пин как вход на чтение
{
	// Настройка GPIO
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	GPIO_InitStruct.Pin  = GPIO_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);

}
//=======================================================================================
void  DS18B20_ConfigPinToWrite(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)					// Сконфигурировать GPIO пин как выход на запись
{
	// Настройка GPIO
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	GPIO_InitStruct.Pin  = GPIO_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}
//=======================================================================================


//=======================================================================================
// Транспортный уровень 1-Wire уровень программно:
//=======================================================================================
uint8_t DS18B20_ResetN(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)							// Сделать RESET на 1-Wire линии
{
	uint8_t ret = 1;																	// Код возврата (0=Ок, 1=Ошибка)
	DS18B20_ConfigPinToWrite(GPIOx, GPIO_Pin);											// переключить порт в режим выхода
//	__disable_irq(); 																	// Глобально запретить все прерывания
	HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_RESET);									// Опустить линию ВНИЗ и подождать 480 мкс
	Delay_us(480);
	HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_SET);									// Освобождаем линию ВВЕРХ и ждем 60 мкс
	Delay_us(60);
	DS18B20_ConfigPinToRead(GPIOx, GPIO_Pin);											// переключить порт в режим входа
	ret = HAL_GPIO_ReadPin(GPIOx, GPIO_Pin);											// Считываем состояние линии и ждем завершения 420 мкс
	Delay_us(420);
//	__enable_irq();  																	// Глобально разрешить обратно все прерывания
	return ret;


//	cli();																				// критично к задержкам, чтобы таймеры не мешали
//	//http://chipenable.ru/index.php/programming-avr/item/173-rabota-s-portom-cherez-ukazateli.html
//	uint8_t i;
//	BitClear(PortState(Port),  Pin);													// Pull line low and wait for 480uS
//	BitSet(PortDDR(Port),  Pin);
//	_delay_us(480);
//	BitClear(PortDDR(Port),  Pin);														// Release line and wait for 60uS
//	_delay_us(60);
//	i = (PortPins(Port) & (1 << Pin));													// Store line value and wait until the completion of 480uS period
//	_delay_us(420);
//	sei();
//	return i;																			// Return the value read from the presence pulse (0=OK, 1=WRONG)
}
//=======================================================================================
void DS18B20_Write_BitN(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState) // Отправка 1 бита в 1-Wire
{
	HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_RESET);									// Опустить линию ВНИЗ и подождать 1 мкс
	Delay_us(1);
	if (PinState == GPIO_PIN_SET)														// Если нужно записать 1
		HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_RESET);								// 		отпускаем линию ВВЕРХ
	else																				// 		продолжаем держать линию ВНИЗу и ждем  60 мкс
	{
	}
	Delay_us(60);
	HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_RESET);									// 		отпускаем линию ВВЕРХ

//	BitClear(PortState(Port), Pin);														// Pull line low for 1uS
//	BitSet(PortDDR(Port), Pin);
//	_delay_us(1);
//	if (bit)																			// If we want to write 1, release the line (if not will keep low)
//		BitClear(PortDDR(Port), Pin);
//	_delay_us(60);																		// Wait for 60uS and release the line
//	BitClear(PortDDR(Port), Pin);

}
//=======================================================================================
void DS18B20_Write_ByteN(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, uint8_t byte) 			// Отправка 1 байта в 1-Wire
{
	uint8_t i = 8;
	DS18B20_ConfigPinToWrite(GPIOx, GPIO_Pin);											// переключить порт в режим выхода
//	__disable_irq(); 																	// Глобально запретить все прерывания
	while (i--)
	{
		DS18B20_Write_BitN(GPIOx, GPIO_Pin, (byte & 1));								// Пишем текущий бит
		byte >>= 1;																		// и сдвигаем на 1 позицию вправо для записи следующего бита
	}
//	__enable_irq();  																	// Глобально разрешить обратно все прерывания

//	cli();																				// критично к задержкам, чтобы таймеры не мешали
//	uint8_t i = 8;
//	while (i--) {
//		DS18B20_Write_BitN(Port, Pin, (byte & 1));										// Write actual bit and shift one position right to make the next bit ready
//		byte >>= 1;
//	}
//	sei();
}
//=======================================================================================
uint8_t DS18B20_Read_BitN(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin) 						// Чтение 1 бита из 1-Wire
{
	uint8_t bit = 0;

	DS18B20_ConfigPinToWrite(GPIOx, GPIO_Pin);											// переключить порт в режим выхода
	HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_RESET);									// Опустить линию ВНИЗ и подождать 1 мкс
	Delay_us(1);

	HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_SET);									// Освобождаем линию ВВЕРХ и ждем 14 мкс
	Delay_us(14);

	DS18B20_ConfigPinToRead(GPIOx, GPIO_Pin);											// переключить порт в режим входа
	if (HAL_GPIO_ReadPin(GPIOx, GPIO_Pin) & (1 << GPIO_Pin))							// Считываем состояние линии
		bit = 1;
	Delay_us(45);																		// Ждем 45 мкс до конца, и возвращаем считанное значение

	return bit;

//	uint8_t bit = 0;
//	BitClear(PortState(Port), Pin);														// Pull line low for 1uS
//	BitSet(PortDDR(Port), Pin);
//	_delay_us(1);
//	BitClear(PortDDR(Port), Pin);														// Release line and wait for 14uS
//	_delay_us(14);
//	if (PortPins(Port) & (1 << Pin))													// Read line value
//		bit = 1;
//	_delay_us(45);																		// Wait for 45uS to end and return read value
//	return bit;
}
//=======================================================================================
uint8_t DS18B20_Read_ByteN(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin) 						// Чтение 1 байта из 1-Wire
{
	uint8_t i = 8;
	uint8_t n = 0;

//	__disable_irq(); 																	// Глобально запретить все прерывания
	while (i--)
	{
		n >>= 1;																		// сдвигаем на 1 позицию вправо
		n |= (DS18B20_Read_BitN(GPIOx, GPIO_Pin) << 7);									// и сохраняем считанное значение
	}
//	__enable_irq();  																	// Глобально разрешить обратно все прерывания

	return n;





//	cli();																				// критично к задержкам, чтобы таймеры не мешали
//	uint8_t i = 8, n = 0;
//	while (i--) {
//		n >>= 1;																		// Shift one position right and store read value
//		n |= (DS18B20_Read_BitN(Port, Pin) << 7);
//	}
//	sei();
//	return n;
}
//=======================================================================================


//=======================================================================================
// High-level functions
//=======================================================================================
void DS18B20_Measure_Async_Start(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{	// Асинхронный старт измерения температуры чтобы в процессе можно было чем-то еще заняться.
	// записываем конфигурацию битности преобразователя (1 раз по хорошему, но можно и при каждом включении)
	// число записей во флеш конфиг - 50 000 раз (10лет хранения)
	// тут оказывается не в EEPROM запись а в RAM,
	// т.е. с начала пишется в RAM а посто командой DS18B20_CMD_CPYSCRATCHPAD это переносится в EEPROM
	// соотв при каждом включении DS18B20 копирует из EEPROM в RAM данные
	// тогда при ресете каждый раз инициализируем нужную точность (не в падлу)

	// Установка битности преобразования
	DS18B20_ResetN(GPIOx, GPIO_Pin);													// Сброс линии
	DS18B20_Write_ByteN(GPIOx, GPIO_Pin, OW_CMD_SKIPROM);								// т.к. устройство только одно на линии - пропускаем проверку адреса
	DS18B20_Write_ByteN(GPIOx, GPIO_Pin, DS18B20_CMD_WSCRATCHPAD);						// пошлем команду о том что мы будем сейчас писать данные в ScratchPad (3 байта)
	DS18B20_Write_ByteN(GPIOx, GPIO_Pin, 0);											// запись регистра Th (верхний порог аларма, здесь нам не нужен)
	DS18B20_Write_ByteN(GPIOx, GPIO_Pin, 0);											// запись регистра Tl (нижний порог аларма, здесь нам не нужен)
	DS18B20_Write_ByteN(GPIOx, GPIO_Pin, DS18B20_RES_11BIT);							// запись регистра конфигурации (разрядность преобразования температуры)



	//DS18X20_Get_Power_Status(GPIOx, Pin);
	// Запуск преобразования
	DS18B20_ResetN(GPIOx, GPIO_Pin);													// Сброс линии
	DS18B20_Write_ByteN(GPIOx, GPIO_Pin, OW_CMD_SKIPROM);								// т.к. устройство только одно на линии - пропускаем проверку адреса

	//BitSet(PortState(GPIOx),  Pin);													// PortState=PullUp чтобы питать во время измерения (для паразитного питания)
	//BitClear(PortDDR(Port),  Pin);													// Линию сконфигурировать как выход
	DS18B20_Write_ByteN(GPIOx, GPIO_Pin, DS18B20_CMD_CONVERTTEMP);						// пошлем команду о том что нужно запусить процесс измерения (разной дительности, в зав от битности преобразования)

	//	uint8_t i = 8;
	//	uint8_t byte = DS18B20_CMD_CONVERTTEMP;
	//	while (i--) {
	//
	//		BitClear(PortState(Port), Pin);												// Pull line low for 1uS
	//		BitSet(PortDDR(Port), Pin);
	//		_delay_us(1);
	//		if (byte & 1)																// If we want to write 1, release the line (if not will keep low)
	//			BitClear(PortDDR(Port), Pin);
	//		_delay_us(60);																// Wait for 60uS and release the line
	//		BitClear(PortDDR(Port), Pin);
	//		BitSet(PortState(Port), Pin);
	//
	//		byte >>= 1;
	//	}
	//	BitClear(PortDDR(Port), Pin);	//input
	//	BitSet(PortState(Port), Pin);	//Pull-UP
	//	BitSet(PortPins(Port), Pin);	//1
	//	_delay_ms(400);
	//
	//	BitClear(PortState(Port), Pin);	//tristate
	//	BitClear(PortDDR(Port),  Pin);  //input
	//
	//	wdt_reset();

}
//=======================================================================================
uint16_t DS18B20_Measure_Async_FinishN(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
	//ds_sbi(PortReg(Port), Pin);													// Pull line hi
	//ds_sbi(PortDDR(Port), Pin);

	int16_t Temp_FULL = DS18B20_ERR;											// такого кода на бывает у этих датчиков (5 старших разрядов должны быть одинаково 0 или 1, там знак температуры пишется)
	int16_t Temp_LSByte;	// обязательно 16битные переменные, иначе глючит сборка в одну Temp_FULL (не догонюпочему)
	int16_t Temp_MSByte;	// обязательно 16битные переменные, иначе глючит сборка в одну Temp_FULL (не догонюпочему)
	uint8_t sp[DS18X20_SP_SIZE];
	uint8_t CRC_Result = DS18X20_ERROR_CRC;

	if (DS18B20_ResetN(GPIOx, GPIO_Pin) == 0)
	{
		DS18B20_Write_ByteN(GPIOx, GPIO_Pin, OW_CMD_SKIPROM);
		DS18B20_Write_ByteN(GPIOx, GPIO_Pin, DS18B20_CMD_RSCRATCHPAD);				//Read Scratchpad (only 2 first bytes)
		//Temp_LSByte = DS18B20_Read_ByteN(Port, Pin);							// temp LSByte младший
		//Temp_MSByte = DS18B20_Read_ByteN(Port, Pin);							// temp MSByte старший

		// вычитываем полностью весь ScratchPad чтобы проверить по CRC
		for (int i = 0; i < DS18X20_SP_SIZE; i++ )
			sp[i] = DS18B20_Read_ByteN(GPIOx, GPIO_Pin);

		DS18B20_ResetN(GPIOx, GPIO_Pin);


		// После вычисления контрольной суммы мастер должен сравнить получившееся значение с переданной CRC.
		// Если эти значения совпадают, значит прием данных прошел без ошибок.
		// Можно также вычислить контрольную сумму для всех 64 принятых бит, тогда результат должен быть равен нулю. (Из статьи Ридико Л.И.)
		if ( DS18B20_CRC8( &sp[0], DS18X20_SP_SIZE ) == 0 )								// если CRC проверен, возвращаем 2 байта температуры (потом декодировать)
		{
			Temp_LSByte = sp[0];							// temp LSByte младший
			Temp_MSByte = sp[1];							// temp MSByte старший
			Temp_FULL   = ((Temp_MSByte << 8) + (Temp_LSByte));
			CRC_Result = DS18X20_ERROR_CRC;
		}
		else
		{
			// Если передача прошла с ошибкой - переспросить пока нормально не передаст  (РЕКУРСИЯ !!!!!)
			//wdt_reset();	// аккуратно здесь с таймером - можно по идее улететь в бесконечный зависон!!!!!!
			Temp_FULL = DS18B20_Measure_Async_FinishN(GPIOx, GPIO_Pin);
		}

	}
	return Temp_FULL;
}
//=======================================================================================
uint16_t DS18B20_Read_Temperature(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
	DS18B20_Measure_Async_Start(GPIOx, GPIO_Pin);										// Запрос на старт замера температуры
	osDelay(800);																		// задержка 800 мс для 12-битного преобразования
	return DS18B20_Measure_Async_FinishN(GPIOx, GPIO_Pin);								// Возврат ответа от финальной фазы замера


//	wdt_reset();
//	//DS18B20_Measure_Async_Start(&SENSOR_DS18B20_INT_PORT, SENSOR_DS18B20_INT_PIN);
//	DS18B20_Measure_Async_Start(GPIOx, GPIO_Pin);
//	/*
//while (!ds18b20_read_bit())													//Wait until conversion is complete
//	continue;
//	 */
//	_delay_ms(380);		// для 11-битного преобразования
//	//_delay_ms(780);	// для 12-битного преобразования
//	wdt_reset();
//	return DS18B20_Measure_Async_FinishN(GPIOx, GPIO_Pin);
}
//=======================================================================================
void DS18B20_Read_ROM(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, unsigned char * romValue, uint8_t type)  		// Sends the READ ROM command and reads back the ROM id.
{																				// romValue    A pointer where the id will be placed.
	uint8_t bytesLeft = 8;
	DS18B20_Write_ByteN(GPIOx, GPIO_Pin, OW_CMD_READROM); 							// Send the READ ROM command on the bus.
	while (bytesLeft > 0) {														// Do 8 times.
		*romValue++ = DS18B20_Read_ByteN(GPIOx, GPIO_Pin); 							// Place the received data in memory.
		bytesLeft--;
	}
}
//=======================================================================================
void DS18B20_Match_ROM(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, unsigned char * romValue, uint8_t type)		// Sends the MATCH ROM command and the ROM id to match against
{																				// romValue    A pointer to the ID to match against.
	uint8_t bytesLeft = 8;
	DS18B20_Write_ByteN(GPIOx, GPIO_Pin, OW_CMD_MATCHROM); 							// Send the MATCH ROM command.
	while (bytesLeft > 0)														// Do once for each byte.
	{
		DS18B20_Write_ByteN(GPIOx, GPIO_Pin, *romValue++); 							// Transmit 1 byte of the ID to match.
		bytesLeft--;
	}
}

//=======================================================================================

/* get power status of DS18x20
returns: DS18X20_POWER_EXTERN or DS18X20_POWER_PARASITE */
uint8_t	DS18X20_Get_Power_Status(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
	uint8_t pstat;
	DS18B20_ResetN(GPIOx, GPIO_Pin);
	DS18B20_Write_ByteN(GPIOx, GPIO_Pin, OW_CMD_SKIPROM);
	DS18B20_Write_ByteN(GPIOx, GPIO_Pin, DS18B20_CMD_RPWRSUPPLY);
	pstat = DS18B20_Read_BitN(GPIOx, GPIO_Pin); // pstat 0=is parasite/ !=0 ext. powered
	DS18B20_ResetN(GPIOx, GPIO_Pin);
	return (pstat) ? DS18X20_POWER_EXTERN:DS18X20_POWER_PARASITE;
}

//=======================================================================================
// Пользовательские символы
// LCD_SetUserChar(quarterNote, 0);
//__flash uint8_t Char_User_Celsius[] = {4,4,4,4,4,4,28,28};					// Символ

//=======================================================================================
uint8_t DS18B20_Temperature_Integer(uint16_t TempWord)							// Получить только целую часть темпертуры по модулю без знака
{
	if ((TempWord & 0b11111100000000000) > 0) {									// отрицательная температура
		// DS18B20 для представления отрицательной температуры используется дополнительный код.
		// Особенность этого кода заключается в том, что он позволяет осуществлять операции вычитания через сложение.
		// Чтобы получить дополнительный код числа, нужно выполнить над числом поразрядную инверсию (~)
		// и прибавить к результату единицу.
		TempWord = ~TempWord + 1;												// перевод в дополнительный код числа
	}
	return (int8_t)((TempWord & 0b0000011111110000) >> 4);						// целая часть
}
//=======================================================================================
uint8_t DS18B20_Temperature_Compare(uint16_t TempWord_A, uint16_t TempWord_B)	// Сравнить 2 температуры
{
	// т.к. 11битное преобразование, то последний разряд в десятичной части неактуален
	TempWord_A = TempWord_A & 0b1111111111111110;
	TempWord_B = TempWord_B & 0b1111111111111110;
	uint8_t ret = DS18B20_COMPARE_ERROR;

	if ((TempWord_A == DS18B20_ERR) || (TempWord_B == DS18B20_ERR))				// датчик не подключен
		return ret;

	if (TempWord_A == TempWord_B)												// если числа равны
	{
		ret = DS18B20_COMPARE_EQUAL;
	}
	else
	{

		if ((TempWord_A & 0b11111100000000000) != (TempWord_B & 0b11111100000000000)) // Если сравниваем числа с разными знаками
		{
			if (TempWord_A & 0b11111100000000000)									// если число A отрицательное
				ret = DS18B20_COMPARE_LESS;
			else
				ret = DS18B20_COMPARE_MORE;
		}
		else																		// иначе - одинаковые знаки у чисел
		{
			int8_t IntA = (int8_t)((TempWord_A & 0b0000011111110000) >> 4);			// целая часть A
			int8_t IntB = (int8_t)((TempWord_B & 0b0000011111110000) >> 4);			// целая часть B

			if (IntA == IntB)															// если целые части равны, то сравниваем только десятичные после точки
			{
				int8_t DecA = ((int8_t)(TempWord_A & 0b0000000000001110))>>1;			// дробная часть - оставляем 4 младших бита
				int8_t DecB = ((int8_t)(TempWord_B & 0b0000000000001110))>>1;			// дробная часть - оставляем 4 младших бита
				// при 11 битной конверсии только биты 1-3 актуальны (0й - не определен)

				ret = ((DecA < DecB)?(DS18B20_COMPARE_LESS):(DS18B20_COMPARE_MORE));
			}
			else
			{
				// сравниваем только целые
				ret = ((IntA < IntB)?(DS18B20_COMPARE_LESS):(DS18B20_COMPARE_MORE));
			}


		}




		//
		//		// знак - если биты 3-7 м MSByte -1, то отрицательная температура, если 0 - положительная
		//		if ((TempWord & 0b11111100000000000) > 0) {								// отрицательная температура
		//			// DS18B20 для представления отрицательной температуры используется дополнительный код.
		//			// Особенность этого кода заключается в том, что он позволяет осуществлять операции вычитания через сложение.
		//			// Чтобы получить дополнительный код числа, нужно выполнить над числом поразрядную инверсию (~)
		//			// и прибавить к результату единицу.
		//
		//			TempWord = ~TempWord + 1;											// перевод в дополнительный код числа
		//			Sign = -1;
		//		}
		//		else
		//		{
		//			Sign = +1;
		//		}
		//
		//		Temp_Integer = (int8_t)((TempWord & 0b0000011111110000) >> 4);			// целая часть
		//
		//		Temp_Decimal = (int8_t)(TempWord & 0b0000000000001111);					// дробная часть - оставляем 4 младших бита
		//																				// преобразование 11-бит - амый младший не определен
		//
		//		// ВЗЯТО ЗДЕСЬ: http://chipenable.ru/index.php/programming-c/86-1-wire-ds18b20-avr.html
		//		Temp_Decimal = (Temp_Decimal>>1);										// при 11 битной конверсии только биты 1-3 актуальны
		//
		//		ret = Sign*(Temp_Integer + 0.125*Temp_Decimal);
		//
	}
	return ret;

}
//=======================================================================================
//void DS18B20_Show_Temperature(uint16_t TempWord)										// Вывести на LCD строку с температурой
//{
//	// Температура хранится - целое биты 4-7 в LS Byte и 0-2 в MS Byte, дробное - биты 0-3 в  LS Byte
//	// соединяем часть младшего [4-7], подвинув влево на 4 и старшего байта [0-2], подвинув вправо на 4,
//	// для получения целой части температуры
//
//
//	//LCD_SEND_CHAR(0xFF);
//	//LCD_SEND_String("==");
//	if (TempWord == DS18B20_ERR)														// датчик не подключен
//	{
//		LCD_SEND_String("-HET-");
//		return;
//	}
//
//	if (TempWord == 0)															// просто 0
//	{
//		LCD_SEND_String("  0.0");
//	}
//	else
//	{
//		int8_t 		Temp_Integer;
//		uint16_t	Temp_Decimal;
//
//		//LCD_SEND_String("t=");
//
//		// знак - если биты 3-7 м MSByte -1, то отрицательная температура, если 0 - положительная
//		if ((TempWord & 0b11111100000000000) > 0) {								// отрицательная температура
//			// DS18B20 для представления отрицательной температуры используется дополнительный код.
//			// Особенность этого кода заключается в том, что он позволяет осуществлять операции вычитания через сложение.
//			// Чтобы получить дополнительный код числа, нужно выполнить над числом поразрядную инверсию (~)
//			// и прибавить к результату единицу.
//
//			TempWord = ~TempWord + 1;											// перевод в дополнительный код числа
//			LCD_SEND_CHAR('-');
//		}
//		else
//		{
//			LCD_SEND_CHAR('+');
//		}
//
//		Temp_Integer = (int8_t)((TempWord & 0b0000011111110000) >> 4);			// целая часть
//		LCD_SEND_Dec(Temp_Integer);
//		LCD_SEND_CHAR('.');														// разделитель - десятичная точка
//
//		Temp_Decimal = (int8_t)(TempWord & 0b0000000000001111);					// дробная часть - оставляем 4 младших бита
//		// преобразование 11-бит
//
//		// ВЗЯТО ЗДЕСЬ: http://chipenable.ru/index.php/programming-c/86-1-wire-ds18b20-avr.html
//		Temp_Decimal = (Temp_Decimal>>1);										// при 11 битной конверсии только биты 1-3 актуальны
//		Temp_Decimal = (Temp_Decimal<<1) + (Temp_Decimal<<3);					// Умножаем на 10
//		Temp_Decimal = (Temp_Decimal>>3);										// Делим на 8 (1/8 шаг 11-битной конверсии)
//
//
//		LCD_SEND_Dec(Temp_Decimal);
//		//LCD_SEND_CHAR(0xEF);													// Символ градуса С (загружаемый при старте в LCD)
//	}
//	return;
//
//	//Temp_Decimal = Temp_Decimal*1/16;			// 1/16 = 0.0625C - шаг долей градуса при 12-битной точности
//	//Temp_Decimal = Temp_Decimal*1/8;			// 1/8 = 0.125C - шаг долей градуса при 11-битной точности
//	//Temp_Decimal = Temp_Decimal*1/4;			// 1/4 = 0.25C - шаг долей градуса при 10-битной точности
//	//Temp_Decimal = Temp_Decimal*1/2;			// 1/2 = 0.5C - шаг долей градуса при  9-битной точности
//	/*
//switch(Temp_Decimal)		// табличное округление для 11-битного преобразования
//{
//case 0:	Temp_Decimal = 0; break;
//case 1:	Temp_Decimal = 1; break;
//case 2:	Temp_Decimal = 2; break;
//case 3:	Temp_Decimal = 4; break;
//case 4:	Temp_Decimal = 5; break;
//case 5:	Temp_Decimal = 6; break;
//case 6:	Temp_Decimal = 8; break;
//case 7:	Temp_Decimal = 9; break;
//}
//	 */
//}
////=======================================================================================



#define CRC8INIT    0x00
#define CRC8POLY    0x18              //0X18 = X^8+X^5+X^4+X^0
////=======================================================================================
uint8_t DS18B20_CRC8( uint8_t *data, uint16_t number_of_bytes_in_data )
{
	uint8_t  crc;
	uint16_t loop_count;
	uint8_t  bit_counter;
	uint8_t  b;
	uint8_t  feedback_bit;

	crc = CRC8INIT;

	for (loop_count = 0; loop_count != number_of_bytes_in_data; loop_count++)
	{
		b = data[loop_count];

		bit_counter = 8;
		do {
			feedback_bit = (crc ^ b) & 0x01;

			if ( feedback_bit == 0x01 ) {
				crc = crc ^ CRC8POLY;
			}
			crc = (crc >> 1) & 0x7F;
			if ( feedback_bit == 0x01 ) {
				crc = crc | 0x80;
			}

			b = b >> 1;
			bit_counter--;

		} while (bit_counter > 0);
	}

	return crc;
}
//=======================================================================================7
