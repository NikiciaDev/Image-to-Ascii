#include "PNGDecoder.h"

namespace pdr {
	void pdr::decode(const char* filename, std::vector<Pixel>& pixels) {
		std::vector<unsigned char> vec;
		unsigned int width, height;
		unsigned int error = lodepng::decode(vec, width, height, filename);
		
		//COPE
		if (error) exit(-1);

		for (unsigned int i = 0; i < vec.size(); i += 4) {
			pixels.push_back(Pixel(vec[i], vec[i + 1], vec[i + 2], vec[i + 3]));
		}
	}
}