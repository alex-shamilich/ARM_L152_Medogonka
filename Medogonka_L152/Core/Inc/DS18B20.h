// Драйвер термодатчиков DS18B20.h

#ifndef INC_DS18B20_H_
#define INC_DS18B20_H_

//=======================================================================================
// GPIO для подключенных термодатчиков

// Вход-выход термодатчика 1-wire. Температура воздуха
#define TEMP_AIR_1W_Pin 			GPIO_PIN_0
#define TEMP_AIR_1W_GPIO_Port 		GPIOB

// Вход-выход термодатчика 1-wire. Температура мотора
#define TEMP_MOTOR_1W_Pin 			GPIO_PIN_1
#define TEMP_MOTOR_1W_GPIO_Port 	GPIOB

// Вход-выход термодатчика 1-wire. Температура драйвера мотора
#define TEMP_DRIVER_1W_Pin 			GPIO_PIN_2
#define TEMP_DRIVER_1W_GPIO_Port 	GPIOB

//======================================================================================
uint16_t Temperature_Air_RAW;															// Темература от датчика воздуха в сыром виде
uint16_t Temperature_Motor_RAW;															// Темература от датчика мотора в сыром виде
uint16_t Temperature_Driver_RAW;														// Темература от датчика драйвера в сыром виде

double 	 Temperature_Air;																// Темература от датчика воздуха
double 	 Temperature_Motor;																// Темература от датчика мотора
double 	 Temperature_Driver;															// Темература от датчика драйвера
//======================================================================================

// Общие командв 1-Wire
#define OW_CMD_SEARCHROM 			0xF0
#define OW_CMD_READROM				0x33
#define OW_CMD_SKIPROM 				0xCC
#define OW_CMD_MATCHROM 			0x55
#define OW_CMD_ALARMSEARCH 			0xEC

// команды термодатчика DS18B20
#define DS18B20_CMD_CONVERTTEMP 	0x44
#define DS18B20_CMD_RSCRATCHPAD 	0xBE
#define DS18B20_CMD_WSCRATCHPAD 	0x4E
#define DS18B20_CMD_CPYSCRATCHPAD 	0x48
#define DS18B20_CMD_RPWRSUPPLY 		0xB4
#define DS18B20_CMD_RECEEPROM 		0xB8

#define DS18X20_POWER_PARASITE 		0x00
#define DS18X20_POWER_EXTERN   		0x01

// Общий ID термодатчиков DS18B20
#define DS18B20_FAMILY				0x28

#define DS18B20_RES_9BIT 			0b00011111		// Время преобразования = 93.75ms		точность = 0.5		1/2
#define DS18B20_RES_10BIT 			0b00111111		// Время преобразования = 187.5ms		точность = 0.25		1/4
#define DS18B20_RES_11BIT 			0b01011111		// Время преобразования = 375ms			точность = 0.125	1/8
#define DS18B20_RES_12BIT 			0b01111111		// Время преобразования = 750ms			точность = 0.0625  1/16

// scratchpad size in bytes
#define DS18X20_SP_SIZE           	9

#define DS18X20_OK                  0x00
#define DS18X20_ERROR_CRC         	0x03
#define DS18B20_ERR					0xDFFF			// такого кода не бывает у этих датчиков (5 старших разрядов должны быть одинаково 0 или 1, там знак температуры пишется)

#define DS18B20_TYPE_INT			0
#define DS18B20_TYPE_EXT			1

#define DS18B20_COMPARE_EQUAL 		0
#define DS18B20_COMPARE_LESS 		1
#define DS18B20_COMPARE_MORE 		2
#define DS18B20_COMPARE_ERROR 		3

//======================================================================================
// Транспортный уровень 1-Wire:
uint8_t  DS18B20_ResetN(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);						// Сгенерировать RESET на 1-Wire
uint8_t  DS18B20_Read_BitN(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin); 					// Прочитать 1 бит из 1-wire и вернуть его
void 	 DS18B20_Write_BitN(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState);// записать 1 бит в 1-wire
uint8_t  DS18B20_Read_ByteN(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin); 					// Прочитать 1 байт из 1-wire
void 	 DS18B20_Write_ByteN(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, uint8_t byte); 	// Записать 1 байт в 1-wire

void  	 DS18B20_ConfigPinToRead(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);				// Сконфигурировать GPIO пин как вход на чтение
void 	 DS18B20_ConfigPinToWrite(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);				// Сконфигурировать GPIO пин как выход на запись
//======================================================================================
// High-level functions
void     DS18B20_Init(void);															// Инициализация термодатчиков
uint8_t	 DS18X20_Get_Power_Status(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);

uint16_t DS18B20_Read_Temperature(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);					// Измерение температуры
void 	 DS18B20_Measure_Async_Start(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
uint16_t DS18B20_Measure_Async_FinishN(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);

uint8_t  DS18B20_Temperature_Integer(uint16_t TempWord);								// Получить только целую часть темпертуры по модулю без знака
double 	 DS18B20_Temperature_Double(uint16_t TempWord);									// Получить температуру полностью со знаком и в double

uint8_t  DS18B20_Temperature_Compare(uint16_t TempWord_A, uint16_t TempWord_B);			// Сравнить 2 температуры

uint8_t  DS18B20_CRC8( uint8_t* data, uint16_t number_of_bytes_in_data );

//======================================================================================
#endif /* INC_DS18B20_H_ */
