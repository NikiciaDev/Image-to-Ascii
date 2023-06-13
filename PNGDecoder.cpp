#include "PNGDecoder.h"

namespace pdr {
	void pdr::decode(const char* filename, unsigned int& width, unsigned int& height, std::vector<Pixel>& pixels, const short pixelsPerPixel) {
		std::vector<unsigned char> vec;
		double lastPercentage = -1;
		unsigned int error = lodepng::decode(vec, width, height, filename);
		
		//COPE
		if (error) exit(-1);

		std::cout << "Decoding: ";
		for (unsigned int i = 0; i < vec.size(); i += 4) {
			double percentage = i / (vec.size() - 1.0);
			if (lastPercentage == -1 || (lastPercentage + (pixelsPerPixel == -1 ? 0.025 : 0.05)) <= percentage) {
				std::cout << "|";
				lastPercentage = percentage;
			}
			pixels.push_back(Pixel(vec[i], vec[i + 1], vec[i + 2], vec[i + 3]));
		}

		if (pixelsPerPixel == -1) {
			std::cout << "\nFinnished!\n";
			return;
		}

		lastPercentage = -1;
		std::vector<Pixel> averagedPixels, neededPixels;
		const unsigned short pixelsPerLine = pixelsPerPixel / 2;
		const unsigned int pWidth = width / pixelsPerLine;
		
		for (unsigned int i = 0; i < pixels.size(); i++) {
			double percentage = i / (pixels.size() - 1.0);
			if (lastPercentage == -1 || lastPercentage + 0.05 <= percentage) {
				std::cout << "|";
				lastPercentage = percentage;
			}
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
		std::cout << "\nFinnished!\n";

		pixels.clear();
		pixels.assign(averagedPixels.begin(), averagedPixels.end());
		pixels.shrink_to_fit();
	}
}