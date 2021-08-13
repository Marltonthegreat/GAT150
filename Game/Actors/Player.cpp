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
	//locator->transform.localRotation = glds::DegToRad(180);
	AddChild(std::move(locator));

	locator = std::make_unique<Actor>();
	locator->transform.localPosition = glds::Vector2{ 5, 3 };
	//locator->transform.localRotation = glds::DegToRad(180);
	AddChild(std::move(locator));

	//std::unique_ptr thruster = std::make_unique<Actor>(glds::Transform{}, scene->engine->Get<glds::ResourceSystem>()->Get<glds::texture>("thruster.txt"));
	//thruster->transform.localPosition = glds::Vector2{ -6, 0 };
	//thruster->transform.localScale = glds::Vector2{.5f};
	//AddChild(std::move(thruster));

	//thruster = std::make_unique<Actor>(glds::Transform{}, scene->engine->Get<glds::ResourceSystem>()->Get<glds::Shape>("thruster.txt"));
	//thruster->transform.localPosition = glds::Vector2{ 4, 3 };
	//thruster->transform.localRotation = glds::DegToRad(180);
	//thruster->transform.localScale = glds::Vector2{ .25f };
	//AddChild(std::move(thruster));

	//thruster = std::make_unique<Actor>(glds::Transform{}, scene->engine->Get<glds::ResourceSystem>()->Get<glds::Shape>("thruster.txt"));
	//thruster->transform.localPosition = glds::Vector2{ 4, -3 };
	//thruster->transform.localRotation = glds::DegToRad(180);
	//thruster->transform.localScale = glds::Vector2{ .25f };
	//AddChild(std::move(thruster));
}

void Player::Update(float dt)
{
	//children[3]->transform.localRotation += 5 * dt;

	//movement
	float thrust = 0;
	if (glds::IsButtonPressHold(SDL_SCANCODE_A, scene->engine)) transform.rotation -= 5 * dt;
	if (glds::IsButtonPressHold(SDL_SCANCODE_D, scene->engine)) transform.rotation += 5 * dt;
	if (glds::IsButtonPressHold(SDL_SCANCODE_W, scene->engine))
	{
		thrust = speed;
		scene->engine->Get<glds::ParticleSystem>()->Create(children[0]->transform.position, 3, scene->engine->Get<glds::ResourceSystem>()->Get<glds::Texture>("particle01.png", scene->engine->Get<glds::Renderer>()), 2, 150, children[0]->transform.rotation, glds::DegToRad(10));
	}
	//if (Core::Input::IsPressed('S'))
	//{
	//	velocity *= .95f;
	//	if (velocity.Length() > 1 )
	//	{
	//		scene->engine->Get<glds::ParticleSystem>()->Create(children[2]->transform.position, 3, 1, colors, velocity.Length()/4 + 50, children[2]->transform.rotation, glds::DegToRad(10));
	//		scene->engine->Get<glds::ParticleSystem>()->Create(children[3]->transform.position, 3, 1, colors, velocity.Length()/4 + 50, children[3]->transform.rotation, glds::DegToRad(10));
	//	}
	//	else if(velocity.Length() !=0 )
	//	{
	//		velocity = 0;
	//	}
	//}

	//acceleration
	glds::Vector2 acceleration = glds::Vector2::Rotate(glds::Vector2::right, transform.rotation) * thrust;


	velocity *= .99f; //dampening

	velocity += acceleration * dt;
	transform.position += velocity * dt;
	transform.position.x = glds::Wrap(transform.position.x, 0.0f, 800.0f);
	transform.position.y = glds::Wrap(transform.position.y, 0.0f, 600.0f);

	//fire
	fireTimer -= dt;
	//if (fireTimer <= 0 && Core::Input::IsPressed(VK_SPACE))
	//{
	//	fireTimer = fireRate;;

	//	glds::Transform t = children[1]->transform;
	//	t.scale = .5f;

	//	std::unique_ptr<Projectile> projectile = std::make_unique<Projectile>(t, scene->engine->Get<glds::ResourceSystem>()->Get<glds::Shape>("playerBullet.txt"), velocity.Length() + 600);
	//	projectile->tag = "Player";
	//	projectile->transform.scale = 5;
	//	scene->AddActor(std::move(projectile));

	//	scene->engine->Get<glds::AudioSystem>()->PlayAudio("playerFire");
	//}

	Actor::Update(dt);
}

void Player::OnCollision(Actor* actor)
{
	//if (dynamic_cast<Enemy*>(actor) || (dynamic_cast<Projectile*>(actor) && actor->tag == "Enemy"))
	//{
	//	destroy = true;
	//	std::vector<glds::Color> colors = { glds::Color::white, glds::Color::red, glds::Color::blue };
	//	scene->engine->Get<glds::ParticleSystem>()->Create(transform.position, 100, 2, colors[glds::RandomRangeInt(0, colors.size())], 150);
	//	scene->engine->Get<glds::AudioSystem>()->PlayAudio("explosion");

	//	glds::Event event;
	//	event.name = "PlayerDeath";
	//	scene->engine->Get<glds::EventSystem>()->Notify(event);
	//}
}
