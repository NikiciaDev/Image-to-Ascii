#include <iostream>
#include <vector>
#include "SetupUtil.h"
#include "Pixel.h"
#include "PNGDecoder.h"
#include "ConversionUtil.h"
#include "BrightnessUtil.h"

short brightnessCalculationAlgorithm = 0;
bool useReversedAsciiTable = false;

int main(int argc, char* argv[]) {
	std::string pngPath;
	unsigned int width, height;
	char ynInput;

	while (true) {
		while (true) {
			std::cout << "[ITA] Please input the path to the PNG you wish to convert.\n";
			std::cin >> pngPath;
			if (!sul::isValidPath(pngPath)) {
				std::cout << "[ITA] Path seems to be invalid!\n";
				continue;
			}
			std::cout << "[ITA] Please input the desired brightness calculation algorithm (0 - 3).\n";
			std::cin >> brightnessCalculationAlgorithm;
			if (brightnessCalculationAlgorithm < 0 || brightnessCalculationAlgorithm > 3) {
				std::cout << "[ITA] Invalid brightness calculation algorithm!\n";
				continue;
			}
			std::cout << "[ITA] Would you like to use a brightness reversed ascii table? (Y/N)\n";
			std::cin >> ynInput;
			if (ynInput != 'y' && ynInput != 'Y' && ynInput != 'n' && ynInput != 'N') {
				std::cout << "[ITA] Please either input \"Y\" or \"N\"!";
				continue;
			}
			useReversedAsciiTable = (ynInput == 'y' || ynInput == 'Y');
			break;
		}

		std::vector<Pixel>* pixels = new std::vector<Pixel>;
		pdr::decode(pngPath.c_str(), width, height, *pixels);

		unsigned int pixelsSize = pixels->size();
		unsigned char* cPixels = new unsigned char[pixelsSize];
		for (unsigned int i = 0; i < pixelsSize; i++) {
			cPixels[i] = bul::calculateBrightness(pixels->at(i), brightnessCalculationAlgorithm);
		}

		pixels->clear();
		pixels->shrink_to_fit();
		delete pixels;

		cul::convertToAscii(cPixels, pixelsSize, useReversedAsciiTable);
		std::cout << "\n";

		for (unsigned int i = 1; i <= pixelsSize; i++) {
			std::cout << cPixels[i - 1];
			if (i % width == 0) std::cout << "\n";
		}
		std::cout << std::endl;

		delete[] cPixels;
	}
	
	return 0;
}