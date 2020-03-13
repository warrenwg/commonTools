#include "FileWriteRead.h"
#include <time.h>
#include <lTools/LogTool.h>
#include <iostream>
#include <fstream>

FileWriteRead::FileWriteRead()
{
}
    
FileWriteRead::~FileWriteRead()
{
}

void FileWriteRead::writeBin(char *path, void *data, int datalen, int oneDataSize)
{

    FILE *pFile = NULL;
    if (pFile == NULL)
    {
        pFile = fopen(path, "wb");
    }
    if (pFile != NULL)
    {
        if (0 == fwrite(data, datalen, oneDataSize, pFile))
        {
            LOGE("%s fwrite err\r\n", path);
        }
        fclose(pFile);
    }
}

void FileWriteRead::readBin(char *path, void *data, int datalen, int oneDataSize)
{

    FILE *pFile = NULL;
    pFile = fopen(path, "rb");
    if (pFile != NULL)
    {
        if (0 == fread(data, datalen, oneDataSize, pFile))
        {
            LOGE("%s read file error \n", path);
        }

        fclose(pFile);
    }
}

void FileWriteRead::writeStr(char *path, std::string str)
{
    std::ofstream o_file(path, std::ios::trunc);

    if (!o_file.is_open())
    {
        LOGE("error,write file is not valid :%s \n", path);
        return;
    }

    o_file << str << std::endl;
    o_file.close();
}

std::string FileWriteRead::readStr(char *path)
{
    std::ifstream fin(path);

    if (!fin.is_open())
    {
        LOGE("error,read file is not valid :%s \n", path);
        return "";
    }

    std::string s;
    getline(fin, s);
    fin.close();
    return s;
}
