#include "Game.h"
#include "document.h"

int main(int, char**)
{
	Game game;
	game.Initialize();

	rapidjson::Document document;
	bool success = glds::json::Load("json.txt", document);
	assert(success);

	int i1;
	glds::json::Get(document, "integer1", i1);
	std::cout << i1 << std::endl;

	int i2;
	glds::json::Get(document, "integer2", i2);
	std::cout << i2 << std::endl;

	bool quit = false;
	SDL_Event event;

	while (!quit && !game.IsQuit())
	{
		SDL_PollEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT:
			quit = true;
			break;
		}

		game.Update();
		game.Draw();
	}

	SDL_Quit();

	return 0;
}