
#include "includes.h"


CMenuTemplate::CMenuTemplate(CLauncherProgram *program, string name, MenuType type)
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
	CMenu *m;

	switch(type)
	{
		case LIST_MENU:
			m = new CListMenu(program, previous);
			break;
		case THUMBS_MENU:
			m = new CThumbsMenu(program, previous);
			break;
		default:
			return 0;
	}

	for(vector<CMenuEntryTemplate *>::iterator i=entries.begin(); i!=entries.end(); i++)
	{
		CMenuEntry *e;
		m->AddEntry(e = (*i)->CreateMenuEntry());
		e->Render(type);
	}

	return m;
}



// ------------------------------------------


CMenuEntryTemplate::CMenuEntryTemplate(CLauncherProgram *program, string text, string thumb_file)
{
	this->program = program;
	this->text = text;

	this->thumb_surface = 0;
	if(thumb_file.size() > 0)
		LoadThumbnail(thumb_file);
}

CMenuEntryTemplate::~CMenuEntryTemplate(void)
{
	if(thumb_surface)
		SDL_FreeSurface(thumb_surface);
}

void CMenuEntryTemplate::LoadThumbnail(string file)
{
	thumb_surface = IMG_Load((string(THUMBNAILS_FOLDER) + string("/") + file).c_str());
}



CCommandMenuEntryTemplate::CCommandMenuEntryTemplate(CLauncherProgram *program, string text, string command, string thumb_file) : CMenuEntryTemplate(program, text, thumb_file)
{
	this->command = command;
}

CCommandMenuEntryTemplate::~CCommandMenuEntryTemplate(void)
{
}

CMenuEntry *CCommandMenuEntryTemplate::CreateMenuEntry(void)
{
	return new CCommandMenuEntry(program, text, command, thumb_surface);
}


CScreenMenuEntryTemplate::CScreenMenuEntryTemplate(CLauncherProgram *program, string text, CMenuStructure *menu_structure, string screen_name, string thumb_file) : CMenuEntryTemplate(program, text, thumb_file)
{
	this->menu_structure = menu_structure;
	this->screen_name = screen_name;
}

CScreenMenuEntryTemplate::~CScreenMenuEntryTemplate(void)
{
}

CMenuEntry *CScreenMenuEntryTemplate::CreateMenuEntry(void)
{
	CScreenTemplate *t = menu_structure->GetScreenTemplate(screen_name);
	return new CScreenMenuEntry(program, text, t, thumb_surface);
}


CQuitMenuEntryTemplate::CQuitMenuEntryTemplate(CLauncherProgram *program, string text, string thumb_file) : CMenuEntryTemplate(program, text, thumb_file)
{
}

CQuitMenuEntryTemplate::~CQuitMenuEntryTemplate(void)
{
}

CMenuEntry *CQuitMenuEntryTemplate::CreateMenuEntry(void)
{
	return new CQuitMenuEntry(program, text, thumb_surface);
}






