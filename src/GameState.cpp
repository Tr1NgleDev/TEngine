#include "../include/tengine/GameState.h"

TEngine::GameState::GameState()
{
	w = MainGame::getInstance()->gameWidth;
	h = MainGame::getInstance()->gameHeight;

	resized(MainGame::getInstance()->getWidth(), MainGame::getInstance()->getHeight());

	renderTex = RenderTexture(this);
	auto a = [this](int width, int height) { resized(width, height); };
	resizedActionInd = MainGame::getInstance()->aResize.add(a);
}

void TEngine::GameState::resized(int width, int height)
{
	if (this == nullptr) return;
	prevChangedData = true;
	changedData = true;
	targetScale = fminf((float)width / (float)w, (float)height / (float)h);

	offsetX = roundf(((float)width - ((float)w * targetScale)) / 2.0f);
	offsetY = roundf(((float)height - ((float)h * targetScale)) / 2.0f);

	if (renderTex.state && renderTex.useScreenRes)
		renderTex.resized();
}

void TEngine::GameState::add(GameObject* obj)
{
	if (!objects.empty())
		obj->_zOrder = objects.back()->getZOrder() + 1;
	else
		obj->_zOrder = 0;

	objects.push_back(obj);
	updateOrdering();

	obj->state = this;
	obj->start();
}

void TEngine::GameState::add(GameObject* obj, int zOrder)
{
	obj->_zOrder = zOrder;

	objects.push_back(obj);
	updateOrdering();

	obj->state = this;
	obj->start();
}

void TEngine::GameState::remove(GameObject* obj)
{
	VECTOR_REMOVE(objects, obj);
	updateOrdering();
}

void TEngine::GameState::updateOrdering()
{
	resort = true;
}

void TEngine::GameState::start()
{
	trans = new Sprite(w * 0.5f, h * 0.5f);
	trans->makeGraphic(1, 1);
	trans->color = Color(0.f, 0.f, 0.f, 1.f);
	trans->offset = glm::vec2{ 0.5f };
	trans->state = this;
	trans->setAntialiased(false);
	trans->setZOrder(0);
	trans->start();
	
	resized(MainGame::getInstance()->getWidth(), MainGame::getInstance()->getHeight());
}

void TEngine::GameState::exit()
{
	for (auto& tween : tweens)
		delete tween;
	tweens.clear();
	for (auto& timer : timers)
		delete timer;
	timers.clear();
	MainGame::getInstance()->aResize.remove(resizedActionInd);

	for (auto& obj : std::vector(objects))
	{
		if (!obj) continue;
		remove(obj);
		obj->destroy();
		delete obj;
	}
	objects.clear();
	objects.clear();

	delete trans;

	renderTex.dispose(true);
}

void TEngine::GameState::update(double deltaTime)
{
	if(cam.x != prevCam.x || cam.y != prevCam.y || cam.angle != prevCam.angle || cam.zoom != prevCam.zoom || renderTex.w != prevRTW || renderTex.w != prevRTH)
	{
		changedData = true;
		prevCam.x = cam.x;
		prevCam.y = cam.y;
		prevCam.angle = cam.angle;
		prevCam.zoom = cam.zoom;
		prevRTW = renderTex.w;
		prevRTH = renderTex.h;
	}
	if (transOut)
		return;

	stateTime += deltaTime;

	for (auto it = objects.begin(); it < objects.end();)
	{
		if (*it == nullptr)
		{
			it = objects.erase(it);
			continue;
		}
		GameObject* obj = *it;
		if (obj->active)
			obj->update(deltaTime);
		it++;
	}

	prevChangedData = changedData;

	updateTimers(deltaTime);
	updateTweens(deltaTime);
}

void TEngine::GameState::updateTimers(double deltaTime)
{
	if (timers.empty()) return;

	for (int i = 0; i < timers.size();)
	{
		if (timers[i] == nullptr)
		{
			i = timers.erase(timers.begin() + i) - timers.begin();
		}
		else
		{
			Timer* timer = timers[i];
			timer->time += deltaTime;
			if (timer->time >= timer->duration)
			{
				timer->callback();
				if (timer->ind < timer->times)
				{
					timer->time = 0;
					timer->ind++;
				}
				else
				{
					delete timer;
					timers[i] = nullptr;
				}
			}
			i++;
		}
	}
}

void TEngine::GameState::updateTweens(double deltaTime)
{
	if (tweens.empty()) return;

	for (int i = 0; i < tweens.size();)
	{
		if (tweens[i] == nullptr)
		{
			i = tweens.erase(tweens.begin() + i) - tweens.begin();
		}
		else
		{
			Tween* tween = tweens[i];
			double speed = Tween::globalSpeed * tweenSpeed;
			tween->time = glm::min(tween->time + deltaTime * speed, tween->duration);
			tween->update();
			if (tween->time >= tween->duration)
			{
				tween->time = tween->duration;
				tween->update();
				delete tween;
				tweens[i] = nullptr;
			}
			i++;
		}
	}
}

void TEngine::GameState::render(double deltaTime)
{
	renderTex.renderBegin();
	
	if (resort)
	{
		resort = false;

		std::sort(objects.begin(), objects.end(),
			[](GameObject* const& a, GameObject* const& b) {
				return a->_zOrder < b->_zOrder;
			});
	}

	//glViewport(0, 0, (int)((float)renderTex.w * renderTex.getResScale()), (int)((float)renderTex.h * renderTex.getResScale()));
	for (auto it = objects.begin(); it < objects.end();)
	{
		if (*it == nullptr)
		{
			it = objects.erase(it);
			continue;
		}
		GameObject* obj = *it;
		if (obj->active && obj->visible)
			obj->render(deltaTime);
		it++;
	}
	
	if (trans == nullptr) return;
	if (renderTime <= 1)
		trans->color.a = 1 - Easings::easeOutQuad(renderTime / 0.2f);
	else if (transOut)
	{
		trans->color.a = Easings::easeInQuad((renderTime - transStart) / 0.2f);
	}
	if(renderTime <= 1 || transOut)
	{
		trans->setGraphicSize((int)(w / getZoom() * 2.f), (int)(h / getZoom() * 2.f));
		trans->angle = -cam.angle;
		trans->render(deltaTime);
	}
	renderTime += deltaTime;
}

float TEngine::GameState::getBottom() const
{
	return cam.y + ((float)h + (float)h / getZoom()) * 0.5f;
}

float TEngine::GameState::getLeft() const
{
	return cam.x + ((float)w - (float)w / getZoom()) * 0.5f;
}

float TEngine::GameState::getRight() const
{
	return cam.x + ((float)w + (float)w / getZoom()) * 0.5f;
}

float TEngine::GameState::getTop() const
{
	return cam.y + ((float)h - (float)h / getZoom()) * 0.5f;
}

float TEngine::GameState::getZoom() const
{
	return cam.zoom + 1 > 0.01f ? cam.zoom + 1 : 0.01f;
}

TEngine::GameState::~GameState()
{
	
}
