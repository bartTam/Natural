#include "Parser.h"
namespace Parser {

	Parser::Parser(StreamRef stream)
	{
	}


	Parser::~Parser()
	{
	}

	ParserFunction<char> parseSingleChar(char curr)
	{
		return ParserFunction<char>([curr](StreamRef stream) -> ParseResult<char> {
			// Read char and advance stream
			char readChar = stream.get().getChar();
			if (readChar == curr) {
				// If correct, return char
				return { true, readChar }; 
			}
			else {
				// Otherwise, rewind the stream and return unsuccessful
				stream.get().ungetChar(readChar);
				return { false, 0 };
			}
		});
	}

	ParserFunction<char> parseNumericChar() {
		ParserFunction<char> parser = parseSingleChar('0');
		for (char c = '1'; c <= '9'; c++) {
			parser = parseOr(parser, parseSingleChar(c));
		}
		return parser;
	}

	ParserFunction<char> parseAlphaChar()
	{
		return parseOr(parseLowerCaseAlphaChar(), parseUpperCaseAlphaChar());
	}

	ParserFunction<char> parseLowerCaseAlphaChar()
	{
		ParserFunction<char> parser = parseFailDummy<char>();
		for (char c = 'a'; c <= 'z'; c++) {
			parser = parseOr(parser, parseSingleChar(c));
		}
		return parser;
	}

	ParserFunction<char> parseUpperCaseAlphaChar()
	{
		ParserFunction<char> parser = parseFailDummy<char>();
		for (char c = 'A'; c <= 'Z'; c++) {
			parser = parseOr(parser, parseSingleChar(c));
		}
		return parser;
	}

	ParserFunction<std::string> parseCharToString(ParserFunction<char> inParser)
	{
		return ParserFunction<std::string>([inParser](StreamRef stream) {
			return { true, std::string(1, inParser(stream).token) };
		});
	}

	ParserFunction<std::string> parseString(std::string match)
	{
		ParserFunction<std::string> parser = parseApply(
			[](char first) { std::string(a) }, 
			parseSingleChar(match[0]));
	}

	template<typename T>
	ParserFunction<T> parseFailDummy()
	{
		return ParserFunction<T>([](StreamRef stream) {
			return { false, 0 };
		});
	}

	template<typename T>
	ParserFunction<T> parsePassDummy()
	{
		return ParserFunction<T>([](StreamRef stream) {
			return { true, 0 };
		});
	}

	template<typename T1, typename T2>
	auto parseOr(ParserFunction<T1> p1, ParserFunction<T2> p2) {
		return std::function([](StreamRef stream) {
			ParseResult result1 = p1(stream);
			if (result1.success) {
				return result1;
			}
			ParseResult result2 = p2(stream);
			if (result2.success) {
				return result2;
			}
			return { false, 0 };
		});
	}

	template<typename T1, typename T2>
	auto parseAnd(ParserFunction<T1> p1, ParserFunction<T2> p2)
	{
		return std::function([](StreamRef stream) {
			ParseResult result1 = p1(stream);
			if (!result1.success) {
				return { false, 0 };
			}
			ParseResult result2 = p2(stream);
			if (!result2.success) {
				return { false, 0 };
			}
			return { true, result1.token + result2.token };
		});
	}

	template<typename inT, typename outT>
	auto parseApply(std::function<outT(inT)> f, ParserFunction<inT> p)
	{
		return ParserFunction<outT>([f](StreamRef stream) {
			auto result = p(stream);
			if (result.success) {
				return { true, f(result.token) };
			}
			else {
				return { false, 0 };
			}
		});
	}
}
