#include "stdafx.h"
#include "DirManager.h"
#include <time.h>


DirManager::DirManager()
{
}


DirManager::~DirManager()
{
}


void DirManager::newmkdir(std::string dir)
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
		n = _access(str2.c_str(), 0); //�жϸ�Ŀ¼�Ƿ����   //c_str()������һ��const char*ָ�룬ָ��str2
		//_access,ȷ���ļ����ļ��еķ���Ȩ�ޡ����ָ���Ĵ�ȡ��ʽ��Ч����������0������������-1��
		if (n == -1)
		{
			_mkdir(str2.c_str());     //����Ŀ¼
		}
		str1 = str1.substr(m + 1, str1.size());
	}
}


std::string DirManager::mkdirUseTime(std::string sProjectDir)
{
	//��ȡ��ǰʱ�䱣�ֵ��ַ�����
	struct tm t;   //tm�ṹָ��
	time_t now;  //����time_t���ͱ���
	time(&now);      //��ȡϵͳ���ں�ʱ��
	localtime_s(&t, &now);   //��ȡ�������ں�ʱ��
	char cNowTime[64];
	strftime(cNowTime, sizeof(cNowTime), "%Y%m%d-%H%M%S", &t);
	//��ʽ���������ʱ��
	//�ж��ļ����Ƿ���ڲ�������
	std::cout << cNowTime;
	//string sProjectDir = "D://lcmProject//";
	newmkdir(sProjectDir);
	std::string sNowTimeFileDir = sProjectDir + cNowTime;
	newmkdir(sNowTimeFileDir);

	return sNowTimeFileDir;
}