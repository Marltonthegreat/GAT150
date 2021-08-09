#pragma once
#include "Framework/System.h"
#include "Math/Vector2.h"
#include <vector>

namespace glds
{
	class Renderer;
	class Texture;

	class ParticleSystem : public GraphicsSystem
	{
	private:
		struct Particle
		{
			Vector2 position, prevPosition, velocity;
			std::shared_ptr<Texture> texture;

			float lifetime;
			bool isActive{ false };

			static bool IsNotActive(Particle particle) { return !particle.isActive; }
		};
	public:
		void Startup() override;
		void Shutdown() override;

		void Update(float dt) override;
		void Draw(Renderer* renderer) override;

		void Create(const Vector2& position, const size_t count, const std::shared_ptr<Texture> texture, const float lifetime, const float speed);
		void Create(const Vector2& position, const size_t count, const float lifetime, const float speed, const float angle, const float angleRange);

	private:
		std::vector<Particle> particles;

	};
}