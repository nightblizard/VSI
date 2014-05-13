#include "WidgetBuilder.h"
#include <fstream>
#include <filesystem>
#include <vector>

#include <rapidxml\rapidxml_iterators.hpp>
#include "../Widgets/Connector.h"

namespace XML
{
	std::size_t getFileSize(const std::string& path)
	{
		std::ifstream file(path, std::ios::binary | std::ios::ate);
		return static_cast<std::size_t>(file.tellg());
	}

	WidgetBuilder::WidgetBuilder()
	{
	}


	std::shared_ptr<Widgets::Function> WidgetBuilder::Parse(const std::string& filePath)
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

		for (auto* attr = node->first_attribute(); attr; attr = attr->next_attribute())
			mWidget->SetProperty(attr->name(), attr->value());

		for (auto* subNode = node->first_node(); subNode; subNode = subNode->next_sibling())
		{
			for (auto* connectorNode = subNode->first_node(); connectorNode; connectorNode = connectorNode->next_sibling())
			{
				auto connector = std::make_shared<Widgets::Connector>();
				for (auto* attr = connectorNode->first_attribute(); attr; attr = attr->next_attribute())
					connector->SetProperty(attr->name(), attr->value());

				if (subNode->name() == std::string("Inputs"))
					mWidget->AddInput(connector);
				else if (subNode->name() == std::string("Outputs"))
					mWidget->AddOutput(connector);
				else if (subNode->name() == std::string("Variables"))
					mWidget->AddVariable(connector);
			}
		}

		return mWidget;
	}
}