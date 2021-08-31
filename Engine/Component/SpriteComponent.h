#pragma once
#include "Component/GraphicsComponent.h"

#include <memory>

namespace glds
{
	class SpriteComponent : public GraphicsComponent
	{
	public:
		std::unique_ptr<Object> Clone() const override { return std::make_unique<SpriteComponent>(*this); }

		void Update() override;
		void Draw(Renderer* renderer) override;

		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;
	
	public:
		std::shared_ptr<class Texture> texture;
	};
}