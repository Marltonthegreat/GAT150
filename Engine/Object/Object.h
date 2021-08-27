#pragma once

namespace glds
{
	class Object
	{
	public:
		virtual ~Object() {}

		virtual void Create() {}
	};
}