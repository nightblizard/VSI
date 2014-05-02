#include "stdafx.h"
#include "DrawableString.h"
#include "CodeStub.h"

CodeStub::CodeStub(const std::string& name, const cinder::Vec2f& vec) :
	position(vec),
	name(name)
{
}

CodeStub::CodeStub(const cinder::Vec2f& vec) :
	position(vec)
{
}

CodeStub::CodeStub()
{
}

float CodeStub::getTotalStringPixelLength()
{
	float lenInputs = 0;
	for (auto& stub : mInputs)
		lenInputs = std::max(stub.getPixelLength(), lenInputs);

	float lenVariables = 0;
	for (auto& stub : mVariables)
		lenVariables += stub.getPixelLength() + 2 * mPadding;
	mVariableLength = lenVariables;

	float lenOutputs = 0;
	for (auto& stub : mOutputs)
		lenOutputs = std::max(stub.getPixelLength(), lenOutputs);

	auto lenTotal = lenInputs + lenOutputs + mPadding * 2;
	float lenName = name.getPixelLength();

	return std::max(lenVariables + 6 * mPadding, std::max(lenTotal, lenName) + mPadding * 4);
}

float CodeStub::getTotalHeight()
{
	return std::max(mInputs.size(), mOutputs.size())
		* 35.f  //Spaces between the connectors and its text
		+ 20.f //additional spaceing at the bottom
		+ (mVariables.size() > 0.f ? 35.f : 0); //Extra space for variables
}

void CodeStub::drawFunction()
{
	using namespace cinder;
	auto sizex = getTotalStringPixelLength();
	Vec2f size(sizex, sizex);
	size += position;

	/* Title Background */
	glColor4f(color);
	gl::drawSolidRect(Rectf(position + Vec2f(-2, -2), Vec2f(size.x, position.y + 32) + Vec2f(2, 2)));
	glColor4f(.8f, .8f, .4f, 1.f);
	gl::drawSolidRect(Rectf(position, Vec2f(size.x, position.y + 32)));

	/* COntent Background */
	auto actualPosition = Vec2f(position.x, position.y + 37);
	glColor4f(color);
	gl::drawSolidRect(Rectf(actualPosition + Vec2f(-2, -2), Vec2f(size.x, actualPosition.y + getTotalHeight()) + Vec2f(2, 2)));
	glColor4f(.8f, .8f, .4f, 1.f);
	gl::drawSolidRect(Rectf(actualPosition, Vec2f(size.x, actualPosition.y + getTotalHeight())));

	/* Title */
	name.color = Color::black();
	auto x = (position.x + sizex / 2) - (name.getPixelLength() / 2);
	name.position = Vec2f(x, position.y + 4);
	name.draw();

	/* Inputs */
	auto inputPosition = actualPosition;
	inputPosition.y += 16;
	glColor4f(0.f, 0.f, 0.f, 1.f);
	for (auto& stub : mInputs)
	{
		gl::drawSolidRect(Rectf(inputPosition + Vec2f(0, 6), inputPosition + Vec2f(-16, 22)));
		stub.setPosition(inputPosition);
		stub.draw();
		inputPosition.y += 35;
	}

	/* Variables */
	Vec2f variablePosition(actualPosition.x + 2 * mPadding, actualPosition.y + getTotalHeight());
	glColor4f(0.f, 0.f, 0.f, 1.f);
	for (auto& stub : mVariables)
	{
		//center the variables when their total namelength is smaller than the total width of the stub
		if ((mVariableLength + 6 * mPadding) < sizex)
		{
			auto padding = (sizex - (mVariableLength)) / (mVariables.size() + 1);

			variablePosition += Vec2f(padding, -35);
			stub.setPosition(variablePosition);
			stub.draw();
			variablePosition += Vec2f(stub.getPixelLength() / 2.f, 35);
			gl::drawSolidRect(Rectf(variablePosition, variablePosition + Vec2f(16, 16)));
			variablePosition.x += stub.getPixelLength() / 2.f;
		}
		else
		{
			variablePosition += Vec2f(mPadding * 2, -35);
			stub.setPosition(variablePosition);
			stub.draw();
			variablePosition += Vec2f(stub.getPixelLength() / 2.f, 35);
			gl::drawSolidRect(Rectf(variablePosition, variablePosition + Vec2f(16, 16)));
			variablePosition.x += stub.getPixelLength() / 2;
		}
	}


	/* Outputs */
	auto outputPosition = actualPosition;
	outputPosition.y += 16;
	glColor4f(0.f, 0.f, 0.f, 1.f);
	for (auto& stub : mOutputs)
	{
		outputPosition.x = size.x;
		gl::drawSolidRect(Rectf(outputPosition + Vec2f(0, 6), outputPosition + Vec2f(16, 22)));
		outputPosition.x = size.x - stub.getPixelLength() - 5;
		stub.setPosition(outputPosition);
		stub.draw();
		outputPosition.y += 35;
	}
}

void CodeStub::drawComperator()
{
}

void CodeStub::drawEvent()
{
}

void CodeStub::drawVariable()
{
}

void CodeStub::drawComment()
{
}

void CodeStub::addInput(const std::string& name)
{
	mInputs.push_back({ *this, name });
}

void CodeStub::addVariable(const std::string& name)
{
	mVariables.push_back({ *this, name });
}

void CodeStub::addOutput(const std::string& name)
{
	mOutputs.push_back({ *this, name });
}

void CodeStub::draw()
{
	switch(type)
	{
	case StubType::Function: drawFunction(); break;
	case StubType::Comperator: drawComperator(); break;
	case StubType::Event: drawEvent(); break;
	case StubType::Variable: drawVariable(); break;
	case StubType::Comment: drawComment(); break;
	}
}