#pragma once

#include "Widget.h"
#include "Dragable.h"
#include <cinder\Color.h>

namespace Widgets
{
	class Connector;

	class Function : public Dragable
	{
		std::vector<std::shared_ptr<Connector>> mInputs;
		std::vector<std::shared_ptr<Connector>> mOutputs;
		std::vector<std::shared_ptr<Connector>> mVariables;

		cinder::Color mColor = cinder::Color::hex(0xFFC993);

	public:
		void Draw() const override;

		void AddInput(std::shared_ptr<Connector> input);
		void AddOutput(std::shared_ptr<Connector> output);
		void AddVariable(std::shared_ptr<Connector> variable);
	};
}