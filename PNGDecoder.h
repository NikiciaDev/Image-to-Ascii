#pragma once
#include <vector>
#include <cmath>
#include "lodepng.h"
#include "Pixel.h"

namespace pdr {

	// Decodes a PNG and puts its pixels in the given vector
	void decode(const char* filename, unsigned int& width, unsigned int& height, std::vector<Pixel>& pixels, const short pixelsPerPixel);
}