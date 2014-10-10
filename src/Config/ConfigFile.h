#pragma once

#include "ConfigEntry.h"
#include <fstream>
#include <map>

namespace Config
{
	class IParser;

	class ConfigFile
	{
		std::map<std::string, ConfigEntry> mKeyValues;

		std::string mFileName;
		std::fstream mFile;

	public:

		std::fstream& GetFileHandle();
		std::string GetFileName() const;

		template <typename T>
		T GetValueOrDefault(const std::string& key, T default) const
		{
			auto value = mKeyValues.find(key);
			if (value == mKeyValues.end())
				return default;

			return value->second.To<T>();
		}

		ConfigEntry operator [](const std::string& key) const;
		ConfigEntry& operator [](const std::string& key);


		ConfigFile(const std::string& filePath, IParser& parser);
		ConfigFile(const ConfigFile&) = default;
		ConfigFile(ConfigFile&& rhs) = default;
		ConfigFile& operator=(const ConfigFile&) = default;
		ConfigFile& operator=(ConfigFile&&) = default;
		virtual ~ConfigFile() = default;
	};
}