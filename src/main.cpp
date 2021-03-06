
#include "includes.h"

#define MIN_FRAME_TIME 16

int main(int argc, const char *argv[])
{
	if(SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		printf("Failed to init SDL: %s\n", SDL_GetError());
		return 1;
	}

	int img_flags = IMG_INIT_PNG | IMG_INIT_JPG;
	if((IMG_Init(img_flags)&img_flags) != img_flags)
	{
		printf("Failed to init SDL image\n");
		SDL_Quit();
		return 1;
	}

	if(TTF_Init() == -1)
	{
		printf("Failed to init SDL ttf\n");
		SDL_Quit();
		IMG_Quit();
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
	Uint32 start_time, end_time, delta_time;
	while(program->GetRunning())
	{
		start_time = SDL_GetTicks();

		while(SDL_PollEvent(&event))
			program->ProcessEvent(event);

		program->Update();
		program->Render();

		end_time = SDL_GetTicks();
		delta_time = end_time - start_time;

		if(delta_time < MIN_FRAME_TIME)
			SDL_Delay(MIN_FRAME_TIME - delta_time);
	}

	delete program;
	SDL_Quit();
	IMG_Quit();
	TTF_Quit();
}
