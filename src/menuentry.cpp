
#include "includes.h"

CMenuEntry::CMenuEntry(CLauncherProgram *program, string text)
{
	this->program = program;
	this->text = text;
	unselected_tex = 0;
	selected_tex = 0;
}

CMenuEntry::~CMenuEntry(void)
{
	if(unselected_tex)
		SDL_DestroyTexture(unselected_tex);
	if(selected_tex)
		SDL_DestroyTexture(selected_tex);
}

void CMenuEntry::Render(MenuType menu_type)
{
	switch(menu_type)
	{
		case LIST_MENU:
			RenderList();
			break;
		case THUMBS_MENU:
			RenderThumb();
			break;
	}
}

void CMenuEntry::RenderList(void)
{
	CTheme *theme = program->GetTheme();

	if(unselected_tex)
		SDL_DestroyTexture(unselected_tex);
	unselected_tex = theme->RenderUnselectedListMenuEntry(text);

	if(selected_tex)
		SDL_DestroyTexture(selected_tex);
	selected_tex = theme->RenderSelectedListMenuEntry(text);
}

void CMenuEntry::RenderThumb(void)
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
	if(!screen_template)
		return;

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
