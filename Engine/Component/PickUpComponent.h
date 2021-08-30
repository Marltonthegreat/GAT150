#pragma once
#include "Component/Component.h"
#include "Framework/EventSystem.h"

namespace glds
{


	class PickUpComponent : public Component
	{
	public:
		void Create() override;

		virtual void Update() override;

		virtual void OnCollisionEnter(const glds::Event& event);

		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;

	private:
		std::string soundName{};
	};
}