
#include "includes.h"

CMenuEntry::CMenuEntry(CLauncherProgram *program, string text)
{
	this->program = program;
	this->text = text;
}

CMenuEntry::~CMenuEntry(void)
{
}



CCommandMenuEntry::CCommandMenuEntry(CLauncherProgram *program, string text, string command) : CMenuEntry(program, text)
{
	this->command = command;
}

CCommandMenuEntry::~CCommandMenuEntry(void)
{
}

void CCommandMenuEntry::Trigger(void)
{
	system(command.c_str());
}



CScreenMenuEntry::CScreenMenuEntry(CLauncherProgram *program, string text, CScreenTemplate *screen_template) : CMenuEntry(program, text)
{
	this->screen_template = screen_template;
}

CScreenMenuEntry::~CScreenMenuEntry(void)
{
}

void CScreenMenuEntry::Trigger(void)
{
	CScreen *screen = screen_template->CreateScreen();
	GetProgram()->ChangeToScreen(screen);
}




CQuitMenuEntry::CQuitMenuEntry(CLauncherProgram *program, string text) : CMenuEntry(program, text)
{
}

CQuitMenuEntry::~CQuitMenuEntry(void)
{
}

void CQuitMenuEntry::Trigger(void)
{
	GetProgram()->Quit();
}
