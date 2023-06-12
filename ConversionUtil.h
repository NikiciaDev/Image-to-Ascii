#pragma once

namespace cul {

	const short tableSize = 65;
	const char asciiTable[tableSize] = {'.', '`', '^', '"', ',', ':', ';', 'I', 'l', '!', 'i', '>', '<', '~', '+', '_', '-', '?', ']', '{', '}', '1', '(', '|', '\\', 't', 'f', 'j', 'r', 'x', 'n', 'u', 'v', 'c', 'z', 'X', 'Y', 'U', 'J', 'C', 'L', 'Q', '0', 'O', 'Z', 'm', 'w', 'q', 'p', 'd', 'b', 'k', 'h', 'a', 'o', '*', '#', 'M', 'W', '&', '8', '%', 'B', '@', '$'};

	// Converts the brightness array to its ASCII brightness mapping.
	void convertToAscii(unsigned char* brightness, const unsigned int arraySize, bool useReversedAsciiTable);
}