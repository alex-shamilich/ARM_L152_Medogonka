// terminal function: SET
#include <string.h>				// for strcmp, strstr
#include <stdio.h>

#include "microrl_func.h"
#include "microrl_func_set.h"
#include "microrl_func_get.h"

#include "ExchangeStruct.h"
#include "FreeRTOSUser.h"

#include "EEPROM.h"

extern char str[255];


//=======================================================================================
int prv_TerminalFunc_set(int argc, const char * const * argv)
{
//	microrl_printString ("Set something...");
//	microrl_printEndl();
	osStatus status = osMutexWait(MircoRL_Tx_MutexHandle, portMAX_DELAY);					// ждем пока не освободиться порт терминала на передачу

	if (status == osOK)
	{
		switch (argc)
		{
		case 0:																				// если вызвали get без параметра - показать help
			prv_printHelpSet();
			break;
		case 1:
			prv_TerminalFuncSetParams(argv[0]);												// реакция на параметры в set
//			EEPROM_OptionsSave();
			break;
		case 2:
			prv_TerminalFuncSetParamsArg(argv[0], argv[1]);									// реакция на параметры с 1 аргументом в set
//			EEPROM_OptionsSave();
			break;
		case 3:																				// реакция на параметры с 2 аргументами в set
			if ( (strncmp(argv[0], "pwroff", 5) == 0) && (strncmp(argv[1], "5v", 2) == 0))	// отложенное выключение питания +5V, чтобы raspberry успел завершить работу
			{
//				int  Delay = 0;
//				if ( (sscanf(argv[2], "%d", &Delay) == EOF) || (Delay <=0 ) || (Delay > 1000) )
//				{
//					microrl_printStringWithEndl("Incorrect value for pwroff timeout (1..1000 sec)");
//					return 1;
//				}
//				else
//				{
//					osDelay(Delay*1000);
//					MP_Power_Set_5V0(POWERSTATE_DISABLE);
//				}
			}
			if ( (strncmp(argv[0], "mode", 5) == 0) && (strncmp(argv[1], "auto", 2) == 0))	// время для интервала отсылки данных в автоматическом режиме (в миллисекундах)
			{
				uint32_t  Interval = 0;
				if ( (sscanf(argv[2], "%lu", &Interval) == EOF) || (Interval <100 ) || (Interval > 100000) )
				{
					microrl_printStringWithEndl("Incorrect value for automode interval (100..100000 msec)");
					return 1;
				}
				else
				{
					ExchangeStruct.TerminalModeAuto_interval = Interval;
					sprintf(str, "Auto mode interval = %lu msec.\n",	 	ExchangeStruct.TerminalModeAuto_interval );				microrl_printString(str);
				}

			}
//			EEPROM_OptionsSave();
			break;
		default:																			// тройной уровень параметров не сделан (пока)
			microrl_printStringWithEndl("Set is available only for 1,2-level commands, yet (Ex:  '>set pwr', '>set pwr on'");
			break;
		}

		osMutexRelease(MircoRL_Tx_MutexHandle);
	}


	return 0;

}
//=======================================================================================
void prv_printHelpSet(void)
{
	// здесь нужно расписать какие есть параметры у set
	microrl_printStringWithEndl("set <parameter>");
	microrl_printStringWithEndl("  buzzer X      - Set buzzer state (on|off)");
	microrl_printStringWithEndl("  defaults      - Set factory default settings");
	microrl_printStringWithEndl("  mode X        - AUTO or by requests (auto|cmd)");
	microrl_printStringWithEndl("  mode auto X   - AUTO mode interval (100..100 000 msec)");
	microrl_printStringWithEndl("  options       - Manage options in EEPROM (format|defaults|load|save)");
	microrl_printStringWithEndl("  pwrcalref1 X  - Set ADC battery calibration: REF voltage  3.3V (0..10 volts)");
	microrl_printStringWithEndl("  pwrcalref2 X  - Set ADC battery calibration: REF voltage 12.0V (0..20 volts)");
	microrl_printStringWithEndl("  pwron X       - Set power state ON  (5v|10v|eop|encoder|hvps|cpu|cpld)");
	microrl_printStringWithEndl("  pwroff X      - Set power state OFF (5v|10v|eop|encoder|hvps|cpu|cpld)");
	microrl_printStringWithEndl("  pwroff 5v X   - Set power OFF with timeout (1..1000 sec)");

	//microrl_printStringWithEndl("  gps			- Set gps mode - (GPS/GLONASS)");
	//microrl_printStringWithEndl("  bat			- Battery calibration constants");

	//microrl_printStringWithEndl("  serial	- set serial number");	//undocumented command
	microrl_printEndl();
}
//=======================================================================================
void prv_TerminalFuncSetParams(const char *name)									// set для 1 параметра
{
	UNUSED(name);
//	microrl_printString("Command: ");
//	microrl_printStringWithEndl(name);

//	else if (strncmp(name, "pwr", 3) == 0)
//		TerminalPrintGet_BAT();
//	else if (strncmp(name, "bat", 3) == 0)
//		TerminalPrintGet_BAT();
//	else if (strncmp(name, "gps", 3) == 0)
//		TerminalPrintGet_COMPASS();
//	else if (strncmp(name, "", 3) == 0)
//		TerminalPrintGet_KEYS();
//	else if (strncmp(name, "", 3) == 0)
//		TerminalPrintGet_GPS();
//	else if (strncmp(name, "time", 3) == 0)
//		TerminalPrintGet_TIME();
//	else if (strncmp(name, "lrf", 3) == 0)
//		TerminalPrintGet_LRF();
//	else if (strncmp(name, "target", 3) == 0)
//		TerminalPrintGet_TARGET();
//	else if (strncmp(name, "mode", 3) == 0)
//		TerminalPrintGet_MODE();
//	else if (strncmp(name, "serial", 3) == 0)
//		TerminalPrintGet_SERIAL();
//	else
//		microrl_printStringWithEndl("Unknown parameter for command 'GET'");

}
//=======================================================================================

