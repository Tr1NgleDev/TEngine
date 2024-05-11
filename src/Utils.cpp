#include "../include/tengine/Utils.h"

#include "../include/tengine/MainGame.h"
#include <format>

std::vector<std::string> TEngine::Utils::split(const std::string& str, char delim)
{
	std::vector<std::string> tokens;
	size_t pos = 0;
	size_t len = str.length();
	tokens.reserve(len / 2);  // allocate memory for expected number of tokens

	while (pos < len)
	{
		size_t end = str.find_first_of(delim, pos);
		if (end == std::string::npos)
		{
			tokens.emplace_back(str.substr(pos));
			break;
		}
		tokens.emplace_back(str.substr(pos, end - pos));
		pos = end + 1;
	}

	return tokens;
}

bool TEngine::Utils::AABB(const Rect& a, const Rect& b)
{
	return AABB(a.x, a.y, a.w, a.h, b.x, b.y, b.w, b.h);
}

bool TEngine::Utils::AABB(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2)
{
	return x1 < x2 + w2 && x1 + w1 > x2 && y1 < y2 + h2 && y1 + h1 > y2;
}

bool TEngine::Utils::AABBI(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2)
{
	return x1 < x2 + w2 && x1 + w1 > x2 && y1 < y2 + h2 && y1 + h1 > y2;
}

int TEngine::Utils::XYToInd(const glm::ivec2& p, int width)
{
	return p.x + p.y * width;
}

int TEngine::Utils::XYToInd(int x, int y, int width)
{
	return x + y * width;
}

float TEngine::Utils::deltaRatio(float ratio, double dt)
{
	return deltaRatio(ratio, dt, 1.0 / 100.0);
}

float TEngine::Utils::deltaRatio(float ratio, double dt, double targetDelta)
{
	const double rDelta = dt / (1.0 / (1.0 / targetDelta));
	const double s = 1.0 - ratio;

	return (float)(1.0 - pow(s, rDelta));
}

std::string TEngine::Utils::formatSeconds(double totalSeconds)
{
	int seconds = (int)totalSeconds % 60;
	int minutes = (int)totalSeconds / 60;
	return std::format("{}:{:02}", minutes, seconds);
}

float TEngine::Utils::ilerp(float a, float b, float ratio, float dt, bool clampRatio)
{
	return lerp(a, b, deltaRatio(ratio, dt), clampRatio);
}

glm::vec2 TEngine::Utils::ilerp(const glm::vec2& a, const glm::vec2& b, float ratio, float dt, bool clampRatio)
{
	return lerp(a, b, deltaRatio(ratio, dt), clampRatio);
}

glm::vec3 TEngine::Utils::ilerp(const glm::vec3& a, const glm::vec3& b, float ratio, float dt, bool clampRatio)
{
	return lerp(a, b, deltaRatio(ratio, dt), clampRatio);
}

glm::vec4 TEngine::Utils::ilerp(const glm::vec4& a, const glm::vec4& b, float ratio, float dt, bool clampRatio)
{
	return lerp(a, b, deltaRatio(ratio, dt), clampRatio);
}

TEngine::Color TEngine::Utils::ilerp(const Color& a, const Color& b, float ratio, float dt, bool clampRatio)
{
	return lerp(a, b, deltaRatio(ratio, dt), clampRatio);
}

glm::ivec2 TEngine::Utils::indToXY(int ind, int width)
{
	int x = ind % width;
	int y = (ind - x) / width;
	return { x, y };
}

bool TEngine::Utils::indexIsInside(int ind, int len)
{
	return len > 0 && ind < len && ind >= 0;
}

float TEngine::Utils::lerp(float a, float b, float ratio, bool clampRatio)
{
	if (clampRatio)
		ratio = glm::clamp(ratio, 0.f, 1.f);
	return a + (b - a) * ratio;
}

glm::vec2 TEngine::Utils::lerp(const glm::vec2& a, const glm::vec2& b, float ratio, bool clampRatio)
{
	return { lerp(a.x, b.x, ratio, clampRatio), lerp(a.y, b.y, ratio, clampRatio) };
}

glm::vec3 TEngine::Utils::lerp(const glm::vec3& a, const glm::vec3& b, float ratio, bool clampRatio)
{
	return { lerp(a.x, b.x, ratio, clampRatio), lerp(a.y, b.y, ratio, clampRatio), lerp(a.z, b.z, ratio, clampRatio) };
}

glm::vec4 TEngine::Utils::lerp(const glm::vec4& a, const glm::vec4& b, float ratio, bool clampRatio)
{
	return { lerp(a.x, b.x, ratio, clampRatio), lerp(a.y, b.y, ratio, clampRatio), lerp(a.z, b.z, ratio, clampRatio), lerp(a.w, b.w, ratio, clampRatio) };
}

