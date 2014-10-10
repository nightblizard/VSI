#pragma once

#include "ConfigEntry.h"
#include "ConfigFile.h"

namespace Config
{
	class ConfigFile;

	class IParser
	{
	public:
		virtual void Parse(ConfigFile& cfgFile) = 0;
		virtual ~IParser() {}
	};
}