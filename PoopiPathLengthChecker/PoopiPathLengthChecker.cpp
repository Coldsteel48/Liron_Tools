// PoopiPathLengthChecker.cpp : This file contains the 'main' function. Program execution begins and ends there.
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
#include <conio.h>


void ReplaceLastDelimiter(std::string& in_out_path)
{
	size_t pos = in_out_path.find_last_of("/\\");
	if (pos == in_out_path.length() - 1)
	{
		in_out_path.erase(in_out_path.length() - 1);
	}
}


int main(int argc, char* argv[])
{
	std::string path = std::string(argv[0], strlen(argv[0]));
	std::string base_filename = path.substr(path.find_last_of("/\\") + 1);
	std::string inputFolderPath = path.substr(0, path.find_last_of("/\\") + 1);
	std::string outputTxtPath = inputFolderPath + "Poopi_Bad_Path_Length.txt";


	if (argc > 2)
	{
		outputTxtPath = std::string(argv[2], strlen(argv[2]));
	}

	if (argc > 1)
	{
		std::string directoryPath = std::string(argv[1], strlen(argv[1]));

		//Error handling:
		if (!IsDirectoryExists(directoryPath.c_str()))
		{
			std::cout << "Input directory is: " << directoryPath << std::endl;
			std::cout << "Please specify a valid directory path!" << std::endl;
			return -1;
		}

		inputFolderPath = directoryPath;
	}

	ReplaceLastDelimiter(inputFolderPath);

	std::vector<std::string> badFileNames;  badFileNames.reserve(150);

	for (const auto& entry : std::experimental::filesystem::recursive_directory_iterator(inputFolderPath))
	{
		std::string fullPath = entry.path().string();
		std::string filename = GetFileName(fullPath);

		if ("Poopi_File_List.txt" == filename || base_filename == filename) // Remove self:
		{
			continue;
		}

		FindAndReplaceAll(fullPath, inputFolderPath, "");

		if (fullPath.length() > 140)
		{
			badFileNames.push_back(fullPath);
		}
	}

	if (badFileNames.size() <= 0)
	{
		std::cout << "All Paths are good" << std::endl;
		system("pause");

		return 0;
	}

	//Prepare output file:
	std::ofstream out(outputTxtPath);

	for (std::string path : badFileNames)
	{
		std::cout << "[" << path.length() << "] " << path << " [" << path.length() << "] \n";
		out <<"[" << path.length() << "] " << path <<" [" << path.length()<<"] \n";
	}
	out.close();

	std::cout << std::endl << std::endl << std::endl;
	std::cout << "Some paths were too long, please checkout:" << outputTxtPath << std::endl;
	system("pause");

}
