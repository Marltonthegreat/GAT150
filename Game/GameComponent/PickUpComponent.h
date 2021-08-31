#pragma once
#include "Component/Component.h"
#include "Framework/EventSystem.h"

class PickUpComponent : public glds::Component
{
public:
	virtual ~PickUpComponent();

	std::unique_ptr<Object> Clone() const override { return std::make_unique<PickUpComponent>(*this); }

	void Create() override;

	virtual void Update() override;

	virtual void OnCollisionEnter(const glds::Event& event);

	virtual bool Write(const rapidjson::Value& value) const override;
	virtual bool Read(const rapidjson::Value& value) override;
};