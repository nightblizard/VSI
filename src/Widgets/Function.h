#pragma once

#include "Widget.h"
#include <cinder\Color.h>

namespace Widgets
{
	class Connector;

	class Function : public Widget
	{
		std::vector<std::shared_ptr<Connector>> mInputs;
		std::vector<std::shared_ptr<Connector>> mOutputs;
		std::vector<std::shared_ptr<Connector>> mVariables;

		cinder::Color mColor = cinder::Color::hex(0xFFC993);


		void OnMouseUp(cinder::app::MouseEvent& event) override;
		void OnMouseDown(cinder::app::MouseEvent& event) override;
		void OnMouseMove(cinder::app::MouseEvent& event) override;
		void OnMouseDrag(cinder::app::MouseEvent& event) override;

	public:
		void Draw() const override;

		void AddInput(std::shared_ptr<Connector> input);
		void AddOutput(std::shared_ptr<Connector> output);
		void AddVariable(std::shared_ptr<Connector> variable);
	};
}