#include "FileFunctions.h"

std::string ReadFileToString(const std::string& filePath)
{
	std::ifstream file(filePath);
	if (!file.is_open()) std::cout << "ERROR WHILE TRYING TO OPEN A FILE (ReadFileToString)" << "\n";
	std::stringstream buffer;
	buffer << file.rdbuf();
	return buffer.str();
}

