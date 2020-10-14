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

//======================================================================================

// Общие командв 1-Wire
#define OW_CMD_SEARCHROM 			0xf0
#define OW_CMD_READROM				0x33
#define OW_CMD_SKIPROM 				0xcc
#define OW_CMD_MATCHROM 			0x55
#define OW_CMD_ALARMSEARCH 			0xec

// команды термодатчика DS18B20
#define DS18B20_CMD_CONVERTTEMP 	0x44
#define DS18B20_CMD_RSCRATCHPAD 	0xbe
#define DS18B20_CMD_WSCRATCHPAD 	0x4e
#define DS18B20_CMD_CPYSCRATCHPAD 	0x48
#define DS18B20_CMD_RPWRSUPPLY 		0xb4
#define DS18B20_CMD_RECEEPROM 		0xb8

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
uint8_t  DS18B20_ResetN(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);						// Generate a 1-Wire reset
uint8_t  DS18B20_Read_BitN(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin); 					//  Read a bit from the 1-wire bus and return it.
void 	 DS18B20_Write_BitN(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState);// Send a 1-wire write bit.
uint8_t  DS18B20_Read_ByteN(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin); 					// Read a byte from the 1-wire bus
void 	 DS18B20_Write_ByteN(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, uint8_t byte); 	// Write a byte to the 1-wire bus


//======================================================================================
// High-level functions
void     DS18B20_Init(void);															// Инициализация термодатчиков
void  	 DS18B20_ConfigPinToRead(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);				// Сконфигурировать GPIO пин как вход на чтение
void 	 DS18B20_ConfigPinToWrite(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);				// Сконфигурировать GPIO пин как выход на запись

uint8_t	 DS18X20_Get_Power_Status(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);

uint16_t DS18B20_Read_Temperature(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);					// Измерение температуры
void 	 DS18B20_Measure_Async_Start(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
uint16_t DS18B20_Measure_Async_FinishN(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);

uint8_t  DS18B20_Temperature_Integer(uint16_t TempWord);								// Получить только целую часть темпертуры по модулю без знака
float	 DS18B20_Temperature_Float(uint16_t TempWord);									// Получить темпертуру в натуральном виде со знаком (для сравнения мин макс)
uint8_t  DS18B20_Temperature_Compare(uint16_t TempWord_A, uint16_t TempWord_B);			// Сравнить 2 температуры

void 	 DS18B20_Read_ROM(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, unsigned char *romValue, uint8_t type);		// Sends the READ ROM command and reads back the ROM id
void 	 DS18B20_Match_ROM(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, unsigned char *romValue, uint8_t type);		// Sends the MATCH ROM command and the ROM id to match against

//void 	 DS18B20_Show_Temperature(uint16_t TempWord);									// Вывести на LCD строку с температурой

uint8_t  DS18B20_CRC8( uint8_t* data, uint16_t number_of_bytes_in_data );


//======================================================================================
#endif /* INC_DS18B20_H_ */
