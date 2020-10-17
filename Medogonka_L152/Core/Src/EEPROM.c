#include <string.h>
#include <EEPROM.h>
#include <Buzzer_TIM.h>

#include "ExchangeStruct.h"

//=======================================================================================
HAL_StatusTypeDef EEPROM_Format(void)													// Очистка всей памяти настроек
 {
    HAL_StatusTypeDef  	status = HAL_ERROR;
    HAL_FLASHEx_DATAEEPROM_Unlock();  													// Разблокировать возможность записи в EEPROM
    for (uint32_t address = EEPROM_ADDR_BASE; address < EEPROM_ADDR_SETTINGS_LEN; address++)	// побайтно записываем нули в EEPROM
    {
    	status = HAL_FLASHEx_DATAEEPROM_Program(FLASH_TYPEPROGRAMDATA_BYTE, address,  0);
    }
    HAL_FLASHEx_DATAEEPROM_Lock();  													// Заблокировать возможность записи в EEPROM
    return status;
 }
//=======================================================================================

HAL_StatusTypeDef EEPROM_WriteObject(uint32_t address, void *obj_p, size_t obj_size)	// Записл любого объекта в EEPROM
 {
    HAL_StatusTypeDef  	status = HAL_ERROR;
    address = EEPROM_ADDR_BASE + address;												// 0x08080000 - стартовый адрес EEPROM для SMT32L1xx процессоров
    HAL_FLASHEx_DATAEEPROM_Unlock();  													// Разблокировать возможность записи в EEPROM
    unsigned char *p = obj_p;															// превращаем объект в набор байтов (получаем указатель на первый байт объекта)
    while (obj_size--)																	// побайтно записываем в EEPROM
    {
    	status = HAL_FLASHEx_DATAEEPROM_Program(FLASH_TYPEPROGRAMDATA_BYTE, address++,  *p++);
    }
    HAL_FLASHEx_DATAEEPROM_Lock();  													// Заблокировать возможность записи в EEPROM
    return status;
    //http://www.microchip.com/forums/m622032.aspx
 }
//=======================================================================================
HAL_StatusTypeDef EEPROM_WriteByte(uint32_t address, uint8_t data)						// Запись байта в EEPROM
 {
    HAL_StatusTypeDef  	status;
    address = EEPROM_ADDR_BASE + address;														// 0x08080000 - стартовый адрес EEPROM для SMT32L1xx процессоров
    HAL_FLASHEx_DATAEEPROM_Unlock();  													// Разблокировать возможность записи в EEPROM
    status = HAL_FLASHEx_DATAEEPROM_Program(FLASH_TYPEPROGRAMDATA_BYTE, address, data);	// Запись байта по адресу
    HAL_FLASHEx_DATAEEPROM_Lock();  													// Заблокировать возможность записи в EEPROM
    return status;
    // https://developer.mbed.org/forum/mbed/topic/4912/
}
//=======================================================================================
HAL_StatusTypeDef EEPROM_WriteWord(uint32_t address, uint32_t data)						// Запись слова (4 байта) в EEPROM
 {
    HAL_StatusTypeDef  	status;
    address = EEPROM_ADDR_BASE + address;														// 0x08080000 - стартовый адрес EEPROM для SMT32L1xx процессоров
    HAL_FLASHEx_DATAEEPROM_Unlock();  													// Разблокировать возможность записи в EEPROM
    status = HAL_FLASHEx_DATAEEPROM_Program(FLASH_TYPEPROGRAMDATA_BYTE, address, data);	// Запись слова (4 байта) по адресу
    HAL_FLASHEx_DATAEEPROM_Lock();  													// Заблокировать возможность записи в EEPROM
    return status;
    // https://developer.mbed.org/forum/mbed/topic/4912/
}
//=======================================================================================
HAL_StatusTypeDef EEPROM_WriteDouble(uint32_t address, double data)						// Запись double (8 байт) в EEPROM
{
	return EEPROM_WriteObject(address, &data, sizeof(data) );
	// http://www.binaryconvert.com/result_double.html
}
//=======================================================================================
HAL_StatusTypeDef EEPROM_WriteUInt32(uint32_t address, uint32_t data)					// Запись uint32_t (4 байта) в EEPROM
{
	return EEPROM_WriteObject(address, &data, sizeof(data) );
}
//=======================================================================================