TEngine::Color TEngine::Utils::lerp(const Color& a, const Color& b, float ratio, bool clampRatio)
{
	return { lerp(a.r, b.r, ratio, clampRatio), lerp(a.g, b.g, ratio, clampRatio), lerp(a.b, b.b, ratio, clampRatio), lerp(a.a, b.a, ratio, clampRatio) };
}

float TEngine::Utils::remap(float v, float inMin, float inMax, float outMin, float outMax)
{
	return (v - inMin) * ((outMax - outMin) / (inMax - inMin)) + outMin;
}

unsigned char* TEngine::Utils::generateBitmap(const Color& color, const glm::ivec2& size)
{
	return generateBitmap(color, size.x, size.y);
}

unsigned char* TEngine::Utils::generateBitmap(const Color& color, int width, int height)
{
	const uint8_t rgba[4] = {
		static_cast<uint8_t>(color.r * 255),
		static_cast<uint8_t>(color.g * 255),
		static_cast<uint8_t>(color.b * 255),
		static_cast<uint8_t>(color.a * 255)
	};

	unsigned char* imageData = (unsigned char*)malloc(width * height * 4);

	for(int i = 0; i < width * height * 4; i += 4)
	{
		imageData[i] = rgba[0];
		imageData[i + 1] = rgba[1];
		imageData[i + 2] = rgba[2];
		imageData[i + 3] = rgba[3];
	}

	return imageData;
}

glm::mat4 TEngine::Utils::createTranslation(float x, float y)
{
	glm::mat4 result = glm::identity<glm::mat4>();
	result[3][0] = x;
	result[3][1] = y;
	result[3][2] = 1;
	return result;
}

glm::mat4 TEngine::Utils::createScale(float x, float y)
{
	glm::mat4 result = glm::identity<glm::mat4>();
	result[0][0] = x;
	result[1][1] = y;
	result[2][2] = 1;
	return result;
}

glm::mat4 TEngine::Utils::createScale(float scale)
{
	return createScale(scale, scale);
}

glm::mat4 TEngine::Utils::createRotationZ(float angle)
{
	float cos = glm::cos(angle);
	float sin = glm::sin(angle);

	glm::mat4 result = glm::identity<glm::mat4>();
	result[0][0] = cos;
	result[0][1] = sin;
	result[1][0] = -sin;
	result[1][1] = cos;

	return result;
}

glm::mat4 TEngine::Utils::mult(const glm::mat4& left, const glm::mat4& right)
{
	glm::mat4 result = glm::mat4(1.0);

	const float leftM11 = left[0][0];
	const float leftM12 = left[0][1];
	const float leftM13 = left[0][2];
	const float leftM14 = left[0][3];
	const float leftM21 = left[1][0];
	const float leftM22 = left[1][1];
	const float leftM23 = left[1][2];
	const float leftM24 = left[1][3];
	const float leftM31 = left[2][0];
	const float leftM32 = left[2][1];
	const float leftM33 = left[2][2];
	const float leftM34 = left[2][3];
	const float leftM41 = left[3][0];
	const float leftM42 = left[3][1];
	const float leftM43 = left[3][2];
	const float leftM44 = left[3][3];
	const float rightM11 = right[0][0];
	const float rightM12 = right[0][1];
	const float rightM13 = right[0][2];
	const float rightM14 = right[0][3];
	const float rightM21 = right[1][0];
	const float rightM22 = right[1][1];
	const float rightM23 = right[1][2];
	const float rightM24 = right[1][3];
	const float rightM31 = right[2][0];
	const float rightM32 = right[2][1];
	const float rightM33 = right[2][2];
	const float rightM34 = right[2][3];
	const float rightM41 = right[3][0];
	const float rightM42 = right[3][1];
	const float rightM43 = right[3][2];
	const float rightM44 = right[3][3];

	result[0][0] = (leftM11 * rightM11) + (leftM12 * rightM21) + (leftM13 * rightM31) + (leftM14 * rightM41);
	result[0][1] = (leftM11 * rightM12) + (leftM12 * rightM22) + (leftM13 * rightM32) + (leftM14 * rightM42);
	result[0][2] = (leftM11 * rightM13) + (leftM12 * rightM23) + (leftM13 * rightM33) + (leftM14 * rightM43);
	result[0][3] = (leftM11 * rightM14) + (leftM12 * rightM24) + (leftM13 * rightM34) + (leftM14 * rightM44);
	result[1][0] = (leftM21 * rightM11) + (leftM22 * rightM21) + (leftM23 * rightM31) + (leftM24 * rightM41);
	result[1][1] = (leftM21 * rightM12) + (leftM22 * rightM22) + (leftM23 * rightM32) + (leftM24 * rightM42);
	result[1][2] = (leftM21 * rightM13) + (leftM22 * rightM23) + (leftM23 * rightM33) + (leftM24 * rightM43);
	result[1][3] = (leftM21 * rightM14) + (leftM22 * rightM24) + (leftM23 * rightM34) + (leftM24 * rightM44);
	result[2][0] = (leftM31 * rightM11) + (leftM32 * rightM21) + (leftM33 * rightM31) + (leftM34 * rightM41);
	result[2][1] = (leftM31 * rightM12) + (leftM32 * rightM22) + (leftM33 * rightM32) + (leftM34 * rightM42);
	result[2][2] = (leftM31 * rightM13) + (leftM32 * rightM23) + (leftM33 * rightM33) + (leftM34 * rightM43);
	result[2][3] = (leftM31 * rightM14) + (leftM32 * rightM24) + (leftM33 * rightM34) + (leftM34 * rightM44);
	result[3][0] = (leftM41 * rightM11) + (leftM42 * rightM21) + (leftM43 * rightM31) + (leftM44 * rightM41);
	result[3][1] = (leftM41 * rightM12) + (leftM42 * rightM22) + (leftM43 * rightM32) + (leftM44 * rightM42);
	result[3][2] = (leftM41 * rightM13) + (leftM42 * rightM23) + (leftM43 * rightM33) + (leftM44 * rightM43);
	result[3][3] = (leftM41 * rightM14) + (leftM42 * rightM24) + (leftM43 * rightM34) + (leftM44 * rightM44);

	return result;
}

