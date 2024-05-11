#include "../include/tengine/Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../stb_image.h"

using namespace TEngine::IO;

TEngine::Texture* TEngine::Texture::get(const std::string& path, bool antialiased)
{
	if (loadedTextures.contains(path))
		return loadedTextures[path];

	return new Texture(path, antialiased);
}

TEngine::Texture* TEngine::Texture::get(int width, int height, const Color& color, bool antialiased)
{
	std::string path = std::format("g{}x{}:{}x{}x{}x{}", width, height, (uint8_t)(color.r * 255), (uint8_t)(color.g * 255), (uint8_t)(color.b * 255), (uint8_t)(color.a * 255));
	if (loadedTextures.contains(path))
		return loadedTextures[path];

	return new Texture(width, height, color, antialiased);
}

TEngine::Texture* TEngine::Texture::get(int width, int height, bool antialiased)
{
	std::string path = std::format("g{}x{}:255x255x255x255", width, height);
	if (loadedTextures.contains(path))
		return loadedTextures[path];

	return new Texture(width, height, antialiased);
}

TEngine::Texture* TEngine::Texture::get(bool antialiased)
{
	std::string path = "g1x1:255x255x255x255";
	if (loadedTextures.contains(path))
		return loadedTextures[path];

	return new Texture(antialiased);
}

TEngine::Texture* TEngine::Texture::get(const Color& color, bool antialiased)
{
	std::string path = std::format("g1x1:{}x{}x{}x{}", (uint8_t)(color.r * 255), (uint8_t)(color.g * 255), (uint8_t)(color.b * 255), (uint8_t)(color.a * 255));

	if (loadedTextures.contains(path))
		return loadedTextures[path];

	return new Texture(color, antialiased);
}

TEngine::Texture::Texture(const Texture& other)
{
	_renderTexUpdatedActionInd = other._renderTexUpdatedActionInd;
	_usedRenderTexture = other._usedRenderTexture;

	id = other.id;
	w = other.w;
	h = other.h;
	channels = other.channels;
}

TEngine::Texture::Texture(Texture&& other) noexcept
{
	_renderTexUpdatedActionInd = other._renderTexUpdatedActionInd;
	_usedRenderTexture = other._usedRenderTexture;

	id = other.id;
	w = other.w;
	h = other.h;
	channels = other.channels;

	other._renderTexUpdatedActionInd = -1;
	other._usedRenderTexture = nullptr;
	other.id = 0;
	other.w = 0;
	other.h = 0;
	other.channels = 0;
}

TEngine::Texture& TEngine::Texture::operator=(const Texture& other)
{
	if (this != &other)
	{
		_renderTexUpdatedActionInd = other._renderTexUpdatedActionInd;
		_usedRenderTexture = other._usedRenderTexture;

		id = other.id;
		w = other.w;
		h = other.h;
		channels = other.channels;
	}
	return *this;
}

TEngine::Texture& TEngine::Texture::operator=(Texture&& other) noexcept
{
	if (this != &other)
	{
		_renderTexUpdatedActionInd = other._renderTexUpdatedActionInd;
		_usedRenderTexture = other._usedRenderTexture;

		id = other.id;
		w = other.w;
		h = other.h;
		channels = other.channels;

		other._renderTexUpdatedActionInd = -1;
		other._usedRenderTexture = nullptr;
		other.id = 0;
		other.w = 0;
		other.h = 0;
		other.channels = 0;
	}
	return *this;
}

TEngine::Texture::Texture(const Color& color, bool antialiased)
{
	std::string path = std::format("g1x1:{}x{}x{}x{}", (uint8_t)(color.r * 255), (uint8_t)(color.g * 255), (uint8_t)(color.b * 255), (uint8_t)(color.a * 255));
	if (loadedTextures.contains(path))
	{
		id = loadedTextures[path]->id;
		w = loadedTextures[path]->w;
		h = loadedTextures[path]->h;
		channels = loadedTextures[path]->channels;
		return;
	}
	unsigned char* data = Utils::generateBitmap(color, 1, 1);
	w = 1;
	h = 1;
	channels = 4;
	genID(data, antialiased);
	loadedTextures[path] = this;
	stbi_image_free(data);
}

