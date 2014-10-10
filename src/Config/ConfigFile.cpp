#include "ConfigFile.h"
#include "IParser.h"

#include <sstream>

namespace Config
{
	std::fstream& ConfigFile::GetFileHandle()
	{
		return mFile;
	}

	std::string ConfigFile::GetFileName() const
	{
		return mFileName;
	}

	ConfigEntry ConfigFile::operator [](const std::string& key) const
	{
		auto it = mKeyValues.find(key);
		if (it != mKeyValues.end())
			return it->second;

		return ConfigEntry();
	}

	ConfigEntry& ConfigFile::operator [](const std::string& key)
	{
		return mKeyValues[key];
	}

	ConfigFile::ConfigFile(const std::string& filePath, IParser& parser) :
		mFile(filePath),
		mFileName(filePath)
	{
		if (!mFile.is_open())
		{
			std::stringstream ss;
			ss << "could not open file '" << filePath << "'!";
			throw std::exception(ss.str().c_str());
		}

		parser.Parse(const_cast<ConfigFile&>(*this));
	}
}