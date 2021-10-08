#include "ConfigWriteReader.h"
#include "LogTool.h"
#include "FileWriteRead.h"
#include <fstream>
#include <iostream>

ConfigWriteReader::ConfigWriteReader()
{
}


ConfigWriteReader::~ConfigWriteReader()
{
}

int ConfigWriteReader::readConfig(char * path,json& dataJson)
{
	// FileWriteRead tFileWriteRead;
	// json dataJson = json::object();
	// try
	// {
	// 	std::string dataStr = tFileWriteRead.readStr(path);
		
	// 	if (dataStr.size() > 0) {
	// 		dataJson = json::parse(dataStr);
	// 	}else{
	// 		printf("json str  is empty: %s \n",path);
	// 	}
	// }
	// catch(const std::exception& e)
	// {
	// 	printf("read config error :%s \n",path);
	// }
    std::ifstream jfile(path);
	if(jfile.is_open()){
		try
		{
			jfile >> dataJson;
			if(dataJson.empty()){
				LOGE("dataJson is empty :%s \n",path);
				return -1;
			}
		}
		catch(const std::exception& e)
		{
			LOGE("read jsonconfig error: %s \n",path);
			std::cerr << e.what() << '\n';
			return -1;
		}
	}else{
		jfile.close();
		return -1;
	}
	return 1;
}

int ConfigWriteReader::writeConfig(char * path,json data)
{
	FileWriteRead tFileWriteRead;
	std::string dataStr="";
	if(!data.empty()){
		dataStr = data.dump();
	}
	tFileWriteRead.writeStr(path, dataStr);
	return 1;
}
