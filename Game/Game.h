#pragma once
#include "Engine.h"
#include <SDL.h>
#include <SDL_image.h>

class Game
{
public:
	enum class GameState
	{
		Title,
		StartGame,
		StartLevel,
		Game,
		GameOver,

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

public:
	std::unique_ptr<glds::Engine> engine;
	std::unique_ptr<glds::Scene> scene;

private:
	bool quit{ false };

	GameState state{ GameState::Title };
	float stateTimer{ 0 };

	size_t score{ 0 };
	size_t highScore{ 0 };
	size_t lives{ 0 };

	glds::AudioChannel musicChannel;
	std::shared_ptr<glds::Texture> particleTexture;
	std::shared_ptr<glds::Texture> titleTexture;
	std::shared_ptr<glds::Texture> startTexture;
	std::shared_ptr<glds::Texture> gameOverTexture;
	std::shared_ptr<glds::Texture> scoreTexture;
	std::shared_ptr<glds::Texture> highScoreTexture;
	std::shared_ptr<glds::Texture> livesTexture;
	std::shared_ptr<glds::Font> font;
};