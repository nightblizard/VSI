#include "WidgetBuilder.h"
#include <fstream>
#include <filesystem>
#include <vector>

#include <rapidxml\rapidxml_iterators.hpp>

#include "Widget.h"

namespace Widgets
{
	std::size_t getFileSize(const std::string& path)
	{
		std::ifstream file(path, std::ios::binary | std::ios::ate);
		return static_cast<std::size_t>(file.tellg());
	}

	WidgetBuilder::WidgetBuilder()
	{
	}


	std::shared_ptr<Widget> WidgetBuilder::Parse(const std::string& filePath)
	{
		auto size = getFileSize(filePath);

		std::ifstream inFile(filePath);

		if (!inFile.is_open())
			throw std::exception("Could not open file!");

		std::vector<char> buffer(size);
		inFile.read(buffer.data(), size);

		mXmlDocument.parse<0>(buffer.data());

		auto node = mXmlDocument.first_node("Widget");

		mWidget = std::make_shared<Widget>();

		for (auto* attr = node->first_attribute(); attr; attr = attr->next_attribute())
			mWidget->SetProperty(attr->name(), attr->value());



		return mWidget;
	}
}