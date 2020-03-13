#include "TextManager.h"
#include <fstream>


TextManager::TextManager()
{
}


TextManager::~TextManager()
{
}

void TextManager::writetxt(std::vector<std::vector<float >> data, char* txt){

	std::ofstream o_file(txt, std::ios::trunc);
	for (size_t i = 0; i < data.size(); i++)
	{
		for (size_t j = 0; j < data[i].size(); j++)
		{
			o_file << data[i][j];
			if (j != data[i].size()-1){
				o_file << ",";
			}
		}
		o_file << std::endl;
	}
}
