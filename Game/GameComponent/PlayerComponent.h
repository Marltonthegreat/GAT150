#pragma once
#include "Component/Component.h"
#include "Framework/EventSystem.h"
#include <list>

class PlayerComponent : public glds::Component
{
public:
	void Create() override;

	virtual void Update() override;

	virtual void OnCollisionEnter(const glds::Event& event);
	virtual void OnCollisionExit(const glds::Event& event);

	virtual bool Write(const rapidjson::Value& value) const override;
	virtual bool Read(const rapidjson::Value& value) override;

public:
	float speed{ 0 };
private:
	std::list<glds::Actor*> contacts;
};