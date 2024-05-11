#pragma once

#include "BasicIncludes.h"
#include "Color.h"

#define PI(type) (glm::pi<type>() * 0.5)
#define HALF_PI(type) (glm::pi<type>())
#define PI_F PI(float)
#define PI_D PI(double)
#define HALF_PI_F HALF_PI(float)
#define HALF_PI_D HALF_PI(double)

namespace TEngine
{
	namespace Easings
	{
		enum EasingFunctions
		{
			Linear,
			EaseInSine,
			EaseOutSine,
			EaseInOutSine,
			EaseInQuad,
			EaseOutQuad,
			EaseInOutQuad,
			EaseInCubic,
			EaseOutCubic,
			EaseInOutCubic,
			EaseInQuart,
			EaseOutQuart,
			EaseInOutQuart,
			EaseInQuint,
			EaseOutQuint,
			EaseInOutQuint,
			EaseInExpo,
			EaseOutExpo,
			EaseInOutExpo,
			EaseInCirc,
			EaseOutCirc,
			EaseInOutCirc,
			EaseInBack,
			EaseOutBack,
			EaseInOutBack,
			EaseInElastic,
			EaseOutElastic,
			EaseInOutElastic,
			EaseInBounce,
			EaseOutBounce,
			EaseInOutBounce
		};
        double easeInSine(double t);
        double easeOutSine(double t);
        double easeInOutSine(double t);
        double easeInQuad(double t);
        double easeOutQuad(double t);
        double easeInOutQuad(double t);
        double easeInCubic(double t);
        double easeOutCubic(double t);
        double easeInOutCubic(double t);
        double easeInQuart(double t);
        double easeOutQuart(double t);
        double easeInOutQuart(double t);
        double easeInQuint(double t);
        double easeOutQuint(double t);
        double easeInOutQuint(double t);
        double easeInExpo(double t);
        double easeOutExpo(double t);
        double easeInOutExpo(double t);
        double easeInCirc(double t);
        double easeOutCirc(double t);
        double easeInOutCirc(double t);
        double easeInBack(double t);
        double easeOutBack(double t);
        double easeInOutBack(double t);
        double easeInElastic(double t);
        double easeOutElastic(double t);
        double easeInOutElastic(double t);
        double easeInBounce(double t);
        double easeOutBounce(double t);
        double easeInOutBounce(double t);

		double ease(double t, EasingFunctions easing = Linear);
	}
	class Tween
	{
	protected:
		double time = 0;
		unsigned char state = 0;

		Easings::EasingFunctions easing = Easings::Linear;
		double duration = 0;

		virtual void update() = NULL;

		friend class TweenManager;
	};
	class TweenFloat : public Tween
	{
		float* obj = nullptr;
		float startV = 0;
		float targetV = 0;
	public:
		TweenFloat(double duration, Easings::EasingFunctions easing, float* obj, float value);
		void update() override;
	};
	class TweenDouble : public Tween
	{
		double* obj = nullptr;
		double startV = 0;
		double targetV = 0;
	public:
		TweenDouble(double duration, Easings::EasingFunctions easing, double* obj, double value);
		void update() override;
	};
	class TweenInt : public Tween
	{
		int* obj = nullptr;
		int startV = 0;
		int targetV = 0;
	public:
		TweenInt(double duration, Easings::EasingFunctions easing, int* obj, int value);
		void update() override;
	};
	class TweenVec2 : public Tween
	{
		glm::vec2* obj = nullptr;
		glm::vec2 startV = glm::vec2(0);
		glm::vec2 targetV = glm::vec2(0);
	public:
		TweenVec2(double duration, Easings::EasingFunctions easing, glm::vec2* obj, const glm::vec2& value);
		void update() override;
	};
	class TweenColor : public Tween
	{
		Color* obj = nullptr;
		Color startV;
		Color targetV;
	public:
		TweenColor(double duration, Easings::EasingFunctions easing, Color* obj, const Color& value);
		void update() override;
	};
	class TweenManager
	{
		inline static std::vector<Tween*> tweensState;
		inline static std::vector<Tween*> tweensOverlayState;
	public:
		inline static double globalSpeed = 1.0;
		inline static double stateSpeed = 1.0;
		inline static double overlayStateSpeed = 1.0;
		static void addTween(Tween* tween);
		static void update(double deltaTime);
		static void stopAll();
		static void stopState();
		static void stopOverlayState();
	};
}
