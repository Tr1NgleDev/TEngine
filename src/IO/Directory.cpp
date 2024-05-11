#include "../../include/tengine/IO/Directory.h"

bool TEngine::IO::Directory::create(const std::string& path)
{
	return std::filesystem::create_directory(path);
}

bool TEngine::IO::Directory::copy(const std::string& sourcePath, const std::string& destPath, bool overwrite)
{
	if (overwrite || !exists(destPath)) 
	{
		try 
		{
			std::filesystem::copy(sourcePath, destPath, std::filesystem::copy_options::recursive);
			return true;
		}
		catch (const std::filesystem::filesystem_error& e) 
		{
			Console::print(CMode(RED, BLINKING), std::format("TEngine::IO::Directory: Error copying directory: {}", e.what()));
		}
	}
	return false;
}

void TEngine::IO::Directory::move(const std::string& sourcePath, const std::string& destPath)
{
	std::filesystem::rename(sourcePath, destPath);
}

void TEngine::IO::Directory::rename(const std::string& oldName, const std::string& newName)
{
	move(oldName, newName);
}

bool TEngine::IO::Directory::exists(const std::string& path)
{
	return std::filesystem::exists(path) && std::filesystem::is_directory(path);
}

bool TEngine::IO::Directory::remove(const std::string& path)
{
	return std::filesystem::remove_all(path) > 0;
}

std::vector<std::string> TEngine::IO::Directory::getDirectories(const std::string& path)
{
	std::vector<std::string> directories;

	for (const auto& entry : std::filesystem::directory_iterator(path)) 
		if (std::filesystem::is_directory(entry.path()))
			directories.push_back(entry.path().string());

	return directories;
}

std::vector<std::string> TEngine::IO::Directory::getFiles(const std::string& path)
{
	std::vector<std::string> files;

	for (const auto& entry : std::filesystem::directory_iterator(path)) 
		if (std::filesystem::is_regular_file(entry.path())) 
			files.push_back(entry.path().string());

	return files;
}
