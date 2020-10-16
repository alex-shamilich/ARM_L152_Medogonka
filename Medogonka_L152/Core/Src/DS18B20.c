// Драйвер термодатчиков DS18B20.c
//   не очень хорошо адаптирован под RtOS из з задержек
//   не точно работают микросекундные задержки (при переезде на другой CPU промерять времянку транспортного уровня, особенно чтение битов)
//
// По мотивам проекта USB-термометра:
//   http://cxem.net/mc/mc39.php
//   Автор: Бражников Михаил (devices2000 {сцобака} ya.ru)
//
// Описание термодатчика
// http://mypractic.ru/ds18b20-datchik-temperatury-s-interfejsom-1-wire-opisanie-na-russkom-yazyke.html

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
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(TEMP_AIR_1W_GPIO_Port, &GPIO_InitStruct);


	GPIO_InitStruct.Pin = TEMP_MOTOR_1W_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(TEMP_MOTOR_1W_GPIO_Port, &GPIO_InitStruct);


	GPIO_InitStruct.Pin = TEMP_DRIVER_1W_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
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

	__disable_irq(); 																	// Глобально запретить все прерывания
	HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_RESET);									// Опустить линию ВНИЗ и подождать 480 мкс
	Delay_us(480);
	HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_SET);									// Освобождаем линию ВВЕРХ и ждем 60 мкс
	DS18B20_ConfigPinToRead(GPIOx, GPIO_Pin);											// переключить порт в режим входа
	Delay_us(60);
	ret = HAL_GPIO_ReadPin(GPIOx, GPIO_Pin);											// Считываем состояние линии и ждем завершения 420 мкс
	__enable_irq();  																	// Глобально разрешить обратно все прерывания

	Delay_us(420);
	return ret;
}
//=======================================================================================
void DS18B20_Write_BitN(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState) // Отправка 1 бита в 1-Wire
{
	HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_RESET);									// Опустить линию ВНИЗ и подождать 1 мкс
	Delay_us(1);
	if (PinState == GPIO_PIN_SET)														// Если нужно записать 1
		HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_SET);								// 		отпускаем линию ВВЕРХ
	else																				// 		продолжаем держать линию ВНИЗу и ждем  60 мкс
	{
	}
	Delay_us(60);
	HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_SET);									// 		отпускаем линию ВВЕРХ
}
//=======================================================================================
void DS18B20_Write_ByteN(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, uint8_t byte) 			// Отправка 1 байта в 1-Wire
{
	uint8_t i = 8;
	uint8_t bit = 0;
	DS18B20_ConfigPinToWrite(GPIOx, GPIO_Pin);											// переключить порт в режим выхода
	__disable_irq(); 																	// Глобально запретить все прерывания
	while (i--)
	{
		bit = byte & 1;
		DS18B20_Write_BitN(GPIOx, GPIO_Pin, bit);										// Пишем текущий бит
		byte >>= 1;																		// и сдвигаем на 1 позицию вправо для записи следующего бита
	}
	__enable_irq();  																	// Глобально разрешить обратно все прерывания
}
//=======================================================================================
uint8_t DS18B20_Read_BitN(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin) 						// Чтение 1 бита из 1-Wire
{
	uint8_t bit = 0;
	uint16_t wait = 5;

	DS18B20_ConfigPinToWrite(GPIOx, GPIO_Pin);											// переключить порт в режим выхода

	// запрос приема бита
//	__disable_irq(); 																	// Глобально запретить все прерывания здесь важна времянка и чтобы никто не отвлекал!!!
	HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_RESET);									// Опустить линию ВНИЗ и подождать 1 мкс
//	Delay_us(1);
	while (wait--);																		// делаем так, т.к. вверхед на Delay_us(1); сильно больше необходимого интервала

	HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_SET);									// Освобождаем линию ВВЕРХ

	// читаем ответа бита
	DS18B20_ConfigPinToRead(GPIOx, GPIO_Pin);											// переключить порт в режим входа
	//Delay_us(14);																		// и ждем 14 мкс
	//Delay_us(2);																		// Delay_us - не точно работает за счет оверхеда на HAL на таких задержках (при 14мкс пролетает мимо)

//	LED_LIGHT_SET;
	bit = HAL_GPIO_ReadPin(GPIOx, GPIO_Pin);											// Считываем состояние линии
//	LED_LIGHT_RESE  T;

