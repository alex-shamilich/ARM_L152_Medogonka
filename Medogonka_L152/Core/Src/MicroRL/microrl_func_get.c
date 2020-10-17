// terminal function: GET
#include <string.h>				// for strcmp, strstr

#include "microrl_func.h"
#include "microrl_func_get.h"

#include "ExchangeStruct.h"
#include "FreeRTOSUser.h"

extern char str[255];

//=======================================================================================
int prv_TerminalFunc_get(int argc, const char * const * argv)
{
//	microrl_printString ("Get something...");
//	microrl_printEndl();
	osStatus status = osMutexWait(MircoRL_Tx_MutexHandle, portMAX_DELAY);					// ждем пока не освободиться порт терминала на передачу

	if (status == osOK)
	{
		switch (argc)
		{
		case 0:																				// если вызвали get без параметра - показать help
			prv_printHelpGet();
			break;
		case 1:
			prv_TerminalFuncGetParams(argv[0]);												// реакция на параметры в get

			break;
		default:																			// тройной уровень параметров не сделан (пока)
			microrl_printStringWithEndl("Get is available only for high-level commands, yet (Ex:  '>get gps'");
			break;
		}

		osMutexRelease(MircoRL_Tx_MutexHandle);
	}


	return 0;

}
//=======================================================================================
void prv_printHelpGet(void)
{
	// здесь нужно расписать какие есть параметры у get
	microrl_printStringWithEndl("get <parameter>");
	microrl_printStringWithEndl("  all		- All info");
	microrl_printStringWithEndl("  bat		- Battery level");
	microrl_printStringWithEndl("  buzzer	- Buzzer state (on|off)");
	microrl_printStringWithEndl("  calbat	- Battery calibration constants");
	microrl_printStringWithEndl("  compass	- Compass (Heading, Roll, Pitch, Temperature)");
	microrl_printStringWithEndl("  fire		- Measure the renge by LRF & get target info");
	microrl_printStringWithEndl("  gps		- GPS/GLONASS info");
	microrl_printStringWithEndl("  keys		- Keyboard & encoder state");
	microrl_printStringWithEndl("  lrf		- Laser Range Finder state");
	microrl_printStringWithEndl("  mode		- AUTO or by requests");
	microrl_printStringWithEndl("  pwr		- Power status");
	microrl_printStringWithEndl("  serial	- Device Serial Number");
	microrl_printStringWithEndl("  target	- Target info (if GPS & LRF data available");
	microrl_printStringWithEndl("  time		- Date/Time from GPS/GLONASS [UTC]");
	microrl_printEndl();
}
//=======================================================================================

