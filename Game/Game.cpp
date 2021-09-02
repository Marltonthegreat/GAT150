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

	//events
	engine->Get<glds::EventSystem>()->Subscribe("add_points", std::bind(&Game::OnAddPoints, this, std::placeholders::_1));
	engine->Get<glds::EventSystem>()->Subscribe("player_death", std::bind(&Game::OnPlayerDeath, this, std::placeholders::_1));
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

	switch (state)
	{
	case Game::GameState::Reset:
		Reset();
		break;
	case Game::GameState::Title:
		Title();
		break;
	case Game::GameState::StartGame:
		StartGame();
		break;
	case Game::GameState::StartLevel:
		StartLevel();
		break;
	case Game::GameState::Level:
		Level();
		break;
	case Game::GameState::PlayerDead:
		PlayerDead();
		break;
	case Game::GameState::GameOver:
		GameOver();
		break;
	default:
		std::cout << "How did you get here" << std::endl;
		break;
	}
	//update score
	auto scoreActor = scene->FindActor("score");
	if (scoreActor)
	{
		scoreActor->GetComponent<glds::TextComponent>()->SetText(std::to_string(score));
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

void Game::OnAddPoints(const glds::Event& event)
{
	score += std::get<int>(event.data);
}

void Game::OnPlayerDeath(const glds::Event& event)
{
}

void Game::Reset()
{
	scene->RemoveAllActors();

	rapidjson::Document document;
	bool success = glds::json::Load("Title.txt", document);
	assert(success);
	scene->Read(document);
	
	state = GameState::Title;
}

void Game::Title()
{
	if (glds::IsButtonPressed(SDL_SCANCODE_SPACE, engine.get()))
	{
		auto title = scene->FindActor("Title");
		assert(title);
		title->active = false;

		state = GameState::StartGame;
	}
}

void Game::StartGame()
{
	rapidjson::Document document;
	bool success = glds::json::Load("Level.txt", document);
	assert(success);
	scene->Read(document);

	glds::Tilemap tilemap;
	tilemap.scene = scene.get();
	success = glds::json::Load("map.txt", document);
	assert(success);
	tilemap.Read(document);
	tilemap.Create();

	state = GameState::StartLevel;
	stateTimer = 0;
}

void Game::StartLevel()
{
	stateTimer += engine->time.deltaTime;

	if (stateTimer >= 1)
	{
		auto player = glds::ObjectFactory::Instance().Create<glds::Actor>("Player");
		player->transform.position = { 400, 350 };
		scene->AddActor(std::move(player));
		state = GameState::Level;
	}
}

void Game::Level()
{
	spawnTimer -= engine->time.deltaTime;

	if (spawnTimer <= 0)
	{
		spawnTimer = glds::RandomRange(3, 6);


		auto enemy = glds::ObjectFactory::Instance().Create<glds::Actor>("coin");
		enemy->transform.position = { glds::RandomRange(100, 700), 0.0f };
		scene->AddActor(std::move(enemy));

	}
}

void Game::PlayerDead()
{

}

void Game::GameOver()
{
}
