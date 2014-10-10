#pragma once

#include <memory>
#include <string>
#include <rapidxml\rapidxml.hpp>
#include "../Widgets/Function.h"


namespace XML
{

	class WidgetBuilder
	{
		std::shared_ptr<Widgets::Function> mWidget;

		rapidxml::xml_document<> mXmlDocument;
	public:

		WidgetBuilder();

		std::shared_ptr<Widgets::Function> Parse(const std::string& filePath);

};
}