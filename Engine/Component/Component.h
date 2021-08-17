#pragma once
#include "Object/Object.h"

namespace glds
{
	class Component : public Object
	{
	public:
		virtual void Update() = 0;

	public:
		class Actor* owner{ nullptr };
	};
}