#pragma once

#include <memory>
#include <string>
#include <rapidxml\rapidxml.hpp>

namespace Widgets
{
	class Widget;

	class WidgetBuilder
	{
		std::shared_ptr<Widget> mWidget;

		rapidxml::xml_document<> mXmlDocument;
	public:

		WidgetBuilder();

		std::shared_ptr<Widget> Parse(const std::string& filePath);
};
}