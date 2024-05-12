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
    *obj = std::lerp(startV, targetV, (float)Easings::ease(time / duration, easing));
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
    *obj = std::lerp(startV, targetV, Easings::ease(time / duration, easing));
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
    obj->x = std::lerp(startV.x, targetV.x, (float)Easings::ease(time / duration, easing));
    obj->y = std::lerp(startV.y, targetV.y, (float)Easings::ease(time / duration, easing));
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
    *obj = (int)std::lerp((double)startV, (double)targetV, Easings::ease(time / duration, easing));
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
    obj->r = std::lerp(startV.r, targetV.r, (float)Easings::ease(time / duration, easing));
    obj->g = std::lerp(startV.g, targetV.g, (float)Easings::ease(time / duration, easing));
    obj->b = std::lerp(startV.b, targetV.b, (float)Easings::ease(time / duration, easing));
    obj->a = std::lerp(startV.a, targetV.a, (float)Easings::ease(time / duration, easing));
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
    return sin(HALF_PI_D * t);
}

double Easings::easeOutSine(double t)
{
    t = glm::clamp(t, 0.0, 1.0);
    return 1 + sin(HALF_PI_D * (--t));
}

double Easings::easeInOutSine(double t)
{
    t = glm::clamp(t, 0.0, 1.0);
    return 0.5 * (1 + sin(PI_D * (t - 0.5)));
}

double Easings::easeInQuad(double t)
{
    t = glm::clamp(t, 0.0, 1.0);
    return t * t;
}

double Easings::easeOutQuad(double t)
{
    t = glm::clamp(t, 0.0, 1.0);
    return t * (2 - t);
}

double Easings::easeInOutQuad(double t)
{
    t = glm::clamp(t, 0.0, 1.0);
    return t < 0.5 ? 2 * t * t : t * (4 - 2 * t) - 1;
}

double Easings::easeInCubic(double t)
{
    t = glm::clamp(t, 0.0, 1.0);
    return t * t * t;
}

double Easings::easeOutCubic(double t)
{
    t = glm::clamp(t, 0.0, 1.0);
    return 1 + (--t) * t * t;
}

double Easings::easeInOutCubic(double t)
{
    t = glm::clamp(t, 0.0, 1.0);
    return t < 0.5 ? 4 * t * t * t : 1 + (--t) * (2 * (--t)) * (2 * t);
}

double Easings::easeInQuart(double t)
{
    t = glm::clamp(t, 0.0, 1.0);
    t *= t;
    return t * t;
}

double Easings::easeOutQuart(double t)
{
    t = glm::clamp(t, 0.0, 1.0);
    t = (--t) * t;
    return 1 - t * t;
}

double Easings::easeInOutQuart(double t)
{
    t = glm::clamp(t, 0.0, 1.0);
    if (t < 0.5) {
        t *= t;
        return 8 * t * t;
    }
    else {
        t = (--t) * t;
        return 1 - 8 * t * t;
    }
}

double Easings::easeInQuint(double t)
{
    t = glm::clamp(t, 0.0, 1.0);
    double t2 = t * t;
    return t * t2 * t2;
}

double Easings::easeOutQuint(double t)
{
    t = glm::clamp(t, 0.0, 1.0);
    double t2 = (--t) * t;
    return 1 + t * t2 * t2;
}

double Easings::easeInOutQuint(double t)
{
    t = glm::clamp(t, 0.0, 1.0);
    double t2;
    if (t < 0.5) {
        t2 = t * t;
        return 16 * t * t2 * t2;
    }
    else {
        t2 = (--t) * t;
        return 1 + 16 * t * t2 * t2;
    }
}

double Easings::easeInExpo(double t)
{
    t = glm::clamp(t, 0.0, 1.0);
    return (pow(2, 8 * t) - 1) / 255;
}

double Easings::easeOutExpo(double t)
{
    t = glm::clamp(t, 0.0, 1.0);
    return 1 - pow(2, -8 * t);
}

double Easings::easeInOutExpo(double t)
{
    t = glm::clamp(t, 0.0, 1.0);
    if (t < 0.5) {
        return (pow(2, 16 * t) - 1) / 510;
    }
    else {
        return 1 - 0.5 * pow(2, -16 * (t - 0.5));
    }
}

double Easings::easeInCirc(double t)
{
    t = glm::clamp(t, 0.0, 1.0);
    return 1 - sqrt(1 - t);
}

double Easings::easeOutCirc(double t)
{
    t = glm::clamp(t, 0.0, 1.0);
    return sqrt(t);
}

double Easings::easeInOutCirc(double t)
{
    t = glm::clamp(t, 0.0, 1.0);
    if (t < 0.5) {
        return (1 - sqrt(1 - 2 * t)) * 0.5;
    }
    else {
        return (1 + sqrt(2 * t - 1)) * 0.5;
    }
}

double Easings::easeInBack(double t)
{
    t = glm::clamp(t, 0.0, 1.0);
    return t * t * (2.70158 * t - 1.70158);
}

double Easings::easeOutBack(double t)
{
    t = glm::clamp(t, 0.0, 1.0);
    return 1 + (--t) * t * (2.70158 * t + 1.70158);
}

double Easings::easeInOutBack(double t)
{
    t = glm::clamp(t, 0.0, 1.0);
    if (t < 0.5) {
        return t * t * (7 * t - 2.5) * 2;
    }
    else {
        return 1 + (--t) * t * 2 * (7 * t + 2.5);
    }
}

double Easings::easeInElastic(double t)
{
    t = glm::clamp(t, 0.0, 1.0);
    double t2 = t * t;
    return t2 * t2 * sin(t * PI_D * 4.5);
}

double Easings::easeOutElastic(double t)
{
    t = glm::clamp(t, 0.0, 1.0);
    double t2 = (t - 1) * (t - 1);
    return 1 - t2 * t2 * cos(t * PI_D * 4.5);
}

double Easings::easeInOutElastic(double t)
{
    t = glm::clamp(t, 0.0, 1.0);
    double t2;
    if (t < 0.45) {
        t2 = t * t;
        return 8 * t2 * t2 * sin(t * PI_D * 9);
    }
    else if (t < 0.55) {
        return 0.5 + 0.75 * sin(t * PI_D * 4);
    }
    else {
        t2 = (t - 1) * (t - 1);
        return 1 - 8 * t2 * t2 * sin(t * PI_D * 9);
    }
}

double Easings::easeInBounce(double t)
{
    t = glm::clamp(t, 0.0, 1.0);
    return pow(2, 6 * (t - 1)) * abs(sin(t * PI_D * 3.5));
}

double Easings::easeOutBounce(double t)
{
    t = glm::clamp(t, 0.0, 1.0);
    return 1 - pow(2, -6 * t) * abs(cos(t * PI_D * 3.5));
}

double Easings::easeInOutBounce(double t)
{
    t = glm::clamp(t, 0.0, 1.0);
    if (t < 0.5) {
        return 8 * pow(2, 8 * (t - 1)) * abs(sin(t * PI_D * 7));
    }
    else {
        return 1 - 8 * pow(2, -8 * t) * abs(sin(t * PI_D * 7));
    }
}