#include "../include/tengine/Gradient.h"

using namespace TEngine;

Gradient::Gradient(float x, float y, int w, int h): Sprite(Texture::get(w, h, Color::White()))
{
	gA = Color::White();
	gB = Color::White();
	gOffset = 0;
	gScale = 1;
	shader = Shader::get(shaderName);
	setPos(x, y);
}

void Gradient::render(double deltaTime)
{
	shader->use();
	shader->setUniform("colorA", gA);
	shader->setUniform("colorB", gB);
	shader->setUniform("gScale", gScale);
	shader->setUniform("gOffset", gOffset);

	Sprite::render(deltaTime);
}
