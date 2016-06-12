//=================================================================================//
//                                                                                 //
//  ArchEngine                                                                     //
//                                                                                 //
//  Copyright (C) 2011-2016 Terry                                                  //
//                                                                                 //
//  This file is a portion of the ArchEngine. It is distributed under the MIT      //
//  License, available in the root of this distribution and at the following URL.  //
//  http://opensource.org/licenses/mit-license.php                                 //
//                                                                                 //
//=================================================================================//

#include <memory>
#include <arch/io/filesystem.h>

#ifdef ARCHENGINE_PLATFORM_WINDOWS

#include <Shlwapi.h>
#include <direct.h>
#include <filesystem>

#pragma comment(lib, "Shlwapi.lib")

namespace arch
{

namespace io
{

bool is_file(const std::string& path)
{
	return PathFileExistsA(path.c_str()) != FALSE && !is_directory(path);
}

bool is_directory(const std::string& path)
{
	return PathIsDirectoryA(path.c_str()) != FALSE;
}

namespace file
{

bool exists(const std::string& path)
{
	return is_file(path);
}

bool move(const std::string& path, const std::string& new_path)
{
	return exists(path) && MoveFileA(path.c_str(), new_path.c_str()) != 0;
}

bool copy(const std::string& path, const std::string& new_path)
{
	return exists(path) && CopyFileA(path.c_str(), new_path.c_str(), TRUE) != FALSE;
}

bool remove(const std::string& path)
{
	return exists(path) && DeleteFileA(path.c_str()) != FALSE;
}

}

namespace directory
{

bool empty(const std::string& path)
{
	return PathIsDirectoryEmptyA(path.c_str()) == TRUE;
}

bool create(const std::string& path)
{
	return _mkdir(path.c_str()) == 0;
}

bool exists(const std::string& path)
{
	return PathFileExistsA(path.c_str()) && is_directory(path);
}

bool move(const std::string& path, const std::string& new_path)
{
	return exists(path) && MoveFileA(path.c_str(), new_path.c_str()) != 0;
}

bool copy(const std::string& path, const std::string& new_path)
{
	//ディレクトリの場合
	if(is_directory(path) && is_directory(new_path))
	{
		//新しいパスにディレクトリを作成
		if(CreateDirectoryA(new_path.c_str(), NULL) == 0)
		{
			return false;
		}

		std::string OldFilePath;
		std::string NewFilePath;
		std::vector<std::string> Files = enumerate_files_and_directories(path);
		bool Result = true;
		for(unsigned int i = 0; i < Files.size() && Result; i++)
		{
			OldFilePath = path + Files[i];
			NewFilePath = new_path + Files[i];
			if (is_directory(OldFilePath))
			{
				Result = copy(OldFilePath, NewFilePath);
			}
			else if (is_file(OldFilePath))
			{
				Result = file::copy(OldFilePath, NewFilePath);
			}
		}

		return Result;
	}

	return false;
}

bool remove(const std::string& path)
{
	return _rmdir(path.c_str()) == 0;
}

std::vector<std::string> enumerate_files(const std::string& path)
{
	return std::move(enumerate_files(path, ""));
}

std::vector<std::string> enumerate_files(const std::string& path, const std::string& ExtensionName)
{
	std::vector<std::string> FindFiles;

	if(!exists(path))
	{
		return std::move(FindFiles);
	}

	std::string FindPath = path;

	FindPath += "*.";
	FindPath += ExtensionName.empty() ? "*" : ExtensionName;

	WIN32_FIND_DATAA FindData;

	HANDLE hFile = FindFirstFileA(FindPath.c_str(), &FindData);
	if(hFile != INVALID_HANDLE_VALUE)
	{
		do
		{
			//検索結果がディレクトリ以外の場合はリストにファイル名を追加
			if((FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0)
			{
				FindFiles.push_back(FindData.cFileName);
			}
		}
		while(FindNextFileA(hFile, &FindData) != FALSE);
	}

	FindClose(hFile);
	return std::move(FindFiles);
}

std::vector<std::string> enumerate_directories(const std::string& path)
{
	std::vector<std::string> FindFiles;

	if(!exists(path))
	{
		return std::move(FindFiles);
	}
	std::string FindPath = path + "*.*";

	WIN32_FIND_DATAA FindData;
	HANDLE hFile = FindFirstFileA(FindPath.c_str(), &FindData);
	if(hFile != INVALID_HANDLE_VALUE)
	{
		do
		{
			//検索結果がディレクトリの場合はリストに追加
			if(strcmp(FindData.cFileName, ".") != 0 && strcmp(FindData.cFileName, "..") != 0 && (FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0)
			{
				FindFiles.push_back(FindData.cFileName);
			}
		}
		while(FindNextFileA(hFile, &FindData) != FALSE);
	}

	FindClose(hFile);
	return std::move(FindFiles);
}

std::vector<std::string> enumerate_files_and_directories(const std::string& path)
{
	std::vector<std::string> FindFiles;

	if(!exists(path))
	{
		return std::move(FindFiles);
	}
	std::string FindPath = path + "*.*";

	WIN32_FIND_DATAA FindData;
	HANDLE hFile = FindFirstFileA(FindPath.c_str(), &FindData);
	if(hFile != INVALID_HANDLE_VALUE)
	{
		do
		{
			if(strcmp(FindData.cFileName, ".") != 0 && strcmp(FindData.cFileName, "..") != 0)
			{
				//リストに追加
				FindFiles.push_back(FindData.cFileName);
			}

		}
		while(FindNextFileA(hFile, &FindData) != FALSE);
	}

	FindClose(hFile);
	return std::move(FindFiles);
}

void set_current(const std::string& path)
{
	SetCurrentDirectoryA(path.c_str());
}

std::string get_current()
{
	std::string path;
	path.resize((unsigned int)GetCurrentDirectoryA(0, NULL));
	GetCurrentDirectoryA(path.size(), &path[0]);
	return std::move(path);
}

}

}

}

#elif ARCHENGINE_PLATFORM_OSX

#endif