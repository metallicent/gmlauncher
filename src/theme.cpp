
#include "includes.h"

CTheme::CTheme(CLauncherProgram *program)
{
	this->program = program;
	Load();
}

CTheme::~CTheme(void)
{
	UnLoad();
}

void CTheme::Load(void)
{
	loaded_completely = true;

	screen_width = 1024;
	screen_height = 768;

	background = LoadImage("themes/test/background.png");
	list_menu_entry_font = LoadFont("themes/test/Ponderosa.ttf", 25);
	thumbs_menu_entry_font = LoadFont("themes/test/Ponderosa.ttf", 16);

	menu_rect = CRect(75, 75, screen_width - 75*2, 682 - 75);
	list_menu_entry_distance = 38;
	unselected_menu_text_color = CreateColor(255, 255, 255);
	selected_menu_text_color = CreateColor(0, 0, 0);
	selected_menu_entry_text_background_color = CreateColor(255, 255, 255);

	thumb_width = 128;
	thumb_height = 100;
	thumbs_menu_entry_width = thumb_width;
	thumbs_menu_entry_height = thumb_height + 25;
	thumbs_menu_entry_distance_x = (menu_rect.width - thumbs_menu_entry_width * GetMaxThumbsMenuEntriesX()) / (GetMaxThumbsMenuEntriesX() - 1);
	thumbs_menu_entry_distance_y = (menu_rect.height - thumbs_menu_entry_height * GetMaxThumbsMenuEntriesY()) / (GetMaxThumbsMenuEntriesY() - 1);
}

SDL_Texture *CTheme::LoadImage(const char *file)
{
	SDL_Texture *texture = program->LoadImage(file);

	if(!texture)
		loaded_completely = false;

	return texture;
}

TTF_Font *CTheme::LoadFont(const char *file, int size)
{
	TTF_Font *font = TTF_OpenFont(file, size);
	if(!font)
		loaded_completely = false;
	return font;
}


void CTheme::UnLoad(void)
{
	UnLoadImage(background);
}

void CTheme::UnLoadImage(SDL_Texture *tex)
{
	if(!tex)
		return;
	SDL_DestroyTexture(tex);
}

void CTheme::UnLoadFont(TTF_Font *font)
{
	if(!font)
		return;
	TTF_CloseFont(font);
}


SDL_Texture *CTheme::RenderUnselectedListMenuEntry(string text)
{
	SDL_Surface *surface = TTF_RenderText_Solid(GetListMenuEntryFont(), text.c_str(), GetUnselectedMenuEntryTextColor());
	SDL_Texture *tex = SDL_CreateTextureFromSurface(program->GetRenderer(), surface);
	SDL_FreeSurface(surface);

	return tex;
}

SDL_Texture *CTheme::RenderSelectedListMenuEntry(string text)
{
	SDL_Surface *surface = RenderTextWithBackground(GetListMenuEntryFont(), text, GetSelectedMenuEntryTextColor(), GetSelectedMenuEntryTextBackgroundColor());

	SDL_Texture *tex = SDL_CreateTextureFromSurface(program->GetRenderer(), surface);
	SDL_FreeSurface(surface);

	return tex;
}

SDL_Surface *CTheme::RenderBasicThumbsMenuEntry(SDL_Surface *thumb)
{
	Uint32 rmask = 0xff000000;
	Uint32 gmask = 0x00ff0000;
	Uint32 bmask = 0x0000ff00;
	Uint32 amask = 0x000000ff;

	SDL_Surface *surface = SDL_CreateRGBSurface(0, thumbs_menu_entry_width, thumbs_menu_entry_height, 32, rmask, gmask, bmask, amask);
	SDL_FillRect(surface, 0, 0x00000000);

	SDL_Rect dst, src;

	dst.x = (thumbs_menu_entry_width - thumb_width) / 2;
	dst.y = 0;
	dst.w = thumb_width;
	dst.h = thumb_height;

	if(thumb)
	{
		float dst_aspect = (float)thumb_height / (float)thumb_width;

		if(dst_aspect > (float)thumb->h / (float)thumb->w) // thumb has greater width
		{
			src.y = 0;
			src.h = thumb->h;

			int w = thumb->h / (dst_aspect);
			src.x = (thumb->w - w) / 2;
			src.w = w;
		}
		else // thumb is taller
		{
			src.x = 0;
			src.w = thumb->w;

			int h = thumb->w * dst_aspect;
			src.y = (thumb->h - h) / 2;
			src.h = h;
		}

		SDL_BlitScaled(thumb, &src, surface, &dst);
	}
	else
		SDL_FillRect(surface, &dst, 0xff0000ff);

	return surface;
}

SDL_Texture *CTheme::RenderUnselectedThumbsMenuEntry(string text, SDL_Surface *thumb)
{
	SDL_Surface *surface = RenderBasicThumbsMenuEntry(thumb);

	SDL_Surface *text_surface = TTF_RenderText_Solid(GetThumbsMenuEntryFont(), text.c_str(), GetUnselectedMenuEntryTextColor());
	SDL_Rect r;
	r.x = surface->w / 2 - text_surface->w / 2;
	r.y = surface->h - text_surface->h;

	SDL_BlitSurface(text_surface, 0, surface, &r);
	SDL_FreeSurface(text_surface);

	SDL_Texture *tex = SDL_CreateTextureFromSurface(program->GetRenderer(), surface);
	SDL_FreeSurface(surface);
	return tex;
}

SDL_Texture *CTheme::RenderSelectedThumbsMenuEntry(string text, SDL_Surface *thumb)
{
	SDL_Surface *surface = RenderBasicThumbsMenuEntry(thumb);

	SDL_Surface *text_surface = RenderTextWithBackground(GetThumbsMenuEntryFont(), text.c_str(), GetSelectedMenuEntryTextColor(), GetSelectedMenuEntryTextBackgroundColor());
	SDL_Rect r;
	r.x = surface->w / 2 - text_surface->w / 2;
	r.y = surface->h - text_surface->h;

	SDL_BlitSurface(text_surface, 0, surface, &r);
	SDL_FreeSurface(text_surface);

	SDL_Texture *tex = SDL_CreateTextureFromSurface(program->GetRenderer(), surface);
	SDL_FreeSurface(surface);
	return tex;
}

SDL_Color CTheme::CreateColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	SDL_Color c;
	c.r = r;
	c.g = g;
	c.b = b;
	c.a = a;
	return c;
}

SDL_Surface *CTheme::RenderTextWithBackground(TTF_Font *font, string text, SDL_Color fg, SDL_Color bg)
{
	Uint32 rmask = 0xff000000;
	Uint32 gmask = 0x00ff0000;
	Uint32 bmask = 0x0000ff00;
	Uint32 amask = 0x000000ff;

	SDL_Surface *text_surface = TTF_RenderText_Solid(font, text.c_str(), fg);

	SDL_Surface *surface = SDL_CreateRGBSurface(0, text_surface->w, text_surface->h, 32, rmask, gmask, bmask, amask);
	SDL_FillRect(surface, 0, SDL_MapRGBA(surface->format, bg.r, bg.g, bg.b, bg.a));
	SDL_BlitSurface(text_surface, 0, surface, 0);
	SDL_FreeSurface(text_surface);

	return surface;
}