//=======================================================================================
void EEPROM_ReadObject(uint32_t address, void *obj_p, size_t obj_size)
 {
     unsigned char *p = obj_p;

     while (obj_size--) {
    	 *p++ = (unsigned char)( *(__IO uint32_t*)(EEPROM_ADDR_BASE + address++) );
//         *p++ = eeprom_read(address++);
     }
     // http://www.microchip.com/forums/m622032.aspx
 }
//=======================================================================================
uint8_t  EEPROM_ReadByte(uint32_t address)												// Чтение байта из EEPROM
 {
    return (uint8_t)( *(__IO uint32_t*)(EEPROM_ADDR_BASE + address) );						// Читаем как из обычной памяти по адресу, 0x08080000 - стартовый адрес EEPROM для SMT32L1xx процессоров
    // https://developer.mbed.org/forum/mbed/topic/4912/
}
//=======================================================================================
uint32_t  EEPROM_ReadWord(uint32_t address)												// Чтение слова (4 байта) из EEPROM
 {
    return (uint32_t)( *(__IO uint32_t*)(EEPROM_ADDR_BASE + address) );						// Читаем как из обычной памяти по адресу, 0x08080000 - стартовый адрес EEPROM для SMT32L1xx процессоров
    // https://developer.mbed.org/forum/mbed/topic/4912/
}
//=======================================================================================
double  EEPROM_ReadDouble(uint32_t address)												// Чтение double (8 байт) из EEPROM
 {
	double ret = 0.0;
	EEPROM_ReadObject(address, &ret, sizeof(ret) );
    return ret;

}
//=======================================================================================
uint32_t EEPROM_ReadUInt32(uint32_t address)											// Чтение uint32_t (4 байта) из EEPROM
 {
	uint32_t ret = 0.0;
	EEPROM_ReadObject(address, &ret, sizeof(ret) );
    return ret;

}
//=======================================================================================





