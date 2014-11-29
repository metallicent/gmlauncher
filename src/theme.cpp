
#include "includes.h"

CTheme::CTheme(SDL_Renderer *renderer)
{
	Load(renderer);
}

CTheme::~CTheme(void)
{
	UnLoad();
}

void CTheme::Load(SDL_Renderer *renderer)
{
	loaded_completely = true;

	screen_width = 1024;
	screen_height = 768;

	background = LoadImage(renderer, "themes/test/background.png");
}

SDL_Texture *CTheme::LoadImage(SDL_Renderer *renderer, const char *file)
{
	SDL_Surface *surface;
	SDL_Texture *texture;

	surface = IMG_Load(file);
	if(!surface)
	{
		loaded_completely = false;
		return 0;
	}
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	if(!texture)
		loaded_completely = false;
	SDL_FreeSurface(surface);

	return texture;
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
