
#ifndef _THEME_H
#define _THEME_H

class CTheme
{
	private:
		SDL_Texture *background;
		TTF_Font *menu_entry_font;

		int screen_width, screen_height;

		CRect menu_rect;
		int list_menu_entry_distance;


		bool loaded_completely;

		void Load(SDL_Renderer *renderer);
		SDL_Texture *LoadImage(SDL_Renderer *renderer, const char *file);
		TTF_Font *LoadFont(const char *file, int size);

		void UnLoad(void);
		void UnLoadImage(SDL_Texture *tex);
		void UnLoadFont(TTF_Font *font);

	public:
		CTheme(SDL_Renderer *renderer);
		virtual ~CTheme(void);

		SDL_Texture *GetBackground(void)	{ return background; }
		TTF_Font *GetMenuEntryFont(void)	{ return menu_entry_font; }

		bool GetLoadedCompletely(void)		{ return loaded_completely; }
		int GetScreenWidth(void)			{ return screen_width; }
		int GetScreenHeight(void)			{ return screen_height; }
		CRect GetMenuRect(void)				{ return menu_rect; }
		int GetListMenuEntryDistance(void)	{ return list_menu_entry_distance; }
		int GetMaxListMenuEntries(void)		{ return max(0, menu_rect.height / list_menu_entry_distance - 1); }
};

#endif
