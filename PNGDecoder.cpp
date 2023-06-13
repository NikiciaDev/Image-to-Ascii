#include "PNGDecoder.h"

namespace pdr {
	void pdr::decode(const char* filename, unsigned int& width, unsigned int& height, std::vector<Pixel>& pixels, const short pixelsPerPixel) {
		std::vector<unsigned char> vec;
		unsigned int error = lodepng::decode(vec, width, height, filename);
		
		//COPE
		if (error) exit(-1);

		for (unsigned int i = 0; i < vec.size(); i += 4) {
			pixels.push_back(Pixel(vec[i], vec[i + 1], vec[i + 2], vec[i + 3]));
		}

		if (pixelsPerPixel == 1) return;

		std::vector<Pixel> averagedPixels;
		const unsigned int pWidth = width / 4;
		const unsigned short pixelsPerLine = pixelsPerPixel / 2;

		for (unsigned int i = 0; i < pixels.size(); i++) {
			unsigned int averagerRed = 0, averageGreen = 0, averageBlue = 0, averageAlpha = 0;
			if (pixels[i].used) continue;
			for (unsigned short s = 0; s < pixelsPerLine; s++) {
				averagerRed += pixels[i + s].red + pixels[i + pWidth + s].red;
				averageGreen += pixels[i + s].green + pixels[i + pWidth + s].green;
				averageBlue += pixels[i + s].blue + pixels[i + pWidth + s].blue;
				averageAlpha += pixels[i + s].alpha + pixels[i + pWidth + s].alpha;
				pixels[i + s].used = true;
				pixels[i + pWidth + s].used = true;
			}
			averagedPixels.push_back(Pixel(std::round(averagerRed / (float) pixelsPerPixel), std::round(averageGreen / (float) pixelsPerPixel),
				std::round(averageBlue / (float) pixelsPerPixel), std::round(averageAlpha / (float) pixelsPerPixel)));
		}

		pixels.clear();
		pixels.assign(averagedPixels.begin(), averagedPixels.end());
		pixels.shrink_to_fit();
	}
}