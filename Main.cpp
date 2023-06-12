#include <iostream>
#include <vector>
#include "ArgumentsUtil.h"
#include "Pixel.h"
#include "PNGDecoder.h"
#include "BrightnessUtil.h"
#include "Console.h"

Console console(120, 40);
std::string pngPath = "";
short brightnessCalculationAlgorithm = 0;

int main(int argc, char* argv[]) {
	aul::parse(argc, argv, pngPath, brightnessCalculationAlgorithm);

	std::vector<Pixel> pixels;
	pdr::decode(pngPath.c_str(), pixels);

	unsigned short* brightness = new unsigned short[pixels.size()];

	for (int i = 0; i < pixels.size(); i++) {
		brightness[i] = bul::calculateBrightness(pixels[i], brightnessCalculationAlgorithm);
		std::cout << brightness[i] << "\n";
	}

	delete[] brightness;
	return 0;
}