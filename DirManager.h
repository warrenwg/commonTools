#pragma once
#include <iostream>
#include <string>
#include <direct.h> //_mkdir函数的头文件
#include <io.h>     //_access函数的头文件
#include <windows.h>
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

