
#ifndef _LAUNCHERPROGRAM_H
#define _LAUNCHERPROGRAM_H


class CLauncherProgram
{
	private:
		SDL_Window *window;
		SDL_Renderer *renderer;

		CTheme *theme;
		CMenuStructure *menu_structure;
		CScreen *current_screen;

		bool running;

		void Quit(void);

		void OnKeyDown(SDL_KeyboardEvent event);

	public:
		CLauncherProgram(void);
		~CLauncherProgram(void);

		void ProcessEvent(SDL_Event event);
		void Update(void);
		void Render(void);

		bool GetRunning(void)	{ return running; }
		CTheme *GetTheme(void)	{ return theme; }

		SDL_Texture *LoadImage(const char *file);
};


#endif
