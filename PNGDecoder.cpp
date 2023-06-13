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
		const unsigned short pixelsPerLine = pixelsPerPixel / 2;
		const unsigned int pWidth = width / pixelsPerLine;

		for (unsigned int i = 0; i < pixels.size(); i++) {
			if (pixels[i].used) continue;

			for (short s = 0; s < pixelsPerLine; s++) {
				for (short s2 = 0; s2 < pixelsPerLine; s2++) {
					if (i + (s * width) + s2 >= pixels.size()) goto out;
					neededPixels.push_back(pixels[i + (s * width) + s2]);
					pixels[i + (s * width) + s2].used = true;
				}
			}

			unsigned int averageRed = 0, averageGreen = 0, averageBlue = 0, averageAlpha = 0;
			for (Pixel p : neededPixels) {
				averageRed += p.red;
				averageGreen += p.green;
				averageBlue += p.blue;
				averageAlpha += p.alpha;
			}
			averagedPixels.push_back(Pixel(std::round(averageRed / (float) pixelsPerPixel), std::round(averageGreen / (float) pixelsPerPixel),
				std::round(averageBlue / (float) pixelsPerPixel), std::round(averageAlpha / (float) pixelsPerPixel)));

			neededPixels.clear();
		}
		out:

		pixels.clear();
		pixels.assign(averagedPixels.begin(), averagedPixels.end());
		pixels.shrink_to_fit();
	}
}