#pragma once

#include "TEngine.h"

namespace TEngine
{
	struct Color;
	class Shader
	{
	private:
		unsigned int _HANDLE;
		inline static unsigned int _curHANDLE = 0;

		Shader(const std::string& vertexPath, const std::string& fragmentPath);
		Shader(const char* vertexSource, const char* fragmentSource);
		~Shader();
		void compile(const char* vertexSource, const char* fragmentSource);

		static std::string colorLogANSI(const char* log);

	public:
		inline static std::unordered_map<std::string, Shader*> shaders;

		std::string name;

		static void disposeShaders();
		static const Shader* get(const std::string& name);
		static const Shader* load(const std::string& vertexPath, const std::string& fragmentPath, const std::string& name);
		static const Shader* loadFromSource(const char* vertexSource, const char* fragmentSource, const std::string& name);

		void use() const
		{
			if (_curHANDLE == _HANDLE) return;

			glUseProgram(_curHANDLE = _HANDLE);
		}

		void setUniform(const std::string& name, float value) const
		{
			glUniform1f(glGetUniformLocation(_HANDLE, name.c_str()), value);
		}

		void setUniform(const std::string& name, double value) const
		{
			glUniform1d(glGetUniformLocation(_HANDLE, name.c_str()), value);
		}

		void setUniform(const std::string& name, int value) const
		{
			glUniform1i(glGetUniformLocation(_HANDLE, name.c_str()), value);
		}

		void setUniform(const std::string& name, bool value) const
		{
			glUniform1i(glGetUniformLocation(_HANDLE, name.c_str()), value);
		}

		void setUniform(const std::string& name, const glm::vec2& value) const
		{
			glUniform2fv(glGetUniformLocation(_HANDLE, name.c_str()), 1, glm::value_ptr(value));
		}

		void setUniform(const std::string& name, const glm::vec3& value) const
		{
			glUniform3fv(glGetUniformLocation(_HANDLE, name.c_str()), 1, glm::value_ptr(value));
		}

		void setUniform(const std::string& name, const glm::vec4& value) const
		{
			glUniform4fv(glGetUniformLocation(_HANDLE, name.c_str()), 1, glm::value_ptr(value));
		}

		void setUniform(const std::string& name, const glm::ivec2& value) const
		{
			glUniform2iv(glGetUniformLocation(_HANDLE, name.c_str()), 1, glm::value_ptr(value));
		}

		void setUniform(const std::string& name, const glm::ivec3& value) const
		{
			glUniform3iv(glGetUniformLocation(_HANDLE, name.c_str()), 1, glm::value_ptr(value));
		}

		void setUniform(const std::string& name, const glm::ivec4& value) const
		{
			glUniform4iv(glGetUniformLocation(_HANDLE, name.c_str()), 1, glm::value_ptr(value));
		}

		void setUniform(const std::string& name, const Color& value) const
		{
			glUniform4f(glGetUniformLocation(_HANDLE, name.c_str()), value.r, value.g, value.b, value.a);
		}

		void setUniform(const std::string& name, glm::mat4& value, bool transpose) const
		{
			glUniformMatrix4fv(glGetUniformLocation(_HANDLE, name.c_str()), 1, transpose ? GL_TRUE : GL_FALSE, glm::value_ptr(value));
		}

		void setUniform(const std::string& name, glm::mat3& value, bool transpose) const
		{
			glUniformMatrix3fv(glGetUniformLocation(_HANDLE, name.c_str()), 1, transpose ? GL_TRUE : GL_FALSE, glm::value_ptr(value));
		}

		void setUniform(const std::string& name, glm::mat2& value, bool transpose) const
		{
			glUniformMatrix2fv(glGetUniformLocation(_HANDLE, name.c_str()), 1, transpose ? GL_TRUE : GL_FALSE, glm::value_ptr(value));
		}

		unsigned int getHANDLE() const
		{
			return _HANDLE;
		}

		inline static void unbind()
		{
			if (_curHANDLE == 0) return;

			glUseProgram(_curHANDLE = 0);
		}

		Shader(const Shader& other);
		Shader(Shader&& other) noexcept;
		Shader& operator=(const Shader& other);
		Shader& operator=(Shader&& other) noexcept;
	};
}
