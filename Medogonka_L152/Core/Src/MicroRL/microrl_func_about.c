// terminal function: ABOUT

#include "main.h"
#include "microrl_func.h"
#include "microrl_func_about.h"

#include "ExchangeStruct.h"
#include "FreeRTOSUser.h"

//=======================================================================================
//static int prv_TerminalFunc_about(int argc, const char * const * argv)
//{
//	microrl_printString("Microrl based terminal. Ver. ");
//	microrl_printStringWithEndl(MICRORL_LIB_VER);
//	return 0;
//}
//=======================================================================================
int prv_TerminalFunc_about(int argc, const char * const * argv)
{
	UNUSED(argc);
	UNUSED(argv);
	osStatus status = osMutexWait(MircoRL_Tx_MutexHandle, portMAX_DELAY);								// ждем пока не освободиться порт терминала на передачу

	if (status == osOK)
	{
		microrl_printString("Medogonka. Version: ");
		microrl_printString(FIRMWARE_VER);
		microrl_printString("  ( ");
		microrl_printString(__DATE__);
		microrl_printString("  ");
		microrl_printString(__TIME__);
		microrl_printStringWithEndl(" )");
		osMutexRelease(MircoRL_Tx_MutexHandle);
	}

	return 0;
}
//=======================================================================================
