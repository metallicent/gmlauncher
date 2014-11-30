
#include "includes.h"

CScreen::CScreen(CLauncherProgram *program, CScreen *previous)
{
	this->program = program;
	this->previous_screen = previous;
}
