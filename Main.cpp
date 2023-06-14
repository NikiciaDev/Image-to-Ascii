#include <iostream>
#include <vector>
#include <Windows.h>
#include "SetupUtil.h"
#include "Pixel.h"
#include "PNGDecoder.h"
#include "ConversionUtil.h"
#include "BrightnessUtil.h"

void copyStringToClipboard(const std::string& string);

short brightnessCalculationAlgorithm = 0;
short pixelsPerPixel = -1;
double roundingPercision = 0;
bool useReversedAsciiTable = false;
bool copyToClipboard = false;
bool printToConsole = true;

int main(int argc, char* argv[]) {
	std::string pngPath;
	unsigned int width, height;

	while (true) {
		while (true) {
			if (sul::setup(pngPath, brightnessCalculationAlgorithm, roundingPercision, useReversedAsciiTable, copyToClipboard, pixelsPerPixel, printToConsole)) break;
		}

		std::vector<Pixel>* pixels = new std::vector<Pixel>;
		pdr::decode(pngPath.c_str(), width, height, *pixels, pixelsPerPixel);

		unsigned int pixelsSize = pixels->size();
		unsigned char* cPixels = new unsigned char[pixelsSize];
		for (unsigned int i = 0; i < pixelsSize; i++) {
			cPixels[i] = bul::calculateBrightness(pixels->at(i), brightnessCalculationAlgorithm);
		}

		pixels->clear();
		pixels->shrink_to_fit();
		delete pixels;

		cul::convertToAscii(cPixels, pixelsSize, useReversedAsciiTable, roundingPercision);
		std::cout << "Preparing ascii: ";

		double lastPercentage = -1;
		std::string asciiPNG;
		for (unsigned int i = 1; i <= pixelsSize; i++) {
			double percentage = i / (float) pixelsSize;
			if (lastPercentage == -1 || lastPercentage + 0.025 <= percentage) {
				std::cout << "|";
				lastPercentage = percentage;
			}
			asciiPNG += cPixels[i - 1];
			if (i % (width / (pixelsPerPixel == -1 ? 1 : pixelsPerPixel / 2)) == 0) {
				asciiPNG += "\n";
			}
		}
		if (printToConsole) std::cout << "\n" << asciiPNG;
		if (copyToClipboard) copyStringToClipboard(asciiPNG);
		std::cout << "\nFinnished!\n" << std::endl;

		delete[] cPixels;
	}
	
	return 0;
}

void copyStringToClipboard(const std::string& string) {
	const size_t len = string.size();
	if (len == 0) return;
	HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, len);
	memcpy(GlobalLock(hMem), string.c_str(), len);
	GlobalUnlock(hMem);
	OpenClipboard(0);
	EmptyClipboard();
	SetClipboardData(CF_TEXT, hMem);
	CloseClipboard();
}