#pragma once
#include <string>
#include <fstream>

#include "Stream.h"

class FileStream :
	public Stream
{
public:
	FileStream(std::string filename);
	~FileStream();

	// Functions from Stream.
	char getChar();
	void ungetChar(char c);
	bool isEnd();
private:
	std::ifstream filestream;
};