glm::mat4 TEngine::Utils::createOrthographicOffCenter(float left, float right, float bottom, float top, float zNear, float zFar)
{
	glm::mat4 result = glm::identity<glm::mat4>();

	float invRL = 1.0f / (right - left);
	float invTB = 1.0f / (top - bottom);
	float invFN = 1.0f / (zFar - zNear);

	result[0][0] = 2 * invRL;
	result[1][1] = 2 * invTB;
	result[2][2] = -2 * invFN;

	result[3][0] = -(right + left) * invRL;
	result[3][1] = -(top + bottom) * invTB;
	result[3][2] = -(zFar + zNear) * invFN;

	return result;
}

void TEngine::Utils::translate(glm::mat4& mat, float x, float y)
{
	mat[3][0] += x;
	mat[3][1] += y;
}

void TEngine::Utils::scale(glm::mat4& mat, float x, float y)
{
	const float leftM11 = mat[0][0];
	const float leftM12 = mat[0][1];
	const float leftM21 = mat[1][0];
	const float leftM22 = mat[1][1];
	const float leftM31 = mat[2][0];
	const float leftM32 = mat[2][1];
	const float leftM41 = mat[3][0];
	const float leftM42 = mat[3][1];
	const float rightM11 = x;
	const float rightM22 = y;

	mat[0][0] = leftM11 * rightM11;
	mat[0][1] = leftM12 * rightM22;
	mat[1][0] = leftM21 * rightM11;
	mat[1][1] = leftM22 * rightM22;
	mat[2][0] = leftM31 * rightM11;
	mat[2][1] = leftM32 * rightM22;
	mat[3][0] = leftM41 * rightM11;
	mat[3][1] = leftM42 * rightM22;
}

void TEngine::Utils::rotate(glm::mat4& mat, float angle)
{
	float cos = glm::cos(angle);
	float sin = glm::sin(angle);

	const float leftM11 = mat[0][0];
	const float leftM12 = mat[0][1];
	const float leftM21 = mat[1][0];
	const float leftM22 = mat[1][1];
	const float leftM31 = mat[2][0];
	const float leftM32 = mat[2][1];
	const float leftM41 = mat[3][0];
	const float leftM42 = mat[3][1];
	const float rightM11 = cos;
	const float rightM12 = sin;
	const float rightM21 = -sin;
	const float rightM22 = cos;

	mat[0][0] = (leftM11 * rightM11) + (leftM12 * rightM21);
	mat[0][1] = (leftM11 * rightM12) + (leftM12 * rightM22);
	mat[1][0] = (leftM21 * rightM11) + (leftM22 * rightM21);
	mat[1][1] = (leftM21 * rightM12) + (leftM22 * rightM22);
	mat[2][0] = (leftM31 * rightM11) + (leftM32 * rightM21);
	mat[2][1] = (leftM31 * rightM12) + (leftM32 * rightM22);
	mat[3][0] = (leftM41 * rightM11) + (leftM42 * rightM21);
	mat[3][1] = (leftM41 * rightM12) + (leftM42 * rightM22);
}

bool TEngine::Utils::findGoodPath(std::string& path, const std::vector<std::string>& formats)
{
	std::string initialPath = path;
	for(auto& format : formats)
		if(IO::File::exists(path = std::format("{}.{}", initialPath, format)))
			return true;
	return false;
}
