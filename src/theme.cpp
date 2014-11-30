
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

	menu_rect = CRect(50, 50, screen_width - 50*2, 692 - 50);
	list_menu_entry_distance = 35;
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
