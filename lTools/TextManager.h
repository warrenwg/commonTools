#pragma once
#include <iostream>
#include <vector>

class TextManager
{
public:
	TextManager();
	~TextManager();

	void writetxt(std::vector<std::vector<float > > data, char* txt);
};

