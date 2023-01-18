// DirList.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <windows.h>
#include <string.h>
#include <filesystem>
#include <fstream>
#include "DirUtil.h"
#include "strnatcmp.hpp"
#include <algorithm>
#include "StrDict.h"
#include <map>
#include <conio.h>

void FilterStringToUE(std::string& in_out_string);
void GuessRestoreFilteredString(std::string& in_out_string);
void ReplaceLastDelimiter(std::string & in_out_path);

int main(int argc, char* argv[])
{
	std::string path = std::string(argv[0], strlen(argv[0]));
	std::string base_filename = path.substr(path.find_last_of("/\\") + 1);

	std::string inputFolderPath = path.substr(0, path.find_last_of("/\\") + 1);
	std::string outputTxtPath = inputFolderPath + "Poopi_File_List.txt";

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

	//Prepare output file:
	std::ofstream out(outputTxtPath);
	
	ReplaceLastDelimiter(inputFolderPath);

	std::vector<std::string> file_names;
	file_names.reserve(1000);

	std::map<std::string, std::vector<std::string>> files;

	//Get all files in directory and its sub directory:
	for (const auto & entry : std::filesystem::recursive_directory_iterator(inputFolderPath))
	{
		std::string fullPath = entry.path().string();
		if (IsDirectoryExists(fullPath.c_str()))
		{
			//This is a directory:
			//Insert it to the map.
			files.insert(std::pair<std::string, std::vector<std::string>>(fullPath, std::vector<std::string>()));
		}
		else 
		{
			std::string filename = GetFileName(fullPath); //Looks good.
			if ("Poopi_File_List.txt" == filename || base_filename == filename) //Don't print self :)
			{
				continue;
			}

			FindAndReplaceAll(fullPath, filename, "");
			ReplaceLastDelimiter(fullPath);

			std::string directoryName = fullPath; //Not really :F

			FilterStringToUE(filename);

			if (files.find(directoryName) != files.end())
			{
				//Just emplace
				files[directoryName].push_back(filename);
			}
			else
			{
				files.insert(std::pair<std::string, std::vector<std::string>>(directoryName, std::vector<std::string>()));
				files[directoryName].push_back(filename);
			}
		}
	}

	//Get all keys (Directories)
	std::vector<std::string> fileDirectories;
	fileDirectories.reserve(files.size());

	for (std::map<std::string, std::vector<std::string>>::iterator it = files.begin(); it != files.end(); ++it)
	{
		fileDirectories.push_back(it->first);
	}

	//Sort the keys (directories)
	std::sort(fileDirectories.begin(), fileDirectories.end(), compareNat_path);

	//Make sure parent directory is always on top!
	inputFolderPath = GetFileName(inputFolderPath);
	std::vector<std::string>::iterator itr = std::find(fileDirectories.begin(), fileDirectories.end(), inputFolderPath);
	if (itr != fileDirectories.cend())
	{
		__int64 index = std::distance(fileDirectories.begin(), itr);
		fileDirectories.erase(fileDirectories.begin() + index);
		fileDirectories.insert(fileDirectories.begin(), inputFolderPath);
	}

	//Iterate each directory:
	for (const std::string& direcotryName : fileDirectories)
	{
		std::string output = "";
		
		//Print directory:
		output += "\n\n*** ";
		output += GetFileName(direcotryName);
		output += " ***\n\n";

		std::cout << output;
		out << output;

		std::vector<std::string> fileNames = files[direcotryName];
		std::sort(fileNames.begin(), fileNames.end(), compareNat_path);

		//Sorted files:
		for (std::string fileName : fileNames)
		{
			output = fileName.substr(0, fileName.find_last_of(".")); //Discard extension
			GuessRestoreFilteredString(output); //Try restore eye candies
			output += "\n";

			std::cout << output;
			out << output;
		}
	}

	out.close();

	std::cout << "Please check out the file:" << outputTxtPath << std::endl;
	system("pause");

	return 0;
}

void FilterStringToUE(std::string& in_out_string)
{
	std::replace(in_out_string.begin(), in_out_string.end(), ' ', '_');
	std::replace(in_out_string.begin(), in_out_string.end(), '\'', '\0');
}

void ReplaceLastDelimiter(std::string & in_out_path)
{
	size_t pos = in_out_path.find_last_of("/\\");
	if (pos == in_out_path.length() - 1)
	{
		in_out_path.erase(in_out_path.length() - 1);
	}
}

void GuessRestoreFilteredString(std::string& in_out_string)
{
	std::vector<StrDict> dictionary;
	StrDict::CreateDictionary(dictionary);

	for (const StrDict& entry : dictionary)
	{
		FindAndReplaceAll(in_out_string, entry.origin, entry.target);
	}
}
