#pragma once

struct DrawableString
{
	std::string string = "";
	cinder::Vec2f position = cinder::Vec2f::zero();
	cinder::ColorA color = cinder::ColorA::white();

	cinder::Font font = cinder::Font("Consolas", 32);

	DrawableString() = default;
	DrawableString(const std::string& str);
	DrawableString(std::string&& str);
	DrawableString(const DrawableString&) = default;
	~DrawableString() = default;

	void draw() const;
	float getPixelLength() const;
};

