#pragma once

#include <utility>
#include <string>
#include <vector>
#include <cstdint>

namespace Config
{
	class ConfigEntry
	{
		std::string mValue = "";

	public:
		template <typename T>
		T To() const;

		bool IsEmpty() const;

		ConfigEntry() = default;
		ConfigEntry(const std::string& value);
		ConfigEntry(const ConfigEntry&) = default;
		ConfigEntry(ConfigEntry&& rhs) = default;
		ConfigEntry& operator=(const ConfigEntry&) = default;
		ConfigEntry& operator=(ConfigEntry&&) = default;
		virtual ~ConfigEntry() = default;
	};

	typedef std::pair<std::string, ConfigEntry> KeyValuePair;
}