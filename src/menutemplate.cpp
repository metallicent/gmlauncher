
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

CScreen *CMenuTemplate::CreateMenu(CScreen *previous)
{
	CMenu *m = new CMenu(program, previous);

	for(vector<CMenuEntryTemplate *>::iterator i=entries.begin(); i!=entries.end(); i++)
		m->AddEntry((*i)->CreateMenuEntry());

	return m;
}



// ------------------------------------------


CMenuEntryTemplate::CMenuEntryTemplate(CLauncherProgram *program, string text, Action action, string command, const char *thumb_file)
{
	this->program = program;
	this->text = text;
	this->action = action;

	if(action == COMMAND_ACTION)
		this->command = command;

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

CMenuEntry *CMenuEntryTemplate::CreateMenuEntry(void)
{
	return new CMenuEntry(program, text);
}
