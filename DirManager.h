#pragma once
#include <iostream>
#include <string>

#ifdef  __linux

#include <unistd.h>
    #include <sys/types.h>
    #include <sys/stat.h>
#else
#include <direct.h> //_mkdir函数的头文件
#include <io.h>     //_access函数的头文件
#include <windows.h>

#endif

#include <vector>

class DirManager
{
public:
	DirManager();
	~DirManager();

    void tmkdir(std::string dir);
    void newTimemkdir(std::string dir);
	std::string mkdirUseTime(std::string sProjectDir);

};

