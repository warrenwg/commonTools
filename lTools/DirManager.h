#pragma once
#include <iostream>
#include <string>
#include <vector>


#ifdef  __linux

#include <unistd.h>
    #include <sys/types.h>
    #include <sys/stat.h>
#else
#include <direct.h> //_mkdir������ͷ�ļ�
#include <io.h>     //_access������ͷ�ļ�
#include <windows.h>

#endif


class DirManager
{
public:
	DirManager();
	~DirManager();

    void tmkdir(std::string dir);
    void newTimemkdir(std::string dir);
	std::string mkdirUseTime(std::string sProjectDir);

};

