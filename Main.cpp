#include <iostream>
#include <vector>
#include "ArgumentsUtil.h"
#include "Pixel.h"
#include "PNGDecoder.h"
#include "ConversionUtil.h"
#include "BrightnessUtil.h"
#include "Console.h"

Console console(120, 40);
short brightnessCalculationAlgorithm = 0;
bool useReversedAsciiTable = false;

int main(int argc, char* argv[]) {
	std::string pngPath;
	unsigned int width, height;

	aul::parse(argc, argv, pngPath, brightnessCalculationAlgorithm, useReversedAsciiTable);

	std::vector<Pixel>* pixels = new std::vector<Pixel>;
	pdr::decode(pngPath.c_str(), width, height, *pixels);

	unsigned int pixelsSize = pixels->size();
	unsigned char* cPixels = new unsigned char[pixelsSize];
	for (unsigned int i = 0; i < pixels->size(); i++) {
		cPixels[i] = bul::calculateBrightness(pixels->at(i), brightnessCalculationAlgorithm);
	}
	pixels->clear();
	pixels->shrink_to_fit();
	delete pixels;

	cul::convertToAscii(cPixels, pixelsSize, useReversedAsciiTable);

	for (unsigned int i = 0; i < pixelsSize; i++) {
		std::cout << cPixels[i];
		if (i % width == 0) std::cout << "\n";
	}

	delete[] cPixels;
	return 0;
}