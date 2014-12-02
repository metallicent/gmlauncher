
#include "includes.h"

CMenuStructure::CMenuStructure(CLauncherProgram *program, const char *file)
{
	this->program = program;
	main_screen_template = 0;
	if(!LoadFromFile(file))
		throw "Failed to load menu structure";
}

CMenuStructure::~CMenuStructure(void)
{
	for(map<string, CScreenTemplate *>::iterator i=screen_templates.begin(); i!=screen_templates.end(); i++)
		delete i->second;
}

bool CMenuStructure::LoadFromFile(const char *file)
{
	xmlDocPtr doc;
	xmlNodePtr root;
	xmlNodePtr cur;

	string main_screen_name;


	doc = xmlParseFile(file);

	if(!doc)
		return false;

	root = xmlDocGetRootElement(doc);

	if(!root)
	{
		xmlFreeDoc(doc);
		return false;
	}

	if(!xmlStrEqual(root->name, (const xmlChar *)"gmlauncher-menu-structure"))
	{
		xmlFreeDoc(doc);
		return false;
	}

	main_screen_name = string((const char *)xmlGetProp(root, (const xmlChar *)"main-menu"));


	cur = root->children;
	while(cur)
	{
		if(xmlStrEqual(cur->name, (const xmlChar *)"menu"))
			ParseMenuNode(cur);

		cur = cur->next;
	}

	xmlFreeDoc(doc);


	map<string, CScreenTemplate *>::iterator msi = screen_templates.find(main_screen_name);
	if(msi == screen_templates.end())
	{
		if(screen_templates.size() == 0)
			main_screen_template = 0;
		else
			main_screen_template = screen_templates.begin()->second;
	}
	else
		main_screen_template = msi->second;

	return true;
}

void CMenuStructure::ParseMenuNode(xmlNodePtr node)
{
	xmlNodePtr child;
	xmlChar *prop;
	string name;
	CMenuTemplate::Type type = CMenuTemplate::LIST_MENU;

	string entry_text;
	string entry_param;
	enum EntryAction { COMMAND_ACTION, MENU_ACTION, QUIT_ACTION } entry_action;
	string entry_thumb_file;

	CMenuTemplate *menu_template;
	CMenuEntryTemplate *entry_template;

	if(!(prop = xmlGetProp(node, (const xmlChar *)"name")))
		return;
	name = string((const char *)prop);
	if(name.size() == 0)
		return;

	if((prop = xmlGetProp(node, (const xmlChar *)"type")))
	{
		if(xmlStrEqual(prop, (const xmlChar *)"list"))
			type = CMenuTemplate::LIST_MENU;
		else if(xmlStrEqual(prop, (const xmlChar *)"thumbs"))
			type = CMenuTemplate::THUMBS_MENU;
	}

	menu_template = new CMenuTemplate(program, name, type);

	for(child=node->children; child; child=child->next)
	{
		if(xmlStrEqual(child->name, (const xmlChar *)"entry"))
		{
			// text
			if(!(prop = xmlGetProp(child, (const xmlChar *)"text")))
				continue;
			entry_text = string((const char *)prop);

			// action
			if(!(prop = xmlGetProp(child, (const xmlChar *)"action")))
				continue;

			if(xmlStrEqual(prop, (const xmlChar *)"command"))
				entry_action = COMMAND_ACTION;
			else if(xmlStrEqual(prop, (const xmlChar *)"menu"))
				entry_action = MENU_ACTION;
			else if(xmlStrEqual(prop, (const xmlChar *)"quit"))
				entry_action = QUIT_ACTION;
			else
				continue;

			// thumbnail
			if((prop = xmlGetProp(child, (const xmlChar *)"thumbnail")))
				entry_thumb_file = string((const char *)prop);
			else
				entry_thumb_file = string();

			// param
			if(entry_action == COMMAND_ACTION || entry_action == MENU_ACTION)
			{
				if((prop = xmlGetProp(child, (const xmlChar *)"param")))
					entry_param = string((const char *)prop);
				else
					entry_param = string();
			}


			// create entry template
			switch(entry_action)
			{
				case COMMAND_ACTION:
					entry_template = new CCommandMenuEntryTemplate(program, entry_text, entry_param, entry_thumb_file);
					break;
				case MENU_ACTION:
					entry_template = new CScreenMenuEntryTemplate(program, entry_text, this, entry_param, entry_thumb_file);
					break;
				case QUIT_ACTION:
					entry_template = new CQuitMenuEntryTemplate(program, entry_text, entry_thumb_file);
					break;
				default:
					entry_template = 0;
					break;
			}

			if(entry_template)
				menu_template->AddEntry(entry_template);
		}

	}

	screen_templates[name] = menu_template;
}

CScreenTemplate *CMenuStructure::GetScreenTemplate(string name)
{
	map<string, CScreenTemplate *>::iterator i = screen_templates.find(name);
	if(i == screen_templates.end())
		return 0;
	return i->second;
}

CScreen *CMenuStructure::CreateMainScreen(void)
{
	if(!main_screen_template)
		return 0;
	return main_screen_template->CreateScreen();
}
