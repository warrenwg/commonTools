#pragma once
#include <iostream>
#include <string>
#include <vector>

class FileWriteRead
{
public:
	FileWriteRead();
	~FileWriteRead();

	void writeBin(char *path, void *data, int datalen, int oneDataSize);

	void readBin(char *path, void *data, int datalen, int oneDataSize);

	void writeStr(char *path, std::string str);

	void writeOneLine(char *path, std::string strLine);

	std::string readStr(char *path);

	int getDevice(const char* path,int& value);

	int getDevice(const char* path,char* value);

	int setDevicePlus(const char* path,int value);

	int setDevice(const char* path,int value);

	int setDevice(const char* path,char* value);	

	int getProp(const char* prop,const char* defaultValue,int& value);

	int setProp(const char* prop,int value);

	int writeCSV(std::string path,std::vector<std::vector<std::string> > datas);

	int readCSV(std::string path,std::vector<std::vector<std::string> >& datas);


};
