
#include "includes.h"

CLauncherProgram::CLauncherProgram(void)
{
	window = SDL_CreateWindow("gmlauncher", 700, 100, 1024, 768, SDL_WINDOW_SHOWN);
	if(!window)
		throw "Failed to create Window";

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if(!renderer)
	{
		SDL_DestroyWindow(window);
		throw "Failed to create Renderer";
	}

	theme = new CTheme(this);

	menu_structure = new CMenuStructure(this, "menu_structure.xml");
	current_screen = menu_structure->CreateMainScreen();

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
		case SDL_SCANCODE_F1:
			Quit();
			break;
		case SDL_SCANCODE_UP:
			if(current_screen)
				current_screen->OnInputDirection(UP);
			break;
		case SDL_SCANCODE_DOWN:
			if(current_screen)
				current_screen->OnInputDirection(DOWN);
			break;
		case SDL_SCANCODE_LEFT:
			if(current_screen)
				current_screen->OnInputDirection(LEFT);
			break;
		case SDL_SCANCODE_RIGHT:
			if(current_screen)
				current_screen->OnInputDirection(RIGHT);
			break;
		case SDL_SCANCODE_SPACE:
			if(current_screen)
				current_screen->OnInputFire();
			break;
		case SDL_SCANCODE_ESCAPE:
			ChangeToPreviousScreen();
			break;
		default:
			break;
	}
}

void CLauncherProgram::Render(void)
{
	SDL_RenderClear(renderer);

	SDL_RenderCopy(renderer, theme->GetBackground(), 0, 0);

	if(current_screen)
		current_screen->Render(renderer);

	SDL_RenderPresent(renderer);
}

void CLauncherProgram::Quit(void)
{
	running = false;
}

void CLauncherProgram::ChangeToScreen(CScreen *screen)
{
	screen->SetPreviousScreen(current_screen);
	current_screen = screen;
}

void CLauncherProgram::ChangeToPreviousScreen(void)
{
	if(!current_screen)
		return;

	if(current_screen->GetPreviousScreen())
	{
		CScreen *s = current_screen;
		current_screen = current_screen->GetPreviousScreen();
		delete s;
	}
}

SDL_Texture *CLauncherProgram::LoadImage(const char *file)
{
	SDL_Surface *surface;
	SDL_Texture *texture;

	surface = IMG_Load(file);
	if(!surface)
		return 0;
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	return texture;
}
