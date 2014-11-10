#include "WidgetBuilder.h"
#include <fstream>
#include <filesystem>
#include <vector>

#include <rapidxml\rapidxml_iterators.hpp>
#include "../Widgets/Connector.h"

#include "../Widgets/Controls/Panel.h"

namespace XML
{
	std::size_t getFileSize(const std::string& path)
	{
		std::ifstream file(path, std::ios::binary | std::ios::ate);
		return static_cast<std::size_t>(file.tellg());
	}

	WidgetBuilder::WidgetBuilder() : 
		mWidget(nullptr)
	{
	}


	std::shared_ptr<Widgets::Widget> WidgetBuilder::BuildFunction(rapidxml::xml_node<char>* node)
	{
		auto widget = std::make_shared<Widgets::Function>();
		for (auto* subNode = node->first_node(); subNode; subNode = subNode->next_sibling())
		{
			for (auto* connectorNode = subNode->first_node(); connectorNode; connectorNode = connectorNode->next_sibling())
			{
				auto connector = std::make_shared<Widgets::Connector>();
				for (auto* attr = connectorNode->first_attribute(); attr; attr = attr->next_attribute())
					connector->SetProperty(attr->name(), attr->value());

				if (subNode->name() == std::string("Inputs"))
					widget->AddInput(connector);
				else if (subNode->name() == std::string("Outputs"))
					widget->AddOutput(connector);
				else if (subNode->name() == std::string("Variables"))
					widget->AddVariable(connector);
			}
		}

		return widget;
	}


	std::shared_ptr<Widgets::Widget> WidgetBuilder::BuildPanel(rapidxml::xml_node<char>* node)
	{
		auto widget = std::make_shared<Widgets::Panel>();
		return widget;
	}


	std::shared_ptr<Widgets::Widget> WidgetBuilder::Parse(const std::string& filePath)
	{
		auto size = getFileSize(filePath);

		std::ifstream inFile(filePath);

		if (!inFile.is_open())
			throw std::exception("Could not open file!");

		std::vector<char> buffer(size);
		inFile.read(buffer.data(), size);

		mXmlDocument.parse<0>(buffer.data());

		auto node = mXmlDocument.first_node("Widget");

		mWidget = std::make_shared<Widgets::Function>();

		//Hackfix! Redo this one
		int i = 0;

		for (auto* attr = node->first_attribute(); attr; attr = attr->next_attribute())
		{
			if (i == 0)
			{
				if (attr->name() != std::string("type"))
					throw std::exception("First widget attribute must be its type!");

				std::string type = attr->value();
				if (type == "function")
					mWidget = BuildFunction(node);
				if (type == "panel")
					mWidget = BuildPanel(node);
				++i;
			}

			mWidget->SetProperty(attr->name(), attr->value());
		}

		return mWidget;
	}
}