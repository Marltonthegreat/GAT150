#pragma once
#include "Object/Actor.h"

class Enemy : public glds::Actor
{
//public:
	Enemy(const glds::Transform& transform, std::shared_ptr<glds::Texture> texture, float speed) : glds::Actor{ transform, texture }, speed{ speed } {}

	void Update(float dt) override;

	void OnCollision(Actor* actor) override;

private:
	float fireTimer{ .5f };
	float fireRate{ 5.0f };
	float speed{ 300 };
};