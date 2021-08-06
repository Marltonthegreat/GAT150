#include "Actor.h"
#include "Math/MathUtils.h"
#include "Graphics/Renderer.h"
#include <algorithm>

namespace glds
{
	void Actor::Update(float dt)
	{
		transform.rotation += 360 * dt;
		transform.rotation = glds::Wrap(transform.rotation, 0.0f, 360.0f);
		transform.position.x +=  900 * dt;
		transform.position.x = glds::Wrap(transform.position.x, -50.0f, 850.0f);

		transform.Update();
		std::for_each(children.begin(), children.end(), [](auto& child) {child->transform.Update(child->parent->transform.matrix); });
	}

	void Actor::Draw(Renderer* renderer)
	{
		renderer->Draw(texture, transform);
	}
	
	void Actor::AddChild(std::unique_ptr<Actor> actor)
	{
		actor->parent = this;
		children.push_back(std::move(actor));
	}

	float Actor::GetRadius()
	{
		Vector2 size = texture->GetSize();

		return (texture) ? texture->GetSize().Length() * 0.5f : 0;
	}
}