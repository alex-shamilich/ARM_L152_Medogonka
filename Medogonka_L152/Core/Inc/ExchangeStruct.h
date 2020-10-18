#ifndef _exchenagestruct_h
#define _exchenagestruct_h

//======================================================================================
#define FIRMWARE_VER "0.0.5"
//======================================================================================





#include "stdint.h"
#include <Encoder.h>

typedef enum {
	TERMINALMODE_AUTO    = 0, 		// Autosend all info (1Hz)
	TERMINALMODE_COMMAND = 1  		// Send info by GET requests
} MP_TerminalMode_TypeDef;

typedef enum {
	TERMINALFORMAT_HUMAN   = 0,  	// Человеко-понятный интерфейс терминала
	TERMINALFORMAT_MACHINE = 1   	// Машинный интерфейс терминала
} MP_TerminalFormat_TypeDef;

typedef struct
{
////	MP_HCM505_ResultAll_TypeDef		*HCM505_ResultAll;					// структура с информацией от компаса HCM505									// MP_Compass_HCM505.h
//	MP_LRF1502_State_TypeDef 		*LRF1502_State;						// структура с сотоянием дальномера												// MP_LRF1502.h
//	MP_LRF1502_Maintenance_TypeDef	*LRF1502_Maintenance;				// структура с информацией об износе дальномера (счетчик/время работы)  		// MP_LRF1502.h
//	MP_Keys_State_TypeDef 			*Keys_State;						// структура с информацией от кнопок 											// MP_Keys.h
//	MP_HMC6343_ResultAll_TypeDef	*HMC6343_ResultAll;					// структура с информацией от компаса HMC6343									// HMC6343.h
//	MP_Power_State_TypeDef 			*Power_State;						// структура с информацией о питании  											// MP_Power.h
//	MP_Battery_State_TypeDef 		*Battery_State;						// структура с информацией о батарее 											// MP_Battery.h
//	nmeaINFO 						*GPS_info;							// структура с сотоянием GPS приемника											// nmea/info.h
////	MP_FIS1100_State_TypeDef 		*FIS1100_State;						// структура с информацией от IMU-датчика FIS-1100								// MP_FIS1100.h

	Encoder_State_TypeDef 			*Encoder_State;						// структура с информацией от энкодера 											// MP_Encoder.h
	char							DeviceSerialNumber[9];				// серийный номер устройства
	MP_TerminalFormat_TypeDef		TerminalFormat;						// Формат работы терминала (Человеко-понятный/Машинный)
	MP_TerminalMode_TypeDef			TerminalMode;						// режим работы терминала (команды/авто)
	uint32_t						TerminalModeAuto_interval;			// интервал посылок в автоматическом режиме работы терминала (в миллисекундах)
}  ExchangeStruct_TypeDef;
// ============================================================================

ExchangeStruct_TypeDef ExchangeStruct;


extern uint8_t BUZZER_BuzzerState;										// для настройки включения/выключения баззера

#endif //_exchenagestruct_h
