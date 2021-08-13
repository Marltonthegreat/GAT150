#include "Utilities.h"
#include "Engine.h"
#include <algorithm>

namespace glds
{
	std::string string_toLower(const std::string& str)
	{
		std::string lower = str;

		std::transform(lower.begin(), lower.end(), lower.begin(), [](char c)
		{
			return std::tolower(c);
		});
	
		return lower;
	}

	bool istring_compare(const std::string& str1, const std::string& str2)
	{
		return std::equal(str1.begin(), str1.end(), str2.begin(), [](char c1, char c2)
		{
			return (std::tolower(c1) == std::tolower(c2));
		});
	}

	bool IsButtonPressed(int id, Engine* engine)
	{
		return engine->Get<glds::InputSystem>()->GetKeyState(id) == glds::InputSystem::eKeyState::Pressed;
	}

	bool IsButtonHeld(int id, Engine* engine)
	{
		return engine->Get<glds::InputSystem>()->GetKeyState(id) == glds::InputSystem::eKeyState::Held;
	}

	bool IsButtonPressHold(int id, Engine* engine)
	{
		return IsButtonPressed(id, engine) || IsButtonHeld(id, engine);
	}
}