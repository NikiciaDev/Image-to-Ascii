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

		if (pixelsPerPixel == -1) return;

		std::vector<Pixel> averagedPixels, neededPixels;
		const unsigned int pWidth = width / 4;
		const unsigned short pixelsPerLine = pixelsPerPixel / 2;

		for (unsigned int i = 0; i < pixels.size(); i += pixelsPerLine) {
			if (pixels[i].used) continue;

			for (short s = 0; s < pixelsPerLine; s++) {
				for (short s2 = 0; s2 < pixelsPerLine; s2++) {
					if (i + (s * pWidth) + s2 >= pixels.size()) break;
					neededPixels.push_back(pixels[i + (s * pWidth) + s2]);
					pixels[i + (s * pWidth) + s2].used = true;
				}
			}

			unsigned int averagerRed = 0, averageGreen = 0, averageBlue = 0, averageAlpha = 0;
			for (Pixel p : neededPixels) {
				averagerRed += p.red;
				averagerRed += p.green;
				averagerRed += p.blue;
				averagerRed += p.alpha;
			}
			averagedPixels.push_back(Pixel(std::round(averagerRed / (float) pixelsPerPixel), std::round(averageGreen / (float) pixelsPerPixel),
				std::round(averageBlue / (float) pixelsPerPixel), std::round(averageAlpha / (float) pixelsPerPixel)));

			neededPixels.clear();
		}

		pixels.clear();
		pixels.assign(averagedPixels.begin(), averagedPixels.end());
		pixels.shrink_to_fit();
	}
}