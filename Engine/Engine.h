#pragma once
//Audio
#include "Audio/AudioSystem.h"

//Core
#include "Core/Utilities.h"
#include "Core/FileSystem.h"
#include "Core/Timer.h"

//Math
#include "Math/Vector2.h"
#include "Math/Color.h"
#include "Math/Random.h"
#include "Math/MathUtils.h"
#include "Math/Transform.h"

//Graphics
#include "Graphics/Renderer.h"
#include "Graphics/Texture.h"
#include "Graphics/Font.h"
#include "Graphics/ParticleSystem.h"

//Input
#include "Input/InputSystem.h"

//Objects
#include "Object/Actor.h"
#include "Object/Scene.h"

//Framework
#include "Framework/EventSystem.h"

// Resource
#include "Resource/ResourceSystem.h"

//Others
#include <vector>
#include <memory>
#include <string>
#include <iostream>
#include <algorithm>

namespace glds
{
	class Engine
	{
	public:
		void Startup();
		void Shutdown();

		void Update();
		void Draw(Renderer* renderer);

		template<typename T>
		T* Get();

	public:
		FrameTimer time;

	private:
		std::vector<std::unique_ptr<System>> systems;
	};

	template<typename T>
	inline T* Engine::Get()
	{
		for (auto& system : systems)
		{
			if (dynamic_cast<T*>(system.get())) return dynamic_cast<T*>(system.get());
		}
		return nullptr;
	}
}