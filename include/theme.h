
#ifndef _THEME_H
#define _THEME_H

class CTheme
{
	private:
		SDL_Texture *background;

		int screen_width, screen_height;


		bool loaded_completely;

		void Load(SDL_Renderer *renderer);
		SDL_Texture *LoadImage(SDL_Renderer *renderer, const char *file);

		void UnLoad(void);
		void UnLoadImage(SDL_Texture *tex);

	public:
		CTheme(SDL_Renderer *renderer);
		virtual ~CTheme(void);

		SDL_Texture *GetBackground(void)	{ return background; }

		bool GetLoadedCompletely(void)		{ return loaded_completely; }
		int GetScreenWidth(void)			{ return screen_width; }
		int GetScreenHeight(void)			{ return screen_height; }
};

#endif
