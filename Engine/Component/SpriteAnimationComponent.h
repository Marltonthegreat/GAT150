#pragma once
#include "SpriteComponent.h"
#include <SDL.h>

namespace glds
{
	class SpriteAnimationComponent : public SpriteComponent
	{
	public:
		void Update() override;
		void Draw(Renderer* renderer) override;

	public:
		int frame{};
		int fps{};
		int numFramesX{};
		int numFramesY{};

		float frameTimer{};
		float frameTime{};

		SDL_Rect rect{};
	};
}