//=======================================================================================
void EEPROM_OptionsLoadDefault(void)
{
// // Defaults:
// MP_BUZZER_BuzzerState = BUZZER_STSTE_ON;												// по-умолчанию баззер включен
// strcpy(ExchangeStruct.DeviceSerialNumber, "MP000000");								// устанавливаем нулевой серийный номер устройства (8 символов)
// ExchangeStruct.TerminalMode = TERMINALMODE_COMMAND;									// командный режим (запрос-ответ)
// ExchangeStruct.TerminalModeAuto_interval = 1000;									// интервал автообновления в Авто-режиме 1000мс = 1сек
// //MP_ExchangeStruct.TerminalFormat = TERMINALFORMAT_HUMAN;								// Формат работы терминала (man/machine)
// ExchangeStruct.Battery_State->ADC_Ref_Voltage = ADC_REF_VOLTAGE_DEFAULT;			// калибровка батареи - опорное напряжение АЦП
// ExchangeStruct.Battery_State->ADC_12V_Voltage = ADC_12V_VOLTAGE_DEFAULT;			// калибровка батареи - напряжение 12V
//
// MP_Power_Set_5V0(POWERSTATE_DISABLE);
// MP_Power_Set_10V(POWERSTATE_DISABLE);
// MP_Power_Set_EOP(POWERSTATE_DISABLE);
// MP_Power_Set_Encoder(POWERSTATE_DISABLE);
//
	ExchangeStruct.TerminalFormat = TERMINALFORMAT_HUMAN;
//	ExchangeStruct.TerminalFormat = TERMINALFORMAT_MACHINE;
}
//=======================================================================================
void EEPROM_OptionsLoad(void)															// Загрузить настройки из энергонезависимой памяти
{
	EEPROM_OptionsLoadDefault();
//
// if (EEPROM_ReadByte(EEPROM_ADDR_SETTINGS_CLEAN ) != EEPROM_SETTINGS_CLEAN_MARKER ) 	// первое включение, настроек в EEPROM еще нет, считываем и записываем дефолтные настройки
// {
//	 EEPROM_OptionsLoadDefault();
//	 EEPROM_OptionsSave();
// }
//
// // заполнение из EEPROM
//
// ExchangeStruct.TerminalMode 					=	(MP_TerminalMode_TypeDef)( *(__IO uint32_t*)(EEPROM_ADDR_BASE + EEPROM_ADDR_SETTINGS_TERMINALMODE) );
// ExchangeStruct.TerminalModeAuto_interval		= EEPROM_ReadUInt32(EEPROM_ADDR_SETTINGS_TERMAUTOINTERVAL );
//
// ExchangeStruct.Battery_State->ADC_Ref_Voltage 	= EEPROM_ReadDouble(EEPROM_ADDR_SETTINGS_ADCREF3V3);
// ExchangeStruct.Battery_State->ADC_12V_Voltage 	= EEPROM_ReadDouble(EEPROM_ADDR_SETTINGS_ADCREF12V);
//
// MP_Power_Set_5V0( (MP_PowerState_TypeDef)( *(__IO uint32_t*)(EEPROM_ADDR_BASE + EEPROM_ADDR_SETTINGS_PWR5V0) ));
// MP_Power_Set_10V( (MP_PowerState_TypeDef)( *(__IO uint32_t*)(EEPROM_ADDR_BASE + EEPROM_ADDR_SETTINGS_PWR10V) ));
// MP_Power_Set_EOP( (MP_PowerState_TypeDef)( *(__IO uint32_t*)(EEPROM_ADDR_BASE + EEPROM_ADDR_SETTINGS_PWREOP) ));
// MP_Power_Set_Encoder( (MP_PowerState_TypeDef)( *(__IO uint32_t*)(EEPROM_ADDR_BASE + EEPROM_ADDR_SETTINGS_PWRENC) ));
//
//// EEPROM_ReadObject(EEPROM_ADDR_SETTINGS_ADCREF3V3, &(MP_ExchangeStruct.Battery_State->ADC_Ref_Voltage), sizeof(MP_ExchangeStruct.Battery_State->ADC_Ref_Voltage) );
//// EEPROM_ReadObject(EEPROM_ADDR_SETTINGS_ADCREF12V, &(MP_ExchangeStruct.Battery_State->ADC_12V_Voltage), sizeof(MP_ExchangeStruct.Battery_State->ADC_12V_Voltage) );
//
//
// memcpy(&ExchangeStruct.DeviceSerialNumber, (__IO uint32_t*)(EEPROM_ADDR_BASE + EEPROM_ADDR_SETTINGS_SERIAL), (sizeof(uint8_t) * 8) );
// ExchangeStruct.DeviceSerialNumber[8] = '\0';
//
//
// MP_BUZZER_BuzzerState = (((uint8_t)( *(__IO uint32_t*)(EEPROM_ADDR_BASE + EEPROM_ADDR_SETTINGS_BUZZER) ) == 0)?(BUZZER_STSTE_OFF):(BUZZER_STSTE_ON)) ;
//
}
//=======================================================================================
void EEPROM_OptionsSave(void)															// Сохранить настройки в энергонезависимой памяти
{
//	EEPROM_WriteObject(EEPROM_ADDR_SETTINGS_SERIAL, &ExchangeStruct.DeviceSerialNumber, 8 );
//	EEPROM_WriteByte(EEPROM_ADDR_SETTINGS_TERMINALMODE, (uint8_t)(ExchangeStruct.TerminalMode) );
//	EEPROM_WriteUInt32(EEPROM_ADDR_SETTINGS_TERMAUTOINTERVAL, ExchangeStruct.TerminalModeAuto_interval );
//
// 	EEPROM_WriteDouble(EEPROM_ADDR_SETTINGS_ADCREF3V3, ExchangeStruct.Battery_State->ADC_Ref_Voltage);
// 	EEPROM_WriteDouble(EEPROM_ADDR_SETTINGS_ADCREF12V, ExchangeStruct.Battery_State->ADC_12V_Voltage);
//
// 	EEPROM_WriteByte(EEPROM_ADDR_SETTINGS_PWR5V0, (uint8_t)(ExchangeStruct.Power_State->EN_5V0) );
// 	EEPROM_WriteByte(EEPROM_ADDR_SETTINGS_PWR10V, (uint8_t)(ExchangeStruct.Power_State->EN_10V) );
// 	EEPROM_WriteByte(EEPROM_ADDR_SETTINGS_PWREOP, (uint8_t)(ExchangeStruct.Power_State->EN_EOP) );
// 	EEPROM_WriteByte(EEPROM_ADDR_SETTINGS_PWRENC, (uint8_t)(ExchangeStruct.Power_State->EN_ENCODER) );
//
// 	EEPROM_WriteByte(EEPROM_ADDR_SETTINGS_BUZZER, (uint8_t)MP_BUZZER_BuzzerState );
//
//
// 	EEPROM_WriteByte(EEPROM_ADDR_SETTINGS_CLEAN, EEPROM_SETTINGS_CLEAN_MARKER );
//
//
//
//	 //	//EEPROM_WriteByte(5, 0x11);
//	 //	EEPROM_WriteByte(EEPROM_ADDR_SETTINGS_SERIAL + 0, 'M');
//	 //	EEPROM_WriteByte(EEPROM_ADDR_SETTINGS_SERIAL + 1, 'P');
//	 //	EEPROM_WriteByte(EEPROM_ADDR_SETTINGS_SERIAL + 2, '0');
//	 // MP_ExchangeStruct.TerminalMode = TERMINALMODE_COMMAND;
//	 //	double ref_3v3 = 3.4596459;
//	 //	double ref_12v = 14.00116007;
//	 //	EEPROM_WriteObject(EEPROM_ADDR_SETTINGS_ADCREF3V3, &ref_3v3, sizeof(ref_3v3) );
//	 //	EEPROM_WriteObject(EEPROM_ADDR_SETTINGS_ADCREF12V, &ref_12v, sizeof(ref_12v) );
}
//=======================================================================================
void EEPROM_OptionsSaveDefaults(void)													// Сохранить настройки по-умолчанию в энергонезависимой памяти
{
	EEPROM_OptionsLoadDefault();
	EEPROM_OptionsSave();
}
//=======================================================================================
void EEPROM_PrintSettings(void)
{
//	MP_Power_GetPowerRegister();														// Получить состояние из регистров управления питанием

	printf("\n\nEEPROM Stored Settings: \n");
	printf("SERIAL_NUMBER=%s\n", ExchangeStruct.DeviceSerialNumber);
	printf("MODE=%s\n", ((ExchangeStruct.TerminalMode==TERMINALMODE_COMMAND)?("COMMAND"):("AUTO"))  );
	printf("AutoTime=%lu msec\n", ExchangeStruct.TerminalModeAuto_interval );

//	printf("Bat cal: 3V3 =  %02.4lf\n", ExchangeStruct.Battery_State->ADC_Ref_Voltage );
//	printf("Bat cal: 12V = %02.4lf\n", ExchangeStruct.Battery_State->ADC_12V_Voltage );
//
////	printf("PWR_5V0=%s\n", 		((MP_ExchangeStruct.Power_State->EN_5V0 	== POWERSTATE_DISABLE)?("OFF"):("ON")) );
////	printf("PWR_10V=%s\n", 		((MP_ExchangeStruct.Power_State->EN_10V 	== POWERSTATE_DISABLE)?("OFF"):("ON")) );
//	printf("PWR_5V0=%s\n", 		((ExchangeStruct.Power_State->PG_5V0 	== POWERSTATE_DISABLE)?("OFF"):("ON")) );
//	printf("PWR_10V=%s\n", 		((ExchangeStruct.Power_State->PG_10V 	== POWERSTATE_DISABLE)?("OFF"):("ON")) );
//	printf("PWR_EOP=%s\n", 		((ExchangeStruct.Power_State->EN_EOP 	== POWERSTATE_DISABLE)?("OFF"):("ON")) );
//	printf("PWR_ENC=%s\n", 		((ExchangeStruct.Power_State->EN_ENCODER == POWERSTATE_DISABLE)?("OFF"):("ON")) );
//	printf("PWR_CPU=%s\n", 		((ExchangeStruct.Power_State->EN_MAIN_CPU== POWERSTATE_DISABLE)?("OFF"):("ON")) );
//	printf("PWR_CPLD=%s\n", 	((ExchangeStruct.Power_State->EN_CPLD 	== POWERSTATE_DISABLE)?("OFF"):("ON")) );



	printf("BUZZER=%s\n", 		((BUZZER_BuzzerState)?("ON"):("OFF")) );
	printf("TERMINAL_FORMAT=%s\n", 	((ExchangeStruct.TerminalFormat == TERMINALFORMAT_HUMAN)?("HUMAN"):("MACHINE")) );

}
//=======================================================================================
