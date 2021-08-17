#include "Game.h"
#include "Actors/Player.h"
#include "Actors/Enemy.h"
#include "Core/Utilities.h"	
#include <fstream>
#include <string>

void Game::Initialize()
{
	if (!LoadScore())
	{
		SaveScore(0);
	}
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

	// get font from resource system
	int size = 16;
	font = engine->Get<glds::ResourceSystem>()->Get<glds::Font>("fonts/jokerman.ttf", &size);

	titleTexture = std::make_shared<glds::Texture>(engine->Get<glds::Renderer>());
	titleTexture->Create(font->CreateSurface("GameName :P", glds::Color::yellow));
	engine->Get<glds::ResourceSystem>()->Add("titleTexture", titleTexture);

	startTexture = std::make_shared<glds::Texture>(engine->Get<glds::Renderer>());
	startTexture->Create(font->CreateSurface("Press Space to Start", glds::Color::white));
	engine->Get<glds::ResourceSystem>()->Add("startTexture", startTexture);

	gameOverTexture = std::make_shared<glds::Texture>(engine->Get<glds::Renderer>());
	gameOverTexture->Create(font->CreateSurface("Game Over", glds::Color::red));
	engine->Get<glds::ResourceSystem>()->Add("gameOverTexture", gameOverTexture);

	scoreTexture = std::make_shared<glds::Texture>(engine->Get<glds::Renderer>());
	scoreTexture->Create(font->CreateSurface("Score: 00", glds::Color::white));
	engine->Get<glds::ResourceSystem>()->Add("scoreTexture", scoreTexture);

	highScoreTexture = std::make_shared<glds::Texture>(engine->Get<glds::Renderer>());
	highScoreTexture->Create(font->CreateSurface("High Score: " + std::to_string(highScore), glds::Color::white));
	engine->Get<glds::ResourceSystem>()->Add("highScoreTexture", highScoreTexture);

	livesTexture = std::make_shared<glds::Texture>(engine->Get<glds::Renderer>());
	livesTexture->Create(font->CreateSurface("Lives: 00", glds::Color::white));
	engine->Get<glds::ResourceSystem>()->Add("livesTexture", livesTexture);



	//game
	engine->Get<glds::AudioSystem>()->AddAudio("explosion", "audio/explosion.wav");
	engine->Get<glds::AudioSystem>()->AddAudio("playerFire", "audio/playerFire.wav");
	engine->Get<glds::AudioSystem>()->AddAudio("enemyFire", "audio/enemyFire.wav");
	engine->Get<glds::AudioSystem>()->AddAudio("music", "audio/Sunday Morning.mp3");

	musicChannel = engine->Get<glds::AudioSystem>()->PlayAudio("music", 1, 1, true);
	
	engine->Get<glds::EventSystem>()->Subscribe("AddPoints", std::bind(&Game::OnAddPoints, this, std::placeholders::_1));
	engine->Get<glds::EventSystem>()->Subscribe("PlayerDeath", std::bind(&Game::OnPlayerDeath, this, std::placeholders::_1));
}

void Game::Shutdown()
{

}

bool Game::LoadScore()
{
	bool success = false;

	std::ifstream stream("highscore.txt");
	if (stream.is_open())
	{
		success = true;

		std::string line;
		std::getline(stream, line);
		highScore = std::stoi(line);
	}

	return success;
}

bool Game::SaveScore(int score)
{
	bool success = false;
	
	std::ofstream ofstream("highscore.txt");
	if (ofstream.is_open())
	{
		ofstream << score;
		ofstream.close();
	}

	return success;
}

void Game::Update()
{
	engine->Update();
	float dt = engine->time.deltaTime;

	stateTimer += dt;

	switch (state)
	{
	case Game::GameState::Title:
		if (glds::IsButtonPressed(SDL_SCANCODE_SPACE, engine.get()))
		{
			state = GameState::StartGame;
		}
		break;
	case Game::GameState::StartGame:
		score = 0;
		lives = 1;
		state = GameState::StartLevel;
		break;
	case Game::GameState::StartLevel:
		UpdateStartLevel(2);
		state = GameState::Game;
		break;
	case Game::GameState::Game:
		if (scene->GetActors<Enemy>().size() == 0)
		{
			SpawnEnemies(static_cast<int>(score * 1.25));
		}
		break;
	case Game::GameState::GameOver:
		if (score > highScore)
		{
			highScore = score;
			SaveScore(score);
		}

		if (engine->Get<glds::InputSystem>()->GetKeyState(SDL_SCANCODE_RETURN) == glds::InputSystem::eKeyState::Pressed)
		{
			scene.reset();
			scene = std::make_unique<glds::Scene>();
			scene->engine = engine.get();
			scene->name = "GameName";

			state = GameState::StartGame;
		}
		break;
	default:
		break;
	}

	scene->Update(dt);
	if (glds::IsButtonPressed(SDL_SCANCODE_ESCAPE, engine.get()))
	{
		quit = true;
	}
	if (engine->Get<glds::InputSystem>()->GetButtonState(static_cast<int>(glds::InputSystem::eMouseButton::Left)) == glds::InputSystem::eKeyState::Pressed)
	{
		musicChannel.SetPitch(musicChannel.GetPitch() + .1f);

		std::shared_ptr<glds::Texture> particleTexture = engine->Get<glds::ResourceSystem>()->Get<glds::Texture>("particle01.png", engine->Get<glds::Renderer>());
		engine->Get<glds::ParticleSystem>()->Create(engine->Get<glds::InputSystem>()->GetMousePos(), 100, particleTexture, .5f, 600);
		engine->Get<glds::AudioSystem>()->PlayAudio("explosion");
	}
	if (engine->Get<glds::InputSystem>()->GetButtonState(static_cast<int>(glds::InputSystem::eMouseButton::Right)) == glds::InputSystem::eKeyState::Pressed)
	{
		musicChannel.SetPitch(1);
	}
}

