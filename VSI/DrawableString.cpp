#include "stdafx.h"
#include "DrawableString.h"


DrawableString::DrawableString(const std::string& str) :
	string(str)
{
}


DrawableString::DrawableString(std::string&& str) :
	string(std::forward<std::string>(str))
{
}

void DrawableString::draw() const
{
	cinder::gl::drawString(string, position, color, font);
}

float DrawableString::getPixelLength() const
{
	return 11 * string.size() + 3.f * string.size();
}