
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

		string GetText(void)	{ return text; }

		virtual void Trigger(void) {};
};


#endif
