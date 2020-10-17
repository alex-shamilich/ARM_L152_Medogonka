// terminal function: RESET
#include <string.h>				// for strcmp, strstr

#include "microrl_func.h"
#include "microrl_func_reset.h"
//#include "microrl_func_get.h"

#include "ExchangeStruct.h"
#include "FreeRTOSUser.h"



//=======================================================================================
int prv_TerminalFunc_reset(int argc, const char * const * argv)
{
//	microrl_printString ("Set something...");
//	microrl_printEndl();
	osStatus status = osMutexWait(MircoRL_Tx_MutexHandle, portMAX_DELAY);					// ждем пока не освободиться порт терминала на передачу

	if (status == osOK)
	{
		switch (argc)
		{
		case 0:																				// если вызвали reset без параметра - показать help
			prv_printHelpReset();
			break;
		case 1:
			prv_TerminalFuncResetParams(argv[0]);											// реакция на параметры в reset
			break;
		case 2:
			prv_TerminalFuncResetParamsArg(argv[0], argv[1]);								// реакция на параметры с 1 аргументом в set
			break;
		default:																			// двойной уровень параметров не сделан
			microrl_printStringWithEndl("Reset is available only for 1-level commands, yet (Ex:  '>reset all', '>reset gps'");
			break;
		}

		osMutexRelease(MircoRL_Tx_MutexHandle);
	}


	return 0;

}
//=======================================================================================
void prv_printHelpReset(void)
{
	// здесь нужно расписать какие есть параметры у set
	microrl_printStringWithEndl("reset <parameter>");
	microrl_printStringWithEndl("  all           - reset periferial cpu (STM)");
//	microrl_printStringWithEndl("  cpu           - reset main CPU");
//	microrl_printStringWithEndl("  gps           - reset GPS receiver");
	microrl_printEndl();
}
//=======================================================================================
void prv_TerminalFuncResetParams(const char *name)									// set для 1 параметра
{
	UNUSED(name);
//	microrl_printString("Command: ");
//	microrl_printStringWithEndl(name);

	if (strncmp(name, "all", 3) == 0)
	{
		NVIC_SystemReset();
	}
	else if (strncmp(name, "gps", 3) == 0)
	{
		microrl_printStringWithEndl("not realised yet");
	}
	else if (strncmp(name, "cpu", 3) == 0)
	{
		microrl_printStringWithEndl("not realised yet");
	}

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

void prv_TerminalFuncResetParamsArg(const char *name, const char *param)			// set для 2 параметров
{
	UNUSED(name);
	UNUSED(param);
//	microrl_printString("Command: ");
//	microrl_printStringWithEndl(name);
//	microrl_printString("Param: ");
//	microrl_printStringWithEndl(param);





}
//=======================================================================================
