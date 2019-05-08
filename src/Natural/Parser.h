#pragma once
#include <functional>

#include "Stream.h"

namespace Parser {
	template<typename T>
	struct ParseResult {
		bool success;
		T token;
	};

	template<typename T>
	using ParserFunction = std::function <ParseResult<T>(StreamRef)>;

	class Parser
	{
	public:
		Parser(StreamRef stream);
		~Parser();

	private:
	};
	/**
	* Creates a funtion that always fails to parse.
	*/
	template<typename T>
	ParserFunction<T> parseFailDummy();
	/**
	* Creates a function that always succeeds in parsing.
	*/
	template<typename T>
	ParserFunction<T> parsePassDummy();
	/**
	* Creates functions that parses a single char.
	*/
	ParserFunction<char>  parseSingleChar(char curr);
	/**
	* Creates parsers that parse a numeric char.
	*/
	ParserFunction<char> parseNumericChar();
	/**
	* Creates parsers that parse a alphabetic char.
	*/
	ParserFunction<char> parseAlphaChar();
	ParserFunction<char> parseLowerCaseAlphaChar();
	ParserFunction<char> parseUpperCaseAlphaChar();
	ParserFunction<std::string> parseCharToString(ParserFunction<char> inParser);
	/**
	* Creates parsers that parse a string exactly.
	*/
	ParserFunction<std::string> parseString(std::string match);
	/**
	* Creates functions that matche either of two parsers.
	*/
	template<typename T1, typename T2>
	auto parseOr(ParserFunction<T1> p1, ParserFunction<T2> p2);
	/**
	* Creates functions that match the first and then the second parser.
	*/
	template<typename T1, typename T2>
	auto parseAnd(ParserFunction<T1> p1, ParserFunction<T2> p2);
	/**
	* Creates functions that apply a funtion while parsing.
	*/
	template<typename inT, typename outT>
	auto parseApply(std::function<outT(inT)> f, ParserFunction<inT> p);
}
