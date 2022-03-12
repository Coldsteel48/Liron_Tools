#pragma once

#include <io.h>			// For access().
#include <sys/types.h>  // For stat().
#include <sys/stat.h>   // For stat().
#include <windows.h>
#include <string.h>


bool DirectoryExists(const char* absolutePath)
{
	if (_access(absolutePath, 0) == 0)
	{
		struct stat status;
		stat(absolutePath, &status);

		return (status.st_mode & S_IFDIR) != 0;
	}
	return false;
}


std::wstring s2ws(const std::string& str)
{
	int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
	std::wstring wstrTo(size_needed, 0);
	MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstrTo[0], size_needed);
	return wstrTo;
}