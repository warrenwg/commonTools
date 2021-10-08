#pragma once
#include <iostream>
#include <vector>
#include <stdio.h>
#include <string>
#include <string.h>
#include "json.hpp"
using json = nlohmann::json;

class ConfigWriteReader
{
public:
	ConfigWriteReader();
	~ConfigWriteReader();

	// json readConfig(char* path);
	int readConfig(char * path,json& dataJson);	
	int writeConfig(char* path, json data);
	
};

