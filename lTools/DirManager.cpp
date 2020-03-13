#include "DirManager.h"
#include <time.h>


DirManager::DirManager()
{
}


DirManager::~DirManager()
{
}



void DirManager::tmkdir(std::string dir)
{
    int m = 0, n;
#ifdef __linux
    n =access(dir.c_str(), F_OK);
#else
    n = _access(dir.c_str(), 0); //判断该目录是否存在   //c_str()：生成一个const char*指针，指向str2
#endif
    //_access,确定文件或文件夹的访问权限。如果指定的存取方式有效，则函数返回0，否则函数返回-1。
    if (n == -1)
    {
		#ifdef __linux
		mkdir(dir.c_str(),S_IRUSR | S_IWUSR | S_IXUSR | S_IRWXG | S_IRWXO);
		#else
        _mkdir(dir.c_str());     //创建目录

		#endif
    }
}

void DirManager::newTimemkdir(std::string dir)
{
	int m = 0, n;
	std::string str1, str2;
	str1 = dir;
	str2 = str1.substr(0, 2);   //substr是C++语言函数，主要功能是复制子字符串，要求从指定位置开始，并具有指定的长度
	str1 = str1.substr(3, str1.size()); //  '//'算一个字符，转义字符
	while (m >= 0)
	{
		m = str1.find('\\');     //.find()是寻找该字符串下标位置
		str2 += '\\' + str1.substr(0, m);
	#ifdef __linux
		n = access(str2.c_str(), F_OK);
	#else
		n = _access(str2.c_str(), 0); //判断该目录是否存在   //c_str()：生成一个const char*指针，指向str2
		//_access,确定文件或文件夹的访问权限。如果指定的存取方式有效，则函数返回0，否则函数返回-1。
	#endif
		if (n == -1)
		{
			#ifdef __linux
			mkdir(str2.c_str(),S_IRUSR | S_IWUSR | S_IXUSR | S_IRWXG | S_IRWXO);
			#else
			_mkdir(str2.c_str());     //创建目录
			#endif
		}
		str1 = str1.substr(m + 1, str1.size());
	}
}


std::string DirManager::mkdirUseTime(std::string sProjectDir)
{
	char cNowTime[128];
	//获取当前时间保持到字符串中
#ifdef __linux

time_t timep;
struct tm *p;
time(&timep);
p=gmtime(&timep);
sprintf(cNowTime,"%d%d%d-%d%d%d",(1900+p->tm_year),(1+p->tm_mon),p->tm_mday,p->tm_hour,p->tm_min,p->tm_sec);

#else
	struct tm t;   //tm结构指针
	time_t now;  //声明time_t类型变量
	time(&now);      //获取系统日期和时间
	localtime_s(&t, &now);   //获取当地日期和时间

	strftime(cNowTime, sizeof(cNowTime), "%Y%m%d-%H%M%S", &t);
	//格式化输出本地时间
	//判断文件夹是否存在并且命名
#endif
	std::cout << cNowTime;
	//string sProjectDir = "D://lcmProject//";
    newTimemkdir(sProjectDir);
	std::string sNowTimeFileDir = sProjectDir + cNowTime;
    newTimemkdir(sNowTimeFileDir);

	return sNowTimeFileDir;
}