
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
	menu_entry_font = LoadFont("themes/test/Ponderosa.ttf", 25);

	menu_rect = CRect(75, 75, screen_width - 75*2, 692 - 50);
	list_menu_entry_distance = 38;
	unselected_menu_text_color = CreateColor(255, 255, 255);
	selected_menu_text_color = CreateColor(0, 0, 0);
	selected_menu_text_background_color = CreateColor(255, 255, 255);

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
	SDL_Surface *surface = TTF_RenderText_Solid(GetMenuEntryFont(), text.c_str(), GetUnselectedMenuEntryTextColor());
	SDL_Texture *tex = SDL_CreateTextureFromSurface(program->GetRenderer(), surface);
	SDL_FreeSurface(surface);

	return tex;
}

SDL_Texture *CTheme::RenderSelectedListMenuEntry(string text)
{
	Uint32 rmask = 0xff000000;
	Uint32 gmask = 0x00ff0000;
	Uint32 bmask = 0x0000ff00;
	Uint32 amask = 0x000000ff;

	SDL_Surface *text_surface = TTF_RenderText_Solid(GetMenuEntryFont(), text.c_str(), GetSelectedMenuEntryTextColor());

	SDL_Surface *surface = SDL_CreateRGBSurface(0, text_surface->w, text_surface->h, 32, rmask, gmask, bmask, amask);
	SDL_FillRect(surface, 0, SDL_MapRGBA(surface->format, 	GetSelectedMenuTextBackgroundColor().r,
			 	 	 	 	 	 	 	 	 	 	 	 	 	GetSelectedMenuTextBackgroundColor().g,
			 	 	 	 	 	 	 	 	 	 	 	 	 	GetSelectedMenuTextBackgroundColor().b,
			 	 	 	 	 	 	 	 	 	 	 	 	 	GetSelectedMenuTextBackgroundColor().a));
	SDL_BlitSurface(text_surface, 0, surface, 0);
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







