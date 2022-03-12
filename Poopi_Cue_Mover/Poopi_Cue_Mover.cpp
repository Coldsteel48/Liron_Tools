// Poopi_Cue_Mover.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "../DirList/DirUtil.h"
#include <vector>
#include <string>
#include <cstring>
#include <filesystem>
#include <algorithm>
#include <windows.h>
#include <algorithm>
#include <fstream>


bool IsCueFile(const std::string& filename)
{
	return (filename.find("_Cue") != std::string::npos);
}

std::string GetProperCuePath(const std::string& WavDir)
{
	std::string CueDir = std::string(WavDir);
	FindAndReplaceAll(CueDir, "\\Wav\\", "\\Cue\\");
	std::string FileName = GetFileName(CueDir);
	std::string TempCueFolder = std::string(CueDir);
	FindAndReplaceAll(TempCueFolder, FileName, "");

	if (!IsDirectoryExists(TempCueFolder.c_str()))
	{
		CueDir = "";
	}

	return CueDir;
}


int main(int argc, char* argv[])
{
	//std::string path = "H:\\HeroAlexVP"; 
	std::string path = std::string(argv[0], strlen(argv[0]));
	std::string base_filename = path.substr(path.find_last_of("/\\") + 1);
	std::string inputFolderPath = path.substr(0, path.find_last_of("/\\") + 1);

	std::vector<std::string> CueFilePaths;

	//We have to list files and move them to Cue dir instead of Wav
	for (const auto& entry : std::filesystem::recursive_directory_iterator(inputFolderPath))
	{
		std::string fullPath = entry.path().string();
		if (!IsDirectoryExists(fullPath.c_str())) 
		{
			if (IsCueFile(GetFileName(fullPath)))
			{
				//We have Cue file, we should move it.
				CueFilePaths.push_back(fullPath);
			}
		}
	}

	for (const auto& CueFile : CueFilePaths)
	{
		std::string NewFilePath = GetProperCuePath(CueFile);
		if (NewFilePath.length() > 0)
		{
			std::filesystem::rename(CueFile, NewFilePath);
		}
	}

	return 0;
}

