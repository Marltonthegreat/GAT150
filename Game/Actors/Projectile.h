#pragma once
#include "Object/Actor.h"

class Projectile : public glds::Actor
{
public:
	Projectile(const glds::Transform& transform, std::shared_ptr<glds::Texture> texture, float speed) : glds::Actor{ transform, texture }, speed{ speed } {}

	void Update(float dt) override;

	void OnCollision(Actor* actor) override;

private:
	float lifetime{ 2 };
	float speed{ 0 };
};