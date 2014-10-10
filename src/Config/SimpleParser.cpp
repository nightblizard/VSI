#include "SimpleParser.h"
#include "ConfigFile.h"

#include <sstream>

namespace Config
{
	void SimpleParser::Parse(ConfigFile& cfgFile)
	{
		auto& file = cfgFile.GetFileHandle();

		int lineCounter = 1;
		std::string key;
		while (std::getline(file, key, ' '))
		{
			std::string value;
			if(!std::getline(file, value) || value.empty() || key.find('\n') != -1)
			{
				std::stringstream ss;
				ss << "unexpected end of file in file '" << cfgFile.GetFileName() << "'"
					<< " line: " << lineCounter;

				throw std::exception(ss.str().c_str());
			}

			cfgFile[key] = value;
			++lineCounter;
		}
	}
}