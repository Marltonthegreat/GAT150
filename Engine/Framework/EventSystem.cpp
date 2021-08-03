#include "EventSystem.h"

void glds::EventSystem::Startup()
{

}

void glds::EventSystem::Shutdown()
{

}

void glds::EventSystem::Update(float dt)
{

}

void glds::EventSystem::Subscribe(const std::string& name, function_t function)
{
	Observer observer;
	observer.function = function;
	observers[name].push_back(observer);
}

void glds::EventSystem::Notify(const Event& event)
{
	auto& eventObservers = observers[event.name];

	for (auto& observer : eventObservers)
	{
		observer.function(event);
	}
}
