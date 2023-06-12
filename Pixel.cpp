#include "Pixel.h"

Pixel::Pixel(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha) : red(red), green(green), blue(blue), alpha(alpha) {}

std::string Pixel::toString() {
	return "(" + std::to_string((int) red) + ", " + std::to_string((int) green) + ", " + std::to_string((int) blue) + ", " + std::to_string((int) alpha) + ")";
}