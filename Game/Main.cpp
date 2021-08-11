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

	engine.Get<glds::AudioSystem>()->AddAudio("explosion", "audio/explosion.wav");
	engine.Get<glds::AudioSystem>()->AddAudio("playerFire", "audio/playerFire.wav");
	engine.Get<glds::AudioSystem>()->AddAudio("enemyFire", "audio/enemyFire.wav");
	engine.Get<glds::AudioSystem>()->AddAudio("music", "audio/Sunday Morning.mp3");

	glds::AudioChannel channel = engine.Get<glds::AudioSystem>()->PlayAudio("music", 1, 1, true);

	std::shared_ptr<glds::Texture> actorTexture = engine.Get<glds::ResourceSystem>()->Get<glds::Texture>("sf2.png", engine.Get<glds::Renderer>());

	for (int i = 0; i < 10; i++)
	{
		glds::Transform transform{ glds::Vector2{ glds::RandomRange(0, 800), glds::RandomRange(0, 600)}, glds::RandomRange(0, 360) };
		std::unique_ptr<glds::Actor> actor = std::make_unique<glds::Actor>(transform, actorTexture);
		scene.AddActor(std::move(actor));
	}


	bool quit = false;
	SDL_Event event;
	float quitTime = engine.time.time + 3;

	// get font from resource system
	int size = 16;
	std::shared_ptr<glds::Font> font = engine.Get<glds::ResourceSystem>()->Get<glds::Font>("fonts/jokerman.ttf", &size);

	// create font texture
	std::shared_ptr<glds::Texture> textTexture = std::make_shared<glds::Texture>(engine.Get<glds::Renderer>());
	// set font texture with font surface
	textTexture->Create(font->CreateSurface("hello world", glds::Color{ 1, 1, 1 }));
	// add font texture to resource system
	engine.Get<glds::ResourceSystem>()->Add("textTexture", textTexture);


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
		if (engine.Get<glds::InputSystem>()->GetKeyState(SDL_SCANCODE_ESCAPE) == glds::InputSystem::eKeyState::Pressed)
		{
			quit = true;
		}
		if (engine.Get<glds::InputSystem>()->GetButtonState(static_cast<int>(glds::InputSystem::eMouseButton::Left)) == glds::InputSystem::eKeyState::Held)
		{
			channel.SetPitch(channel.GetPitch() + .1f);

			std::shared_ptr<glds::Texture> particleTexture = engine.Get<glds::ResourceSystem>()->Get<glds::Texture>("particle01.png", engine.Get<glds::Renderer>());
			engine.Get<glds::ParticleSystem>()->Create(engine.Get<glds::InputSystem>()->GetMousePos(), 100, particleTexture, .5f, 600);
			engine.Get<glds::AudioSystem>()->PlayAudio("explosion");
		}
		if (engine.Get<glds::InputSystem>()->GetButtonState(static_cast<int>(glds::InputSystem::eMouseButton::Right)) == glds::InputSystem::eKeyState::Pressed)
		{
			channel.SetPitch(1);
		}

		engine.Get<glds::Renderer>()->BeginFrame();

		glds::Transform t;
		t.position = { 30, 30 };
		t.scale = 8;
		engine.Get<glds::Renderer>()->Draw(textTexture, t);

		engine.Draw(engine.Get<glds::Renderer>());
		scene.Draw(engine.Get<glds::Renderer>());
		
		engine.Get<glds::Renderer>()->EndFrame();

	}

	SDL_Quit();

	return 0;
}