//	__enable_irq();  																	// Глобально разрешить обратно все прерывания

	Delay_us(50);																		// Ждем 45 мкс до конца, и возвращаем считанное значение

	return bit;
}
//=======================================================================================
uint8_t DS18B20_Read_ByteN(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin) 						// Чтение 1 байта из 1-Wire
{
	uint8_t i = 8;
	uint8_t n = 0;

	__disable_irq(); 																	// Глобально запретить все прерывания
	while (i--)
	{
		n >>= 1;																		// сдвигаем на 1 позицию вправо
		n |= (DS18B20_Read_BitN(GPIOx, GPIO_Pin) << 7);									// и сохраняем считанное значение
	}
	__enable_irq();  																	// Глобально разрешить обратно все прерывания

	return n;
}
//=======================================================================================


//=======================================================================================
// High-level functions
//=======================================================================================
void DS18B20_Measure_Async_Start(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{	// Асинхронный старт измерения температуры чтобы в процессе можно было чем-то еще заняться.

	// Установка битности преобразования
	DS18B20_ResetN(GPIOx, GPIO_Pin);													// Сброс линии
	DS18B20_Write_ByteN(GPIOx, GPIO_Pin, OW_CMD_SKIPROM);								// т.к. устройство только одно на линии - пропускаем проверку адреса
	DS18B20_Write_ByteN(GPIOx, GPIO_Pin, DS18B20_CMD_WSCRATCHPAD);						// пошлем команду о том что мы будем сейчас писать данные в ScratchPad (3 байта)
	DS18B20_Write_ByteN(GPIOx, GPIO_Pin, 0);											// запись регистра Th (верхний порог аларма, здесь нам не нужен)
	DS18B20_Write_ByteN(GPIOx, GPIO_Pin, 0);											// запись регистра Tl (нижний порог аларма, здесь нам не нужен)
	DS18B20_Write_ByteN(GPIOx, GPIO_Pin, DS18B20_RES_12BIT);							// запись регистра конфигурации (разрядность преобразования температуры)

	// Запуск преобразования
	DS18B20_ResetN(GPIOx, GPIO_Pin);													// Сброс линии
	DS18B20_Write_ByteN(GPIOx, GPIO_Pin, OW_CMD_SKIPROM);								// т.к. устройство только одно на линии - пропускаем проверку адреса

	DS18B20_Write_ByteN(GPIOx, GPIO_Pin, DS18B20_CMD_CONVERTTEMP);						// пошлем команду о том что нужно запусить процесс измерения
}
//=======================================================================================
uint16_t DS18B20_Measure_Async_FinishN(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
	int16_t Temp_FULL = DS18B20_ERR;													// такого кода на бывает у этих датчиков (5 старших разрядов должны быть одинаково 0 или 1, там знак температуры пишется)
	int16_t Temp_LSByte;
	int16_t Temp_MSByte;
	uint8_t ScratchPad[DS18X20_SP_SIZE];
//	uint8_t CRC_Result = DS18X20_ERROR_CRC;

	if (DS18B20_ResetN(GPIOx, GPIO_Pin) == 0)											// Если на RESET пришел правильный ответ PRESENSE
	{
		DS18B20_Write_ByteN(GPIOx, GPIO_Pin, OW_CMD_SKIPROM);
		DS18B20_Write_ByteN(GPIOx, GPIO_Pin, DS18B20_CMD_RSCRATCHPAD);					// Запрос на чтение ScratchPad

		for (int i = 0; i < DS18X20_SP_SIZE; i++ )										// вычитываем полностью весь ScratchPad чтобы проверить по CRC
			ScratchPad[i] = DS18B20_Read_ByteN(GPIOx, GPIO_Pin);

		DS18B20_ResetN(GPIOx, GPIO_Pin);												// Сброс по окончании чтения ScratchPad


		// После вычисления контрольной суммы мастер должен сравнить получившееся значение с переданной CRC.
		// Если эти значения совпадают, значит прием данных прошел без ошибок.
		// Можно также вычислить контрольную сумму для всех 64 принятых бит, тогда результат должен быть равен нулю. (Из статьи Ридико Л.И.)
		if ( DS18B20_CRC8( &ScratchPad[0], DS18X20_SP_SIZE ) == 0 )								// если CRC проверен, возвращаем 2 байта температуры (потом декодировать)
		{
			Temp_LSByte = ScratchPad[0];							// temp LSByte младший
			Temp_MSByte = ScratchPad[1];							// temp MSByte старший
			Temp_FULL   = ((Temp_MSByte << 8) + (Temp_LSByte));
//			CRC_Result = DS18X20_ERROR_CRC;
		}
		else
		{
			// Если передача прошла с ошибкой - передаем ошибку
			Temp_FULL = DS18B20_ERR;
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
}
//=======================================================================================
uint8_t	DS18X20_Get_Power_Status(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)				// Получить статус питания (DS18X20_POWER_EXTERN или DS18X20_POWER_PARASITE)
{
	uint8_t pstat;
	DS18B20_ResetN(GPIOx, GPIO_Pin);
	DS18B20_Write_ByteN(GPIOx, GPIO_Pin, OW_CMD_SKIPROM);
	DS18B20_Write_ByteN(GPIOx, GPIO_Pin, DS18B20_CMD_RPWRSUPPLY);
	pstat = DS18B20_Read_BitN(GPIOx, GPIO_Pin); 										// 0 = паразитное / !0 = внешнее питание
	DS18B20_ResetN(GPIOx, GPIO_Pin);
	return pstat;
}
//=======================================================================================
uint8_t DS18B20_Temperature_Integer(uint16_t TempWord)									// Получить только целую часть темпертуры по модулю без знака
{
	if ((TempWord & 0b11111100000000000) > 0) {											// отрицательная температура
		// DS18B20 для представления отрицательной температуры используется дополнительный код.
		// Особенность этого кода заключается в том, что он позволяет осуществлять операции вычитания через сложение.
		// Чтобы получить дополнительный код числа, нужно выполнить над числом поразрядную инверсию (~)
		// и прибавить к результату единицу.
		TempWord = ~TempWord + 1;														// перевод в дополнительный код числа
	}
	return (int8_t)((TempWord & 0b0000011111110000) >> 4);								// целая часть
}
//=======================================================================================
double DS18B20_Temperature_Double(uint16_t TempWord)									// Получить температуру полностью со знаком и в double
{
	double temp_c = -56.0;

	if (TempWord >= 0x800) 																// Ортицательная температура
	{
		temp_c = 0;
		// дробная часть
		if(TempWord & 0x0001) temp_c += 0.06250;
		if(TempWord & 0x0002) temp_c += 0.12500;
		if(TempWord & 0x0004) temp_c += 0.25000;
		if(TempWord & 0x0008) temp_c += 0.50000;

		// целая часть
		TempWord = (TempWord >> 4) & 0x00FF;
		TempWord = TempWord - 0x0001; //subtract 1
		TempWord = ~TempWord; //ones compliment
		temp_c = temp_c - (double)(TempWord & 0xFF);
	}
	else 																				// Положительная температура
	{
		temp_c = 0;
		// целая часть
		temp_c = (TempWord >> 4) & 0x00FF;
		// дробная часть
		if(TempWord & 0x0001) temp_c = temp_c + 0.06250;
		if(TempWord & 0x0002) temp_c = temp_c + 0.12500;
		if(TempWord & 0x0004) temp_c = temp_c + 0.25000;
		if(TempWord & 0x0008) temp_c = temp_c + 0.50000;
	}
	return temp_c;
}
//=======================================================================================
uint8_t DS18B20_Temperature_Compare(uint16_t TempWord_A, uint16_t TempWord_B)			// Сравнить 2 температуры
{
	// т.к. 11битное преобразование, то последний разряд в десятичной части неактуален
	TempWord_A = TempWord_A & 0b1111111111111110;
	TempWord_B = TempWord_B & 0b1111111111111110;
	uint8_t ret = DS18B20_COMPARE_ERROR;

	if ((TempWord_A == DS18B20_ERR) || (TempWord_B == DS18B20_ERR))						// датчик не подключен
		return ret;

	if (TempWord_A == TempWord_B)														// если числа равны
	{
		ret = DS18B20_COMPARE_EQUAL;
	}
	else
	{

		if ((TempWord_A & 0b11111100000000000) != (TempWord_B & 0b11111100000000000)) 	// Если сравниваем числа с разными знаками
		{
			if (TempWord_A & 0b11111100000000000)										// если число A отрицательное
				ret = DS18B20_COMPARE_LESS;
			else
				ret = DS18B20_COMPARE_MORE;
		}
		else																			// иначе - одинаковые знаки у чисел
		{
			int8_t IntA = (int8_t)((TempWord_A & 0b0000011111110000) >> 4);				// целая часть A
			int8_t IntB = (int8_t)((TempWord_B & 0b0000011111110000) >> 4);				// целая часть B

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
	}
	return ret;
}
//=======================================================================================
#define CRC8INIT    0x00
#define CRC8POLY    0x18              //0X18 = X^8+X^5+X^4+X^0
////=======================================================================================
uint8_t DS18B20_CRC8( uint8_t *data, uint16_t number_of_bytes_in_data )					// Рассчет CRC
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
