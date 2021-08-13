#pragma once
#include "Object/Actor.h"

class Player : public glds::Actor
{
public:
	Player(const glds::Transform& transform, std::shared_ptr<glds::Texture> texture, float speed);

	void Initialize() override;

	void Update(float dt) override;
	void OnCollision(Actor* actor) override;

private:
	float fireTimer{ 0 };
	float fireRate{ 0.5f };
	float speed{ 300 };
	glds::Vector2 velocity;
};