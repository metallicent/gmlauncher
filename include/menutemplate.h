

#ifndef _MENUTEMPLATE_H
#define _MENUTEMPLATE_H

class CMenuEntryTemplate;

class CMenuTemplate : public CScreenTemplate
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
		CScreen *CreateScreen(CScreen *previous);
		CScreen *CreateScreen(void)		{ return CreateScreen(0); }
};


class CMenuEntryTemplate
{
	protected:
		CLauncherProgram *program;

		string text;
		SDL_Texture *thumbnail;

		void LoadThumbnail(const char *file);

	public:
		CMenuEntryTemplate(CLauncherProgram *program, string text, const char *thumb_file = 0);
		virtual ~CMenuEntryTemplate(void);

		SDL_Texture *GetThumbnail(void)	{ return thumbnail; }

		virtual CMenuEntry *CreateMenuEntry(void) =0;
};

class CCommandMenuEntryTemplate : public CMenuEntryTemplate
{
	private:
		string command;

	public:
		CCommandMenuEntryTemplate(CLauncherProgram *program, string text, string command, const char *thumb_file = 0);
		~CCommandMenuEntryTemplate(void);

		CMenuEntry *CreateMenuEntry(void);
};

class CScreenMenuEntryTemplate : public CMenuEntryTemplate
{
	private:
		CScreenTemplate *screen_template;

	public:
		CScreenMenuEntryTemplate(CLauncherProgram *program, string text, CScreenTemplate *screen_template, const char *thumb_file = 0);
		~CScreenMenuEntryTemplate(void);

		CMenuEntry *CreateMenuEntry(void);
};

class CQuitMenuEntryTemplate : public CMenuEntryTemplate
{
	public:
		CQuitMenuEntryTemplate(CLauncherProgram *program, string text, const char *thumb_file = 0);
		~CQuitMenuEntryTemplate(void);

		CMenuEntry *CreateMenuEntry(void);
};







#endif
