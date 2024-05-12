#include "../include/tengine/Tween.h"

#include "../include/tengine/Utils.h"
#include "../include/tengine/MainGame.h"
#include "../include/tengine/GameState.h"

using namespace TEngine;

void Tween::addTo(GameState* state)
{
    state->tweens.push_back(this);
}

TweenFloat::TweenFloat(GameState* state, double duration, Easings::EasingFunctions easing, float* obj, float value)
{
    this->duration = duration;
    this->easing = easing;
    this->obj = obj;
    this->startV = *obj;
    this->targetV = value;
    addTo(state);
}
void TweenFloat::update()
{
    *obj = glm::mix(startV, targetV, (float)Easings::ease(time / duration, easing));
}

TweenDouble::TweenDouble(GameState* state, double duration, Easings::EasingFunctions easing, double* obj, double value)
{
    this->duration = duration;
    this->easing = easing;
    this->obj = obj;
    this->startV = *obj;
    this->targetV = value;
    addTo(state);
}
void TweenDouble::update()
{
    *obj = glm::mix(startV, targetV, Easings::ease(time / duration, easing));
}

TweenVec2::TweenVec2(GameState* state, double duration, Easings::EasingFunctions easing, glm::vec2* obj, const glm::vec2& value)
{
    this->duration = duration;
    this->easing = easing;
    this->obj = obj;
    this->startV = *obj;
    this->targetV = value;
    addTo(state);
}
void TweenVec2::update()
{
    *obj = glm::mix(startV, targetV, (float)Easings::ease(time / duration, easing));
}

TweenInt::TweenInt(GameState* state, double duration, Easings::EasingFunctions easing, int* obj, int value)
{
    this->duration = duration;
    this->easing = easing;
    this->obj = obj;
    this->startV = *obj;
    this->targetV = value;
    addTo(state);
}
void TweenInt::update()
{
    *obj = (int)glm::mix((double)startV, (double)targetV, Easings::ease(time / duration, easing));
}

TweenColor::TweenColor(GameState* state, double duration, Easings::EasingFunctions easing, Color* obj, const Color& value)
{
    this->duration = duration;
    this->easing = easing;
    this->obj = obj;
    this->startV = *obj;
    this->targetV = value;
    addTo(state);
}
void TweenColor::update()
{
    obj->r = glm::mix(startV.r, targetV.r, (float)Easings::ease(time / duration, easing));
    obj->g = glm::mix(startV.g, targetV.g, (float)Easings::ease(time / duration, easing));
    obj->b = glm::mix(startV.b, targetV.b, (float)Easings::ease(time / duration, easing));
    obj->a = glm::mix(startV.a, targetV.a, (float)Easings::ease(time / duration, easing));
}

double Easings::ease(double t, EasingFunctions easing)
{
    switch (easing) {
    case EaseInSine:
        return easeInSine(t);
    case EaseOutSine:
        return easeOutSine(t);
    case EaseInOutSine:
        return easeInOutSine(t);
    case EaseInQuad:
        return easeInQuad(t);
    case EaseOutQuad:
        return easeOutQuad(t);
    case EaseInOutQuad:
        return easeInOutQuad(t);
    case EaseInCubic:
        return easeInCubic(t);
    case EaseOutCubic:
        return easeOutCubic(t);
    case EaseInOutCubic:
        return easeInOutCubic(t);
    case EaseInQuart:
        return easeInQuart(t);
    case EaseOutQuart:
        return easeOutQuart(t);
    case EaseInOutQuart:
        return easeInOutQuart(t);
    case EaseInQuint:
        return easeInQuint(t);
    case EaseOutQuint:
        return easeOutQuint(t);
    case EaseInOutQuint:
        return easeInOutQuint(t);
    case EaseInExpo:
        return easeInExpo(t);
    case EaseOutExpo:
        return easeOutExpo(t);
    case EaseInOutExpo:
        return easeInOutExpo(t);
    case EaseInCirc:
        return easeInCirc(t);
    case EaseOutCirc:
        return easeOutCirc(t);
    case EaseInOutCirc:
        return easeInOutCirc(t);
    case EaseInBack:
        return easeInBack(t);
    case EaseOutBack:
        return easeOutBack(t);
    case EaseInOutBack:
        return easeInOutBack(t);
    case EaseInElastic:
        return easeInElastic(t);
    case EaseOutElastic:
        return easeOutElastic(t);
    case EaseInOutElastic:
        return easeInOutElastic(t);
    case EaseInBounce:
        return easeInBounce(t);
    case EaseOutBounce:
        return easeOutBounce(t);
    case EaseInOutBounce:
        return easeInOutBounce(t);
    default: return t; // linear
    }
}

double Easings::easeInSine(double t)
{
    t = glm::clamp(t, 0.0, 1.0);
    return 1 - cos(HALF_PI_D * t);
}

double Easings::easeOutSine(double t)
{
    t = glm::clamp(t, 0.0, 1.0);
    return sin(HALF_PI_D * t);
}

double Easings::easeInOutSine(double t)
{
    t = glm::clamp(t, 0.0, 1.0);
    return -(cos(PI_D * t) - 1) * 0.5;
}

double Easings::easeInQuad(double t)
{
    t = glm::clamp(t, 0.0, 1.0);
    return t * t;
}

double Easings::easeOutQuad(double t)
{
    t = glm::clamp(t, 0.0, 1.0);
    return 1 - (1 - t) * (1 - t);
}

double Easings::easeInOutQuad(double t)
{
    t = glm::clamp(t, 0.0, 1.0);
    return t < 0.5 ? 2 * t * t : 1 - pow(-2 * t + 2, 2)* 0.5;
}

double Easings::easeInCubic(double t)
{
    t = glm::clamp(t, 0.0, 1.0);
    return t * t * t;
}

