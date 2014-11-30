

#ifndef _MENUTEMPLATE_H
#define _MENUTEMPLATE_H

class CMenuEntryTemplate;

class CMenuTemplate
{
	public:
		enum Type { LIST_MENU, THUMBS_MENU };

	private:
		CLauncherProgram *program;

		string name;
		Type type;

		vector<CMenuEntryTemplate *> entries;

	public:
		CMenuTemplate(CLauncherProgram *program, string name, Type type);
		~CMenuTemplate(void);

		void AddEntry(CMenuEntryTemplate *entry);
		CScreen *CreateMenu(CScreen *previous);
};


class CMenuEntryTemplate
{
	public:
		enum Action { COMMAND_ACTION, QUIT_ACTION };

	private:
		CLauncherProgram *program;

		string text;
		Action action;

		string command;

		SDL_Texture *thumbnail;

		void LoadThumbnail(const char *file);

	public:
		CMenuEntryTemplate(CLauncherProgram *program, string text, Action action, string command = string(), const char *thumb_file = 0);
		~CMenuEntryTemplate(void);

		SDL_Texture *GetThumbnail(void)	{ return thumbnail; }

		CMenuEntry *CreateMenuEntry(void);
};


#endif
