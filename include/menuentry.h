
#ifndef _MENUENTRY_H
#define _MENUENTRY_H

class CMenuEntry
{
	private:
		CLauncherProgram *program;

		string text;

	public:
		CMenuEntry(CLauncherProgram *program, string text);
		virtual ~CMenuEntry(void);

		string GetText(void)				{ return text; }
		CLauncherProgram *GetProgram(void)	{ return program; }

		virtual void Trigger(void) {};
};

class CCommandMenuEntry : public CMenuEntry
{
	private:
		string command;

	public:
		CCommandMenuEntry(CLauncherProgram *program, string text, string command);
		~CCommandMenuEntry(void);

		void Trigger(void);
};

class CScreenMenuEntry : public CMenuEntry
{
	private:
		CScreenTemplate *screen_template;

	public:
		CScreenMenuEntry(CLauncherProgram *program, string text, CScreenTemplate *screen_template);
		~CScreenMenuEntry(void);

		void Trigger(void);
};

class CQuitMenuEntry : public CMenuEntry
{
	public:
		CQuitMenuEntry(CLauncherProgram *program, string text);
		~CQuitMenuEntry(void);

		void Trigger(void);
};


#endif
