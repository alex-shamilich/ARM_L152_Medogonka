// terminal function: CLEAR

#include "microrl_func.h"
#include "microrl_func_clear.h"

//=======================================================================================
#define UNUSED(x) ((void)(x))

//=======================================================================================
int prv_TerminalFunc_clear(int argc, const char * const * argv)
{
	UNUSED(argc);
	UNUSED(argv);

	microrl_printString ("\033[2J");    // ESC seq for clear entire screen
	microrl_printString ("\033[H");     // ESC seq for move cursor at left-top corner
	return 0;
}
//=======================================================================================


