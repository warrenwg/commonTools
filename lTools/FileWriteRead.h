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

	std::string readStr(char *path);
};
