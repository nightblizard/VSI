#pragma once
#include "Connector.h"

enum class StubType
{
	Function,
	Comperator,
	Event,
	Variable,
	Comment
};

class CodeStub
{
	std::vector<Connector> mInputs;
	std::vector<Connector> mOutputs;
	std::vector<Connector> mVariables;


	const float mPadding = 10;
	float getTotalStringPixelLength();
	float getTotalHeight();

	void drawFunction();
	void drawComperator();
	void drawEvent();
	void drawVariable();
	void drawComment();

	float mVariableLength = 0;
public:
	DrawableString name = "Foobar";
	cinder::Vec2f position;
	cinder::ColorA color = cinder::ColorA::black();
	StubType type = StubType::Function;

	CodeStub();
	CodeStub(const cinder::Vec2f& vec);
	CodeStub(const std::string& name, const cinder::Vec2f& vec);
	~CodeStub() = default;
	CodeStub(const CodeStub&) = default;

	void addInput(const std::string& name);
	void addVariable(const std::string& name);
	void addOutput(const std::string& name);

	void draw();
};