TEngine::Texture::Texture(bool antialiased)
{
	std::string path = "g1x1:255x255x255x255";
	if (loadedTextures.contains(path))
	{
		id = loadedTextures[path]->id;
		w = loadedTextures[path]->w;
		h = loadedTextures[path]->h;
		channels = loadedTextures[path]->channels;
		return;
	}
	unsigned char* data = Utils::generateBitmap(Color::White(), 1, 1);
	w = 1;
	h = 1;
	channels = 4;
	genID(data, antialiased);
	loadedTextures[path] = this;
	stbi_image_free(data);
}

TEngine::Texture::Texture(const std::string& path, bool antialiased)
{
	genID(path, antialiased);
}

TEngine::Texture::Texture(int width, int height, const Color& color, bool antialiased)
{
	std::string path = std::format("g{}x{}:{}x{}x{}x{}", width, height, (uint8_t)(color.r * 255), (uint8_t)(color.g * 255), (uint8_t)(color.b * 255), (uint8_t)(color.a * 255));
	if (loadedTextures.contains(path))
	{
		id = loadedTextures[path]->id;
		w = loadedTextures[path]->w;
		h = loadedTextures[path]->h;
		channels = loadedTextures[path]->channels;
		return;
	}
	unsigned char* data = Utils::generateBitmap(color, width, height);
	w = width;
	h = height;
	channels = 4;
	genID(data, antialiased);
	loadedTextures[path] = this;
	stbi_image_free(data);
}

TEngine::Texture::Texture(int width, int height, bool antialiased)
{
	std::string path = std::format("g{}x{}:255x255x255x255", width, height);
	if (loadedTextures.contains(path))
	{
		id = loadedTextures[path]->id;
		w = loadedTextures[path]->w;
		h = loadedTextures[path]->h;
		channels = loadedTextures[path]->channels;
		return;
	}
	unsigned char* data = Utils::generateBitmap(Color::White(), width, height);
	w = width;
	h = height;
	channels = 4;
	genID(data, antialiased);
	loadedTextures[path] = this;
	stbi_image_free(data);
}

TEngine::Texture::~Texture()
{
	if (_usedRenderTexture && _renderTexUpdatedActionInd != -1)
		_usedRenderTexture->updated.remove(_renderTexUpdatedActionInd);
}

void TEngine::Texture::genID(const std::string& path, bool antialiased)
{
	if (loadedTextures.contains(path))
	{
		id = loadedTextures[path]->id;
		w = loadedTextures[path]->w;
		h = loadedTextures[path]->h;
		channels = loadedTextures[path]->channels;
		return;
	}
	if (!File::exists(path)) return;
	//stbi_set_flip_vertically_on_load(true); // Flip the image vertically to match OpenGL's coordinate system
	unsigned char* data = stbi_load(path.c_str(), &w, &h, &channels, 0);
	genID(data, antialiased);
	loadedTextures[path] = this;
	stbi_image_free(data);
}

void TEngine::Texture::genID(unsigned char* data, bool antialiased)
{
	if (!data) return;

	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);

	GLenum format = GL_RGBA;

	if (channels == 3)
	{
		format = GL_RGB;
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	}

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, format, GL_UNSIGNED_BYTE, data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	setAntialiasing(antialiased);

	unbind();
}

TEngine::Texture::Texture(RenderTexture* renderTex)
{
	_renderTexUpdatedActionInd = renderTex->updated.add([this](const RenderTexture* renderTexU)
		{
			this->id = renderTexU->texID;
			this->w = renderTexU->w;
			this->h = renderTexU->h;
			this->channels = 4;
		});
	this->id = renderTex->texID;
	this->w = renderTex->w;
	this->h = renderTex->h;
	this->channels = 4;
	_usedRenderTexture = renderTex;
}
