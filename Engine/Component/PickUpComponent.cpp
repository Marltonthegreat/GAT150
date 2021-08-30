#include "PickUpComponent.h"
#include "Engine.h"

namespace glds
{
	void PickUpComponent::Create()
	{
		owner->scene->engine->Get<EventSystem>()->Subscribe("collision_enter", std::bind(&PickUpComponent::OnCollisionEnter, this, std::placeholders::_1), owner);
	
		owner->scene->engine->Get<AudioSystem>()->AddAudio(soundName, "audio/" + soundName + ".wav");
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
			owner->scene->engine->Get<AudioSystem>()->PlayAudio("coin");

			owner->destroy = true;
		}
	}

	bool PickUpComponent::Write(const rapidjson::Value& value) const
	{
		return false;
	}
	
	bool PickUpComponent::Read(const rapidjson::Value& value)
	{
		JSON_READ(value, soundName);

		return true;
	}
}