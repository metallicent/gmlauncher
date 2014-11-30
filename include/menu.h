
#ifndef _MENU_H
#define _MENU_H

class CMenu : public CScreen
{
	private:
		vector<CMenuEntry *> menu_entries;

		int selected_entry;
		int scroll;

	public:
		CMenu(CLauncherProgram *program, CScreen *previous);
		~CMenu(void);

		void Render(SDL_Renderer *renderer);

		void OnInputDirection(InputDirection dir);
		void OnInputFire(void);

		void AddEntry(CMenuEntry *entry);
};

#endif
