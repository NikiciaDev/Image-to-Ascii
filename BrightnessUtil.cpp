#include "BrightnessUtil.h"

namespace bul {
	unsigned short calculateBrightness(Pixel& pixel, short mode) {
		switch (mode) {
		case 0: // Average.
			return pixel.red + pixel.green + pixel.blue / 3;
			break;
		case 1: // Standard luminance.
			return 0.2126 * pixel.red + 0.7152 * pixel.green + 0.0722 * pixel.blue;
			break;
		case 2: // Perceived luminance.
			return 0.299 * pixel.red + 0.587 * pixel.green + 0.114 * pixel.blue;
			break;
		case 3: // Luminosity.
			0.299 * pixel.red + 0.587 * pixel.green + 0.114 * pixel.blue;
			break;
		}
		return 0;
	}
}