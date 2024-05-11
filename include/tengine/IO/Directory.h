#pragma once

#include "../TEngine.h"

namespace TEngine::IO
{
	class Directory
	{
	public:
		static bool exists(const std::string& path);
		static void move(const std::string& sourcePath, const std::string& destPath);
		static bool copy(const std::string& sourcePath, const std::string& destPath, bool overwrite = true);
		static void rename(const std::string& oldName, const std::string& newName);
		static bool remove(const std::string& path);
		static std::vector<std::string> getFiles(const std::string& path);
		static std::vector<std::string> getDirectories(const std::string& path);
		static bool create(const std::string& path);
	};
}
