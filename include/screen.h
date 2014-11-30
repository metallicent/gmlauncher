
#ifndef _SCREEN_H
#define _SCREEN_H


class CScreen
{
	private:
		CLauncherProgram *program;
		CScreen *previous_screen;

	public:
		CScreen(CLauncherProgram *program, CScreen *previous);
		virtual ~CScreen(void) {};

		CLauncherProgram *GetProgram(void)	{ return program; }
		CScreen *GetPreviousScreen(void)	{ return previous_screen; }

		virtual void Render(SDL_Renderer *renderer) =0;
		virtual void OnInputDirection(InputDirection dir) {}
		virtual void OnInputFire(void) {}
};



#endif
