#pragma once

#include "BlendMode.h"
#include "../glew/glew.h"
#include "../glm/glm.hpp"

namespace TEngine
{
    class GameState;
	class GameObject
	{
	protected:
        int _zOrder = -INT_MAX;

        glm::vec2 parallaxPos(const glm::vec2& position);
        glm::vec2 parallaxPos();
        friend class GameState;
	private:
        float prevAngle;
        glm::vec2 prevPosition;
        glm::vec2 prevScale;
	public:
        glm::vec2 position{0};
        float angle = 0;
        glm::vec2 scale{ 1,1 };
        bool visible = true;
        bool active = true;
        GameState* state;
        BlendMode blending = BlendMode::Normal;

        float parallaxX = 0.0;
        float parallaxY = 0.0;

        GameObject(const GameObject& other);
        GameObject(GameObject&& other) noexcept;
        GameObject& operator=(const GameObject& other);
        GameObject& operator=(GameObject&& other) noexcept;

        GameObject();
        GameObject(float x, float y);
        virtual ~GameObject();

        float getX() const;
        float getY() const;
        void setX(float x = 0);
        void setY(float y = 0);
        void setPos(float x, float y);
        void setPos(float d = 0);
        void setPos(const glm::vec2& pos);
        glm::vec2 getPos() const;
        void setScale(float s = 1);
        void setScale(float sx, float sy);
        void setScale(const glm::vec2& scale);
        glm::vec2 getScale() const;
        float getScaleF() const;
        void setAngle(float angle = 0);
        float getAngle() const;
        int getZOrder() const;
        void setZOrder(int zOrder);
        void setParallax(float x, float y);
        void setParallax(float xy);

        virtual void destroy();
        virtual void start();
        virtual void update(double deltaTime);
        virtual void render(double deltaTime);
	};
}
