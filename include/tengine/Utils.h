#pragma once

#include <string>
#include <vector>
#include "../glm/glm.hpp"
#include "Color.h"
#include "Rect.h"

#define CONCAT_(x, y) x##y
#define CONCAT(x, y) CONCAT_(x, y)
#define VECTOR_REMOVE(vec, obj) (vec).erase(std::remove((vec).begin(), (vec).end(), (obj)), (vec).end())
#define LAST(list) (--list.end())
#define VECTOR_CONTAINS(vec, obj) std::find((vec).begin(), (vec).end(), (obj)) != (vec).end()

#define VECTOR_CONTAINS_UNIQUEPTR(vec, obj) (std::find_if((vec).begin(), (vec).end(), \
                          [obj](const std::unique_ptr<decltype(*(vec).begin())::value_type>& uniquePtr) { \
                              return uniquePtr.get() == (obj); \
                          }) != (vec).end())

#define VECTOR_REMOVE_UNIQUEPTR(vec, obj) \
    (vec).erase(std::remove_if((vec).begin(), (vec).end(), \
        [obj](const auto& uniquePtr) { \
            return uniquePtr.get() == (obj); \
        }), (vec).end())



namespace TEngine
{
	class Utils
	{
	public:
		template <typename T, typename U>
		inline static bool is_type_of(U* obj) {
			return dynamic_cast<T*>(obj) != nullptr;
		}
		static bool findGoodPath(std::string& path, const std::vector<std::string>& formats);
		static std::string formatSeconds(double totalSeconds);
		static bool AABB(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2);
		static bool AABB(const Rect& a, const Rect& b);
		static bool AABBI(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2);
		static float deltaRatio(float ratio, double dt, double targetDelta);
		static float deltaRatio(float ratio, double dt);
		static float ilerp(float a, float b, float ratio, float dt, bool clampRatio = true);
		static glm::vec2 ilerp(const glm::vec2& a, const glm::vec2& b, float ratio, float dt, bool clampRatio = true);
		static glm::vec3 ilerp(const glm::vec3& a, const glm::vec3& b, float ratio, float dt, bool clampRatio = true);
		static glm::vec4 ilerp(const glm::vec4& a, const glm::vec4& b, float ratio, float dt, bool clampRatio = true);
		static Color ilerp(const Color& a, const Color& b, float ratio, float dt, bool clampRatio = true);
		static float lerp(float a, float b, float ratio, bool clampRatio = true);
		static glm::vec2 lerp(const glm::vec2& a, const glm::vec2& b, float ratio, bool clampRatio = true);
		static glm::vec3 lerp(const glm::vec3& a, const glm::vec3& b, float ratio, bool clampRatio = true);
		static glm::vec4 lerp(const glm::vec4& a, const glm::vec4& b, float ratio, bool clampRatio = true);
		static Color lerp(const Color& a, const Color& b, float ratio, bool clampRatio = true);
		static bool indexIsInside(int ind, int len);
		static float remap(float v, float inMin, float inMax, float outMin, float outMax);
		static glm::ivec2 indToXY(int ind, int width);
		static int XYToInd(int x, int y, int width);
		static int XYToInd(const glm::ivec2& p, int width);
		static unsigned char* generateBitmap(const Color& color, int width, int height);
		static unsigned char* generateBitmap(const Color& color, const glm::ivec2& size);
		// fuck glm
		static glm::mat4 createScale(float x, float y);
		// fuck glm
		static glm::mat4 createScale(float scale);
		// fuck glm
		static glm::mat4 createTranslation(float x, float y);
		// fuck glm
		static glm::mat4 createRotationZ(float angle);
		// fuck glm
		static glm::mat4 mult(const glm::mat4& left, const glm::mat4& right);
		// fuck glm
		static glm::mat4 createOrthographicOffCenter(float left, float right, float bottom, float top, float zNear, float zFar);
		static void translate(glm::mat4& mat, float x, float y);
		static void scale(glm::mat4& mat, float x, float y);
		static void rotate(glm::mat4& mat, float angle);
		static std::vector<std::string> split(const std::string& str, char delim);
	};
}
