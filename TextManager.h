#pragma once
#include <iostream>
#include <vector>

class TextManager
{
public:
	TextManager();
	~TextManager();

	void TextManager::writetxt(std::vector<std::vector<float >> data, char* txt);
};

