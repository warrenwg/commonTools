#pragma once
#include <iostream>
#include <string>
#include <direct.h> //_mkdir������ͷ�ļ�
#include <io.h>     //_access������ͷ�ļ�
#include <windows.h>
#include <vector>

class DirManager
{
public:
	DirManager();
	~DirManager();

	void newmkdir(std::string dir);
	std::string mkdirUseTime(std::string sProjectDir);

};

