
#ifndef _MENU_H
#define _MENU_H

class CMenu : public CScreen
{
	protected:
		vector<CMenuEntry *> menu_entries;

		void RenderDownArrow(SDL_Renderer *renderer);
		void RenderUpArrow(SDL_Renderer *renderer);

	public:
		CMenu(CLauncherProgram *program, CScreen *previous);
		virtual ~CMenu(void);

		void Render(SDL_Renderer *renderer) =0;

		void AddEntry(CMenuEntry *entry);
};

class CListMenu : public CMenu
{
	private:
		int selected_entry;
		int scroll;

	public:
		CListMenu(CLauncherProgram *program, CScreen *previous);
		~CListMenu(void);

		void Render(SDL_Renderer *renderer);

		void OnInputDirection(InputDirection dir);
		void OnInputFire(void);

};

class CThumbsMenu : public CMenu
{
	private:
		int selected_entry;
		int scroll;

	public:
		CThumbsMenu(CLauncherProgram *program, CScreen *previous);
		~CThumbsMenu(void);

		void Render(SDL_Renderer *renderer);

		void OnInputDirection(InputDirection dir);
		void OnInputFire(void);
};

#endif
