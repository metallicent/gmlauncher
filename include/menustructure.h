
#ifndef _MENUSTRUCTURE_H
#define _MENUSTRUCTURE_H


class CMenuStructure
{
	private:
		CLauncherProgram *program;

		map<string, CScreenTemplate *> screen_templates;
		CScreenTemplate *main_screen_template;

		bool LoadFromFile(const char *file);
		void ParseMenuNode(xmlNodePtr node);

	public:
		CMenuStructure(CLauncherProgram *program, const char *file);
		~CMenuStructure(void);

		CScreenTemplate *GetScreenTemplate(string name);

		CScreen *CreateMainScreen(void);
};


#endif
