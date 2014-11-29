
#include "includes.h"

CLauncherProgram::CLauncherProgram(void)
{
	window = SDL_CreateWindow("gmlauncher", 100, 100, 1024, 768, SDL_WINDOW_SHOWN);
	if(!window)
		throw "Failed to create Window";

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if(!renderer)
	{
		SDL_DestroyWindow(window);
		throw "Failed to create Renderer";
	}

	theme = new CTheme(renderer);

	running = true;
}

CLauncherProgram::~CLauncherProgram(void)
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
}


void CLauncherProgram::Update(void)
{
}

void CLauncherProgram::ProcessEvent(SDL_Event event)
{
	switch(event.type)
	{
		case SDL_KEYDOWN:
			OnKeyDown(event.key);
			break;
	}
}

void CLauncherProgram::OnKeyDown(SDL_KeyboardEvent event)
{
	switch(event.keysym.scancode)
	{
		case SDL_SCANCODE_ESCAPE:
			Quit();
			break;
		default:
			break;
	}
}

void CLauncherProgram::Render(void)
{
	SDL_RenderClear(renderer);

	SDL_RenderCopy(renderer, theme->GetBackground(), 0, 0);

	SDL_RenderPresent(renderer);
}

void CLauncherProgram::Quit(void)
{
	running = false;
}
