#include "Game.h"
#include "Core/Utilities.h"	
#include "GameComponent/PlayerComponent.h"
#include "GameComponent/EnemyComponent.h"
#include "GameComponent/PickUpComponent.h"
#include <fstream>
#include <string>

void Game::Initialize()
{
	//create engine
	engine = std::make_unique<glds::Engine>();
	engine->Startup();
	engine->Get<glds::Renderer>()->Create("GAT150", 800, 600);

	//register classes
	REGISTER_CLASS(PlayerComponent);
	REGISTER_CLASS(EnemyComponent);
	REGISTER_CLASS(PickUpComponent);

	//create scene
	scene = std::make_unique<glds::Scene>();
	scene->engine = engine.get();
	scene->name = "GameName";

	glds::SeedRandom(static_cast<unsigned int>(time(nullptr)));
	glds::SetFilePath("../Resources");

	rapidjson::Document document;
	bool success = glds::json::Load("scene.txt", document);
	assert(success);
	scene->Read(document);

	glds::Tilemap tilemap;
	tilemap.scene = scene.get();
	success = glds::json::Load("map.txt", document);
	assert(success);
	tilemap.Read(document);
	tilemap.Create();

	for (int i = 0; i < 1; i++)
	{
		auto actor = glds::ObjectFactory::Instance().Create<glds::Actor>("coin");
		actor->transform.position = glds::Vector2{ glds::RandomRange(0,800), 500.0f };
		scene->AddActor(std::move(actor));
	}
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