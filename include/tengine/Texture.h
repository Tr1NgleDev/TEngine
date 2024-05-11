#pragma once

#include "TEngine.h"

namespace TEngine
{
	class RenderTexture;
	class Texture
	{
	private:
		void genID(const std::string& path, bool antialiased);
		void genID(unsigned char* data, bool antialiased);
		int _renderTexUpdatedActionInd = -1;
		RenderTexture* _usedRenderTexture;
	public:
		inline static std::unordered_map<std::string, Texture*> loadedTextures;
		inline static unsigned int curTex = 0;

		unsigned int id;
		int w;
		int h;
		int channels;

		glm::ivec2 getSize() const
		{
			return { w, h };
		}

		Texture(const Texture& other);
		Texture(Texture&& other) noexcept;
		Texture& operator=(const Texture& other);
		Texture& operator=(Texture&& other) noexcept;

		Texture(RenderTexture* renderTex);

		Texture(const std::string& path = "", bool antialiased = false);
		Texture(int width, int height, const Color& color, bool antialiased = false);
		Texture(int width, int height, bool antialiased = false);
		Texture(bool antialiased = false);
		Texture(const Color& color, bool antialiased = false);

		static Texture* get(const std::string& path = "", bool antialiased = false);
		static Texture* get(int width, int height, const Color& color, bool antialiased = false);
		static Texture* get(int width, int height, bool antialiased = false);
		static Texture* get(bool antialiased = false);
		static Texture* get(const Color& color, bool antialiased = false);
		~Texture();

		void setAntialiasing(bool v) const
		{
			glBindTexture(GL_TEXTURE_2D, id);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, !v ? GL_NEAREST : GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, !v ? GL_NEAREST : GL_LINEAR);
		}

		void use(int unit = 0) const
		{
			if (curTex == id) return;
			glActiveTexture(unit + GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, curTex = id);
		}

		inline static void unbind()
		{
			if (curTex == 0) return;
			glBindTexture(GL_TEXTURE_2D, curTex = 0);
		}
	};
}
