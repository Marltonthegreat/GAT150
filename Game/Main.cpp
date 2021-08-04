#include "Engine.h"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

int main(int, char**)
{
	glds::Engine engine;
	engine.Startup();

	engine.Get<glds::Renderer>()->Create("GAT150", 800, 600);

	std::cout << glds::GetFilePath() << std::endl;
	glds::SetFilePath("../Resources");
	std::cout << glds::GetFilePath() << std::endl;

	std::shared_ptr<glds::Texture> texture = engine.Get<glds::ResourceSystem>()->Get<glds::Texture>("sf2.png", engine.Get<glds::Renderer>());

	bool quit = false;
	SDL_Event event;
	while (!quit)
	{


		SDL_PollEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT:
			quit = true;
			break;
		}

		engine.Get<glds::Renderer>()->BeginFrame();

		glds::Vector2 position{ 300,400 };
		engine.Get<glds::Renderer>()->Draw(texture, position);

		engine.Get<glds::Renderer>()->EndFrame();

		//			for (size_t i = 0; i < 2; i++)
		//			{
		//				SDL_Rect src{ 32, 64, 32, 64 };
		//				SDL_Rect dest{ glds::RandomRangeInt( 0, screen.x ), glds::RandomRangeInt(0, screen.y), 64, 96};

		//				SDL_RenderCopy(renderer, texture, &src, &dest);
		//			}

	}


	std::getchar();

	SDL_Quit();

	return 0;
}