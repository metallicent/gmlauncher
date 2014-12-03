
#ifndef _MENU_H
#define _MENU_H

class CMenu : public CScreen
{
	protected:
		vector<CMenuEntry *> menu_entries;

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

#endif
