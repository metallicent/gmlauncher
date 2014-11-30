
#include "includes.h"

CMenuEntry::CMenuEntry(CLauncherProgram *program, string text)
{
	this->program = program;
	this->text = text;
}

CMenuEntry::~CMenuEntry(void)
{
}
