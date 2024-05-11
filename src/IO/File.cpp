#include "../../include/tengine/IO/File.h"

std::string TEngine::IO::File::readAllText(const std::string& filePath)
{
	std::ifstream file(filePath);
	if (file.is_open()) 
	{
		std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
		file.close();
		return content;
	}
	return "";
}

std::vector<std::string> TEngine::IO::File::readAllLines(const std::string& filePath)
{
	std::ifstream file(filePath);
	if (!file.is_open())
		return {};

	std::vector<std::string> lines;
	std::string line;
	while (std::getline(file, line))
		lines.push_back(line);

	file.close();
	return lines;
}

std::vector<uint8_t> TEngine::IO::File::readAllBytes(const std::string& filePath)
{
	std::ifstream file(filePath, std::ios::binary | std::ios::ate);
	if (file.is_open()) 
	{
		size_t length = file.tellg();
		file.seekg(0, std::ios::beg);

		std::vector<uint8_t> buffer(length);
		file.read(reinterpret_cast<char*>(buffer.data()), length);
		file.close();

		return buffer;
	}
	return {};
}

bool TEngine::IO::File::writeAllText(const std::string& filePath, const std::string& content)
{
	std::ofstream file(filePath);
	if (file.is_open()) 
	{
		file << content;
		file.close();
		return true;
	}
	return false;
}

bool TEngine::IO::File::writeAllBytes(const std::string& filePath, const uint8_t* content, size_t length)
{
	std::ofstream file(filePath, std::ios::binary);
	if (file.is_open()) 
	{
		file.write(reinterpret_cast<const char*>(content), length);
		file.close();
		return true;
	}
	return false;
}

bool TEngine::IO::File::writeAllBytes(const std::string& filePath, const std::vector<uint8_t>& content)
{
	std::ofstream file(filePath, std::ios::binary);
	if (file.is_open())
	{
		file.write(reinterpret_cast<const char*>(content.data()), content.size());
		file.close();
		return true;
	}
	return false;
}

bool TEngine::IO::File::copy(const std::string& sourcePath, const std::string& destPath, bool overwrite)
{
	if (overwrite || !exists(destPath))
	{
		std::ifstream source(sourcePath, std::ios::binary);
		std::ofstream destination(destPath, std::ios::binary);

		if (source.is_open() && destination.is_open()) 
		{
			destination << source.rdbuf();
			source.close();
			destination.close();
			return true;
		}
	}
	return false;
}

bool TEngine::IO::File::move(const std::string& sourcePath, const std::string& destPath)
{
	return std::rename(sourcePath.c_str(), destPath.c_str()) == 0;
}

bool TEngine::IO::File::remove(const std::string& filePath)
{
	return std::remove(filePath.c_str()) == 0;
}

bool TEngine::IO::File::rename(const std::string& oldName, const std::string& newName)
{
	return move(oldName, newName);
}

bool TEngine::IO::File::exists(const std::string& filePath)
{
	std::ifstream file(filePath);
	return file.good();
}
