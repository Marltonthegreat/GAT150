#pragma once

#define REGISTER_CLASS(class) glds::ObjectFactory::Instance().Register<class>(#class)

//Math
#include "Math/Vector2.h"
#include "Math/Color.h"
#include "Math/Random.h"
#include "Math/MathUtils.h"
#include "Math/Transform.h"

//Framework
#include "Framework/EventSystem.h"
#include "Framework/Singleton.h"
#include "Framework/Factory.h"

//Core
#include "Core/Utilities.h"
#include "Core/FileSystem.h"
#include "Core/Timer.h"
#include "Core/Json.h"
#include "Core/Serializable.h"

//Audio
#include "Audio/AudioSystem.h"

//Graphics
#include "Graphics/Renderer.h"
#include "Graphics/Texture.h"
#include "Graphics/Font.h"
#include "Graphics/ParticleSystem.h"

//Physics
#include "Physics/PhysicsSystem.h"

//Input
#include "Input/InputSystem.h"

//Object
#include "Object/Actor.h"
#include "Object/Scene.h"

//Component
#include "Component/SpriteComponent.h"
#include "Component/SpriteAnimationComponent.h"
#include "Component/PhysicsComponent.h"
#include "Component/RBPhysicsComponent.h"
#include "Component/AudioComponent.h"
#include "Component/TextComponent.h"

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
	using ObjectFactory = Singleton<Factory<std::string, Object>>;

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