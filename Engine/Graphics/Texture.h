#pragma once
#include "Resource/ResourceSystem.h"
#include <SDL.h>
#include <iostream>

// seperate Resource from ResourceSystem then include it in ResourceSystem

namespace glds
{
	class Texture : public Resource
	{
	public:
		bool Load(const std::string& name, void* data) override;

		friend class Renderer;

	private:
		SDL_Texture* texture{ nullptr };
		SDL_Renderer* renderer{ nullptr };
	};
}