void Game::Draw()
{
	glds::Transform screenCenter;
	screenCenter.position = { 400, 300 };
	screenCenter.scale = 2;

	engine->Get<glds::Renderer>()->BeginFrame();

	switch (state)
	{
	case Game::GameState::Title:
	{
		engine->Get<glds::Renderer>()->Draw(startTexture, screenCenter);
	}
		break;
	case Game::GameState::StartGame:
		break;
	case Game::GameState::StartLevel:
		break;
	case Game::GameState::Game:
	{
		// score text
		int size = 16;

		glds::Transform scoreTransform;
		scoreTransform.position = { 50, 20 };

		std::shared_ptr<glds::Texture> texture = engine->Get<glds::ResourceSystem>()->Get<glds::Texture>("scoreTexture");
		std::shared_ptr<glds::Font> font = engine->Get<glds::ResourceSystem>()->Get<glds::Font>("fonts/jokerman.ttf", &size);
		texture->Create(font->CreateSurface("Score: " + std::to_string(score), glds::Color{1, 1, 1}));
		engine->Get<glds::Renderer>()->Draw(texture, scoreTransform);

		scoreTransform.position.y += 20;

		engine->Get<glds::Renderer>()->Draw(highScoreTexture, scoreTransform);

		glds::Transform livesTransform;
		livesTransform.position = { 750, 20 };

		texture = engine->Get<glds::ResourceSystem>()->Get<glds::Texture>("livesTexture");
		font = engine->Get<glds::ResourceSystem>()->Get<glds::Font>("fonts/jokerman.ttf", &size);
		texture->Create(font->CreateSurface("Lives: " + std::to_string(lives), glds::Color{1, 1, 1}));
		engine->Get<glds::Renderer>()->Draw(texture, livesTransform);
	}
		break;
	case Game::GameState::GameOver:
	{
		engine->Get<glds::Renderer>()->Draw(gameOverTexture, screenCenter);

		int size = 16;

		glds::Transform scoreTransform;
		scoreTransform.position = { 50, 20 };

		std::shared_ptr<glds::Texture> texture = engine->Get<glds::ResourceSystem>()->Get<glds::Texture>("highScoreTexture");
		std::shared_ptr<glds::Font> font = engine->Get<glds::ResourceSystem>()->Get<glds::Font>("fonts/jokerman.ttf", &size);
		texture->Create(font->CreateSurface("High Score: " + std::to_string(highScore), glds::Color{ 1, 1, 1 }));
	}
		break;
	default:
		break;
	}


	engine->Draw(engine->Get<glds::Renderer>());
	scene->Draw(engine->Get<glds::Renderer>());

	engine->Get<glds::Renderer>()->EndFrame();
}

void Game::UpdateStartLevel(unsigned int enemyAmount)
{
	scene->AddActor(std::make_unique<Player>(glds::Transform{ glds::Vector2{400.0f, 300.0f}}, engine->Get<glds::ResourceSystem>()->Get<glds::Texture>("playerShip3_blue.png", engine->Get<glds::Renderer>()), 600.0f));
	
	SpawnEnemies(enemyAmount);
}

void Game::SpawnEnemies(unsigned int amount)
{
	for (size_t i = 0; i < amount; i++)
	{
		scene->AddActor(std::make_unique<Enemy>(glds::Transform{ glds::Vector2{0.0f, glds::RandomRange(0, 600)}, glds::RandomRange(0, glds::TwoPi)}, engine->Get<glds::ResourceSystem>()->Get<glds::Texture>("enemyBlack1.png", engine->Get<glds::Renderer>()), 100));
	}
}

void Game::OnAddPoints(const glds::Event& event)
{

	score += std::get<int>(event.data);
	if (score % 5 == 0) lives++;
}

void Game::OnPlayerDeath(const glds::Event& event)
{
	lives--;
	if (lives <= 0)
	{ 
		state = GameState::GameOver;
	}
	else
	{
		scene->RemoveActor(scene->GetActor<Player>());
		std::unique_ptr<Player> player = std::make_unique<Player>(glds::Transform{ glds::Vector2{400.0f, 300.0f} }, engine->Get<glds::ResourceSystem>()->Get<glds::Texture>("playerShip3_blue.png", engine->Get<glds::Renderer>()), 600.0f);
		player->transform.rotation = glds::DegToRad(glds::RandomRange(0, 360));
		scene->AddActor(std::move(player));
	}
}

