#include "BrightnessUtil.h"

namespace bul {
	unsigned char calculateBrightness(const Pixel& pixel, const short mode) {
		switch (mode) {
		case 0: // Average.
			return (((short) pixel.red) + ((short) pixel.green) + ((short) pixel.blue)) / 3;
			break;
		case 1: // Standard luminance.
			return 0.2126 * ((short) pixel.red) + 0.7152 * ((short) pixel.green) + 0.0722 * ((short) pixel.blue);
			break;
		case 2: // Perceived luminance.
			return 0.299 * ((short) pixel.red) + 0.587 * ((short) pixel.green) + 0.114 * ((short) pixel.blue);
			break;
		case 3: // Luminosity.
			0.299 * ((short) pixel.red) + 0.587 * ((short) pixel.green) + 0.114 * ((short) pixel.blue);
			break;
		}
		return 0;
	}
}