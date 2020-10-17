// terminal function: HELP
//#include <string.h>				// for strcmp, strstr

#include "microrl_func.h"
#include "microrl_func_help.h"

#include "ExchangeStruct.h"
#include "FreeRTOSUser.h"

//extern char str[255];

//=======================================================================================


//=======================================================================================
int prv_TerminalFunc_help(int argc, const char * const * argv)
{
	osStatus status = osMutexWait(MircoRL_Tx_MutexHandle, portMAX_DELAY);				// ждем пока не освободиться порт терминала на передачу

	if (status == osOK)
	{
		switch (argc)
		{
		case 0:
			prv_printMainHelp();
			break;
		case 1:
			prv_printTerminalFuncHelp(argv[0]);
			break;
		default:
			microrl_printStringWithEndl("Help is available only for high-level commands. It isn't available for subcommands.");
			break;
		}
		osMutexRelease(MircoRL_Tx_MutexHandle);
	}

	return 0;
}
//=======================================================================================
void prv_printMainHelp()
{
	microrl_printStringWithEndl("Hint: Use <TAB> key for auto-completion");
	microrl_printStringWithEndl("Hint: Use <Ctrl+C> keys to system reset");
	microrl_printStringWithEndl("Type \"help\" <command> for more details.");
	microrl_printEndl();
	microrl_printStringWithEndl("Available commands:");
	int i;
	for (i = 0; i < terminalFuncArrayIndex; ++i) {
		microrl_printString("  ");
		microrl_printString(terminalFuncArray[i].name);
		microrl_printString("\033[20G");												//  подвинуть курсор в 20ю позицию текущей строки (https://www.opennet.ru/base/dev/console_ctl.txt.html)
		microrl_printString(terminalFuncArray[i].help);
		microrl_printEndl();
		//microrl_printString(" ");
	}
	microrl_printEndl();
}
//=======================================================================================
void prv_printTerminalFuncHelp(const char *name)
{
	int funcIndex = prv_getFuncArrayIndex(name);
	if (funcIndex == (-1))	{
		microrl_printStringWithEndl("Command not found.");
		return;
	}
	if (terminalFuncArray[funcIndex].help != NULL)	{
		microrl_printStringWithEndl(terminalFuncArray[funcIndex].help);
	}
	else	{
		microrl_printStringWithEndl("Help is not available for this command.");
	}
}
//=======================================================================================
