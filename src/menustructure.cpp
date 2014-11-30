
#include "includes.h"

CMenuStructure::CMenuStructure(CLauncherProgram *program, const char *file)
{
	this->program = program;
	main_menu_template = 0;
	if(!LoadFromFile(file))
		throw "Failed to load menu structure";
}

CMenuStructure::~CMenuStructure(void)
{
	for(map<string, CMenuTemplate *>::iterator i=menu_templates.begin(); i!=menu_templates.end(); i++)
		delete i->second;
}

bool CMenuStructure::LoadFromFile(const char *file)
{
	CMenuTemplate *m = new CMenuTemplate(program, string("main"), CMenuTemplate::LIST_MENU);
	m->AddEntry(new CMenuEntryTemplate(program, string("Mah Boi!"), CMenuEntryTemplate::COMMAND_ACTION));
	m->AddEntry(new CMenuEntryTemplate(program, string("This peace is..."), CMenuEntryTemplate::COMMAND_ACTION));
	m->AddEntry(new CMenuEntryTemplate(program, string("...peace is what all true warriors strive for!"), CMenuEntryTemplate::COMMAND_ACTION));
	m->AddEntry(new CMenuEntryTemplate(program, string("Enough! My shit sails in the morning!"), CMenuEntryTemplate::QUIT_ACTION));
	menu_templates[string("main")] = m;
	main_menu_template = m;

	return true;
}

CScreen *CMenuStructure::CreateMainScreen(void)
{
	if(!main_menu_template)
		return 0;
	return main_menu_template->CreateMenu(0);
}
