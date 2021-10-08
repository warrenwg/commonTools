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

	int findStringIndex(std::vector<std::string> list,std::string s);

	std::string   replace_all(std::string&   str,const   std::string&   old_value,const   std::string&   new_value);   

	std::string   replace_all_distinct(std::string&   str,const   std::string&   old_value,const   std::string&   new_value);



};

