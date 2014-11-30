
#ifndef _MENUSTRUCTURE_H
#define _MENUSTRUCTURE_H


class CMenuStructure
{
	private:
		CLauncherProgram *program;

		map<string, CMenuTemplate *> menu_templates;
		CMenuTemplate *main_menu_template;

		bool LoadFromFile(const char *file);

	public:
		CMenuStructure(CLauncherProgram *program, const char *file);
		~CMenuStructure(void);

		CScreen *CreateMainScreen(void);
};


#endif
