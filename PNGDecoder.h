#pragma once
#include <vector>
#include "lodepng.h"
#include "Pixel.h"

namespace pdr {

	// Decodes a PNG and puts its pixels in the given vector
	void decode(const char* filename, std::vector<Pixel>& pixels);
}