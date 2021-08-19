#include "Game.h"
#include "Core/Utilities.h"	
#include <fstream>
#include <string>

void Game::Initialize()
{
	//create engine
	engine = std::make_unique<glds::Engine>();
	engine->Startup();
	engine->Get<glds::Renderer>()->Create("GAT150", 800, 600);

	//create scene
	scene = std::make_unique<glds::Scene>();
	scene->engine = engine.get();
	scene->name = "GameName";

	glds::SeedRandom(static_cast<unsigned int>(time(nullptr)));
	glds::SetFilePath("../Resources");

	std::unique_ptr<glds::Actor> actor = std::make_unique<glds::Actor>(glds::Transform{ {400,300}, 0, 9 });

	auto component = glds::ObjectFactory::Instance().Create<glds::SpriteAnimationComponent>("SpriteAnimationComponent");

	//glds::SpriteAnimationComponent* spriteAnimationComponent = actor->AddComponent<glds::SpriteAnimationComponent>();

	component->texture = engine->Get<glds::ResourceSystem>()->Get<glds::Texture>("character.png", engine->Get<glds::Renderer>());
	component->fps = 30;
	component->numFramesX = 12;
	component->numFramesY = 8;

	actor->AddComponent(std::move(component));

	glds::PhysicsComponent* physicsComponent = actor->AddComponent<glds::PhysicsComponent>();
	//physicsComponent->ApplyForce(glds::Vector2::right * 200);

	scene->AddActor(std::move(actor));
}

void Game::Shutdown()
{

}

void Game::Update()
{
	engine->Update();
	if (glds::IsButtonPressed(SDL_SCANCODE_ESCAPE, engine.get()))
	{
		quit = true;
	}

	scene->Update(engine->time.deltaTime);
}

void Game::Draw()
{
	glds::Transform screenCenter;
	screenCenter.position = { 400, 300 };
	screenCenter.scale = 2;

	engine->Get<glds::Renderer>()->BeginFrame();

	engine->Draw(engine->Get<glds::Renderer>());
	scene->Draw(engine->Get<glds::Renderer>());

	engine->Get<glds::Renderer>()->EndFrame();
}