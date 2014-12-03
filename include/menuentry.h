
#ifndef _MENUENTRY_H
#define _MENUENTRY_H

class CMenuEntry
{
	private:
		CLauncherProgram *program;

		string text;

		SDL_Surface *thumb_surface;

		SDL_Texture *unselected_tex;
		SDL_Texture *selected_tex;

		void RenderList(void);
		void RenderThumb(void);

	public:
		CMenuEntry(CLauncherProgram *program, string text, SDL_Surface *thumb_surface = 0);
		virtual ~CMenuEntry(void);

		string GetText(void)				{ return text; }
		CLauncherProgram *GetProgram(void)	{ return program; }

		void Render(MenuType menu_type);
		SDL_Texture *GetUnselectedTexture(void)	{ return unselected_tex; }
		SDL_Texture *GetSelectedTexture(void)	{ return selected_tex; }

		virtual void Trigger(void) {};
};

class CCommandMenuEntry : public CMenuEntry
{
	private:
		string command;

	public:
		CCommandMenuEntry(CLauncherProgram *program, string text, string command, SDL_Surface *thumb_surface = 0);
		~CCommandMenuEntry(void);

		void Trigger(void);
};

class CScreenMenuEntry : public CMenuEntry
{
	private:
		CScreenTemplate *screen_template;

	public:
		CScreenMenuEntry(CLauncherProgram *program, string text, CScreenTemplate *screen_template, SDL_Surface *thumb_surface = 0);
		~CScreenMenuEntry(void);

		void Trigger(void);
};

class CQuitMenuEntry : public CMenuEntry
{
	public:
		CQuitMenuEntry(CLauncherProgram *program, string text, SDL_Surface *thumb_surface = 0);
		~CQuitMenuEntry(void);

		void Trigger(void);
};


#endif
