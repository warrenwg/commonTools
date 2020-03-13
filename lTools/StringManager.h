#pragma once
#include <iostream>
#include <string>
#include <string.h>
#include <vector>


class StringManager
{
public:
	StringManager();
	~StringManager();

	std::vector<std::string> vStringSplit(const  std::string s, const std::string delim);
};

