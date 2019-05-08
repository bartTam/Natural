#include "FileStream.h"



FileStream::FileStream(std::string filename) : filestream(filename)
{
}


FileStream::~FileStream()
{
}

char FileStream::getChar()
{
	if (isEnd()) {
		throw std::overflow_error("Attempted to read past end of file");
	}
	return filestream.get();
}

void FileStream::ungetChar(char c)
{
	filestream.unget();
}

bool FileStream::isEnd()
{
	return filestream.eof();
}
