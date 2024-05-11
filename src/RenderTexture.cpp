#include "../include/tengine/RenderTexture.h"
#include "../include/tengine/Shader.h"
#include "../include/tengine/GameState.h"

TEngine::RenderTexture::RenderTexture() = default;

TEngine::RenderTexture::RenderTexture(const RenderTexture& other)
{
	_resScale = other._resScale;
	_disposed = other._disposed;

	shader = other.shader;

	texID = other.texID;
	fbo = other.fbo;

	w = other.w;
	h = other.h;

	useScreenRes = other.useScreenRes;

	state = other.state;

	VAO = other.VAO;
	VBO = other.VBO;

	updated = other.updated;
}

TEngine::RenderTexture::RenderTexture(RenderTexture&& other) noexcept
{
	_resScale = other._resScale;
	_disposed = other._disposed;

	shader = other.shader;

	texID = other.texID;
	fbo = other.fbo;

	w = other.w;
	h = other.h;

	useScreenRes = other.useScreenRes;

	state = other.state;

	VAO = other.VAO;
	VBO = other.VBO;

	updated = other.updated;

	other._resScale = 1.0f;
	other._disposed = false;
	other.shader = nullptr;
	other.texID = 0;
	other.fbo = 0;
	other.w = 0;
	other.h = 0;
	other.useScreenRes = false;
	other.state = nullptr;
	other.VAO = 0;
	other.VBO = 0;
	other.updated.dispose();
}

TEngine::RenderTexture& TEngine::RenderTexture::operator=(const RenderTexture& other)
{
	if (this != &other)
	{
		_resScale = other._resScale;
		_disposed = other._disposed;

		shader = other.shader;

		texID = other.texID;
		fbo = other.fbo;

		w = other.w;
		h = other.h;

		useScreenRes = other.useScreenRes;

		state = other.state;

		VAO = other.VAO;
		VBO = other.VBO;

		updated = other.updated;
	}
	return *this;
}

TEngine::RenderTexture& TEngine::RenderTexture::operator=(RenderTexture&& other) noexcept
{
	if (this != &other)
	{
		_resScale = other._resScale;
		_disposed = other._disposed;

		shader = other.shader;

		texID = other.texID;
		fbo = other.fbo;

		w = other.w;
		h = other.h;

		useScreenRes = other.useScreenRes;

		state = other.state;

		VAO = other.VAO;
		VBO = other.VBO;

		updated = other.updated;

		// Invalidate the other object's member variables to indicate that it has been moved from.
		other._resScale = 1.0f;
		other._disposed = false;
		other.shader = nullptr;
		other.texID = 0;
		other.fbo = 0;
		other.w = 0;
		other.h = 0;
		other.useScreenRes = false;
		other.state = nullptr;
		other.VAO = 0;
		other.VBO = 0;
		other.updated.dispose();
	}
	return *this;
}

TEngine::RenderTexture::RenderTexture(GameState* state, float resScale, const std::string& vertPath, const std::string& fragPath, const std::string& shaderName)
{
	fbo = 0;
	VAO = 0;
	VBO = 0;
	texID = 0;
	this->state = state;
	this->setResScale(resScale);

	useScreenRes = true;

	shader = Shader::load(vertPath, fragPath, shaderName);

	init((int)(state->w * state->targetScale), (int)(state->h * state->targetScale));
}

TEngine::RenderTexture::RenderTexture(GameState* state, float resScale, const std::string& shaderName)
{
	fbo = 0;
	VAO = 0;
	VBO = 0;
	texID = 0;
	this->state = state;
	this->setResScale(resScale);

	useScreenRes = true;

	shader = Shader::get(shaderName);

	init((int)(state->w * state->targetScale), (int)(state->h * state->targetScale));
}

TEngine::RenderTexture::RenderTexture(GameState* state, int w, int h, const std::string& shaderName)
{
	fbo = 0;
	VAO = 0;
	VBO = 0;
	texID = 0;
	this->state = state;
	shader = Shader::get(shaderName);

	init(w, h);
}

TEngine::RenderTexture::RenderTexture(GameState* state, int w, int h, const std::string& vertPath, const std::string& fragPath, const std::string& shaderName)
{
	fbo = 0;
	VAO = 0;
	VBO = 0;
	texID = 0;
	this->state = state;
	shader = Shader::load(vertPath, fragPath, shaderName);

	init(w, h);
}

TEngine::RenderTexture::~RenderTexture()
{
	dispose(true);
}

void TEngine::RenderTexture::dispose(bool changeVal)
{
	if (!(fbo || VAO || VBO || texID)) return;
	Console::print(std::format("\nTEngine::RenderTexture::dispose({}): {};{};{};{};{}:\n", changeVal, _disposed, fbo, VAO, VBO, texID));
	if(!_disposed || !changeVal)
	{
		glDeleteTextures(1, &texID);
		glDeleteFramebuffers(1, &fbo);
		glBindVertexArray(VAO);
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		if (changeVal)
			_disposed = true;
	}
}

float TEngine::RenderTexture::getResScale() const
{
	return _resScale;
}

void TEngine::RenderTexture::setResScale(float resScale)
{
	_resScale = resScale;
	init(w, h);
}

void TEngine::RenderTexture::init(int w, int h)
{
	if (w == 0 || h == 0)
		return;
	dispose(false);
	this->w = w;
	this->h = h;
	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	
	glGenTextures(1, &texID);
	Texture::curTex = texID;
	glBindTexture(GL_TEXTURE_2D, texID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, (int)((float)w * _resScale), (int)((float)h * _resScale), 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	Texture::curTex = 0;
	glBindTexture(GL_TEXTURE_2D, 0);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texID, 0);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_BYTE, GL_FALSE, 4 * sizeof(int8_t), nullptr); // pos
	glEnableVertexAttribArray(0);
	
	glVertexAttribPointer(1, 2, GL_BYTE, GL_FALSE, 4 * sizeof(int8_t), (void*)(2 * sizeof(int8_t))); // uv
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	updated(this);
}

void TEngine::RenderTexture::resized()
{
	Console::printLine("\nTEngine::RenderTexture: ", _disposed, ';', _resScale, ';', useScreenRes);
	
	
	init((int)((float)state->w * state->targetScale), (int)((float)state->h * state->targetScale));
}

void TEngine::RenderTexture::renderBegin(float r, float g, float b, float a)
{
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);

	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT);

	glViewport(0, 0, (int)((float)w * _resScale), (int)((float)h * _resScale));
}

void TEngine::RenderTexture::renderBegin()
{
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);

	glViewport(0, 0, (int)((float)w * _resScale), (int)((float)h * _resScale));
}

void TEngine::RenderTexture::renderEnd(bool displayQuad)
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	if(displayQuad)
	{
		glBindVertexArray(Sprite::curVAO = VAO);
		shader->use();
		
		shader->setUniform("bitmap", 0);
		shader->setUniform("time", (float)MainGame::getInstance()->getTime());
		Texture::curTex = texID;
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texID);
		glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
		glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	}
}

void TEngine::RenderTexture::render(std::function<void()> renderFunction)
{
	renderBegin();

	glViewport(0, 0, (int)(w * _resScale), (int)(h * _resScale));
	renderFunction();

	glViewport((int)state->offsetX, (int)state->offsetY, (int)(state->w * state->targetScale), (int)(state->h * state->targetScale));
	renderEnd();
}