void prv_TerminalFuncSetParamsArg(const char *name, const char *param)			// set для 2 параметров
{
//	microrl_printString("Command: ");
//	microrl_printStringWithEndl(name);
//	microrl_printString("Param: ");
//	microrl_printStringWithEndl(param);


	if (strncmp(name, "mode", 3) == 0)
	{
		if (strncmp(param, "auto", 3) == 0)
		{
			ExchangeStruct.TerminalMode = TERMINALMODE_AUTO;
			EEPROM_OptionsSave();
		}
		else if (strncmp(param, "cmd", 3) == 0)
		{
			ExchangeStruct.TerminalMode = TERMINALMODE_COMMAND;
			EEPROM_OptionsSave();
		}
		else
			microrl_printStringWithEndl("Unknown argument for parameter: mode");
	}
	if (strncmp(name, "buzzer", 3) == 0)
	{
//		if (strncmp(param, "on", 2) == 0)
//		{
//			MP_BUZZER_BuzzerState = BUZZER_STSTE_ON;
//			EEPROM_OptionsSave();
//		}
//		else if (strncmp(param, "off", 2) == 0)
//		{
//			MP_BUZZER_BuzzerState = BUZZER_STSTE_OFF;
//			EEPROM_OptionsSave();
//		}
//		else
//			microrl_printStringWithEndl("Unknown argument for parameter: mode");
	}
	else if (strncmp(name, "pwron", 5) == 0)
	{
//		if (strncmp(param, "5v", 2) == 0)
//		{
//			MP_Power_Set_5V0(POWERSTATE_ENABLE);
//		}
//		else if (strncmp(param, "10v", 3) == 0)
//		{
//			MP_Power_Set_10V(POWERSTATE_ENABLE);
//			osTimerStart(LRF_POWER_TimerHandle, TIMER_LRF_POWER_TIMEOUT);						// запускаем таймер для выделенного времени работы основного источника питания дальномера
//			sprintf(str, "PowerSource +10V activated. Timeout: %lu sec.\n",	 	(uint32_t)(TIMER_LRF_POWER_TIMEOUT/1000) );				microrl_printString(str);
//		}
//		else if (strncmp(param, "eop", 3) == 0)
//			MP_Power_Set_EOP(POWERSTATE_ENABLE);
//		else if (strncmp(param, "encoder", 3) == 0)
//			MP_Power_Set_Encoder(POWERSTATE_ENABLE);
//		else if (strncmp(param, "hvps", 4) == 0)
//		{
//			MP_LRF1502_SetDefaultState();														// обнуляем статус дальномера
//			ExchangeStruct.LRF1502_State->HVPS_State = MP_LRF1502_HVPS_ON;					// включаем высоковольтный источник питания дальномера
//			MP_LRF1502_GetStatus(&huart5, MP_LRF1502_TPG_ON, MP_LRF1502_RETURN_SECOND_RANGE);	// засылаем команду включения HVPS и получаем статус
//			osTimerStart(LRF_HVPS_TimerHandle,  TIMER_LRF_HVPS_TIMEOUT);						// запускаем таймер для выделенного времени работы высоковольтного источника питания дальномера
//		}
//		else if (strncmp(param, "cpu", 3) == 0)
//			MP_Power_Set_MainCPU(POWERSTATE_ENABLE);
//		else if (strncmp(param, "cpld", 4) == 0)
//			MP_Power_Set_CPLD(POWERSTATE_ENABLE);
//		else
//			microrl_printStringWithEndl("Unknown argument for parameter: pwron (5v|10V|eop|encoder|HVPS|cpu|cpld)");
	}
	else if (strncmp(name, "pwroff", 5) == 0)
	{
//		if (strncmp(param, "5v", 2) == 0)
//			MP_Power_Set_5V0(POWERSTATE_DISABLE);
//		else if (strncmp(param, "10v", 3) == 0)
//		{
//			MP_Power_Set_10V(POWERSTATE_DISABLE);
//			osTimerStop(LRF_POWER_TimerHandle);													// останавливаем таймер для выделенного времени работы основного источника питания дальномера
//		}
//		else if (strncmp(param, "eop", 3) == 0)
//			MP_Power_Set_EOP(POWERSTATE_DISABLE);
//		else if (strncmp(param, "encoder", 3) == 0)
//			MP_Power_Set_Encoder(POWERSTATE_DISABLE);
//		else if (strncmp(param, "hvps", 4) == 0)
//		{
//			MP_LRF1502_SetDefaultState();														// обнуляем статус дальномера
//			ExchangeStruct.LRF1502_State->HVPS_State = MP_LRF1502_HVPS_OFF;					// выключаем высоковольтный источник питания дальномера
//			MP_LRF1502_GetStatus(&huart5, MP_LRF1502_TPG_ON, MP_LRF1502_RETURN_SECOND_RANGE);	// засылаем команду выключения HVPS и получаем статус
//			osTimerStop(LRF_HVPS_TimerHandle);													// останавливаем таймер для выделенного времени работы высоковольтного источника питания дальномера
//		}
//		else if (strncmp(param, "cpu", 3) == 0)
//			MP_Power_Set_MainCPU(POWERSTATE_DISABLE);
//		else if (strncmp(param, "cpld", 4) == 0)
//			MP_Power_Set_CPLD(POWERSTATE_DISABLE);
//		else
//			microrl_printStringWithEndl("Unknown argument for parameter: pwroff (5v|10V|eop|encoder|HVPS|cpu|cpld)");
	}
	else if (strncmp(name, "serial", 3) == 0)
	{
		if (strlen(param) == 8)
		{
			strcpy(ExchangeStruct.DeviceSerialNumber, param);
			TerminalPrintGet_SERIAL();
			EEPROM_OptionsSave();
		}
		else
			microrl_printStringWithEndl("Illegal format for serial number. (8 chars/digits)");
	}
	else if (strncmp(name, "pwrcalref1", 10) == 0)										// калибровка батареи - опорное напряжение АЦП 3.3V
	{
//		double  Voltage = ADC_REF_VOLTAGE_DEFAULT;
//		if ( (sscanf(param, "%lf", &Voltage) == EOF) || (Voltage <0.0 ) || (Voltage > 10.0) )
//		{
//			microrl_printStringWithEndl("Incorrect value for calibration ADC REF 3.3 voltage (0.0 .. 10.0 V)");
//			return;
//		}
//		else
//		{
//			ExchangeStruct.Battery_State->ADC_Ref_Voltage = Voltage;
//			sprintf(str, "BAT Calibration: REF 3.3V voltage = %2.2f V.\n",	 	ExchangeStruct.Battery_State->ADC_Ref_Voltage );				microrl_printString(str);
//			EEPROM_OptionsSave();
//		}
	}
	else if (strncmp(name, "pwrcalref2", 10) == 0)										// калибровка батареи - напряжение 12V
	{
//		double  Voltage = ADC_12V_VOLTAGE_DEFAULT;
//		if ( (sscanf(param, "%lf", &Voltage) == EOF) || (Voltage <0.0 ) || (Voltage > 20.0) )
//		{
//			microrl_printStringWithEndl("Incorrect value for calibration ADC REF 12V voltage (0.0 .. 20.0 V)");
//			return;
//		}
//		else
//		{
//			ExchangeStruct.Battery_State->ADC_12V_Voltage = Voltage;
//			sprintf(str, "BAT Calibration: REF 12V voltage = %2.2f V.\n",	 	ExchangeStruct.Battery_State->ADC_12V_Voltage );				microrl_printString(str);
//			EEPROM_OptionsSave();
//		}
	}
	else if (strncmp(name, "optinos", 3) == 0)										// калибровка батареи - напряжение 12V
	{
//		if (strncmp(param, "format", 3) == 0)
//		{
//			EEPROM_Format();
//			microrl_printStringWithEndl("Settings area in EEPROM cleaned");
//		}
//		else if (strncmp(param, "load", 4) == 0)
//		{
//			EEPROM_OptionsLoad();
//			microrl_printStringWithEndl("Options loaded from EEPROM");
//		}
//		else if (strncmp(param, "save", 4) == 0)
//		{
//			EEPROM_OptionsSave();
//			microrl_printStringWithEndl("Options saved to EEPROM");
//		}
//		else if (strncmp(param, "defaults", 3) == 0)
//		{
//	//		EEPROM_Format();
//			EEPROM_OptionsLoadDefault();
//			EEPROM_OptionsSave();
//			EEPROM_OptionsLoad();
//			microrl_printStringWithEndl("Default settings saved to EEPROM & reloaded");
//		}
//		else
//			microrl_printStringWithEndl("Unknown argument for 'set options'");
	}



}
//=======================================================================================
