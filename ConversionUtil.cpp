#include "ConversionUtil.h"

double cul::round(double value, double percision) {
	if (percision == 0) return value;
	return std::round(value / percision) * percision;
}

void cul::convertToAscii(unsigned char* brightness, const unsigned int arraySize, bool useReversedAsciiTable, double roundingPercision) {
	short index = 0;
	double percentage = 0;

	for (unsigned int i = 0; i < arraySize; i++) {
		percentage = ((short) brightness[i]) / 255.0;
		index = round(percentage, roundingPercision) * (tableSize - 1);
		brightness[i] = (useReversedAsciiTable ? asciiTable[tableSize - 1 - index] : asciiTable[index]);
	}
}