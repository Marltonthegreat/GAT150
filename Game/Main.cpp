#include "Engine.h"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

int main(int, char**)
{

	glds::Engine engine;
	engine.Startup();

	engine.Get<glds::Renderer>()->Create("GAT150", 800, 600);

	glds::Scene scene;
	scene.engine = &engine;

	glds::SetFilePath("../Resources");

	std::shared_ptr<glds::Texture> texture = engine.Get<glds::ResourceSystem>()->Get<glds::Texture>("sf2.png", engine.Get<glds::Renderer>());

	for (int i = 0; i < 100; i++)
	{
		glds::Transform transform{ glds::Vector2{ glds::RandomRange(0, 800), glds::RandomRange(0, 600)}, glds::RandomRange(0, 360) };
		std::unique_ptr<glds::Actor> actor = std::make_unique<glds::Actor>(transform, texture);
		scene.AddActor(std::move(actor));
	}


	bool quit = false;
	SDL_Event event;
	float quitTime = engine.time.time + 3;

	while (!quit)
	{


		SDL_PollEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT:
			quit = true;
			break;
		}

		engine.Update();
		scene.Update(engine.time.deltaTime);

		//std::cout << engine.time.time << std::endl;
		if (engine.time.time >= quitTime) quit = true;
		engine.time.timeScale = .25;

		engine.Get<glds::Renderer>()->BeginFrame();

		glds::Vector2 position{ 300,400 };
		//engine.Get<glds::Renderer>()->Draw(texture, position);
		scene.Draw(engine.Get<glds::Renderer>());

		engine.Get<glds::Renderer>()->EndFrame();

	}


	std::getchar();

	SDL_Quit();

	return 0;
}