
#include "includes.h"

int main(int argc, const char *argv[])
{
	if(SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		printf("Failed to init SDL: %s\n", SDL_GetError());
		return 1;
	}

	int img_flags = IMG_INIT_PNG | IMG_INIT_JPG;
	if(IMG_Init(img_flags)&img_flags != img_flags)
	{
		printf("Failed to init SDL image\n");
		SDL_Quit();
		return 1;
	}

	CLauncherProgram *program;
	try
	{
		program = new CLauncherProgram();
	}
	catch(const char *msg)
	{
		printf("%s\n", msg);
		exit(1);
	}

	SDL_Event event;
	while(program->GetRunning())
	{
		while(SDL_PollEvent(&event))
			program->ProcessEvent(event);

		program->Update();
		program->Render();

		SDL_Delay(100);
	}

	delete program;
	SDL_Quit();
}
