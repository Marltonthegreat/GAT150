#include "PickUpComponent.h"
#include "Engine.h"

using namespace glds;

PickUpComponent::~PickUpComponent()
{
	owner->scene->engine->Get<EventSystem>()->Unsubscribe("collision_enter", owner);
}

void PickUpComponent::Create()
{
	owner->scene->engine->Get<EventSystem>()->Subscribe("collision_enter", std::bind(&PickUpComponent::OnCollisionEnter, this, std::placeholders::_1), owner);
}

void PickUpComponent::Update()
{

}

void PickUpComponent::OnCollisionEnter(const glds::Event& event)
{
	void* p = std::get<void*>(event.data);
	Actor* actor = reinterpret_cast<Actor*>(p);

	if (istring_compare(actor->tag, "Player"))
	{
		owner->GetComponent<AudioComponent>()->Play();
		owner->destroy = true;

		Event event;
		event.name = "add_points";
		event.data = 1;

		owner->scene->engine->Get<EventSystem>()->Notify(event);
	}
}

bool PickUpComponent::Write(const rapidjson::Value& value) const
{
	return false;
}
	
bool PickUpComponent::Read(const rapidjson::Value& value)
{
	return false;
}