#pragma once
#include "document.h"
#include "Math/Vector2.h"
#include <string>

#define JSON_READ(value, data) glds::json::Get(value, #data , data)

namespace glds
{
	namespace json
	{
		bool Load(const std::string& filename, rapidjson::Document& document);
		bool Get(const rapidjson::Value& value, const std::string& name, int& data);
		bool Get(const rapidjson::Value& value, const std::string& name, float& data);
		bool Get(const rapidjson::Value& value, const std::string& name, std::string& data);
		bool Get(const rapidjson::Value& value, const std::string& name, Vector2& data);
	}
}