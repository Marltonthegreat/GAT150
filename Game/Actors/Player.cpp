#include "Player.h"
#include "Projectile.h"
#include "Enemy.h"
#include "Engine.h"
#include <SDL.h>
#include "Math/MathUtils.h"

Player::Player(const glds::Transform& transform, std::shared_ptr<glds::Texture> texture, float speed) : glds::Actor{ transform, texture }, speed{ speed }
{

}

void Player::Initialize()
{
	std::unique_ptr locator = std::make_unique<Actor>();
 	locator->transform.localPosition = glds::Vector2{ -8, 0 };
	locator->transform.localRotation = glds::DegToRad(180);
	AddChild(std::move(locator));

	locator = std::make_unique<Actor>();
	locator->transform.localPosition = glds::Vector2{ 5, 0 };
	AddChild(std::move(locator));

	locator = std::make_unique<Actor>();
	locator->transform.localPosition = glds::Vector2{ 5, -3 };
	AddChild(std::move(locator));

	locator = std::make_unique<Actor>();
	locator->transform.localPosition = glds::Vector2{ 5, 3 };
	AddChild(std::move(locator));
}

void Player::Update(float dt)
{
	//movement
	float thrust = 0;
	if (glds::IsButtonPressHold(SDL_SCANCODE_A, scene->engine)) transform.rotation -= 5 * dt;
	if (glds::IsButtonPressHold(SDL_SCANCODE_D, scene->engine)) transform.rotation += 5 * dt;
	if (glds::IsButtonPressHold(SDL_SCANCODE_W, scene->engine))
	{
		thrust = speed;
		scene->engine->Get<glds::ParticleSystem>()->Create(children[0]->transform.position, 3, scene->engine->Get<glds::ResourceSystem>()->Get<glds::Texture>("particle01.png", scene->engine->Get<glds::Renderer>()), 1, 150, children[0]->transform.rotation, glds::DegToRad(10));
	}
	if (glds::IsButtonPressHold(SDL_SCANCODE_S, scene->engine))
	{
		velocity *= .95f;
		if (velocity.Length() > 10 )
		{
			scene->engine->Get<glds::ParticleSystem>()->Create(children[2]->transform.position, 3, scene->engine->Get<glds::ResourceSystem>()->Get<glds::Texture>("particle01.png", scene->engine->Get<glds::Renderer>()), 1, velocity.Length()/2 + 50, children[2]->transform.rotation, glds::DegToRad(10));
			scene->engine->Get<glds::ParticleSystem>()->Create(children[3]->transform.position, 3, scene->engine->Get<glds::ResourceSystem>()->Get<glds::Texture>("particle01.png", scene->engine->Get<glds::Renderer>()), 1, velocity.Length()/2 + 50, children[3]->transform.rotation, glds::DegToRad(10));
		}
		else if(velocity.Length() !=0 )
		{
			velocity = 0;
		}
	}

	//acceleration
	glds::Vector2 acceleration = glds::Vector2::Rotate(glds::Vector2::right, transform.rotation) * thrust;


	velocity *= .99f; //dampening

	velocity += acceleration * dt;
	transform.position += velocity * dt;
	transform.position.x = glds::Wrap(transform.position.x, 0.0f, 800.0f);
	transform.position.y = glds::Wrap(transform.position.y, 0.0f, 600.0f);

	//fire
	fireTimer -= dt;
	if (fireTimer <= 0 && glds::IsButtonPressHold(SDL_SCANCODE_SPACE, scene->engine))
	{
		fireTimer = fireRate;;

		glds::Transform t = children[1]->transform;
		t.scale = .5f;

		std::unique_ptr<Projectile> projectile = std::make_unique<Projectile>(t, scene->engine->Get<glds::ResourceSystem>()->Get<glds::Texture>("particle01.png", scene->engine->Get<glds::Renderer>()), velocity.Length() + 600);
		projectile->tag = "Player";
		scene->AddActor(std::move(projectile));

		scene->engine->Get<glds::AudioSystem>()->PlayAudio("playerFire");
	}

	Actor::Update(dt);
}

void Player::OnCollision(Actor* actor)
{
	if (dynamic_cast<Enemy*>(actor) || (dynamic_cast<Projectile*>(actor) && actor->tag == "Enemy"))
	{
		destroy = true;
		std::vector<glds::Color> colors = { glds::Color::white, glds::Color::red, glds::Color::blue };
		scene->engine->Get<glds::ParticleSystem>()->Create(transform.position, 10, scene->engine->Get<glds::ResourceSystem>()->Get<glds::Texture>("particle02.png", scene->engine->Get<glds::Renderer>()), 1, 150, transform.rotation, glds::DegToRad(360));
		scene->engine->Get<glds::AudioSystem>()->PlayAudio("explosion");

		glds::Event event;
		event.name = "PlayerDeath";
		scene->engine->Get<glds::EventSystem>()->Notify(event);
	}
}
