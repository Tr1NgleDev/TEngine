#include "../include/tengine/Color.h"

#include <format>

TEngine::Color::Color(const TEngine::Color& other)
{
	r = other.r;
	g = other.g;
	b = other.b;
	a = other.a;
}


TEngine::Color::Color(Color&& other) noexcept
{
	r = other.r;
	g = other.g;
	b = other.b;
	a = other.a;

	other.r = 0.0f;
	other.g = 0.0f;
	other.b = 0.0f;
	other.a = 0.0f;
}

TEngine::Color& TEngine::Color::operator=(const Color& other)
{
	if (this != &other)
	{
		r = other.r;
		g = other.g;
		b = other.b;
		a = other.a;
	}
	return *this;
}

TEngine::Color& TEngine::Color::operator=(Color&& other) noexcept
{
	if (this != &other)
	{
		r = other.r;
		g = other.g;
		b = other.b;
		a = other.a;

		other.r = 0.0f;
		other.g = 0.0f;
		other.b = 0.0f;
		other.a = 0.0f;
	}
	return *this;
}

TEngine::Color::Color()
{
	r = 0;
	g = 0;
	b = 0;
	a = 0;
}

TEngine::Color::Color(const glm::vec2& rg, const glm::vec2& ba)
{
	r = rg.x;
	g = rg.y;
	b = ba.x;
	a = ba.y;
}

TEngine::Color::Color(const glm::vec2& rg, float b, float a)
{
	this->r = rg.x;
	this->g = rg.y;
	this->b = b;
	this->a = a;
}

TEngine::Color::Color(const glm::vec3& rgb, float a)
{
	this->r = rgb.x;
	this->g = rgb.y;
	this->b = rgb.z;
	this->a = a;
}

TEngine::Color::Color(const glm::vec4& rgba)
{
	r = rgba.x;
	g = rgba.y;
	b = rgba.z;
	a = rgba.w;
}

TEngine::Color::Color(float r, const glm::vec2& gb, float a)
{
	this->r = r;
	this->g = gb.x;
	this->b = gb.y;
	this->a = a;
}

TEngine::Color::Color(float r, const glm::vec3& gba)
{
	this->r = r;
	this->g = gba.x;
	this->b = gba.y;
	this->a = gba.z;
}

TEngine::Color::Color(float r, float g, const glm::vec2& ba)
{
	this->r = r;
	this->g = g;
	this->b = ba.x;
	this->a = ba.y;
}

TEngine::Color::Color(float r, float g, float b, float a)
{
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}

TEngine::Color::Color(int r, int g, int b, int a)
{
	this->r = (float)r / 255.f;
	this->g = (float)g / 255.f;
	this->b = (float)b / 255.f;
	this->a = (float)a / 255.f;
}

bool TEngine::Color::equals(const Color& other) const
{
	return r == other.r && g == other.g && b == other.b && a == other.a;
}

TEngine::Color TEngine::Color::fromSrgb(const Color& srgb)
{
	float r = ((!(srgb.r <= 0.04045f)) ? ((float)pow((srgb.r + 0.055f) / 1.055f, 2.4000000953674316)) : (srgb.r / 12.92f));
	float g = ((!(srgb.g <= 0.04045f)) ? ((float)pow((srgb.g + 0.055f) / 1.055f, 2.4000000953674316)) : (srgb.g / 12.92f));
	float b = ((!(srgb.b <= 0.04045f)) ? ((float)pow((srgb.b + 0.055f) / 1.055f, 2.4000000953674316)) : (srgb.b / 12.92f));
	return { r, g, b, srgb.a };
}

std::size_t TEngine::Color::hash() const
{
	return toARGB();
}

bool TEngine::Color::operator==(const Color& other) const
{
	return this->equals(other);
}

glm::vec3 TEngine::Color::rgb()
{
	return { r,g,b };
}

glm::vec4 TEngine::Color::rgba()
{
	return { r,g,b,a };
}

int TEngine::Color::toARGB() const
{
	return (int)(((unsigned int)(a * 255) << 24) | ((unsigned int)(r * 255) << 16) | ((unsigned int)(g * 255) << 8) | (unsigned int)(b * 255));
}

TEngine::Color TEngine::Color::toSrgb(const Color& rgb)
{
	float r = ((!((double)rgb.r <= 0.0031308f)) ? (1.055f * (float)pow(rgb.r, 0.4166666567325592) - 0.055f) : (12.92f * rgb.r));
	float g = ((!((double)rgb.g <= 0.0031308f)) ? (1.055f * (float)pow(rgb.g, 0.4166666567325592) - 0.055f) : (12.92f * rgb.g));
	float b = ((!((double)rgb.b <= 0.0031308f)) ? (1.055f * (float)pow(rgb.b, 0.4166666567325592) - 0.055f) : (12.92f * rgb.b));
	return { r, g, b, rgb.a };
}

std::string TEngine::Color::to_string() const
{
	return std::format("{{ (R,G,B,A):floats -> {{ {},{},{},{} }} | (R,G,B,A):bytes -> {{ {},{},{},{} }} }}", r, g, b, a, (int)(r * 255), (int)(g * 255), (int)(b * 255), (int)(a * 255));
}

std::string TEngine::Color::Simple::to_string() const
{
	if(bytes)
		return std::format("{{ {},{},{},{} }}", (int)(color->r * 255), (int)(color->g * 255), (int)(color->b * 255), (int)(color->a * 255));
	return std::format("{{ {},{},{},{} }}", color->r, color->g, color->b, color->a);
}

TEngine::Color::Simple TEngine::Color::to_simple(bool bytes) const
{
	return { this, bytes };
}

TEngine::Color TEngine::Color::operator*(const Color& other) const
{
	Color result;
	result.r = this->r * other.r;
	result.g = this->g * other.g;
	result.b = this->b * other.b;
	result.a = this->a * other.a;
	return result;
}

TEngine::Color TEngine::Color::operator*(float v) const
{
	Color result;
	result.r = this->r * v;
	result.g = this->g * v;
	result.b = this->b * v;
	result.a = this->a * v;
	return result;
}