double Easings::easeOutCubic(double t)
{
    t = glm::clamp(t, 0.0, 1.0);
    return 1 - pow(1 - t, 3);
}

double Easings::easeInOutCubic(double t)
{
    t = glm::clamp(t, 0.0, 1.0);
    return t < 0.5 ? 4 * t * t * t : 1 - pow(-2 * t + 2, 3)* 0.5;
}

double Easings::easeInQuart(double t)
{
    t = glm::clamp(t, 0.0, 1.0);
    return t * t * t * t;
}

double Easings::easeOutQuart(double t)
{
    t = glm::clamp(t, 0.0, 1.0);
    return 1 - pow(1 - t, 4);
}

double Easings::easeInOutQuart(double t)
{
    t = glm::clamp(t, 0.0, 1.0);
    return t < 0.5 ? 8 * t * t * t * t : 1 - pow(-2 * t + 2, 4)* 0.5;
}

double Easings::easeInQuint(double t)
{
    t = glm::clamp(t, 0.0, 1.0);
    return t * t * t * t * t;
}

double Easings::easeOutQuint(double t)
{
    t = glm::clamp(t, 0.0, 1.0);
    return 1 - pow(1 - t, 5);
}

double Easings::easeInOutQuint(double t)
{
    t = glm::clamp(t, 0.0, 1.0);
    return t < 0.5 ? 16 * t * t * t * t * t : 1 - pow(-2 * t + 2, 5)* 0.5;
}

double Easings::easeInExpo(double t)
{
    t = glm::clamp(t, 0.0, 1.0);
    return t == 0 ? 0 : pow(2, 10 * t - 10);
}

double Easings::easeOutExpo(double t)
{
    t = glm::clamp(t, 0.0, 1.0);
    return t == 1 ? 1 : 1 - pow(2, -10 * t);
}

double Easings::easeInOutExpo(double t)
{
    t = glm::clamp(t, 0.0, 1.0);
    return t == 0
        ? 0
        : t == 1
        ? 1
        : t < 0.5 ? pow(2, 20 * t - 10)* 0.5
        : (2 - pow(2, -20 * t + 10))* 0.5;
}

double Easings::easeInCirc(double t)
{
    t = glm::clamp(t, 0.0, 1.0);
    return 1 - sqrt(1 - pow(t, 2));
}

double Easings::easeOutCirc(double t)
{
    t = glm::clamp(t, 0.0, 1.0);
    return sqrt(1 - pow(t - 1, 2));
}

double Easings::easeInOutCirc(double t)
{
    t = glm::clamp(t, 0.0, 1.0);
    return t < 0.5
        ? (1 - sqrt(1 - pow(2 * t, 2)))* 0.5
        : (sqrt(1 - pow(-2 * t + 2, 2)) + 1)* 0.5;
}

double Easings::easeInBack(double t)
{
    const double c1 = 1.70158;
    const double c3 = c1 + 1;

    t = glm::clamp(t, 0.0, 1.0);
    return c3 * t * t * t - c1 * t * t;
}

double Easings::easeOutBack(double t)
{
    const double c1 = 1.70158;
    const double c3 = c1 + 1;

    t = glm::clamp(t, 0.0, 1.0);
    return 1 + c3 * pow(t - 1, 3) + c1 * pow(t - 1, 2);
}

double Easings::easeInOutBack(double t)
{
    const double c1 = 1.70158;
    const double c2 = c1 * 1.525;

    t = glm::clamp(t, 0.0, 1.0);
    return t < 0.5
        ? (pow(2 * t, 2) * ((c2 + 1) * 2 * t - c2)) * 0.5
        : (pow(2 * t - 2, 2) * ((c2 + 1) * (t * 2 - 2) + c2) + 2) * 0.5;
}

double Easings::easeInElastic(double t)
{
    const double c4 = (2 * PI_D) / 3;

    t = glm::clamp(t, 0.0, 1.0);

    return t == 0
        ? 0
        : t == 1
        ? 1
        : -pow(2, 10 * t - 10) * sin((t * 10 - 10.75) * c4);
}

double Easings::easeOutElastic(double t)
{
    const double c4 = (2 * PI_D) / 3;

    t = glm::clamp(t, 0.0, 1.0);
    return t == 0
        ? 0
        : t == 1
        ? 1
        : pow(2, -10 * t) * sin((t * 10 - 0.75) * c4) + 1;
}

double Easings::easeInOutElastic(double t)
{
    const double c5 = (2 * PI_D) / 4.5;

    t = glm::clamp(t, 0.0, 1.0);
    return t == 0
        ? 0
        : t == 1
        ? 1
        : t < 0.5
        ? -(pow(2, 20 * t - 10) * sin((20 * t - 11.125) * c5)) * 0.5
        : (pow(2, -20 * t + 10) * sin((20 * t - 11.125) * c5)) * 0.5 + 1;
}

double Easings::easeInBounce(double t)
{
    return 1 - easeOutBounce(1 - t);
}

double Easings::easeOutBounce(double t)
{
    const double n1 = 7.5625;
    const double d1 = 2.75;

    t = glm::clamp(t, 0.0, 1.0);
    if (t < 1 / d1)
        return n1 * t * t;
    else if (t < 2 / d1)
        return n1 * (t -= 1.5 / d1) * t + 0.75;
    else if (t < 2.5 / d1)
        return n1 * (t -= 2.25 / d1) * t + 0.9375;
    else
        return n1 * (t -= 2.625 / d1) * t + 0.984375;
}

double Easings::easeInOutBounce(double t)
{
    return t < 0.5
        ? (1 - easeOutBounce(1 - 2 * t)) * 0.5
        : (1 + easeOutBounce(2 * t - 1)) * 0.5;
}