void prv_TerminalFuncGetParams(const char *name)
{
//	microrl_printString("Command: ");
//	microrl_printStringWithEndl(name);

	if (strncmp(name, "all", 3) == 0)
	{
		osStatus statusCMD = osMutexWait(MircoRL_TxCMD_MutexHandle, portMAX_DELAY);						// для защиты от вклинивкания в цельный блок "get all" сообщений от кнопок, энкодера и дальномера

	    if (statusCMD == osOK)
	    {
			TerminalPrintGet_GPS();
	//		TerminalPrintGet_TIME();
			TerminalPrintGet_LRF();
			TerminalPrintGet_TARGET();
			TerminalPrintGet_COMPASS();
			TerminalPrintGet_KEYS();
			TerminalPrintGet_PWR();
			TerminalPrintGet_BAT();
			TerminalPrintGet_MODE();

			osMutexRelease(MircoRL_TxCMD_MutexHandle);
	    }
	}
	else if (strncmp(name, "pwr", 3) == 0)
		TerminalPrintGet_PWR();
	else if (strncmp(name, "bat", 3) == 0)
		TerminalPrintGet_BAT();
	else if (strncmp(name, "calbat", 6) == 0)
		TerminalPrintGet_BATCatlibration();
	else if (strncmp(name, "compass", 3) == 0)
		TerminalPrintGet_COMPASS();
	else if (strncmp(name, "keys", 3) == 0)
		TerminalPrintGet_KEYS();
	else if (strncmp(name, "gps", 3) == 0)
		TerminalPrintGet_GPS();
	else if (strncmp(name, "time", 3) == 0)
		TerminalPrintGet_TIME();
	else if (strncmp(name, "lrf", 3) == 0)
		TerminalPrintGet_LRF();
	else if (strncmp(name, "fire", 3) == 0)
		TerminalPrintGet_FIRE();
	else if (strncmp(name, "target", 3) == 0)
		TerminalPrintGet_TARGET();
	else if (strncmp(name, "mode", 3) == 0)
		TerminalPrintGet_MODE();
	else if (strncmp(name, "serial", 3) == 0)
		TerminalPrintGet_SERIAL();
	else if (strncmp(name, "buzzer", 3) == 0)
		TerminalPrintGet_BUZZER();
	else
		microrl_printStringWithEndl("Unknown parameter for command 'GET'");


//	int funcIndex = prv_getFuncArrayIndex(name);
//	if (funcIndex == (-1))																// не нашли нужного параметра для "GET"
//	{
//		microrl_printStringWithEndl("Command not found.");
//		return;
//	}
//	if (terminalFuncArray[funcIndex].help != NULL)										//
//	{
//		microrl_printStringWithEndl(terminalFuncArray[funcIndex].help);
//	}
//	else
//	{
//		microrl_printStringWithEndl("Help is not available for this command.");
//	}
}
//=======================================================================================


//=======================================================================================
void TerminalPrintGet_PWR(void)
{
//	// Сосотояние системы питания
//	microrl_printStringWithEndl("[PWR]");
//	MP_Power_GetPowerRegister();														// Получить состояние из регистров управления питанием
//
////	sprintf(str, "PWR_5V0=%s\n", 		((MP_ExchangeStruct.Power_State->EN_5V0  	 == POWERSTATE_DISABLE)?("OFF"):("ON")) );	microrl_printString(str);
////	sprintf(str, "PWR_10V=%s\n", 		((MP_ExchangeStruct.Power_State->EN_10V 	 == POWERSTATE_DISABLE)?("OFF"):("ON")) );	microrl_printString(str);
//	sprintf(str, "PWR_5V0=%s\n", 		((ExchangeStruct.Power_State->PG_5V0  	 == POWERSTATE_DISABLE)?("OFF"):("ON")) );	microrl_printString(str);
//	sprintf(str, "PWR_10V=%s\n", 		((ExchangeStruct.Power_State->PG_10V 	 == POWERSTATE_DISABLE)?("OFF"):("ON")) );	microrl_printString(str);
//	sprintf(str, "PWR_EOP=%s\n", 		((ExchangeStruct.Power_State->EN_EOP 	 == POWERSTATE_DISABLE)?("OFF"):("ON")) );	microrl_printString(str);
//	sprintf(str, "PWR_ENCODER=%s\n", 	((ExchangeStruct.Power_State->EN_ENCODER  == POWERSTATE_DISABLE)?("OFF"):("ON")) );	microrl_printString(str);
//	sprintf(str, "PWR_CPU=%s\n", 	 	((ExchangeStruct.Power_State->EN_MAIN_CPU == POWERSTATE_DISABLE)?("OFF"):("ON")) );	microrl_printString(str);
//	sprintf(str, "PWR_CPLD=%s\n",	 	((ExchangeStruct.Power_State->EN_CPLD     == POWERSTATE_DISABLE)?("OFF"):("ON")) );	microrl_printString(str);
//	TerminalPrintGet_PWRSource();
}
//=======================================================================================
void TerminalPrintGet_PWRSource(void)
{
//	// От чего питаемся
//	sprintf(str, "PWR_SRC=");																				microrl_printString(str);
//	switch (ExchangeStruct.Power_State->PWR_Source)
//	{
//		case POWERSOURCE_BAT:
//			microrl_printStringWithEndl("BAT");
//			break;
//		case POWERSOURCE_EXT:
//			microrl_printStringWithEndl("EXT");
//			break;
//		case POWERSOURCE_BACKUP:
//			microrl_printStringWithEndl("BACKUP");
//			break;
//		default:
//			microrl_printStringWithEndl("UNKNOWN");
//			break;
//	}
}
//=======================================================================================

