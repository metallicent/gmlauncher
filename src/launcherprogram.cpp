
#include "includes.h"

CLauncherProgram::CLauncherProgram(void)
{
	window = SDL_CreateWindow("gmlauncher", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, (FULLSCREEN_ENABLED ? SDL_WINDOW_FULLSCREEN : 0));
	if(!window)
		throw "Failed to create Window";

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if(!renderer)
	{
		SDL_DestroyWindow(window);
		throw "Failed to create Renderer";
	}

	SDL_ShowCursor(SDL_DISABLE);

	theme = new CTheme(this);
	if(!theme->GetLoadedCompletely())
		printf("Warning: Theme could not be loaded completely!\n");

	menu_structure = new CMenuStructure(this, MENU_STRUCTURE_FILE);
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

void CLauncherProgram::SkipEvents(void)
{
	SDL_Event e;
	while(SDL_PollEvent(&e));
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
		case INPUT_KEY_QUIT:
			Quit();
			break;
		case INPUT_KEY_UP:
			if(current_screen)
				current_screen->OnInputDirection(UP);
			break;
		case INPUT_KEY_DOWN:
			if(current_screen)
				current_screen->OnInputDirection(DOWN);
			break;
		case INPUT_KEY_LEFT:
			if(current_screen)
				current_screen->OnInputDirection(LEFT);
			break;
		case INPUT_KEY_RIGHT:
			if(current_screen)
				current_screen->OnInputDirection(RIGHT);
			break;
		case INPUT_KEY_FIRE:
			if(current_screen)
				current_screen->OnInputFire();
			break;
		case INPUT_KEY_BACK:
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
	if(!screen)
		return;

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

SDL_Texture *CLauncherProgram::LoadTexture(const char *file)
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
