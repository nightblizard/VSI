#include "Function.h"
#include "Connector.h"

#include "../stdafx.h"

namespace Widgets
{
	void Function::Draw() const
	{
		static cinder::Font font = cinder::Font("Consolas", 32);

		/*		Background		*/
		static auto innerRect = cinder::Rectf{ -2.f, -2.f, 2.f, 2.f };
		cinder::gl::color(cinder::Color::black());
		cinder::gl::drawSolidRect(mBounds);
		cinder::gl::color(mColor);
		cinder::gl::drawSolidRect(mBounds - innerRect);
		

		/*		Title			*/
		cinder::gl::enableAlphaBlending();

		cinder::gl::color(cinder::Color::black());
		auto titleRect = cinder::Rectf{ mBounds.x1, mBounds.y1, mBounds.x2, mBounds.y1 + 35 };
		cinder::gl::drawSolidRect(titleRect);
		cinder::gl::color(mColor);
		cinder::gl::drawSolidRect(titleRect - innerRect);

		cinder::gl::drawStringCentered(mName, 
									   cinder::Vec2f
										{
											(titleRect.x1 + titleRect.x2) / 2,
											titleRect.y1 + 5
										},
										cinder::Color::black(),
										font
										);


		/*		Connectors		*/
		cinder::gl::color(cinder::Color::black());

		for (auto& input : mInputs)
		{
			input->Draw();

			auto x = static_cast<int>(input->GetBounds().x2);
			auto y = static_cast<int>(input->GetBounds().y1) + 2;

			cinder::gl::drawString(input->GetName(), cinder::Vec2i{ x, y }, cinder::Color::black(), font);
		}

		for (auto& output : mOutputs)
		{
			output->Draw();

			auto x = static_cast<int>(output->GetBounds().x2) - 30;
			auto y = static_cast<int>(output->GetBounds().y1) + 2;

			cinder::gl::drawStringRight(output->GetName(), cinder::Vec2i{ x, y }, cinder::Color::black(), font);
		}

		for (auto& variable : mVariables)
			variable->Draw();

		cinder::gl::disableAlphaBlending();
	}


	void Function::AddInput(std::shared_ptr<Connector> input)
	{
		if (mInputs.size() > 0)
		{
			input->SetParent(mInputs[mInputs.size() - 1]);
			input->SetRelativePoint(RelativePoint::BottomLeft);
			input->SetPosition({ 0, 60 });
		} else {
			input->SetParent(shared_from_this());
			input->SetRelativePoint(RelativePoint::TopLeft);
			input->SetPosition({ 0, 60 });
		}

		input->SetSize({30, 30});

		mInputs.push_back(input);
	}


	void Function::AddOutput(std::shared_ptr<Connector> output)
	{
		if (mOutputs.size() > 0)
		{
			output->SetParent(mOutputs[mOutputs.size() - 1]);
			output->SetRelativePoint(RelativePoint::BottomLeft);
			output->SetPosition({ 0, 60 });
		} else {
			output->SetParent(shared_from_this());
			output->SetRelativePoint(RelativePoint::TopRight);
			output->SetPosition({ -30, 60 });
		}

		output->SetSize({ 30, 30 });

		mOutputs.push_back(output);
	}


	void Function::AddVariable(std::shared_ptr<Connector> variable)
	{
	}


	void Function::OnMouseUp(cinder::app::MouseEvent& event)
	{
		auto pos = event.getPos();

		if (mBounds.contains(pos))
			event.setHandled();
	}


	void Function::OnMouseDown(cinder::app::MouseEvent& event)
	{
		auto pos = event.getPos();

		if (mBounds.contains(pos))
			event.setHandled();
	}


	void Function::OnMouseMove(cinder::app::MouseEvent& event)
	{
	}


	void Function::OnMouseDrag(cinder::app::MouseEvent& event)
	{
	}
}