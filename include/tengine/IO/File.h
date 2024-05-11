#pragma once

#include "../TEngine.h"

namespace TEngine::IO
{
	class File
	{
	public:
		static std::string readAllText(const std::string& filePath);
		static std::vector<uint8_t> readAllBytes(const std::string& filePath);
		static std::vector<std::string> readAllLines(const std::string& filePath);
		static bool writeAllText(const std::string& filePath, const std::string& content);
		static bool writeAllBytes(const std::string& filePath, const uint8_t* content, size_t length);
		static bool writeAllBytes(const std::string& filePath, const std::vector<uint8_t>& content);
		static bool remove(const std::string& filePath);
		static bool copy(const std::string& sourcePath, const std::string& destPath, bool overwrite = true);
		static bool move(const std::string& sourcePath, const std::string& destPath);
		static bool rename(const std::string& oldName, const std::string& newName);
		static bool exists(const std::string& filePath);
	};
}