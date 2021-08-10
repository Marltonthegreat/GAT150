#include "ParticleSystem.h"
#include "Texture.h"
#include "Renderer.h"
#include "Math/Random.h"

namespace glds
{
	float random()
	{
		return rand() / static_cast<float>(RAND_MAX);
	}

	float random(float min, float max)
	{
		return min + (max - min) * random();
	}

	void ParticleSystem::Startup()
	{
		particles.resize(1000);
	}

	void ParticleSystem::Shutdown()
	{
		particles.clear();
	}

	void ParticleSystem::Update(float dt)
	{
		for (Particle& particle : particles)
		{
			if(particle.isActive)
			{
				particle.lifetime -= dt;
				particle.isActive = particle.lifetime > 0;
				particle.prevPosition = particle.position;
				particle.position += particle.velocity * dt;
			}
		}
	}

	void ParticleSystem::Draw(Renderer* renderer)
	{
		for (const Particle& particle : particles)
		{
			if (particle.isActive)
			{
				renderer->Draw(particle.texture, particle.position);
			}
		}
	}

	void ParticleSystem::Create(const Vector2& position, const size_t count, const std::shared_ptr<Texture> texture, const float lifetime, const float speed)
	{
		for (size_t i = 0; i < count; i++)
		{
			auto particle = std::find_if(particles.begin(), particles.end(), Particle::IsNotActive);
			if (particle != particles.end())
			{
				particle->isActive = true;
				particle->lifetime = lifetime;
				particle->position = position;
				particle->prevPosition = position;
				particle->texture = texture;
				
				particle->velocity = Vector2(RandomRange(-1,1) * speed, RandomRange(-1, 1) * speed);
			}
		}
	}
	
	void ParticleSystem::Create(const Vector2& position, const size_t count, const float lifetime, const float speed, const float angle, const float angleRange)
	{
		for (size_t i = 0; i < count; i++)
		{
			auto particle = std::find_if(particles.begin(), particles.end(), Particle::IsNotActive);
			if (particle != particles.end())
			{
				particle->isActive = true;
				particle->lifetime = lifetime;
				particle->position = position;
				particle->prevPosition = position;

				particle->velocity = (glds::Vector2::Rotate(glds::Vector2::right, angle + glds::RandomRange(-angleRange, angleRange))) * (speed * Random());
			}
		}
	}
}