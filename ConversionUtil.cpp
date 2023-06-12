#include "ConversionUtil.h"
#include <iostream>

void cul::convertToAscii(unsigned char* brightness, const unsigned int arraySize, bool useReversedAsciiTable) {
	short index = 0;
	double percentage = 0;

	for (unsigned int i = 0; i < arraySize; i++) {
		percentage = ((short) brightness[i]) / 255.0;
		index = percentage * (tableSize - 1);
		brightness[i] = (useReversedAsciiTable ? reversedAsciiTable[index] : asciiTable[index]);
	}
}