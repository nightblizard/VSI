#pragma once

class CodeStub;

class Connector
{
	CodeStub& mOwner;
	Connector* mConnectedWith = nullptr;

	DrawableString mName;

public:
	Connector(CodeStub& owner, const std::string& name);
	~Connector() = default;
	Connector(const Connector&) = default;

	float getPixelLength() const;
	void setPosition(const cinder::Vec2f& position);
	void draw() const;
};

