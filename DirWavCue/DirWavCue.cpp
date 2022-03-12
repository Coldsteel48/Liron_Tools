// DirWavCue.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "../DirList/DirUtil.h"
#include <string>
#include <cstring>
#include <filesystem>
#include <algorithm>

void ListDirectories(std::string rootPath, std::vector<std::string>& out_directories);
void WavAndCueVoodoo(const std::vector<std::string>& directories);
bool IsWavFile(const std::string& path);
void MoveFilesToDir(const std::vector<std::string>& files, const std::string& directory);

static const std::string WAV = "\\Wav";
static const std::string CUE = "\\Cue";

int main(int argc, char* argv[])
{
	std::string path = std::string(argv[0], strlen(argv[0]));
	std::string base_filename = path.substr(path.find_last_of("/\\") + 1);

	std::string inputFolderPath = path.substr(0, path.find_last_of("/\\") + 1);

	if (argc > 1)
	{
		std::string directoryPath = std::string(argv[1], strlen(argv[1]));

		//Error handling:
		if (!DirectoryExists(directoryPath.c_str()))
		{
			std::cout << "Input directory is: " << directoryPath << std::endl;
			std::cout << "Please specify a valid directory path!" << std::endl;
			return -1;
		}

		inputFolderPath = directoryPath;
	}

	std::vector<std::string> sub_directories;
	sub_directories.reserve(100);

	ListDirectories(inputFolderPath, sub_directories);
	WavAndCueVoodoo(sub_directories);

	std::cout << '\a';
	Sleep(1000);

	return 0;
}

void ListDirectories(std::string rootPath, std::vector<std::string>& out_directories)
{
	//Get all files in directory and its sub directory:
	for (const auto & entry : std::experimental::filesystem::recursive_directory_iterator(rootPath))
	{
		if (DirectoryExists(entry.path().string().c_str()))
		{
			//We have a directory;
			out_directories.push_back(entry.path().string());
		}
	}
}

void WavAndCueVoodoo(const std::vector<std::string>& directories)
{
	//For each directory:

	for (auto & dir : directories)
	{
		std::vector<std::string> this_dir_wavs;
		this_dir_wavs.reserve(1000);

		//Non recursive because we want to voodoo
		for (const auto & entry : std::experimental::filesystem::directory_iterator(dir))
		{
			if (!DirectoryExists(entry.path().string().c_str())) //No directory 
			{
				if (IsWavFile(entry.path().string()))
				{
					this_dir_wavs.push_back(entry.path().string());
				}

			}
		}

		if (this_dir_wavs.size() > 0)
		{
			//Create Wav and Cue subdirectoriesP:
			std::string wav_directory = dir + WAV;
			std::string cue_directory = dir + CUE;
			std::experimental::filesystem::create_directories(wav_directory);
			std::experimental::filesystem::create_directories(cue_directory);

			MoveFilesToDir(this_dir_wavs, wav_directory);
		}
	}
}

void MoveFilesToDir(const std::vector<std::string>& files, const std::string& directory)
{
	for (const std::string& file : files)
	{
		std::string newFileName = directory + file.substr(file.find_last_of("/\\")) ;
		std::experimental::filesystem::rename(file, newFileName);
	}
}

//Case insensitive compare:
bool IsEqual(const std::string& a, const std::string& b)
{
	return std::equal(a.begin(), a.end(),
		b.begin(), b.end(),
		[](char a, char b)
	{
		return tolower(a) == tolower(b);
	});
}

bool IsWavFile(const std::string& path)
{
	return IsEqual(path.substr(path.find_last_of(".") + 1), std::string("wav"));
}

