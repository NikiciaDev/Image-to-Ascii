#pragma once

namespace cul {

	const short tableSize = 66;
	const char asciiTable[tableSize] = {' ' , '.', '`', '^', '"', ',', ':', ';', 'I', 'l', '!', 'i', '>', '<', '~', '+', '_', '-', '?', ']', '{', '}', '1', '(', '|', '\\', 't', 'f', 'j', 'r', 'x', 'n', 'u', 'v', 'c', 'z', 'X', 'Y', 'U', 'J', 'C', 'L', 'Q', '0', 'O', 'Z', 'm', 'w', 'q', 'p', 'd', 'b', 'k', 'h', 'a', 'o', '*', '#', 'M', 'W', '&', '8', '%', 'B', '@', '$'};
	const char reversedAsciiTable[tableSize] = {'$', '@', 'B', '%', '8', '&', 'W', '*', '#', 'o', 'a', 'h', 'k', 'b', 'd', 'p', 'q', 'w', 'm', 'Z', 'O', '0', 'Q', 'L', 'C', 'J', 'U', 'Y', 'X', 'z', 'c', 'v', 'u', 'n', 'x', 'r', 'j', 'f', 't', '\\', ' | ', '(', '1', ' }', '{', ']', ' ? ', ' - ', '_', ' + ', '~', ' < ', ' > ', 'i', '!', 'l', 'I', '; ', ':', ', ', '"', '^', '`', '.', ' '};

	// Converts the brightness array to its ASCII brightness mapping.
	void convertToAscii(unsigned char* brightness, const unsigned int arraySize, bool useReversedAsciiTable);
}