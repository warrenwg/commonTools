#pragma once
#include <iostream>
#include <string>
#include <string.h>
#include <vector>


#ifdef __linux
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>

#else

#endif 
using namespace std;


class FileListRead
{
public:
	FileListRead();
	~FileListRead();

	std::vector<std::string> readFileLists(char* dir_name);
};

