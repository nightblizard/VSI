#pragma once

#include <memory>
#include <string>
#include <rapidxml\rapidxml.hpp>
#include "../Widgets/Function.h"


namespace XML
{

	class WidgetBuilder
	{
		std::shared_ptr<Widgets::Widget> mWidget;

		rapidxml::xml_document<> mXmlDocument;

		std::shared_ptr<Widgets::Widget> BuildFunction(rapidxml::xml_node<char>* node);
		std::shared_ptr<Widgets::Widget> BuildPanel(rapidxml::xml_node<char>* node);

	public:

		WidgetBuilder();

		std::shared_ptr<Widgets::Widget> Parse(const std::string& filePath);
	};
}