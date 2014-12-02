
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
	CMenuTemplate *sub = new CMenuTemplate(program, string("sub"), CMenuTemplate::LIST_MENU);
	sub->AddEntry(new CCommandMenuEntryTemplate(program, string("submenu"), string("glxgears")));
	sub->AddEntry(new CCommandMenuEntryTemplate(program, string("submensdafsdfasfu"), string("glxgears")));
	sub->AddEntry(new CCommandMenuEntryTemplate(program, string("submensdafsdfasfu"), string("glxgears")));

	CMenuTemplate *m = new CMenuTemplate(program, string("main"), CMenuTemplate::LIST_MENU);
	m->AddEntry(new CCommandMenuEntryTemplate(program, string("Mah Boi!"), string("glxgears")));
	m->AddEntry(new CCommandMenuEntryTemplate(program, string("This peace is..."), string()));
	m->AddEntry(new CCommandMenuEntryTemplate(program, string("...peace is what all true warriors strive for!"), string()));
	m->AddEntry(new CScreenMenuEntryTemplate(program, string("Submenu"), sub));
	m->AddEntry(new CQuitMenuEntryTemplate(program, string("Enough! My shit sails in the morning!")));
	menu_templates[string("main")] = m;
	main_menu_template = m;

	return true;
}

CScreen *CMenuStructure::CreateMainScreen(void)
{
	if(!main_menu_template)
		return 0;
	return main_menu_template->CreateScreen(0);
}
