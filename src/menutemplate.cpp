
#include "includes.h"


CMenuTemplate::CMenuTemplate(CLauncherProgram *program, string name, Type type)
{
	this->program = program;
	this->name = name;
	this->type = type;
}

CMenuTemplate::~CMenuTemplate(void)
{
	for(vector<CMenuEntryTemplate *>::iterator i=entries.begin(); i!=entries.end(); i++)
	{
		if(*i)
			delete *i;
	}
}


void CMenuTemplate::AddEntry(CMenuEntryTemplate *entry)
{
	entries.push_back(entry);
}

CScreen *CMenuTemplate::CreateScreen(CScreen *previous)
{
	CMenu *m = new CMenu(program, previous);

	for(vector<CMenuEntryTemplate *>::iterator i=entries.begin(); i!=entries.end(); i++)
		m->AddEntry((*i)->CreateMenuEntry());

	return m;
}



// ------------------------------------------


CMenuEntryTemplate::CMenuEntryTemplate(CLauncherProgram *program, string text, const char *thumb_file)
{
	this->program = program;
	this->text = text;

	thumbnail = 0;
	if(thumb_file)
		LoadThumbnail(thumb_file);
}

CMenuEntryTemplate::~CMenuEntryTemplate(void)
{
	if(thumbnail)
		SDL_DestroyTexture(thumbnail);
}

void CMenuEntryTemplate::LoadThumbnail(const char *file)
{
	thumbnail = program->LoadImage(file);
}



CCommandMenuEntryTemplate::CCommandMenuEntryTemplate(CLauncherProgram *program, string text, string command, const char *thumb_file) : CMenuEntryTemplate(program, text, thumb_file)
{
	this->command = command;
}

CCommandMenuEntryTemplate::~CCommandMenuEntryTemplate(void)
{
}

CMenuEntry *CCommandMenuEntryTemplate::CreateMenuEntry(void)
{
	return new CCommandMenuEntry(program, text, command);
}


CScreenMenuEntryTemplate::CScreenMenuEntryTemplate(CLauncherProgram *program, string text, CScreenTemplate *screen_template, const char *thumb_file) : CMenuEntryTemplate(program, text, thumb_file)
{
	this->screen_template = screen_template;
}

CScreenMenuEntryTemplate::~CScreenMenuEntryTemplate(void)
{
}

CMenuEntry *CScreenMenuEntryTemplate::CreateMenuEntry(void)
{
	return new CScreenMenuEntry(program, text, screen_template);
}


CQuitMenuEntryTemplate::CQuitMenuEntryTemplate(CLauncherProgram *program, string text, const char *thumb_file) : CMenuEntryTemplate(program, text, thumb_file)
{
}

CQuitMenuEntryTemplate::~CQuitMenuEntryTemplate(void)
{
}

CMenuEntry *CQuitMenuEntryTemplate::CreateMenuEntry(void)
{
	return new CQuitMenuEntry(program, text);
}






