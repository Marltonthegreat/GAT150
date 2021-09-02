#pragma once
#include "Engine.h"
#include <SDL.h>
#include <SDL_image.h>

class Game
{
public:
	enum class GameState
	{
		Reset,
		Title,
		StartGame,
		StartLevel,
		Level,
		PlayerDead,
		GameOver
	};

public:
	void Initialize();
	void Shutdown();

	bool LoadScore();
	bool SaveScore(int score);

	void Update();
	void Draw();

	bool IsQuit() { return quit; }

private:
	void UpdateTitle(float dt);
	void UpdateStartLevel(unsigned int enemyAmount);

	void SpawnEnemies(unsigned int amount);

	void OnAddPoints(const glds::Event& event);
	void OnPlayerDeath(const glds::Event& event);

	void Reset();
	void Title();
	void StartGame();
	void StartLevel();
	void Level();
	void PlayerDead();
	void GameOver();

public:
	std::unique_ptr<glds::Engine> engine;
	std::unique_ptr<glds::Scene> scene;

private:

	bool quit{ false };

	GameState state{ GameState::Reset };
	float stateTimer{ 0 };
	float spawnTimer{ 0 };

	size_t score{ 0 };
	size_t highScore{ 0 };
	size_t lives{ 0 };
};