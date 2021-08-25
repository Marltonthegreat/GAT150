#include "PlayerComponent.h"
#include "Engine.h"

using namespace glds;

void PlayerComponent::Update()
{
	Vector2 force = 0;

	if (IsButtonPressHold(SDL_SCANCODE_A, owner->scene->engine))
	{
		force.x -= speed;
	}
	if (IsButtonPressHold(SDL_SCANCODE_D, owner->scene->engine))
	{
		force.x += speed;
	}

	PhysicsComponent* physicsComponent = owner->GetComponent<PhysicsComponent>();
	assert(physicsComponent);

	physicsComponent->ApplyForce(force);
}

bool PlayerComponent::Write(const rapidjson::Value& value) const
{
	return false;
}

bool PlayerComponent::Read(const rapidjson::Value& value)
{
	JSON_READ(value, speed);

	return true;
}