#include "../include/tengine/Shader.h"

#include <regex>

using namespace TEngine::IO;

TEngine::Shader::Shader(const Shader& other)
{
	_HANDLE = other._HANDLE;
}

TEngine::Shader::Shader(Shader&& other) noexcept
{
	_HANDLE = other._HANDLE;

	other._HANDLE = 0;
}

TEngine::Shader& TEngine::Shader::operator=(const Shader& other)
{
	if (this != &other)
	{
		_HANDLE = other._HANDLE;
	}
	return *this;
}

TEngine::Shader& TEngine::Shader::operator=(Shader&& other) noexcept
{
	if (this != &other)
	{
		_HANDLE = other._HANDLE;
		other._HANDLE = 0;
	}
	return *this;
}

TEngine::Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath)
{
	const std::string vertSource = File::readAllText(vertexPath);
	const std::string fragSource = File::readAllText(fragmentPath);

	if (!vertSource.empty() && !fragSource.empty())
	{
		Console::print(std::format("TEngine::Shader: Compiling Shaders:{} | {}\n", vertexPath, fragmentPath));
		compile(vertSource.c_str(), fragSource.c_str());
	}
}

TEngine::Shader::Shader(const char* vertexSource, const char* fragmentSource)
{
	compile(vertexSource, fragmentSource);
}

const TEngine::Shader* TEngine::Shader::loadFromSource(const char* vertexSource, const char* fragmentSource, const std::string& name)
{
	auto shader = new Shader(vertexSource, fragmentSource);

	if (shaders.contains(name))
		delete shaders[name];

	shaders[name] = shader;

	return shader;
}

std::string TEngine::Shader::colorLogANSI(const char* log)
{
	std::string str(log);

	str = std::regex_replace(str, std::regex("error"), "\x1B[31merror\x1B[0m");
	str = std::regex_replace(str, std::regex("warning"), "\x1B[31mwarning\x1B[0m");

	return str + '\n';
}

void TEngine::Shader::compile(const char* vertexSource, const char* fragmentSource)
{
	int vertShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertShader, 1, &vertexSource, nullptr);

	int fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragShader, 1, &fragmentSource, nullptr);

	Console::print(CMode(GREEN, BRIGHT), "TEngine::Shader: Compiling Vertex Shader\n");
	glCompileShader(vertShader);

	GLint success;
	glGetShaderiv(vertShader, GL_COMPILE_STATUS, &success);

	if(!success)
	{
		GLint infoLogLength;
		glGetShaderiv(vertShader, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar* infoLog = new GLchar[infoLogLength];

		glGetShaderInfoLog(vertShader, infoLogLength, nullptr, infoLog);

		Console::print(CMode(RED, BLINKING), "TEngine::Shader: Shader Compilation Failed!\n\tLog:\n\t");
		Console::print(colorLogANSI(infoLog));

		glDeleteShader(vertShader);

		delete[] infoLog;
		return;
	}

	Console::print(CMode(GREEN, BRIGHT), "TEngine::Shader: Compiling Fragment Shader\n");
	glCompileShader(fragShader);

	glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		GLint infoLogLength;
		glGetShaderiv(fragShader, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar* infoLog = new GLchar[infoLogLength];

		glGetShaderInfoLog(fragShader, infoLogLength, nullptr, infoLog);

		Console::print(CMode(RED, BLINKING), "TEngine::Shader: Shader Compilation Failed!\n\tLog:\n\t");
		Console::print(colorLogANSI(infoLog));

		glDeleteShader(fragShader);
		glDeleteShader(vertShader); // because it has been successfully compiled before

		delete[] infoLog;
		return;
	}

	_HANDLE = glCreateProgram();

	glAttachShader(_HANDLE, vertShader);
	glAttachShader(_HANDLE, fragShader);

	glLinkProgram(_HANDLE);

	glDetachShader(_HANDLE, vertShader);
	glDetachShader(_HANDLE, fragShader);

	glDeleteShader(vertShader);
	glDeleteShader(fragShader);

}

const TEngine::Shader* TEngine::Shader::get(const std::string& name)
{
	if (shaders.contains(name))
		return shaders[name];

	return nullptr;
}

const TEngine::Shader* TEngine::Shader::load(const std::string& vertexPath, const std::string& fragmentPath, const std::string& name)
{
	auto shader = new Shader(vertexPath, fragmentPath);

	if (shaders.contains(name))
		delete shaders[name];

	shaders[name] = shader;

	return shader;
}

void TEngine::Shader::disposeShaders()
{
	for (auto& shader : shaders)
		delete shader.second;
	shaders.clear();
}

TEngine::Shader::~Shader()
{
	glDeleteProgram(_HANDLE);
}
