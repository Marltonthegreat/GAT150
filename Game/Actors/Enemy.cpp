#include "Enemy.h"
#include "Player.h"
#include "Projectile.h"
#include "Engine.h"

void Enemy::Update(float dt)
{
	if (scene->GetActor<Player>())
	{
		glds::Vector2 direction = scene->GetActor<Player>()->transform.position - transform.position;
		glds::Vector2 forward = glds::Vector2::Rotate(glds::Vector2::right, transform.rotation);

		float turnAngle = glds::Vector2::SignedAngle(forward, direction.Normalized());
		transform.rotation = transform.rotation + turnAngle * (dt * 3);
		
		//transform.rotation = glds::Lerp(transform.rotation, transform.rotation + turnAngle, dt * 5);

		float angle = glds::Vector2::Angle(forward, direction.Normalized());

		fireTimer -= dt;
		//if (fireTimer <= 0 && angle <= glds::DegToRad(10))
		//{
		//	fireTimer = fireRate;
		//	std::vector<glds::Vector2> points = { {-5,-5}, {5,-5}, {0,8}, {-5,-5} };
		//	std::shared_ptr<glds::Shape> shape = std::make_shared<glds::Shape>(points, glds::Color::red);

		//	glds::Transform t = transform;
		//	t.scale = .5f;

		//	std::unique_ptr<Projectile> projectile = std::make_unique<Projectile>(t, scene->engine->Get<glds::ResourceSystem>()->Get<glds::Shape>("enemyBullet.txt"), 450);
		//	projectile->tag = "Enemy";
		//	projectile->transform.scale = 5;
		//	scene->AddActor(std::move(projectile));

		//	scene->engine->Get<glds::AudioSystem>()->PlayAudio("enemyFire");
		//}

	}
	//transform.rotation = ;

	transform.position += glds::Vector2::Rotate(glds::Vector2::right, transform.rotation) * speed * dt;
	transform.position.x = glds::Wrap(transform.position.x, 0.0f, 800.0f);
	transform.position.y = glds::Wrap(transform.position.y, 0.0f, 600.0f);

	Actor::Update(dt);
}

void Enemy::OnCollision(Actor* actor)
{
	if (dynamic_cast<Player*>(actor) || (dynamic_cast<Projectile*>(actor) && actor->tag == "Player"))
	{
		destroy = true;
		std::vector<glds::Color> colors = { glds::Color::white, glds::Color::red, glds::Color::blue };
		scene->engine->Get<glds::ParticleSystem>()->Create(transform.position, 10, scene->engine->Get<glds::ResourceSystem>()->Get<glds::Texture>("particle02.png", scene->engine->Get<glds::Renderer>()), 1, 150, transform.rotation, glds::DegToRad(360));
		scene->engine->Get<glds::AudioSystem>()->PlayAudio("explosion");

		glds::Event event;
		event.name = "AddPoints";
		event.data = 1;
		scene->engine->Get<glds::EventSystem>()->Notify(event);
	}
}
