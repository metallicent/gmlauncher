
#ifndef _THEME_H
#define _THEME_H

class CTheme
{
	private:
		CLauncherProgram *program;

		SDL_Texture *background;
		TTF_Font *list_menu_entry_font;
		TTF_Font *thumbs_menu_entry_font;

		int screen_width, screen_height;

		CRect menu_rect;
		int list_menu_entry_distance;
		SDL_Color unselected_menu_text_color;
		SDL_Color selected_menu_text_color;
		SDL_Color selected_menu_entry_text_background_color;

		int thumb_width, thumb_height;
		int thumbs_menu_entry_distance_x, thumbs_menu_entry_distance_y;
		int thumbs_menu_entry_width, thumbs_menu_entry_height;

		bool loaded_completely;

		void Load(void);
		SDL_Texture *LoadImage(const char *file);
		TTF_Font *LoadFont(const char *file, int size);

		void UnLoad(void);
		void UnLoadImage(SDL_Texture *tex);
		void UnLoadFont(TTF_Font *font);

		SDL_Surface *RenderBasicThumbsMenuEntry(SDL_Surface *thumb);

	public:
		CTheme(CLauncherProgram *program);
		virtual ~CTheme(void);

		SDL_Texture *GetBackground(void)	{ return background; }
		TTF_Font *GetListMenuEntryFont(void)	{ return list_menu_entry_font; }
		TTF_Font *GetThumbsMenuEntryFont(void)	{ return thumbs_menu_entry_font; }

		bool GetLoadedCompletely(void)		{ return loaded_completely; }
		int GetScreenWidth(void)			{ return screen_width; }
		int GetScreenHeight(void)			{ return screen_height; }
		CRect GetMenuRect(void)				{ return menu_rect; }
		int GetListMenuEntryDistance(void)	{ return list_menu_entry_distance; }
		int GetMaxListMenuEntries(void)		{ return max(0, menu_rect.height / list_menu_entry_distance - 1); }
		SDL_Color GetUnselectedMenuEntryTextColor(void)		{ return unselected_menu_text_color; }
		SDL_Color GetSelectedMenuEntryTextColor(void)		{ return selected_menu_text_color; }
		SDL_Color GetSelectedMenuEntryTextBackgroundColor(void)	{ return selected_menu_entry_text_background_color; }

		int GetMaxThumbsMenuEntriesX(void)	{ return max(0, menu_rect.width / thumbs_menu_entry_width); }
		int GetMaxThumbsMenuEntriesY(void)	{ return max(0, menu_rect.height / thumbs_menu_entry_height); }
		int GetThumbsMenuEntryDistanceX(void)	{ return thumbs_menu_entry_distance_x; }
		int GetThumbsMenuEntryDistanceY(void)	{ return thumbs_menu_entry_distance_y; }

		SDL_Texture *RenderUnselectedListMenuEntry(string text);
		SDL_Texture *RenderSelectedListMenuEntry(string text);

		SDL_Texture *RenderUnselectedThumbsMenuEntry(string text, SDL_Surface *thumb);
		SDL_Texture *RenderSelectedThumbsMenuEntry(string text, SDL_Surface *thumb);

		static SDL_Color CreateColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255);
		static SDL_Surface *RenderTextWithBackground(TTF_Font *font, string text, SDL_Color fg, SDL_Color bg);
};

#endif
