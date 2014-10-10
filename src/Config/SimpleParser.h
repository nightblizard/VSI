#pragma once
/**
	SimpleParser
	Parses config files with the format "key value"
*/



#include "IParser.h"

namespace Config
{
	class SimpleParser : public IParser
	{
	public:
		void Parse(ConfigFile& file) override;

		SimpleParser() = default;
		SimpleParser(const SimpleParser&) = default;
		SimpleParser(SimpleParser&& rhs) = default;
		SimpleParser& operator=(const SimpleParser&) = default;
		SimpleParser& operator=(SimpleParser&&) = default;
		virtual ~SimpleParser() = default;
	};
}