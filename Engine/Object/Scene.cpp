#include "Scene.h"
#include "Actor.h"
#include "Engine.h"
#include <algorithm>

namespace glds
{
	void Scene::Update(float dt)
	{
		// add new actors
		actors.insert(actors.end(), std::make_move_iterator(newActors.begin()), std::make_move_iterator(newActors.end()));
		newActors.clear();

		// update actors
		std::for_each(actors.begin(), actors.end(), [dt](auto& actor) {actor->Update(dt); });

		// check collissions
		for (size_t i = 0; i < actors.size(); i++)
		{
			for (size_t j = i + 1; j < actors.size(); j++)
			{
				if (actors[i]->destroy || actors[j]->destroy) continue;

				glds::Vector2 dir = actors[i]->transform.position - actors[j]->transform.position;
				float distance = dir.Length();

				if (distance < actors[i]->GetRadius())
				{
					actors[i]->OnCollision(actors[j].get());
					actors[j]->OnCollision(actors[i].get());
				}
			}
		}

		// destroy actors
		auto iter = actors.begin();
		while (iter != actors.end())
		{
			if ((*iter)->destroy)
			{
				iter = actors.erase(iter);
			}
			else
			{
				iter++;
			}
		}
	}

	void Scene::Draw(Renderer* renderer)
	{
		std::for_each(actors.begin(), actors.end(), [renderer](auto& actor) {actor->Draw(renderer); });
	}

	void Scene::AddActor(std::unique_ptr<Actor> actor)
	{
		actor->scene = this;
		actor->Initialize();

		newActors.push_back(std::move(actor));
	}

	void Scene::RemoveActor(Actor* actor)
	{
	}

	void Scene::RemoveAllActors()
	{
		actors.clear();
	}

	Actor* Scene::FindActor(const std::string& name)
	{
		for (auto& actor : actors)
		{
			if (actor->name == name) return actor.get();
		}

		return nullptr;
	}
	
	bool Scene::Write(const rapidjson::Value& value) const
	{
		return false;
	}
	
	bool Scene::Read(const rapidjson::Value& value)
	{
		if (value.HasMember("actors") && value["actors"].IsArray())
		{
			for (auto& actorValue : value["actors"].GetArray())
			{
				std::string type;
				JSON_READ(actorValue, type);
				auto actor = ObjectFactory::Instance().Create<Actor>(type);

				if (actor)
				{
					actor->scene = this;
					actor->Read(actorValue);
					AddActor(std::move(actor));
				}
			}
		}

		return true;
	}
}