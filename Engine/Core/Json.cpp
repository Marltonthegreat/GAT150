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
	
	bool Get(const rapidjson::Value& value, const std::string& name, float& data)
	{
		// check if 'name' member exists and is of type
		if (value.HasMember(name.c_str()) == false || value[name.c_str()].IsNumber() == false)
		{
			return false;
		}

		// set data
		data = value[name.c_str()].GetFloat();

		return true;
	}

	bool Get(const rapidjson::Value& value, const std::string& name, bool& data)
	{
		// check if 'name' member exists and is of type
		if (value.HasMember(name.c_str()) == false || value[name.c_str()].IsBool() == false)
		{
			return false;
		}

		// set data
		data = value[name.c_str()].GetBool();

		return true;
	}

	bool Get(const rapidjson::Value& value, const std::string& name, std::string& data)
	{
		// check if 'name' member exists and is of type
		if (value.HasMember(name.c_str()) == false || value[name.c_str()].IsString() == false)
		{
			return false;
		}

		// set data
		data = value[name.c_str()].GetString();

		return true;
	}

	bool Get(const rapidjson::Value& value, const std::string& name, Vector2& data)
	{
		// check if 'name' member exists and is of type
		if (value.HasMember(name.c_str()) == false || value[name.c_str()].IsArray() == false || value[name.c_str()].Size() != 2)
		{
			return false;
		}

		// set data
		auto& array = value[name.c_str()];
		for (rapidjson::SizeType i = 0; i < array.Size(); i++)
		{
			if (array[i].IsNumber())
			{
				data[i] = array[i].GetFloat();
			}
		}

		return true;
	}

	bool Get(const rapidjson::Value& value, const std::string& name, Color& data)
	{
		// check if 'name' member exists and is of type
		if (value.HasMember(name.c_str()) == false || value[name.c_str()].IsArray() == false || value[name.c_str()].Size() != 3)
		{
			return false;
		}

		// set data
		auto& array = value[name.c_str()];
		for (rapidjson::SizeType i = 0; i < array.Size(); i++)
		{
			if (array[i].IsNumber())
			{
				data[i] = array[i].GetFloat();
			}
		}

		return true;
	}

	bool Get(const rapidjson::Value& value, const std::string& name, SDL_Rect& data)
	{
		// check if 'name' member exists and is of type
		if (value.HasMember(name.c_str()) == false || value[name.c_str()].IsArray() == false || value[name.c_str()].Size() != 4)
		{
			return false;
		}

		// set data
		auto& array = value[name.c_str()];

		data.x = array[0].GetInt();
		data.y = array[1].GetInt();
		data.w = array[2].GetInt();
		data.h = array[3].GetInt();

		return true;
	}

	bool Get(const rapidjson::Value& value, const std::string& name, std::vector<std::string>& data)
	{
		// check if 'name' member exists and is of type
		if (value.HasMember(name.c_str()) == false || value[name.c_str()].IsArray() == false)
		{
			return false;
		}

		// set data
		auto& array = value[name.c_str()];
		for (auto& element : array.GetArray())
		{
			data.push_back(element.GetString());
		}

		return true;
	}

	bool Get(const rapidjson::Value& value, const std::string& name, std::vector<int>& data)
	{
		// check if 'name' member exists and is of type
		if (value.HasMember(name.c_str()) == false || value[name.c_str()].IsArray() == false)
		{
			return false;
		}

		// set data
		auto& array = value[name.c_str()];
		for (auto& element : array.GetArray())
		{
			data.push_back(element.GetInt());
		}

		return true;
	}
}