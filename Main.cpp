#include <iostream>
#include <vector>
#include "Pixel.h"
#include "PNGDecoder.h"
#include "Console.h"

std::string pngPath;

int main(int argc, char* argv[]) {
	if (argc != 2) exit(-1);
	pngPath = argv[1];

	std::vector<Pixel> pixels;
	pdr::decode(pngPath.c_str(), pixels);

	return 0;
}