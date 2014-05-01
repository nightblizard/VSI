#include "stdafx.h"
#include "DrawableString.h"
#include "Connector.h"


Connector::Connector(CodeStub& owner, const std::string& name) :
	mOwner(owner),
	mName(name)
{
	mName.color = cinder::Color::black();
}


float Connector::getPixelLength() const
{
	return mName.getPixelLength();
}

void Connector::setPosition(const cinder::Vec2f& position)
{
	mName.position = position;
}

void Connector::draw() const
{
	mName.draw();
}