void TerminalPrintGet_COMPASS(void)
{
//	// Магниторезистивный компас HoneyWell HMC6343
//	microrl_printStringWithEndl("[COMPASS-6343]");
//
//	sprintf(str, "COMPASS_HEADING=%+3.1f\n", 		ExchangeStruct.HMC6343_ResultAll->Heading );		microrl_printString(str);
//	sprintf(str, "COMPASS_ROLL=%+3.1f\n", 			ExchangeStruct.HMC6343_ResultAll->Roll );		microrl_printString(str);
//	sprintf(str, "COMPASS_PITCH=%+3.1f\n", 			ExchangeStruct.HMC6343_ResultAll->Pitch );		microrl_printString(str);
//	sprintf(str, "COMPASS_TEMPERATURE=%+3.1f\n", 	ExchangeStruct.HMC6343_ResultAll->Temperature );	microrl_printString(str);

}
//=======================================================================================
void TerminalPrintGet_KEYS(void)
{
//	// Кнопки
//	microrl_printStringWithEndl("[KEYS]");
//	sprintf(str, "STATE=0x%04X\n", ExchangeStruct.Keys_State->Buttons);																microrl_printString(str);
//	//sprintf(str, "ENCODER_VAL=%d\n", 				(int8_t)(MP_ExchangeStruct.Encoder_State->MP_Encoder_Value - ENCODER_VAL_DEFAULT));	microrl_printString(str);
//	sprintf(str, "ENCODER_VAL=%u\n", 				(uint8_t)(ExchangeStruct.Encoder_State->MP_Encoder_Value));						microrl_printString(str);
//	sprintf(str, "ENCODER_DIR=%lu\n", 				ExchangeStruct.Encoder_State->MP_Encoder_Dir);									microrl_printString(str);
//	sprintf(str, "ENCODER_DELTA=%d\n", 				(int8_t)ExchangeStruct.Encoder_State->MP_Encoder_Delta);							microrl_printString(str);
}
//=======================================================================================
void TerminalPrintGet_GPS(void)
{
//	microrl_printStringWithEndl("[GPS]");
//	sprintf(str, "GPS_FIX=%d\n", ExchangeStruct.GPS_info->fix);microrl_printString(str);
//	// Широта
////	printf("GPS_LATITUDE=%2.8f\n", MP_ExchangeStruct.GPS_info->lat);
//	sprintf(str, "GPS_LATITUDE=%2.8fN\n", nmea_ndeg2degree(ExchangeStruct.GPS_info->lat));microrl_printString(str);  // Google, YandexMaps
//
//	// Долгота
////	printf("GPS_LONGITUDE=%03.8f\n", MP_ExchangeStruct.GPS_info->lon);
//	sprintf(str, "GPS_LONGITUDE=%03.8fE\n", nmea_ndeg2degree(ExchangeStruct.GPS_info->lon));microrl_printString(str);  // Google, YandexMaps
//
//	// Высота по спутникам
//	sprintf(str, "GPS_ALTITUDE=%.1f\n", ExchangeStruct.GPS_info->elv);microrl_printString(str);
//
//	// Курс по спутникам
//	sprintf(str, "GPS_DIRECTION=%.1f\n", ExchangeStruct.GPS_info->direction);microrl_printString(str);
//
//	// Скорость по спутникам
//	sprintf(str, "GPS_SPEED=%.1f\n", ExchangeStruct.GPS_info->speed);microrl_printString(str);
//	if (ExchangeStruct.GPS_info->utc.year != 9999)
//	{
//		sprintf(str, "GPS_DATE=%04d-%02d-%02d\n", 1900 + ExchangeStruct.GPS_info->utc.year, ExchangeStruct.GPS_info->utc.mon, ExchangeStruct.GPS_info->utc.day);microrl_printString(str);
//		sprintf(str, "GPS_TIME=%02d:%02d:%02d\n", ExchangeStruct.GPS_info->utc.hour + TIME_ZONE, ExchangeStruct.GPS_info->utc.min, ExchangeStruct.GPS_info->utc.sec);microrl_printString(str);
////		printf("GPS_TIME=%02d:%02d:%02d\n", MP_ExchangeStruct.GPS_info->utc.hour , MP_ExchangeStruct.GPS_info->utc.min, MP_ExchangeStruct.GPS_info->utc.sec);
//	}
//	else
//	{
//		microrl_printStringWithEndl("GPS_DATE=NONE");
//		microrl_printStringWithEndl("GPS_TIME=NONE");
//	}
//
//	// Количество спутников [используемых/всего]
//	sprintf(str, "GPS_SATS_ALL_INUSE=%02d\n", ExchangeStruct.GPS_info->satinuse);microrl_printString(str); //GPS+GLONASS - будет показывать больше чем 12
//	sprintf(str, "GPS_SATS_ALL_INVIEW=%02d\n", ExchangeStruct.GPS_info->satinfo.inview);microrl_printString(str);
//	//sprintf(str, "GPS_SATS_ALL_INVIEW=%02d\n", 24);microrl_printString(str);
//
}
//=======================================================================================
void TerminalPrintGet_TIME(void)
{
//	microrl_printStringWithEndl("TIME by GPS/GLONASS:");
//	sprintf(str, "GPS_DATE = %04d-%02d-%02d\nGPS_TIME =   %02d:%02d:%02d\n", 1900 + ExchangeStruct.GPS_info->utc.year, GPS_info.utc.mon, ExchangeStruct.GPS_info->utc.day, ExchangeStruct.GPS_info->utc.hour + TIME_ZONE, ExchangeStruct.GPS_info->utc.min, ExchangeStruct.GPS_info->utc.sec);
//	microrl_printStringWithEndl(str);
}
//=======================================================================================
void TerminalPrintGet_LRF(void)
{
//	MP_LRF1502_SetDefaultState();													// обнуляем статус дальномера
//
//	if (MP_Power_Get_10V() == POWERSTATE_ENABLE)									// если питание дальномера включено
//	{
//		MP_LRF1502_GetStatus(&huart5, MP_LRF1502_TPG_ON, MP_LRF1502_RETURN_SECOND_RANGE);	// сканим стстус дальномера, записываем сосотяние MP_LRF1502_HVPS_State
//	}
//	// Дальномер
//	microrl_printStringWithEndl("[LRF]");
//	sprintf(str, "LRF_POWER_ON=%d\n", MP_Power_Get_10V());												microrl_printString(str);
//	sprintf(str, "LRF_READY_TO_FIRE=%d\n", ExchangeStruct.LRF1502_State->ReadyToFire);				microrl_printString(str);
//	sprintf(str, "LRF_HVPS_ON=%d\n", ExchangeStruct.LRF1502_State->HVPS_On);							microrl_printString(str);
//	sprintf(str, "LRF_TARGET_DIST_LAST=%d\n", ExchangeStruct.LRF1502_State->Target1Last);			microrl_printString(str);
//	sprintf(str, "LRF_TARGET_NUM=%d\n", ExchangeStruct.LRF1502_State->TargetsNum);					microrl_printString(str);
//	sprintf(str, "LRF_TARGET_DIST=%d\n", ExchangeStruct.LRF1502_State->Target1);						microrl_printString(str);
//	sprintf(str, "LRF_NEW_DATA=%d\n", ExchangeStruct.LRF1502_State->NewDataAvailable);				microrl_printString(str);
//	sprintf(str, "LRF_SHOTS_COUNT=%lu\n", ExchangeStruct.LRF1502_Maintenance->ShotCount);			microrl_printString(str);
}
//=======================================================================================
void TerminalPrintGet_TARGET(void)
{
//	// Координаты цели
//	//char buf[1024];
//	double pt1[2], pt2[2];
//	double azi1, dist;
//
//	azi1 = ExchangeStruct.HMC6343_ResultAll->Heading;
//	dist = ExchangeStruct.LRF1502_State->Target1Last;
//
//	pt1[0] = Radians(nmea_ndeg2degree(ExchangeStruct.GPS_info->lat));
//	pt1[1] = Radians(nmea_ndeg2degree(ExchangeStruct.GPS_info->lon));
//
////    pt1[0] = Radians(55.77804000);
////    pt1[1] = Radians(37.73787283);
////    azi1=153.16;
////    dist=423;
//
//	SphereDirect(pt1, Radians(azi1), dist / A_E, pt2);	// Решение прямой задачи
//
//	if (dist >0)
//	{
//		microrl_printStringWithEndl("[TARGET]");
//		sprintf(str, "DIST=%d\n", 		ExchangeStruct.LRF1502_State->Target1Last);			microrl_printString(str);
//		sprintf(str, "AZIM=%+3.1f\n", 	ExchangeStruct.HMC6343_ResultAll->Heading );			microrl_printString(str);
//
//
//		// Широта
//	//	printf("TARGET_LATITUDE=%2.8f\n", MP_ExchangeStruct.GPS_info->lat);
//
//		sprintf(str, "TARG_LAT=%2.8fN\n", Degrees(pt2[0]));  									microrl_printString(str);		// Google, YandexMaps
//
//		// Долгота
//		//printf("TARGET_LONGITUDE=%03.8f\n", MP_ExchangeStruct.GPS_info->lon);
//		sprintf(str, "TARG_LON=%03.8fE\n", Degrees(pt2[1]));  									microrl_printString(str);		// Google, YandexMaps
//
//		// Широта
//		sprintf(str, "POSN_LAT=%2.8fN\n", Degrees(pt1[0]));  									microrl_printString(str);		// Google, YandexMaps
//		// Долгота
//		sprintf(str, "POSN_LON=%03.8fE\n", Degrees(pt1[1]));  									microrl_printString(str);		// Google, YandexMaps
//
//
////		sprintf(str, "POSN=%2.8fN %03.8fE\n", Degrees(pt1[0]), Degrees(pt1[1]));  						microrl_printString(str);		// Google, YandexMaps
////		sprintf(str, "TARG=%2.8fN %03.8fE\n", Degrees(pt2[0]), Degrees(pt2[1]));  						microrl_printString(str);		// Google, YandexMaps
//
//	}
}
//=======================================================================================
void TerminalPrintGet_FIRE(void)
{
	// принудительное измерение по команде от дальномера
//	// измерить расстояние дальномером
//	MP_Power_Set_10V(POWERSTATE_ENABLE);												// включить преобразователь питания дальномера 16V->10V
//	osTimerStart(LRF_POWER_TimerHandle, TIMER_LRF_POWER_TIMEOUT);						// запускаем таймер для выделенного времени работы основного источника питания дальномера
//	osTimerStart(LRF_HVPS_TimerHandle,  TIMER_LRF_HVPS_TIMEOUT);						// запускаем таймер для выделенного времени работы высоковольтного источника питания дальномера
//	microrl_printStringWithEndl("[FIRE]");
//
//	osDelay(20);																		// Задержка, пока дальномер запустится по питанию
//	MP_LRF1502_SetDefaultState();														// обнуляем статус дальномера
//	ExchangeStruct.LRF1502_State->HVPS_State = MP_LRF1502_HVPS_ON;					// включаем высоковольтный источник питания дальномера
//	MP_LRF1502_GetStatus(&huart5, MP_LRF1502_TPG_ON, MP_LRF1502_RETURN_SECOND_RANGE);	// засылаем команду включения HVPS и получаем статус
//
//	uint16_t Error_Timer = 150;															// защитный таймер на 50*150 мс чтобы не завис при отключенном дальномере
//	while (!ExchangeStruct.LRF1502_State->ReadyToFire)
//	{
//		osDelay(50);																	// Задержка, пока дальномер не будет готов к замеру (зарядится HVPS)
//		MP_BUZZER_Beep_TickTIM();														// квакнем
//		Error_Timer--;
//		if (Error_Timer == 0)
//		{
//			microrl_printStringWithEndl("LRF Timeout...");
//			return;
//		}
//	}
//	MP_LRF1502_MeasureTheRange(&huart5);												// делаем замер дальномерм
//	MP_BUZZER_Beep_ShortTIM();															// квакнем
//	osTimerStart(LRF_POWER_TimerHandle, TIMER_LRF_POWER_TIMEOUT);						// еще раз запускаем таймер обратного отсчета для времени работы основного источника, чтобы таймаут шел уже от измерения
//	osTimerStart(LRF_HVPS_TimerHandle,  TIMER_LRF_HVPS_TIMEOUT);						// еще раз запускаем таймер обратного отсчета для времени работы HVPS, чтобы таймаут шел уже от измерения
//
//
//	TerminalPrintGet_TARGET();
}
//=======================================================================================
void TerminalPrintGet_MODE(void)
{
	microrl_printString("MODE=");
	if (ExchangeStruct.TerminalMode)
		microrl_printStringWithEndl("COMMAND");
	else
		microrl_printStringWithEndl("AUTO");
}
//=======================================================================================
void TerminalPrintGet_SERIAL(void)
{
	microrl_printString("SERIAL_NUMBER=");
	microrl_printStringWithEndl(ExchangeStruct.DeviceSerialNumber);
}
//=======================================================================================
void TerminalPrintGet_BAT(void)
{
//	uint16_t TimeOut = 25;
//	while (!ExchangeStruct.Battery_State->DataReady)									// Ждем с таймаутом пока не дочитаются данные из АЦП
//	{
//		TimeOut--;
//		if (TimeOut == 0)
//			break;
//		osDelay(2);
//	}
//
//	//if (MP_ExchangeStruct.Battery_State->DataReady)
//	{
//		sprintf(str, "PWR_BAT_RAW=%lu\n",	 	ExchangeStruct.Battery_State->ADC_RAW);				microrl_printString(str);
//		sprintf(str, "PWR_BAT_VOLT=%3.2f\n", 	ExchangeStruct.Battery_State->battery_cell_volts);	microrl_printString(str);
//		sprintf(str, "PWR_BAT_CHG=%d\n", 		ExchangeStruct.Battery_State->battery_level);		microrl_printString(str);
//		TerminalPrintGet_PWRSource();
//	}
////	else
////	{
////		sprintf(str, "PWR_BAT_RAW=0\n"); 		microrl_printString(str);
////		sprintf(str, "PWR_BAT_VOLT=0\n"); 		microrl_printString(str);
////		sprintf(str, "PWR_BAT_CHG=0\n"); 		microrl_printString(str);
////
////	}
}
//=======================================================================================
void TerminalPrintGet_BATCatlibration(void)
{
//
//	sprintf(str, "Bat cal: 3V3 =  %02.4lf\n", ExchangeStruct.Battery_State->ADC_Ref_Voltage );		microrl_printString(str);
//	sprintf(str, "Bat cal: 12V = %02.4lf\n",  ExchangeStruct.Battery_State->ADC_12V_Voltage );		microrl_printString(str);
}
//=======================================================================================
void TerminalPrintGet_BUZZER(void)
{
	microrl_printString("BUZZER=");
	if (BUZZER_BuzzerState)
		microrl_printStringWithEndl("ON");
	else
		microrl_printStringWithEndl("OFF");

}
//=======================================================================================
