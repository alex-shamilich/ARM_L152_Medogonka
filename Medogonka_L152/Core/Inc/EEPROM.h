#ifndef _mp_eeprom_h_
#define _mp_eeprom_h_

#include "stm32l1xx_hal.h"

// Базовый адрес EEPROM:
#define EEPROM_ADDR_BASE							0x08080000							// 0x08080000 - стартовый адрес EEPROM для SMT32L1xx процессоров  (для STM32L152VET6 EEPROM = 16kb)

// Распредееление адресов для настроек:  (смещение от EEPROM_ADDR_BASE)
#define EEPROM_ADDR_SETTINGS_SERIAL					(0)									// Серийный номер (9 байт) 9й = '\0'
#define EEPROM_ADDR_SETTINGS_TERMINALMODE			(12)								// Режим работы терминала (4 байта)
#define EEPROM_ADDR_SETTINGS_TERMAUTOINTERVAL		(16)								// Интервал посылок данных в автоматическом режиме работы терминала (в миллисекундах) (4 байта)
#define EEPROM_ADDR_SETTINGS_CLEAN					(20)								// Маркер того что настроки не сохранены (4 байта) (при первом включении)
#define EEPROM_ADDR_SETTINGS_ADCREF3V3				(32)								// калибровка батареи - опорное напряжение АЦП 3.3V (double, 8 байт)
#define EEPROM_ADDR_SETTINGS_ADCREF12V				(40)								// калибровка батареи - опорное напряжение 12V (double, 8 байт)
#define EEPROM_ADDR_SETTINGS_PWR5V0					(48)								// статус источника питания 5В (uint32_t, 4 байта)
#define EEPROM_ADDR_SETTINGS_PWR10V					(52)								// статус источника питания 5В (uint32_t, 4 байта)
#define EEPROM_ADDR_SETTINGS_PWREOP					(56)								// статус источника питания 5В (uint32_t, 4 байта)
#define EEPROM_ADDR_SETTINGS_PWRENC					(60)								// статус источника питания 5В (uint32_t, 4 байта)
#define EEPROM_ADDR_SETTINGS_BUZZER					(64)								// статус состояния баззера (uint8_t, 1 байт)

#define EEPROM_ADDR_SETTINGS_LEN					0x080800FF							// Под настройки резервируем 255 байт

#define EEPROM_SETTINGS_CLEAN_MARKER				0xAA								// значение маркера длля проверки актуальности настроек (для первого включения)

// Транспортный уровень:
HAL_StatusTypeDef 	EEPROM_WriteByte(uint32_t address, uint8_t data);					// Запись байта в EEPROM
HAL_StatusTypeDef 	EEPROM_WriteWord(uint32_t address, uint32_t data);					// Запись слова (4 байта) в EEPROM
HAL_StatusTypeDef 	EEPROM_WriteDouble(uint32_t address, double data);					// Запись double (8 байт) в EEPROM
HAL_StatusTypeDef 	EEPROM_WriteUInt32(uint32_t address, uint32_t data);				// Запись uint32_t (4 байта) в EEPROM
HAL_StatusTypeDef 	EEPROM_WriteObject(uint32_t address, void *obj_p, size_t obj_size);	// Запись объекта (obj_size - байт) в EEPROM
HAL_StatusTypeDef 	EEPROM_Format(void);												// Очистка всей памяти настроек

uint8_t   			EEPROM_ReadByte(uint32_t address);									// Чтение байта из EEPROM
uint32_t  			EEPROM_ReadWord(uint32_t address);									// Чтение слова (4 байта) из EEPROM
double  			EEPROM_ReadDouble(uint32_t address);								// Чтение double (8 байт) из EEPROM
uint32_t 			EEPROM_ReadUInt32(uint32_t address);								// Чтение uint32_t (4 байта) из EEPROM
void 				EEPROM_ReadObject(uint32_t address, void *obj_p, size_t obj_size);  // Чтение объекта (obj_size - байт) из EEPROM


// Основная логика:

void EEPROM_OptionsLoad(void);															// Прочитать настройки из EEPROM в MP_ExchangeStruct
void EEPROM_OptionsSave(void);															// Сохранить настройки из MP_ExchangeStruct в EEPROM
void EEPROM_OptionsLoadDefault(void);													// Записать в MP_ExchangeStruct настройки по-умолчанию
void EEPROM_OptionsSaveDefaults(void);													// Сохранить настройки по-умолчанию в энергонезависимой памяти

// Сервис:
void EEPROM_PrintSettings(void);

//=======================================================================================
#endif // _mp_eeprom_h_

// http://www.microchip.com/forums/m622032.aspx
// https://developer.mbed.org/forum/mbed/topic/4912/
// http://www.purplealienplanet.com/node/56
// http://www.st.com/content/ccc/resource/technical/document/reference_manual/21/bd/0f/bd/1c/88/40/f0/DM00108282.pdf/files/DM00108282.pdf/jcr:content/translations/en.DM00108282.pdf
// https://community.st.com/thread/36005-how-to-used-internal-eepromread-and-write-operation-of-stm32l011f3
// http://www.binaryconvert.com/result_double.html
// http://arduino.ru/forum/programmirovanie/kak-zapisat-peremennuyu-tipa-float-v-eeprom
// http://www.keil.com/support/man/docs/armcc/armcc_chr1359125009502.htm
