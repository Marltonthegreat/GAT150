#include "Json.h"
#include "istreamwrapper.h"
#include <fstream>

namespace glds::json
{
	bool Load(const std::string& filename, rapidjson::Document& document)
	{
		bool success = false;

		std::ifstream stream(filename);
			if (stream.is_open())
			{
				rapidjson::IStreamWrapper istream(stream);
				document.ParseStream(istream);
				success = document.IsObject();
			}

		return success;
	}

	bool Get(const rapidjson::Value& value, const std::string& name, int& data)
	{
		// check if 'name' member exists and is of type
		if (value.HasMember(name.c_str()) == false || value[name.c_str()].IsInt() == false)
		{
			return false;
		}

		// set data
		data = value[name.c_str()].GetInt();

		return true;
	}
}