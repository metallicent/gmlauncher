

#ifndef _MENUTEMPLATE_H
#define _MENUTEMPLATE_H

class CMenuEntryTemplate;

class CMenuTemplate : public CScreenTemplate
{
	private:
		CLauncherProgram *program;

		string name;
		MenuType type;

		vector<CMenuEntryTemplate *> entries;

	public:
		CMenuTemplate(CLauncherProgram *program, string name, MenuType type);
		~CMenuTemplate(void);

		void AddEntry(CMenuEntryTemplate *entry);
		CScreen *CreateScreen(CScreen *previous);
		CScreen *CreateScreen(void)		{ return CreateScreen(0); }
};


class CMenuEntryTemplate
{
	protected:
		CLauncherProgram *program;

		string text;
		SDL_Surface *thumb_surface;

		void LoadThumbnail(string file);

	public:
		CMenuEntryTemplate(CLauncherProgram *program, string text, string thumb_file = string());
		virtual ~CMenuEntryTemplate(void);

		SDL_Surface *GetThumbSurface(void)	{ return thumb_surface; }

		virtual CMenuEntry *CreateMenuEntry(void) =0;
};

class CCommandMenuEntryTemplate : public CMenuEntryTemplate
{
	private:
		string command;

	public:
		CCommandMenuEntryTemplate(CLauncherProgram *program, string text, string command, string thumb_file = string());
		~CCommandMenuEntryTemplate(void);

		CMenuEntry *CreateMenuEntry(void);
};

class CScreenMenuEntryTemplate : public CMenuEntryTemplate
{
	private:
		CMenuStructure *menu_structure;
		string screen_name;

	public:
		CScreenMenuEntryTemplate(CLauncherProgram *program, string text, CMenuStructure *menu_structure, string screen_name, string thumb_file = string());
		~CScreenMenuEntryTemplate(void);

		CMenuEntry *CreateMenuEntry(void);
};

class CQuitMenuEntryTemplate : public CMenuEntryTemplate
{
	public:
		CQuitMenuEntryTemplate(CLauncherProgram *program, string text, string thumb_file = string());
		~CQuitMenuEntryTemplate(void);

		CMenuEntry *CreateMenuEntry(void);
};







#endif
