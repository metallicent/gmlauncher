
#ifndef _THEME_H
#define _THEME_H

class CTheme
{
	private:
		CLauncherProgram *program;

		SDL_Texture *background;
		TTF_Font *list_menu_entry_font;
		TTF_Font *thumbs_menu_entry_font;

		SDL_Texture *arrow_down;
		SDL_Texture *arrow_up;
		int arrow_down_x, arrow_down_y, arrow_up_x, arrow_up_y;

		SDL_Surface *thumbnail_border;
		SDL_Surface *thumbnail_border_selected;

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
		SDL_Surface *LoadSurface(string file);
		SDL_Texture *LoadTexture(string file);
		TTF_Font *LoadFont(string file, int size);
		SDL_Surface *LoadBorder(int width, int height, string left, string right, string top, string bottom, string left_top, string right_top, string left_bottom, string right_bottom);

		void UnLoad(void);
		void UnLoadTexture(SDL_Texture *tex);
		void UnLoadFont(TTF_Font *font);
		void UnLoadSurface(SDL_Surface *surface);

		SDL_Surface *RenderBasicThumbsMenuEntry(SDL_Surface *thumb, bool selected);

	public:
		CTheme(CLauncherProgram *program);
		virtual ~CTheme(void);

		SDL_Texture *GetBackground(void)		{ return background; }
		TTF_Font *GetListMenuEntryFont(void)	{ return list_menu_entry_font; }
		TTF_Font *GetThumbsMenuEntryFont(void)	{ return thumbs_menu_entry_font; }

		SDL_Texture *GetArrowDown(void)			{ return arrow_down; }
		SDL_Texture *GetArrowUp(void)			{ return arrow_up; }

		SDL_Surface *GetThumbnailBorder(void)			{ return thumbnail_border; }
		SDL_Surface *GetThumbnailBorderSelected(void)	{ return thumbnail_border_selected; }

		bool GetLoadedCompletely(void)		{ return loaded_completely; }
		int GetScreenWidth(void)			{ return screen_width; }
		int GetScreenHeight(void)			{ return screen_height; }
		CRect GetMenuRect(void)				{ return menu_rect; }
		int GetListMenuEntryDistance(void)	{ return list_menu_entry_distance; }
		int GetMaxListMenuEntries(void)		{ return max(0, menu_rect.height / list_menu_entry_distance); }
		SDL_Color GetUnselectedMenuEntryTextColor(void)		{ return unselected_menu_text_color; }
		SDL_Color GetSelectedMenuEntryTextColor(void)		{ return selected_menu_text_color; }
		SDL_Color GetSelectedMenuEntryTextBackgroundColor(void)	{ return selected_menu_entry_text_background_color; }

		int GetMaxThumbsMenuEntriesX(void)	{ return max(0, menu_rect.width / thumbs_menu_entry_width); }
		int GetMaxThumbsMenuEntriesY(void)	{ return max(0, menu_rect.height / thumbs_menu_entry_height); }
		int GetThumbsMenuEntryDistanceX(void)	{ return thumbs_menu_entry_distance_x; }
		int GetThumbsMenuEntryDistanceY(void)	{ return thumbs_menu_entry_distance_y; }

		CRect GetArrowDownPosition(void)		{ return CRect(arrow_down_x, arrow_down_y, 0, 0); }
		CRect GetArrowUpPosition(void)			{ return CRect(arrow_up_x, arrow_up_y, 0, 0); }

		SDL_Texture *RenderUnselectedListMenuEntry(string text);
		SDL_Texture *RenderSelectedListMenuEntry(string text);

		SDL_Texture *RenderUnselectedThumbsMenuEntry(string text, SDL_Surface *thumb);
		SDL_Texture *RenderSelectedThumbsMenuEntry(string text, SDL_Surface *thumb);

		static SDL_Color CreateColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255);
		static SDL_Surface *RenderTextWithBackground(TTF_Font *font, string text, SDL_Color fg, SDL_Color bg);
};

#endif
