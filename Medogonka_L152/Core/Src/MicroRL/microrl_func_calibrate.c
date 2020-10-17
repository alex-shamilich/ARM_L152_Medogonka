// terminal function: CALIBRATE
#include <string.h>				// for strcmp, strstr
#include <stdio.h>

#include "microrl_func.h"
#include "microrl_func_calibrate.h"

#include "FreeRTOSUser.h"

#include "EEPROM.h"
//#include "HMC6343.h"


extern char str[255];

//=======================================================================================

int prv_TerminalFunc_calibrate(int argc, const char * const * argv)
{
////	microrl_printString ("Compass calibration...");
////	microrl_printEndl();
//
//	osStatus status = osMutexWait(MircoRL_Tx_MutexHandle, portMAX_DELAY);					// ждем пока не освободиться порт терминала на передачу
//
//	if (status == osOK)
//	{
//		switch (argc)
//		{
//		case 0:																				// если вызвали calibrate без параметра - показать help
//			prv_printHelpCalibrate();
//			break;
//		case 1:
//			prv_TerminalFuncCalibrateParams(argv[0]);										// реакция на параметр в calibrate
//			break;
//		case 2:
//			prv_TerminalFuncCalibrateParamsArg(argv[0], argv[1]);							// реакция на параметр и аргумент в calibrate
//			break;
//		default:																			// тройной уровень параметров не сделан (пока)
//			microrl_printStringWithEndl("Calibrate is available only for 1,2-level commands, yet (Ex:  '>calibrate gps'");
//			break;
//		}
//
//		osMutexRelease(MircoRL_Tx_MutexHandle);
//	}
	return 0;
}
//=======================================================================================
void prv_printHelpCalibrate(void)
{
	// здесь нужно расписать какие есть параметры у calibrate
	microrl_printStringWithEndl("calibrate <parameter> - compass calibration");
	microrl_printStringWithEndl("  start        - Start compass calibration");
	microrl_printStringWithEndl("  stop         - Stop compass calibration");
	microrl_printStringWithEndl("  help         - Info about compass calibration");
	microrl_printStringWithEndl("  deviation    - Get compass deviation angle");
	microrl_printStringWithEndl("  decl         - Get compass declination angle");
	microrl_printStringWithEndl("  devset X     - Set compass deviation angle (-180.0 .. 180.0)");
	microrl_printStringWithEndl("  declset X    - Set compass declination angle (-180.0 .. 180.0)");
	//	microrl_printStringWithEndl("  result       - Compass calibration results");
	//	microrl_printStringWithEndl("  clear        - Clear compass calibration");
	microrl_printEndl();
}
//=======================================================================================
void prv_TerminalFuncCalibrateParams(const char *name)
{
//	if (strncmp(name, "start", 3) == 0)
//	{
//		HMC6343_enterCalMode();
//		sprintf(str, "Compass calibration started\n");				microrl_printString(str);
//	}
//	else if (strncmp(name, "stop", 3) == 0)
//	{
//		HMC6343_exitCalMode();
//	}
//	else if (strncmp(name, "help", 4) == 0)
//	{
//		sprintf(str, "The HMC6343 provides a user calibration routine.\n");																												microrl_printString(str);
//		sprintf(str, "After entering the calibration mode by 'calibration start'\n");																									microrl_printString(str);
//		sprintf(str, "  rotate the device reasonably steady for 360 degrees about the Y (Left - Right) axis\n");																		microrl_printString(str);
//		sprintf(str, "  and then 360 degrees about Z (Up - Down) axis.\n");																												microrl_printString(str);
//		sprintf(str, "During the first rotation, maintain the Y axis at Level as much as possible.\n");																					microrl_printString(str);
//		sprintf(str, "Maintain the Z axis upright as much as possible during the second rotation and until\n");																			microrl_printString(str);
//		sprintf(str, "the exit calibration command is issued.\n");																														microrl_printString(str);
//		sprintf(str, "The first rotation can also be done by rotating 360 degrees about X axis.\n");																					microrl_printString(str);
//		sprintf(str, "Then exit calibration by 'calibration stop'.\n\n");																												microrl_printString(str);
//
//		sprintf(str, "The calibration routine collects these readings to correct for hard-iron distortions of the magnetic field.\n");													microrl_printString(str);
//		sprintf(str, "These hard-iron effects are due to magnetized materials nearby the HMC6343 compass\n");																			microrl_printString(str);
//		sprintf(str, "that in a fixed position with respect to the end user platform.\n");																								microrl_printString(str);
//		sprintf(str, "An example would be the magnetized chassis or engine block of a vehicle in which the compass is mounted onto.\n");												microrl_printString(str);
//		sprintf(str, "Upon exiting the calibration mode, the resulting magnetometer offsets are updated.\n");																			microrl_printString(str);
//	}
//
////	else if (strncmp(name, "result", 3) == 0)
////	{
////
////	}
////	else if (strncmp(name, "clear", 3) == 0)
////	{
////
////	}
//	else if (strncmp(name, "dev", 3) == 0)
//	{
//		double Angle = HMC6343_readDeviation() / 10.0 ;
//		sprintf(str, "Compass deviation angle = %3.1f\n",	Angle );				microrl_printString(str);
//	}
//	else if (strncmp(name, "decl", 3) == 0)
//	{
//		double Angle = HMC6343_readVariation() / 10.0 ;
//		sprintf(str, "Compass declination angle = %3.1f\n",	Angle );				microrl_printString(str);
//	}
//	else
//		microrl_printStringWithEndl("Unknown parameter for command 'calibrate'");
}
//=======================================================================================
void prv_TerminalFuncCalibrateParamsArg(const char *name, const char *param)		// calibrate для 2 параметров
{
//	microrl_printString("Command: ");
//	microrl_printStringWithEndl(name);
//	microrl_printString("Param: ");
//	microrl_printStringWithEndl(param);


//	if (strncmp(name, "devset", 6) == 0)												// Коррекция механического положения компаса -180.0 .. +180.0
//	{
//		double  Angle = 0;
//		if ( (sscanf(param, "%lf", &Angle) == EOF) || (Angle < -180.00 ) || (Angle > 180.0) )
//		{
//			microrl_printStringWithEndl("Incorrect value for compass deviation angle (-180.0 .. 180.0 )");
//			return;
//		}
//		else
//		{
//			int16_t DevAngle = (int16_t)(Angle * 10.0);
//			HMC6343_writeDeviation(DevAngle);
//			sprintf(str, "Compass declination angle set to = %3.1f\n",	Angle );	microrl_printString(str);
//			EEPROM_OptionsSave();
//		}
//	}
//	else if (strncmp(name, "declset", 7) == 0)											// Коррекция магнитного склонения компаса -180.0 .. +180.0
//	{
//		double  Angle = 0;
//		if ( (sscanf(param, "%lf", &Angle) == EOF) || (Angle < -180.00 ) || (Angle > 180.0) )
//		{
//			microrl_printStringWithEndl("Incorrect value for compass declination angle (-180.0 .. 180.0 )");
//			return;
//		}
//		else
//		{
//			int16_t DecAngle = (int16_t)(Angle * 10.0);
//			HMC6343_writeVariation(DecAngle);
//			sprintf(str, "Compass declination angle set to = %3.1f\n",	Angle );	microrl_printString(str);
//			EEPROM_OptionsSave();
//		}
//	}

}
//=======================================================================================
