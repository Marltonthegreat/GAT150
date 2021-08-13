#include "Projectile.h"
#include "Player.h"
#include "Enemy.h"
#include "Engine.h"
#include "Math/MathUtils.h"

void Projectile::Update(float dt)
{
	//Actor::Update(dt);

	//lifetime -= dt;
	//destroy = (lifetime <= 0);

	//transform.position += glds::Vector2::Rotate(glds::Vector2::right, transform.rotation) * speed * dt;

	//std::vector<glds::Color> colors = { glds::Color::white, glds::Color::red, glds::Color::blue };
	//scene->engine->Get<glds::ParticleSystem>()->Create(transform.position, 10, .25f, colors[glds::RandomRangeInt(0, colors.size())], 10);

	//transform.Update();
}

void Projectile::OnCollision(Actor* actor)
{
	if ((dynamic_cast<Enemy*>(actor) && tag != "Enemy") || (dynamic_cast<Player*>(actor) && tag != "Player"))
	{
		destroy = true;
	}
}
