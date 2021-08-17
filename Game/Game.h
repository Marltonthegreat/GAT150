#pragma once
#include "Engine.h"
#include <SDL.h>
#include <SDL_image.h>

class Game
{
public:
	void Initialize();
	void Shutdown();

	void Update();
	void Draw();

	bool IsQuit() { return quit; }

private:

public:
	std::unique_ptr<glds::Engine> engine;
	std::unique_ptr<glds::Scene> scene;

private:
	bool quit{ false };
};