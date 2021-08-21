#pragma once
#include "document.h"
#include <string>

namespace glds
{
	namespace json
	{
		bool Load(const std::string& filename, rapidjson::Document& document);
		bool Get(const rapidjson::Value& value, const std::string& name, int& data);
	}
}