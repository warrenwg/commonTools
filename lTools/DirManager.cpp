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
    n = _access(dir.c_str(), 0); //�жϸ�Ŀ¼�Ƿ����   //c_str()������һ��const char*ָ�룬ָ��str2
#endif
    //_access,ȷ���ļ����ļ��еķ���Ȩ�ޡ����ָ���Ĵ�ȡ��ʽ��Ч����������0������������-1��
    if (n == -1)
    {
		#ifdef __linux
		mkdir(dir.c_str(),S_IRUSR | S_IWUSR | S_IXUSR | S_IRWXG | S_IRWXO);
		#else
        _mkdir(dir.c_str());     //����Ŀ¼

		#endif
    }
}

void DirManager::newTimemkdir(std::string dir)
{
	int m = 0, n;
	std::string str1, str2;
	str1 = dir;
	str2 = str1.substr(0, 2);   //substr��C++���Ժ�������Ҫ�����Ǹ������ַ�����Ҫ���ָ��λ�ÿ�ʼ��������ָ���ĳ���
	str1 = str1.substr(3, str1.size()); //  '//'��һ���ַ���ת���ַ�
	while (m >= 0)
	{
		m = str1.find('\\');     //.find()��Ѱ�Ҹ��ַ����±�λ��
		str2 += '\\' + str1.substr(0, m);
	#ifdef __linux
		n = access(str2.c_str(), F_OK);
	#else
		n = _access(str2.c_str(), 0); //�жϸ�Ŀ¼�Ƿ����   //c_str()������һ��const char*ָ�룬ָ��str2
		//_access,ȷ���ļ����ļ��еķ���Ȩ�ޡ����ָ���Ĵ�ȡ��ʽ��Ч����������0������������-1��
	#endif
		if (n == -1)
		{
			#ifdef __linux
			mkdir(str2.c_str(),S_IRUSR | S_IWUSR | S_IXUSR | S_IRWXG | S_IRWXO);
			#else
			_mkdir(str2.c_str());     //����Ŀ¼
			#endif
		}
		str1 = str1.substr(m + 1, str1.size());
	}
}


std::string DirManager::mkdirUseTime(std::string sProjectDir)
{
	char cNowTime[128];
	//��ȡ��ǰʱ�䱣�ֵ��ַ�����
#ifdef __linux

time_t timep;
struct tm *p;
time(&timep);
p=gmtime(&timep);
sprintf(cNowTime,"%d%d%d-%d%d%d",(1900+p->tm_year),(1+p->tm_mon),p->tm_mday,p->tm_hour,p->tm_min,p->tm_sec);

#else
	struct tm t;   //tm�ṹָ��
	time_t now;  //����time_t���ͱ���
	time(&now);      //��ȡϵͳ���ں�ʱ��
	localtime_s(&t, &now);   //��ȡ�������ں�ʱ��

	strftime(cNowTime, sizeof(cNowTime), "%Y%m%d-%H%M%S", &t);
	//��ʽ���������ʱ��
	//�ж��ļ����Ƿ���ڲ�������
#endif
	std::cout << cNowTime;
	//string sProjectDir = "D://lcmProject//";
    newTimemkdir(sProjectDir);
	std::string sNowTimeFileDir = sProjectDir + cNowTime;
    newTimemkdir(sNowTimeFileDir);

	return sNowTimeFileDir;
}