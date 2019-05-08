#pragma once
class Stream {
public:
	/**
	* Gets the next char and advances the front of the stream.
	*/
	virtual char getChar() = 0;
	/**
	* Put the char back into the stream.
	*/
	virtual void ungetChar(char c) = 0;
	/**
	* Checks if at the end of the stream.
	*/
	virtual bool isEnd() = 0;
};

using StreamRef = std::reference_wrapper<Stream>;
